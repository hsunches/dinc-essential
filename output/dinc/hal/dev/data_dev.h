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

#ifndef DATA_DEV_H
#define DATA_DEV_H

#include <stdint.h>

#define DEV_UID_LEN             16
#define MAX_DEV_VENDOR_LEN      32
#define MAX_DEV_MODEL_LEN       32
#define MAX_DEV_FW_VER_LEN      32
#define MAX_DEV_SN_LEN          32
#define MAX_DEV_CHIP_REV_LEN    32
#define MAX_DEV_USB_DEV_CNT     4
#define MAX_DEV_NIF_CNT         4

enum {
	DEV_USB_NOT_CONNECTED,
	DEV_USB_AUDIO,
	DEV_USB_AUDIO_VIDEO,
	DEV_USB_IMAGE,
	DEV_USB_NIF,
	DEV_USB_PRINTER,
	DEV_USB_MASS_STOARAGE,
	DEV_USB_HUB,
	DEV_USB_OTHER = 0xFE,
	DEV_USB_DEV_PORT = 0xFF
};

struct nif {
	int type;
	int rssi;

	struct {
		uint8_t mac_addr[6];
		uint64_t imsi;
		uint64_t imei;
	};
};

int dev_get_uid(char uid[DEV_UID_LEN + 1]);

int dev_get_vendor(char vendor[MAX_DEV_VENDOR_LEN + 1]);

int dev_get_model(char model[MAX_DEV_MODEL_LEN + 1]);

int dev_get_fw_ver(char ver[MAX_DEV_FW_VER_LEN + 1]);

int dev_get_sn(char sn[MAX_DEV_SN_LEN + 1]);

int dev_get_chip_rev(char rev[MAX_DEV_CHIP_REV_LEN + 1]);

int dev_get_cpu_core_cnt(int *p_cnt);

int dev_get_cpu_clk(int *p_clk);

int dev_get_mem_cap(int *p_cap);

int dev_get_flash_cap(int *p_cap);

int dev_get_batt_cap(int *p_cap);

int dev_get_batt_temp(int *p_temp);

int dev_get_temp(int *p_temp);

int dev_get_cpu_usage(int *p_usage);

int dev_get_mem_usage(int *p_usage);

int dev_get_batt_lv(int *p_lv);

int dev_get_usb_devs(int class_codes[MAX_DEV_USB_DEV_CNT], int *p_cnt);

int dev_get_nifs(struct nif nifs[MAX_DEV_NIF_CNT], int *p_cnt);

int dev_get_neighbor_wifi_info(struct nif* neighbor);

int dev_run_ftp_auto_firmware_upgrade(void);

int dev_allow_web_access_from_wan(int sec);

#endif
