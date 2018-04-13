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
#include "data_voip.h"

/*
 * Description      : Get the vendor name.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The string length is 1 ~ MAX_VOIP_VENDOR_LEN
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int voip_get_vendor(char vendor[MAX_VOIP_VENDOR_LEN + 1]) {

#ifdef SAMPLE_CODE
    strcpy(vendor, "Mobric");
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the number of the phone sockets.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 1 ~ MAX_VOIP_SOCKET_CNT
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int voip_get_socket_cnt(int *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 2;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the call state of the phone line at given index.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 
 *                       VOIP_CALL_STAT_ONHOOK      // phone hang-up
 *                       VOIP_CALL_STAT_OFFHOOK     // phone pick-up
 *                       VOIP_CALL_STAT_RINGING     // ringing and phone hang-up
 *                       VOIP_CALL_STAT_INCOMING    // phone pick-up + call type is incoming
 *                       VOIP_CALL_STAT_OUTGOING    // phone pick-up + call type is outgoing
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int voip_get_call_stat(int *p_stat, int index) {

#ifdef SAMPLE_CODE
    *p_stat = VOIP_CALL_STAT_OUTGOING;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the termination reason of the last call on phone line at given index.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : VOIP_TERM_REASON_*
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int voip_get_term_reason(int *p_reason, int index) {

#ifdef SAMPLE_CODE
    *p_reason = VOIP_SIP_OK;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the codec type of the current call on the phone line at given index.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : VOIP_CODEC_*
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int voip_get_codec(int *p_codec, int index) {

#ifdef SAMPLE_CODE
    *p_codec = VOIP_CODEC_SPEEX;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the IP addrress of the other side on the phone line at given index.
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
int voip_get_remote_ip_addr(char ip_addr[40], int index) {

#ifdef SAMPLE_CODE
    strcpy(ip_addr, "123.123.123.123");
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the port of the other side on the phone line at given index.
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
int voip_get_remote_port(int *p_port, int index) {

#ifdef SAMPLE_CODE
    *p_port = 5234;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the round trip time in milliseconds of the current call on the phone line at given index.
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
int voip_get_round_trip_time(int *p_time, int index) {

#ifdef SAMPLE_CODE
    *p_time = 763;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the number of bytes transmitted during the current call on the phone line at given index.
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
int voip_get_tx_byte(uint64_t *p_byte, int index) {

#ifdef SAMPLE_CODE
    *p_byte = 767234;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the number of packets transmitted during the current call on the phone line at given index.
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
int voip_get_tx_packet_cnt(uint64_t *p_cnt, int index) {

#ifdef SAMPLE_CODE
    *p_cnt = 5674;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the number of lost outgoing packets during the current call on the phone line at given index.
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
int voip_get_tx_packet_loss_cnt(uint64_t *p_cnt, int index) {

#ifdef SAMPLE_CODE
    *p_cnt = 451;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the outgoing packet jitter in milliseconds of the current call on the phone line at given index.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 65535
 *
 * Reference        : RFC 3550
 *
 * Remarks          : 
 *
 */
int voip_get_tx_jitter(int *p_jitter, int index) {

#ifdef SAMPLE_CODE
    *p_jitter = 123;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the number of bytes received during the current call on the phone line at given index.
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
int voip_get_rx_byte(uint64_t *p_byte, int index) {

#ifdef SAMPLE_CODE
    *p_byte = 634234;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the number of packets received during the current call on the phone line at given index.
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
int voip_get_rx_packet_cnt(uint64_t *p_cnt, int index) {

#ifdef SAMPLE_CODE
    *p_cnt = 4534;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the number of lost incoming packets during the current call on the phone line at given index.
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
int voip_get_rx_packet_loss_cnt(uint64_t *p_cnt, int index) {

#ifdef SAMPLE_CODE
    *p_cnt = 216;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the incoming packet jitter in milliseconds of the current call on the phone line at given index.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 65535
 *
 * Reference        : RFC 3550
 *
 * Remarks          : 
 *
 */
int voip_get_rx_jitter(int *p_jitter, int index) {

#ifdef SAMPLE_CODE
    *p_jitter = 123;
    return 0;

#else

#endif
    return -1;
}
