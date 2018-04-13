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

#ifndef DATA_WIFI_AP_H
#define DATA_WIFI_AP_H

#include <stdint.h>

#define MAX_WIFI_SSID_CNT       4
#define MAX_WIFI_SSID_LEN       32
#define MAX_WIFI_CH_CNT         8
#define MAX_WIFI_CLIENT_CNT     16
#define MAX_NEIGHBOR_WIFI_CNT   16

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

struct wifi_ssid_cfg {
	char ssid[MAX_WIFI_SSID_LEN + 1];
	int encrypt;
};

struct wifi_client {
	uint8_t bssid[6];
};

struct wifi_ap {
    uint8_t bssid[6];
    int mode;
    int encrypt;
    int ch;
    int rssi;
};

int wifi_ap_get_country_code(char code[2]);

int wifi_ap_get_supp_freqs(int *p_freqs);

int wifi_ap_get_supp_modes(int *p_modes);

int wifi_ap_get_supp_encrypts(int *p_encrypts);

int wifi_ap_get_work_freqs(int *p_freqs);

int wifi_ap_get_work_modes(int *p_modes);

int wifi_ap_get_work_chs(int chs[MAX_WIFI_CH_CNT], int *p_cnt);

int wifi_ap_get_ssid_cfgs(struct wifi_ssid_cfg cfgs[MAX_WIFI_SSID_CNT], int *p_cnt);

int wifi_ap_get_ip_addr(char ip_addr[40]);

int wifi_ap_get_clients(struct wifi_client clients[MAX_WIFI_CLIENT_CNT], int *p_cnt);

int wifi_ap_get_tx_power(int *p_power);

int wifi_ap_get_tx_byte(uint64_t *p_byte);

int wifi_ap_get_tx_fragment_success_cnt(uint64_t *p_cnt);

int wifi_ap_get_tx_frame_retry_cnt(uint64_t *p_cnt);

int wifi_ap_get_tx_ack_loss_cnt(uint64_t *p_cnt);

int wifi_ap_get_rx_byte(uint64_t *p_byte);

int wifi_ap_get_rx_fragment_success_cnt(uint64_t *p_cnt);

int wifi_ap_get_rx_frame_fcs_err_cnt(uint64_t *p_cnt);

int wifi_ap_get_ngbr_infos(struct wifi_ap ngbr_aps[MAX_NEIGHBOR_WIFI_CNT], int *p_cnt);
#endif
