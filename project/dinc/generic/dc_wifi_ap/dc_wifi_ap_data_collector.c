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
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "msg_format.h"
#include "msg_hal.h"
#include "dc_wifi_ap_data_collector.h"
#include "dc_wifi_ap_data_set.h"
#include "util.h"
#include "data_wifi_ap.h"
#include "data_dev.h"

#define BUF_SIZE	256

typedef int (*pack_func)(uint8_t *data, void *arg);

static void clct_perf_info(void);

static void clct_dev_uid(void);

static void clct_wifi_ap_country_code(void);
static void clct_wifi_ap_supp_freqs(void);
static void clct_wifi_ap_supp_modes(void);
static void clct_wifi_ap_supp_encrypts(void);
static void clct_wifi_ap_work_freqs(void);
static void clct_wifi_ap_work_modes(void);
static void clct_wifi_ap_work_chs(void);
static void clct_wifi_ap_ssid_cfgs(void);
static void clct_wifi_ap_wan_ip_addr(void);
static void clct_wifi_ap_clients(void);
static void clct_wifi_ap_tx_power(void);
static int clct_wifi_ap_tx_byte(void);
static void clct_wifi_ap_tx_fragment_success_cnt(void);
static void clct_wifi_ap_tx_frame_retry_cnt(void);
static void clct_wifi_ap_tx_ack_loss_cnt(void);
static int clct_wifi_ap_rx_byte(void);
static void clct_wifi_ap_rx_fragment_success_cnt(void);
static void clct_wifi_ap_rx_frame_fcs_err_cnt(void);
static void clct_wifi_ap_ngbr_infos(void);
static void clct_wifi_ap_throughput_byte(void);

static void calc_perf_info(void);

static int send_packed_info(write_func writer, pack_func packer, void *arg);

static void calc_peak_mean(const int list[], int cnt, int *p_max, int *p_min, double *p_mean);
static void calc_std_dev(const int list[], int cnt, double mean, double *p_plus, double *p_minus);
static void wifi_ap_current_throughput_update(void);

extern uint64_t util_get_dev_uid(void);
extern double util_unsafe_sqrt(double val, int digits);

int clct_wifi_ap_dev_info(write_func writer) {
	int ret;

	clct_dev_uid();
	clct_wifi_ap_country_code();
	clct_wifi_ap_supp_freqs();
	clct_wifi_ap_supp_modes();
	clct_wifi_ap_supp_encrypts();
	clct_wifi_ap_tx_byte();
	clct_wifi_ap_tx_fragment_success_cnt();
	clct_wifi_ap_tx_frame_retry_cnt();
	clct_wifi_ap_tx_ack_loss_cnt();
	clct_wifi_ap_rx_byte();
	clct_wifi_ap_rx_fragment_success_cnt();
	clct_wifi_ap_rx_frame_fcs_err_cnt();
	clct_wifi_ap_ngbr_infos();
	ret = send_packed_info(writer, &wifi_ap_pack_dev_info, NULL);
	gp_wifi_ap_data_set->ul_rate_cnt = 0;
	gp_wifi_ap_data_set->dl_rate_cnt = 0;
	return ret;
}

int clct_wifi_ap_routine_info(write_func writer) {
	// clct_wifi_ap_tx_byte();
	// clct_wifi_ap_rx_byte();
	clct_wifi_ap_throughput_byte();
	gp_wifi_ap_data_set->routine_cnt++;

	if (gp_wifi_ap_data_set->idle_count > gp_wifi_ap_cfg->idle_threshold && g_report_interval < MAX_REPORT_INTERVAL)
    {
        g_report_interval++;
    }
    
	if (gp_wifi_ap_data_set->routine_cnt == g_report_interval) {
		clct_perf_info();
		calc_perf_info();
		send_packed_info(writer, &wifi_ap_pack_perf_info, NULL);
		g_report_interval = WIFI_AP_REPORT_INTERVAL;
		gp_wifi_ap_data_set->routine_cnt = 0;
		gp_wifi_ap_data_set->idle_count = 0;
		gp_wifi_ap_data_set->ul_rate_cnt = 0;
		gp_wifi_ap_data_set->dl_rate_cnt = 0;
		wifi_ap_current_throughput_update();
	}

	return 0;
}

static void clct_wifi_ap_throughput_byte(void) 
{
	int tx_byte = clct_wifi_ap_tx_byte();
	int rx_byte = clct_wifi_ap_rx_byte();

	if (tx_byte != 0 || rx_byte != 0)
	{
		gp_wifi_ap_data_set->idle_count = 0;
	}
	else
	{
		gp_wifi_ap_data_set->idle_count++;
	}
}

static void clct_perf_info(void) {
	clct_wifi_ap_work_freqs();
	clct_wifi_ap_work_modes();
	clct_wifi_ap_work_chs();
	clct_wifi_ap_ssid_cfgs();
	clct_wifi_ap_wan_ip_addr();
	clct_wifi_ap_clients();
	clct_wifi_ap_tx_power();
	clct_wifi_ap_tx_fragment_success_cnt();
	clct_wifi_ap_tx_frame_retry_cnt();
	clct_wifi_ap_tx_ack_loss_cnt();
	clct_wifi_ap_rx_fragment_success_cnt();
	clct_wifi_ap_rx_frame_fcs_err_cnt();
}

static void clct_dev_uid(void) {
	// char uid[DEV_UID_LEN + 1];

	// if (dev_get_uid(uid) < 0) {
	// 	gp_wifi_ap_data_set->uid = -1;
	// } else {
	// 	gp_wifi_ap_data_set->uid = (uint64_t)strtoull(uid, NULL, 16);
	// }
	gp_wifi_ap_data_set->uid = util_get_dev_uid();
}

static void clct_wifi_ap_country_code(void) {
	if (wifi_ap_get_country_code(gp_wifi_ap_data_set->country_code) < 0) {
		memset(gp_wifi_ap_data_set->country_code, -1, 2);
	}
}

static void clct_wifi_ap_supp_freqs(void) {
	if (wifi_ap_get_supp_freqs(&gp_wifi_ap_data_set->supp_freqs) < 0) {
		gp_wifi_ap_data_set->supp_freqs = -1;
	}
}

static void clct_wifi_ap_supp_modes(void) {
	if (wifi_ap_get_supp_modes(&gp_wifi_ap_data_set->supp_modes) < 0) {
		gp_wifi_ap_data_set->supp_modes = -1;
	}
}

static void clct_wifi_ap_supp_encrypts(void) {
	if (wifi_ap_get_supp_encrypts(&gp_wifi_ap_data_set->supp_encrypts) < 0) {
		gp_wifi_ap_data_set->supp_encrypts = -1;
	}
}

static void clct_wifi_ap_work_freqs(void) {
	if (wifi_ap_get_work_freqs(&gp_wifi_ap_data_set->work_freqs) < 0) {
		gp_wifi_ap_data_set->work_freqs = -1;
	}
}

static void clct_wifi_ap_work_modes(void) {
	if (wifi_ap_get_work_modes(&gp_wifi_ap_data_set->work_modes) < 0) {
		gp_wifi_ap_data_set->work_modes = -1;
	}
}

static void clct_wifi_ap_work_chs(void) {
	if (wifi_ap_get_work_chs(gp_wifi_ap_data_set->work_chs, &gp_wifi_ap_data_set->work_ch_cnt) < 0) {
		gp_wifi_ap_data_set->work_ch_cnt = -1;
	}
}

static void clct_wifi_ap_ssid_cfgs(void) {
	if (wifi_ap_get_ssid_cfgs(gp_wifi_ap_data_set->ssid_cfgs, &gp_wifi_ap_data_set->ssid_cnt) < 0) {
		gp_wifi_ap_data_set->ssid_cnt = -1;
	}
}

static void clct_wifi_ap_wan_ip_addr(void) {
	char ip_addr[40];

	if (wifi_ap_get_ip_addr(ip_addr) < 0) {
		memset(&gp_wifi_ap_data_set->wan_ip_info, -1, sizeof(struct ip_info));
	} else {
		int addr_family;
		
		if (strchr(ip_addr, '.') != NULL) {
			addr_family = AF_INET;
			gp_wifi_ap_data_set->wan_ip_info.len = sizeof(struct in_addr);
		} else {
			addr_family = AF_INET6;
			gp_wifi_ap_data_set->wan_ip_info.len = sizeof(struct in6_addr);
		}

		inet_pton(addr_family, ip_addr, &gp_wifi_ap_data_set->wan_ip_info.addr);
	}
}

static void clct_wifi_ap_clients(void) {
	if (wifi_ap_get_clients(gp_wifi_ap_data_set->clients, &gp_wifi_ap_data_set->client_cnt) < 0) {
		gp_wifi_ap_data_set->client_cnt = -1;
	}
}

static void clct_wifi_ap_tx_power(void) {
	if (wifi_ap_get_tx_power(&gp_wifi_ap_data_set->tx_power) < 0) {
		gp_wifi_ap_data_set->tx_power = 127;
	}
}

static int clct_wifi_ap_tx_byte(void) {
	gp_wifi_ap_data_set->tx_byte[PREV] = gp_wifi_ap_data_set->tx_byte[CURR];
	
	if (wifi_ap_get_tx_byte(&gp_wifi_ap_data_set->tx_byte[CURR]) < 0) {
		gp_wifi_ap_data_set->tx_byte[CURR] = -1;
	} else if (gp_wifi_ap_data_set->tx_byte[PREV] != -1) {
		int index = gp_wifi_ap_data_set->ul_rate_cnt;
		gp_wifi_ap_data_set->ul_rate[gp_wifi_ap_data_set->ul_rate_cnt++] = (int)(gp_wifi_ap_data_set->tx_byte[CURR] - gp_wifi_ap_data_set->tx_byte[PREV]);

		return gp_wifi_ap_data_set->ul_rate[index];
	}

	return 0;
}

static void clct_wifi_ap_tx_fragment_success_cnt(void) {
	gp_wifi_ap_data_set->tx_fragment_success_cnt[PREV] = gp_wifi_ap_data_set->tx_fragment_success_cnt[CURR];
	
	if (wifi_ap_get_tx_fragment_success_cnt(&gp_wifi_ap_data_set->tx_fragment_success_cnt[CURR]) < 0) {
		gp_wifi_ap_data_set->tx_fragment_success_cnt[CURR] = -1;
	}
}

static void clct_wifi_ap_tx_frame_retry_cnt(void) {
	gp_wifi_ap_data_set->tx_frame_retry_cnt[PREV] = gp_wifi_ap_data_set->tx_frame_retry_cnt[CURR];
	
	if (wifi_ap_get_tx_frame_retry_cnt(&gp_wifi_ap_data_set->tx_frame_retry_cnt[CURR]) < 0) {
		gp_wifi_ap_data_set->tx_frame_retry_cnt[CURR] = -1;
	}
}

static void clct_wifi_ap_tx_ack_loss_cnt(void) {
	gp_wifi_ap_data_set->tx_ack_loss_cnt[PREV] = gp_wifi_ap_data_set->tx_ack_loss_cnt[CURR];
	
	if (wifi_ap_get_tx_ack_loss_cnt(&gp_wifi_ap_data_set->tx_ack_loss_cnt[CURR]) < 0) {
		gp_wifi_ap_data_set->tx_ack_loss_cnt[CURR] = -1;
	}
}

static int clct_wifi_ap_rx_byte(void) {
	gp_wifi_ap_data_set->rx_byte[PREV] = gp_wifi_ap_data_set->rx_byte[CURR];
	
	if (wifi_ap_get_rx_byte(&gp_wifi_ap_data_set->rx_byte[CURR]) < 0) {
		gp_wifi_ap_data_set->rx_byte[CURR] = -1;
	} else if (gp_wifi_ap_data_set->rx_byte[PREV] != -1) {
		int index = gp_wifi_ap_data_set->dl_rate_cnt;
		gp_wifi_ap_data_set->dl_rate[gp_wifi_ap_data_set->dl_rate_cnt++] = (int)(gp_wifi_ap_data_set->rx_byte[CURR] - gp_wifi_ap_data_set->rx_byte[PREV]);

		return gp_wifi_ap_data_set->dl_rate[index];
	}

	return 0;
}

static void wifi_ap_current_throughput_update(void) 
{
	// reset previous throughput
	gp_wifi_ap_data_set->tx_byte[PREV] = -1;
	gp_wifi_ap_data_set->rx_byte[PREV] = -1;

	if (wifi_ap_get_tx_byte(&gp_wifi_ap_data_set->tx_byte[CURR]) < 0) {
		gp_wifi_ap_data_set->tx_byte[CURR] = -1;
	}
	
	if (wifi_ap_get_rx_byte(&gp_wifi_ap_data_set->rx_byte[CURR]) < 0) {
		gp_wifi_ap_data_set->rx_byte[CURR] = -1;
	}
}

static void clct_wifi_ap_rx_fragment_success_cnt(void) {
	gp_wifi_ap_data_set->rx_fragment_success_cnt[PREV] = gp_wifi_ap_data_set->rx_fragment_success_cnt[CURR];
	
	if (wifi_ap_get_rx_fragment_success_cnt(&gp_wifi_ap_data_set->rx_fragment_success_cnt[CURR]) < 0) {
		gp_wifi_ap_data_set->rx_fragment_success_cnt[CURR] = -1;
	}
}

static void clct_wifi_ap_rx_frame_fcs_err_cnt(void) {
	gp_wifi_ap_data_set->rx_frame_fcs_err_cnt[PREV] = gp_wifi_ap_data_set->rx_frame_fcs_err_cnt[CURR];
	
	if (wifi_ap_get_rx_frame_fcs_err_cnt(&gp_wifi_ap_data_set->rx_frame_fcs_err_cnt[CURR]) < 0) {
		gp_wifi_ap_data_set->rx_frame_fcs_err_cnt[CURR] = -1;
	}
}

static void clct_wifi_ap_ngbr_infos(void) {
	int i;

	for (i = 0; i < MAX_NEIGHBOR_WIFI_CNT; i++) {
		gp_wifi_ap_data_set->ngbr_aps[i].mode = -1;
		gp_wifi_ap_data_set->ngbr_aps[i].encrypt = -1;
		gp_wifi_ap_data_set->ngbr_aps[i].ch = -1;
		gp_wifi_ap_data_set->ngbr_aps[i].rssi = INT_MAX;
	}

	if (wifi_ap_get_ngbr_infos(gp_wifi_ap_data_set->ngbr_aps, &gp_wifi_ap_data_set->ngbr_ap_cnt) < 0) {
		gp_wifi_ap_data_set->ngbr_ap_cnt = -1;
	} else {
		for (i = 0; i < gp_wifi_ap_data_set->ngbr_ap_cnt; i++) {
			if (gp_wifi_ap_data_set->ngbr_aps[i].rssi == INT_MAX) {
				gp_wifi_ap_data_set->ngbr_aps[i].rssi = 127;
			}
		}
	}
}

static void calc_perf_info() {
	int i;
	int max, min;
	double mean;
	double std_dev_minus, std_dev_plus;

#define MAKE_LIST(s, m)	{s->m##_cnt, s->m, &s->m##_max, &s->m##_min, &s->m##_mean, &s->m##_std_dev_plus, &s->m##_std_dev_minus}

	{
		struct {
			int cnt;
			int *data;
			int *p_max;
			int *p_min;
			int *p_mean;
			double *p_std_dev_plus;
			double *p_std_dev_minus;
		} list[] = {
			MAKE_LIST(gp_wifi_ap_data_set, ul_rate),
			MAKE_LIST(gp_wifi_ap_data_set, dl_rate)
		};
		
		for (i = 0; i < ARRAY_SIZE(list); i++) {
			max = -1;
			min = -1;
			mean = -1.0;
			std_dev_plus = -1.0;
			std_dev_minus = -1.0;
			calc_peak_mean(list[i].data, list[i].cnt, &max, &min, &mean);
			calc_std_dev(list[i].data, list[i].cnt, mean, &std_dev_plus, &std_dev_minus);
			*list[i].p_max = max;
			*list[i].p_min = min;
			*list[i].p_mean = (int)mean;
			*list[i].p_std_dev_plus = std_dev_plus;
			*list[i].p_std_dev_minus = std_dev_minus;
		}
	}
}

static int send_packed_info(write_func writer, pack_func packer, void *arg) {
	uint8_t data[BUF_SIZE];
	int len;
	
	len = (*packer)(data, arg);
	return (*writer)(data, len);
}

static void calc_peak_mean(const int list[], int cnt, int *p_max, int *p_min, double *p_mean) {
	int i;
	int max, min;
	long long sum;

	if (cnt <= 0) {
		return;
	}

	max = list[0];
	min = list[0];
	sum = list[0];

	for (i = 1; i < cnt; i++) {
		if (max < list[i]) {
			max = list[i];
		} else if (min > list[i]) {
			min = list[i];
		}

		sum += list[i];
	}

	if (p_max != NULL) {
		*p_max = max;
	}

	if (p_min != NULL) {
		*p_min = min;
	}

	if (p_mean != NULL) {
		*p_mean = (double)sum/cnt;
	}
}

static void calc_std_dev(const int list[], int cnt, double mean, double *p_plus, double *p_minus) {
	int i;
	double sqr_plus, sqr_minus;
	int cnt_plus, cnt_minus;
	double diff;

	if (cnt <= 0) {
		return;
	}

	sqr_plus = 0.0;
	sqr_minus = 0.0;
	cnt_plus = 0;
	cnt_minus = 0;

	for (i = 0; i < cnt; i++) {
		diff = list[i] - mean;

		if (diff > 0) {
			cnt_plus++;
			sqr_plus += diff * diff;
		} else if (diff < 0) {
			cnt_minus++;
			sqr_minus += diff * diff;
		}
	}

	if (p_plus != NULL) {
		*p_plus = (cnt_plus > 0) ? util_unsafe_sqrt(sqr_plus / cnt_plus, 2) : 0;
	}

	if (p_minus != NULL) {
		*p_minus = (cnt_minus > 0) ? util_unsafe_sqrt(sqr_minus / cnt_minus, 2) : 0;
	}
}
