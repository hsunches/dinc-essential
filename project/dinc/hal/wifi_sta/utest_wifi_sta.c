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
#include <ctype.h>
#include <limits.h>
#include "ut_util.h"
#include "data_wifi_sta.h"

int test_freq(char *text, int freq) {
	switch (freq) {
	case WIFI_FREQ_2_4G:
		strcpy(text, "2.4 GHz");
		break;

	case WIFI_FREQ_3_6G:
		strcpy(text, "3.6 GHz");
		break;

	case WIFI_FREQ_4_9G:
		strcpy(text, "4.9 GHz");
		break;

	case WIFI_FREQ_5G:
		strcpy(text, "5 GHz");
		break;

	case WIFI_FREQ_60G:
		strcpy(text, "60 GHz");
		break;

	default:
		sprintf(text, "*%d*", freq);
		return UT_FAIL;
	}

	return UT_PASS;
}

int test_mode(char *text, int mode) {
	switch (mode) {
	case WIFI_MODE_A:
		strcpy(text, "802.11a");
		break;

	case WIFI_MODE_B:
		strcpy(text, "802.11b");
		break;

	case WIFI_MODE_G:
		strcpy(text, "802.11g");
		break;

	case WIFI_MODE_N:
		strcpy(text, "802.11n");
		break;

	case WIFI_MODE_AC:
		strcpy(text, "802.11ac");
		break;

	case WIFI_MODE_AD:
		strcpy(text, "802.11ad");
		break;

	default:
		sprintf(text, "*%d*, ", mode);
		return UT_FAIL;
	}

	return UT_PASS;
}

int test_encrypt(char *text, int encrypt) {
	switch (encrypt) {
	case WIFI_ENCRYPT_WEP:
		strcpy(text, "WEP");
		break;

	case WIFI_ENCRYPT_WPA:
		strcpy(text, "WPA");
		break;

	case WIFI_ENCRYPT_WPA2:
		strcpy(text, "WPA2");
		break;

	default:
		sprintf(text, "*%d*, ", encrypt);
		return UT_FAIL;
	}

	return UT_PASS;
}

int test_freqs(char *text, int freqs) {
	int ret = UT_PASS;
	int mask = 1;
	int i;
	char buf[32];

	*text = 0;

	for (i = 0; i < sizeof(int) * 8; i++) {
		int freq = freqs & mask;

		if (freq) {
			if (test_freq(buf, freq) == UT_FAIL) {
				ret = UT_FAIL;
			}

			strcat(text, buf);
			strcat(text, ", ");
		}

		mask <<= 1;
	}

	if (*text == 0) {
		strcpy(text, "*No Frequency Specified*");
		return UT_FAIL;
	}
	
	text[strlen(text) - 2] = 0;
	return ret;
}

int test_modes(char *text, int modes) {
	int ret = UT_PASS;
	int mask = 1;
	int i;
	char buf[32];

	*text = 0;

	for (i = 0; i < sizeof(int) * 8; i++) {
		int mode = modes & mask;

		if (mode) {
			if (test_mode(buf, mode) == UT_FAIL) {
				ret = UT_FAIL;
			}

			strcat(text, buf);
			strcat(text, ", ");
		}

		mask <<= 1;
	}

	if (*text == 0) {
		strcpy(text, "*No Mode Specified*");
		return UT_FAIL;
	}

	text[strlen(text) - 2] = 0;
	return ret;
}

int test_encrypts(char *text, int encrypts) {
	int ret = UT_PASS;
	int mask = 1;
	int i;
	char buf[32];

	*text = 0;

	for (i = 0; i < sizeof(int) * 8; i++) {
		int encrypt = encrypts & mask;

		if (encrypt) {
			if (test_encrypt(buf, encrypt) == UT_FAIL) {
				ret = UT_FAIL;
			}

			strcat(text, buf);
			strcat(text, ", ");
		}

		mask <<= 1;
	}

	if (*text == 0) {
		strcpy(text, "None");
	} else {
		text[strlen(text) - 2] = 0;
	}

	return ret;
}

MAKE_TEST_FUNC_INT(wifi_sta_get_work_ch, 1, 196);
MAKE_TEST_FUNC_STR(wifi_sta_get_ssid, MAX_WIFI_SSID_LEN);
MAKE_TEST_FUNC_INT(wifi_sta_get_rssi, -128, 127);
MAKE_TEST_FUNC_INT(wifi_sta_get_tx_power, -128, 127);
MAKE_TEST_FUNC_UINT64(wifi_sta_get_tx_byte, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_sta_get_tx_fragment_success_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_sta_get_tx_frame_retry_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_sta_get_tx_ack_loss_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_sta_get_rx_byte, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_sta_get_rx_fragment_success_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_sta_get_rx_frame_fcs_err_cnt, 0, ~0ULL);

int test_wifi_sta_get_country_code(char *text) {
	char code[2];
	
	if (wifi_sta_get_country_code(code) == 0) {
		if (!isalpha(code[0]) || !isalpha(code[1])) {
			sprintf(text, "*%.2s*", code);
			return UT_FAIL;
		}

		sprintf(text, "%.2s", code);
		return UT_PASS;
	}
	
	return UT_NOT_SUPPORT;
}

int test_wifi_sta_get_supp_freqs(char *text) {
	int freqs;

	if (wifi_sta_get_supp_freqs(&freqs) == 0) {
		return test_freqs(text, freqs);
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_sta_get_supp_modes(char *text) {
	int modes;

	if (wifi_sta_get_supp_modes(&modes) == 0) {
		return test_modes(text, modes);
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_sta_get_supp_encrypts(char *text) {
	int encrypts;

	if (wifi_sta_get_supp_encrypts(&encrypts) == 0) {
		return test_encrypts(text, encrypts);
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_sta_get_work_freq(char *text) {
	int freq;

	if (wifi_sta_get_work_freq(&freq) == 0) {
		return test_freq(text, freq);
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_sta_get_work_mode(char *text) {
	int mode;

	if (wifi_sta_get_work_mode(&mode) == 0) {
		return test_mode(text, mode);
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_sta_get_work_encrypt(char *text) {
	int encrypt;

	if (wifi_sta_get_work_encrypt(&encrypt) == 0) {
		return test_encrypt(text, encrypt);
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_sta_get_ngbr_aps(char *text) {
	struct wifi_ap aps[MAX_WIFI_AP_CNT];
	int cnt;
	int i;

	for (i = 0; i < MAX_WIFI_AP_CNT; i++) {
		aps[i].mode = -1;
		aps[i].encrypt = -1;
		aps[i].ch = -1;
		aps[i].rssi = INT_MAX;
	}
	
	if (wifi_sta_get_ngbr_aps(aps, &cnt) == 0) {
		char buf[32];
		int ret;
		int result;

		sprintf(text, "Count: %d", cnt);
		
		if (cnt < 0 || cnt > MAX_WIFI_AP_CNT) {
			return UT_FAIL;
		}

		ret = UT_PASS;
		*text = 0;
		
		for (i = 0; i < cnt; i++) {
			strcat(text, "BSSID: ");

			if (memcmp(aps[i].bssid, "\xFF\xFF\xFF\xFF\xFF\xFF", sizeof(aps[i].bssid)) == 0) {
				strcat(text, "*FF:FF:FF:FF:FF:FF*");
				ret = UT_FAIL;
			} else {
				sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X",
					aps[i].bssid[0],
					aps[i].bssid[1],
					aps[i].bssid[2],
					aps[i].bssid[3],
					aps[i].bssid[4],
					aps[i].bssid[5]
				);

				strcat(text, buf);
			}

			if (aps[i].mode != -1) {
				strcat(text, ", Mode: ");

				result = test_modes(buf, aps[i].mode);

				if (result == UT_FAIL) {
					ret = UT_FAIL;
				}

				strcat(text, buf);
			}
			
			if (aps[i].encrypt != -1) {
				strcat(text, ", Encryption: ");

				result = test_encrypts(buf, aps[i].encrypt);

				if (result == UT_FAIL) {
					ret = UT_FAIL;
				}

				strcat(text, buf);
			}
			
			if (aps[i].ch != -1) {
				strcat(text, ", Channel: ");

				if (aps[i].ch < 1 || aps[i].ch > 196) {
					sprintf(buf, "*%d*", aps[i].ch);
					ret = UT_FAIL;
				} else {
					sprintf(buf, "%d", aps[i].ch);
				}

				strcat(text, buf);

			}

			if (aps[i].rssi != INT_MAX) {
				strcat(text, ", RSSI: ");

				if (aps[i].rssi < -128 || aps[i].rssi > 127) {
					sprintf(buf, "*%d*", aps[i].rssi);
					ret = UT_FAIL;
				} else {
					sprintf(buf, "%d", aps[i].rssi);
				}

				strcat(text, buf);
			}

			strcat(text, "\n");
		}
	
		return ret;
	}
	
	return UT_NOT_SUPPORT;
}

int test_wifi_sta_get_sta_bssid(char *text) {
	uint8_t bssid[6];
	
	if (wifi_sta_get_sta_bssid(bssid) == 0) {
		if (memcmp(bssid, "\xFF\xFF\xFF\xFF\xFF\xFF", sizeof(bssid)) == 0) {
			strcpy(text, "*FF:FF:FF:FF:FF:FF*\n");
			return UT_FAIL;
		}

		sprintf(text, "%02X:%02X:%02X:%02X:%02X:%02X\n",
			bssid[0],
			bssid[1],
			bssid[2],
			bssid[3],
			bssid[4],
			bssid[5]
		);

		return UT_PASS;
	}
	
	return UT_NOT_SUPPORT;
}

int main() {
    struct test_suite *p_suite;
    struct test_suite *p_sub_suite;
    
	p_suite = create_test_suite("Wi-Fi AP", 1);
	
	p_sub_suite = create_test_suite("Device", 1);
	add_test(p_sub_suite,	"Country Code",						5,	test_wifi_sta_get_country_code);
	add_test(p_sub_suite,	"Supported Frequencies",			5,	test_wifi_sta_get_supp_freqs);
	add_test(p_sub_suite,	"Supported Modes",					5,	test_wifi_sta_get_supp_modes);
	add_test(p_sub_suite,	"Supported Encryptions",			5,	test_wifi_sta_get_supp_encrypts);
	add_test_suite(p_suite, p_sub_suite);
	
	p_sub_suite = create_test_suite("Network Entry", 1);
	add_test(p_sub_suite,	"Working Frequency",				5,	test_wifi_sta_get_work_freq);
	add_test(p_sub_suite,	"Working Channel",					5,	test_wifi_sta_get_work_ch);
	add_test(p_sub_suite,	"Working Mode",						5,	test_wifi_sta_get_work_mode);
	add_test(p_sub_suite,	"Working Encryption",				5,	test_wifi_sta_get_work_encrypt);
	add_test(p_sub_suite,	"Neighboring APs",					5,	test_wifi_sta_get_ngbr_aps);
	add_test(p_sub_suite,	"AP BSSID",							5,	test_wifi_sta_get_sta_bssid);
	add_test(p_sub_suite,	"SSID",								5,	test_wifi_sta_get_ssid);
	add_test(p_sub_suite,	"RSSI",								5,	test_wifi_sta_get_rssi);
	add_test_suite(p_suite, p_sub_suite);
	
	p_sub_suite = create_test_suite("Performance", 1);
	add_test(p_sub_suite,	"Tx Power",							5,	test_wifi_sta_get_tx_power);
	add_test(p_sub_suite,	"Tx Byte",							5,	test_wifi_sta_get_tx_byte);
	add_test(p_sub_suite,	"Tx Fragment Success Count",		5,	test_wifi_sta_get_tx_fragment_success_cnt);
	add_test(p_sub_suite,	"Tx Frame Retry Count",				5,	test_wifi_sta_get_tx_frame_retry_cnt);
	add_test(p_sub_suite,	"Tx ACK Loss Count",				5,	test_wifi_sta_get_tx_ack_loss_cnt);
	add_test(p_sub_suite,	"Rx Byte",							5,	test_wifi_sta_get_rx_byte);
	add_test(p_sub_suite,	"Rx Fragment Success Count",		5,	test_wifi_sta_get_rx_fragment_success_cnt);
	add_test(p_sub_suite,	"Rx Frame FCS Error Count",			5,	test_wifi_sta_get_rx_frame_fcs_err_cnt);
	add_test_suite(p_suite, p_sub_suite);
	
	run_test_suite(p_suite);
	delete_test_suite(p_suite);
	return 0;
}

