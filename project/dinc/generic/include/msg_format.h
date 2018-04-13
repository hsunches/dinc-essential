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

#ifndef MSG_FORMAT_H
#define MSG_FORMAT_H

#include <stdint.h>
#include "util.h"
#include "msg_format.h"

/*
 *	DIN 8 Bytes IPC Packet Header (DIN Client & Data Collector)
 *
 *	[0]~[3] is IPC Message Type
 *	[4]~[7] is IPC DC Type
 *
 */

// IPC Message Type
typedef enum _ipc_msg_type
{
	IPC_MSG_NETWORK_SEARCH = 0x80AA0001,
	IPC_MSG_NETWORK_UP,
	IPC_MSG_NETWORK_DOWN,
	IPC_MSG_DC_REGISTER,
	IPC_MSG_DC_REGISTER_ACK,
	IPC_MSG_DC_SHUT_DOWN,
	IPC_MSG_DC_START,
	IPC_MSG_DC_STOP,
	IPC_MSG_DC_STATUS,
	IPC_MSG_DC_STATUS_ACK,
	IPC_MSG_SEARCH_SERVER_WAIT,
	IPC_MSG_SEARCH_SERVER_FAIL,
	IPC_MSG_SERVER_LOOKUP_RESULT,
	IPC_MSG_GET_LATENCY,
	IPC_MSG_GET_LATENCY_ACK,
	IPC_MSG_REPORT_UID,
	IPC_MSG_SPECIFY_UID,
	IPC_MSG_REPORT_FULL_DOMAIN,
	IPC_MSG_REPORT_LATENCY_FAIL_CNT,
	IPC_MSG_SEND_CONN_HISTORY_INFO,
	IPC_MSG_SEND_REPORT,
	IPC_MSG_SET_DEVICE_INFO,
	// IPC_MSG_SET_DNS_TXT_QUERY_RESULT,// REMOVED
	IPC_MSG_START_SERVER_HANDSHAKE,
	IPC_MSG_DC_WHO,

	IPC_MSG_CUSTOM_EVENT = 0x80AA0001 + 1024,
	IPC_MSG_MAX = 0x80AA0001 + MAX_MSG_CNT
	// 0X80AAFFFF
} ipc_msg_type;

// IPC DC Type
typedef enum _ipc_dc_type
{
	IPC_DC_DEV = 0x80BB0001,
	IPC_DC_WIFI_STA,
	IPC_DC_WIFI_AP,
	IPC_DC_WIMAX,
	IPC_DC_2G,
	IPC_DC_3G,
	IPC_DC_LTE,
	IPC_DC_VOIP,
	IPC_DC_ETHERNET,
	IPC_DC_CUSTOM_BASE = 0x80BB0001 + 16,
	IPC_DC_MAX = 0x80BB0001 + MAX_DC_CNT 
	// 0X80BB0019
} ipc_dc_type;

/*
 *	data structure in DIN
 *
 */

struct event_header {
	uint32_t type;
};

struct din_private_event {
	union	{
		uint8_t content[MAX_EVENT_CONTENT_LEN];
		uint32_t value[2];
	};
};

struct din_command {
	union {
		uint8_t content[MAX_CMD_CONTENT_LEN];
		uint32_t value[6];
	};
};

#pragma pack(1)

struct dev_info_report {
	uint64_t uid;
} g_dev_info_report;

struct dc_data {
	uint32_t value[6];
	uint8_t extra[MAX_STR_LEN];
};

struct data_header {
	uint32_t type;
	uint32_t dc_id;
};

struct dc_report_header {
	struct data_header header;

	uint8_t role;
	uint8_t msg_type;
};

struct dc_register_ack {
	uint32_t net_up_time_list[5];
	uint32_t net_search_latency;
};

struct din_local_msg {
	struct data_header header;

	union {
		struct din_private_event event;
		struct din_command cmd;
	};
};

#pragma pack()

// DIN Packet Role
#define DINP_ROLE_DIN_CLIENT		0x00

#define DINP_ROLE_DEV				(IPC_DC_DEV			& 0x3F)
#define DINP_ROLE_WIFI_STA			(IPC_DC_WIFI_STA  	& 0x3F)
#define DINP_ROLE_WIFI_AP			(IPC_DC_WIFI_AP  	& 0x3F)
#define DINP_ROLE_WIMAX				(IPC_DC_WIMAX  		& 0x3F)
#define DINP_ROLE_2G				(IPC_DC_2G  		& 0x3F)
#define DINP_ROLE_3G				(IPC_DC_3G  		& 0x3F)
#define DINP_ROLE_LTE				(IPC_DC_LTE  		& 0x3F)
#define DINP_ROLE_VOIP				(IPC_DC_VOIP  		& 0x3F)
#define DINP_ROLE_ETHERNET			(IPC_DC_ETHERNET  	& 0x3F)

// DIN Packet Message INT{0 ~ 128} = HEX{0 ~ 80}
#define DINP_MSG_DC_DEVICE_INFO			0x01
#define DINP_MSG_DC_CONN_HISTORY_INFO	0x02
#define DINP_MSG_DC_NETWORK_ENTRY_INFO	0x03
#define DINP_MSG_DC_ALERT_INFO			0x04
#define DINP_MSG_DC_HANDOVER_INFO		0x05
#define DINP_MSG_DC_IP_CHANGING_INFO	0x06
#define DINP_MSG_DC_PERFORMANCE_INFO	0x07
#define DINP_MSG_DC_CALL_INFO			0x08
#define DINP_MSG_DC_TERMINATION_INFO	0x09

// DIN Packet Message INT{192 ~ 255} = HEX {C0 ~ FF}
#define DINP_MSG_DINC_LATENCY			0xC1
#define DINP_MSG_DINC_CONN_HISTORY_INFO	0xC2
#define DINP_MSG_DINC_EXT_CMD_ACK		0xC3
#define DINP_MSG_DINC_DEV_INFO_UPDATE	0xC4

// DIN Client Info
#define DIN_DEVICE_IP	"127.0.0.1"
#define DIN_IPC_PORT	56000
#define DIN_DATA_PORT	8080

// DIN HAL Info
#define DIN_HTTP_HOST	"127.0.0.1:8080"

// DIN Alert Type
#define DIN_ALERT_PROCESSOR_USAGE	0x01
#define DIN_ALERT_MEMORY_USAGE		0x02
#define DIN_ALERT_DEVICE_TEMP		0x03
#define DIN_ALERT_BATTERY_TEMP		0x04

#endif /* MSG_FORMAT_H */
