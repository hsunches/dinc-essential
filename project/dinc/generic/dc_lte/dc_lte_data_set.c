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

#include <stdint.h>
#include <float.h>
#include "dc_lte_data_set.h"
#include "msg_format.h"
#include "util.h"

lte_data_set* gp_lte_data_set;

lte_cfg* gp_lte_cfg;

extern uint32_t g_conn_time[5];
extern uint32_t g_round_trip_latency;
extern int g_report_interval;

int lte_pack_conn_history_info(uint8_t *data, void *arg) {
	uint8_t *p;

	p = data;
	PUT_INT(p, util_htonl(IPC_MSG_SEND_CONN_HISTORY_INFO), 32);
	PUT_INT(p, util_htonl(IPC_DC_LTE), 32);
	PUT_INT(p, DINP_ROLE_LTE, 8);
	PUT_INT(p, DINP_MSG_DC_CONN_HISTORY_INFO, 8);

	if (gp_lte_data_set->rssi_cnt == 0) {
		PUT_INT(p, 127, 8);
	} else {
		PUT_INT(p, gp_lte_data_set->rssi[0], 8);
	}

	if (gp_lte_data_set->rsrp_cnt == 0) {
		PUT_INT(p, 127, 8);
	} else {
		PUT_INT(p, gp_lte_data_set->rsrp[0], 8);
	}
	
	if (gp_lte_data_set->rsrq_cnt == 0) {
		PUT_INT(p, 127, 8);
	} else {
		PUT_INT(p, gp_lte_data_set->rsrq[0], 8);
	}

	return p - data;
}

int pack_dev_info(uint8_t *data, void *arg) {
	uint8_t *p;
	uint64_t freq_bitmap_be;

	p = data;
	PUT_INT(p, util_htonl(IPC_MSG_SEND_REPORT), 32);
	PUT_INT(p, util_htonl(IPC_DC_LTE), 32);
	PUT_INT(p, DINP_ROLE_LTE | DINP_HDR_MASK_UID, 8);
	PUT_INT(p, DINP_MSG_DC_DEVICE_INFO, 8);
	PUT_INT(p, util_htonll(gp_lte_data_set->uid), 64);
	freq_bitmap_be = util_htonll(gp_lte_data_set->freq_bitmap);
	PUT_MEM(p, ((uint8_t *)&freq_bitmap_be) + 2, 6);
	return p - data;
}

int pack_net_entry_info(uint8_t *data, void *arg) {
	uint8_t *p;
	int role;
	int i;
	
	p = data;
	PUT_INT(p, util_htonl(IPC_MSG_SEND_REPORT), 32);
	PUT_INT(p, util_htonl(IPC_DC_LTE), 32);
	role = DINP_ROLE_LTE | DINP_HDR_MASK_UID;
	
	PUT_INT(p, role, 8);
	PUT_INT(p, DINP_MSG_DC_NETWORK_ENTRY_INFO, 8);
	PUT_INT(p, util_htonll(gp_lte_data_set->uid), 64);
	
	PUT_INT(p, gp_lte_data_set->ip_info[CURR].len, 8);
	
	if (gp_lte_data_set->ip_info[CURR].len != -1) {
		PUT_MEM(p, gp_lte_data_set->ip_info[CURR].addr, gp_lte_data_set->ip_info[CURR].len);
	}
	
	PUT_INT(p, util_htonl((uint32_t)gp_lte_data_set->cell_id[CURR]), 32);
	PUT_INT(p, util_htons((uint16_t)gp_lte_data_set->mcc), 16);
	PUT_STR(p, (char *)gp_lte_data_set->mnc);
	PUT_INT(p, util_htons((uint16_t)gp_lte_data_set->lac), 16);
	PUT_INT(p, util_htons((uint16_t)gp_lte_data_set->net_entry_latency), 16);
	PUT_MEM(p, g_conn_time, sizeof(g_conn_time));
	PUT_INT(p, gp_lte_data_set->disconnect_reason, 8);
	PUT_INT(p, gp_lte_data_set->ngbr_cell_cnt[CURR], 8);
	
	for (i = 0; i < gp_lte_data_set->ngbr_cell_cnt[CURR]; i++) {
		PUT_INT(p, util_htonl((uint32_t)gp_lte_data_set->ngbr_cells[CURR][i].cell_id), 32);
		PUT_INT(p, util_htons((uint16_t)gp_lte_data_set->ngbr_cells[CURR][i].mcc), 16);
		PUT_STR(p, (char *)gp_lte_data_set->ngbr_cells[CURR][i].mnc);
		PUT_INT(p, util_htons((uint16_t)gp_lte_data_set->ngbr_cells[CURR][i].lac), 16);
		PUT_INT(p, gp_lte_data_set->ngbr_cells[CURR][i].rssi, 8);
		PUT_INT(p, gp_lte_data_set->ngbr_cells[CURR][i].rsrp, 8);
		PUT_INT(p, gp_lte_data_set->ngbr_cells[CURR][i].rsrq, 8);
	}
	
	PUT_INT(p, util_htons((uint16_t)gp_lte_data_set->ul_max_bearer_speed), 16);
	PUT_INT(p, util_htons((uint16_t)gp_lte_data_set->dl_max_bearer_speed), 16);
	return p - data;
}

int pack_alert_info(uint8_t *data, void *arg) {
	uint8_t *p;
	int role;

	p = data;
	PUT_INT(p, util_htonl(IPC_MSG_SEND_REPORT), 32);
	PUT_INT(p, util_htonl(IPC_DC_LTE), 32);
	role = DINP_ROLE_LTE | DINP_HDR_MASK_UID;
	
	PUT_INT(p, role, 8);
	PUT_INT(p, DINP_MSG_DC_ALERT_INFO, 8);
	PUT_INT(p, util_htonll(gp_lte_data_set->uid), 64);

	{
		int stat_index;
		int stat_and_lv;

		stat_index = *(int *)arg;
		stat_and_lv = stat_index << 6;
		stat_and_lv |= (g_stat_tbl[stat_index].lv[PREV] + 1) << 3;
		stat_and_lv |= (g_stat_tbl[stat_index].lv[CURR] + 1);
		PUT_INT(p, stat_and_lv, 8);
	}
	
	PUT_INT(p, g_stat_tbl[STAT_CPU_USAGE].max, 8);
	PUT_INT(p, g_stat_tbl[STAT_CPU_USAGE].min, 8);
	PUT_INT(p, g_stat_tbl[STAT_CPU_USAGE].mean, 8);
	PUT_INT(p, g_stat_tbl[STAT_MEM_USAGE].max, 8);
	PUT_INT(p, g_stat_tbl[STAT_MEM_USAGE].min, 8);
	PUT_INT(p, g_stat_tbl[STAT_MEM_USAGE].mean, 8);
	PUT_INT(p, gp_lte_data_set->temp, 8);
	PUT_INT(p, gp_lte_data_set->batt_temp, 8);
	return p - data;
}

int pack_handover_info(uint8_t *data, void *arg) {
	uint8_t *p;
	int role;
	int i;
	
	p = data;
	PUT_INT(p, util_htonl(IPC_MSG_SEND_REPORT), 32);
	PUT_INT(p, util_htonl(IPC_DC_LTE), 32);
	role = DINP_ROLE_LTE | DINP_HDR_MASK_UID;
	
	PUT_INT(p, role, 8);
	PUT_INT(p, DINP_MSG_DC_HANDOVER_INFO, 8);
	PUT_INT(p, util_htonll(gp_lte_data_set->uid), 64);
	
	PUT_INT(p, util_htonl((uint32_t)gp_lte_data_set->cell_id[PREV]), 32);
	
	if (gp_lte_data_set->rssi_cnt <= 1) {
	    PUT_INT(p, 127, 8);
	} else {
	    PUT_INT(p, gp_lte_data_set->rssi[gp_lte_data_set->rssi_cnt - 2], 8);
	}
	
	PUT_INT(p, gp_lte_data_set->ngbr_cell_cnt[PREV], 8);
	
	for (i = 0; i < gp_lte_data_set->ngbr_cell_cnt[PREV]; i++) {
		PUT_INT(p, util_htons((uint32_t)gp_lte_data_set->ngbr_cells[PREV][i].cell_id), 32);
		PUT_INT(p, util_htons((uint16_t)gp_lte_data_set->ngbr_cells[PREV][i].mcc), 16);
		PUT_STR(p, (char *)gp_lte_data_set->ngbr_cells[PREV][i].mnc);
		PUT_INT(p, util_htons((uint16_t)gp_lte_data_set->ngbr_cells[PREV][i].lac), 16);
		PUT_INT(p, gp_lte_data_set->ngbr_cells[PREV][i].rssi, 8);
		PUT_INT(p, gp_lte_data_set->ngbr_cells[PREV][i].rsrp, 8);
		PUT_INT(p, gp_lte_data_set->ngbr_cells[PREV][i].rsrq, 8);
	}
	
	PUT_INT(p, util_htonl((uint32_t)gp_lte_data_set->cell_id[CURR]), 32);
	return p - data;
}

int pack_ip_change_info(uint8_t *data, void *arg) {
	uint8_t *p;
	int role;
	int i;
	
	p = data;
	PUT_INT(p, util_htonl(IPC_MSG_SEND_REPORT), 32);
	PUT_INT(p, util_htonl(IPC_DC_LTE), 32);
	role = DINP_ROLE_LTE | DINP_HDR_MASK_UID;
		
	PUT_INT(p, role, 8);
	PUT_INT(p, DINP_MSG_DC_IP_CHANGING_INFO, 8);
	PUT_INT(p, util_htonll(gp_lte_data_set->uid), 64);
	
	for (i = PREV; i <= CURR; i++) {
		PUT_INT(p, gp_lte_data_set->ip_info[i].len, 8);
	
		if (gp_lte_data_set->ip_info[i].len != -1) {
			PUT_MEM(p, gp_lte_data_set->ip_info[i].addr, gp_lte_data_set->ip_info[i].len);
		}
	}
	
	return p - data;
}

int pack_perf_info(uint8_t *data, void *arg) {
	uint8_t *p;
	int role;
	int i;
	
	p = data;
	PUT_INT(p, util_htonl(IPC_MSG_SEND_REPORT), 32);
	PUT_INT(p, util_htonl(IPC_DC_LTE), 32);
	role = DINP_ROLE_LTE | DINP_HDR_MASK_UID;
	
	PUT_INT(p, role, 8);
	PUT_INT(p, DINP_MSG_DC_PERFORMANCE_INFO, 8);
	PUT_INT(p, util_htonll(gp_lte_data_set->uid), 64);

	PUT_INT(p, gp_lte_data_set->ip_info[CURR].len, 8);

	if (gp_lte_data_set->ip_info[CURR].len != -1) {
		PUT_MEM(p, gp_lte_data_set->ip_info[CURR].addr, gp_lte_data_set->ip_info[CURR].len);
	}
	
	PUT_INT(p, util_htonl((uint32_t)gp_lte_data_set->cell_id[CURR]), 32);
	PUT_INT(p, util_htonl((uint32_t)gp_lte_data_set->ul_earfcn), 32);
	PUT_INT(p, util_htonl((uint32_t)gp_lte_data_set->dl_earfcn), 32);
	PUT_INT(p, gp_lte_data_set->ch_bw, 8);

#define MAKE_LIST(s, m)	{s->m##_max, s->m##_min, s->m##_mean, s->m##_std_dev_plus, s->m##_std_dev_minus}

	{
		struct {
			int max;
			int min;
			int mean;
			double std_dev_plus;
			double std_dev_minus;
		} list[] = {
			MAKE_LIST(gp_lte_data_set, rssi),
			MAKE_LIST(gp_lte_data_set, rsrp),
			MAKE_LIST(gp_lte_data_set, rsrq),
			MAKE_LIST(gp_lte_data_set, cqi),
		};
		
		for (i = 0; i < ARRAY_SIZE(list); i++) {
			PUT_INT(p, list[i].max, 8);
			PUT_INT(p, list[i].min, 8);
			PUT_INT(p, list[i].mean, 8);

			if (list[i].std_dev_minus >= 0) {
				PUT_INT(p, util_htons((uint16_t)(list[i].std_dev_minus * 100.0)), 16);
			} else {
				PUT_INT(p, -1, 16);
			}

			if (list[i].std_dev_plus >= 0) {
				PUT_INT(p, util_htons((uint16_t)(list[i].std_dev_plus * 100.0)), 16);
			} else {
				PUT_INT(p, -1, 16);
			}
		}
	}
	
	{
		int *list[] = {
			gp_lte_data_set->ul_mod_cnt,
			gp_lte_data_set->dl_mod_cnt
		};

		for (i = 0; i < ARRAY_SIZE(list); i++) {
			if (list[i][MOD_QPSK] == 0 && list[i][MOD_16QAM] == 0 && list[i][MOD_64QAM] == 0) {
				PUT_INT(p, -1, 8);
				PUT_INT(p, -1, 8);
				PUT_INT(p, -1, 8);
			} else {
				PUT_INT(p, list[i][MOD_QPSK], 8);
				PUT_INT(p, list[i][MOD_16QAM], 8);
				PUT_INT(p, list[i][MOD_64QAM], 8);
			}
		}
	}
	
	{
		struct {
			int max;
			int min;
			int mean;
			int std_dev_plus;
			int std_dev_minus;
		} list[] = {
			MAKE_LIST(gp_lte_data_set, ul_rate),
			MAKE_LIST(gp_lte_data_set, dl_rate),
		};
		
		for (i = 0; i < ARRAY_SIZE(list); i++) {
			if (list[i].max >= 0) {
				PUT_INT(p, util_htons((uint16_t)(list[i].max / 1024)), 16);
			} else {
				PUT_INT(p, -1, 16);
			}
			
			if (list[i].min >= 0) {
				PUT_INT(p, util_htons((uint16_t)(list[i].min / 1024)), 16);
			} else {
				PUT_INT(p, -1, 16);
			}

			if (list[i].mean >= 0) {
				PUT_INT(p, util_htons((uint16_t)(list[i].mean / 1024)), 16);
			} else {
				PUT_INT(p, -1, 16);
			}

			if (list[i].std_dev_minus >= 0.0) {
				PUT_INT(p, util_htons((uint16_t)(list[i].std_dev_minus / 1024.0)), 16);
			} else {
				PUT_INT(p, -1, 16);
			}

			if (list[i].std_dev_plus >= 0.0) {
				PUT_INT(p, util_htons((uint16_t)(list[i].std_dev_plus / 1024.0)), 16);
			} else {
				PUT_INT(p, -1, 16);
			}
		}
	}
	
	{
		uint64_t *list[] = {
			gp_lte_data_set->tx_packet_cnt,
			gp_lte_data_set->rx_packet_cnt,
			gp_lte_data_set->tx_frame_cnt,
			gp_lte_data_set->rx_frame_cnt
		};
		
		uint64_t *err_list[] = {
			gp_lte_data_set->tx_packet_err_cnt,
			gp_lte_data_set->rx_packet_err_cnt,
			gp_lte_data_set->tx_frame_err_cnt,
			gp_lte_data_set->tx_frame_err_cnt,
		};
		
		int tx_packet_cnt, rx_packet_cnt;
		int tx_frame_cnt, rx_frame_cnt;
		
		int *p_cnt_list[] = {
			&tx_packet_cnt,
			&rx_packet_cnt,
			&tx_frame_cnt,
			&rx_frame_cnt
		};
		
		int tx_packet_err_rate, rx_packet_err_rate;
		int tx_frame_err_rate, rx_frame_err_rate;
		
		int *p_err_rate_list[] = {
			&tx_packet_err_rate,
			&rx_packet_err_rate,
			&tx_frame_err_rate,
			&rx_frame_err_rate,
		};
		
		int cnt;
		int err_cnt;
		double err_rate;
		
		for (i = 0; i < ARRAY_SIZE(list); i++) {
			if (list[i][CURR] == -1 || list[i][PREV] == -1) {
				cnt = -1;
			} else {
				cnt = (int)(list[i][CURR] - list[i][PREV]);
			}

			if (err_list[i][CURR] == -1 || err_list[i][PREV] == -1) {
				err_cnt = -1;
			} else {
				err_cnt = (int)(err_list[i][CURR] - err_list[i][PREV]);
			}

			if (cnt == -1 || err_cnt == -1) {
				err_rate = -1.0;
			} else if (cnt == 0) {
			    err_rate = 0.0;
			} else {
				err_rate = 100.0 * err_cnt / cnt;

				if (err_rate < 1.0) {
					err_rate *= 100.0;
					err_rate += 0x80;	// indicate the rate is multiplied by 100 by setting MSB to 1
				}
			}

			*p_cnt_list[i] = cnt;
			*p_err_rate_list[i] = (int)err_rate;
		}
		
		PUT_INT(p, util_htons((uint16_t)tx_packet_cnt), 16);
		PUT_INT(p, util_htons((uint16_t)rx_packet_cnt), 16);
		PUT_INT(p, tx_packet_err_rate, 8);
		PUT_INT(p, rx_packet_err_rate, 8);
		PUT_INT(p, util_htons((uint16_t)tx_frame_cnt), 16);
		PUT_INT(p, util_htons((uint16_t)rx_frame_cnt), 16);
		PUT_INT(p, tx_frame_err_rate, 8);
		PUT_INT(p, rx_frame_err_rate, 8);
	}
	
	if (gp_lte_data_set->handover_event_supportness) {
		if (gp_lte_data_set->handover_event_success_cnt >= 255) {
			PUT_INT(p, 254, 8);
		} else {
			PUT_INT(p, gp_lte_data_set->handover_event_success_cnt, 8);
		}
		
		if (gp_lte_data_set->handover_event_fail_cnt >= 255) {
			PUT_INT(p, 254, 8);
		} else {
			PUT_INT(p, gp_lte_data_set->handover_event_fail_cnt, 8);
		}
	} else {
		if (gp_lte_data_set->handover_success_cnt[PREV] == -1 || gp_lte_data_set->handover_success_cnt[CURR] == -1) {
			PUT_INT(p, gp_lte_data_set->handover_detected_cnt, 8);
		} else {
			int success_cnt = gp_lte_data_set->handover_success_cnt[CURR] - gp_lte_data_set->handover_success_cnt[PREV];

			if (success_cnt >= 255) {
				PUT_INT(p, 254, 8);
			} else {
				PUT_INT(p, success_cnt, 8);
			}
		}
		
		if (gp_lte_data_set->handover_fail_cnt[PREV] == -1 || gp_lte_data_set->handover_fail_cnt[CURR] == -1) {
			PUT_INT(p, -1, 8);
		} else {
			int fail_cnt = gp_lte_data_set->handover_fail_cnt[CURR] - gp_lte_data_set->handover_fail_cnt[PREV];

			if (fail_cnt >= 255) {
				PUT_INT(p, 254, 8);
			} else {
				PUT_INT(p, fail_cnt, 8);
			}
		}
	}
	
	PUT_INT(p, util_htons((uint16_t)gp_lte_data_set->handover_latency_mean), 16);
	PUT_INT(p, gp_lte_data_set->tx_power, 8);
	PUT_INT(p, gp_lte_data_set->temp, 8);
	PUT_INT(p, gp_lte_data_set->batt_temp, 8);
	PUT_INT(p, gp_lte_data_set->batt_lv, 8);
	PUT_INT(p, gp_lte_data_set->cpu_usage_mean, 8);
	PUT_INT(p, gp_lte_data_set->mem_usage_mean, 8);
	PUT_INT(p, gp_lte_data_set->activated_time, 8);
	PUT_INT(p, util_htons((uint16_t) g_round_trip_latency), 16);
	
	PUT_INT(p, gp_lte_data_set->scc_count, 8);
	for (i = 0; i < gp_lte_data_set->scc_count; i++)
	{
		PUT_INT(p, util_htonl((uint32_t)gp_lte_data_set->scc_cell_id[i]), 32);
		PUT_INT(p, gp_lte_data_set->scc_ch_bw[i], 8);

		PUT_INT(p, gp_lte_data_set->scc_rsrp_max[i], 8);
		PUT_INT(p, gp_lte_data_set->scc_rsrp_min[i], 8);
		PUT_INT(p, gp_lte_data_set->scc_rsrp_mean[i], 8);

		if (gp_lte_data_set->scc_rsrp_std_dev_minus[i] >= 0) {
			PUT_INT(p, util_htons((uint16_t)(gp_lte_data_set->scc_rsrp_std_dev_minus[i] * 100.0)), 16);
		} else {
			PUT_INT(p, -1, 16);
		}

		if (gp_lte_data_set->scc_rsrp_std_dev_plus[i] >= 0) {
			PUT_INT(p, util_htons((uint16_t)(gp_lte_data_set->scc_rsrp_std_dev_plus[i] * 100.0)), 16);
		} else {
			PUT_INT(p, -1, 16);
		}

		PUT_INT(p, gp_lte_data_set->scc_rsrq_max[i], 8);
		PUT_INT(p, gp_lte_data_set->scc_rsrq_min[i], 8);
		PUT_INT(p, gp_lte_data_set->scc_rsrq_mean[i], 8);

		if (gp_lte_data_set->scc_rsrq_std_dev_minus[i] >= 0) {
			PUT_INT(p, util_htons((uint16_t)(gp_lte_data_set->scc_rsrq_std_dev_minus[i] * 100.0)), 16);
		} else {
			PUT_INT(p, -1, 16);
		}

		if (gp_lte_data_set->scc_rsrq_std_dev_plus[i] >= 0) {
			PUT_INT(p, util_htons((uint16_t)(gp_lte_data_set->scc_rsrq_std_dev_plus[i] * 100.0)), 16);
		} else {
			PUT_INT(p, -1, 16);
		}

		PUT_INT(p, util_htonl((uint32_t)gp_lte_data_set->scc_dl_earfcn[i]), 32);
	}
	
	return p - data;
}
