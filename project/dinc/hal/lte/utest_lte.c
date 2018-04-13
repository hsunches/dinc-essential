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
#include <float.h>
#include <arpa/inet.h>
#include "ut_util.h"
#include "data_lte.h"

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

void check_value_f(char *text, float x, float y)
{
	if (x == y)
	{
		strcpy(text, "invalid");
	}
	else
	{
		sprintf(text, "%f", x);
	}
}

int test_get_supported_freq_band(char *text)
{
	long long value = 0;
	if (!lte_get_supported_freq_band(&value))
	{
		sprintf(text, "%lld", value);
		if (value < 1 || value > 17592186044415) // 2^44 -1
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

	if (!lte_get_ip_address(ipbuff))
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
	if (!lte_get_network_entry_latency(&value))
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

int test_get_cell_id(char *text)
{
	int value = 0;
	if (!lte_get_cell_id(&value))
	{
		sprintf(text, "%d", value);
		if (value < 1 || value > 268435456)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_rssi(char *text)
{
	int value = 0;
	if (!lte_get_rssi(&value))
	{
		sprintf(text, "%d", value);
		if (value < -100 || value > -25)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_rsrp(char *text)
{
	int value = 0;
	if (!lte_get_rsrp(&value))
	{
		sprintf(text, "%d", value);
		if (value < -140 || value > -44)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_rsrq(char *text)
{
	float value = 0;
	if (!lte_get_rsrq(&value))
	{
		sprintf(text, "%f", value);
		if (value < -19.5 || value > -3)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_cqi(char *text)
{
	int value = 0;
	if (!lte_get_cqi(&value))
	{
		sprintf(text, "%d", value);
		if (value < 0 || value > 15)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_ul_earfcn(char *text)
{
	int value;
	if (!lte_get_ul_earfcn(&value))
	{
		sprintf(text, "%d", value);
		// Check EARFCN Range of Uplink
		if ((value >= 18000 && value <= 27659) || (value >= 36000 && value <= 46589))
		{
			return UT_PASS;
		}
		return UT_FAIL;
	}
	return UT_NOT_SUPPORT;
}

int test_get_dl_earfcn(char *text)
{
	int value;
	if (!lte_get_dl_earfcn(&value))
	{
		sprintf(text, "%d", value);
		// Check EARFCN Range of Downlink
		if ((value >= 0 && value <= 9769) || (value >= 36000 && value <= 46589))
		{
			return UT_PASS;
		}
		return UT_FAIL;
	}
	return UT_NOT_SUPPORT;
}

int test_get_channel_bw(char *text)
{
	int value = 0;
	if (!lte_get_channel_bw(&value))
	{
		switch (value)
		{
			case LTE_CHANNEL_BW_1_4:
				strcpy(text, "LTE_CHANNEL_BW_1_4");
			break;
			case LTE_CHANNEL_BW_3:
				strcpy(text, "LTE_CHANNEL_BW_3");
			break;
			case LTE_CHANNEL_BW_5:
				strcpy(text, "LTE_CHANNEL_BW_5");
			break;
			case LTE_CHANNEL_BW_10:
				strcpy(text, "LTE_CHANNEL_BW_10");
			break;
			case LTE_CHANNEL_BW_15:
				strcpy(text, "LTE_CHANNEL_BW_15");
			break;
			case LTE_CHANNEL_BW_20:
				strcpy(text, "LTE_CHANNEL_BW_20");
			break;
			default:
				sprintf(text, "Unsupported Value:%d", value);
			break;
		}

		if (value < 1 || value > 32)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_mcc(char *text)
{
	int value = 0;
	if (!lte_get_mcc(&value))
	{
		sprintf(text, "%d", value);
		if (value < 1)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_mnc(char *text)
{
	char buff[4] = "";
	if (!lte_get_mnc(buff))
	{
		sprintf(text, "%s", buff);
		if (buff[0] == -1)
		{
			return UT_FAIL;
		}
		return UT_PASS;
	}
	return UT_NOT_SUPPORT;
}

int test_get_lac(char *text)
{
	int value = 0;
	if (!lte_get_lac(&value))
	{
		sprintf(text, "%d", value);
		if (value < 1 || value > 65535 || value == 65534)
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
	if (!lte_get_handover_latency(&value))
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
	if (!lte_get_handover_success_count(&value))
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
	if (!lte_get_handover_failure_count(&value))
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
	if (!lte_get_ul_mcs(&value))
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
	if (!lte_get_dl_mcs(&value))
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
	if (!lte_get_tx_power(&value))
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
	if (!lte_get_tx_byte(&value))
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
	if (!lte_get_rx_byte(&value))
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
	if (!lte_get_tx_packet_count(&value))
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
	if (!lte_get_rx_packet_count(&value))
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
	if (!lte_get_tx_packet_error_count(&value))
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
	if (!lte_get_rx_packet_error_count(&value))
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
	if (!lte_get_tx_frame_count(&value))
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
	if (!lte_get_rx_frame_count(&value))
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
	if (!lte_get_tx_frame_error_count(&value))
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
	if (!lte_get_rx_frame_error_count(&value))
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
	if (!lte_get_disconnect_reason(&value))
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

int test_get_neighboring_cell_info(char *text)
{
	int value = 0;
	char tempstr[7][32];
	char temptext[256] = { 0 };
	const char invalidmark = 0xFF;
	lte_cell_info list[MAX_LTE_NGBR_CELL_CNT];

	*text = 0x00;

	int i = 0;
	for (; i < MAX_LTE_NGBR_CELL_CNT; i++)
	{
		list[i].cell_id = -1;
		list[i].mcc = -1;
		memset(list[i].mnc, 0, 4);
		list[i].mnc[0] = invalidmark;
		list[i].lac = -1;
		list[i].rssi = 127;
		list[i].rsrp = 127;
		list[i].rsrq = FLT_MAX;
	}

	if (!lte_get_neighboring_cell_info(&value, list))
	{
		int i;
		for (i = 0; i < value; ++i)
		{
			if (list[i].cell_id)
			{
				check_value_d(tempstr[0], list[i].cell_id, -1);
				check_value_d(tempstr[1], list[i].mcc, -1);

				if (list[i].mnc[0] == invalidmark)
				{
					strcpy(tempstr[2], (const char *) "invalid");
				}
				else
				{
					strcpy(tempstr[2], (const char *) list[i].mnc);
				}

				check_value_d(tempstr[3], list[i].lac, -1);
				check_value_d(tempstr[4], list[i].rssi, 127);
				check_value_d(tempstr[5], list[i].rsrp, 127);
				check_value_f(tempstr[6], list[i].rsrq, FLT_MAX);

				sprintf(temptext, "CID:%s, MCC:%s, MNC:%s, LAC:%s, RSSI:%s, RSRP:%s, RSRQ:%s\n", tempstr[0], tempstr[1], tempstr[2], tempstr[3], tempstr[4],
						tempstr[5], tempstr[6]);

				strcat(text, temptext);

				if (list[i].mcc < -1 || list[i].mcc > 901)
				{
					return UT_FAIL;
				}

				if ((list[i].lac < 1 || list[i].lac == 65534 || list[i].lac > 65535) && list[i].lac != -1)
				{
					return UT_FAIL;
				}

				if ((list[i].rssi < -100 || list[i].rssi > -25) && list[i].rssi != 127)
				{
					return UT_FAIL;
				}

				if ((list[i].rsrp < -140 || list[i].rsrp > -44) && list[i].rsrp != 127)
				{
					return UT_FAIL;
				}

				if ((list[i].rsrq < -19.5 || list[i].rsrq > -3) && list[i].rsrq != FLT_MAX)
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

int test_get_ul_bearer_flow_max_speed(char *text)
{
	int value = 0;
	if (!lte_get_ul_bearer_flow_max_speed(&value))
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

int test_get_dl_bearer_flow_max_speed(char *text)
{
	int value = 0;
	if (!lte_get_dl_bearer_flow_max_speed(&value))
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

	p_suite = create_test_suite("LTE", 1);

	add_test(p_suite, "SUPPORTED_FREQ_BAND", 3, test_get_supported_freq_band);
	add_test(p_suite, "IP_ADDRESS", 3, test_get_ip_address);
	add_test(p_suite, "NETWORK_ENTRY_LATENCY", 3, test_get_network_entry_latency);
	add_test(p_suite, "CELL_ID", 3, test_get_cell_id);
	add_test(p_suite, "RSSI", 3, test_get_rssi);
	add_test(p_suite, "RSRP", 3, test_get_rsrp);
	add_test(p_suite, "RSRQ", 3, test_get_rsrq);
	add_test(p_suite, "CQI", 3, test_get_cqi);
	add_test(p_suite, "UL_EARFCN", 3, test_get_ul_earfcn);
	add_test(p_suite, "DL_EARFCN", 3, test_get_dl_earfcn);
	add_test(p_suite, "CHANNEL_BW", 3, test_get_channel_bw);
	add_test(p_suite, "MCC", 3, test_get_mcc);
	add_test(p_suite, "MNC", 3, test_get_mnc);
	add_test(p_suite, "LAC", 3, test_get_lac);
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
	add_test(p_suite, "NEIGHBORING_CELL_INFO", 3, test_get_neighboring_cell_info);
	add_test(p_suite, "UL_BEARER_FLOW_MAX_SPEED", 3, test_get_ul_bearer_flow_max_speed);
	add_test(p_suite, "DL_BEARER_FLOW_MAX_SPEED", 3, test_get_dl_bearer_flow_max_speed);

	run_test_suite(p_suite);
	delete_test_suite(p_suite);

	return 0;
}

