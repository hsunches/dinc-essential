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
#include "data_wifi_ap.h"

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
int wifi_ap_get_country_code(char code[2]) {

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
 *                    bit[5:31] - reserved.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_ap_get_supp_freqs(int *p_freqs) {

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
int wifi_ap_get_supp_modes(int *p_modes) {

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
int wifi_ap_get_supp_encrypts(int *p_encrypts) {

#ifdef SAMPLE_CODE
    *p_encrypts = WIFI_ENCRYPT_WEP | WIFI_ENCRYPT_WPA | WIFI_ENCRYPT_WPA2;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the working frequencies.
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
int wifi_ap_get_work_freqs(int *p_freqs) {

#ifdef SAMPLE_CODE
    *p_freqs = WIFI_FREQ_2_4G;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the working modes.
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
int wifi_ap_get_work_modes(int *p_modes) {

#ifdef SAMPLE_CODE
    *p_modes = WIFI_MODE_N;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the working channels.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The channel count is up to MAX_WIFI_CH_CNT.
 *
 *                    The channel range is 1 ~ 196.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_ap_get_work_chs(int chs[MAX_WIFI_CH_CNT], int *p_cnt) {

#ifdef SAMPLE_CODE
    chs[0] = 11;
    *p_cnt = 1;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the SSID configurations.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The SSID count is up to MAX_WIFI_SSID_CNT.
 *
 *                    The SSID length is 1 ~ MAX_WIFI_SSID_LEN.
 *
 *                    Assign WIFI_ENCRYPT_* to encrypt field of ssid_cfg structure.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_ap_get_ssid_cfgs(struct wifi_ssid_cfg cfgs[MAX_WIFI_SSID_CNT], int *p_cnt) {

#ifdef SAMPLE_CODE
    strcpy(cfgs[0].ssid, "ssid-0");
    cfgs[0].encrypt = WIFI_ENCRYPT_WPA;
    
    strcpy(cfgs[1].ssid, "ssid-1");
    cfgs[1].encrypt = WIFI_ENCRYPT_WPA2;
    
    *p_cnt = 2;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the IP addrress.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : Text Format. Only accept [0-9], [A-F], [a-f], [.], [:].
 *
 *                    For an IPv4 address, the string length should not exceed 15.
 *
 *                    For an IPv6 address, the string length should not exceed 39.
 *
 * Reference        : 
 *
 * Remarks          : Accept only numeric format for IPv4.
 *
 */
int wifi_ap_get_ip_addr(char ip_addr[40]) {

#ifdef SAMPLE_CODE
    strcpy(ip_addr, "123.123.123.123");
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the information of clients.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The client count is up to MAX_WIFI_CLIENT_CNT
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_ap_get_clients(struct wifi_client clients[MAX_WIFI_CLIENT_CNT], int *p_cnt) {

#ifdef SAMPLE_CODE
    uint8_t bssid[] = {
        0x12,
        0x23,
        0x12,
        0x23,
        0x12,
        0x23
    };
    
    memcpy(clients[0].bssid, bssid, sizeof(bssid));
    memcpy(clients[1].bssid, bssid, sizeof(bssid));
    *p_cnt = 2;
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
int wifi_ap_get_tx_power(int *p_power) {

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
int wifi_ap_get_tx_byte(uint64_t *p_byte) {

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
int wifi_ap_get_tx_fragment_success_cnt(uint64_t *p_cnt) {

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
int wifi_ap_get_tx_frame_retry_cnt(uint64_t *p_cnt) {

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

int wifi_ap_get_tx_ack_loss_cnt(uint64_t *p_cnt) {

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
int wifi_ap_get_rx_byte(uint64_t *p_byte) {

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
int wifi_ap_get_rx_fragment_success_cnt(uint64_t *p_cnt) {

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
int wifi_ap_get_rx_frame_fcs_err_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 547;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get all neighboring WiFi informations.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The NIF count is up to MAX_NEIGHBOR_WIFI_CNT.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int wifi_ap_get_ngbr_infos(struct wifi_ap ngbr_aps[MAX_NEIGHBOR_WIFI_CNT], int *p_cnt) {

#ifdef SAMPLE_CODE
    uint8_t bssid[] = {
        0x12,
        0x23,
        0x12,
        0x23,
        0x12,
        0x23
    };
    
    memcpy(ngbr_aps[0].bssid, bssid, sizeof(bssid));
    ngbr_aps[0].mode = WIFI_MODE_N;
    ngbr_aps[0].encrypt = WIFI_ENCRYPT_WPA2;
    ngbr_aps[0].ch = 1;
    ngbr_aps[0].rssi = -32;
    
    memcpy(ngbr_aps[1].bssid, bssid, sizeof(bssid));
    ngbr_aps[1].mode = WIFI_MODE_N;
    ngbr_aps[1].encrypt = WIFI_ENCRYPT_WPA2;
    ngbr_aps[1].ch = 1;
    ngbr_aps[1].rssi = -41;
    
    *p_cnt = 2;
    return 0;

#else

#endif
    return -1;
}