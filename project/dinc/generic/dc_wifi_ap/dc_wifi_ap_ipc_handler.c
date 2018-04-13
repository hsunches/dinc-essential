/*
 * MOBRIC CONFIDENTIAL
 * ___________________
 *
 * 2013 Mobric Incorporated
 * All Rights Reserved.
 *
 * NOTICE:
 * All information contained herein is, and remains the property of
 * Mobric Incorporated and its suppliers, if any. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Mobric Incorporated.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "msg_format.h"
#include "dc_wifi_ap_data_set.h"
#include "dc_wifi_ap_ipc_handler.h"
#include "dc_wifi_ap_data_collector.h"
#include "util.h"

struct cmd {
	uint32_t type;
	uint32_t dc_id;

	union {
		uint8_t data[20];
		uint32_t value[6];
	};
};

static int write_data_to_ipc_channel(const void *data, int len);
// static int64_t get_time_usec(void);

// static int g_ipc_fd = 0;
// static struct sockaddr_in g_ipc_addr;
extern int g_ipc_fd;
extern struct sockaddr_in g_ipc_addr;

int start_wifi_ap_ipc_routine(void) {
	int enable;
	fd_set fds;
	struct timeval timeout;
	int select_cnt;
	struct cmd cmd;
	int cmd_len;
	write_func writer;
	int64_t timeout_usec;
	int64_t select_start_usec, select_duration_usec;
	int64_t routine_start_usec, routine_duration_usec;

	enum {
		INIT,
		REG_OK,
		AUTH_OK,
	} state;

	enable = 1;
	state = INIT;
	writer = &write_data_to_ipc_channel;
	timeout_usec = 0;

	while (enable) {
		FD_ZERO(&fds);
		FD_SET(g_ipc_fd, &fds);

		if (timeout_usec <= 0) {
			memset(&timeout, 0, sizeof(timeout));
		} else {
			timeout.tv_sec = (long)(timeout_usec / 1000000);
			timeout.tv_usec = (long)(timeout_usec % 1000000);
		}

		select_start_usec = util_get_time_usec();
		select_cnt = select(g_ipc_fd + 1, &fds, NULL, NULL, &timeout);

		if (select_cnt < 0) {
			perror("select");
			return -1;
		}

		if (select_cnt > 0) {
			select_duration_usec = util_get_time_usec() - select_start_usec;
			timeout_usec -= select_duration_usec;
			cmd_len = recvfrom(g_ipc_fd, &cmd, sizeof(cmd), 0, NULL, NULL);

			if (cmd_len < 0) {
				perror("recvfrom");
				break;
			}

			if (ntohl(cmd.dc_id) != IPC_DC_WIFI_AP) {
				continue;
			}

			switch (ntohl(cmd.type)) 
			{
			case IPC_MSG_DC_REGISTER_ACK:
				if (cmd_len == (sizeof(struct data_header) + sizeof(struct dc_register_ack))) {
					state |= REG_OK;
				}

				break;

			case IPC_MSG_SERVER_LOOKUP_RESULT:
				{
					// get idle threshold
					gp_wifi_ap_cfg->idle_threshold = cmd.value[1];
					
					if (!cmd.value[0]) 
					{
						enable = 0;
					} 
					else 
					{
						state |= AUTH_OK;
						clct_wifi_ap_dev_info(writer);
					}

					break;
				}	
			case IPC_MSG_DC_SHUT_DOWN:
				enable = 0;
				break;
			case IPC_MSG_DC_STATUS:
				cmd.type = htonl(IPC_MSG_DC_STATUS_ACK);
				cmd.dc_id = htonl(IPC_DC_WIFI_AP);
				write_data_to_ipc_channel(&cmd, sizeof(uint32_t) * 2);
				break;
			}
		} else {
			switch (state) {
			case INIT:
				cmd.type = htonl(IPC_MSG_DC_REGISTER);
				cmd.dc_id = htonl(IPC_DC_WIFI_AP);
				write_data_to_ipc_channel(&cmd, sizeof(uint32_t) * 2);
				timeout_usec = 1000000;
				break;
				
			default:
				if ((state & AUTH_OK) == AUTH_OK)
				{
					routine_start_usec = util_get_time_usec();
					clct_wifi_ap_routine_info(writer);
					routine_duration_usec = util_get_time_usec() - routine_start_usec;
					timeout_usec = 1000000 - routine_duration_usec;
				}
				break;
			}
		}
	}

	return 0;
}

static int write_data_to_ipc_channel(const void *data, int len) {
	return sendto(g_ipc_fd, data, len, 0, (struct sockaddr *)&g_ipc_addr, sizeof(g_ipc_addr));
}

// static int64_t get_time_usec(void) {
// 	struct timeval timeval;

// 	gettimeofday(&timeval, NULL);
// 	return (int64_t)(timeval.tv_sec * 1000000 + timeval.tv_usec);
// }
