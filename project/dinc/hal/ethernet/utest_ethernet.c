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
#include "ut_util.h"
#include "data_ethernet.h"

#define INVALID_FOR_8BYTE 0xFFFFFFFFFFFFFFFFULL
#define INVALID_FOR_4BYTE 0xFFFFFFFF
#define CHECK_VALUE_EQUAL(x) ((x == INVALID_FOR_8BYTE) ? 1 : 0)
// #define MAKE_VALUE_STRING(result,text,arg,val,invalid,name) (val == invalid) ? (int)strcpy(text, name): sprintf(text, arg, val) ; strcat(result, text) ;
#define MAKE_VALUE_STRING(result,text,arg,val,invalid,name) if (val == invalid) { strcpy(text, name); } else { sprintf(text, arg, val); } strcat(result, text);

int test_get_port_byte_info(char *text)
{
	int Ret = 0;
	char tempstr[40] = { 0 };
	ethernet_byte_info byte_info[MAX_ETHERNET_PORT_CNT];

	*text = 0x00;

	memset(byte_info, 0xFF, sizeof(ethernet_byte_info) * MAX_ETHERNET_PORT_CNT);

	if (!ethernet_get_port_byte_info(byte_info))
	{
		int i;
		for (i = 0; i < MAX_ETHERNET_PORT_CNT; i++)
		{
			if (byte_info[i].port_state == INVALID_FOR_4BYTE && byte_info[i].tx_byte == INVALID_FOR_8BYTE && byte_info[i].rx_byte == INVALID_FOR_8BYTE)
			{
				continue;
			}

			MAKE_VALUE_STRING(text, tempstr, "Index:%d", i, INVALID_FOR_4BYTE, "Index:invalid");
			strcat(text, ", ");
			MAKE_VALUE_STRING(text, tempstr, "State:%d", byte_info[i].port_state, INVALID_FOR_4BYTE, "State:invalid");
			strcat(text, ", ");
			MAKE_VALUE_STRING(text, tempstr, "Tx_Byte:%llu", byte_info[i].tx_byte, INVALID_FOR_8BYTE, "Tx_Byte:invalid");
			strcat(text, ", ");
			MAKE_VALUE_STRING(text, tempstr, "Rx_Byte:%llu", byte_info[i].rx_byte, INVALID_FOR_8BYTE, "Rx_Byte:invalid");
			strcat(text, "\n");
			switch (byte_info[i].port_state)
			{
				case PORT_ACTIVE:
				{
					if (CHECK_VALUE_EQUAL(byte_info[i].tx_byte) && CHECK_VALUE_EQUAL(byte_info[i].rx_byte))
					{
						Ret = UT_FAIL;
					}
				}
				break;
				case PORT_INACTIVE:
				{
					if (!CHECK_VALUE_EQUAL(byte_info[i].tx_byte) || !CHECK_VALUE_EQUAL(byte_info[i].rx_byte))
					{
						Ret = UT_FAIL;
					}
				}
				break;
			}
		}
		Ret = UT_PASS;
		return Ret;
	}
	return UT_NOT_SUPPORT;
}

int test_get_port_tp_info(char *text)
{
	int Ret = 0;
	char tempstr[48] = { 0 };
	ethernet_throughput_info tp_info[MAX_ETHERNET_PORT_CNT];

	*text = 0x00;

	memset(tp_info, 0xFF, sizeof(ethernet_throughput_info) * MAX_ETHERNET_PORT_CNT);

	if (!ethernet_get_port_tp_info(tp_info))
	{
		int i;
		for (i = 0; i < MAX_ETHERNET_PORT_CNT; i++)
		{
			if (tp_info[i].port_state == INVALID_FOR_4BYTE && tp_info[i].port_speed == INVALID_FOR_4BYTE)
			{
				continue;
			}

			MAKE_VALUE_STRING(text, tempstr, "Index:%d", i, INVALID_FOR_4BYTE, "Index:invalid");
			strcat(text, ", ");
			MAKE_VALUE_STRING(text, tempstr, "State:%d", tp_info[i].port_state, INVALID_FOR_4BYTE, "State:invalid");
			strcat(text, ", ");
			MAKE_VALUE_STRING(text, tempstr, "Speed:%d", tp_info[i].port_speed, INVALID_FOR_4BYTE, "Speed:invalid");
			strcat(text, ", \n");
			MAKE_VALUE_STRING(text, tempstr, "Tx_Packet_Count:%llu", tp_info[i].tx_packet_count, INVALID_FOR_8BYTE, "Tx_Packet_Count:invalid");
			strcat(text, ", ");
			MAKE_VALUE_STRING(text, tempstr, "Rx_Packet_Count:%llu", tp_info[i].rx_packet_count, INVALID_FOR_8BYTE, "Rx_Packet_Count:invalid");
			strcat(text, ", \n");
			MAKE_VALUE_STRING(text, tempstr, "Tx_Packet_Error_Count:%llu", tp_info[i].tx_packet_error_count, INVALID_FOR_8BYTE, "Tx_Packet_Error_Count:invalid");
			strcat(text, ", ");
			MAKE_VALUE_STRING(text, tempstr, "Rx_Packet_Error_Count:%llu", tp_info[i].rx_packet_error_count, INVALID_FOR_8BYTE, "Rx_Packet_Error_Count:invalid");
			strcat(text, ", \n");
			MAKE_VALUE_STRING(text, tempstr, "Tx_Frame_Count:%llu", tp_info[i].tx_frame_count, INVALID_FOR_8BYTE, "Tx_Frame_Count:invalid");
			strcat(text, ", ");
			MAKE_VALUE_STRING(text, tempstr, "Rx_Frame_Count:%llu", tp_info[i].rx_frame_count, INVALID_FOR_8BYTE, "Rx_Frame_Count:invalid");
			strcat(text, ", \n");
			MAKE_VALUE_STRING(text, tempstr, "Tx_Frame_Error_Count:%llu", tp_info[i].tx_frame_error_count, INVALID_FOR_8BYTE, "Tx_Frame_Error_Count:invalid");
			strcat(text, ", ");
			MAKE_VALUE_STRING(text, tempstr, "Rx_Frame_Error_Count:%llu", tp_info[i].rx_frame_error_count, INVALID_FOR_8BYTE, "Rx_Frame_Error_Count:invalid");
			strcat(text, "\n");

			switch (tp_info[i].port_state)
			{

				case PORT_ACTIVE:
				{
					if (CHECK_VALUE_EQUAL(tp_info[i].tx_packet_count) && CHECK_VALUE_EQUAL(tp_info[i].rx_packet_count)
							&& CHECK_VALUE_EQUAL(tp_info[i].tx_packet_error_count) && CHECK_VALUE_EQUAL(tp_info[i].rx_packet_error_count)
							&& CHECK_VALUE_EQUAL(tp_info[i].tx_frame_count) && CHECK_VALUE_EQUAL(tp_info[i].rx_frame_count)
							&& CHECK_VALUE_EQUAL(tp_info[i].tx_frame_error_count) && CHECK_VALUE_EQUAL(tp_info[i].rx_frame_error_count))
					{
						Ret = UT_FAIL;
					}
				}
				break;
				case PORT_INACTIVE:
				{
					if (!CHECK_VALUE_EQUAL(tp_info[i].tx_packet_count) || !CHECK_VALUE_EQUAL(tp_info[i].rx_packet_count)
							|| !CHECK_VALUE_EQUAL(tp_info[i].tx_packet_error_count) || !CHECK_VALUE_EQUAL(tp_info[i].rx_packet_error_count)
							|| !CHECK_VALUE_EQUAL(tp_info[i].tx_frame_count) || !CHECK_VALUE_EQUAL(tp_info[i].rx_frame_count)
							|| !CHECK_VALUE_EQUAL(tp_info[i].tx_frame_error_count) || !CHECK_VALUE_EQUAL(tp_info[i].rx_frame_error_count))
					{
						Ret = UT_FAIL;
					}
				}
				break;
			}
		}
		Ret = UT_PASS;
		return Ret;
	}
	return UT_NOT_SUPPORT;
}

int main(void)
{
	struct test_suite *p_suite;

	p_suite = create_test_suite("ETHERNET", 1);

	add_test(p_suite, "PORT_BYTE_INFO", 3, test_get_port_byte_info);
	add_test(p_suite, "PORT_THROUGHPUT_INFO", 3, test_get_port_tp_info);

	run_test_suite(p_suite);
	delete_test_suite(p_suite);

	return 0;
}
