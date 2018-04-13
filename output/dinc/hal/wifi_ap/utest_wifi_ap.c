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
#include <arpa/inet.h>
#include "ut_util.h"
#include "data_wifi_ap.h"

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

MAKE_TEST_FUNC_INT(wifi_ap_get_tx_power, -128, 127);
MAKE_TEST_FUNC_UINT64(wifi_ap_get_tx_byte, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_ap_get_tx_fragment_success_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_ap_get_tx_frame_retry_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_ap_get_tx_ack_loss_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_ap_get_rx_byte, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_ap_get_rx_fragment_success_cnt, 0, ~0ULL);
MAKE_TEST_FUNC_UINT64(wifi_ap_get_rx_frame_fcs_err_cnt, 0, ~0ULL);

int test_wifi_ap_get_country_code(char *text) {
	char code[2];
	
	if (wifi_ap_get_country_code(code) == 0) {
		if (!isalpha(code[0]) || !isalpha(code[1])) {
			sprintf(text, "*%.2s*", code);
			return UT_FAIL;
		}

		sprintf(text, "%.2s", code);
		return UT_PASS;
	}
	
	return UT_NOT_SUPPORT;
}

int test_wifi_ap_get_supp_freqs(char *text) {
	int freqs;

	if (wifi_ap_get_supp_freqs(&freqs) == 0) {
		return test_freqs(text, freqs);
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_ap_get_supp_modes(char *text) {
	int modes;

	if (wifi_ap_get_supp_modes(&modes) == 0) {
		return test_modes(text, modes);
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_ap_get_supp_encrypts(char *text) {
	int encrypts;

	if (wifi_ap_get_supp_encrypts(&encrypts) == 0) {
		return test_encrypts(text, encrypts);
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_ap_get_work_freqs(char *text) {
	int freqs;

	if (wifi_ap_get_work_freqs(&freqs) == 0) {
		return test_freqs(text, freqs);
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_ap_get_work_chs(char *text) {
	int chs[MAX_WIFI_CH_CNT];
	int cnt;
	int i;

	if (wifi_ap_get_work_chs(chs, &cnt) == 0) {
		char buf[32];
		int ret;

		sprintf(text, "Count: %d\n", cnt);

		if (cnt <= 0 || cnt > MAX_WIFI_CH_CNT) {
			return UT_FAIL;
		}

		ret = UT_PASS;

		for (i = 0; i < cnt; i++) {
			if (chs[i] < 1 || chs[i] > 196) {
				sprintf(buf, "*%d*, ", chs[i]);
				ret = UT_FAIL;
			} else {
				sprintf(buf, "%d, ", chs[i]);
			}

			strcat(text, buf);
		}

		text[strlen(text) - 2] = 0;
		return ret;
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_ap_get_work_modes(char *text) {
	int modes;

	if (wifi_ap_get_work_modes(&modes) == 0) {
		return test_modes(text, modes);
	}

	return UT_NOT_SUPPORT;
}

int test_wifi_ap_get_ssid_cfgs(char *text) {
	struct wifi_ssid_cfg cfgs[MAX_WIFI_SSID_CNT];
	int cnt;
	int i;

	for (i = 0; i < MAX_WIFI_SSID_CNT; i++) {
		cfgs[i].encrypt = -1;
	}
	
	if (wifi_ap_get_ssid_cfgs(cfgs, &cnt) == 0) {
		char buf[64];
		int ret;

		sprintf(text, "Count: %d\n", cnt);

		if (cnt < 0 || cnt > MAX_WIFI_SSID_CNT) {
			return UT_FAIL;
		}

		ret = UT_PASS;
		
		for (i = 0; i < cnt; i++) {
			int ssid_len;
			
			strcat(text, "SSID: ");
			ssid_len = strlen(cfgs[i].ssid);
			
			if (ssid_len == 0 || ssid_len > MAX_WIFI_SSID_LEN) {
				sprintf(buf, "*%s*", cfgs[i].ssid);
				ret = UT_FAIL;
			} else {
				sprintf(buf, "%s", cfgs[i].ssid);
			}

			strcat(text, buf);
			
			if (cfgs[i].encrypt != -1) {
				int result;

				strcat(text, ", Encryption: ");
				result = test_encrypts(buf, cfgs[i].encrypt);

				if (result == UT_FAIL) {
					ret = UT_FAIL;
				}

				strcat(text, buf);
			}

			strcat(text, "\n");
		}
		
		return ret;
	}
	
	return UT_NOT_SUPPORT;
}

int test_wifi_ap_get_ip_addr(char *text) {
	char ip_addr[40];
	
	if (wifi_ap_get_ip_addr(ip_addr) == 0) {
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

int test_wifi_ap_get_clients(char *text) {
	struct wifi_client clients[MAX_WIFI_CLIENT_CNT];
	int cnt;
	
	if (wifi_ap_get_clients(clients, &cnt) == 0) {
		char buf[32];
		int i;

		sprintf(text, "Count: %d\n", cnt);

		if (cnt < 0 || cnt > MAX_WIFI_CLIENT_CNT) {
			return UT_FAIL;
		}

		for (i = 0; i < cnt; i++) {
			sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X, ",
				clients[i].bssid[0],
				clients[i].bssid[1],
				clients[i].bssid[2],
				clients[i].bssid[3],
				clients[i].bssid[4],
				clients[i].bssid[5]
			);

			strcat(text, buf);
		}

		text[strlen(text) - 2] = 0;
		return UT_PASS;
	}
	
	return UT_NOT_SUPPORT;
}

int main() {
	struct test_suite *p_suite;
	struct test_suite *p_sub_suite;
	
	p_suite = create_test_suite("Wi-Fi AP", 1);
	
	p_sub_suite = create_test_suite("Device", 1);
	add_test(p_sub_suite,	"Country Code",						5,	test_wifi_ap_get_country_code);
	add_test(p_sub_suite,	"Supported Frequencies",			5,	test_wifi_ap_get_supp_freqs);
	add_test(p_sub_suite,	"Supported Modes",					5,	test_wifi_ap_get_supp_modes);
	add_test(p_sub_suite,	"Supported Encryptions",			5,	test_wifi_ap_get_supp_encrypts);
	add_test_suite(p_suite, p_sub_suite);
	
	p_sub_suite = create_test_suite("Performance", 1);
	add_test(p_sub_suite,	"Working Frequencies",				5,	test_wifi_ap_get_work_freqs);
	add_test(p_sub_suite,	"Working Channels",					5,	test_wifi_ap_get_work_chs);
	add_test(p_sub_suite,	"Working Modes",					5,	test_wifi_ap_get_work_modes);
	add_test(p_sub_suite,	"SSID Configurations",				5,	test_wifi_ap_get_ssid_cfgs);
	add_test(p_sub_suite,	"WAN IP Address",					5,	test_wifi_ap_get_ip_addr);
	add_test(p_sub_suite,	"Clients",							5,	test_wifi_ap_get_clients);
	add_test(p_sub_suite,	"Tx Power",							5,	test_wifi_ap_get_tx_power);
	add_test(p_sub_suite,	"Tx Byte",							5,	test_wifi_ap_get_tx_byte);
	add_test(p_sub_suite,	"Tx Fragment Success Count",		5,	test_wifi_ap_get_tx_fragment_success_cnt);
	add_test(p_sub_suite,	"Tx Frame Retry Count",				5,	test_wifi_ap_get_tx_frame_retry_cnt);
	add_test(p_sub_suite,	"Tx ACK Loss Count",				5,	test_wifi_ap_get_tx_ack_loss_cnt);
	add_test(p_sub_suite,	"Rx Byte",							5,	test_wifi_ap_get_rx_byte);
	add_test(p_sub_suite,	"Rx Fragment Success Count",		5,	test_wifi_ap_get_rx_fragment_success_cnt);
	add_test(p_sub_suite,	"Rx Frame FCS Error Count",			5,	test_wifi_ap_get_rx_frame_fcs_err_cnt);
	add_test_suite(p_suite, p_sub_suite);
	
	run_test_suite(p_suite);
	delete_test_suite(p_suite);
	return 0;
}
