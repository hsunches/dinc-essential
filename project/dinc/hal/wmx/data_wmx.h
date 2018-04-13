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

#ifndef DATA_WMX_H
#define DATA_WMX_H

#include <stdint.h>

#define MAX_WMX_NGBR_BS_CNT	16

// Supported Freq Band
#define WIMAX_FREQ_BAND_2_3		0x01
#define WIMAX_FREQ_BAND_2_5		0x02
#define WIMAX_FREQ_BAND_3_5		0x04
#define WIMAX_FREQ_BAND_3_8		0x08

typedef struct _wmx_bs_info
{
	int32_t rssi;
	int32_t cinr_r3;
	int32_t cinr_r1;
	uint8_t bs_id[6];
} wmx_bs_info;

/*
 * WiMAX Info
 */
int wmx_get_supported_freq_band(int *value);
int wmx_get_ip_address(char buff[40]);
int wmx_get_network_entry_latency(int *value);
int wmx_get_bs_id(uint8_t buff[6]);
int wmx_get_rssi(int *value);
int wmx_get_cinr_r3(int *value);
int wmx_get_cinr_r1(int *value);
int wmx_get_frequency(int *value);
int wmx_get_bandwidth(int *value);
int wmx_get_handover_latency(int *value);
int wmx_get_handover_success_count(int *value);
int wmx_get_handover_failure_count(int *value);
int wmx_get_ul_mcs(int *value);
int wmx_get_dl_mcs(int *value);
int wmx_get_tx_power(int *value);
int wmx_get_tx_byte(unsigned long long *value);
int wmx_get_rx_byte(unsigned long long *value);
int wmx_get_tx_packet_count(unsigned long long *value);
int wmx_get_rx_packet_count(unsigned long long *value);
int wmx_get_tx_packet_error_count(unsigned long long *value);
int wmx_get_rx_packet_error_count(unsigned long long *value);
int wmx_get_tx_frame_count(unsigned long long *value);
int wmx_get_rx_frame_count(unsigned long long *value);
int wmx_get_tx_frame_error_count(unsigned long long *value);
int wmx_get_rx_frame_error_count(unsigned long long *value);
int wmx_get_disconnect_reason(int *value);
int wmx_get_neighboring_bs_info(int *count, wmx_bs_info list[MAX_WMX_NGBR_BS_CNT]);
int wmx_get_ul_service_flow_max_speed(int *value);
int wmx_get_dl_service_flow_max_speed(int *value);

#endif /* DATA_WMX_H */
