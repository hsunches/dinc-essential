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
#include <string.h>
#include "data_wmx.h"
#include "msg_hal.h"

/*
 * Description		: Get WiMAX frequency band supported by device,
 * 					: please use the constants to make the bitmap defined in data_wmx.h.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: A bitmap
 *					: Bit[0:3]  - representing frequency band 1 to 4
 *					: Bit[4:31] - reserved
 * Reference		:
 * Remarks			:
 */
int wmx_get_supported_freq_band(int *value)
{
#ifdef SAMPLE_CODE
	*value |= WIMAX_FREQ_BAND_2_3;
	*value |= WIMAX_FREQ_BAND_2_5;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get Physical IP Address, please make sure the return data is Text format.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: Text Format, only accept [0-9,a-f,A-F],[.],[:]
 * Reference		:
 * Remarks			: Accept only numeric format for IPv4.
 */
int wmx_get_ip_address(char buff[40])
{
#ifdef SAMPLE_CODE
	// IPv4
	char ipv4str[16] = "123.66.210.133";
	memcpy(buff, ipv4str, strlen(ipv4str));
	// IPv6
	char ipv6str[40] = "2002:0:0:0:0:0:7b42:d285";
	memcpy(buff, ipv6str, strlen(ipv6str));

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get latency in ms when MS enter the WiMAX network.
 *					: If the API doesn't support, get the time elapsed between
 *					: MS connection request and bearer response returned.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int wmx_get_network_entry_latency(int *value)
{
#ifdef SAMPLE_CODE
	int latency = 500;
	*value = latency;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get BS_ID of BS when MS is camping on.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: MAC Address Format
 * Reference		:
 * Remarks			:
 */
int wmx_get_bs_id(uint8_t buff[6])
{
#ifdef SAMPLE_CODE
	uint8_t bs_id[6] = { 0x1F, 0xCA, 0x2E, 0x10, 0x20, 0x30 };
	memcpy(buff, bs_id, sizeof(bs_id));

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get the reading of RSSI in dBm.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: -123 ~ -40
 * Reference		:
 * Remarks			:
 */
int wmx_get_rssi(int *value)
{
#ifdef SAMPLE_CODE
	int rssi = -85;
	*value = rssi;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get the reading of CINR_R3 in dB.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: 2 ~ 25
 * Reference		:
 * Remarks			:
 */
int wmx_get_cinr_r3(int *value)
{
#ifdef SAMPLE_CODE
	int cinr_r3 = 20;
	*value = cinr_r3;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get the reading of CINR_R1 in dB.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: -3 ~ 23
 * Reference		:
 * Remarks			:
 */
int wmx_get_cinr_r1(int *value)
{
#ifdef SAMPLE_CODE
	int cinr_r1 = 18;
	*value = cinr_r1;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get current Frequency in KHz
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: 2300000 ~ 3800000
 * Reference		:
 * Remarks			:
 */
int wmx_get_frequency(int *value)
{
#ifdef SAMPLE_CODE
	*value = 2375000; // 2.375 GHz

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get current Bandwidth in KHz
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: 1250 ~ 28000
 * Reference		:
 * Remarks			:
 */
int wmx_get_bandwidth(int *value)
{
#ifdef SAMPLE_CODE
	*value = 10000; // 10 MHz

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get handover latency in ms.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int wmx_get_handover_latency(int *value)
{
#ifdef SAMPLE_CODE
	int latency = 500;
	*value = latency;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get handover success count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_handover_success_count(int *value)
{
#ifdef SAMPLE_CODE
	int counter = 15;
	*value = counter;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get handover failure count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_handover_failure_count(int *value)
{
#ifdef SAMPLE_CODE
	int counter = 12;
	*value = counter;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get modulation type of Uplink, please use constants MCS_TYPE_XXXX defined in msg_hal.h.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int wmx_get_ul_mcs(int *value)
{
#ifdef SAMPLE_CODE
	*value = MCS_TYPE_QPSK;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get modulation type of Downlink, please use constants MCS_TYPE_XXXX defined in msg_hal.h.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int wmx_get_dl_mcs(int *value)
{
#ifdef SAMPLE_CODE
	*value = MCS_TYPE_16QAM;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get Tx Power in dBm.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: -40 ~ 33
 * Reference		:
 * Remarks			:
 */
int wmx_get_tx_power(int *value)
{
#ifdef SAMPLE_CODE
	int tx_power = -25;
	*value = tx_power;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get IP layer Tx Byte count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_tx_byte(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long tx_byte = 10000000000000001ULL;
	*value = tx_byte;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get IP layer Rx Byte count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_rx_byte(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long rx_byte = 20000000000000001ULL;
	*value = rx_byte;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get IP layer Tx packet count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_tx_packet_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long tx_packet_count = 1001ULL;
	*value = tx_packet_count;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get IP layer Rx packet count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_rx_packet_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long rx_packet_count = 2001ULL;
	*value = rx_packet_count;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get IP layer Tx packet error count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_tx_packet_error_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long tx_packet_error_count = 101ULL;
	*value = tx_packet_error_count;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get IP layer Rx packet error count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_rx_packet_error_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long rx_packet_error_count = 201ULL;
	*value = rx_packet_error_count;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get MAC layer Tx frame count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_tx_frame_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long tx_frame_count = 100001ULL;
	*value = tx_frame_count;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get MAC layer Rx frame count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_rx_frame_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long rx_frame_count = 200001ULL;
	*value = rx_frame_count;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get MAC layer Tx frame error count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_tx_frame_error_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long tx_frame_error_count = 10001ULL;
	*value = tx_frame_error_count;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get MAC layer Rx frame error count since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			: This is a loop counter.
 */
int wmx_get_rx_frame_error_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long rx_frame_error_count = 20001ULL;
	*value = rx_frame_error_count;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get previous disconnection reason, please use constants defined in msg_hal.h.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int wmx_get_disconnect_reason(int *value)
{
#ifdef SAMPLE_CODE
	*value = DC_REASON_SYNCHRONIZATION_LOST;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get Neighboring BS Info defined in data_wmx.h.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: count = 0 ~ MAX_WMX_NGBR_BS_CNT
 *                  : list[n]
 * 					: 	.bs_id = MAC Address Format
 * 					: 	.rssi = -123 ~ -40, leave it empty if unavailable.
 * 					: 	.cinr_r3 = 2 ~ 25, leave it empty if unavailable.
 * 					: 	.cinr_r1 = -3 ~ 23, leave it empty if unavailable.
 * Reference		:
 * Remarks			:
 */
int wmx_get_neighboring_bs_info(int *count, wmx_bs_info list[MAX_WMX_NGBR_BS_CNT])
{
#ifdef SAMPLE_CODE
	char bs_id_list[2][6] = { { 0x1F, 0x1C, 0xCB, 0x0A, 0x0B, 0x0C }, { 0x1F, 0x1C, 0xCB, 0x0D, 0x0E, 0x0F } };

	// Count
	*count = 2;

	// All Available
	memcpy(list[0].bs_id, bs_id_list[0], 6);
	list[0].rssi = -90;
	list[0].cinr_r3 = 20;
	list[0].cinr_r1 = 15;

	// Only BS ID & RSSI Available
	memcpy(list[1].bs_id, bs_id_list[1], 6);
	list[1].rssi = -75;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: There are many service flows of WiMAX, please use the fastest one of uplink as max speed, unit is KByte.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int wmx_get_ul_service_flow_max_speed(int *value)
{
#ifdef SAMPLE_CODE
	*value = 10240;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: There are many service flows of WiMAX, please use the fastest one of downlink as max speed, unit is KByte.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int wmx_get_dl_service_flow_max_speed(int *value)
{
#ifdef SAMPLE_CODE
	*value = 20480;

	return 0;
#else

#endif
	return -1;
}
