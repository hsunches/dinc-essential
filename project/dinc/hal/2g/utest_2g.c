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
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include "ut_util.h"
#include "data_2g.h"
#include "msg_hal.h"

MAKE_TEST_FUNC_INT(two_g_get_net_entry_latency, 0, 65535);
MAKE_TEST_FUNC_INT(two_g_get_ci, 0, 65535);
MAKE_TEST_FUNC_INT(two_g_get_rssi, -128, 127);
MAKE_TEST_FUNC_INT(two_g_get_rxqual, 0, 7);
MAKE_TEST_FUNC_INT(two_g_get_arfcn, 0, 1023);
MAKE_TEST_FUNC_INT(two_g_get_mcc, 0, 999);
MAKE_TEST_FUNC_INT(two_g_get_handover_latency, 0, 65535);
MAKE_TEST_FUNC_INT(two_g_get_handover_success_cnt, 0, 255);
MAKE_TEST_FUNC_INT(two_g_get_handover_fail_cnt, 0, 255);
MAKE_TEST_FUNC_INT(two_g_get_tx_power, -128, 127);
MAKE_TEST_FUNC_UINT64(two_g_get_tx_byte, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(two_g_get_tx_packet_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(two_g_get_tx_packet_err_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(two_g_get_tx_frame_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(two_g_get_tx_frame_err_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(two_g_get_rx_byte, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(two_g_get_rx_packet_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(two_g_get_rx_packet_err_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(two_g_get_rx_frame_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(two_g_get_rx_frame_err_cnt, 0, ~0ULL);

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

int test_band(char *text, int band) {
	const char *band_names[] = {
		"T-GSM-380",
		"T-GSM-410",
		"GSM-450",
		"GSM-480",
		"GSM-710",
		"GSM-750",
		"T-GSM-810",
		"GSM-850",
		"P-GSM-900",
		"E-GSM-900",
		"R-GSM-900",
		"T-GSM-900",
		"DCS-1800",
		"PCS-1900",
	};

	if (band < 1 || band > ARRAY_SIZE(band_names)) {
		sprintf(text, "*%d*", band);
		return UT_FAIL;
	}

	strcpy(text, band_names[band - 1]);
	return UT_PASS;
}

int test_two_g_get_supp_freq_bands(char *text) {
	int bands;

	if (two_g_get_supp_freq_bands(&bands) == 0) {
		char buf[32];
		int ret;
		int i;

		if (bands == 0) {
			strcpy(text, "*No Bands Specified*");
			return UT_FAIL;
		}

		ret = UT_PASS;
		text[0] = 0;

		for (i = 1; i <= sizeof(int) * 8; i++) {
			if (bands & 1) {
				ret = test_band(buf, i);
				strcat(text, buf);
				strcat(text, ", ");
			}

			bands >>= 1;
		}

		text[strlen(text) - 2] = 0;
		return ret;
	}

	return UT_NOT_SUPPORT;
}

int test_two_g_get_ip_addr(char *text) {
	char ip_addr[40];
	
	if (two_g_get_ip_addr(ip_addr) == 0) {
		int addr_family;
		uint8_t addr[16];
		
		if (strchr(ip_addr, '.') != NULL) {
			addr_family = AF_INET;
		} else if (strchr(ip_addr, ':') != NULL) {
			addr_family = AF_INET6;
		} else {
			sprintf(text, "*%s*", ip_addr);
			return UT_FAIL;
		}

		if (inet_pton(addr_family, ip_addr, addr) != 1) {
			sprintf(text, "*%s*", ip_addr);
			return UT_FAIL;
		}
		
		strcpy(text, ip_addr);
		return UT_PASS;
	}
	
	return UT_NOT_SUPPORT;
}

int test_two_g_get_work_mode(char *text) {
	int mode;

	if (two_g_get_work_mode(&mode) == 0) {
		char buf[32];

		switch (mode) {
		case TWO_G_WORK_MODE_GPRS:
			strcpy(text, "GPRS");
			break;

		case TWO_G_WORK_MODE_EDGE:
			strcpy(text, "EDGE");
			break;

		default:
			sprintf(buf, "*%d*", mode);
			return UT_FAIL;
		}

		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_two_g_get_mnc(char *text) {
	char mnc[4];

	if (two_g_get_mnc(mnc) == 0) {
		int mnc_len;
		int i;

		mnc_len = strlen(mnc);

		if (mnc_len < 1 || mnc_len > 3) {
			sprintf(text, "*%s*", mnc);
			return UT_FAIL;
		}

		for (i = 0; i < mnc_len; i++) {
			if (!isdigit(mnc[i])) {
				sprintf(text, "*%s*", mnc);
				return UT_FAIL;
			}
		}

		strcpy(text, mnc);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_two_g_get_lac(char *text) {
	int lac;

	if (two_g_get_lac(&lac) == 0) {
		if (lac < 1 || lac == 65534 || lac > 65535) {
			sprintf(text, "*%d*", lac);
			return UT_FAIL;
		}

		sprintf(text, "%d", lac);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_two_g_get_ul_mcs(char *text) {
	int mcs;

	if (two_g_get_ul_mcs(&mcs) == 0) {
		switch (mcs) {
		case MCS_TYPE_GMSK:
			strcpy(text, "GMSK");
			break;

		case MCS_TYPE_8PSK:
			strcpy(text, "8-PSK");
			break;

		default:
			sprintf(text, "*%d*", mcs);
			return UT_FAIL;
		}

		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_two_g_get_dl_mcs(char *text) {
	int mcs;

	if (two_g_get_ul_mcs(&mcs) == 0) {
		switch (mcs) {
		case MCS_TYPE_GMSK:
			strcpy(text, "GMSK");
			break;

		case MCS_TYPE_8PSK:
			strcpy(text, "8-PSK");
			break;

		default:
			sprintf(text, "*%d*", mcs);
			return UT_FAIL;
		}

		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_two_g_get_ngbr_cells(char *text) {
	struct two_g_cell cells[MAX_TWO_G_NGBR_CELL_CNT];
	int cnt;
	int i;

	for (i = 0; i < MAX_TWO_G_NGBR_CELL_CNT; i++) {
		cells[i].ci = TWO_G_INVALID_CI;
		cells[i].mcc = TWO_G_INVALID_MCC;
		strcpy(cells[i].mnc, TWO_G_INVALID_MNC);
		cells[i].lac = TWO_G_INVALID_LAC;
		cells[i].rssi = TWO_G_INVALID_RSSI;
		cells[i].rxqual = TWO_G_INVALID_RXQUAL;
	}
	
	if (two_g_get_ngbr_cells(cells, &cnt) == 0) {
		char buf[32];
		int ret;

		sprintf(text, "Count: %d\n", cnt);

		if (cnt < 0 || cnt > MAX_TWO_G_NGBR_CELL_CNT) {
			return UT_FAIL;
		}

		ret = UT_PASS;

		for (i = 0; i < cnt; i++) {
			strcat(text, "CI: ");

			if (cells[i].ci < 0 || cells[i].ci > 65535) {
				sprintf(buf, "*%d*, ", cells[i].ci);
				ret = UT_FAIL;
			} else {
				sprintf(buf, "%d, ", cells[i].ci);
			}

			strcat(text, buf);
			
			if (cells[i].mcc != TWO_G_INVALID_MCC) {
				strcat(text, "MCC: ");

				if (cells[i].mcc < 0 || cells[i].mcc > 999) {
					sprintf(buf, "*%d*, ", cells[i].mcc);
					ret = UT_FAIL;
				} else {
					sprintf(buf, "%d, ", cells[i].mcc);
				}

				strcat(text, buf);
			}
			
			if (strcmp(cells[i].mnc, TWO_G_INVALID_MNC) != 0) {
				int mnc_len;
				int j;

				mnc_len = strlen(cells[i].mnc);
				
				for (j = 0; j < mnc_len; j++) {
					if (!isdigit(cells[i].mnc[j])) {
						break;
					}
				}

				strcat(text, "MNC: ");

				if (j < mnc_len) {
					sprintf(buf, "*%s*, ", cells[i].mnc);
					ret = UT_FAIL;
				} else {
					sprintf(buf, "%s, ", cells[i].mnc);
				}

				strcat(text, buf);
			}

			if (cells[i].lac != TWO_G_INVALID_LAC) {
				strcat(text, "LAC: ");

				if (cells[i].lac < 0 || cells[i].lac == 65534 || cells[i].lac > 65535) {
					sprintf(buf, "*%d*, ", cells[i].lac);
					ret = UT_FAIL;
				} else {
					sprintf(buf, "%d, ", cells[i].lac);
				}

				strcat(text, buf);
			}

			if (cells[i].rssi != TWO_G_INVALID_RSSI) {
				strcat(text, "RSSI: ");

				if (cells[i].rssi < -128 || cells[i].rssi > 127) {
					sprintf(buf, "*%d*, ", cells[i].rssi);
					ret = UT_FAIL;
				} else {
					sprintf(buf, "%d, ", cells[i].rssi);
				}

				strcat(text, buf);
			}

			if (cells[i].rxqual != TWO_G_INVALID_RXQUAL) {
				strcat(text, "RXQUAL: ");

				if (cells[i].rxqual < 0 || cells[i].rxqual > 7) {
					sprintf(buf, "*%d*, ", cells[i].rxqual);
					ret = UT_FAIL;
				} else {
					sprintf(buf, "%d, ", cells[i].rxqual);
				}

				strcat(text, buf);
			}

			strcpy(&text[strlen(text) - 2], "\n");
		}
		
		return ret;
	}
	
	return UT_NOT_SUPPORT;
}

#define CASE_DC_REASON(text, reason)	case reason: strcpy(text, #reason); break;

int test_two_g_get_dc_reason(char *text) {
	int reason;

	if (two_g_get_dc_reason(&reason) == 0) {
		switch (reason) {
		CASE_DC_REASON(text, DC_REASON_DISCONNECT_BY_USER);
		CASE_DC_REASON(text, DC_REASON_DISCONNECT_BY_BS);
		CASE_DC_REASON(text, DC_REASON_SYNCHRONIZATION_LOST);
		CASE_DC_REASON(text, DC_REASON_NO_CIRCUIT_OR_CHANNEL_AVAILABLE);
		CASE_DC_REASON(text, DC_REASON_NETWORK_ENTRY_FAILURE);
		CASE_DC_REASON(text, DC_REASON_AUTHENTICATION_FAILURE);
		CASE_DC_REASON(text, DC_REASON_USER_SUSPEND_NETWORK_ENTRY);
		CASE_DC_REASON(text, DC_REASON_HANDOVER_FAILURE);
		CASE_DC_REASON(text, DC_REASON_MISC_FAILURE);

		default:
			sprintf(text, "*%d*", reason);
			return UT_FAIL;
		}

		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int main() {
	struct test_suite *p_suite;
	struct test_suite *p_sub_suite;
	
	p_suite = create_test_suite("2G", 1);
	   
    p_sub_suite = create_test_suite("Device", 1);
    add_test(p_sub_suite,   "Supported Frequency Bands",    5,    test_two_g_get_supp_freq_bands);
    add_test_suite(p_suite, p_sub_suite);
    
    p_sub_suite = create_test_suite("Network Entry", 1);
    add_test(p_sub_suite,   "IP Address",                   5,    test_two_g_get_ip_addr);
    add_test(p_sub_suite,   "Working Mode",                 5,    test_two_g_get_work_mode);
    add_test(p_sub_suite,   "CI",                           5,    test_two_g_get_ci);
    add_test(p_sub_suite,   "MCC",                          5,    test_two_g_get_mcc);
    add_test(p_sub_suite,   "MNC",                          5,    test_two_g_get_mnc);
    add_test(p_sub_suite,   "LAC",                          5,    test_two_g_get_lac);
    add_test(p_sub_suite,   "Network Entry Latency",        5,    test_two_g_get_net_entry_latency);
    add_test(p_sub_suite,   "Disconnection Reason",         5,    test_two_g_get_dc_reason);
    add_test(p_sub_suite,   "Neighboring Cells",            5,    test_two_g_get_ngbr_cells);
    add_test_suite(p_suite, p_sub_suite);
    
    p_sub_suite = create_test_suite("Performance", 1);
    add_test(p_sub_suite,   "RSSI",                         5,    test_two_g_get_rssi);
    add_test(p_sub_suite,   "RXQUAL",                       5,    test_two_g_get_rxqual);
    add_test(p_sub_suite,   "Handover Latency",             5,    test_two_g_get_handover_latency);
    add_test(p_sub_suite,   "Handover Success Count",       5,    test_two_g_get_handover_success_cnt);
    add_test(p_sub_suite,   "Handover Failure Count",       5,    test_two_g_get_handover_fail_cnt);
    add_test(p_sub_suite,   "Uplink Modulation Scheme",     5,    test_two_g_get_ul_mcs);
    add_test(p_sub_suite,   "Downlink Modulation Scheme",   5,    test_two_g_get_dl_mcs);
    add_test(p_sub_suite,   "ARFCN",                        5,    test_two_g_get_arfcn);
    add_test(p_sub_suite,   "TX Power",                     5,    test_two_g_get_tx_power);
    add_test(p_sub_suite,   "TX Byte",                      5,    test_two_g_get_tx_byte);
    add_test(p_sub_suite,   "TX Packet Count",              5,    test_two_g_get_tx_packet_cnt);
    add_test(p_sub_suite,   "TX Packet Error Count",        5,    test_two_g_get_tx_packet_err_cnt);
    add_test(p_sub_suite,   "TX Frame Count",               5,    test_two_g_get_tx_frame_cnt);
    add_test(p_sub_suite,   "TX Frame Error Count",         5,    test_two_g_get_tx_frame_err_cnt);
    add_test(p_sub_suite,   "RX Byte",                      5,    test_two_g_get_rx_byte);
    add_test(p_sub_suite,   "RX Packet Count",              5,    test_two_g_get_rx_packet_cnt);
    add_test(p_sub_suite,   "RX Packet Error Count",        5,    test_two_g_get_rx_packet_err_cnt);
    add_test(p_sub_suite,   "RX Frame Count",               5,    test_two_g_get_rx_frame_cnt);
    add_test(p_sub_suite,   "RX Frame Error Count",         5,    test_two_g_get_rx_frame_err_cnt);
    add_test_suite(p_suite, p_sub_suite);
	
	run_test_suite(p_suite);
	delete_test_suite(p_suite);
	return 0;
}
