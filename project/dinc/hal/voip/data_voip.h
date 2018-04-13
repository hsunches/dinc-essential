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

#ifndef DATA_VOIP_H
#define DATA_VOIP_H

#include <stdint.h>

#define MAX_VOIP_VENDOR_LEN	32
#define MAX_VOIP_SOCKET_CNT	4

enum {
	VOIP_CALL_STAT_ONHOOK	= 0,	// phone hang-up
	VOIP_CALL_STAT_OFFHOOK 	= 1,	// phone pick-up
	VOIP_CALL_STAT_RINGING 	= 2,	// phone hang-up + ringing
	VOIP_CALL_STAT_INCOMING = 3,	// phone pick-up + call type is incoming
	VOIP_CALL_STAT_OUTGOING = 4 	// phone pick-up + call type is outgoing
};

enum {
	VOIP_SIP_TRYING = 100,
	VOIP_SIP_RINGING = 180,
	VOIP_SIP_CALL_BEING_FORWARDED = 181,
	VOIP_SIP_CALL_QUEUED = 182,
	VOIP_SIP_SESSION_PROGRESS = 183,
	VOIP_SIP_OK = 200,
	VOIP_SIP_ACCEPTED = 202,
	VOIP_SIP_MULTIPLE_CHOICES = 300,
	VOIP_SIP_MOVED_PERMANENTLY = 301,
	VOIP_SIP_MOVED_TEMPORARILY = 302,
	VOIP_SIP_USE_PROXY = 305,
	VOIP_SIP_ALTERNATIVE_SERVICE = 380,
	VOIP_SIP_BAD_REQUEST = 400,
	VOIP_SIP_UNAUTHORIZED = 401,
	VOIP_SIP_PAYMENT_REQUIRED = 402,
	VOIP_SIP_FORBIDDEN = 403,
	VOIP_SIP_NOT_FOUND = 404,
	VOIP_SIP_METHOD_NOT_ALLOWED = 405,
	VOIP_SIP_NOT_ACCEPTABLE = 406,
	VOIP_SIP_PROXY_AUTHENTICATION_REQUIRED = 407,
	VOIP_SIP_REQUEST_TIMEOUT = 408,
	VOIP_SIP_CONFLICT = 409,
	VOIP_SIP_GONE = 410,
	VOIP_SIP_LENGTH_REQUIRED = 411,
	VOIP_SIP_REQUEST_ENTITY_TOO_LARGE = 413,
	VOIP_SIP_REQUEST_URI_TOO_LONG = 414,
	VOIP_SIP_UNSUPPORTED_MEDIA_TYPE = 415,
	VOIP_SIP_UNSUPPORTED_URI_SCHEME = 416,
	VOIP_SIP_BAD_EXTENSION = 420,
	VOIP_SIP_EXTENSION_REQUIRED = 421,
	VOIP_SIP_INTERVAL_TOO_BRIEF = 423,
	VOIP_SIP_TEMPORARILY_UNAVAILABLE = 480,
	VOIP_SIP_CALL_TRANSACTION_DOES_NOT_EXIST = 481,
	VOIP_SIP_LOOP_DETECTED = 482,
	VOIP_SIP_TOO_MANY_HOPS = 483,
	VOIP_SIP_ADDRESS_INCOMPLETE = 484,
	VOIP_SIP_AMBIGUOUS = 485,
	VOIP_SIP_BUSY_HERE = 486,
	VOIP_SIP_REQUEST_TERMINATED = 487,
	VOIP_SIP_NOT_ACCEPTABLE_HERE = 488,
	VOIP_SIP_REQUEST_PENDING = 491,
	VOIP_SIP_UNDECIPHERABLE = 493,
	VOIP_SIP_SERVER_INTERNAL_ERROR = 500,
	VOIP_SIP_NOT_IMPLEMENTED = 501,
	VOIP_SIP_BAD_GATEWAY = 502,
	VOIP_SIP_SERVICE_UNAVAILABLE = 503,
	VOIP_SIP_SERVER_TIMEOUT = 504,
	VOIP_SIP_VERSION_NOT_SUPPORTED = 505,
	VOIP_SIP_MESSAGE_TOO_LARGE = 513,
	VOIP_SIP_BUSY_EVERYWHERE = 600,
	VOIP_SIP_DECLINED = 603,
	VOIP_SIP_DOES_NOT_EXIST_ANYWHERE = 604,
	VOIP_SIP_REQUEST_NOT_ACCEPTABLE = 606
};

enum {
	VOIP_CODEC_G_711,
	VOIP_CODEC_G_711_1,
	VOIP_CODEC_G_721,
	VOIP_CODEC_G_722,
	VOIP_CODEC_G_722_1,
	VOIP_CODEC_G_722_2, // AMR-WB
	VOIP_CODEC_G_723,
	VOIP_CODEC_G_723_1,
	VOIP_CODEC_G_726,
	VOIP_CODEC_G_727,
	VOIP_CODEC_G_728,
	VOIP_CODEC_G_729,
	VOIP_CODEC_G_729_1,
	VOIP_CODEC_GSM_06_10,
	VOIP_CODEC_LPC10,
	VOIP_CODEC_SPEEX,
	VOIP_CODEC_ILBC,
	VOIP_CODEC_DOD_CELP,
	VOIP_CODEC_EVRC,
	VOIP_CODEC_DVI,
	VOIP_CODEC_L16,
	VOIP_CODEC_SILK,
	VOIP_CODEC_OTHER
};

int voip_get_vendor(char vendor[MAX_VOIP_VENDOR_LEN + 1]);

int voip_get_socket_cnt(int *p_cnt);

int voip_get_call_stat(int *p_type, int index);

int voip_get_term_reason(int *p_reason, int index);

int voip_get_codec(int *p_codec, int index);

int voip_get_remote_ip_addr(char ip_addr[40], int index);

int voip_get_remote_port(int *p_port, int index);

int voip_get_round_trip_time(int *p_time, int index);

int voip_get_tx_byte(uint64_t *p_byte, int index);

int voip_get_tx_packet_cnt(uint64_t *p_cnt, int index);

int voip_get_tx_packet_loss_cnt(uint64_t *p_cnt, int index);

int voip_get_tx_jitter(int *p_jitter, int index);

int voip_get_rx_byte(uint64_t *p_byte, int index);

int voip_get_rx_packet_cnt(uint64_t *p_cnt, int index);

int voip_get_rx_packet_loss_cnt(uint64_t *p_cnt, int index);

int voip_get_rx_jitter(int *p_jitter, int index);

#endif
