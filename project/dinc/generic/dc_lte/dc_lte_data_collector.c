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
#include <float.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "msg_format.h"
#include "msg_hal.h"
#include "dc_lte_data_collector.h"
#include "dc_lte_data_set.h"
#include "util.h"
#include "data_lte.h"
#include "data_dev.h"

#include "log.h"

#define BUF_SIZE	256

typedef int (*pack_func)(uint8_t *data, void *arg);

static void clct_alert_info(void);
static void clct_handover_info(void);
static void clct_ip_change_info(void);
static void clct_perf_info(void);

static void clct_dev_uid(void);
static void clct_dev_batt_temp(void);
static void clct_dev_temp(void);
static void clct_dev_cpu_usage(void);
static void clct_dev_mem_usage(void);
static void clct_dev_batt_lv(void);

static void clct_lte_supported_freq_band(void);
static void clct_lte_ip_address(void);
static void clct_lte_network_entry_latency(void);
static void clct_lte_cell_id(void);
static void clct_lte_rssi(void);
static void clct_lte_rsrp(void);
static void clct_lte_rsrq(void);
static void clct_lte_cqi(void);
static void clct_lte_ul_earfcn(void);
static void clct_lte_dl_earfcn(void);
static void clct_lte_channel_bw(void);
static void clct_lte_mcc(void);
static void clct_lte_mnc(void);
static void clct_lte_lac(void);
static void clct_lte_handover_latency(void);
static void clct_lte_handover_success_count(void);
static void clct_lte_handover_failure_count(void);
static void clct_lte_ul_mcs(void);
static void clct_lte_dl_mcs(void);
static void clct_lte_tx_power(void);
static int  clct_lte_tx_byte(void);
static int  clct_lte_rx_byte(void);
static void clct_lte_tx_packet_count(void);
static void clct_lte_rx_packet_count(void);
static void clct_lte_tx_packet_error_count(void);
static void clct_lte_rx_packet_error_count(void);
static void clct_lte_tx_frame_count(void);
static void clct_lte_rx_frame_count(void);
static void clct_lte_tx_frame_error_count(void);
static void clct_lte_rx_frame_error_count(void);
static void clct_lte_disconnect_reason(void);
static void clct_lte_neighboring_cell_info(void);
static void clct_lte_ul_bearer_flow_max_speed(void);
static void clct_lte_dl_bearer_flow_max_speed(void);
static void clct_lte_throughput_byte(void);

static void calc_perf_info(void);

static void clct_lte_scc_aggregated_count(void);
static void clct_lte_scc_cell_id(void);
static void clct_lte_scc_channel_bw(void);
static void clct_lte_scc_rsrp(void);
static void clct_lte_scc_rsrq(void);
static void clct_lte_scc_dl_earfcn(void);

static void update_stat_tbl(int type, int data);
static void update_report_interval(int rssi, int rsrp, int rsrq, int cqi);
static void lte_current_throughput_update(void);

static int send_packed_info(write_func writer, pack_func packer, void *arg);
static int send_round_trip_latency_req(write_func writer);

static void calc_peak_mean(const int list[], int cnt, int *p_max, int *p_min, double *p_mean);
static void calc_std_dev(const int list[], int cnt, double mean, double *p_plus, double *p_minus);

// uint32_t g_conn_time[5];
// uint32_t g_round_trip_latency;
extern uint32_t g_round_trip_latency;
// int g_report_interval = MAX_REPORT_INTERVAL;
extern int g_report_interval;
extern int64_t g_handover_start_usec;
extern uint64_t util_get_dev_uid(void);
extern double util_unsafe_sqrt(double val, int digits);

int clct_lte_conn_history_info(write_func writer) {
	int ret;
	int rssi;
	int rsrp;
	int rsrq;
	int cqi;
	
	clct_dev_uid();
	clct_lte_rssi();
	clct_lte_rsrp();
	clct_lte_rsrq();
	clct_lte_cqi();
	ret = send_packed_info(writer, &lte_pack_conn_history_info, NULL);
	rssi = (gp_lte_data_set->rssi_cnt > 0) ? gp_lte_data_set->rssi[0] : -1;
	rsrp = (gp_lte_data_set->rsrp_cnt > 0) ? gp_lte_data_set->rsrp[0] : -1;
	rsrq = (gp_lte_data_set->rsrq_cnt > 0) ? gp_lte_data_set->rsrq[0] : -1;
	cqi = (gp_lte_data_set->cqi_cnt > 0) ? gp_lte_data_set->cqi[0] : -1;
	update_report_interval(rssi, rsrp, rsrq, cqi);
	gp_lte_data_set->rssi_cnt = 0;
	gp_lte_data_set->rsrp_cnt = 0;
	gp_lte_data_set->rsrq_cnt = 0;
	gp_lte_data_set->cqi_cnt = 0;
	return ret;
}

int clct_lte_dev_info(write_func writer) {
	clct_lte_supported_freq_band();
	return send_packed_info(writer, &pack_dev_info, NULL);
}

int clct_lte_net_entry_info(write_func writer) {
	int ret;

	clct_lte_ip_address();
	clct_lte_cell_id();
	clct_lte_mcc();
	clct_lte_mnc();
	clct_lte_lac();
	clct_lte_network_entry_latency();
	clct_lte_disconnect_reason();
	clct_lte_neighboring_cell_info();
	clct_lte_ul_bearer_flow_max_speed();
	clct_lte_dl_bearer_flow_max_speed();
	clct_lte_handover_success_count();
	clct_lte_handover_failure_count();
	clct_lte_tx_byte();
	clct_lte_tx_packet_count();
	clct_lte_tx_packet_error_count();
	clct_lte_tx_frame_count();
	clct_lte_tx_frame_error_count();
	clct_lte_rx_byte();
	clct_lte_rx_packet_count();
	clct_lte_rx_packet_error_count();
	clct_lte_rx_frame_count();
	clct_lte_rx_frame_error_count();
	ret = send_packed_info(writer, &pack_net_entry_info, NULL);
	gp_lte_data_set->ul_rate_cnt = 0;
	gp_lte_data_set->dl_rate_cnt = 0;
	return ret;
}

int clct_lte_routine_info(write_func writer) {
	int i;

	clct_dev_batt_temp();
	clct_dev_temp();
	clct_dev_cpu_usage();
	clct_dev_mem_usage();
	clct_lte_ip_address();
	clct_lte_cell_id();
	clct_lte_rssi();
	clct_lte_rsrp();
	clct_lte_rsrq();
	clct_lte_cqi();
	clct_lte_ul_mcs();
	clct_lte_dl_mcs();
	clct_lte_throughput_byte();
	clct_lte_neighboring_cell_info();
	clct_lte_scc_aggregated_count();
	clct_lte_scc_rsrp();
	clct_lte_scc_rsrq();
	gp_lte_data_set->routine_cnt++;
	
	for (i = 0; i < ARRAY_SIZE(g_stat_tbl); i++) {
		if (g_stat_tbl[i].is_alert_needed) {
			clct_alert_info();
			send_packed_info(writer, &pack_alert_info, &i);
		}
	}

	if (gp_lte_data_set->cell_id[PREV] != gp_lte_data_set->cell_id[CURR]) {
		gp_lte_data_set->handover_detected_cnt++;
		clct_handover_info();
		send_packed_info(writer, &pack_handover_info, NULL);
	}
	
	if (strcmp(gp_lte_data_set->ip_info[PREV].ip_addr, gp_lte_data_set->ip_info[CURR].ip_addr) != 0) {
		clct_ip_change_info();
		send_packed_info(writer, &pack_ip_change_info, NULL);
	}

	if (gp_lte_data_set->idle_count > gp_lte_cfg->idle_threshold && g_report_interval < MAX_REPORT_INTERVAL)
    {
        g_report_interval++;
    }
    
	if (gp_lte_data_set->routine_cnt == g_report_interval - 5) {
		send_round_trip_latency_req(writer);
	} else if (gp_lte_data_set->routine_cnt == g_report_interval) {
		clct_perf_info();
		calc_perf_info();
		send_packed_info(writer, &pack_perf_info, NULL);
		update_report_interval(gp_lte_data_set->rssi_mean, gp_lte_data_set->rsrp_mean, gp_lte_data_set->rsrq_mean, gp_lte_data_set->cqi_mean);
		gp_lte_data_set->routine_cnt = 0;
		gp_lte_data_set->activated_time = 0;
		gp_lte_data_set->idle_count = 0;
		gp_lte_data_set->rssi_cnt = 0;
		gp_lte_data_set->rsrp_cnt = 0;
		gp_lte_data_set->rsrq_cnt = 0;
		gp_lte_data_set->cqi_cnt = 0;
		gp_lte_data_set->handover_event_success_cnt = 0;
		gp_lte_data_set->handover_event_fail_cnt = 0;
		gp_lte_data_set->handover_detected_cnt = 0;
		gp_lte_data_set->handover_latency_cnt = 0;
		memset(gp_lte_data_set->ul_mod_cnt, 0, sizeof(gp_lte_data_set->ul_mod_cnt));
		memset(gp_lte_data_set->dl_mod_cnt, 0, sizeof(gp_lte_data_set->dl_mod_cnt));
		gp_lte_data_set->ul_rate_cnt = 0;
		gp_lte_data_set->dl_rate_cnt = 0;
		gp_lte_data_set->cpu_usage_cnt = 0;
		gp_lte_data_set->mem_usage_cnt = 0;
		gp_lte_data_set->scc_count = 0;
		gp_lte_data_set->scc_rsrp_cnt = 0;
		gp_lte_data_set->scc_rsrq_cnt = 0;
		lte_current_throughput_update();
	}

	return 0;
}

// void set_conn_time(uint32_t conn_time[]) {
// 	memcpy(g_conn_time, conn_time, sizeof(g_conn_time));
// }

void set_lte_net_entry_latency(uint32_t latency) {
	gp_lte_data_set->net_entry_latency = latency;
}

// void set_round_trip_latency(uint32_t latency) {
// 	g_round_trip_latency = latency;
// }

void notify_lte_handover_start(int64_t time_usec) {
	gp_lte_data_set->handover_event_supportness = 1;
	g_handover_start_usec = time_usec;
}

void notify_lte_handover_end(int is_success, int64_t time_usec) {
	int handover_latency_msec;

	if (is_success) {
		gp_lte_data_set->handover_event_success_cnt++;
		handover_latency_msec = (int)(time_usec - g_handover_start_usec) / 1000;
		g_handover_start_usec = 0;

		if (handover_latency_msec > 65535) {
			handover_latency_msec = -1;
		}

		if (gp_lte_data_set->handover_latency_cnt < ARRAY_SIZE(gp_lte_data_set->handover_latency)) {
			gp_lte_data_set->handover_latency[gp_lte_data_set->handover_latency_cnt++] = handover_latency_msec;
		}
	} else {
		gp_lte_data_set->handover_event_fail_cnt++;
	}
}

static void clct_alert_info(void) {

}

static void clct_handover_info(void) {
	clct_lte_handover_latency();
}

static void clct_ip_change_info(void) {

}

static void clct_perf_info(void) {
	clct_dev_batt_lv();
	clct_lte_ul_earfcn();
	clct_lte_dl_earfcn();
	clct_lte_channel_bw();
	clct_lte_handover_success_count();
	clct_lte_handover_failure_count();
	clct_lte_tx_power();
	clct_lte_throughput_byte();
	clct_lte_tx_packet_count();
	clct_lte_tx_packet_error_count();
	clct_lte_tx_frame_count();
	clct_lte_tx_frame_error_count();
	clct_lte_rx_packet_count();
	clct_lte_rx_packet_error_count();
	clct_lte_rx_frame_count();
	clct_lte_rx_frame_error_count();
	clct_lte_scc_cell_id();
	clct_lte_scc_channel_bw();
	clct_lte_scc_dl_earfcn();
}

static void clct_dev_uid(void) {
	// char uid[DEV_UID_LEN + 1];

	// if (dev_get_uid(uid) < 0) {
	// 	gp_lte_data_set->uid = -1;
	// } else {
	// 	gp_lte_data_set->uid = (uint64_t)strtoull(uid, NULL, 16);
	// }
	gp_lte_data_set->uid = util_get_dev_uid();
}

static void clct_dev_batt_temp(void) {
	if (dev_get_batt_temp(&gp_lte_data_set->batt_temp) < 0) {
		gp_lte_data_set->batt_temp = 127;
	} else {
		update_stat_tbl(STAT_BATT_TEMP, gp_lte_data_set->batt_temp);
	}
}

static void clct_dev_temp(void) {
	if (dev_get_temp(&gp_lte_data_set->temp) < 0) {
		gp_lte_data_set->temp = 127;
	} else {
		update_stat_tbl(STAT_TEMP, gp_lte_data_set->temp);
	}
}

static void clct_dev_cpu_usage(void) {
	int cpu_usage;

	if (dev_get_cpu_usage(&cpu_usage) == 0) {
		gp_lte_data_set->cpu_usage[gp_lte_data_set->cpu_usage_cnt++] = cpu_usage;
		update_stat_tbl(STAT_CPU_USAGE, cpu_usage);
	}
}

static void clct_dev_mem_usage(void) {
	int mem_usage;

	if (dev_get_mem_usage(&mem_usage) == 0) {
		gp_lte_data_set->mem_usage[gp_lte_data_set->mem_usage_cnt++] = mem_usage;
		update_stat_tbl(STAT_MEM_USAGE, mem_usage);
	}
}

static void clct_dev_batt_lv(void) {
	if (dev_get_batt_lv(&gp_lte_data_set->batt_lv) < 0) {
		gp_lte_data_set->batt_lv = -1;
	}
}

static void clct_lte_supported_freq_band(void) {
	long long freq_bitmap = 0;

	if (lte_get_supported_freq_band(&freq_bitmap) < 0) {
		gp_lte_data_set->freq_bitmap = -1;
	} else {
		gp_lte_data_set->freq_bitmap = (uint64_t)freq_bitmap;
	}
}

static void clct_lte_ip_address(void) {
	char ip_addr[40] = "";

	memcpy(&gp_lte_data_set->ip_info[PREV], &gp_lte_data_set->ip_info[CURR], sizeof(struct ip_info));
	
	if (lte_get_ip_address(ip_addr) < 0) {
		memset(&gp_lte_data_set->ip_info[CURR], -1, sizeof(struct ip_info));
		*ip_addr = 0;
	} else {
		int addr_family;
		
		if (strchr(ip_addr, '.') != NULL) {
			addr_family = AF_INET;
			gp_lte_data_set->ip_info[CURR].len = sizeof(struct in_addr);
		} else {
			addr_family = AF_INET6;
			gp_lte_data_set->ip_info[CURR].len = sizeof(struct in6_addr);
		}

		inet_pton(addr_family, ip_addr, gp_lte_data_set->ip_info[CURR].addr);
	}

	strcpy(gp_lte_data_set->ip_info[CURR].ip_addr, ip_addr);
}

static void clct_lte_network_entry_latency(void) {
	if (gp_lte_data_set->net_entry_latency == -1) {
		if (lte_get_network_entry_latency(&gp_lte_data_set->net_entry_latency) < 0) {
			gp_lte_data_set->net_entry_latency = -1;
		}
	}
}

static void clct_lte_cell_id(void) {
	gp_lte_data_set->cell_id[PREV] = gp_lte_data_set->cell_id[CURR];

	if (lte_get_cell_id(&gp_lte_data_set->cell_id[CURR]) < 0) {
		gp_lte_data_set->cell_id[CURR] = -1;
	}
}

static void clct_lte_rssi(void) {
	int rssi;

	if (lte_get_rssi(&rssi) == 0) {
		gp_lte_data_set->rssi[gp_lte_data_set->rssi_cnt++] = rssi;
	}
}

static void clct_lte_rsrp(void) {
	int rsrp;

	if (lte_get_rsrp(&rsrp) == 0) {
		gp_lte_data_set->rsrp[gp_lte_data_set->rsrp_cnt++] = rsrp;
	}
}

static void clct_lte_rsrq(void) {
	float rsrq;

	if (lte_get_rsrq(&rsrq) == 0) {
		gp_lte_data_set->rsrq[gp_lte_data_set->rsrq_cnt++] = (int)rsrq;
	}
}

static void clct_lte_cqi(void) {
	int cqi;

	if (lte_get_cqi(&cqi) == 0) {
		gp_lte_data_set->cqi[gp_lte_data_set->cqi_cnt++] = cqi;
	}
}

static void clct_lte_ul_earfcn(void) {
	if (lte_get_ul_earfcn(&gp_lte_data_set->ul_earfcn) < 0) {
		gp_lte_data_set->ul_earfcn = -1;
	}
}

static void clct_lte_dl_earfcn(void) {
	if (lte_get_dl_earfcn(&gp_lte_data_set->dl_earfcn) < 0) {
		gp_lte_data_set->dl_earfcn = -1;
	}
}

static void clct_lte_channel_bw(void) {
	if (lte_get_channel_bw(&gp_lte_data_set->ch_bw) < 0) {
		gp_lte_data_set->ch_bw = -1;
	}
}

static void clct_lte_mcc(void) {
	if (lte_get_mcc(&gp_lte_data_set->mcc) < 0) {
		gp_lte_data_set->mcc = -1;
	}
}

static void clct_lte_mnc(void) {
	memset(gp_lte_data_set->mnc, 0, sizeof(gp_lte_data_set->mnc));
	lte_get_mnc(gp_lte_data_set->mnc);
}

static void clct_lte_lac(void) {
	if (lte_get_lac(&gp_lte_data_set->lac) < 0) {
		gp_lte_data_set->lac = -1;
	}
}

static void clct_lte_handover_latency(void) {
	int latency;

	if (!gp_lte_data_set->handover_event_supportness) {
		if (lte_get_handover_latency(&latency) == 0) {
			gp_lte_data_set->handover_latency[gp_lte_data_set->handover_latency_cnt++] = latency;
		}
	}
}

static void clct_lte_handover_success_count(void) {
	if (!gp_lte_data_set->handover_event_supportness) {
		gp_lte_data_set->handover_success_cnt[PREV] = gp_lte_data_set->handover_success_cnt[CURR];
		
		if (lte_get_handover_success_count(&gp_lte_data_set->handover_success_cnt[CURR]) < 0) {
			gp_lte_data_set->handover_success_cnt[CURR] = -1;
		}
	}
}

static void clct_lte_handover_failure_count(void) {
	if (!gp_lte_data_set->handover_event_supportness) {
		gp_lte_data_set->handover_fail_cnt[PREV] = gp_lte_data_set->handover_fail_cnt[CURR];
	
		if (lte_get_handover_failure_count(&gp_lte_data_set->handover_fail_cnt[CURR]) < 0) {
			gp_lte_data_set->handover_fail_cnt[CURR] = -1;
		}
	}
}

static void clct_lte_ul_mcs(void) {
	int mod;

	if (lte_get_ul_mcs(&mod) == 0) {
		switch (mod) {
		case MCS_TYPE_QPSK:
			gp_lte_data_set->ul_mod_cnt[MOD_QPSK]++;
			break;
		
		case MCS_TYPE_16QAM:
			gp_lte_data_set->ul_mod_cnt[MOD_16QAM]++;
			break;
		
		case MCS_TYPE_64QAM:
			gp_lte_data_set->ul_mod_cnt[MOD_64QAM]++;
			break;
		}
	}
}

static void clct_lte_dl_mcs(void) {
	int mod;

	if (lte_get_dl_mcs(&mod) == 0) {
		switch (mod) {
		case MCS_TYPE_QPSK:
			gp_lte_data_set->dl_mod_cnt[MOD_QPSK]++;
			break;
		
		case MCS_TYPE_16QAM:
			gp_lte_data_set->dl_mod_cnt[MOD_16QAM]++;
			break;
		
		case MCS_TYPE_64QAM:
			gp_lte_data_set->dl_mod_cnt[MOD_64QAM]++;
			break;
		}
	}
}

static void clct_lte_throughput_byte(void) 
{
	int tx_byte = clct_lte_tx_byte();
	int rx_byte = clct_lte_rx_byte();

	if (tx_byte != 0 || rx_byte != 0)
	{
		gp_lte_data_set->activated_time++;
		gp_lte_data_set->idle_count = 0;
	} 
	else
	{
		gp_lte_data_set->idle_count++;
	}
}

static void lte_current_throughput_update(void) 
{
	unsigned long long byte = 0;

	// reset previous throughput
	gp_lte_data_set->tx_byte[PREV] = -1;
	gp_lte_data_set->rx_byte[PREV] = -1;

	if (lte_get_tx_byte(&byte) < 0) {
		gp_lte_data_set->tx_byte[CURR] = -1;
	} else {
		gp_lte_data_set->tx_byte[CURR] = (uint64_t)byte;
	}
	
	if (lte_get_rx_byte(&byte) < 0) {
		gp_lte_data_set->rx_byte[CURR] = -1;
	} else {
		gp_lte_data_set->rx_byte[CURR] = (uint64_t)byte;
	}
}

static void clct_lte_tx_power(void) {
	if (lte_get_tx_power(&gp_lte_data_set->tx_power) < 0) {
		gp_lte_data_set->tx_power = 127;
	}
}

static int clct_lte_tx_byte(void) {
	unsigned long long byte = 0;

	gp_lte_data_set->tx_byte[PREV] = gp_lte_data_set->tx_byte[CURR];
	
	if (lte_get_tx_byte(&byte) < 0) {
		gp_lte_data_set->tx_byte[CURR] = -1;
	} else {
		gp_lte_data_set->tx_byte[CURR] = (uint64_t)byte;

		if (gp_lte_data_set->tx_byte[PREV] != -1) {
			int index = gp_lte_data_set->ul_rate_cnt;
			gp_lte_data_set->ul_rate[gp_lte_data_set->ul_rate_cnt++] = (int)(gp_lte_data_set->tx_byte[CURR] - gp_lte_data_set->tx_byte[PREV]);

			return gp_lte_data_set->ul_rate[index];
		}
	}
	return 0;
}

static void clct_lte_tx_packet_count(void) {
	unsigned long long count;

	gp_lte_data_set->tx_packet_cnt[PREV] = gp_lte_data_set->tx_packet_cnt[CURR];
	
	if (lte_get_tx_packet_count(&count) < 0) {
		gp_lte_data_set->tx_packet_cnt[CURR] = -1;
	} else {
		gp_lte_data_set->tx_packet_cnt[CURR] = (uint64_t)count;
	}
}

static void clct_lte_tx_packet_error_count(void) {
	unsigned long long count;

	gp_lte_data_set->tx_packet_err_cnt[PREV] = gp_lte_data_set->tx_packet_err_cnt[CURR];
	
	if (lte_get_tx_packet_error_count(&count) < 0) {
		gp_lte_data_set->tx_packet_err_cnt[CURR] = -1;
	} else {
		gp_lte_data_set->tx_packet_err_cnt[CURR] = (uint64_t)count;
	}
}

static void clct_lte_tx_frame_count(void) {
	unsigned long long count;

	gp_lte_data_set->tx_frame_cnt[PREV] = gp_lte_data_set->tx_frame_cnt[CURR];
	
	if (lte_get_tx_frame_count(&count) < 0) {
		gp_lte_data_set->tx_frame_cnt[CURR] = -1;
	} else {
		gp_lte_data_set->tx_frame_cnt[CURR] = (uint64_t)count;
	}
}

static void clct_lte_tx_frame_error_count(void) {
	unsigned long long count;

	gp_lte_data_set->tx_frame_err_cnt[PREV] = gp_lte_data_set->tx_frame_err_cnt[CURR];
	
	if (lte_get_tx_frame_error_count(&count) < 0) {
		gp_lte_data_set->tx_frame_err_cnt[CURR] = -1;
	} else {
		gp_lte_data_set->tx_frame_cnt[CURR] = (uint64_t)count;
	}
}

static int clct_lte_rx_byte(void) {
	unsigned long long byte = 0;

	gp_lte_data_set->rx_byte[PREV] = gp_lte_data_set->rx_byte[CURR];
	
	if (lte_get_rx_byte(&byte) < 0) {
		gp_lte_data_set->rx_byte[CURR] = -1;
	} else {
		gp_lte_data_set->rx_byte[CURR] = (uint64_t)byte;

		if (gp_lte_data_set->rx_byte[PREV] != -1) {
			int index = gp_lte_data_set->dl_rate_cnt;
			gp_lte_data_set->dl_rate[gp_lte_data_set->dl_rate_cnt++] = (int)(gp_lte_data_set->rx_byte[CURR] - gp_lte_data_set->rx_byte[PREV]);

			return gp_lte_data_set->dl_rate[index];
		}
	}
	return 0;
}

static void clct_lte_rx_packet_count(void) {
	unsigned long long count;

	gp_lte_data_set->rx_packet_cnt[PREV] = gp_lte_data_set->rx_packet_cnt[CURR];
	
	if (lte_get_rx_packet_count(&count) < 0) {
		gp_lte_data_set->rx_packet_cnt[CURR] = -1;
	} else {
		gp_lte_data_set->rx_packet_cnt[CURR] = (uint64_t)count;
	}
}

static void clct_lte_rx_packet_error_count(void) {
	unsigned long long count;

	gp_lte_data_set->rx_packet_err_cnt[PREV] = gp_lte_data_set->rx_packet_err_cnt[CURR];
	
	if (lte_get_rx_packet_error_count(&count) < 0) {
		gp_lte_data_set->rx_packet_err_cnt[CURR] = -1;
	} else {
		gp_lte_data_set->rx_packet_err_cnt[CURR] = (uint64_t)count;
	}
}

static void clct_lte_rx_frame_count(void) {
	unsigned long long count;

	gp_lte_data_set->rx_frame_cnt[PREV] = gp_lte_data_set->rx_frame_cnt[CURR];
	
	if (lte_get_rx_frame_count(&count) < 0) {
		gp_lte_data_set->rx_frame_cnt[CURR] = -1;
	} else {
		gp_lte_data_set->rx_frame_cnt[CURR] = (uint64_t)count;
	}
}

static void clct_lte_rx_frame_error_count(void) {
	unsigned long long count;

	gp_lte_data_set->rx_frame_err_cnt[PREV] = gp_lte_data_set->rx_frame_err_cnt[CURR];
	
	if (lte_get_rx_frame_error_count(&count) < 0) {
		gp_lte_data_set->rx_frame_err_cnt[CURR] = -1;
	} else {
		gp_lte_data_set->rx_frame_cnt[CURR] = (uint64_t)count;
	}
}

static void clct_lte_disconnect_reason(void) {
	if (lte_get_disconnect_reason(&gp_lte_data_set->disconnect_reason) < 0) {
		gp_lte_data_set->disconnect_reason = -1;
	}
}

static void clct_lte_neighboring_cell_info(void) {
	lte_cell_info list[MAX_LTE_NGBR_CELL_CNT];
	int i;

	gp_lte_data_set->ngbr_cell_cnt[PREV] = gp_lte_data_set->ngbr_cell_cnt[CURR];
	memcpy(gp_lte_data_set->ngbr_cells[PREV], gp_lte_data_set->ngbr_cells[CURR], MAX_LTE_NGBR_CELL_CNT * sizeof(lte_cell_info));

	for (i = 0; i < MAX_LTE_NGBR_CELL_CNT; i++) {
		list[i].cell_id = -1;
		list[i].mcc = -1;
		memset(list[i].mnc, 0, 4);
		list[i].lac = -1;
		list[i].rssi = 127;
		list[i].rsrp = 127;
		list[i].rsrq = FLT_MAX;
	}

	if (lte_get_neighboring_cell_info(&gp_lte_data_set->ngbr_cell_cnt[CURR], list) < 0) {
		gp_lte_data_set->ngbr_cell_cnt[CURR] = -1;
	} else {
		for (i = 0; i < gp_lte_data_set->ngbr_cell_cnt[CURR]; i++) {
			gp_lte_data_set->ngbr_cells[CURR][i].cell_id = list[i].cell_id;
			gp_lte_data_set->ngbr_cells[CURR][i].mcc = list[i].mcc;
			memcpy(gp_lte_data_set->ngbr_cells[CURR][i].mnc, list[i].mnc, 4);
			gp_lte_data_set->ngbr_cells[CURR][i].lac = list[i].lac;
			gp_lte_data_set->ngbr_cells[CURR][i].rssi = (int)list[i].rssi;
			gp_lte_data_set->ngbr_cells[CURR][i].rsrp = (int)list[i].rsrp;

			if (list[i].rsrq == FLT_MAX) {
				gp_lte_data_set->ngbr_cells[CURR][i].rsrq = 127;
			}
		}
	}
}

static void clct_lte_ul_bearer_flow_max_speed(void) {
	if (lte_get_ul_bearer_flow_max_speed(&gp_lte_data_set->ul_max_bearer_speed) < 0) {
		gp_lte_data_set->ul_max_bearer_speed = -1;
	}
}

static void clct_lte_dl_bearer_flow_max_speed(void) {
	if (lte_get_dl_bearer_flow_max_speed(&gp_lte_data_set->dl_max_bearer_speed) < 0) {
		gp_lte_data_set->dl_max_bearer_speed = -1;
	}
}

static void calc_perf_info() {
	int i;
	int max, min;
	double mean;
	double std_dev_minus, std_dev_plus;

#define MAKE_LIST(s, m, i)	{s->m##_cnt, s->m, &s->m##_max, &s->m##_min, &s->m##_mean, &s->m##_std_dev_plus, &s->m##_std_dev_minus, i}

	{
		struct {
			int cnt;
			int *data;
			int *p_max;
			int *p_min;
			int *p_mean;
			double *p_std_dev_plus;
			double *p_std_dev_minus;
			int invalid_value;
		} list[] = {
			MAKE_LIST(gp_lte_data_set, rssi, 127),
			MAKE_LIST(gp_lte_data_set, rsrp, 127),
			MAKE_LIST(gp_lte_data_set, rsrq, 127),
			MAKE_LIST(gp_lte_data_set, cqi, -1),
			MAKE_LIST(gp_lte_data_set, ul_rate, -1),
			MAKE_LIST(gp_lte_data_set, dl_rate, -1)
		};
		
		for (i = 0; i < ARRAY_SIZE(list); i++) {
			max = list[i].invalid_value;
			min = list[i].invalid_value;
			mean = list[i].invalid_value;
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

#define MAKE_LIST2(s, m)	{s->m##_cnt, s->m, &s->m##_mean}

	{
		struct {
			int cnt;
			int *data;
			int *p_mean;
		} list[] = {
			MAKE_LIST2(gp_lte_data_set, handover_latency),
			MAKE_LIST2(gp_lte_data_set, cpu_usage),
			MAKE_LIST2(gp_lte_data_set, mem_usage)
		};

		for (i = 0; i < ARRAY_SIZE(list); i++) {
			mean = -1.0;
			calc_peak_mean(list[i].data, list[i].cnt, NULL, NULL, &mean);
			*list[i].p_mean = (int)mean;
		}
	}

	for (i = 0; i < gp_lte_data_set->scc_count; i++)
	{
		std_dev_plus = -1.0;
		std_dev_minus = -1.0;
		calc_peak_mean(gp_lte_data_set->scc_rsrp[i], gp_lte_data_set->scc_rsrp_cnt, &gp_lte_data_set->scc_rsrp_max[i], &gp_lte_data_set->scc_rsrp_min[i], &mean);
		calc_std_dev(gp_lte_data_set->scc_rsrp[i], gp_lte_data_set->scc_rsrp_cnt, mean, &std_dev_plus, &std_dev_minus);
		gp_lte_data_set->scc_rsrp_mean[i] = (int) mean;
		gp_lte_data_set->scc_rsrp_std_dev_plus[i] = std_dev_plus;
		gp_lte_data_set->scc_rsrp_std_dev_minus[i] = std_dev_minus;
	}

	for (i = 0; i < gp_lte_data_set->scc_count; i++)
	{
		std_dev_plus = -1.0;
		std_dev_minus = -1.0;
		calc_peak_mean(gp_lte_data_set->scc_rsrq[i], gp_lte_data_set->scc_rsrq_cnt, &gp_lte_data_set->scc_rsrq_max[i], &gp_lte_data_set->scc_rsrq_min[i], &mean);
		calc_std_dev(gp_lte_data_set->scc_rsrq[i], gp_lte_data_set->scc_rsrq_cnt, mean, &std_dev_plus, &std_dev_minus);
		gp_lte_data_set->scc_rsrq_mean[i] = (int) mean;
		gp_lte_data_set->scc_rsrq_std_dev_plus[i] = std_dev_plus;
		gp_lte_data_set->scc_rsrq_std_dev_minus[i] = std_dev_minus;
	}
}

static void clct_lte_scc_aggregated_count(void) {
	if (lte_get_scc_aggregated_count(&gp_lte_data_set->scc_count) < 0) {
		gp_lte_data_set->scc_count = 0;
	}
}

static void clct_lte_scc_cell_id(void) {
	int i = 0;

	if (lte_get_scc_cell_id(gp_lte_data_set->scc_cell_id) < 0) {
		
		for (i = 0; i < MAX_LTE_SCC_CNT; i++)
		{
			gp_lte_data_set->scc_cell_id[i] = -1;
		}
	}
}

static void clct_lte_scc_channel_bw(void) {
	int i = 0;

	if (lte_get_scc_channel_bw(gp_lte_data_set->scc_ch_bw) < 0) {
		for (i = 0; i < MAX_LTE_SCC_CNT; i++)
		{
			gp_lte_data_set->scc_ch_bw[i] = -1;
		}
	}
}

static void clct_lte_scc_rsrp(void) {
	int rsrp[MAX_LTE_SCC_CNT];

	if (lte_get_scc_rsrp(rsrp) == 0) 
	{
		int i;
		for (i = 0; i < gp_lte_data_set->scc_count; i++)
		{
			gp_lte_data_set->scc_rsrp[i][gp_lte_data_set->scc_rsrp_cnt] = rsrp[i];
		}
		gp_lte_data_set->scc_rsrp_cnt++;
	}
}

static void clct_lte_scc_rsrq(void) {
	float rsrq[MAX_LTE_SCC_CNT];

	if (lte_get_scc_rsrq(rsrq) == 0) 
	{
		int i;
		for (i = 0; i < gp_lte_data_set->scc_count; i++)
		{
			gp_lte_data_set->scc_rsrq[i][gp_lte_data_set->scc_rsrq_cnt] = (int)rsrq[i];
		}
		gp_lte_data_set->scc_rsrq_cnt++;
	}
}

static void clct_lte_scc_dl_earfcn(void) {
	int i = 0;
	if (lte_get_scc_dl_earfcn(gp_lte_data_set->scc_dl_earfcn) < 0) 
	{
		for (i = 0; i < MAX_LTE_SCC_CNT; i++)
		{
			gp_lte_data_set->scc_dl_earfcn[i] = -1;
		}
	}
}

static void update_stat_tbl(int type, int data) {
	int data_out;
	int lv;
	int i;

	memmove(g_stat_tbl[type].win + 1, g_stat_tbl[type].win, sizeof(int) * WIN_SIZE);
	data_out = g_stat_tbl[type].win[WIN_SIZE];
	g_stat_tbl[type].win[0] = data;

	if (g_stat_tbl[type].win_usage <= WIN_SIZE) {
		g_stat_tbl[type].win_usage++;
	}

	g_stat_tbl[type].is_alert_needed = 0;
	lv = -1;

	for (i = ARRAY_SIZE(g_stat_tbl[type].th) - 1; i >= 0; i--) {
		if (g_stat_tbl[type].win_usage > WIN_SIZE && data_out > g_stat_tbl[type].th[i]) {
			g_stat_tbl[type].over_th_cnt[i]--;
		}

		if (data > g_stat_tbl[type].th[i]) {
			g_stat_tbl[type].over_th_cnt[i]++;
		}

		if (lv == -1 && g_stat_tbl[type].over_th_cnt[i] >= ALERT_TH) {
			lv = i;
		}
	}
	
 	{
 		int cnt = g_stat_tbl[type].win_usage;
 		double mean;

 		if (cnt > WIN_SIZE) {
 			cnt = WIN_SIZE;
 		}

		calc_peak_mean(g_stat_tbl[type].win, cnt, &g_stat_tbl[type].max, &g_stat_tbl[type].min, &mean);
		g_stat_tbl[type].mean = (int)mean;
 	}

 	g_stat_tbl[type].lv[PREV] = g_stat_tbl[type].lv[CURR];

	if (lv == -1) { // none of the thresholds are reached
		g_stat_tbl[type].lv[CURR] = -1;
	} else if (lv > g_stat_tbl[type].lv[PREV]) {
		g_stat_tbl[type].is_alert_needed = 1;
		g_stat_tbl[type].lv[CURR] = lv;
	}
}

static void update_report_interval(int rssi, int rsrp, int rsrq, int cqi) {
	int i;
	int indicator;

	// assign the maximum value in order to prevent unexpected error
	g_report_interval = gp_lte_cfg->report_intervals[gp_lte_cfg->threshold_cnt];

	switch (gp_lte_cfg->indicator) {
	case REPORT_INTERVAL_INDICATOR_RSSI:
		indicator = rssi;
		break;

	case REPORT_INTERVAL_INDICATOR_RSRP:
		indicator = rsrp;
		break;

	case REPORT_INTERVAL_INDICATOR_RSRQ:
		indicator = rsrq;
		break;

	case REPORT_INTERVAL_INDICATOR_CQI:
		indicator = cqi;
		break;

	default:
		return;
	}

	if (indicator == -1) {
		return;
	}

	for (i = 0; i < gp_lte_cfg->threshold_cnt; i++) {
		if (indicator <= gp_lte_cfg->thresholds[i]) {
			g_report_interval = gp_lte_cfg->report_intervals[i];
			break;
		}
	}

	if (i == gp_lte_cfg->threshold_cnt) {
		g_report_interval = gp_lte_cfg->report_intervals[i];
	}
}

static int send_packed_info(write_func writer, pack_func packer, void *arg) {
	uint8_t data[BUF_SIZE];
	int len;
	
	len = (*packer)(data, arg);
	return (*writer)(data, len);
}

static int send_round_trip_latency_req(write_func writer) {
	struct {
		uint32_t type;
		uint32_t dc_id;
	} data;

	data.type = htonl(IPC_MSG_GET_LATENCY);
	data.dc_id = htonl(IPC_DC_LTE);
	return (*writer)(&data, sizeof(data));
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
