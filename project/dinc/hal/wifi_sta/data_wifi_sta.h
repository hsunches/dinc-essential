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

#ifndef DATA_WIFI_STA_H
#define DATA_WIFI_STA_H

#include <stdint.h>

#define MAX_WIFI_SSID_LEN   32
#define MAX_WIFI_AP_CNT     16

enum {
    WIFI_FREQ_2_4G  = 1,
    WIFI_FREQ_3_6G  = 2,
    WIFI_FREQ_4_9G  = 4,
    WIFI_FREQ_5G    = 8,
    WIFI_FREQ_60G   = 16
};

enum {
    WIFI_MODE_A     = 1,
    WIFI_MODE_B     = 2,
    WIFI_MODE_G     = 4,
    WIFI_MODE_N     = 8,
    WIFI_MODE_AC    = 16,
    WIFI_MODE_AD    = 32
};

enum {
    WIFI_ENCRYPT_WEP    = 1,
    WIFI_ENCRYPT_WPA    = 2,
    WIFI_ENCRYPT_WPA2   = 4
};

struct wifi_ap {
	uint8_t bssid[6];
	int mode;
	int encrypt;
	int ch;
	int rssi;
};

int wifi_sta_get_country_code(char code[2]);

int wifi_sta_get_supp_freqs(int *p_bitmap);

int wifi_sta_get_supp_modes(int *p_bitmap);

int wifi_sta_get_supp_encrypts(int *p_bitmap);

int wifi_sta_get_work_freq(int *p_bitmap);

int wifi_sta_get_work_mode(int *p_bitmap);

int wifi_sta_get_work_encrypt(int *p_bitmap);

int wifi_sta_get_work_ch(int *p_ch);

int wifi_sta_get_ngbr_aps(struct wifi_ap aps[MAX_WIFI_AP_CNT], int *p_cnt);

int wifi_sta_get_sta_bssid(uint8_t bssid[6]);

int wifi_sta_get_ssid(char ssid[MAX_WIFI_SSID_LEN + 1]);

int wifi_sta_get_rssi(int *p_rssi);

int wifi_sta_get_tx_power(int *p_power);

int wifi_sta_get_tx_byte(uint64_t *p_byte);

int wifi_sta_get_tx_fragment_success_cnt(uint64_t *p_cnt);

int wifi_sta_get_tx_frame_retry_cnt(uint64_t *p_cnt);

int wifi_sta_get_tx_ack_loss_cnt(uint64_t *p_cnt);

int wifi_sta_get_rx_byte(uint64_t *p_byte);

int wifi_sta_get_rx_fragment_success_cnt(uint64_t *p_cnt);

int wifi_sta_get_rx_frame_fcs_err_cnt(uint64_t *p_cnt);

#endif
