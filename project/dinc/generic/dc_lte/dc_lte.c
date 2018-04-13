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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "msg_format.h"
#include "dc_lte_ipc_handler.h"
#include "dc_lte_data_set.h"
#include "util.h"
#include "version.h"

extern int g_report_interval;

extern void handle_options(int argc, char* argv[]);

void dc_lte_version(void) __attribute((used));
void dc_lte_init(void) __attribute((used));
void dc_lte_load_config(const char* path) __attribute((used));

uint32_t dc_lte_id(void) __attribute((used));
int dc_lte_main(int argc, char *argv[]) __attribute((used));

int dc_lte_main(int argc, char *argv[]) 
{
	lte_data_set ds = {};
	memset(&ds, 0, sizeof(ds));
	gp_lte_data_set = &ds;

	lte_cfg cfg = {};
	gp_lte_cfg = &cfg;

	dc_lte_init();

	handle_options(argc, argv);

	if (util_create_ipc_channel(DIN_DEVICE_IP, DIN_IPC_PORT) < 0) {
		return 1;
	}

	if (start_lte_ipc_routine() < 0) {
		return 1;
	}

	return 0;
}

uint32_t dc_lte_id(void)
{
	return IPC_DC_LTE;
}

void dc_lte_version(void) 
{
	
}

void dc_lte_init(void) 
{
	struct stat_tbl stat_tbl[] = {
		{0, {-1, -1}, {PERCENT_TH1, PERCENT_TH2, PERCENT_TH3, PERCENT_TH4}, {0}, {0}, 0, -1, -1, -1},
		{0, {-1, -1}, {PERCENT_TH1, PERCENT_TH2, PERCENT_TH3, PERCENT_TH4}, {0}, {0}, 0, -1, -1, -1},
		{0, {-1, -1}, {TEMP_TH1, TEMP_TH2, TEMP_TH3, TEMP_TH4}, {0}, {0}, 0, 127, 127, 127},
		{0, {-1, -1}, {TEMP_TH1, TEMP_TH2, TEMP_TH3, TEMP_TH4}, {0}, {0}, 0, 127, 127, 127}
	};
	memcpy(&g_stat_tbl, &stat_tbl, sizeof(g_stat_tbl));

	g_report_interval = MAX_REPORT_INTERVAL;	
}

#define BUF_SIZE	256

void dc_lte_load_config(const char *path) 
{
	const char *sq_tbl[] = {
		"NONE",
		"RSSI",
		"RSRP",
		"RSRQ",
		"CQI"
	};

	char line[BUF_SIZE];
	char temp[BUF_SIZE];
	char threshold_key[32];
	char report_interval_key[32];
	int is_indicator_found = 0;
	int is_threshold_found = 0;
	int is_report_interval_found = 0;
	
	// assign default
	gp_lte_cfg->idle_threshold = 0;
	gp_lte_cfg->indicator = 4;
	gp_lte_cfg->threshold_cnt = 3;
	int default_thresholds[] = {5, 15, 20};
	memcpy(&gp_lte_cfg->thresholds, &default_thresholds, sizeof(gp_lte_cfg->thresholds));
	int default_intervals[] = {30, 60, 120, 150};
	memcpy(&gp_lte_cfg->report_intervals, &default_intervals, sizeof(gp_lte_cfg->report_intervals));

	FILE *file;
	file = fopen(path, "r");

	if (file == NULL) {
		return;
	}

	while (fgets(line, sizeof(line), file) != NULL) {
		char *value;
		char *token;
		int i;

		value = strchr(line, '=');

		if (value == NULL) {
			continue;
		}

		*value++ = 0;
		token = strrchr(value, '\n');

		if (token) {
			*token = 0;
		}

		if (!is_indicator_found) {
			if (!strcmp(line, "REPORT_INTERVAL_INDICATOR")) {
				for (i = 1; i < ARRAY_SIZE(sq_tbl); i++) {
					if (!strcmp(value, sq_tbl[i])) {
						is_indicator_found = 1;
						gp_lte_cfg->indicator = i;
						sprintf(threshold_key, "%s_THRESHOLDS", value);
						sprintf(report_interval_key, "%s_REPORT_INTERVALS", value);
						break;
					}
				}
			}
		} else if (!is_threshold_found) {
			if (!strcmp(line, threshold_key)) {
				int threshold_cnt = 0;

				strcpy(temp, value);
				token = strtok(temp, ",");

				while (token) {
					threshold_cnt++;
					token = strtok(NULL, ",");
				}

				if (threshold_cnt >= MAX_LV_CNT) {
					break;
				}

				is_threshold_found = 1;
				gp_lte_cfg->threshold_cnt = threshold_cnt;
				token = strtok(value, ",");

				for (i = 0; i < threshold_cnt; i++) {
					gp_lte_cfg->thresholds[i] = (int)strtol(token, NULL, 10);
					token = strtok(NULL, ",");
				}
			}
		} else if (!is_report_interval_found) {
			if (!strcmp(line, report_interval_key)) {
				int report_interval_cnt = 0;

				strcpy(temp, value);
				token = strtok(temp, ",");

				while (token) {
					report_interval_cnt++;
					token = strtok(NULL, ",");
				}

				if (report_interval_cnt != gp_lte_cfg->threshold_cnt + 1) {
					break;
				}

				is_report_interval_found = 1;
				token = strtok(value, ",");

				for (i = 0; i < report_interval_cnt; i++) {
					gp_lte_cfg->report_intervals[i] = (int)strtol(token, NULL, 10);

					if (gp_lte_cfg->report_intervals[i] < MIN_REPORT_INTERVAL) {
						gp_lte_cfg->report_intervals[i] = MIN_REPORT_INTERVAL;
					} else if (gp_lte_cfg->report_intervals[i] > MAX_REPORT_INTERVAL) {
						gp_lte_cfg->report_intervals[i] = MAX_REPORT_INTERVAL;
					}
					
					token = strtok(NULL, ",");
				}

				break;
			}
		}
	}

	if (!is_report_interval_found) {
		gp_lte_cfg->indicator = REPORT_INTERVAL_INDICATOR_NONE;
	}

	fclose(file);
}