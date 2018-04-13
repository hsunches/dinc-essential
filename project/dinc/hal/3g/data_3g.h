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

#ifndef DATA_3G_H
#define DATA_3G_H

#include <stdint.h>

#define MAX_3G_NGBR_CELL_CNT	16

// Supported Frequency List
#define MAP_3G_FREQ_BAND(freq) (1 << (freq - 1))

// Working Mode of WCDMA
#define THIRD_G_TECH_WCDMA_FDD      0x01
#define THIRD_G_TECH_WCDMA_TDD      0x02
#define THIRD_G_TECH_TD_SCDMA       0x03
#define THIRD_G_TECH_HSDPA          0x04
#define THIRD_G_TECH_HSUPA          0x05
#define THIRD_G_TECH_HSPA_PLUS      0x06

// Working Mode of CDMA2000
#define THIRD_G_TECH_EV_DO          0x10
#define THIRD_G_TECH_EV_DO_REV_A    0x20
#define THIRD_G_TECH_EV_DO_REV_B    0x30

// Channel Bandwidth
#define THIRD_G_CHANNEL_BW_1_4		0x01
#define THIRD_G_CHANNEL_BW_3		0x02
#define THIRD_G_CHANNEL_BW_5		0x04
#define THIRD_G_CHANNEL_BW_10		0x08
#define THIRD_G_CHANNEL_BW_15		0x10
#define THIRD_G_CHANNEL_BW_20		0x20

typedef struct _third_g_cell_info
{
    int32_t cell_id;
    int32_t mcc;
    uint8_t mnc[4];
    int32_t lac;
    int32_t rssi;
    int32_t rscp;
} third_g_cell_info;

/*
 * 3G Info
 */
int third_g_get_supported_freq_band(int *value);
int third_g_get_ip_address(char buff[16]);
int third_g_get_working_mode(int *value);
int third_g_get_network_entry_latency(int *value);
int third_g_get_cell_id(int *value);
int third_g_get_rssi(int *value);
int third_g_get_rscp(int *value);
int third_g_get_cqi(int *value);
int third_g_get_ul_uarfcn(int *value);
int third_g_get_dl_uarfcn(int *value);
int third_g_get_channel_bw(int *value);
int third_g_get_mcc(int *value);
int third_g_get_mnc(char buff[4]);
int third_g_get_lac(int *value);
int third_g_get_handover_latency(int *value);
int third_g_get_handover_success_count(int *value);
int third_g_get_handover_failure_count(int *value);
int third_g_get_ul_mcs(int *value);
int third_g_get_dl_mcs(int *value);
int third_g_get_tx_power(int *value);
int third_g_get_tx_byte(unsigned long long *value);
int third_g_get_rx_byte(unsigned long long *value);
int third_g_get_tx_packet_count(unsigned long long *value);
int third_g_get_rx_packet_count(unsigned long long *value);
int third_g_get_tx_packet_error_count(unsigned long long *value);
int third_g_get_rx_packet_error_count(unsigned long long *value);
int third_g_get_tx_frame_count(unsigned long long *value);
int third_g_get_rx_frame_count(unsigned long long *value);
int third_g_get_tx_frame_error_count(unsigned long long *value);
int third_g_get_rx_frame_error_count(unsigned long long *value);
int third_g_get_disconnect_reason(int *value);
int third_g_get_neighboring_cell_info(int *count, third_g_cell_info list[MAX_3G_NGBR_CELL_CNT]);
int third_g_get_ul_bearer_flow_max_speed(int *value);
int third_g_get_dl_bearer_flow_max_speed(int *value);

#endif /* DATA_3G_H */
