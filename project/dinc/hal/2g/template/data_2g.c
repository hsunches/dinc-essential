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
#include "data_2g.h"
#include "msg_hal.h"

#define MAP_FREQ_BAND(band) (1LL << (band - 1))

/*
 * Description      : Get the supported frequency bands.
 *
 *                    Use the macro MAP_FREQ_BAND() and pre-defind 14 bands (TWO_G_BAND_*) to assign the value.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : bit[00:13] - representing frequency band 1 to 14.
 *
 *                    bit[14:15] - reserved.
 *
 * Reference        : 3GPP TS 45.005
 *
 * Remarks          : 
 *
 */
int two_g_get_supp_freq_bands(int *p_bands) {

#ifdef SAMPLE_CODE
    *p_bands = MAP_FREQ_BAND(TWO_G_BAND_P_GSM_900) | MAP_FREQ_BAND(TWO_G_BAND_DCS_1800);
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
int two_g_get_ip_addr(char ip_addr[40]) {

#ifdef SAMPLE_CODE
    strcpy(ip_addr, "123.123.123.123");
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the working mode.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : TWO_G_WORK_MODE_GPRS / TWO_G_WORK_MODE_EDGE
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_work_mode(int *p_mode) {

#ifdef SAMPLE_CODE
    *p_mode = TWO_G_WORK_MODE_EDGE;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get latency in milliseconds when UE enters the 2.xG network.
 *
 *                    If the API doesn't support, get the time elapsed between UE connection request and bearer response returned.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 65535
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_net_entry_latency(int *p_latency) {

#ifdef SAMPLE_CODE
    *p_latency = 100;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the CI (cell identity) of the base station UE is camping on.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 65535
 *
 * Reference        : 3GPP TS 23.003
 *
 * Remarks          : 
 *
 */
int two_g_get_ci(int *p_ci) {

#ifdef SAMPLE_CODE
    *p_ci = 28458;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the reading of RSSI (received signal strength indication) in dBm.
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
int two_g_get_rssi(int *p_rssi) {

#ifdef SAMPLE_CODE
    *p_rssi = -40;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the reading of RXQUAL (received signal quality).
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 (best) ~ 7 (worst)
 *
 * Reference        : 3GPP TS 45.008
 *
 * Remarks          : 
 *
 */
int two_g_get_rxqual(int *p_rxqual) {

#ifdef SAMPLE_CODE
    *p_rxqual = 1;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the current ARFCN (absolute radio-frequency channel number).
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 1023
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_arfcn(int *p_arfcn) {

#ifdef SAMPLE_CODE
    *p_arfcn = 60;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the MCC (mobile country code) of current PLMN (public land mobile network)
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 999
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_mcc(int *p_mcc) {

#ifdef SAMPLE_CODE
    *p_mcc = 466;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the MNC (mobile network code) of current PLMN.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : A null-terminated string that consists of 2/3 digits.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_mnc(char mnc[4]) {

#ifdef SAMPLE_CODE
    strcpy(mnc, "11");
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the LAC (location area code).
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 1 ~ 65533 and 65535
 *
 * Reference        : 3GPP TS 23.003
 *
 * Remarks          : 
 *
 */
int two_g_get_lac(int *p_lac) {

#ifdef SAMPLE_CODE
    *p_lac = 10302;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get handover latency in milliseconds.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 65535
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_handover_latency(int *p_latency) {

#ifdef SAMPLE_CODE
    *p_latency = 100;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the handover success count since booting up or network entry.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 255
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_handover_success_cnt(int *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 7;
    return 0;

#else

#endif
    return -1;
}

 /*
 * Description      : Get the handover failure count since booting up or network entry.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 255
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_handover_fail_cnt(int *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 1;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the uplink modulation scheme.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : MCS_TYPE_GMSK / MCS_TYPE_8PSK
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_ul_mcs(int *p_mcs) {

#ifdef SAMPLE_CODE
    *p_mcs = MCS_TYPE_8PSK;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the downlink modulation scheme.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : MCS_TYPE_GMSK / MCS_TYPE_8PSK
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_dl_mcs(int *p_mcs) {

#ifdef SAMPLE_CODE
    *p_mcs = MCS_TYPE_8PSK;
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
int two_g_get_tx_power(int *p_power) {

#ifdef SAMPLE_CODE
    *p_power = -20;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the TX byte count at MAC layer since booting up or network entry.
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
int two_g_get_tx_byte(uint64_t *p_byte) {

#ifdef SAMPLE_CODE
    *p_byte = 783462;
    return 0;

#else
    return -1;

#endif

}

/*
 * Description      : Get the TX packet count at IP layer since booting up or network entry.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ (2^64 -1)
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_tx_packet_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 532;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the TX packet error count at IP layer since booting up or network entry.
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
int two_g_get_tx_packet_err_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 85;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the TX frame count at MAC layer since booting up or network entry.
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
int two_g_get_tx_frame_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 9765;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the TX frame error count at MAC layer since booting up or network entry.
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
int two_g_get_tx_frame_err_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 94;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the RX byte count at MAC layer since booting up or network entry.
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
int two_g_get_rx_byte(uint64_t *p_byte) {

#ifdef SAMPLE_CODE
    *p_byte = 8584575;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the RX packet count at IP layer since booting up or network entry.
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
int two_g_get_rx_packet_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 967;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the RX packet error count at IP layer since booting up or network entry.
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
int two_g_get_rx_packet_err_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 5;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the RX frame count at MAC layer since booting up or network entry.
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
int two_g_get_rx_frame_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 69335;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the RX frame error count at IP layer since booting up or network entry.
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
int two_g_get_rx_frame_err_cnt(uint64_t *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 61;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the last disconnection reason.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : DC_REASON_*
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_dc_reason(int *p_reason) {

#ifdef SAMPLE_CODE
    *p_reason = DC_REASON_DISCONNECT_BY_USER;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the information of the neighboring cells.
 *
 *                    If some fields (except CI) defined in the two_g_cell structure are unavailable, leave them unchanged and still return 0.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The cell count is up to MAX_TWO_G_NGBR_CELL_CNT.
 *
 *                    For CI, the range is 0 ~ 65535.
 *
 *                    For MCC, the range is 0 ~ 999.
 *
 *                    For MNC, fill a null-terminated string consist of 2/3 digits.
 *
 *                    For LAC, the range is 0 ~ 65535.
 *
 *                    For RSSI, the range is -128 ~ 127 in dBm.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int two_g_get_ngbr_cells(struct two_g_cell cells[MAX_TWO_G_NGBR_CELL_CNT], int *p_cnt) {

#ifdef SAMPLE_CODE
    cells[0].ci = 28458;
    cells[0].mcc = 466;
    strcpy(cells[0].mnc, "11");
    cells[0].lac = 10302;
    cells[0].rssi = -30;
    cells[0].rxqual = 2;

    cells[1].ci = 28460;
    cells[1].mcc = 466;
    strcpy(cells[1].mnc, "11");
    cells[1].lac = 10302;
    cells[1].rssi = -40;
    cells[1].rxqual = 4;
    
    *p_cnt = 2;
    return 0;

#else

#endif
    return -1;
}
