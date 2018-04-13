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

#include <stdint.h>
#include "msg_util.h"
#include "misc.h"
#include "util.h"
#include "log.h"
#include "md5.h"
#include "cfg.h"
#include "err_code.h"
#include "msg_format.h"

#define BUF_SIZE	512

struct dev_info g_dev_info;
struct conn_history_info g_conn_history_info;
struct latency_test_info g_latency_test_info;

static int scrmb_data(uint8_t *dst_buf, uint8_t *src_buf, int src_len);
static uint8_t *descrmb_data(uint8_t *buf, int *p_len);

static int scrmb_data(uint8_t *dst_buf, uint8_t *src_buf, int src_len) {
	int i;
	uint8_t rand_buf[8];
	int rand_len;
	int xor_index;
	int dst_len;

	randomize();
	rand_len = get_random() % 8 + 1;

	for (i = 0; i < rand_len; i++) {
		rand_buf[i] = (uint8_t)(get_random() % 256);
	}

	xor_index = get_random() % rand_len;
	LOGG_DBG("Random array length: %d, XOR byte index: %d, XOR byte: %d", rand_len, xor_index, rand_buf[xor_index]);
	dst_buf[0] = (uint8_t)((rand_len << 4) | xor_index);
	util_memcpy(&dst_buf[1], rand_buf, rand_len);
	util_memcpy(&dst_buf[1 + rand_len], src_buf, src_len);
	dst_len = 1 + rand_len + src_len;

	for (i = 1 + rand_len; i < dst_len; i++) {
		dst_buf[i] ^= rand_buf[xor_index];
	}

	return dst_len;
}

static uint8_t *descrmb_data(uint8_t *buf, int *p_len) {
	int rand_len = 0;
	int xor_index = 0;
	uint8_t operand = 0;

	int i = 0;
	int offset = 0;

	if (buf == NULL || p_len == NULL) {
		return NULL;
	}

	rand_len = buf[0] >> 4;
	xor_index = buf[0] & 0xf;
	operand = buf[1 + xor_index];
	offset = 1 + rand_len;

	for (i = offset; i < *p_len; i++) {
		buf[i - offset] = buf[i] ^ operand;
	}
	*p_len -= 1 + rand_len;
	return &buf[0];
}

int parse_remote_msg(struct remote_msg **pp_msg, void *data, int len, int32_t now) {
	struct remote_msg *p_msg;
	const char *private_key;
	md5_state_t state;
	md5_byte_t digest[16];

	p_msg = (struct remote_msg *)descrmb_data((uint8_t *)data, &len);

	if (len != sizeof(struct remote_msg)) {
		LOGG_ERR("Remote message length is %d, should be %u", len, (uint32_t)sizeof(struct remote_msg));
		return DIN_RECV_LEN_MISMATCHED;
	}

	p_msg->timestamp ^= p_msg->chksum;
	p_msg->cmd ^= p_msg->chksum;
	p_msg->value ^= p_msg->chksum;
	private_key = "NEIL";
	md5_init(&state);
	md5_append(&state, (const md5_byte_t *)private_key, 4);
	md5_append(&state, (const md5_byte_t *)p_msg, 12);
	md5_finish(&state, digest);
	LOGG_DBG("Timestamp : 0x%08X", util_ntohl(p_msg->timestamp));
	LOGG_DBG("Command   : 0x%08X", util_ntohl(p_msg->cmd));
	LOGG_DBG("Value     : 0x%08X", util_ntohl(p_msg->value));
	LOGG_DBG("Checksum  : 0x%08X", util_ntohl(p_msg->chksum));
	LOGG_DBG("Digest    : 0x%02X%02X%02X%02X", digest[0], digest[1], digest[2], digest[3]);

	if (util_memcmp(digest, &p_msg->chksum, 4)) {
		LOGG_ERR("Remote message checksum error");
		return DIN_REMOTE_MSG_CHKSUM_ERR;
	}

	if (now - (int32_t)util_ntohl(p_msg->timestamp) > (int32_t)GET_CFG(remote_msg_timeout)) {
		LOGG_WARN("Remote message timeout");
		return DIN_REMOTE_MSG_TIMEOUT;
	}

	p_msg->value = util_ntohl(p_msg->value);
	*pp_msg = p_msg;
	return DIN_NO_ERR;
}

int pack_remote_msg(void *msg, const void *data, int len) {
	const char *private_key;
	uint8_t data_ext[BUF_SIZE];
	int i;
	md5_state_t state;
	md5_byte_t digest[16];

	private_key = "RNCE";
	util_memcpy(data_ext, private_key, 4);
	randomize();

	for (i = 4; i < 8; i++) {
		data_ext[i] = (uint8_t)(get_random() % 256);
	}

	util_memcpy(data_ext + 8, data, len);
	md5_init(&state);
	md5_append(&state, (const md5_byte_t *)data_ext, 8 + len);
	md5_finish(&state, digest);
	util_memcpy(data_ext, digest, 4);
	return scrmb_data((uint8_t *)msg, data_ext, 8 + len);
}

int pack_conn_history_info(uint8_t *data) {
	uint8_t *p;
	int i;

	p = data;
	PUT_INT(p, DINP_ROLE_DIN_CLIENT | DINP_HDR_MASK_UID, 8);
	PUT_INT(p, DINP_MSG_DINC_CONN_HISTORY_INFO, 8);
	PUT_MEM(p, g_dev_info.data + 2, 8);
	PUT_INT(p, g_conn_history_info.list_size, 8);

	for (i = 0; i < g_conn_history_info.list_size; i++) {
		PUT_INT(p, g_conn_history_info.list[i].time, 32);
		PUT_MEM(p, g_conn_history_info.list[i].data, g_conn_history_info.list[i].len);
	}

	return p - data;
}

int pack_latency_test_info(uint8_t *data) {
	uint8_t *p;

	p = data;
	PUT_INT(p, DINP_ROLE_DIN_CLIENT, 8);
	PUT_INT(p, DINP_MSG_DINC_LATENCY, 8);
	PUT_INT(p, g_latency_test_info.test_cnt, 8);

	// increasing packet size to 32 bytes in order to prevent packet being dropped due to too small
	uint8_t empty_data = 0;
	int i = 0;
	for (i = 0; i < 29; i++) {
		PUT_INT(p, empty_data, 8);
	}

	return p - data;
}
