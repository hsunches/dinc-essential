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
#include <unistd.h>
#include <getopt.h>
#include <arpa/inet.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <signal.h>
#include "cfg.h"
#include "din.h"
#include "msg_hdlr.h"
#include "err_code.h"
#include "log.h"
#include "msg_format.h"
#include "util.h"
#include "version.h"

#define BUF_SIZE 128

static int fork_daemon(void);

uint32_t conv_dc_name_to_id(const char *name);
int conv_dc_id_to_name(int id, char *name);

int din_main(int argc, char *argv[]);
int send_data_wait_response(uint32_t type, char *ipstr, const void *data, int len, uint8_t* p_get);

/*
 * Description      : Get command line argumants from file /proc/PID/cmdline then pass to din_main. 
 *
 *
 * Return Code      : 0 - Job done.
 *					 -1 - Open cmdline file failed.
 *					 -2 - Read cmdline file failed.
 *
 * Data Valid Range : 
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int start_din()
{
	// let child process not to turn to zombie when finished
	signal(SIGCHLD, SIG_IGN);

	// try to get command line argumants from file /proc/PID/cmdline then pass to din_main
	char pid_file[BUF_SIZE];
	sprintf(pid_file, "/proc/%d/cmdline", getpid());

	int fd = open(pid_file, O_RDONLY);
	if (fd == -1) {
        LOGG_ERR("open cmdline file failed");
        return -1;
    }

    char buffer[BUF_SIZE];
    int read_in = read(fd, &buffer, BUF_SIZE);
    close(fd);

    if (read_in <= 0) {
		LOGG_ERR("read cmdline file failed");
        return -2;
    }

    char* argv[16];
    int argc = 0;
    int i = 0;
    while (i < read_in && argc < (sizeof(argv)/sizeof(char*)))
    {
    	argv[argc++] = &buffer[i];
    	i += (strlen(&buffer[i]) + 1);
    }

    return din_main(argc, argv);
}

int send_data_wait_response(uint32_t type, char *ipstr, const void *data, int len, uint8_t* p_get) {
	int ret = DIN_NO_ERR;
	int fd;
	fd_set readfds;

	struct sockaddr_in addr;
	struct timeval timeout;
	// timeout after 5 seconds
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;

	int select_cnt;
	socklen_t addr_len = sizeof(struct sockaddr_in);
	struct din_local_msg msg;

	LOGG_FUNC_IN();

	do {
		if (len > MAX_REPORT_DATA_LEN) 
		{
			LOGG_ERR("Content too large");
			ret = DIN_CONTENT_TOO_LARGE;

			break;
		}

		fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (fd < 0) 
		{
			LOGG_ERRNO("socket");
			ret = DIN_CREATE_SOCK_FAIL;

			break;
		}

		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = (ipstr == NULL) ? htonl(INADDR_LOOPBACK) : inet_addr(ipstr);
		addr.sin_port = htons(DIN_IPC_PORT);
		msg.header.type = htonl(type);

		if (data) 
		{
			memcpy(msg.event.content, data, len);
		}
		
		ret = send_data(fd, &msg, sizeof(msg.header) + len, (struct sockaddr *)&addr, sizeof(addr));
		if (ret != DIN_NO_ERR) 
		{
			LOGG_ERR("Fail to send data to IP: %s", ipstr);
			break;
		}

		// ready to read response
		FD_ZERO(&readfds);
		FD_SET(fd, &readfds);
		int maxfd = fd;
		while (1)
		{
			select_cnt = select(maxfd + 1, &readfds, NULL, NULL, &timeout);

			if (select_cnt < 0) 
			{
				perror("select");
				break;
			}

			uint8_t rbuf[BUF_SIZE];
			memset(rbuf, 0, sizeof(rbuf));

			if (select_cnt > 0)
			{
				int recv_len = recvfrom(fd, rbuf, BUF_SIZE, 0, (struct sockaddr *) &addr, &addr_len);

				if (recv_len == RECV_ERROR)
				{
					LOGG_ERRNO("recvfrom");
					break;
				}

				memcpy(p_get, rbuf, recv_len);
				break;
			}
			else
			{
				break; // timeout
			}
		}
		close(fd);
	} while (0);

	LOGG_FUNC_OUT();

	return ret;
}

/*
 * Description      : Parse command line to decide which operation will be taken. 
 *
 *                    Once the operation has decided, send event to message loop to trigger operation
 *
 * Return Code      : 0 - Job done.
 *					  1 - Not finished and will be called later.
 *					 -3 - Fail to fork as a fork_daemon.
 *					 -4 - The network type is not correct.
 *					 -5 - Fail to send a net-search event.
 *					 -6 - Fail to send a network-down event.
 *					 -7 - Fail to send a network-up event.
 *					 -8 - Fail to send a start dc event.
 *					 -9 - Fail to send a stop dc event.
 *					 -10 - The network type is not correct.
 *					 -11 - Fail to send a custom event.
 *					 -12 - Fail to send a request device uid event.
 *					 -13 - Fail to send a request full domain name event.
 *					 -14 - Fail to send a set device uid event.
 *					 -15 - Fail to send a report-server-latency-fail-cnt event.
 *
 * Data Valid Range : 
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int din_main(int argc, char *argv[]) 
{
	enum {
		OPT_NORMAL = 1,
		OPT_DAEMON,
		OPT_NET_SEARCH,
		OPT_NET_UP,
		OPT_NET_DOWN,
		OPT_DOMAIN_NAME,
		OPT_CFG_PATH,
		OPT_EVENT,
		OPT_RECEIVER,
		OPT_VERSION,
		OPT_START_DC,
		OPT_STOP_DC,
		OPT_REQUEST_UID,
		OPT_SPECIFY_UID,
		OPT_REQUEST_DOMAIN,
		OPT_LATENCY_FAIL_CNT,
		OPT_REPORT_WHO
	};

	struct option opt_tbl[] = {
		{"normal",		0,	NULL,	OPT_NORMAL		},
		{"daemon",		0,	NULL,	OPT_DAEMON		},
		{"net_search",	1,	NULL,	OPT_NET_SEARCH	},
		{"net_up",		0,	NULL,	OPT_NET_UP		},
		{"net_down",	0,	NULL,	OPT_NET_DOWN	},
		{"domain_name",	1,	NULL,	OPT_DOMAIN_NAME	},
		{"cfg_path",	1,	NULL,	OPT_CFG_PATH	},
		{"event",		1,	NULL,	OPT_EVENT		},
		{"receiver",	1,	NULL,	OPT_RECEIVER	},
		{"version",		0,	NULL,	OPT_VERSION		},
		{"start_dc",	1,	NULL,	OPT_START_DC	},
		{"stop_dc",		1,	NULL,	OPT_STOP_DC		},
		{"request_dev_uid",		1,	NULL,	OPT_REQUEST_UID		},
		{"specify_dev_uid",		1,	NULL,	OPT_SPECIFY_UID		},
		{"request_full_domain",	1,	NULL,	OPT_REQUEST_DOMAIN	},
		{"latency_fail_cnt",	1,	NULL,	OPT_LATENCY_FAIL_CNT	},
		{"who",	0,	NULL,	OPT_REPORT_WHO	},
		{NULL,			0,	NULL,	0				}
	};

	// reset memebers
	int opt;
	optind = 1; // important for getopt_long_only()
	int opt_index = 0;
	int extra_opt;
	char buf[256];
	char *cfg_path;

	// union din_private_event event;
	struct din_private_event event;
	int ret;

	OPEN_LOGG("DIN");
	LOGG_FUNC_IN();
	ret = 0;
	extra_opt = -1;
	cfg_path = NULL;
	memset(&event, 0, sizeof(event));

	memset(&g_dev_info_report, 0, sizeof(g_dev_info_report));

	while (1) 
	{
		opt = getopt_long_only(argc, argv, "", opt_tbl, &opt_index);

		if (opt == -1) 
		{
			break;
		}

		switch (opt) 
		{
		case OPT_NORMAL:
			LOGG_INFO("Specify normal mode");
			extra_opt = opt;
			break;

		case OPT_DAEMON:
			LOGG_INFO("Specify daemon mode");
			if (fork_daemon() != DIN_NO_ERR) 
			{
				LOGG_ERR("Fail to fork as a fork_daemon");
				return -1;
			}

			LOGG_INFO("Fork as a daemon successfully");
			extra_opt = opt;
			break;

		case OPT_NET_SEARCH:
			LOGG_INFO("Specify net-search event: %s", optarg);
			event.value[0] = conv_dc_name_to_id(optarg);

			if (event.value[0] == IPC_DC_MAX) 
			{
				LOGG_ERR("The network type is not correct: %s", optarg);
				ret = -2;
				break;
			}

			event.value[0] = htonl(event.value[0]);

			if (send_event(IPC_MSG_NETWORK_SEARCH, &event, sizeof(event.value[0])) != DIN_NO_ERR) 
			{
				LOGG_ERR("Fail to send a net-search event");
				ret = -3;
				break;
			}

			LOGG_INFO("Send a net-search event successfully");
			break;

		case OPT_NET_UP:
			LOGG_INFO("Specify network-up event");
			extra_opt = opt;
			break;

		case OPT_REQUEST_UID:
			LOGG_INFO("Specify request-dev-uid event to IP %s", optarg);

			uint8_t uid8[8];
			memset(uid8, 0, sizeof(uid8));
			
			if (send_data_wait_response(IPC_MSG_REPORT_UID, optarg, NULL, 0, uid8) != DIN_NO_ERR)
			{
				LOGG_ERR("Fail to send a request_dev_uid event to IP %s", optarg);
				ret = -10;
			}

			int i = 0;
			for (i = 0; i < sizeof(uid8); i++)
			{
				printf("%02x", uid8[i]);
			}
			break;

		case OPT_REQUEST_DOMAIN:
			LOGG_INFO("Specify request-domain-name event to IP %s", optarg);

			char domain_name[MAX_SERVER_DOMAIN_NAME_LEN];
			memset(domain_name, 0, sizeof(domain_name));

			if (send_data_wait_response(IPC_MSG_REPORT_FULL_DOMAIN, optarg, NULL, 0, (uint8_t*) domain_name) != DIN_NO_ERR)
			{
				LOGG_ERR("Fail to send a report_full_domain event to IP %s", optarg);
				ret = -11;
			}
			printf("%s\n", domain_name);
			break;

		case OPT_LATENCY_FAIL_CNT:
			LOGG_INFO("Specify server-latency-fail-cnt event to IP %s", optarg);

			union t_convert
			{
				uint32_t fail_cnt32;
				uint8_t  fail_cnt8[4];
			} convert;
			memset(convert.fail_cnt8, 0, sizeof(convert.fail_cnt8));

			if (send_data_wait_response(IPC_MSG_REPORT_LATENCY_FAIL_CNT, optarg, NULL, 0, convert.fail_cnt8) != DIN_NO_ERR)
			{
				LOGG_ERR("Fail to send a report-server-latency-fail-cnt event to IP %s", optarg);
				ret = -13;
			}
			printf("%u\n", convert.fail_cnt32);

			break;

		case OPT_NET_DOWN:
			LOGG_INFO("Specify network-down event");

			if (send_event(IPC_MSG_NETWORK_DOWN, NULL, 0) != DIN_NO_ERR) 
			{
				LOGG_ERR("Fail to send a network-down event");
				ret = -4;
				break;
			}

			LOGG_INFO("Send a network-down event successfully");
			break;

		case OPT_DOMAIN_NAME:
			LOGG_INFO("Specify domain name: %s", optarg);
			
			if (strlen(optarg) < MAX_EVENT_CONTENT_LEN) 
			{
				strcpy((char *)event.content, optarg);
			} 
			else {
				LOGG_WARN("Domain name legnth is too long");
				event.content[0] = 0;
			}

			break;

		case OPT_SPECIFY_UID:
			LOGG_INFO("Specify device UID: %s", optarg);
			strcpy((char *)event.content, optarg);
			extra_opt = opt;
			break;

		case OPT_CFG_PATH:
			LOGG_INFO("Specify configuration file path: %s", optarg);

			if (strlen(optarg) < sizeof(buf)) 
			{
				strcpy(buf, optarg);
				cfg_path = buf;
			} 
			else {
				LOGG_WARN("The length of configuration file path is too long");
			}

			break;

		case OPT_EVENT:
			LOGG_INFO("Specify custom event: %s", optarg);
			strncpy((char *)&event.value[1], optarg, 4);
			extra_opt = opt;
			break;

		case OPT_RECEIVER:
			LOGG_INFO("Specify custom-event receiver: %s", optarg);
			event.value[0] = conv_dc_name_to_id(optarg);
			break;

		case OPT_VERSION:
			print_version();
			return 0;

		case OPT_START_DC:
			LOGG_INFO("Start data collector: %s", optarg);
			strcpy((char *)event.content, optarg);
			extra_opt = opt;
			break;

		case OPT_STOP_DC:
			LOGG_INFO("Stop data collector: %s", optarg);
			strcpy((char *)event.content, optarg);
			extra_opt = opt;
			break;

		case OPT_REPORT_WHO:
			LOGG_INFO("Who is on duty?");
			if (send_event(IPC_MSG_DC_WHO, NULL, 0) != DIN_NO_ERR) 
			{
				LOGG_ERR("Fail to send a dc-who event");
				ret = -4;
				break;
			}

			LOGG_INFO("Send a dc-who event successfully");
			break;
		}
	}

	switch (extra_opt) 
	{
		case OPT_NORMAL:
		case OPT_DAEMON:
			if (load_cfg_file(cfg_path) != DIN_NO_ERR) {
				LOGG_WARN("Fail to load configuration file");
			}
			
			start_msg_hdlr();
			break;

		case OPT_NET_UP:
			if (send_event(IPC_MSG_NETWORK_UP, &event, sizeof(event.content)) != DIN_NO_ERR) 
			{
				LOGG_ERR("Fail to send a network-up event");
				ret = -5;
				break;
			}

			LOGG_INFO("Send a network-up event successfully");
			break;

		case OPT_START_DC:
			if (send_event(IPC_MSG_DC_START, &event, sizeof(event.content)) != DIN_NO_ERR) 
			{
				LOGG_ERR("Fail to send a start dc event");
				ret = -6;
			}
			break;

		case OPT_STOP_DC:
			if (send_event(IPC_MSG_DC_STOP, &event, sizeof(event.content)) != DIN_NO_ERR) 
			{
				LOGG_ERR("Fail to send a stop dc event");
				ret = -7;
			}
			break;

		case OPT_EVENT:
			if (event.value[0] == IPC_DC_MAX) 
			{
				LOGG_ERR("The network type is not correct: %s", optarg);
				ret = -8;
				break;
			}
			event.value[0] = htonl(event.value[0]);

			if (send_event(IPC_MSG_CUSTOM_EVENT, &event, sizeof(event.value)) != DIN_NO_ERR) 
			{
				LOGG_ERR("Fail to send a custom event");
				ret = -9;
				break;
			}
			LOGG_INFO("Send a custom event successfully");
			break;

		case OPT_SPECIFY_UID:
			if (send_event(IPC_MSG_SPECIFY_UID, &event, sizeof(event.content)) != DIN_NO_ERR) 
			{
				LOGG_ERR("Fail to send a set uid event");
				ret = -12;
			}
			break;
	}
	LOGG_FUNC_OUT();

	return ret;
}

uint32_t get_dc_id(const char *name)
{
	uint32_t id = IPC_DC_MAX;

	void* handle = dlopen(NULL, RTLD_NOW);
	if (!handle) 
	{
		LOGG_ERR("%s", dlerror());
		return id;
	}

	char func[32];
	sprintf(func, "dc_%s_id", name);

	dlerror();
	uint32_t (*dc_id)(void) = dlsym(handle, func);
	char *error = dlerror();

	if (error != NULL) 
	{
		LOGG_ERR("%s", error);
		dlclose(handle);
		return id;
	}
	id = dc_id();

	dlclose(handle);

	return id;	
}

struct {
	char *name;
	uint32_t id;
} static const conv_tbl[] = {
	{"dev",			IPC_DC_DEV		},
	{"wifi_sta",	IPC_DC_WIFI_STA	},
	{"wifi_ap",		IPC_DC_WIFI_AP	},
	{"wmx", 		IPC_DC_WIMAX	},
	{"2g", 			IPC_DC_2G		},
	{"3g", 			IPC_DC_3G		},
	{"lte", 		IPC_DC_LTE		},
	{"voip", 		IPC_DC_VOIP		},
	{"ethernet", 	IPC_DC_ETHERNET	}
};

uint32_t conv_dc_name_to_id(const char *name)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(conv_tbl); i++) 
	{
		if (!strcmp(name, conv_tbl[i].name)) {
			return conv_tbl[i].id;
		}
	}

	const uint32_t id = get_dc_id(name);
	if (id == IPC_DC_DEV) {
		return IPC_DC_MAX;
	}
	return id;
}

int conv_dc_id_to_name(int id, char *name)
{
	int i;
	sprintf(name, "dev");

	for (i = 0; i < ARRAY_SIZE(conv_tbl); i++)
	{
		if ((id | 0x80BB0000) == conv_tbl[i].id) {
			strcpy(name, conv_tbl[i].name);
			return 0;
		}
	}
	return 1;
}

static int fork_daemon(void) {
	int ret;
	// pid_t pid, sid;

	LOGG_FUNC_IN();
	ret = DIN_NO_ERR;

	if (daemon(0, 0) < 0) 
	{
		LOGG_ERRNO("daemon");
		ret = DIN_CREATE_DAEMON_FAIL;
	}
	/*
	do {
		if (getppid() == 1) {
			LOGG_WARN("Daemon already exists!");
			ret = DIN_DAEMON_ALREADY_EXISTS;
			break;
		}

	    pid = fork();

	    if (pid < 0) {
	    	LOGG_ERRNO("fork");
	    	ret = DIN_FORK_PROC_FAIL;
	    	break;
	    }

	    if (pid > 0) {
	    	exit(0);
	    }

	    umask(0);
	    sid = setsid();

	    if (sid < 0) {
	    	LOGG_ERRNO("setsid");
	        ret = DIN_CREATE_SESSION_FAIL;
	        break;
	    }

	    if ((chdir("/")) < 0) {
	    	LOGG_ERRNO("chdir");
	        ret = DIN_CHANGE_DIR_FAIL;
	        break;
	    }

	    freopen("/dev/null", "r", stdin);
	    freopen("/dev/null", "w", stdout);
	    freopen("/dev/null", "w", stderr);
	} while (0);
	*/
	LOGG_FUNC_OUT();
    return ret;
}
