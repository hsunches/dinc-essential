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
#include <stdint.h>
#include "dc_wifi_ap_data_set.h"
#include "msg_format.h"
#include "util.h"

wifi_ap_data_set* gp_wifi_ap_data_set;
wifi_ap_cfg* gp_wifi_ap_cfg;

// int g_report_interval = MAX_REPORT_INTERVAL;
extern int g_report_interval;

int wifi_ap_pack_dev_info(uint8_t *data, void *arg) {
	uint8_t *p;
	int i;

	p = data;
	PUT_INT(p, util_htonl(IPC_MSG_SEND_REPORT), 32);
	PUT_INT(p, util_htonl(IPC_DC_WIFI_AP), 32);
	PUT_INT(p, DINP_ROLE_WIFI_AP | DINP_HDR_MASK_UID, 8);
	PUT_INT(p, DINP_MSG_DC_DEVICE_INFO, 8);
	PUT_INT(p, util_htonll(gp_wifi_ap_data_set->uid), 64);
	PUT_MEM(p, gp_wifi_ap_data_set->country_code, 2);
	PUT_INT(p, gp_wifi_ap_data_set->supp_freqs, 8);
	PUT_INT(p, gp_wifi_ap_data_set->supp_modes, 8);
	PUT_INT(p, gp_wifi_ap_data_set->supp_encrypts, 8);

	PUT_INT(p, gp_wifi_ap_data_set->ngbr_ap_cnt, 8);
	
	for (i = 0; i < gp_wifi_ap_data_set->ngbr_ap_cnt; i++) {
		PUT_MEM(p, gp_wifi_ap_data_set->ngbr_aps[i].bssid, 6);
		PUT_INT(p, gp_wifi_ap_data_set->ngbr_aps[i].mode, 8);
		PUT_INT(p, gp_wifi_ap_data_set->ngbr_aps[i].encrypt, 8);
		PUT_INT(p, gp_wifi_ap_data_set->ngbr_aps[i].ch, 8);
		PUT_INT(p, gp_wifi_ap_data_set->ngbr_aps[i].rssi, 8);
	}

	return p - data;
}

void put_var_int(uint8_t **pp, int value) {
	if (value >= (1 << 14)) {
		int masked_value_be = util_htonl(value | 0x800000);

		PUT_MEM(*pp, ((uint8_t *)&masked_value_be) + 1, 3);
	} else if (value >= (1 << 6)) {
		PUT_INT(*pp, util_htons(value | 0x4000), 16);
	} else {
		PUT_INT(*pp, value, 8);
	}
}

int wifi_ap_pack_perf_info(uint8_t *data, void *arg) {
	uint8_t *p;
	int i;
	
	p = data;
	PUT_INT(p, util_htonl(IPC_MSG_SEND_REPORT), 32);
	PUT_INT(p, util_htonl(IPC_DC_WIFI_AP), 32);
	PUT_INT(p, DINP_ROLE_WIFI_AP | DINP_HDR_MASK_UID, 8);
	PUT_INT(p, DINP_MSG_DC_PERFORMANCE_INFO, 8);
	PUT_INT(p, util_htonll(gp_wifi_ap_data_set->uid), 64);
	PUT_INT(p, gp_wifi_ap_data_set->work_freqs, 8);
	PUT_INT(p, gp_wifi_ap_data_set->work_modes, 8);
	PUT_INT(p, gp_wifi_ap_data_set->work_ch_cnt, 8);

	for (i = 0; i < gp_wifi_ap_data_set->work_ch_cnt; i++) {
		PUT_INT(p, gp_wifi_ap_data_set->work_chs[i], 8);
	}

	PUT_INT(p, gp_wifi_ap_data_set->ssid_cnt, 8);

	for (i = 0; i < gp_wifi_ap_data_set->ssid_cnt; i++) {
		PUT_STR(p, gp_wifi_ap_data_set->ssid_cfgs[i].ssid);
		PUT_INT(p, gp_wifi_ap_data_set->ssid_cfgs[i].encrypt, 8);
	}

	PUT_INT(p, gp_wifi_ap_data_set->wan_ip_info.len, 8);

	if (gp_wifi_ap_data_set->wan_ip_info.len != -1) {
		PUT_MEM(p, gp_wifi_ap_data_set->wan_ip_info.addr, gp_wifi_ap_data_set->wan_ip_info.len);
	}

	PUT_INT(p, gp_wifi_ap_data_set->client_cnt, 8);

	for (i = 0; i < gp_wifi_ap_data_set->client_cnt; i++) {
		PUT_MEM(p, gp_wifi_ap_data_set->clients[i].bssid, 6);
	}

#define MAKE_LIST(s, m)	{s->m##_max, s->m##_min, s->m##_mean, s->m##_std_dev_plus, s->m##_std_dev_minus}

	{
		struct {
			int max;
			int min;
			int mean;
			double std_dev_plus;
			double std_dev_minus;
		} list[] = {
			MAKE_LIST(gp_wifi_ap_data_set, ul_rate),
			MAKE_LIST(gp_wifi_ap_data_set, dl_rate),
		};
		
		for (i = 0; i < ARRAY_SIZE(list); i++) {
			if (list[i].max >= 0) {
				put_var_int(&p, list[i].max / 1024);
			} else {
				PUT_INT(p, -1, 16);
			}
			
			if (list[i].min >= 0) {
				put_var_int(&p, list[i].min / 1024);
			} else {
				PUT_INT(p, -1, 16);
			}

			if (list[i].mean >= 0) {
				put_var_int(&p, list[i].mean / 1024);
			} else {
				PUT_INT(p, -1, 16);
			}

			if (list[i].std_dev_minus >= 0.0) {
				put_var_int(&p, (int)(list[i].std_dev_minus / 1024.0));
			} else {
				PUT_INT(p, -1, 16);
			}

			if (list[i].std_dev_plus >= 0.0) {
				put_var_int(&p, (int)(list[i].std_dev_plus / 1024.0));
			} else {
				PUT_INT(p, -1, 16);
			}
		}
	}
	
	{
		uint64_t *list[] = {
			gp_wifi_ap_data_set->tx_fragment_success_cnt,
			gp_wifi_ap_data_set->rx_fragment_success_cnt,
			gp_wifi_ap_data_set->tx_frame_retry_cnt,
			gp_wifi_ap_data_set->tx_ack_loss_cnt,
			gp_wifi_ap_data_set->rx_frame_fcs_err_cnt,
		};

		for (i = 0; i < ARRAY_SIZE(list); i++) {
			if (list[i][CURR] == -1 || list[i][PREV] == -1) {
				PUT_INT(p, -1, 16);
			} else {
				PUT_INT(p, util_htons((uint16_t)(list[i][CURR] - list[i][PREV])), 16);
			}
		}
	}
	
	PUT_INT(p, gp_wifi_ap_data_set->tx_power, 8);
	PUT_INT(p, g_report_interval, 8);
	return p - data;
}
