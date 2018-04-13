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

#ifndef DATA_2G_H
#define DATA_2G_H

#include <stdint.h>
#include <limits.h>

#define MAX_TWO_G_NGBR_CELL_CNT	16

#define TWO_G_INVALID_CI        -1
#define TWO_G_INVALID_MCC       -1
#define TWO_G_INVALID_MNC       ""
#define TWO_G_INVALID_LAC       -1
#define TWO_G_INVALID_RSSI      INT_MAX
#define TWO_G_INVALID_RXQUAL	-1

#define TWO_G_WORK_MODE_GPRS    (NIF_TYPE_2G | 0x01)
#define TWO_G_WORK_MODE_EDGE	(NIF_TYPE_2G | 0x02)

enum {
	TWO_G_BAND_T_GSM_380 = 1,
	TWO_G_BAND_T_GSM_410,
	TWO_G_BAND_GSM_450,
	TWO_G_BAND_GSM_480,
	TWO_G_BAND_GSM_710,
	TWO_G_BAND_GSM_750,
	TWO_G_BAND_T_GSM_810,
	TWO_G_BAND_GSM_850,
	TWO_G_BAND_P_GSM_900,
	TWO_G_BAND_E_GSM_900,
	TWO_G_BAND_R_GSM_900,
	TWO_G_BAND_T_GSM_900,
	TWO_G_BAND_DCS_1800,
	TWO_G_BAND_PCS_1900
};

struct two_g_cell {
	int ci;
	int mcc;
	char mnc[4];
	int lac;
	int rssi;
	int rxqual;
};

int two_g_get_supp_freq_bands(int *p_bands);

int two_g_get_ip_addr(char ip_addr[40]);

int two_g_get_work_mode(int *p_mode);

int two_g_get_net_entry_latency(int *p_latency);

int two_g_get_ci(int *p_ci);

int two_g_get_rssi(int *p_rssi);

int two_g_get_rxqual(int *p_rxqual);

int two_g_get_arfcn(int *p_arfcn);

int two_g_get_mcc(int *p_mcc);

int two_g_get_mnc(char mnc[4]);

int two_g_get_lac(int *p_lac);

int two_g_get_handover_latency(int *p_latency);

int two_g_get_handover_success_cnt(int *p_cnt);

int two_g_get_handover_fail_cnt(int *p_cnt);

int two_g_get_ul_mcs(int *p_mcs);

int two_g_get_dl_mcs(int *p_mcs);

int two_g_get_tx_power(int *p_power);

int two_g_get_tx_byte(uint64_t *p_byte);

int two_g_get_tx_packet_cnt(uint64_t *p_cnt);

int two_g_get_tx_packet_err_cnt(uint64_t *p_cnt);

int two_g_get_tx_frame_cnt(uint64_t *p_cnt);

int two_g_get_tx_frame_err_cnt(uint64_t *p_cnt);

int two_g_get_rx_byte(uint64_t *p_byte);

int two_g_get_rx_packet_cnt(uint64_t *p_cnt);

int two_g_get_rx_packet_err_cnt(uint64_t *p_cnt);

int two_g_get_rx_frame_cnt(uint64_t *p_cnt);

int two_g_get_rx_frame_err_cnt(uint64_t *p_cnt);

int two_g_get_dc_reason(int *p_reason);

int two_g_get_ngbr_cells(struct two_g_cell cells[MAX_TWO_G_NGBR_CELL_CNT], int *p_cnt);

#endif
