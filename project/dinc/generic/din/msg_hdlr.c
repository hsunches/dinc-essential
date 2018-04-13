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
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <limits.h>
#include "msg_hdlr.h"
#include "msg_util.h"
#include "err_code.h"
#include "cfg.h"
#include "net.h"
#include "thread.h"
#include "misc.h"
#include "log.h"
#include "msg_format.h"
#include "util.h"
#include "version.h"

#define BUF_SIZE				512
// #define MAX_CMD_CONTENT_LEN		512
// #define MAX_STR_LEN				128
#define NET_UP_TIME_LIST_SIZE	5
#define SERVER_ADDR_LIST_SIZE	16
#define SERVER_PORT_LIST_SIZE	16
#define LAT_FAIL_MAX			65535

enum {
	LOCAL,
	REMOTE
};

enum {
	OPEN_SOCKET,
	CLOSE_SOCKET
};

enum pipe_opt{
	OPEN,
	GET_READ,
	CLOSE_READ,
	GET_WRITE,
	CLOSE_WRITE,
	CLOSE_ALL
};

enum handshake_opt {
	CONTINUE,
	TERMINATE
};

enum conn_state {
	DISCONNECTED,
	CONNECTED
};

enum search_state {
	INIT,
	IN_PROGRESS,
	WAIT,
	SUCCESS,
	FAIL
};

enum dc_info_type {
	NET_SEARCH_START,
	NET_SEARCH_END
};

/* Timer info for the send dev info period. */
static time_t g_dev_info_last_update_time;
static uint8_t g_dev_info_last_update_time_init = 0;

static enum conn_state g_conn_state;
static int64_t g_select_timeout_usec;

static struct dc_info {
	pid_t pid;
	struct sockaddr_in addr;
	int64_t net_search_start_time;						// microseconds (us)
	uint32_t net_search_latency;						// milliseconds (ms), network order
	uint32_t net_up_time_list[NET_UP_TIME_LIST_SIZE];	// seconds (s), network order
} g_dc_info_list[MAX_DC_CNT];

static struct {
	enum search_state state;
	int fd[2];
	char domain_name[MAX_STR_LEN];
} g_search_info;

static struct {
	int is_active;
	socklen_t len;

	union {
		struct sockaddr addr;
		struct sockaddr_in addr_v4;
		struct sockaddr_in6 addr_v6;
	};
} g_server_addr;

struct socket_fd {
	int fd[2];
};

extern uint32_t conv_dc_name_to_id(const char *name);
extern int conv_dc_id_to_name(int id, char *name);

static int hdl_msg(const int fd[], int type);
static int hdl_local_msg(const int fd[], struct din_local_msg *p_msg, int msg_len, const struct sockaddr_in *p_addr);
static int hdl_remote_msg(const int fd[], void *data, int data_len, const struct sockaddr *p_addr, socklen_t addr_len);
static void bcast_cmd(int fd, uint32_t cmd_type, const void *data, int len);
static int send_cmd(int fd, uint32_t cmd_type, uint32_t dc_id, const void *data, int len);
static int send_remote_msg(int fd, const void *data, int data_len, const struct sockaddr *p_addr, socklen_t addr_len);
static int search_server(const int fd[], const char *domain_name);
static int handshake(int fd, const struct sockaddr *p_addr, socklen_t addr_len);
static int send_conn_history_info(int fd);
static int start_latency_test(int fd, uint32_t requester);
static void stop_latency_test(int fd, int is_success);
static int respond_request(const void *data, int len, const struct sockaddr_in *p_addr);
static int pack_and_send_ext_cmd_ack(char *cmd, uint32_t value, int ret);
// static int init_ext_cmd_routine();

static void set_dev_info(const void *data, int len);
static void set_conn_state(enum conn_state state);
static void set_select_timeout(int64_t timeout_usec);
static void set_search_info(enum search_state state, const int fd[], const char *domain_name);
static void set_server_addr(const struct sockaddr *p_addr, int addr_len);
static void set_latency_test_info(int is_start, uint32_t requester);
static void set_dc_info(int type, uint32_t id, const struct sockaddr_in *p_addr);
static void set_conn_history_info(const void *data, int len);
static void reset_dc_activity(void);
static struct dc_info *get_dc_info(uint32_t id);
static int lock_pid_file(const char* dc);
static int unlock_pid_file(const int fd);
static int parse_standard_options(int argc, char *argv[], void* handle);

static pid_t start_dc(int argc, char *argv[]);
static void search_server_impl(void);
static int search_server_pipe(const int option);
static struct socket_fd* din_socket_fds(const int option);
static void exit_msg_hdlr(void);
void handle_options(int argc, char* argv[]);
void handle_ext_cmd_child_process(void *lib_handle,
								  char *pid_name,
								  char cmd[5],
								  uint32_t value,
								  int (*prog)(uint8_t, uint32_t));
int update_dev_info(int fd);

static int unlock_pid_file(const int fd) 
{
	if (fd < 0) {
		LOGG_ERR("unlock parameter error");
		return -1;
	}
	
	int res = lockf(fd, F_ULOCK, 0);
	if (res < 0)
	{
		LOGG_ERR("unlock pid file failed");
	}
	close(fd);
	return res;
}

static int lock_pid_file(const char* dc) 
{
	int fd;	
	char buf[32];

	char pid_file[32];
	sprintf(pid_file, "/var/run/dc_%s.pid", dc);

	fd = open(pid_file, O_CREAT | O_RDWR, 0666);
	if (fd < 0) {
		LOGG_ERR("open pid file failed: (%d)%s", errno, strerror(errno));
		return fd;
	}

	if (lockf(fd, F_TLOCK, 0) < 0) {
		LOGG_ERR("lock pid file failed: (%d)%s", errno, strerror(errno));
		close(fd);
		return -1;
	}

	sprintf(buf, "%u\n", getpid());
	if (write(fd, buf, strlen(buf)) < 0) {
		LOGG_ERR("%s", buf);
		close(fd);
		return -1;
	}
	return fd;
}

// this function is provided to older dc which will be called in each dc_main
void handle_options(int argc, char* argv[])
{
	void* handle = dlopen(NULL, RTLD_NOW);
	if (!handle) {
		LOGG_ERR("%s", dlerror());
		return;
	}
	parse_standard_options(argc, argv, handle);

	dlclose(handle);
}

static int parse_standard_options(int argc, char *argv[], void* handle)
{
	int res = -1;
	while (1) 
	{
		int opt = getopt(argc, argv, "c:v");

		if (opt == -1) {
			break;
		}

		switch (opt) 
		{
		case 'c':
			{
				char func[32];
				sprintf(func, "dc_%s_load_config", argv[0]);
				dlerror();
				void (*dc_load_config)(const char*) = dlsym(handle, func);
				char *error = dlerror();

				if (error == NULL)
				{
					dc_load_config(optarg);
				}
				res = 0;
			}
			break;

		case 'v':
			{
				print_version();

				char func[32];
				sprintf(func, "dc_%s_version", argv[0]);
				dlerror();
				void (*dc_version)(void) = dlsym(handle, func);
				char *error = dlerror();

				if (error == NULL)
				{
					dc_version();
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

static pid_t start_dc(int argc, char *argv[]) 
{
	if (argv == NULL) {
		return 0;
	}
	
	void* lib_handle = dlopen(NULL, RTLD_NOW);
	if (!lib_handle) {
		LOGG_ERR("%s", dlerror());
		return 0;
	}

	char func[32];
	sprintf(func, "dc_%s_main", argv[0]);
	
	dlerror();
	int (*dc_main)(int, char**) = dlsym(lib_handle, func);
	char *error = dlerror();

	if (error != NULL) {
		LOGG_ERR("%s", error);
		dlclose(lib_handle);
		return 0;
	}

	// try to lock pid file to determine if there is a dc already running
	int fd = lock_pid_file(argv[0]);
	if (fd < 0) {
		dlclose(lib_handle);
		return 0;
	}
	unlock_pid_file(fd); // if pass then unlock it

	// fork a process to execute dc main function in child process
	const pid_t pid = fork();
	if (pid < 0) {
		LOGG_ERRNO("fork failed");
		dlclose(lib_handle);
		return -1;
	}

	if (pid == 0)
	{
		// this is the child process
		if ((fd = lock_pid_file(argv[0])) < 0) {
			dlclose(lib_handle);
			LOGG_DBG("DC %s has already started, close this call", (char *) argv[0]);
			exit(0);
		}

		const int r = dc_main(argc, argv);

		unlock_pid_file(fd);
		dlclose(lib_handle);
		LOGG_DBG("Child process DC %s is done", (char *) argv[0]);
		exit(r);
	}
	dlclose(lib_handle);
	return pid;
}

static struct socket_fd* din_socket_fds(const int option)
{
	static struct socket_fd sfd;

	switch(option)
	{
		case OPEN_SOCKET:
		{
			sfd.fd[LOCAL] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			sfd.fd[REMOTE] = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);

			// in case device not support IPv6
			if (sfd.fd[REMOTE] < 0)
			{
				sfd.fd[REMOTE] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);				
			}

			if (sfd.fd[LOCAL] < 0 || sfd.fd[REMOTE] < 0) 
			{
				LOGG_ERRNO("socket");
				return NULL;
			}
		}
		break;
		case CLOSE_SOCKET:
		{
			int i;
			for (i = 0; i < ARRAY_SIZE(sfd.fd); i++) 
			{
				if (sfd.fd[i] > 0) 
				{
					close(sfd.fd[i]);
				}
			}
			return NULL;
		}
		break;
	}

	return &sfd;
}

static void exit_msg_hdlr(void)
{
	LOGG_FUNC_IN();

	search_server_pipe(CLOSE_ALL);

	din_socket_fds(CLOSE_SOCKET);

	LOGG_FUNC_OUT();
}

void start_msg_hdlr(void) {
	struct socket_fd* p_sfd;
	int nfds;
	fd_set fds;
	int select_cnt;
	struct sockaddr_in addr;
	struct timeval timeout;
	struct timeval *p_timeout;
	int64_t start_time_usec;
	int64_t end_time_usec;
	int64_t duration_usec;
	int i;

	atexit(exit_msg_hdlr);

	set_conn_state(DISCONNECTED);
	set_select_timeout(-1);
	set_search_info(FAIL, NULL, NULL);
	set_latency_test_info(0, -1);

	do {
		if ((p_sfd = din_socket_fds(OPEN_SOCKET)) == NULL)
		{
			break;
		}

		memset(&addr, 0, sizeof(struct sockaddr_in));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(DIN_IPC_PORT);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		LOGG_INFO("Bind port %d", DIN_IPC_PORT);

		if (bind(p_sfd->fd[LOCAL], (struct sockaddr *)&addr, sizeof(addr)) < 0) {
			LOGG_ERRNO("bind");
			break;
		}

		p_timeout = NULL;

		while (1) {
			FD_ZERO(&fds);
			FD_SET(p_sfd->fd[LOCAL], &fds);
			FD_SET(p_sfd->fd[REMOTE], &fds);
			nfds = (p_sfd->fd[LOCAL] > p_sfd->fd[REMOTE] ? p_sfd->fd[LOCAL] : p_sfd->fd[REMOTE]) + 1;

			start_time_usec = get_time_now_usec();
			select_cnt = select(nfds, &fds, NULL, NULL, p_timeout);
			end_time_usec = get_time_now_usec();

			if (select_cnt < 0) {
				LOGG_ERRNO("select");
				break;
			}

			for (i = 0; i < ARRAY_SIZE(p_sfd->fd); i++) 
			{
				if (FD_ISSET(p_sfd->fd[i], &fds)) {
					hdl_msg(p_sfd->fd, i);
				}
			}

			update_dev_info(p_sfd->fd[REMOTE]);

			if (g_select_timeout_usec == -1) 
			{
				LOGG_DBG("Timeout setting for selecting socket: infinite");
				p_timeout = NULL;
			} 
			else {
				if (p_timeout == NULL) 
				{
					get_timeval_from_usec(&timeout, g_select_timeout_usec);
					LOGG_DBG("Timeout setting for selecting socket(init): %ld.%06ld", timeout.tv_sec, timeout.tv_usec);
					p_timeout = &timeout;
				} 
				else 
				{
					duration_usec = end_time_usec - start_time_usec;
					g_select_timeout_usec -= duration_usec;

					if (g_select_timeout_usec > 0) 
					{
						get_timeval_from_usec(&timeout, g_select_timeout_usec);
						LOGG_DBG("Timeout setting for selecting socket(next): %ld.%06ld", timeout.tv_sec, timeout.tv_usec);
						p_timeout = &timeout;
					} 
					else 
					{
						LOGG_DBG("Timeout when selecting sockets");

						if (g_latency_test_info.is_testing) 
						{
							stop_latency_test(p_sfd->fd[LOCAL], 0);
						} else {
							set_select_timeout(-1);
							search_server(NULL, NULL);
						}

						p_timeout = NULL;
					}
				}
			}
		}
	} while (0);
}

int send_event(uint32_t type, const void *data, int len) {
	int fd;
	struct sockaddr_in addr;
	int ret;
	struct din_local_msg msg;

	LOGG_FUNC_IN();

	do {
		if (len > MAX_EVENT_CONTENT_LEN) {
			LOGG_ERR("Content too large");
			ret = DIN_CONTENT_TOO_LARGE;
			break;
		}

		fd = socket(AF_INET, SOCK_DGRAM, 0);

		if (fd < 0) {
			LOGG_ERRNO("socket");
			ret = DIN_CREATE_SOCK_FAIL;
			break;
		}

		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		addr.sin_port = htons(DIN_IPC_PORT);
		msg.header.type = htonl(type);

		if (data) {
			memcpy(msg.event.content, data, len);
		}
		
		ret = send_data(fd, &msg, sizeof(msg.header) + len, (struct sockaddr *)&addr, sizeof(addr));
		close(fd);
	} while (0);

	LOGG_FUNC_OUT();
	return ret;
}

static int respond_request(const void *data, int len, const struct sockaddr_in *p_addr) {
	int fd;
	int ret;

	uint8_t content[MAX_REPORT_DATA_LEN];
	memset(content, 0, sizeof(content));

	LOGG_FUNC_IN();

	do {
		if (len > MAX_REPORT_DATA_LEN) 
		{
			LOGG_ERR("Content too large");
			ret = DIN_CONTENT_TOO_LARGE;
			break;
		}

		fd = socket(AF_INET, SOCK_DGRAM, 0);

		if (fd < 0) 
		{
			LOGG_ERRNO("socket");
			ret = DIN_CREATE_SOCK_FAIL;
			break;
		}

		if (data) 
		{
			memcpy(content, data, len);
		}

		ret = send_data(fd, &content, len, (struct sockaddr *) p_addr, sizeof(struct sockaddr_in));
		
		close(fd);
	} while (0);

	LOGG_FUNC_OUT();
	return ret;
}

static int hdl_msg(const int fd[], int type) {
	uint8_t buf[BUF_SIZE];
	int buf_usage;
	struct sockaddr_in6 addr;
	socklen_t addr_len;

	addr_len = sizeof(addr);
	buf_usage = recvfrom(fd[type], buf, BUF_SIZE, 0, (struct sockaddr *)&addr, &addr_len);

	if (buf_usage <= 0) {
		LOGG_ERRNO("recvfrom");
		return DIN_RECV_DATA_FAIL;
	}

	if (type == LOCAL) 
	{
		return hdl_local_msg(fd, (struct din_local_msg *)buf, buf_usage, (struct sockaddr_in *)&addr);
	} else {
		return hdl_remote_msg(fd, buf, buf_usage, (struct sockaddr *)&addr, addr_len);
	}
}

static int hdl_local_msg(const int fd[], struct din_local_msg *p_msg, int msg_len, const struct sockaddr_in *p_addr) {
	struct dc_info *p_dc_info;
	uint32_t dc_id;
	// uint32_t value;
	struct dc_data result = {};
	int ret;

	LOGG_FUNC_IN();
	ret = DIN_NO_ERR;

	if (p_msg == NULL) {
		ret = DIN_INVALID_PARAM;
	} else {
		switch (ntohl(p_msg->header.type)) {
		case IPC_MSG_NETWORK_SEARCH:
			LOGG_INFO("Receive a network-search event");
			dc_id = ntohl(p_msg->event.value[0]);
			set_dc_info(NET_SEARCH_START, dc_id, NULL);
			break;

		case IPC_MSG_NETWORK_UP:
			LOGG_INFO("Receive a network-up event");
			g_latency_test_info.fail_cnt = 0; // reset latency fail count
			set_conn_state(CONNECTED);
			search_server_pipe(OPEN);
			ret = search_server(fd, (const char *)p_msg->event.content);
			break;

		case IPC_MSG_NETWORK_DOWN:
			LOGG_INFO("Receive a network-down event");
			set_conn_state(DISCONNECTED);
			set_search_info(FAIL, NULL, NULL);
			set_server_addr(NULL, 0);
			reset_dc_activity();
			break;

		case IPC_MSG_DC_WHO:
			LOGG_INFO("Receive a dc-who event");
			bcast_cmd(fd[LOCAL], IPC_MSG_DC_STATUS, NULL, 0);
			break;

		case IPC_MSG_DC_STATUS_ACK:
			LOGG_INFO("Receive a report dc-status ack command");

			dc_id = ntohl(p_msg->header.dc_id);
			printf("0X%x\n", dc_id);
			break;

		case IPC_MSG_DC_REGISTER:
			LOGG_INFO("Receive a DC-registration command");

			dc_id = ntohl(p_msg->header.dc_id);
			set_dc_info(NET_SEARCH_END, dc_id, p_addr);
			p_dc_info = get_dc_info(dc_id);

			if (p_dc_info != NULL)
			{
				struct dc_register_ack data;
				
				memcpy(data.net_up_time_list, p_dc_info->net_up_time_list, sizeof(p_dc_info->net_up_time_list));
				
				data.net_search_latency = p_dc_info->net_search_latency;
				
				ret = send_cmd(fd[LOCAL], IPC_MSG_DC_REGISTER_ACK, dc_id, &data, sizeof(data));
			}

			if (GET_CFG(op_mode) == 1) 
			{
				if (g_search_info.state == SUCCESS) 
				{
					// value = htonl(1);
					result.value[0] = htonl(1);
					ret = send_cmd(fd[LOCAL], IPC_MSG_SERVER_LOOKUP_RESULT, dc_id, &result, sizeof(struct dc_data));
				} 
				else if (g_search_info.state == FAIL) 
				{
					// value = 0;
					result.value[0] = 0;
					ret = send_cmd(fd[LOCAL], IPC_MSG_SERVER_LOOKUP_RESULT, dc_id, &result, sizeof(struct dc_data));
				}
			} 
			else 
			{
				// value = 0;
				result.value[0] = 0;
				ret = send_cmd(fd[LOCAL], IPC_MSG_SERVER_LOOKUP_RESULT, dc_id, &result, sizeof(struct dc_data));
			}

			break;

		case IPC_MSG_DC_START:
			{
				LOGG_INFO("Receive a start-dc event");
				int i = 0;
				char *argv[3];
				char *token = strtok((char *)p_msg->event.content, " ");

				while (token != NULL && i < 3) {
					argv[i++] = token;
					token = strtok(NULL, " ");
				}

				uint32_t id = conv_dc_name_to_id(argv[0]);
				optind = 1;
				
				pid_t dc_pid = -1;

				dc_pid = start_dc((sizeof(argv)/sizeof(char*)), argv);
						
				p_dc_info = get_dc_info(id);

				if (p_dc_info != NULL && p_dc_info->pid == 0)
				{
					p_dc_info->pid = dc_pid;
				}
			}
			break;

		case IPC_MSG_DC_STOP:
			{
				LOGG_INFO("Receive a stop-dc event");
				uint32_t id = conv_dc_name_to_id((char *)p_msg->event.content);

				p_dc_info = get_dc_info(id);
				if (p_dc_info != NULL && p_dc_info->pid > 0)
				{
					kill(p_dc_info->pid, SIGKILL);
					p_dc_info->pid = 0;
				}
			}
			break;

		case IPC_MSG_GET_LATENCY:
			LOGG_INFO("Receive a get-latency command");

			dc_id = ntohl(p_msg->header.dc_id);

			if (start_latency_test(fd[REMOTE], dc_id) != DIN_NO_ERR) {
				stop_latency_test(fd[LOCAL], 0);
			}
			break;

		case IPC_MSG_REPORT_UID:
			{
				LOGG_INFO("Receive a report-device-uid request");

				uint8_t data[8];
				uint8_t *p = data;
				PUT_INT(p, util_htonll(g_dev_info_report.uid), 64); 
				if (respond_request(data, sizeof(data), p_addr) != DIN_NO_ERR) 
				{
					LOGG_ERR("Fail to send report_dev_uid");
				}
			}
			break;

		case IPC_MSG_SPECIFY_UID:
			{
				LOGG_INFO("Receive a set-device-uid event");

				union t_convert
				{
					uint64_t uid64;
				    uint8_t  uid8[8]; 
				} convert;
				memset(convert.uid8, 0, sizeof(convert.uid8));

				char *p = (char *)p_msg->event.content;
				int v, i;
				for (i = 0; i < 8; i++)
				{
					sscanf(p, "%02x", &v);
					convert.uid8[i] = (uint8_t)v;
					p += 2;
				}
				g_dev_info_report.uid = util_ntohll(convert.uid64);
			}
			break;

		case IPC_MSG_REPORT_FULL_DOMAIN:
			{
				LOGG_INFO("Receive a report-domain-name request");
				
				if (respond_request(g_search_info.domain_name, strlen(g_search_info.domain_name), p_addr) != DIN_NO_ERR) 
				{
					LOGG_ERR("Fail to send report_full_domain");
				}
			}
			break;

		case IPC_MSG_REPORT_LATENCY_FAIL_CNT:
			{
				LOGG_INFO("Receive a report-server-latency-fail-cnt request");

				if (respond_request(&g_latency_test_info.fail_cnt, sizeof(g_latency_test_info.fail_cnt), p_addr) != DIN_NO_ERR) 
				{
					LOGG_ERR("Fail to send report_server-latency-fail-cnt");
				}
			}
			break;

		case IPC_MSG_SEND_REPORT:
			LOGG_INFO("Receive a send-report command");

			if (p_msg->header.dc_id == htonl(IPC_DC_DEV)) {
				printf("*********\n");
				set_dev_info(p_msg->cmd.content, msg_len - sizeof(struct data_header));
			} else {
				ret = send_remote_msg(fd[REMOTE], p_msg->cmd.content, msg_len - sizeof(struct data_header), NULL, 0);
			}

			break;

		case IPC_MSG_SET_DEVICE_INFO:
			{
				LOGG_INFO("Receive a device-information report");
				if (p_msg->header.dc_id == htonl(IPC_DC_DEV))
				{
					struct dev_info_report* report = (struct dev_info_report*) p_msg->cmd.content;

					// save device data into global variable
					g_dev_info_report.uid = util_ntohll(report->uid);
				}
			}
			break;

		case IPC_MSG_START_SERVER_HANDSHAKE:
			{
				LOGG_INFO("Receive a start-server-handshake event");
				set_search_info(IN_PROGRESS, NULL, NULL);
			}
			break;

		// case IPC_MSG_SET_DNS_TXT_QUERY_RESULT:
		// 	{
		// 		LOGG_INFO("Receive a set-dns-txt-query-result event");
		// 		load_cfg_str((char *)p_msg->event.content, " ");
		// 	}
		// 	break;
			// REMOVED

		case IPC_MSG_SEARCH_SERVER_FAIL:
			LOGG_INFO("Receive a search-server-fail event");
			set_search_info(FAIL, NULL, NULL);

			// set latency fail count to max number in order to enable server auto search
			g_latency_test_info.fail_cnt = LAT_FAIL_MAX;
			
			// value = 0;
			result.value[0] = 0;
			
			bcast_cmd(fd[LOCAL], IPC_MSG_SERVER_LOOKUP_RESULT, &result, sizeof(struct dc_data));

			break;

		case IPC_MSG_SEARCH_SERVER_WAIT:
			LOGG_INFO("Receive a search-server-wait event");
			set_search_info(WAIT, NULL, NULL);
			set_select_timeout(GET_CFG(max_latency) * 1000);
			break;

		case IPC_MSG_SEND_CONN_HISTORY_INFO:
			LOGG_INFO("Receive a send-conn-history-info command");
			set_conn_history_info(p_msg->cmd.content, msg_len - sizeof(struct data_header));
			ret = send_conn_history_info(fd[REMOTE]);
			break;

		case IPC_MSG_CUSTOM_EVENT:
			LOGG_INFO("Receive a custom event");
			dc_id = ntohl(p_msg->event.value[0]);
			ret = send_cmd(fd[LOCAL], IPC_MSG_CUSTOM_EVENT, dc_id, &p_msg->event.value[1], sizeof(uint32_t));
			break;

		default:
			LOGG_WARN("Receive an unknown local message");
			ret = DIN_UNKNOWN_MSG;
			break;
		}
	}

	LOGG_FUNC_OUT();
	return ret;
}

static int hdl_remote_msg(const int fd[], void *data, int data_len, const struct sockaddr *p_addr, socklen_t addr_len) {
	struct remote_msg *p_msg;
	char cmd[4 + 1];
	uint32_t is_auth_ok;
	struct dc_data result = {};
	int ret;

	LOGG_FUNC_IN();
	ret = DIN_NO_ERR;

	if (parse_remote_msg(&p_msg, data, data_len, (int32_t)time(NULL)) != DIN_NO_ERR) 
	{
		ret = DIN_INVALID_REMOTE_MSG;
	} else {
		memcpy(cmd, &p_msg->cmd, sizeof(p_msg->cmd));
		cmd[4] = '\0';
		LOGG_INFO("Receive %s command", cmd);

		if (!strcmp(cmd, "AUTH")) {
			set_select_timeout(-1);
			is_auth_ok = p_msg->value;
			
			if (is_auth_ok) 
			{
				LOGG_INFO("Authentication OK");
				is_auth_ok = htonl(is_auth_ok);

				// send gapi key to dc
				result.value[0] = htonl(is_auth_ok);
				// dc idle threshold
				result.value[1] = GET_CFG(idle_threshold);
				
				bcast_cmd(fd[LOCAL], IPC_MSG_SERVER_LOOKUP_RESULT, &result, sizeof(struct dc_data));
				
				// reset latency fail count to be ensured
				g_latency_test_info.fail_cnt = 0;

				set_search_info(SUCCESS, NULL, NULL);
				set_server_addr(p_addr, addr_len);
				send_conn_history_info(fd[REMOTE]);
			} 
			else 
			{
				LOGG_INFO("Authentication failed");
				ret = search_server(NULL, NULL);
			}
		} else if (!strcmp(cmd, "LATT")) {
			if (p_msg->value == g_latency_test_info.test_cnt) {
				stop_latency_test(fd[LOCAL], 1);
			}

		} else if (!strcmp(cmd, "DNSM")) {
			SET_CFG_INT(max_dns_query, p_msg->value);
		} else if (!strcmp(cmd, "HANS")) {
			SET_CFG_INT(max_handshake, p_msg->value);
		} else if (!strcmp(cmd, "DINM")) {
			SET_CFG_INT(op_mode, p_msg->value);

			if (GET_CFG(op_mode) == 0) {
				bcast_cmd(fd[LOCAL], IPC_MSG_DC_SHUT_DOWN, NULL, 0);
			}
		} else if (cmd[0] == '@') {
			memmove(cmd, &cmd[1], 3);
			cmd[3] = '&';

			if (system(cmd) < 0) {
				LOGG_WARN("Fail to execute %.3s", cmd);
			}
		} else if (cmd[0] == '>') {
			// cmd[0]: >; cmd[1]: dc offset; cmd[2]: command id; cmd[3]: ack;

			char dc[32];
			char prog_name[64];
			char pid_name[16];

			uint8_t dc_id = cmd[1];
			uint8_t type = cmd[2];

			if (conv_dc_id_to_name(dc_id, dc)) return DIN_INVALID_PARAM;

			sprintf(prog_name, "dc_%s_external_cmd_execute", dc);
			sprintf(pid_name, "%s_cmd_%d", dc, type);

			void* lib_handle = dlopen(NULL, RTLD_NOW);
			if (!lib_handle) {
				LOGG_ERR("%s", dlerror());
				return DIN_OPEN_FILE_FAIL;
			}

			dlerror();
			int (*prog)(uint8_t, uint32_t) = dlsym(lib_handle, prog_name);
			char *error = dlerror();

			if (error != NULL) {
				LOGG_ERR("%s", error);
				dlclose(lib_handle);
				return DIN_READ_FILE_FAIL;
			}

			// try to lock pid file to determine if it's already running
			int fd = lock_pid_file(pid_name);
			if (fd < 0) {
				dlclose(lib_handle);
				return DIN_DAEMON_ALREADY_EXISTS;
			}
			unlock_pid_file(fd); // if pass then unlock it

			// fork a process to execute dc main function in child process
			const pid_t pid = fork();
			if (pid < 0) {
				LOGG_ERRNO("fork failed");
				dlclose(lib_handle);
				return DIN_FORK_PROC_FAIL;
			}

			if (pid == 0)
			{
				handle_ext_cmd_child_process(lib_handle, pid_name, cmd, p_msg->value, prog);
			}
			dlclose(lib_handle);
		}
	}

	LOGG_FUNC_OUT();
	return ret;
}

void handle_ext_cmd_child_process(void *lib_handle,
								  char *pid_name,
								  char cmd[5],
								  uint32_t value,
								  int (*prog)(uint8_t, uint32_t)) {
	int fd;
	if ((fd = lock_pid_file(pid_name)) < 0) {
		dlclose(lib_handle);
		LOGG_DBG("Process for %s has already started, close this call", pid_name);
		exit(0);
	}

	int r = prog(cmd[2], value);
	/*
		Bits of cmd[3]:
		0: reserved
		1: reserved
		2: reserved
		3: reserved
		4: reserved
		5: 0 for success, 1 for fail
		6: 1 for supported, 0 for unsupported
		7: 1 for sending ack, 0 for not sending
	*/

	// Packing ack bits if necessary
	if (cmd[3] & 0x1) {
		if (r != -1) {
			cmd[3] |= (0x1<<1);
			if (r == 1) cmd[3] |= (0x1<<2);
		}
	}

	unlock_pid_file(fd);
	dlclose(lib_handle);
	// if ((r = init_ext_cmd_routine()) != 0) {
	// 	LOGG_DBG("Failed to init routine for ext cmd of %s", pid_name);
	// 	exit(r);
	// }

	// Send ack data back to server only if ack bit is set
	if (cmd[3] & 0x1) pack_and_send_ext_cmd_ack(cmd, value, r);
	exit(r);
}

static int pack_and_send_ext_cmd_ack(char cmd[5], uint32_t value, int ret) {
	// Check if the ack bit has been set.
	if (ret != 0 || !(cmd[3] & 0x01)) return ret;

	int ack_data_len = 13;
	uint8_t *p;
	uint8_t data[ack_data_len];
	p = data;

	PUT_INT(p, cmd[0], 8);
	PUT_INT(p, cmd[1], 8);
	PUT_INT(p, cmd[2], 8);
	PUT_INT(p, cmd[3], 8);
	PUT_INT(p, util_htonl(value), 32);

	return util_send_report_ex(DINP_MSG_DINC_EXT_CMD_ACK, DINP_HDR_MASK_UID, data, ack_data_len, cmd[1]);
}

// static int init_ext_cmd_routine() {
// 	dc_routine_definition def = {};

// 	def.dc_id = IPC_DC_DEV;
// 	def.dc_ip = DIN_DEVICE_IP;
// 	def.dc_port = DIN_IPC_PORT;

// 	// If it's ext cmd, this means that the routine does not need to
// 	// wait for DINC to send response data.
// 	def.dc_ext_cmd = 1;

// 	def.dc_init = NULL;
// 	def.dc_version = NULL;
// 	def.dc_load_config = NULL;

// 	return util_start_dc_routine(0, NULL, &def);
// }

/*
 *	For periodically sending dev info to server.
 */
int update_dev_info(int fd) {
	if (g_dev_info_last_update_time_init == 0) {
		time(&g_dev_info_last_update_time);
		g_dev_info_last_update_time_init = 1;
		return DIN_NO_ERR;
	}

	time_t cur_time;
	time(&cur_time);
	double diff = difftime(cur_time, g_dev_info_last_update_time);

	// Set min interval so that update is not too frequent.
	int update_interval = GET_CFG(dev_info_report_interval);
	if (update_interval < 60) update_interval = 60;

	if (g_dev_info.len > 0 && diff >= update_interval) {
		time(&g_dev_info_last_update_time);
		*(g_dev_info.data+1) = DINP_MSG_DINC_DEV_INFO_UPDATE;

		if (send_remote_msg(fd, g_dev_info.data, g_dev_info.len, &g_server_addr.addr, g_server_addr.len) != DIN_NO_ERR) {
			*(g_dev_info.data+1) = DINP_MSG_DC_DEVICE_INFO;
			return DIN_SEND_DATA_FAIL;
		}
		*(g_dev_info.data+1) = DINP_MSG_DC_DEVICE_INFO;
	}
	return DIN_NO_ERR;
}

static void bcast_cmd(int fd, uint32_t cmd_type, const void *data, int len) {
	int i;

	for (i = 0; i < MAX_DC_CNT; i++) 
	{
		if (g_dc_info_list[i].pid > 0) 
		{
			send_cmd(fd, cmd_type, IPC_DC_DEV + i, data, len);
		}
	}
}

static int send_cmd(int fd, uint32_t cmd_type, uint32_t dc_id, const void *data, int len) {
	struct dc_info *p_dc_info;
	struct din_local_msg msg;
	int ret;

	LOGG_FUNC_IN();

	do {
		if (len > MAX_CMD_CONTENT_LEN) 
		{
			ret = DIN_CONTENT_TOO_LARGE;
			break;
		}

		p_dc_info = get_dc_info(dc_id);

		if (p_dc_info == NULL) 
		{
			ret = DIN_DC_NOT_RECOG;
			break;
		}

		if (p_dc_info->pid <= 0) 
		{
			ret = DIN_DC_NOT_REG;
			break;
		}

		LOGG_INFO("Command Type: %08X", cmd_type);
		LOGG_INFO("DC ID: %08X", dc_id);

		msg.header.type = htonl(cmd_type);
		msg.header.dc_id = htonl(dc_id);

		if (data) {
			memcpy(msg.cmd.content, data, len);	
		}

		ret = send_data(fd, &msg, sizeof(msg.header) + len, (struct sockaddr *)&p_dc_info->addr, sizeof(struct sockaddr_in));
	} while (0);

	LOGG_FUNC_OUT();
	return ret;
}

static int send_remote_msg(int fd, const void *data, int data_len, const struct sockaddr *p_addr, socklen_t addr_len) 
{
	uint8_t msg[BUF_SIZE];
	int msg_len;

	if (p_addr == NULL) 
	{
		if (!g_server_addr.is_active) 
		{
			return DIN_SEND_REMOTE_MSG_FAIL;
		}

		p_addr = (struct sockaddr *)&g_server_addr.addr;
		addr_len = g_server_addr.len;
	}

	msg_len = pack_remote_msg(msg, data, data_len);
	return send_data(fd, msg, msg_len, p_addr, addr_len);
}

int send_data(int fd, const void *data, int data_len, const struct sockaddr *p_addr, socklen_t addr_len) 
{
	int sent_len;

	while (data_len > 0) 
	{
		sent_len = sendto(fd, data, data_len, 0, p_addr, addr_len);
		if (sent_len < 0) 
		{
			LOGG_ERRNO("sendto");
			return DIN_SEND_DATA_FAIL;
		}

		if (sent_len == 0) {
			break;
		}

		data += sent_len;
		data_len -= sent_len;
	}

	return DIN_NO_ERR;
}

enum {
	READ,
	WRITE
};

static int search_server_pipe(const int option)
{
	static int pipe_fd[2];

	switch(option)
	{
		case OPEN:
		{
			if (pipe_fd[READ] != -1 || pipe_fd[WRITE] != -1)
			{
				search_server_pipe(CLOSE_ALL);
			}

			if (pipe(pipe_fd) < 0)
			{
				LOGG_ERRNO("Initial pipe failed");
			}
			break;
		}
		case GET_READ:
		{
			return pipe_fd[READ];
		}
		case GET_WRITE:
		{
			return pipe_fd[WRITE];
		}
		case CLOSE_READ:
		{
			if (pipe_fd[READ] != -1)
			{
				close(pipe_fd[READ]);

				pipe_fd[READ] = -1;
			}
			break;
		}
		case CLOSE_WRITE:
		{
			if (pipe_fd[WRITE] != -1)
			{
				close(pipe_fd[WRITE]);

				pipe_fd[WRITE] = -1;
			}
			break;
		}
		case CLOSE_ALL:
		{
			search_server_pipe(CLOSE_READ);
			search_server_pipe(CLOSE_WRITE);
			break;
		}
		default:
		{
			return -1;
		}
	}
	
	return 0;
}

static int search_server(const int fd[], const char *domain_name) 
{
	switch (g_search_info.state) {
	case SUCCESS:
	case FAIL:
		if (fd == NULL || domain_name == NULL) 
		{
			return DIN_INVALID_PARAM;
		}

		set_search_info(INIT, fd, domain_name);
		break;

	case WAIT:
		if (fd == NULL && domain_name == NULL) 
		{
			set_search_info(IN_PROGRESS, NULL, NULL);
			int opt = CONTINUE;
			if (write(search_server_pipe(GET_WRITE), &opt, sizeof(opt)) < 0) 
			{
				LOGG_ERRNO("Write to pipe failed");
				return DIN_PIPE_OPT_FAIL;
			}
			// break;
		}
		/* no break */
	case INIT:
	case IN_PROGRESS:
		LOGG_WARN("Search not yet finished");
		return DIN_SEARCH_NOT_YET_FINISHED;

	default:
		return DIN_UNKNOWN_ERR;
	}

	// fork process to do handshake: using IPC message to communicate from child to parent
	// and using pipe to notify child process to do the next handshake try
	const pid_t pid = fork();
	if (pid < 0)
	{
		LOGG_ERRNO("Fork handshake process failed");
		return DIN_FORK_PROC_FAIL;
	}

	if (pid == 0)
	{
		// in child process close write pipe fd
		search_server_pipe(CLOSE_WRITE);
		search_server_impl();
		LOGG_INFO("Leave server handshake process");
		exit(0);
	}
	else
	{
		// in parent process close read pipe fd
		search_server_pipe(CLOSE_READ);
	}

	LOGG_INFO("Start searching server");
	return DIN_NO_ERR;
}

static void search_server_impl(void)
{
	enum {
		SRC_OPT_DOMAIN_NAME,
		SRC_CFG_DOMAIN_NAME,
		SRC_CFG_IP_ADDR,
		SRC_DFLT_DOMAIN_NAME,
		SRC_END
	};

	struct sockaddr_in6 addr_list[SERVER_ADDR_LIST_SIZE];
	int port_list[SERVER_PORT_LIST_SIZE];
	int addr_index;
	int port_index;
	int addr_cnt;
	int port_cnt;
	int src_index;
	
	in_port_t port;
	char domain_name[MAX_STR_LEN];
	char ip_addr[MAX_STR_LEN];
	char txt_rec[MAX_STR_LEN];
	struct sockaddr *p_addr;
	struct sockaddr_in *p_addr_v4;
	struct sockaddr_in6 *p_addr_v6;
	int cont;
	socklen_t addr_len;

	LOGG_FUNC_IN();

	if (g_search_info.state == INIT) 
	{
		send_event(IPC_MSG_START_SERVER_HANDSHAKE, NULL, 0);
		src_index = SRC_OPT_DOMAIN_NAME;

		addr_index = 0;
		port_index = 0;
		
		// if (strlen(g_search_info.domain_name) > 0) 
		// {
		// 	sprintf(domain_name, "%s.%s-%s", GET_CFG(server_prefix), g_search_info.domain_name, GET_CFG(server_suffix));

		// 	if (query_txt_rec(txt_rec, domain_name) == DIN_NO_ERR) 
		// 	{
		// 		// send to parent process to parse cfg values
		// 		send_event(IPC_MSG_SET_DNS_TXT_QUERY_RESULT, txt_rec, sizeof(txt_rec));

		// 		// since search_server_impl is a forked child process, therefore need to parse cfg text in this process again.
		// 		// for the server search procedure in the following.
		// 		load_cfg_str(txt_rec, " ");
		// 	}
		// }
		// REMOVED

		addr_cnt = 0;
		port_cnt = SERVER_PORT_LIST_SIZE;
		load_random_list(port_list, &port_cnt, GET_CFG(server_port), GET_CFG(server_port_range));
	}

	cont = 1;

	while (cont) 
	{
		if (g_conn_state == DISCONNECTED) 
		{
			break;
		}

		if (port_index < port_cnt) 
		{
			if (addr_index < addr_cnt) 
			{
				p_addr 	= (struct sockaddr *)&addr_list[addr_index];
				port 	= (in_port_t)port_list[port_index];
				
				LOGG_DBG("IP address family: %hu", p_addr->sa_family);

				if (p_addr->sa_family == AF_INET) 
				{
					p_addr_v4 = (struct sockaddr_in *)p_addr;
					p_addr_v4->sin_port = htons(port);
					addr_len = sizeof(struct sockaddr_in);
					inet_ntop(AF_INET, &p_addr_v4->sin_addr, ip_addr, sizeof(ip_addr));
				} 
				else 
				{
					p_addr_v6 = (struct sockaddr_in6 *)p_addr;
					p_addr_v6->sin6_port = htons(port);
					addr_len = sizeof(struct sockaddr_in6);
					inet_ntop(AF_INET6, &p_addr_v6->sin6_addr, ip_addr, sizeof(ip_addr));
				}

				int r = handshake(g_search_info.fd[REMOTE], p_addr, addr_len);
				
				// printf("Handshake with %s(#%d):%d(#%d); result = [%d]\n", ip_addr, addr_index + 1, port_list[port_index], port_index + 1, r);
				LOGG_INFO("Handshake with %s(#%d):%d(#%d); result = [%d]", ip_addr, addr_index + 1, port_list[port_index], port_index + 1, r);

				port_index++;

				if (r == DIN_NO_ERR) 
				{
					send_event(IPC_MSG_SEARCH_SERVER_WAIT, NULL, 0);
					
					// when handshake timout parent process will send a operation to indicate the next step
					int opt;
					int read_in = read(search_server_pipe(GET_READ), &opt, sizeof(opt));
					if (read_in <= 0)
					{
						LOGG_ERRNO("Read from pipe failed");
						break;
					}
					switch(opt)
					{
						case CONTINUE:
						{
							// continue to the next handshake procedure
							LOGG_DBG("Handshake process is going to continue");
						}
						break;
						case TERMINATE:
						{
							LOGG_DBG("Handshake process is going to terminate");
							cont = 0;
						}
						break;
						default:
						{
							LOGG_ERR("Search server process receive wrong operation: %d", opt);
							break;
						}
						break;
					}
				}
			} 
			else 
			{
				addr_cnt = 0;
				addr_index = 0;

				switch (src_index++) 
				{
					case SRC_OPT_DOMAIN_NAME:
					{
						LOGG_INFO("Search server using domain name from command-line argument: %s", g_search_info.domain_name);
						
						if (strlen(g_search_info.domain_name) > 0) 
						{
							sprintf(domain_name, "%s-%s", g_search_info.domain_name, GET_CFG(server_suffix));
							addr_cnt = SERVER_ADDR_LIST_SIZE;
							query_server_addr(addr_list, &addr_cnt, domain_name, GET_CFG(max_dns_query));
						}

						break;
					}
					case SRC_CFG_DOMAIN_NAME:
					{
						LOGG_INFO("Search server using domain name from configuration file: %s", GET_CFG(server_domain_name));

						if (strlen(GET_CFG(server_domain_name)) > 0) {
							sprintf(domain_name, "%s-%s", GET_CFG(server_domain_name), GET_CFG(server_suffix));
							addr_cnt = SERVER_ADDR_LIST_SIZE;
							query_server_addr(addr_list, &addr_cnt, domain_name, GET_CFG(max_dns_query));
						}

						break;
					}
					case SRC_CFG_IP_ADDR:
					{
						LOGG_INFO("Search server using IP address from configuration file: %s", GET_CFG(server_ip_addr));
						if (strlen(GET_CFG(server_ip_addr)) > 0) {
							p_addr_v4 = (struct sockaddr_in *)&addr_list[0];

							if (inet_pton(AF_INET, GET_CFG(server_ip_addr), &p_addr_v4->sin_addr) == 1) {
								p_addr_v4->sin_family = AF_INET;
								addr_cnt = 1;
							} else {
								p_addr_v6 = (struct sockaddr_in6 *)&addr_list[0];

								if (inet_pton(AF_INET6, GET_CFG(server_ip_addr), &p_addr_v6->sin6_addr) == 1) {
									p_addr_v6->sin6_family = AF_INET6;
									addr_cnt = 1;
								}
							}
						}

						break;
					}
					case SRC_DFLT_DOMAIN_NAME:
					{
						LOGG_INFO("Search server using default domain name");

						sprintf(domain_name, "default-%s", GET_CFG(server_suffix));
						addr_cnt = SERVER_ADDR_LIST_SIZE;
						query_server_addr(addr_list, &addr_cnt, domain_name, GET_CFG(max_dns_query));

						break;
					}
					case SRC_END:
					{
						send_event(IPC_MSG_SEARCH_SERVER_FAIL, NULL, 0);

						cont = 0;

						break;
					}
				}
			}
		} 
		else 
		{
			port_index = 0;
			addr_index++;
		}
	}

	LOGG_FUNC_OUT();
}

static int handshake(int fd, const struct sockaddr *p_addr, socklen_t addr_len) {
	int i;
	int ret;

	LOGG_FUNC_IN();
	ret = DIN_HANDSHAKE_FAIL;

	if (g_dev_info.len > 0) 
	{
		for (i = 1; i <= GET_CFG(max_handshake); i++) 
		{
			LOGG_INFO("Handshake with server, #%d", i);

			if (send_remote_msg(fd, g_dev_info.data, g_dev_info.len, p_addr, addr_len) == DIN_NO_ERR) 
			{
				ret = DIN_NO_ERR;
				break;
			}
		}
	}

	LOGG_FUNC_OUT();
	return ret;
}

static int send_conn_history_info(int fd) {
	uint8_t data[BUF_SIZE];
	int data_len;
	int ret;

	LOGG_FUNC_IN();

	if (!g_server_addr.is_active) {
		return DIN_SEND_CONN_HISTORY_INFO_FAIL;
	}

	ret = DIN_NO_ERR;

	if (!g_conn_history_info.is_sent && g_conn_history_info.list_size > 0) {
		data_len = pack_conn_history_info(data);
		ret = send_remote_msg(fd, data, data_len, &g_server_addr.addr, g_server_addr.len);

		if (ret == DIN_NO_ERR) {
			g_conn_history_info.is_sent = 1;
		}
	}

	LOGG_FUNC_OUT();
	return ret;
}

static int start_latency_test(int fd, uint32_t requester) {
	uint8_t data[BUF_SIZE];
	int data_len;

	if (!g_latency_test_info.is_testing) {
		set_latency_test_info(1, requester);

		if (!g_server_addr.is_active) {
			return DIN_LATENCY_TEST_FAIL;
		}

		data_len = pack_latency_test_info(data);

		// continuously sending latency test packet to server 3 times, in case packet lost during travel
		if (send_remote_msg(fd, data, data_len, &g_server_addr.addr, g_server_addr.len) != DIN_NO_ERR) {
			return DIN_LATENCY_TEST_FAIL;
		}
		if (send_remote_msg(fd, data, data_len, &g_server_addr.addr, g_server_addr.len) != DIN_NO_ERR) {
			return DIN_LATENCY_TEST_FAIL;
		}
		if (send_remote_msg(fd, data, data_len, &g_server_addr.addr, g_server_addr.len) != DIN_NO_ERR) {
			return DIN_LATENCY_TEST_FAIL;
		}

		set_select_timeout(GET_CFG(max_latency) * 1000);
	}

	return DIN_NO_ERR;
}

static void stop_latency_test(int fd, int is_success) {
	uint32_t latency;

	if (g_latency_test_info.is_testing) {
		set_latency_test_info(0, -1);

		if (is_success) {
			latency = (uint32_t)(g_latency_test_info.end_time_usec - g_latency_test_info.start_time_usec) / 1000;

			if (latency > GET_CFG(max_latency)) {
				latency = -1;
			}
			g_latency_test_info.fail_cnt = 0;
		} else {
			latency = -1;

			if (g_latency_test_info.fail_cnt < LAT_FAIL_MAX)
			{
				g_latency_test_info.fail_cnt++;
			}
		}
		send_cmd(fd, IPC_MSG_GET_LATENCY_ACK, g_latency_test_info.requester, &latency, sizeof(latency));
		set_select_timeout(-1);
	}
}

static void set_dev_info(const void *data, int len) {
	g_dev_info.len = len;
	memcpy(g_dev_info.data, data, len);
}

static void set_conn_state(enum conn_state state) {
	g_conn_state = state;
}

static void set_select_timeout(int64_t timeout_usec) {
	g_select_timeout_usec = timeout_usec;
}

static void set_search_info(enum search_state state, const int fd[], const char *domain_name) 
{
	LOGG_FUNC_IN();

	g_search_info.state = state;

	if (state == SUCCESS)
	{
		int opt = TERMINATE;
		if (write(search_server_pipe(GET_WRITE), &opt, sizeof(opt)) < 0) 
		{
			LOGG_ERRNO("Write to pipe failed");
		}
		search_server_pipe(CLOSE_WRITE);
	}
	
	if (state == FAIL)
	{
		search_server_pipe(CLOSE_ALL);
	}

	if (fd != NULL) 
	{
		memcpy(g_search_info.fd, fd, sizeof(g_search_info.fd));
	}

	if (domain_name != NULL) 
	{
		strcpy(g_search_info.domain_name, domain_name);
	}

	LOGG_FUNC_OUT();
}

static void set_server_addr(const struct sockaddr *p_addr, int addr_len) {
	if (p_addr != NULL) {
		g_server_addr.is_active = 1;
		g_server_addr.len = addr_len;
		memcpy(&g_server_addr.addr, p_addr, addr_len);
	} else {
		g_server_addr.is_active = 0;
	}
}

static void set_latency_test_info(int is_start, uint32_t requester) {
	if (is_start) {
		g_latency_test_info.is_testing = 1;
		g_latency_test_info.test_cnt++;
		g_latency_test_info.start_time_usec = get_time_now_usec();
		g_latency_test_info.requester = requester;
	} else {
		g_latency_test_info.is_testing = 0;
		g_latency_test_info.end_time_usec = get_time_now_usec();
	}
}

static void set_dc_info(int type, uint32_t id, const struct sockaddr_in *p_addr) {
	struct dc_info *p_info = get_dc_info(id);

	if (p_info != NULL) 
	{
		switch (type) 
		{
		case NET_SEARCH_START:
			p_info->net_search_start_time = get_time_now_usec();
			break;

		case NET_SEARCH_END:
			p_info->addr = *p_addr;
			memmove(&p_info->net_up_time_list[1], &p_info->net_up_time_list[0], (NET_UP_TIME_LIST_SIZE - 1) * sizeof(uint32_t));
			p_info->net_up_time_list[0] = htonl((uint32_t)time(NULL));

			if (p_info->net_search_start_time == 0) {
				p_info->net_search_latency = -1;
			} else {
				p_info->net_search_latency = htonl((uint32_t)(get_time_now_usec() - p_info->net_search_start_time) / 1000);
			}
			
			break;
		}
	}
}

static void set_conn_history_info(const void *data, int len) {
	struct conn_history *p_info;

	if (data != NULL) {
		g_conn_history_info.is_sent = 0;

		if (g_conn_history_info.list_size < MAX_CONN_HISTORY_LIST_SIZE) {
			g_conn_history_info.list_size++;
		}

		memmove(&g_conn_history_info.list[1], &g_conn_history_info.list[0], (MAX_CONN_HISTORY_LIST_SIZE - 1) * sizeof(struct conn_history));
		p_info = &g_conn_history_info.list[0];
		p_info->len = len;
		p_info->time = htonl((uint32_t)time(NULL));
		memcpy(p_info->data, data, len);
	}
}

static void reset_dc_activity(void) {
	int i;

	for (i = 0; i < MAX_DC_CNT; i++) 
	{
		g_dc_info_list[i].pid = 0;
		g_dc_info_list[i].net_search_start_time = 0;
	}
}

static struct dc_info *get_dc_info(uint32_t id) {
	uint32_t index;

	index = id - IPC_DC_DEV;

	if (index >= 0 && index < MAX_DC_CNT) 
	{
		return &g_dc_info_list[index];
	}
	return NULL;
}
