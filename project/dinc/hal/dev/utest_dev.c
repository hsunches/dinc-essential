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
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "ut_util.h"
#include "msg_hal.h"
#include "data_dev.h"

MAKE_TEST_FUNC_STR(dev_get_vendor, MAX_DEV_VENDOR_LEN);
MAKE_TEST_FUNC_STR(dev_get_model, MAX_DEV_MODEL_LEN);
MAKE_TEST_FUNC_STR(dev_get_fw_ver, MAX_DEV_FW_VER_LEN);
MAKE_TEST_FUNC_STR(dev_get_sn, MAX_DEV_SN_LEN);
MAKE_TEST_FUNC_STR(dev_get_chip_rev, MAX_DEV_CHIP_REV_LEN);
MAKE_TEST_FUNC_INT(dev_get_cpu_core_cnt, 1, 255);
MAKE_TEST_FUNC_INT(dev_get_cpu_clk, 1, 65535);
MAKE_TEST_FUNC_INT(dev_get_mem_cap, 1, 65535);
MAKE_TEST_FUNC_INT(dev_get_flash_cap, 1, 65535);
MAKE_TEST_FUNC_INT(dev_get_batt_cap, 1, 65535);
MAKE_TEST_FUNC_INT(dev_get_batt_temp, -128, 127);
MAKE_TEST_FUNC_INT(dev_get_temp, -128, 127);
MAKE_TEST_FUNC_INT(dev_get_cpu_usage, 0, 100);
MAKE_TEST_FUNC_INT(dev_get_mem_usage, 0, 100);
MAKE_TEST_FUNC_INT(dev_get_batt_lv, 0, 100);

int test_dev_get_uid(char *text) {
	char uid[DEV_UID_LEN + 1];

	if (dev_get_uid(uid) == 0) {
		int uid_len;

		strcpy(text, uid);
		uid_len = strlen(uid);
		
		if (uid_len == DEV_UID_LEN) {
			int i;

			for (i = 0; i < DEV_UID_LEN; i++) {
				if (!isxdigit(uid[i])) {
					return UT_FAIL;
				}
			}

			return UT_PASS;
		}
	}

	return UT_FAIL;
}

int test_dev_get_usb_devs(char *text) {
	int devs[MAX_DEV_USB_DEV_CNT];
	int cnt;
	
	if (dev_get_usb_devs(devs, &cnt) == 0) {
		char buf[32];
		int ret;
		int i;

		sprintf(text, "Count: %d\n", cnt);
		
		if (cnt < 0 || cnt > MAX_DEV_USB_DEV_CNT) {
			return UT_FAIL;
		}

		ret = UT_PASS;

		for (i = 0; i < cnt; i++) {
			switch (devs[i]) {
			case DEV_USB_NOT_CONNECTED:
				strcat(text, "Not Connected, ");
				break;

			case DEV_USB_AUDIO:
				strcat(text, "Audio, ");
				break;

			case DEV_USB_AUDIO_VIDEO:
				strcat(text, "Audio/Video, ");
				break;

			case DEV_USB_IMAGE:
				strcat(text, "Image, ");
				break;

			case DEV_USB_NIF:
				strcat(text, "NIF, ");
				break;

			case DEV_USB_PRINTER:
				strcat(text, "Printer, ");
				break;

			case DEV_USB_MASS_STOARAGE:
				strcat(text, "Storage, ");
				break;

			case DEV_USB_HUB:
				strcat(text, "Hub, ");
				break;

			case DEV_USB_OTHER:
				strcat(text, "Other, ");
				break;

			case DEV_USB_DEV_PORT:
				strcat(text, "Device Port, ");
				break;

			default:
				sprintf(buf, "*%d*, ", devs[i]);
				strcat(text, buf);
				ret = UT_FAIL;
				break;
			}
		}

		text[strlen(text) - 2] = 0;
		return ret;
	}

	return UT_NOT_SUPPORT;
}

int test_dev_get_nifs(char *text) {
	struct nif nifs[MAX_DEV_NIF_CNT];
	int cnt;
	int i;

	memset(nifs, 0xFF, sizeof(nifs));

	if (dev_get_nifs(nifs, &cnt) == 0) {
		char buf[32];
		int ret;

		sprintf(text, "Count: %d\n", cnt);

		if (cnt < 0 || cnt > MAX_DEV_NIF_CNT) {
			return UT_FAIL;
		}

		ret = UT_PASS;

		for (i = 0; i < cnt; i++) {
			strcat(text, "Type: ");

			switch (nifs[i].type) {
			case NIF_TYPE_WIFI:
				strcat(text, "Wi-Fi, ");
				break;

			case NIF_TYPE_WMX:
				strcat(text, "WiMAX, ");
				break;

			case NIF_TYPE_ETHERNET:
				strcat(text, "Ethernet, ");
				break;

			case NIF_TYPE_2G:
				strcat(text, "2G, ");
				break;

			case NIF_TYPE_WCDMA:
				strcat(text, "WCDMA, ");
				break;

			case NIF_TYPE_CDMA2K:
				strcat(text, "CDMA2000, ");
				break;

			case NIF_TYPE_LTE:
				strcat(text, "LTE, ");
				break;

			default:
				sprintf(buf, "*%d*, ", nifs[i].type);
				strcat(text, buf);
				ret = UT_FAIL;
				continue;
			}

			switch (nifs[i].type) {
			case NIF_TYPE_2G:
			case NIF_TYPE_WCDMA:
			case NIF_TYPE_CDMA2K:
			case NIF_TYPE_LTE:
				if (nifs[i].imsi != ~0ULL) {
					strcat(text, "IMSI: ");
					sprintf(buf, "%llu", (unsigned long long)nifs[i].imsi);

					if (strlen(buf) > 15) {
						sprintf(buf, "*%llu*, ", (unsigned long long)nifs[i].imsi);
						strcat(text, buf);
						ret = UT_FAIL;
					} else {
						strcat(text, buf);
						strcat(text, ", ");
					}
				}

				if (nifs[i].imei != ~0ULL) {
					strcat(text, "IMEI: ");
					sprintf(buf, "%llu", (unsigned long long)nifs[i].imei);

					if (strlen(buf) > 15) {
						sprintf(buf, "*%llu*, ", (unsigned long long)nifs[i].imei);
						strcat(text, buf);
						ret = UT_FAIL;
					} else {
						strcat(text, buf);
						strcat(text, ", ");
					}
				}

				/* fall through */
				/* no break		*/
			case NIF_TYPE_WIFI:
			case NIF_TYPE_WMX:
			case NIF_TYPE_ETHERNET:
				strcat(text, "MAC Address: ");

				if (memcmp(nifs[i].mac_addr, "\xFF\xFF\xFF\xFF\xFF\xFF", sizeof(nifs[i].mac_addr)) == 0) {
					strcat(text, "*FF:FF:FF:FF:FF:FF*\n");
					ret = UT_FAIL;
				} else {
					sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X\n",
						nifs[i].mac_addr[0],
						nifs[i].mac_addr[1],
						nifs[i].mac_addr[2],
						nifs[i].mac_addr[3],
						nifs[i].mac_addr[4],
						nifs[i].mac_addr[5]
					);

					strcat(text, buf);
				}

				break;
			}
		}

		return ret;
	}

	return UT_NOT_SUPPORT;
}

int main() {
    struct test_suite *p_suite;
    struct test_suite *p_sub_suite;

    p_suite = create_test_suite("Device", 1);

    p_sub_suite = create_test_suite("Test 1", 1);
    add_test(p_sub_suite,	"Unique ID",			5,	test_dev_get_uid);
    add_test(p_sub_suite,	"Vendor", 				5,	test_dev_get_vendor);
    add_test(p_sub_suite,	"Model",				5,	test_dev_get_model);
    add_test(p_sub_suite,	"Firmware Version",		5,	test_dev_get_fw_ver);
    add_test(p_sub_suite,	"Serial Number",		5,	test_dev_get_sn);
    add_test(p_sub_suite,	"Chipset Revision",		5,	test_dev_get_chip_rev);
    add_test(p_sub_suite,	"CPU Core Count",		5,	test_dev_get_cpu_core_cnt);
    add_test(p_sub_suite,	"CPU Clock",			5,	test_dev_get_cpu_clk);
    add_test(p_sub_suite,	"Memory Capacity",		5,	test_dev_get_mem_cap);
    add_test(p_sub_suite,	"Flash Capacity",		5,	test_dev_get_flash_cap);
    add_test(p_sub_suite,	"Battery Capacity",		5,	test_dev_get_batt_cap);
    add_test(p_sub_suite,	"USB Devices",			5,	test_dev_get_usb_devs);
    add_test(p_sub_suite,	"Network Interfaces",	5,	test_dev_get_nifs);
    add_test_suite(p_suite, p_sub_suite);

    p_sub_suite = create_test_suite("Test 2", 1);
    add_test(p_sub_suite,	"Battery Temperature",	5,	test_dev_get_batt_temp);
    add_test(p_sub_suite,	"Temperature",			5,	test_dev_get_temp);
    add_test(p_sub_suite,	"CPU Usage",			5,	test_dev_get_cpu_usage);
    add_test(p_sub_suite,	"Memory Usage",			5,	test_dev_get_mem_usage);
    add_test(p_sub_suite,	"Battery Level",		5,	test_dev_get_batt_lv);
    add_test_suite(p_suite, p_sub_suite);

    run_test_suite(p_suite);
    delete_test_suite(p_suite);
    return 0;
}
