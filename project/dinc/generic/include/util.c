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

// #include <stdint.h>
// #include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>

#include <errno.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "msg_format.h"
#include "msg_hal.h"
#include "util.h"
#include "log.h"
#include "data_dev.h"
#include "version.h"


uint64_t util_get_dev_uid(void);

int util_allow_web_access_from_wan(int (*allow_access)(int enable), int sec);
uint32_t util_string_replace_token(char* pstr, const char token, const char replent);

#define IS_LITTLE_ENDIAN	(*(uint16_t *)"\0\1" >> 8)

struct stat_tbl g_stat_tbl[4];

int g_ipc_fd = 0;
struct sockaddr_in g_ipc_addr;

uint32_t g_conn_time[5];
uint32_t g_round_trip_latency;

int64_t g_handover_start_usec;

int g_dc_begin_stage = 0;
int g_report_length = 0;
int g_interval_counter = 0;
int g_debug_type = 0;

int g_report_interval = 0;

static int g_dc_id;

static uint32_t util_get_round_trip_latency(void);

uint32_t util_string_replace_token(char* pstr, const char token, const char replent)
{
    uint32_t cnt = 0;

    if (pstr == NULL) {
        return cnt;
    }

    size_t len = strlen(pstr);
    uint32_t i = 0;
    for (i = 0; i < len; i++)
    {
        if (pstr[i] == token)
        {
            pstr[i] = replent;
            cnt++;
        }
    }
    return cnt;
}

int util_parse_options(int argc, char *argv[], dc_routine_definition* def)
{
	int res = -1;
	int opt;

	// Bypass if it is started by ext cmd.
	if (def->dc_ext_cmd == 1) {
		return 0;
	}

	while ((opt = getopt(argc, argv, "c:v")) != -1)
	{
		if (opt == -1) {
			break;
		}

		switch (opt) 
		{
		case 'c':
			{
				if (def->dc_load_config != NULL)
				{
					def->dc_load_config(optarg);
				}
				res = 0;
			}
			break;

		case 'v':
			{
				print_version();

				if (def->dc_version != NULL)
				{
					def->dc_version();
				}
				res = -1;
			}
			break;
		default:
			{
				// do nothing
			}
			break;
		}
	}
	return res;
}

int util_write_data_to_ipc_channel(const void *data, int len)
{
	return sendto(g_ipc_fd, data, len, 0, (struct sockaddr *)&g_ipc_addr, sizeof(g_ipc_addr));
}

static uint32_t util_get_round_trip_latency(void)
{
	return g_round_trip_latency;
}

int util_start_ipc_routine(dc_routine_definition* def) 
{
	int enable;
	fd_set fds;
	
	struct timeval timeout;
	int select_cnt;
	char buffer[1024];
	int msg_len;

	int dc_report_interval = 0;
	int idle_threshold = 0;
	
	dc_routine_context context = {};
	
	int64_t handover_start_usec;
	int64_t timeout_usec;
	int64_t select_start_usec 		= 0;
	int64_t select_duration_usec 	= 0;
	int64_t routine_start_usec 		= 0;
	int64_t routine_duration_usec 	= 0;

	enum {
		INIT,
		REG_OK,
		AUTH_OK,
	} state;

	enable = 1;
	state = INIT;
	handover_start_usec = 0;
	timeout_usec = 0;

	g_dc_id = def->dc_id;

	context.send_dc_report = &util_send_report;
	context.send_dc_round_trip_latency_request = &util_send_round_trip_latency_request;
	context.send_dc_connection_history_information = &util_send_connection_history_information;
	context.get_dc_latest_round_trip_latency = &util_get_round_trip_latency;
	
	while (enable) 
	{
		FD_ZERO(&fds);
		FD_SET(g_ipc_fd, &fds);

		if (dc_report_interval == 0 && def->dc_generate_report_interval != NULL)
		{
			int interval = def->dc_generate_report_interval();
			context.report_interval_countdown = dc_report_interval = (interval > 0) ? interval : 0;
		}

		if (timeout_usec <= 0) 
		{
			memset(&timeout, 0, sizeof(timeout));
		} 
		else {
			timeout.tv_sec = (long)(timeout_usec / 1000000);
			timeout.tv_usec = (long)(timeout_usec % 1000000);
		}

		select_start_usec = util_get_time_usec();
		select_cnt = select(g_ipc_fd + 1, &fds, NULL, NULL, &timeout);

		if (select_cnt < 0) 
		{
			perror("select");
			return -1;
		}

		if (select_cnt > 0) 
		{
			select_duration_usec = util_get_time_usec() - select_start_usec;
			timeout_usec -= select_duration_usec;

			msg_len = recvfrom(g_ipc_fd, &buffer, sizeof(buffer), 0, NULL, NULL);

			if (msg_len < 0) 
			{
				perror("recvfrom");
				break;
			}

			if (msg_len < sizeof(struct data_header))
			{
				continue;
			}
			struct data_header* header = (struct data_header*) buffer;

			if (ntohl(header->dc_id) != def->dc_id)
			{
				continue;
			}

			switch (ntohl(header->type)) 
			{
			case IPC_MSG_DC_REGISTER_ACK:
			{
				if (msg_len < sizeof(struct data_header) + sizeof(struct dc_register_ack))
				{
					continue;
				}
				struct dc_register_ack* data = (struct dc_register_ack*) (buffer + sizeof(struct data_header));

				if (msg_len == (sizeof(struct data_header) + sizeof(struct dc_register_ack)))
				{
					state |= REG_OK;

					util_set_conn_time(data->net_up_time_list);

					if (def->on_network_entry_complete != NULL)
					{
						def->on_network_entry_complete(&context, data->net_search_latency);
					}

					// update report interval
					if (def->dc_generate_report_interval != NULL)
					{
						int interval = def->dc_generate_report_interval();
						if (interval > 0)
						{
							context.report_interval_countdown = dc_report_interval = interval;
						}
					}
				}
			}
			break;
			case IPC_MSG_SERVER_LOOKUP_RESULT:
			{
				if (msg_len < sizeof(struct data_header) + sizeof(struct dc_data))
				{
					continue;
				}
				
				struct dc_data* result = (struct dc_data*) (buffer + sizeof(struct data_header));

				idle_threshold = result->value[1];

				if (!result->value[0]) 
				{
					enable = 0;
					
					if (def->on_server_lookup_failed != NULL)
					{
						def->on_server_lookup_failed(&context);
					}
				} 
				else 
				{
					state |= AUTH_OK;

					if (def->on_server_lookup_success != NULL)
					{
						def->on_server_lookup_success(&context);
					}
				}
			}
			break;
			case IPC_MSG_GET_LATENCY_ACK:
			{
				// temporarily remove the size check, we need to test it in future 
				// if (msg_len < sizeof(struct data_header) + sizeof(struct dc_data))
				// {
				// 	continue;
				// }
				struct dc_data* result = (struct dc_data*) (buffer + sizeof(struct data_header));

				if (def->on_check_latency_ack != NULL)
				{
					def->on_check_latency_ack(&context, result->value[0]);
				}
				util_set_round_trip_latency(result->value[0]);
			}
			break;
			case IPC_MSG_DC_SHUT_DOWN:
			{
				enable = 0;
			}
			break;
			case IPC_MSG_DC_STATUS:
			{
				struct din_local_msg msg;
				msg.header.type = htonl(IPC_MSG_DC_STATUS_ACK);
				msg.header.dc_id = htonl(def->dc_id);
				util_write_data_to_ipc_channel(&msg, sizeof(msg.header));
			}
			break;
			case IPC_MSG_CUSTOM_EVENT:
			{
				if (msg_len < sizeof(struct data_header) + sizeof(struct dc_data))
				{
					continue;
				}
				struct dc_data* result = (struct dc_data*) (buffer + sizeof(struct data_header));

				if (!strncmp("HOBN", (char *)&result->value[0], 4) && (def->on_handover_start != NULL)) 
				{	
					// handover begin
					handover_start_usec = util_get_time_usec();

					def->on_handover_start(util_get_time_usec());
				} 
				else if (!strncmp("HOES", (char *)&result->value[0], 4) && (def->on_handover_end != NULL)) 
				{	
					// handover success
					const int64_t timestamp = util_get_time_usec();
					const int64_t latency = timestamp - handover_start_usec;

					def->on_handover_end(1, timestamp, latency);
					
					handover_start_usec = 0;
				} 
				else if (!strncmp("HOEF", (char *)&result->value[0], 4) && (def->on_handover_end != NULL)) 
				{	
					// handover fail
					const int64_t timestamp = util_get_time_usec();
					const int64_t latency = timestamp - handover_start_usec;

					def->on_handover_end(0, timestamp, latency);

					handover_start_usec = 0;
				}
			}
			break;
			default:
			{
				def->handle_extra_ipc_message(&context, ntohl(header->type));
			}
			break;
			}
		} 
		else {
			switch (state) 
			{
			case INIT:
			{
				struct din_local_msg msg;
				msg.header.type = htonl(IPC_MSG_DC_REGISTER);
				msg.header.dc_id = htonl(def->dc_id);
				util_write_data_to_ipc_channel(&msg, sizeof(msg.header));
				timeout_usec = 1000000;

				// Terminate loop early if it's ext cmd.
				if (def->dc_ext_cmd == 1) {
					enable = 0;
					break;
				}
			}
			break;
			default:
			{
				if ((state & AUTH_OK) == AUTH_OK)
				{
					routine_start_usec = util_get_time_usec();
					if (def->collect_dc_routine_info != NULL)
					{
						context.report_interval_countdown--;

						def->collect_dc_routine_info(&context, dc_report_interval, idle_threshold);
					}

					// update report interval
					if (context.report_interval_countdown <= 0 && def->dc_generate_report_interval != NULL)
					{
						int interval = def->dc_generate_report_interval();
						if (interval > 0)
						{
							context.report_interval_countdown = dc_report_interval = interval;
						}
					}
					
					routine_duration_usec = util_get_time_usec() - routine_start_usec;
					timeout_usec = 1000000 - routine_duration_usec;	
				}
			}
			break;
			}
		}
	}
	return 0;
}

uint64_t util_get_dev_uid(void)
{
	if (g_dev_info_report.uid == 0)
	{
		char uid[DEV_UID_LEN + 1];

		if (dev_get_uid(uid) < 0) 
		{
			return -1;
		} 
		else 
		{
			g_dev_info_report.uid = (uint64_t)strtoull(uid, NULL, 16);
		}
	}
	return g_dev_info_report.uid;
}

// Ian
int util_send_report_ex(const int msg_type, const int extra_role, const uint8_t* data, const int len, const int dc_id) {
	g_dc_id = dc_id;
	return util_send_report(msg_type, extra_role, data, len);
}

int util_send_report(const int msg_type, const int extra_role, const uint8_t* data, const int len)
{
	uint8_t buffer[1024];

	struct dc_report_header* header = (struct dc_report_header*) (buffer);
	
	header->header.type = htonl(IPC_MSG_SEND_REPORT);
	header->header.dc_id = htonl(g_dc_id);

	header->role = (g_dc_id & 0x3F) | extra_role;
	header->msg_type = msg_type;

	uint8_t* p = buffer + sizeof(struct dc_report_header);

	if ((header->role & DINP_HDR_MASK_UID) == DINP_HDR_MASK_UID)
	{
		PUT_INT(p, util_htonll(g_dev_info_report.uid), 64);
	}

	memcpy(buffer + (p - buffer), data, len);
	return util_write_data_to_ipc_channel(buffer, p - buffer + len);
}

int util_send_connection_history_information(const uint8_t* data, const int len)
{
	uint8_t buffer[1024];

	struct dc_report_header* info = (struct dc_report_header*) (buffer);

	info->header.type = htonl(IPC_MSG_SEND_CONN_HISTORY_INFO);
	info->header.dc_id = htonl(g_dc_id);

	info->role = (g_dc_id & 0x3F);
	info->msg_type = DINP_MSG_DC_CONN_HISTORY_INFO;

	memcpy(buffer + sizeof(struct dc_report_header), data, len);

	return util_write_data_to_ipc_channel(buffer, sizeof(struct dc_report_header) + len);	
}

int util_send_round_trip_latency_request(void) 
{
	struct data_header data;

	data.type = htonl(IPC_MSG_GET_LATENCY);
	data.dc_id = htonl(g_dc_id);

	return util_write_data_to_ipc_channel(&data, sizeof(data));
}

int util_start_dc_routine(int argc, char* argv[], dc_routine_definition* def) 
{
	// initial dc
	if (def->dc_init != NULL)
	{
		def->dc_init();
	}

	// parse standard options (-v/-c)
	if (util_parse_options(argc, argv, def) != 0)
	{
		return 1;
	}

	if (util_create_ipc_channel(def->dc_ip, def->dc_port) < 0) 
	{
		return 1;
	}

	if (util_start_ipc_routine(def) < 0)
	{
		return 1;
	}

	return 0;
}

int util_create_ipc_channel(char *ipstr, int port)
{
	// prevent null value
	ipstr = (ipstr == NULL) ? DIN_DEVICE_IP : ipstr;
	port  = (port == 0) ? DIN_IPC_PORT : port;

	g_ipc_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (g_ipc_fd == SOCKET_ERROR)
	{
		return (-1);
	}

	memset(&g_ipc_addr, 0, sizeof(g_ipc_addr));
	g_ipc_addr.sin_family = AF_INET;
	g_ipc_addr.sin_port = htons((unsigned short) port);
	g_ipc_addr.sin_addr.s_addr = inet_addr(ipstr);

	return 0;
}

int64_t util_get_time_usec(void) 
{
	struct timeval timeval = {0, 0};

	if (gettimeofday(&timeval, NULL) == -1) {
		LOGG_ERRNO("gettimeofday");
		return -1;
	}

	return (int64_t)((int64_t)timeval.tv_sec * 1000000 + timeval.tv_usec);
}

void util_set_conn_time(const uint32_t conn_time[]) 
{
	memcpy(g_conn_time, conn_time, sizeof(g_conn_time));
}

void util_set_round_trip_latency(const uint32_t latency)
{
	g_round_trip_latency = latency;
}

uint16_t util_htons(uint16_t val) {
	if (IS_LITTLE_ENDIAN) {
		val = (uint16_t)(
			((val & 0xFF00) >> 8) |
			((val & 0x00FF) << 8)
		);
	}
	
	return val;
}

uint32_t util_htonl(uint32_t val) {
	if (IS_LITTLE_ENDIAN) {
		val = (uint32_t)(
			((val & 0xFF000000) >> 24)	|
			((val & 0x00FF0000) >> 8)	|
			((val & 0x0000FF00) << 8)	|
			((val & 0x000000FF) << 24)
		);
	}
	
	return val;
}

uint64_t util_htonll(uint64_t val) {
	if (IS_LITTLE_ENDIAN) {
		val = (uint64_t)(
	       ((val & 0xFF00000000000000ULL) >> 56)	|
	       ((val & 0x00FF000000000000ULL) >> 40)	|
	       ((val & 0x0000FF0000000000ULL) >> 24)	|
	       ((val & 0x000000FF00000000ULL) >> 8)		|
	       ((val & 0x00000000FF000000ULL) << 8)		|
	       ((val & 0x0000000000FF0000ULL) << 24)	|
	       ((val & 0x000000000000FF00ULL) << 40)	|
	       ((val & 0x00000000000000FFULL) << 56)
		);
	}
	
	return val;
}

void *util_memcpy(void *dst, const void *src, size_t n) {
	size_t i;
	
	for (i = 0; i < n; i++) {
		*((char *)dst + i) = *((char *)src + i);
	}
	
	return dst;
}

int util_memcmp(const void *s1, const void *s2, size_t n) {
	const uint8_t *a1 = (const uint8_t *)s1;
	const uint8_t *a2 = (const uint8_t *)s2;
	size_t i;

	for (i = 0; i < n; i++) {
		int diff = (int)a1[i] - (int)a2[i];

		if (diff != 0) {
			return diff;
		}
	}

	return 0;
}

size_t util_strlen(const char *s) {
	const char *p = s - 1;
	
	while (*++p);
	return p - s;
}

double util_simple_sqrt(double val, double errors)
{
	if (val < 0)
	{
		return 0;
	}

	double top = (val > 1) ? val : 1;
	double bottom = 0;
	double result = 0;
	double diff = 0;
	do
	{
		result = (top + bottom) / 2;

		diff = (result * result) - val;
		if (diff > 0)
		{
			top = result;
		}
		else if (diff < 0)
		{
			bottom = result;
			diff *= -1;
		}

		if (diff == 0 || diff < errors) break;
	}
	while(diff > errors);

	return result;
}

int util_allow_web_access_from_wan(int (*allow_access)(int enable), int sec)
{
	int ret = 0;

	const pid_t cpid = fork();
	if (cpid < 0) {
		ret = -1;
	}

	if (cpid == 0)
	{
		int ret = 0;

	    if ((ret = allow_access(1)) != 0) {
	    	LOGG_ERR("Enable access from WAN function failed. Result: %d", ret);
	    	exit(ret);
	    }
	    LOGG_INFO("Enable access from WAN. Result: %d", ret);

	    LOGG_INFO("Start to sleep...");
	    sleep(sec);
	    LOGG_INFO("Stop sleeping...");

	    ret = allow_access(0);
	    LOGG_INFO("Disable access from WAN. Result: %d", ret);
	    exit(ret);
	}

	return ret;
}

double util_unsafe_sqrt(double val, int digits)
{
	if (INT_MAX != 0x7FFFFFFF)
	{
		LOGG_ERR("Only 32bit INT supported now");
		exit(1);
	}

	if (val < 0 || digits < 0)
	{
		return 0;
	}

	if (val > 926)       { digits = 0; } // if val > 926 and digits > 0 then the value of (result*result) will exceed INT_MAX
	else if (val > 9)  	 { digits = 1; } // if val > 9 and digits > 1 then the value of (result*result) will exceed INT_MAX
	else if (digits > 2) { digits = 2; } // then maximum can only be 2

	int pow10 = 1;
	int pow100 = 1;
	int i = 0;
	for (i = 0; i < digits; i++)
	{
		pow100 *= 100;
		pow10 *= 10;
	}

	int ival = (int) (val * pow100);
	
	int top = (val > 1) ? ival : pow100;
	int bottom = 0;
	int result = 0;
	int diff = 0;
	do
	{
		result = (top + bottom) / 2;

		int d = (result * result) - ival;
		if (d > 0)
		{
			top = result;
		}
		else if (d < 0)
		{
			bottom = result;
			d *= -1;
		}

		if (d == 0 || d == diff) {
			break;
		}
		diff = d;
	}
	while(diff > pow10);

	return (double) result / pow10;
}