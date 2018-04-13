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

#ifndef DC_LTE_DATA_SET_H
#define DC_LTE_DATA_SET_H

#include <stdint.h>
#include "data_lte.h"
#include "util.h"

enum {
	PREV,
	CURR
};

enum {
	REPORT_INTERVAL_INDICATOR_NONE,
	REPORT_INTERVAL_INDICATOR_RSSI,
	REPORT_INTERVAL_INDICATOR_RSRP,
	REPORT_INTERVAL_INDICATOR_RSRQ,
	REPORT_INTERVAL_INDICATOR_CQI
};

enum {
	MOD_QPSK,
	MOD_16QAM,
	MOD_64QAM
};

enum {
	STAT_CPU_USAGE,
	STAT_MEM_USAGE,
	STAT_TEMP,
	STAT_BATT_TEMP
};

struct ip_info {
	int len;
	char ip_addr[40];
	uint8_t addr[16];
};

struct ngbr_cell {
	int cell_id;
	int mcc;
	char mnc[4];
	int lac;
	int rssi;
	int rsrp;
	int rsrq;
};

// extern struct stat_tbl {
// 	int is_alert_needed;
// 	int lv[2];
// 	int th[4];
// 	int over_th_cnt[4];
// 	int win[WIN_SIZE + 1];
// 	int win_usage;
// 	int max;
// 	int min;
// 	int mean;
// } g_stat_tbl[4];

typedef struct {
	int report_interval;
	int routine_cnt;
	int activated_time;
	int idle_count;
	uint64_t uid;
	uint64_t freq_bitmap;
	struct ip_info ip_info[2];
	int net_entry_latency;
	int cell_id[2];
	int ul_max_bearer_speed;
	int dl_max_bearer_speed;

	int rssi_cnt;
	int rssi[MAX_REPORT_INTERVAL];
	int rssi_max;
	int rssi_min;
	int rssi_mean;
	double rssi_std_dev_plus;
	double rssi_std_dev_minus;

	int rsrp_cnt;
	int rsrp[MAX_REPORT_INTERVAL];
	int rsrp_max;
	int rsrp_min;
	int rsrp_mean;
	double rsrp_std_dev_plus;
	double rsrp_std_dev_minus;

	int rsrq_cnt;
	int rsrq[MAX_REPORT_INTERVAL];
	int rsrq_max;
	int rsrq_min;
	int rsrq_mean;
	double rsrq_std_dev_plus;
	double rsrq_std_dev_minus;

	int cqi_cnt;
	int cqi[MAX_REPORT_INTERVAL];
	int cqi_max;
	int cqi_min;
	int cqi_mean;
	double cqi_std_dev_plus;
	double cqi_std_dev_minus;

	int ul_earfcn;
	int dl_earfcn;
	int ch_bw;
	int mcc;
	char mnc[4];
	int lac;

	int handover_event_supportness;
	int handover_event_success_cnt;
	int handover_event_fail_cnt;

	int handover_latency_cnt;
	int handover_latency[MAX_REPORT_INTERVAL];
	int handover_latency_mean;

	int handover_detected_cnt;
	int handover_success_cnt[2];
	int handover_fail_cnt[2];
	int ul_mod_cnt[3];
	int dl_mod_cnt[3];
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

	uint64_t tx_packet_cnt[2];
	uint64_t rx_packet_cnt[2];
	uint64_t tx_packet_err_cnt[2];
	uint64_t rx_packet_err_cnt[2];
	uint64_t tx_frame_cnt[2];
	uint64_t rx_frame_cnt[2];
	uint64_t tx_frame_err_cnt[2];
	uint64_t rx_frame_err_cnt[2];
	int disconnect_reason;
	int ngbr_cell_cnt[2];
	struct ngbr_cell ngbr_cells[2][MAX_LTE_NGBR_CELL_CNT];
	int temp;
	int batt_temp;

	int cpu_usage_cnt;
	int cpu_usage[MAX_REPORT_INTERVAL];
	int cpu_usage_mean;

	int mem_usage_cnt;
	int mem_usage[MAX_REPORT_INTERVAL];
	int mem_usage_mean;

	int batt_lv;

	uint8_t scc_count;
	int scc_cell_id[MAX_LTE_SCC_CNT];
	int scc_ch_bw[MAX_LTE_SCC_CNT];
	double scc_rssi_std_dev_plus[MAX_LTE_SCC_CNT];
	double scc_rssi_std_dev_minus[MAX_LTE_SCC_CNT];

	int scc_rsrp_cnt;
	int scc_rsrp[MAX_LTE_SCC_CNT][MAX_REPORT_INTERVAL];
	int scc_rsrp_max[MAX_LTE_SCC_CNT];
	int scc_rsrp_min[MAX_LTE_SCC_CNT];
	int scc_rsrp_mean[MAX_LTE_SCC_CNT];
	double scc_rsrp_std_dev_plus[MAX_LTE_SCC_CNT];
	double scc_rsrp_std_dev_minus[MAX_LTE_SCC_CNT];

	int scc_rsrq_cnt;
	int scc_rsrq[MAX_LTE_SCC_CNT][MAX_REPORT_INTERVAL];
	int scc_rsrq_max[MAX_LTE_SCC_CNT];
	int scc_rsrq_min[MAX_LTE_SCC_CNT];
	int scc_rsrq_mean[MAX_LTE_SCC_CNT];
	double scc_rsrq_std_dev_plus[MAX_LTE_SCC_CNT];
	double scc_rsrq_std_dev_minus[MAX_LTE_SCC_CNT];

	int scc_dl_earfcn[MAX_LTE_SCC_CNT];
} lte_data_set;

extern lte_data_set* gp_lte_data_set;

typedef struct {
	int indicator;
	int idle_threshold;
	int threshold_cnt;
	int thresholds[MAX_LV_CNT - 1];
	int report_intervals[MAX_LV_CNT];
} lte_cfg;

extern lte_cfg* gp_lte_cfg;

int lte_pack_conn_history_info(uint8_t *data, void *arg);
int pack_dev_info(uint8_t *data, void *arg);
int pack_net_entry_info(uint8_t *data, void *arg);
int pack_alert_info(uint8_t *data, void *arg);
int pack_handover_info(uint8_t *data, void *arg);
int pack_ip_change_info(uint8_t *data, void *arg);
int pack_perf_info(uint8_t *data, void *arg);

#endif
