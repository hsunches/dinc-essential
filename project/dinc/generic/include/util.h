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

#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stddef.h>
#include "dc_definition.h"

#define MIN_REPORT_INTERVAL	30
#define MAX_REPORT_INTERVAL	240 // 4 min
#define MAX_LV_CNT			8

#define WIN_SIZE			10
#define ALERT_TH			5

#define PERCENT_TH1			80
#define	PERCENT_TH2			85
#define PERCENT_TH3			90
#define PERCENT_TH4			95

#define TEMP_TH1			45
#define TEMP_TH2			50
#define TEMP_TH3			55
#define TEMP_TH4			60
 
#define MAX_EVENT_CONTENT_LEN	128
#define MAX_CMD_CONTENT_LEN		512
#define MAX_REPORT_DATA_LEN		128
#define MAX_DC_CNT				24
#define MAX_MSG_CNT				65534
#define MAX_STR_LEN				128

#define PUT_INT(dst, val, len)		{int##len##_t src = val; util_memcpy((void*)dst, (void*)(&src), len/8); dst += (len) / 8;}
#define PUT_MEM(dst, src, len)		{util_memcpy(dst, src, len); dst += len;}
#define PUT_STR(dst, src)			{int _len = util_strlen(src); PUT_INT(dst, _len ? _len : -1, 8); PUT_MEM(dst, src, _len);}

#define FIELD_SIZE(type, field)		sizeof(((type *)NULL)->field)
#define ARRAY_SIZE(a)				(sizeof(a) / sizeof(a[0]))

#define util_ntohs	util_htons
#define util_ntohl	util_htonl
#define util_ntohll	util_htonll

#define INVALID_SOCKET		-1
#define SOCKET_ERROR INVALID_SOCKET
#define RECV_ERROR INVALID_SOCKET

extern struct stat_tbl {
	int is_alert_needed;
	int lv[2];
	int th[4];
	int over_th_cnt[4];
	int win[WIN_SIZE + 1];
	int win_usage;
	int max;
	int min;
	int mean;
} g_stat_tbl[4];

uint16_t util_htons(uint16_t val);
uint32_t util_htonl(uint32_t val);
uint64_t util_htonll(uint64_t val);

int64_t util_get_time_usec(void);

void util_set_conn_time(const uint32_t conn_time[]);
void util_set_round_trip_latency(const uint32_t latency);

int util_write_data_to_ipc_channel(const void *data, int len);
int util_start_ipc_routine(dc_routine_definition* def);
int util_create_ipc_channel(char *ipstr, int port);
int util_parse_options(int argc, char *argv[], dc_routine_definition* def);
int util_start_dc_routine(int argc, char* argv[], dc_routine_definition* def);
int util_send_round_trip_latency_request(void);
int util_send_report(const int msg_type, const int extra_role, const uint8_t* data, const int len);
int util_send_report_ex(const int msg_type, const int extra_role, const uint8_t* data, const int len, const int dc_id);
int util_send_connection_history_information(const uint8_t* data, const int len);

void *util_memcpy(void *dst, const void *src, size_t n);
int util_memcmp(const void *s1, const void *s2, size_t n);
size_t util_strlen(const char *s);

double util_simple_sqrt(double val, double errors);
double util_unsafe_sqrt(double val, int digits);

#endif
