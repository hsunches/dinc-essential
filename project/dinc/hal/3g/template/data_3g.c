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
#include "data_3g.h"
#include "msg_hal.h"

/*
 * Description		: Get 3G frequency band supported by device, please use MACRO to make the bitmap defined in data_3g.h.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: A bitmap
 *					: Bit[0:21,24,25]  - representing frequency band 1 to 22 and 25,26
 *					: Bit[22,23,26:31] - reserved
 * Reference		: 3GPP TS 25.101
 * Remarks			: Also reference to http://niviuk.free.fr/umts_band.php
 */
int third_g_get_supported_freq_band(int *value)
{
#ifdef SAMPLE_CODE
	*value |= MAP_3G_FREQ_BAND(1);
	*value |= MAP_3G_FREQ_BAND(2);
	*value |= MAP_3G_FREQ_BAND(4);

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
int third_g_get_ip_address(char buff[16])
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
 * Description      : Get current working mode by device, please use constants defined in data_3g.h.
 * Return Code      : 0 for Success, -1 for Failure
 * Data Valid Range :
 * Reference        : http://en.wikipedia.org/wiki/Universal_Mobile_Telecommunications_System, http://en.wikipedia.org/wiki/CDMA2000
 * Remarks          :
 */
int third_g_get_working_mode(int *value)
{
#ifdef SAMPLE_CODE
	*value = THIRD_G_TECH_HSPA_PLUS;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get latency in ms when UE enter the 3G network.
 *					: If the API doesn't support, get the time elapsed between
 *					: UE connection request and bearer response returned.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int third_g_get_network_entry_latency(int *value)
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
 * Description		: Get Cell ID in numeric format of NodeB UE is camping on.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: 1 ~ 65535
 * Reference		:
 * Remarks			:
 */
int third_g_get_cell_id(int *value)
{
#ifdef SAMPLE_CODE
	int cell_id = 250;
	*value = cell_id;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get the reading of RSSI in dBm.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: -100 ~ -25
 * Reference		: 3GPP TS 25.133
 * Remarks			:
 */
int third_g_get_rssi(int *value)
{
#ifdef SAMPLE_CODE
	int rssi = -80;
	*value = rssi;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get the reading of RSCP in dBm.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: -120 ~ -25
 * Reference		: 3GPP TS 25.133
 * Remarks			:
 */
int third_g_get_rscp(int *value)
{
#ifdef SAMPLE_CODE
	int rsrp = -90;
	*value = rsrp;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get the value index of CQI.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: 0 ~ 30
 * Reference		: 3GPP TS 25.214
 * Remarks			:
 */
int third_g_get_cqi(int *value)
{
#ifdef SAMPLE_CODE
	int cqi = 22;
	*value = cqi;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get current UARFCN of Uplink
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: 12 ~ 9888
 * Reference		: 3GPP TS 25.101
 * Remarks			: Also reference to http://niviuk.free.fr/umts_band.php
 */
int third_g_get_ul_uarfcn(int *value)
{
#ifdef SAMPLE_CODE
	int ul_uarfcn = 9750;
	*value = ul_uarfcn;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get current UARFCN of Downlink
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: 412 ~10838
 * Reference		: 3GPP TS 25.101
 * Remarks			: Also reference to http://niviuk.free.fr/umts_band.php
 */
int third_g_get_dl_uarfcn(int *value)
{
#ifdef SAMPLE_CODE
	int dl_uarfcn = 10700;
	*value = dl_uarfcn;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get current Channel Bandwidth, please use constants THIRD_G_CHANNEL_BW_XX defined in data_3g.h.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int third_g_get_channel_bw(int *value)
{
#ifdef SAMPLE_CODE
	*value = THIRD_G_CHANNEL_BW_5;
#else

#endif
	return 0;
}

/*
 * Description		: Get MCC of current PLMN.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: 3-digit number
 * Reference		: 3GPP TS 23.003
 * Remarks			: Also reference to https://en.wikipedia.org/wiki/Mobile_country_code
 */
int third_g_get_mcc(int *value)
{
#ifdef SAMPLE_CODE
	*value = 208;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get MNC of current PLMN.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: 2/3-digit number
 * Reference		: 3GPP TS 23.003
 * Remarks			: Also reference to https://en.wikipedia.org/wiki/Mobile_country_code
 */
int third_g_get_mnc(char buff[4])
{
#ifdef SAMPLE_CODE
	char *mnc208[] = { "01", "02", "04", "10", "11", "13", "14", "15" };
	memcpy(buff, mnc208[0], strlen(mnc208[0]));

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get LAC
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: 0 ~ 65535, except 0x0000 and 0xFFFE
 * Reference		: 3GPP TS 23.003
 * Remarks			:
 */
int third_g_get_lac(int *value)
{
#ifdef SAMPLE_CODE
	*value = 21021;

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
int third_g_get_handover_latency(int *value)
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
int third_g_get_handover_success_count(int *value)
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
int third_g_get_handover_failure_count(int *value)
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
int third_g_get_ul_mcs(int *value)
{
#ifdef SAMPLE_CODE
	*value = MCS_TYPE_16QAM;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get modulation type of Downlink, please use constants MCS_TYPE_XXXX define in msg_hal.h.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int third_g_get_dl_mcs(int *value)
{
#ifdef SAMPLE_CODE
	*value = MCS_TYPE_64QAM;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get Tx Power in dBm.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: -40 ~ 33
 * Reference		: 3GPP TS 25.101
 * Remarks			:
 */
int third_g_get_tx_power(int *value)
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
int third_g_get_tx_byte(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long tx_byte = 10000000000000001LLU;
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
int third_g_get_rx_byte(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long rx_byte = 20000000000000001LLU;
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
int third_g_get_tx_packet_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long tx_packet_count = 1001LLU;
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
int third_g_get_rx_packet_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long rx_packet_count = 2001LLU;
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
int third_g_get_tx_packet_error_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long tx_packet_error_count = 101LLU;
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
int third_g_get_rx_packet_error_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long rx_packet_error_count = 201LLU;
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
int third_g_get_tx_frame_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long tx_frame_count = 100001LLU;
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
int third_g_get_rx_frame_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long rx_frame_count = 200001LLU;
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
int third_g_get_tx_frame_error_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long tx_frame_error_count = 10001LLU;
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
int third_g_get_rx_frame_error_count(unsigned long long *value)
{
#ifdef SAMPLE_CODE
	unsigned long long rx_frame_error_count = 20001LLU;
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
int third_g_get_disconnect_reason(int *value)
{
#ifdef SAMPLE_CODE
	*value = DC_REASON_SYNCHRONIZATION_LOST;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get Neighboring Cell Info defined in data_3g.h.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: count = 0 ~ MAX_3G_NGBR_CELL_CNT
 *                  : list[n]
 * 					: 	.cell_id = 1 ~ 65535
 * 					: 	.mcc = 3-digit number, leave it empty if unavailable.
 * 					: 	.mnc = 2/3-digit number, leave it empty if unavailable.
 * 					: 	.lac = 0 ~ 65535 except 0x0000 and 0xFFFE, leave it empty if unavailable.
 * 					: 	.rssi = -100 ~ -25, leave it empty if unavailable.
 * 					: 	.rscp = -120 ~ -25, leave it empty if unavailable.
 * Reference		:
 * Remarks			:
 */
int third_g_get_neighboring_cell_info(int *count, third_g_cell_info list[MAX_3G_NGBR_CELL_CNT])
{
#ifdef SAMPLE_CODE
	*count = 2;

	// All Available
	list[0].cell_id = 20216;
	list[0].mcc = 208;
	memcpy(list[0].mnc, "01\0", 3);
	list[0].lac = 21212;
	list[0].rssi = -90;
	list[0].rscp = -80;

	// Only Cell ID & RSSI Available
	list[1].cell_id = 20238;
	list[1].rssi = -75;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: There are many bearer flows of 3G, please use the fastest one of uplink as max speed, unit is KByte.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int third_g_get_ul_bearer_flow_max_speed(int *value)
{
#ifdef SAMPLE_CODE
	*value = 10240;

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: There are many bearer flows of 3G, please use the fastest one of downlink as max speed, unit is KByte.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	:
 * Reference		:
 * Remarks			:
 */
int third_g_get_dl_bearer_flow_max_speed(int *value)
{
#ifdef SAMPLE_CODE
	*value = 20480;

	return 0;
#else

#endif
	return -1;
}
