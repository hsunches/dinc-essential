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
#include "dc_wifi_ap_ipc_handler.h"
#include "dc_wifi_ap_data_set.h"
#include "util.h"
#include "version.h"

extern int g_report_interval;

extern void handle_options(int argc, char* argv[]);

void dc_wifi_ap_version(void) __attribute((used));
void dc_wifi_ap_init(void) __attribute((used));
void dc_wifi_ap_load_config(const char* path) __attribute((used));

uint32_t dc_wifi_ap_id(void) __attribute((used));
int dc_wifi_ap_main(int argc, char *argv[]) __attribute((used));

int dc_wifi_ap_main(int argc, char *argv[]) 
{
	wifi_ap_data_set ds = {};
	memset(&ds, 0, sizeof(ds));
	gp_wifi_ap_data_set = &ds;

	wifi_ap_cfg cfg = {};
	gp_wifi_ap_cfg = &cfg;

	dc_wifi_ap_init();
	
	handle_options(argc, argv);

	if (util_create_ipc_channel(DIN_DEVICE_IP, DIN_IPC_PORT) < 0) {
		return 1;
	}

	if (start_wifi_ap_ipc_routine() < 0) {
		return 1;
	}

	return 0;
}

uint32_t dc_wifi_ap_id(void)
{
	return IPC_DC_WIFI_AP;
}

void dc_wifi_ap_version(void) 
{
	
}

void dc_wifi_ap_init(void) 
{
	// assign default
	g_report_interval = WIFI_AP_REPORT_INTERVAL;
}

#define BUF_SIZE	256

void dc_wifi_ap_load_config(const char *path)
{
	gp_wifi_ap_cfg->idle_threshold = 0;
	
	char line[BUF_SIZE];
	FILE *file;

	file = fopen(path, "r");

	if (file == NULL) {
		return;
	}
	
	while (fgets(line, sizeof(line), file) != NULL) {
		char *value;
		char *token;

		value = strchr(line, '=');

		if (value == NULL) {
			continue;
		}

		*value++ = 0;
		token = strrchr(value, '\n');

		if (token) {
			*token = 0;
		}

		if (!strcmp(line, "REPORT_INTERVAL")) {
			g_report_interval = (int)strtol(value, NULL, 10);

			if (g_report_interval < MIN_REPORT_INTERVAL) {
				g_report_interval = MIN_REPORT_INTERVAL;
			} else if (g_report_interval > MAX_REPORT_INTERVAL) {
				g_report_interval = MAX_REPORT_INTERVAL;
			}

			break;
		}
	}
	
	fclose(file);
}