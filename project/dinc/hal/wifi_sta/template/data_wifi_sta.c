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
#include <string.h>
#include "data_wifi_sta.h"

/*
 * Description      : Get the country code from the Wi-Fi settings.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 
 *
 * Reference        : ISO 3166-1 alpha-2
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_country_code(char code[2]) {

#ifdef SAMPLE_CODE
	strncpy(code, "TW", 2);
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the supported frequencies.
 *
 *                    Use the combination of WIFI_FREQ_* to assign the value.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : bit[0]    - 2.4 GHz
 *
 *                    bit[1]    - 3.6 GHz
 *
 *                    bit[2]    - 4.9 GHz
 *
 *                    bit[3]    -   5 GHz
 *
 *                    bit[4]    -  60 GHz
 *
 *                    bit[5:31] - 3.6 GHz
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_supp_freqs(int *p_freqs) {

#ifdef SAMPLE_CODE
	*p_freqs = WIFI_FREQ_2_4G | WIFI_FREQ_5G;
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the supported modes.
 *
 *                    Use the combination of WIFI_MODE_* to assign the value.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : bit[0]    - 802.11a
 *
 *                    bit[1]    - 802.11b
 *
 *                    bit[2]    - 802.11g
 *
 *                    bit[3]    - 802.11n
 *
 *                    bit[4]    - 802.11ac
 *
 *                    bit[5]    - 802.11ad
 *
 *                    bit[6:31] - reserved.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_supp_modes(int *p_modes) {

#ifdef SAMPLE_CODE
	*p_modes = WIFI_MODE_B | WIFI_MODE_G | WIFI_MODE_N;
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the supported encryptions.
 *
 *                    Use the combination of WIFI_ENCRYPT_* to assign the value.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : bit[0]    - WEP
 *
 *                    bit[1]    - WPA
 *
 *                    bit[2]    - WPA2
 *
 *                    bit[3:31] - reserved.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_supp_encrypts(int *p_encrypts) {

#ifdef SAMPLE_CODE
	*p_encrypts = WIFI_ENCRYPT_WEP | WIFI_ENCRYPT_WPA | WIFI_ENCRYPT_WPA2;
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the working frequency.
 *
 *                    Use the macro WIFI_FREQ_* to assign the value.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : bit[0]    - 2.4 GHz
 *
 *                    bit[1]    - 3.6 GHz
 *
 *                    bit[2]    - 4.9 GHz
 *
 *                    bit[3]    -   5 GHz
 *
 *                    bit[4]    -  60 GHz
 *
 *                    bit[5:31] - reserved
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_work_freq(int *p_freq) {

#ifdef SAMPLE_CODE
	*p_freq = WIFI_FREQ_2_4G;
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the working mode.
 *
 *                    Use the macro WIFI_MODE_* to assign the value.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : bit[0]    - 802.11a
 *
 *                    bit[1]    - 802.11b
 *
 *                    bit[2]    - 802.11g
 *
 *                    bit[3]    - 802.11n
 *
 *                    bit[4]    - 802.11ac
 *
 *                    bit[5]    - 802.11ad
 *
 *                    bit[6:31] - reserved.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_work_mode(int *p_mode) {

#ifdef SAMPLE_CODE
	*p_mode = WIFI_MODE_N;
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the working encryption.
 *
 *                    Use the macro WIFI_ENCRYPT_* to assign the value.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : bit[0]    - WEP
 *
 *                    bit[1]    - WPA
 *
 *                    bit[2]    - WPA2
 *
 *                    bit[3:31] - reserved.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_work_encrypt(int *p_encrypt) {

#ifdef SAMPLE_CODE
	*p_encrypt = WIFI_ENCRYPT_WPA2;
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the working channel.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 1 ~ 196
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_work_ch(int *p_ch) {

#ifdef SAMPLE_CODE
	*p_ch = 1;
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the information of APs.
 *
 *                    If some fields (except BSSID) defined in the wifi_ap structure are unavailable, leave them unchanged and still return 0.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The AP count is up to MAX_WIFI_AP_CNT
 *
 * Reference        : For working encryption, use the macro WIFI_ENCRYPT_* to assign the value.
 *
 *                    For working mode, use the macro WIFI_MODE_* to assign the value.
 *
 *                    For working channel, the range is 1 ~ 196.
 *
 *                    For RSSI, the range is -128 ~ 127 in dBm.
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_ngbr_aps(struct wifi_ap aps[], int *p_cnt) {

#ifdef SAMPLE_CODE
	uint8_t bssid[] = {
		0x12,
		0x23,
		0x12,
		0x23,
		0x12,
		0x23
	};
	
	memcpy(aps[0].bssid, bssid, sizeof(bssid));
	aps[0].mode = WIFI_MODE_N;
	aps[0].encrypt = WIFI_ENCRYPT_WPA2;
	aps[0].ch = 1;
	aps[0].rssi = -32;
	
	memcpy(aps[1].bssid, bssid, sizeof(bssid));
	aps[1].mode = WIFI_MODE_N;
	aps[1].encrypt = WIFI_ENCRYPT_WPA2;
	aps[1].ch = 1;
	aps[1].rssi = -41;
	
	*p_cnt = 2;
	return 0;

#else

#endif
	return -1;
}

/*
 * Description      : Get the BSSID of the connected AP.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_sta_bssid(uint8_t bssid[6]) {

#ifdef SAMPLE_CODE
	uint8_t fake_bssid[] = {
		0x12,
		0x23,
		0x12,
		0x23,
		0x12,
		0x23
	};
	
	memcpy(bssid, fake_bssid, sizeof(fake_bssid));
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the connected SSID.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The string length is 1 ~ MAX_WIFI_SSID_LEN
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_ssid(char ssid[MAX_WIFI_SSID_LEN + 1]) {

#ifdef SAMPLE_CODE
	strcpy(ssid, "mobric");
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the RSSI in dBm.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : -128 ~ 127
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_rssi(int *p_rssi) {

#ifdef SAMPLE_CODE
	*p_rssi = -32;
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the TX power in dBm.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : -128 ~ 127
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_tx_power(int *p_power) {

#ifdef SAMPLE_CODE
	*p_power = -30;
	return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the TX byte count since booting up.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ (2^64 - 1)
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_tx_byte(uint64_t *p_byte) {

#ifdef SAMPLE_CODE
    *p_byte = 1236561;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the TX fragment success count since booting up.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ (2^64 - 1)
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_tx_fragment_success_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 5475;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the TX frame retry count since booting up.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ (2^64 - 1)
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_tx_frame_retry_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 252;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the TX ACK loss count since booting up.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ (2^64 - 1)
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */

int wifi_sta_get_tx_ack_loss_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 65;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the RX byte count since booting up.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ (2^64 - 1)
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_rx_byte(uint64_t *p_byte) {

#ifdef SAMPLE_CODE
    *p_byte = 1342365;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the RX fragment success count since booting up.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ (2^64 - 1)
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_rx_fragment_success_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 12163;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the RX frame FCS error count since booting up.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ (2^64 - 1)
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_sta_get_rx_frame_fcs_err_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 547;
    return 0;

#else

#endif
    return -1;
}

