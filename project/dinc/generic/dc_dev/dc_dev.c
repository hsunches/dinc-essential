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
#include <limits.h>
#include <float.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "util.h"
#include "msg_format.h"
#include "msg_hal.h"
#include "data_dev.h"
#include "dc_dev_data_set.h"
#include "version.h"

#include "log.h"

#define BUF_SIZE	256

static int clct_dev_info(uint8_t *p_info);

static void clct_dev_uid(void);
static void clct_dev_vendor(void);
static void clct_dev_model(void);
static void clct_dev_fw_ver(void);
static void clct_dev_sn(void);
static void clct_dev_chip_rev(void);
static void clct_dev_cpu_core_cnt(void);
static void clct_dev_cpu_clk(void);
static void clct_dev_mem_cap(void);
static void clct_dev_flash_cap(void);
static void clct_dev_batt_cap(void);
static void clct_dev_usb_devs(void);
static void clct_dev_nifs(void);

static int send_dev_info_msg(uint8_t *p_msg, int len);

extern void handle_options(int argc, char* argv[]);
extern uint64_t util_get_dev_uid(void);
extern uint32_t util_string_replace_token(char* pstr, const char token, const char replent);

void dc_dev_version(void) __attribute((used));
void dc_dev_init(void) __attribute((used));

uint32_t dc_dev_id(void) __attribute((used));
int dc_dev_main(int argc, char *argv[]) __attribute((used));
int dc_dev_external_cmd_execute(uint8_t type, uint32_t sec) __attribute((used));

int dc_dev_main(int argc, char *argv[]) 
{
	dev_data_set ds = {};
	memset(&ds, 0, sizeof(ds));
	gp_dev_data_set = &ds;

	dc_dev_init();
	
	uint8_t dev_info_msg[BUF_SIZE];
	uint8_t dev_info_report[BUF_SIZE];
	uint8_t *p_msg;
	int len;

	handle_options(argc, argv);

	memset(dev_info_msg, 0, sizeof(dev_info_msg));
	p_msg = dev_info_msg;
	len = clct_dev_info(p_msg);

	if (len < 0 || send_dev_info_msg(dev_info_msg, len) < 0) {
		return 1;
	}

	memset(dev_info_report, 0, sizeof(dev_info_report));
	p_msg = dev_info_report;
	len = dev_pack_report(p_msg);
	
	if (len < 0 || send_dev_info_msg(dev_info_report, len) < 0) 
	{
		return 1;
	}

	return 0;
}

int dc_dev_external_cmd_execute(uint8_t type, uint32_t value) {
	int ret = 0;
	switch(type) {
		case RUN_FTP_AUTO_FIRMWARE_UPGRADE:
			ret = dev_run_ftp_auto_firmware_upgrade();
			break;
		case ALLOW_WEB_ACCESS_FROM_WAN:
			ret = dev_allow_web_access_from_wan((int)value);
			break;
		default:
			LOGG_ERR("Unsupported External Cmd.");
			ret = 1;
			break;
	}
	return ret;
}

uint32_t dc_dev_id(void)
{
	return IPC_DC_DEV;
}

void dc_dev_version(void) 
{	
}

void dc_dev_init(void) 
{
}

int clct_dev_info(uint8_t *p_info) {
	clct_dev_uid();
	clct_dev_vendor();
	clct_dev_model();
	clct_dev_fw_ver();
	clct_dev_sn();
	clct_dev_chip_rev();
	clct_dev_cpu_core_cnt();
	clct_dev_cpu_clk();
	clct_dev_mem_cap();
	clct_dev_flash_cap();
	clct_dev_batt_cap();
	clct_dev_usb_devs();
	clct_dev_nifs();
	return dev_pack_info(p_info);
}

static void clct_dev_uid(void) {
	// char uid[DEV_UID_LEN + 1];

	// if (dev_get_uid(uid) < 0) {
	// 	gp_dev_data_set->uid = -1;
	// } else {
	// 	gp_dev_data_set->uid = (uint64_t)strtoull(uid, NULL, 16);
	// }
	gp_dev_data_set->uid = util_get_dev_uid();
}

static void clct_dev_vendor(void) {
	if (dev_get_vendor(gp_dev_data_set->vendor) < 0) {
		*gp_dev_data_set->vendor = 0;
	}
	util_string_replace_token(gp_dev_data_set->vendor, '\n', ' ');
}

static void clct_dev_model(void) {
	if (dev_get_model(gp_dev_data_set->model) < 0) {
		*gp_dev_data_set->model = 0;
	}
	util_string_replace_token(gp_dev_data_set->model, '\n', ' ');
}

static void clct_dev_fw_ver(void) {
	if (dev_get_fw_ver(gp_dev_data_set->fw_ver) < 0) {
		*gp_dev_data_set->fw_ver = 0;
	}
	util_string_replace_token(gp_dev_data_set->fw_ver, '\n', ' ');
}

static void clct_dev_sn(void) {
	if (dev_get_sn(gp_dev_data_set->sn) < 0) {
		*gp_dev_data_set->sn = 0;
	}
	util_string_replace_token(gp_dev_data_set->sn, '\n', ' ');
}

static void clct_dev_chip_rev(void) {
	if (dev_get_chip_rev(gp_dev_data_set->chip_rev) < 0) {
		*gp_dev_data_set->chip_rev = 0;
	}
	util_string_replace_token(gp_dev_data_set->chip_rev, '\n', ' ');
}

static void clct_dev_cpu_core_cnt(void) {
	if (dev_get_cpu_core_cnt(&gp_dev_data_set->cpu_core_cnt) < 0) {
		gp_dev_data_set->cpu_core_cnt = -1;
	}
}

static void clct_dev_cpu_clk(void) {
	if (dev_get_cpu_clk(&gp_dev_data_set->cpu_clk) < 0) {
		gp_dev_data_set->cpu_clk = -1;
	}
}

static void clct_dev_mem_cap(void) {
	if (dev_get_mem_cap(&gp_dev_data_set->mem_cap) < 0) {
		gp_dev_data_set->mem_cap = -1;
	}
}

static void clct_dev_flash_cap(void) {
	if (dev_get_flash_cap(&gp_dev_data_set->flash_cap) < 0) {
		gp_dev_data_set->flash_cap = -1;
	}
}

static void clct_dev_batt_cap(void) {
	if (dev_get_batt_cap(&gp_dev_data_set->batt_cap) < 0) {
		gp_dev_data_set->batt_cap = -1;
	}
}

static void clct_dev_usb_devs(void) {
	if (dev_get_usb_devs(gp_dev_data_set->usb_devs, &gp_dev_data_set->usb_dev_cnt) < 0) {
		gp_dev_data_set->usb_dev_cnt = -1;
	}
}

static void clct_dev_nifs(void) {
	memset(gp_dev_data_set->nifs, 0xFF, sizeof(gp_dev_data_set->nifs));

	if (dev_get_nifs(gp_dev_data_set->nifs, &gp_dev_data_set->nif_cnt) < 0) {
		gp_dev_data_set->nif_cnt = -1;
	}
}

int send_dev_info_msg(uint8_t *p_msg, int msg_len) {
	int fd;
	struct sockaddr_in addr;

	fd = socket(AF_INET, SOCK_DGRAM, 0);

	if (fd < 0) {
		return -1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(DIN_IPC_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if (sendto(fd, p_msg, msg_len, 0, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		return -1;
	}

	return 0;
}
