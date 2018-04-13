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
#include <arpa/inet.h>
#include "ut_util.h"
#include "data_wmx.h"

void check_value_d(char *text, int x, int y)
{
	if (x == y)
	{
		strcpy(text, "invalid");
	}
	else
	{
		sprintf(text, "%d", x);
	}
}

int test_get_supported_freq_band(char *text)
{
	int value = 0;
	if (!wmx_get_supported_freq_band(&value))
	{
		switch (value)
		{
			case WIMAX_FREQ_BAND_2_3:
				strcpy(text, "WIMAX_FREQ_BAND_2_3");
			break;
			case WIMAX_FREQ_BAND_2_5:
				strcpy(text, "WIMAX_FREQ_BAND_2_5");
			break;
			case WIMAX_FREQ_BAND_3_5:
				strcpy(text, "WIMAX_FREQ_BAND_3_5");
			break;
			case WIMAX_FREQ_BAND_3_8:
				strcpy(text, "WIMAX_FREQ_BAND_3_8");
			break;
			default:
				sprintf(text, "Unsupported Value:%d", value);
			break;
		}

		if (value < 1 || value > 15)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_ip_address(char *text)
{
	char ipbuff[40] = "";
	struct in_addr s4;
	struct in6_addr s6;
	int ip_check = 0;

	if (!wmx_get_ip_address(ipbuff))
	{
		sprintf(text, "%s", ipbuff);
		if (strchr(ipbuff, '.'))
		{
			//IPv4
			ip_check = inet_pton(AF_INET, ipbuff, (void *) &s4);
		}
		else
		{
			//IPv6
			ip_check = inet_pton(AF_INET6, ipbuff, (void *) &s6);
		}

		if (!ip_check)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_network_entry_latency(char *text)
{
	int value = 0;
	if (!wmx_get_network_entry_latency(&value))
	{
		sprintf(text, "%d", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_bs_id(char *text)
{
	uint8_t buff[6];
	if (!wmx_get_bs_id(buff))
	{
		sprintf(text, "%02X:%02X:%02X:%02X:%02X:%02X", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_rssi(char *text)
{
	int value = 0;
	if (!wmx_get_rssi(&value))
	{
		sprintf(text, "%d", value);
		if (value < -123 || value > -40)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_cinr_r3(char *text)
{
	int value = 0;
	if (!wmx_get_cinr_r3(&value))
	{
		sprintf(text, "%d", value);
		if (value < 2 || value > 25)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_cinr_r1(char *text)
{
	int value = 0;
	if (!wmx_get_cinr_r1(&value))
	{
		sprintf(text, "%d", value);
		if (value < -3 || value > 22)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_frequency(char *text)
{
	int value = 0;
	if (!wmx_get_frequency(&value))
	{
		sprintf(text, "%d", value);
		if (value < 2300000 || value > 3800000)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_bandwidth(char *text)
{
	int value = 0;
	if (!wmx_get_bandwidth(&value))
	{
		sprintf(text, "%d", value);
		if (value < 1250 || value > 20000)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_handover_latency(char *text)
{
	int value = 0;
	if (!wmx_get_handover_latency(&value))
	{
		sprintf(text, "%d", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_handover_success_count(char *text)
{
	int value = 0;
	if (!wmx_get_handover_success_count(&value))
	{
		sprintf(text, "%d", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_handover_failure_count(char *text)
{
	int value = 0;
	if (!wmx_get_handover_failure_count(&value))
	{
		sprintf(text, "%d", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_ul_mcs(char *text)
{
	int value = 0;
	if (!wmx_get_ul_mcs(&value))
	{
		sprintf(text, "%d", value);
		int mcs_type[13] = { 1, 17, 18, 19, 20, 21, 22, 34, 35, 36, 37, 38, 39 };
		int i = 0;
		for (; i < 13; i++)
		{
			if (value == mcs_type[i])
			{
				return UT_PASS;
			}
		}
		return UT_FAIL;
	}
	return UT_NOT_SUPPORT;
}

int test_get_dl_mcs(char *text)
{
	int value = 0;
	if (!wmx_get_dl_mcs(&value))
	{
		sprintf(text, "%d", value);
		int mcs_type[13] = { 1, 17, 18, 19, 20, 21, 22, 34, 35, 36, 37, 38, 39 };
		int i = 0;
		for (; i < 13; i++)
		{
			if (value == mcs_type[i])
			{
				return UT_PASS;
			}
		}
		return UT_FAIL;
	}
	return UT_NOT_SUPPORT;
}

int test_get_tx_power(char *text)
{
	int value = 0;
	if (!wmx_get_tx_power(&value))
	{
		sprintf(text, "%d", value);
		if (value < -40 || value > 33)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_tx_byte(char *text)
{
	unsigned long long value = 0;
	if (!wmx_get_tx_byte(&value))
	{
		sprintf(text, "%llu", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_rx_byte(char *text)
{
	unsigned long long value = 0;
	if (!wmx_get_rx_byte(&value))
	{
		sprintf(text, "%llu", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_tx_packet_count(char *text)
{
	unsigned long long value = 0;
	if (!wmx_get_tx_packet_count(&value))
	{
		sprintf(text, "%llu", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_rx_packet_count(char *text)
{
	unsigned long long value = 0;
	if (!wmx_get_rx_packet_count(&value))
	{
		sprintf(text, "%llu", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_tx_packet_error_count(char *text)
{
	unsigned long long value = 0;
	if (!wmx_get_tx_packet_error_count(&value))
	{
		sprintf(text, "%llu", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_rx_packet_error_count(char *text)
{
	unsigned long long value = 0;
	if (!wmx_get_rx_packet_error_count(&value))
	{
		sprintf(text, "%llu", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_tx_frame_count(char *text)
{
	unsigned long long value = 0;
	if (!wmx_get_tx_frame_count(&value))
	{
		sprintf(text, "%llu", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_rx_frame_count(char *text)
{
	unsigned long long value = 0;
	if (!wmx_get_rx_frame_count(&value))
	{
		sprintf(text, "%llu", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_tx_frame_error_count(char *text)
{
	unsigned long long value = 0;
	if (!wmx_get_tx_frame_error_count(&value))
	{
		sprintf(text, "%llu", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_rx_frame_error_count(char *text)
{
	unsigned long long value = 0;
	if (!wmx_get_rx_frame_error_count(&value))
	{
		sprintf(text, "%llu", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_disconnect_reason(char *text)
{
	int value = 0;
	if (!wmx_get_disconnect_reason(&value))
	{
		sprintf(text, "%d", value);
		if (value < 1 || value > 9)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_neighboring_bs_info(char *text)
{
	int value = 0;
	char tempstr[4][32];
	char temptext[256] = { 0 };
	const uint8_t invalidmark = 0xFF;
	wmx_bs_info list[MAX_WMX_NGBR_BS_CNT];

	*text = 0x00;

	int i = 0;
	for (; i < MAX_WMX_NGBR_BS_CNT; i++)
	{
		memset(list[i].bs_id, 0xFF, 4);
		list[i].rssi = 127;
		list[i].cinr_r3 = 127;
		list[i].cinr_r1 = 127;
	}

	if (!wmx_get_neighboring_bs_info(&value, list))
	{
		int i;
		for (i = 0; i < value; ++i)
		{
			if (list[i].bs_id[0] == invalidmark)
			{
				strcpy(tempstr[0], (const char *) "invalid");
			}
			else
			{
				sprintf(tempstr[0], "%02X:%02X:%02X:%02X:%02X:%02X", list[i].bs_id[0], list[i].bs_id[1], list[i].bs_id[2], list[i].bs_id[3], list[i].bs_id[4],
						list[i].bs_id[5]);
			}

			check_value_d(tempstr[1], list[i].rssi, 127);
			check_value_d(tempstr[2], list[i].cinr_r3, 127);
			check_value_d(tempstr[3], list[i].cinr_r1, 127);

			sprintf(temptext, "BS_ID:%s, RSSI:%s, CINR_R3:%s, CINR_R1:%s\n", tempstr[0], tempstr[1], tempstr[2], tempstr[3]);

			strcat(text, temptext);

			if (list[i].bs_id[0] != invalidmark)
			{
				if ((list[i].rssi < -150 || list[i].rssi > -40) && list[i].rssi != 127)
				{
					return UT_FAIL;
				}

				if ((list[i].cinr_r3 < -10 || list[i].cinr_r3 > 25) && list[i].cinr_r3 != 127)
				{
					return UT_FAIL;
				}

				if ((list[i].cinr_r1 < -10 || list[i].cinr_r1 > 23) && list[i].cinr_r1 != 127)
				{
					return UT_FAIL;
				}
			}
			else
			{
				return UT_FAIL;
			}
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_ul_service_flow_max_speed(char *text)
{
	int value = 0;
	if (!wmx_get_ul_service_flow_max_speed(&value))
	{
		sprintf(text, "%d", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_dl_service_flow_max_speed(char *text)
{
	int value = 0;
	if (!wmx_get_dl_service_flow_max_speed(&value))
	{
		sprintf(text, "%d", value);
		if (value < 0)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int main(void)
{
	struct test_suite *p_suite;

	p_suite = create_test_suite("WiMAX", 1);

	add_test(p_suite, "SUPPORTED_FREQ_BAND", 3, test_get_supported_freq_band);
	add_test(p_suite, "IP_ADDRESS", 3, test_get_ip_address);
	add_test(p_suite, "NETWORK_ENTRY_LATENCY", 3, test_get_network_entry_latency);
	add_test(p_suite, "BS_ID", 3, test_get_bs_id);
	add_test(p_suite, "RSSI", 3, test_get_rssi);
	add_test(p_suite, "CINR_R3", 3, test_get_cinr_r3);
	add_test(p_suite, "CINR_R1", 3, test_get_cinr_r1);
	add_test(p_suite, "FREQUENCY", 3, test_get_frequency);
	add_test(p_suite, "BANDWIDTH", 3, test_get_bandwidth);
	add_test(p_suite, "HANDOVER_LATENCY", 3, test_get_handover_latency);
	add_test(p_suite, "HANDOVER_SUCCESS_COUNT", 3, test_get_handover_success_count);
	add_test(p_suite, "HANDOVER_FAILURE_COUNT", 3, test_get_handover_failure_count);
	add_test(p_suite, "UL_MCS", 3, test_get_ul_mcs);
	add_test(p_suite, "DL_MCS", 3, test_get_dl_mcs);
	add_test(p_suite, "TX_POWER", 3, test_get_tx_power);
	add_test(p_suite, "TX_BYTE", 3, test_get_tx_byte);
	add_test(p_suite, "RX_BYTE", 3, test_get_rx_byte);
	add_test(p_suite, "TX_PACKET_COUNT", 3, test_get_tx_packet_count);
	add_test(p_suite, "RX_PACKET_COUNT", 3, test_get_rx_packet_count);
	add_test(p_suite, "TX_PACKET_ERROR_COUNT", 3, test_get_tx_packet_error_count);
	add_test(p_suite, "RX_PACKET_ERROR_COUNT", 3, test_get_rx_packet_error_count);
	add_test(p_suite, "TX_FRAME_COUNT", 3, test_get_tx_frame_count);
	add_test(p_suite, "RX_FRAME_COUNT", 3, test_get_rx_frame_count);
	add_test(p_suite, "TX_FRAME_ERROR_COUNT", 3, test_get_tx_frame_error_count);
	add_test(p_suite, "RX_FRAME_ERROR_COUNT", 3, test_get_rx_frame_error_count);
	add_test(p_suite, "DISCONNECT_REASON", 3, test_get_disconnect_reason);
	add_test(p_suite, "NEIGHBORING_BS_INFO", 3, test_get_neighboring_bs_info);
	add_test(p_suite, "UL_SERVICE_FLOW_MAX_SPEED", 3, test_get_ul_service_flow_max_speed);
	add_test(p_suite, "DL_SERVICE_FLOW_MAX_SPEED", 3, test_get_dl_service_flow_max_speed);

	run_test_suite(p_suite);
	delete_test_suite(p_suite);

	return 0;
}
