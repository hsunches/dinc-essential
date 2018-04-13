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

#ifndef DC_WIFI_AP_DATA_SET_H
#define DC_WIFI_AP_DATA_SET_H

#include <stdint.h>
#include "data_wifi_ap.h"
#include "util.h"

#define WIFI_AP_REPORT_INTERVAL 60

enum {
	PREV,
	CURR
};

struct ip_info {
	int len;
	uint8_t addr[16];
};

typedef struct {
	int routine_cnt;
	int idle_count;
	uint64_t uid;
	char country_code[2];
	int supp_freqs;
	int supp_modes;
	int supp_encrypts;
	int work_freqs;
	int work_modes;

	int work_ch_cnt;
	int work_chs[MAX_WIFI_CH_CNT];

	int ssid_cnt;
	struct wifi_ssid_cfg ssid_cfgs[MAX_WIFI_SSID_CNT];

	struct ip_info wan_ip_info;

	int client_cnt;
	struct wifi_client clients[MAX_WIFI_CLIENT_CNT];

	int ngbr_ap_cnt;
	struct wifi_ap ngbr_aps[MAX_NEIGHBOR_WIFI_CNT];

	int tx_power;

	uint64_t tx_byte[2];
	uint64_t rx_byte[2];

	int ul_rate_cnt;
	int ul_rate[MAX_REPORT_INTERVAL];
	int ul_rate_max;
	int ul_rate_min;
	int ul_rate_mean;
	double ul_rate_std_dev_plus;
	double ul_rate_std_dev_minus;

	int dl_rate_cnt;
	int dl_rate[MAX_REPORT_INTERVAL];
	int dl_rate_max;
	int dl_rate_min;
	int dl_rate_mean;
	double dl_rate_std_dev_plus;
	double dl_rate_std_dev_minus;

	uint64_t tx_fragment_success_cnt[2];
	uint64_t rx_fragment_success_cnt[2];
	uint64_t tx_frame_retry_cnt[2];
	uint64_t tx_ack_loss_cnt[2];
	uint64_t rx_frame_fcs_err_cnt[2];
} wifi_ap_data_set;

extern wifi_ap_data_set* gp_wifi_ap_data_set;

extern int g_report_interval;

typedef struct {
	int idle_threshold;
} wifi_ap_cfg;

extern wifi_ap_cfg* gp_wifi_ap_cfg;

int wifi_ap_pack_dev_info(uint8_t *data, void *arg);
int wifi_ap_pack_perf_info(uint8_t *data, void *arg);

#endif
