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
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <arpa/inet.h>
#include "ut_util.h"
#include "data_voip.h"

MAKE_TEST_FUNC_STR(voip_get_vendor, MAX_VOIP_VENDOR_LEN);
MAKE_TEST_FUNC_INT(voip_get_socket_cnt, 1, MAX_VOIP_SOCKET_CNT);

int test_voip_get_call_stat(char *text) {
	int type;

	if (voip_get_call_stat(&type, 0) == 0) {
		switch (type) {
		case VOIP_CALL_STAT_ONHOOK:
			strcpy(text, "On-hook");
			return UT_PASS;

		case VOIP_CALL_STAT_OFFHOOK:
			strcpy(text, "Off-hook");
			return UT_PASS;

		case VOIP_CALL_STAT_RINGING:
			strcpy(text, "Ringing");
			return UT_PASS;

		case VOIP_CALL_STAT_INCOMING:
			strcpy(text, "Incoming");
			return UT_PASS;

		case VOIP_CALL_STAT_OUTGOING:
			strcpy(text, "Outgoing");
			return UT_PASS;

		default:
			sprintf(text, "*%d*", type);
			return UT_FAIL;
		}
	}

	return UT_NOT_SUPPORT;
}

int test_voip_get_term_reason(char *text) {
	int reason;

	if (voip_get_term_reason(&reason, 0) == 0) {
		
		sprintf(text, "*%d*", reason);

		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_voip_get_codec(char *text) {
	int codec;

	if (voip_get_codec(&codec, 0) == 0) {
		char *codec_names[] = {
			"G.711",
			"G.711.1",
			"G.721",
			"G.722",
			"G.722.1",
			"G.722.2",
			"G.723",
			"G.723.1",
			"G.726",
			"G.727",
			"G.728",
			"G.729",
			"G.729.1",
			"GSM 06.10",
			"LPC10",
			"Speex",
			"iLBC",
			"DoD CELP",
			"EVRC",
			"DVI",
			"L16",
			"SLIK",
			"Other"
		};

		if (codec < VOIP_CODEC_G_711 || codec > VOIP_CODEC_OTHER) {
			sprintf(text, "*%d*", codec);
			return UT_FAIL;
		}

		strcpy(text, codec_names[codec]);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_voip_get_remote_ip_addr(char *text) {
	char ip_addr[40];
	
	if (voip_get_remote_ip_addr(ip_addr, 0) == 0) {
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

int test_voip_get_remote_port(char *text) {
	int port;

	if (voip_get_remote_port(&port, 0) == 0) {
		if (port < 0 || port > 65535) {
			sprintf(text, "*%d*", port);
			return UT_FAIL;
		}

		sprintf(text, "%d", port);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_voip_get_round_trip_time(char *text) {
	int time;

	if (voip_get_round_trip_time(&time, 0) == 0) {
		if (time < 0 || time > 65535) {
			sprintf(text, "*%d*", time);
			return UT_FAIL;
		}

		sprintf(text, "%d", time);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_voip_get_tx_byte(char *text) {
	uint64_t byte;

	if (voip_get_tx_byte(&byte, 0) == 0) {
		sprintf(text, "%llu", (unsigned long long)byte);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_voip_get_tx_packet_cnt(char *text) {
	uint64_t cnt;

	if (voip_get_tx_packet_cnt(&cnt, 0) == 0) {
		sprintf(text, "%llu", (unsigned long long)cnt);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_voip_get_tx_packet_loss_cnt(char *text) {
	uint64_t cnt;

	if (voip_get_tx_packet_loss_cnt(&cnt, 0) == 0) {
		sprintf(text, "%llu", (unsigned long long)cnt);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_voip_get_tx_jitter(char *text) {
	int jitter;

	if (voip_get_tx_jitter(&jitter, 0) == 0) {
		if (jitter < 0 || jitter > 65535) {
			sprintf(text, "*%d*", jitter);
			return UT_FAIL;
		}

		sprintf(text, "%d", jitter);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_voip_get_rx_byte(char *text) {
	uint64_t byte;

	if (voip_get_rx_byte(&byte, 0) == 0) {
		sprintf(text, "%llu", (unsigned long long)byte);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_voip_get_rx_packet_cnt(char *text) {
	uint64_t cnt;

	if (voip_get_rx_packet_cnt(&cnt, 0) == 0) {
		sprintf(text, "%llu", (unsigned long long)cnt);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int test_voip_get_rx_packet_loss_cnt(char *text) {
	uint64_t cnt;

	if (voip_get_rx_packet_loss_cnt(&cnt, 0) == 0) {
		sprintf(text, "%llu", (unsigned long long)cnt);
		return UT_PASS;
	}	

	return UT_NOT_SUPPORT;
}

int test_voip_get_rx_jitter(char *text) {
	int jitter;

	if (voip_get_rx_jitter(&jitter, 0) == 0) {
		if (jitter < 0 || jitter > 65535) {
			sprintf(text, "*%d*", jitter);
			return UT_FAIL;
		}

		sprintf(text, "%d", jitter);
		return UT_PASS;
	}

	return UT_NOT_SUPPORT;
}

int main() {
    struct test_suite *p_suite;
    struct test_suite *p_sub_suite;
    
	p_suite = create_test_suite("VoIP", 1);
	
	p_sub_suite = create_test_suite("Device", 1);
	add_test(p_sub_suite,	"Vendor",					5,	test_voip_get_vendor);
	add_test(p_sub_suite,	"Socket Count",				5,	test_voip_get_socket_cnt);
	add_test_suite(p_suite, p_sub_suite);
	
	p_sub_suite = create_test_suite("Call", 1);
	add_test(p_sub_suite,	"Call State",				5,	test_voip_get_call_stat);
	add_test(p_sub_suite,	"Termination Reason",		5,	test_voip_get_term_reason);
	add_test(p_sub_suite,	"Codec",					5,	test_voip_get_codec);
	add_test(p_sub_suite,	"Remote IP Address",		5,	test_voip_get_remote_ip_addr);
	add_test(p_sub_suite,	"Remote Port",				5,	test_voip_get_remote_port);
	add_test(p_sub_suite,	"Tx Byte",					5,	test_voip_get_tx_byte);
	add_test(p_sub_suite,	"Tx Packet Count",			5,	test_voip_get_tx_packet_cnt);
	add_test(p_sub_suite,	"Tx Packet Loss Count",		5,	test_voip_get_tx_packet_loss_cnt);
	add_test(p_sub_suite,	"Tx Jitter",				5,	test_voip_get_tx_jitter);
	add_test(p_sub_suite,	"Rx Byte",					5,	test_voip_get_rx_byte);
	add_test(p_sub_suite,	"Rx Packet Count",			5,	test_voip_get_rx_packet_cnt);
	add_test(p_sub_suite,	"Rx Packet Loss Count",		5,	test_voip_get_rx_packet_loss_cnt);
	add_test(p_sub_suite,	"Rx Jitter",				5,	test_voip_get_rx_jitter);
	add_test(p_sub_suite,	"Round Trip Time",			5,	test_voip_get_round_trip_time);
	add_test_suite(p_suite, p_sub_suite);
	
	run_test_suite(p_suite);
	delete_test_suite(p_suite);
	return 0;
}
