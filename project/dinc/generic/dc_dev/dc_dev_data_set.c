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
 
#include "dc_dev_data_set.h"
#include "msg_format.h"
#include "msg_hal.h"
#include "util.h"

dev_data_set* gp_dev_data_set;

int dev_pack_info(uint8_t data[]) {
	uint8_t *p;
	int i;
	
	p = data;
	PUT_INT(p, util_htonl(IPC_MSG_SEND_REPORT), 32);
	PUT_INT(p, util_htonl(IPC_DC_DEV), 32);
	PUT_INT(p, DINP_ROLE_DEV | DINP_HDR_MASK_UID, 8);
	PUT_INT(p, DINP_MSG_DC_DEVICE_INFO, 8);
	PUT_INT(p, util_htonll(gp_dev_data_set->uid), 64);
	PUT_STR(p, gp_dev_data_set->vendor);
	PUT_STR(p, gp_dev_data_set->model);
	PUT_STR(p, gp_dev_data_set->fw_ver);
	PUT_STR(p, gp_dev_data_set->sn);
	PUT_STR(p, gp_dev_data_set->chip_rev);
	PUT_INT(p, gp_dev_data_set->cpu_core_cnt, 8);
	PUT_INT(p, util_htons((uint16_t)gp_dev_data_set->cpu_clk), 16);
	PUT_INT(p, util_htons((uint16_t)gp_dev_data_set->mem_cap), 16);
	PUT_INT(p, util_htons((uint16_t)gp_dev_data_set->flash_cap), 16);
	PUT_INT(p, util_htons((uint16_t)gp_dev_data_set->batt_cap), 16);
	PUT_INT(p, gp_dev_data_set->usb_dev_cnt, 8);

	for (i = 0; i < gp_dev_data_set->usb_dev_cnt; i++) {
		PUT_INT(p, gp_dev_data_set->usb_devs[i], 8);
	}

	PUT_INT(p, gp_dev_data_set->nif_cnt, 8);

	for (i = 0; i < gp_dev_data_set->nif_cnt; i++) {
		PUT_INT(p, gp_dev_data_set->nifs[i].type, 8);
		PUT_MEM(p, gp_dev_data_set->nifs[i].mac_addr, FIELD_SIZE(struct nif, mac_addr));

		switch (gp_dev_data_set->nifs[i].type) {
		case NIF_TYPE_WIFI:
		case NIF_TYPE_WMX:
		case NIF_TYPE_ETHERNET:
			break;

		default:
			PUT_INT(p, util_htonll(gp_dev_data_set->nifs[i].imsi), 64);
			PUT_INT(p, util_htonll(gp_dev_data_set->nifs[i].imei), 64);
			break;
		}
	}
	
	return p - data;
}

int dev_pack_report(uint8_t data[]) 
{
	uint8_t *p = data;
	
	PUT_INT(p, util_htonl(IPC_MSG_SET_DEVICE_INFO), 32);
	PUT_INT(p, util_htonl(IPC_DC_DEV), 32);
	PUT_INT(p, util_htonll(gp_dev_data_set->uid), 64);

	return p - data;
}