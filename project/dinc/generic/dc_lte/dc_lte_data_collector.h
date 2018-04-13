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

#ifndef DC_DATA_COLLECTOR_H
#define DC_DATA_COLLECTOR_H

typedef int (*write_func)(const void *data, int len);

int clct_lte_conn_history_info(write_func writer);
int clct_lte_dev_info(write_func writer);
int clct_lte_net_entry_info(write_func writer);
int clct_lte_routine_info(write_func writer);

// void set_conn_time(uint32_t conn_time[]);
void set_lte_net_entry_latency(uint32_t latency);
// void set_round_trip_latency(uint32_t latency);
void notify_lte_handover_start(int64_t time_usec);
void notify_lte_handover_end(int is_success, int64_t time_usec);

#endif
