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

#ifndef MSG_UTIL
#define MSG_UTIL

#define MAX_DEV_INFO_LEN			256
#define MAX_CONN_HISTORY_DATA_LEN	16
#define MAX_CONN_HISTORY_LIST_SIZE	5

struct remote_msg {
	uint32_t timestamp;
	uint32_t cmd;
	uint32_t value;
	uint32_t chksum;
};

extern struct dev_info {
	int len;
	uint8_t data[MAX_DEV_INFO_LEN];
} g_dev_info;

extern struct conn_history_info {
	int is_sent;
	int list_size;

	struct conn_history {
		int len;
		uint32_t time;
		uint8_t data[MAX_CONN_HISTORY_DATA_LEN];
	} list[MAX_CONN_HISTORY_LIST_SIZE];
} g_conn_history_info;

extern struct latency_test_info {
	int is_testing;
	int test_cnt;
	int64_t start_time_usec;
	int64_t end_time_usec;
	uint32_t requester;
	uint32_t fail_cnt;
} g_latency_test_info;

int parse_remote_msg(struct remote_msg **pp_msg, void *data, int len, int32_t now);
int pack_remote_msg(void *msg, const void *data, int len);

int pack_conn_history_info(uint8_t *data);
int pack_latency_test_info(uint8_t *data);

#endif
