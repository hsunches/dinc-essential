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

#ifndef DC_DEV_DATA_SET_H
#define DC_DEV_DATA_SET_H

#include <stdint.h>
#include "data_dev.h"

typedef struct {
	uint64_t uid;
	char vendor[MAX_DEV_VENDOR_LEN + 1];
	char model[MAX_DEV_MODEL_LEN + 1];
	char fw_ver[MAX_DEV_FW_VER_LEN + 1];
	char sn[MAX_DEV_SN_LEN + 1];
	char chip_rev[MAX_DEV_CHIP_REV_LEN + 1];
	int cpu_core_cnt;
	int cpu_clk;
	int mem_cap;
	int flash_cap;
	int batt_cap;
	int usb_dev_cnt;
	int usb_devs[MAX_DEV_USB_DEV_CNT];
	int nif_cnt;
	struct nif nifs[MAX_DEV_NIF_CNT];
} dev_data_set;

typedef enum {
	RUN_FTP_AUTO_FIRMWARE_UPGRADE = 0,
	ALLOW_WEB_ACCESS_FROM_WAN
} dev_external_cmd_type;

extern dev_data_set* gp_dev_data_set;

int dev_pack_info(uint8_t data[]);
int dev_pack_report(uint8_t data[]);

#endif
