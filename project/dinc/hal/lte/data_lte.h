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

#ifndef DATA_LTE_H
#define DATA_LTE_H

#include <stdint.h>

#define MAX_LTE_NGBR_CELL_CNT	16
#define MAX_LTE_SCC_CNT			5

// Supported Frequency Band
#define MAP_LTE_FREQ_BAND(freq) (1LL << (freq - 1))

// Channel Bandwidth
#define LTE_CHANNEL_BW_1_4		0x00000001
#define LTE_CHANNEL_BW_3		0x00000002
#define LTE_CHANNEL_BW_5		0x00000004
#define LTE_CHANNEL_BW_10		0x00000008
#define LTE_CHANNEL_BW_15		0x00000010
#define LTE_CHANNEL_BW_20		0x00000020

typedef struct _lte_cell_info
{
	int32_t cell_id;
	int32_t mcc;
	uint8_t mnc[4];
	int32_t lac;
	int32_t rssi;
	int32_t rsrp;
	float rsrq;
} lte_cell_info;

/*
 * LTE Info
 */
int lte_get_supported_freq_band(long long *value);
int lte_get_ip_address(char buff[16]);
int lte_get_network_entry_latency(int *value);
int lte_get_cell_id(int *value);
int lte_get_rssi(int *value);
int lte_get_rsrp(int *value);
int lte_get_rsrq(float *value);
int lte_get_cqi(int *value);
int lte_get_ul_earfcn(int *value);
int lte_get_dl_earfcn(int *value);
int lte_get_channel_bw(int *value);
int lte_get_mcc(int *value);
int lte_get_mnc(char buff[4]);
int lte_get_lac(int *value);
int lte_get_handover_latency(int *value);
int lte_get_handover_success_count(int *value);
int lte_get_handover_failure_count(int *value);
int lte_get_ul_mcs(int *value);
int lte_get_dl_mcs(int *value);
int lte_get_tx_power(int *value);
int lte_get_tx_byte(unsigned long long *value);
int lte_get_rx_byte(unsigned long long *value);
int lte_get_tx_packet_count(unsigned long long *value);
int lte_get_rx_packet_count(unsigned long long *value);
int lte_get_tx_packet_error_count(unsigned long long *value);
int lte_get_rx_packet_error_count(unsigned long long *value);
int lte_get_tx_frame_count(unsigned long long *value);
int lte_get_rx_frame_count(unsigned long long *value);
int lte_get_tx_frame_error_count(unsigned long long *value);
int lte_get_rx_frame_error_count(unsigned long long *value);
int lte_get_disconnect_reason(int *value);
int lte_get_neighboring_cell_info(int *count, lte_cell_info list[MAX_LTE_NGBR_CELL_CNT]);
int lte_get_ul_bearer_flow_max_speed(int *value);
int lte_get_dl_bearer_flow_max_speed(int *value);
int lte_get_scc_aggregated_count(uint8_t *value);
int lte_get_scc_cell_id(int value[MAX_LTE_SCC_CNT]);
int lte_get_scc_channel_bw(int value[MAX_LTE_SCC_CNT]);
int lte_get_scc_rsrp(int value[MAX_LTE_SCC_CNT]);
int lte_get_scc_rsrq(float value[MAX_LTE_SCC_CNT]);
int lte_get_scc_dl_earfcn(int value[MAX_LTE_SCC_CNT]);
#endif /* DATA_LTE_H */
