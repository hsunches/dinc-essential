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
#include "data_ethernet.h"
#include "msg_hal.h"

/*
 * Description		: Get IP layer Tx/Rx Byte info of every active port since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: Active Port is Bitmap showed as array index
 * 					: Array[0:15]  - representing port index 1 to 16
 * 					: 	.port_state = use constants defined in data_ethernet.h, leave it empty if unavailable.
 * 					: 	.tx/rx byte = 1 ~ (2^64 - 1), leave it empty if unavailable.
 * Reference		:
 * Remarks			:
 */
int ethernet_get_port_byte_info(ethernet_byte_info byte_info[MAX_ETHERNET_PORT_CNT])
{
#ifdef SAMPLE_CODE
	// Assume this device have 4 ports, but only 2 ports are active and port index is 2 and 3.
	// Array[0] = port 1
	// Array[1] = port 2 active
	// Array[2] = port 3 active
	// Array[3] = port 4
	ethernet_byte_info temp_info[4];
	memset(temp_info, 0xFF, sizeof(ethernet_byte_info) * 4);

	temp_info[0].port_state = PORT_INACTIVE;
	temp_info[1].port_state = PORT_ACTIVE;
	temp_info[1].tx_byte = 100000001ULL;
	temp_info[1].rx_byte = 200000001ULL;
	temp_info[2].port_state = PORT_ACTIVE;
	temp_info[2].tx_byte = 123000001ULL;
	temp_info[2].rx_byte = 234000001ULL;
	temp_info[3].port_state = PORT_INACTIVE;

	// Due to the device with 4 ports, please only copy 4 is enough.
	memcpy(byte_info, temp_info, sizeof(ethernet_byte_info) * 4);

	return 0;
#else

#endif
	return -1;
}

/*
 * Description		: Get Throughtput info of every active port since booting up or network entry.
 * Return Code      : 0 for success, -1 for failure or unsupported.
 * Data Valid Range	: Active Port is Bitmap showed as array index
 * 					: Array[0:15]  - representing port index 1 to 16
 * 					:	.port_state = use constants defined in data_ethernet.h, leave it empty if unavailable.
 * 					: 	.port_speed = use constants defined in the data_ethernet.h, leave it empty if unavailable.
 * 					: 	.tx/rx packet count  		= 1 ~ (2^64 - 1), leave it empty if unavailable.
 * 					: 	.tx/rx packet error count	= 1 ~ (2^64 - 1), leave it empty if unavailable.
 * 					: 	.tx/rx frame count  		= 1 ~ (2^64 - 1), leave it empty if unavailable.
 * 					: 	.tx/rx frame error count 	= 1 ~ (2^64 - 1), leave it empty if unavailable.
 * Reference		:
 * Remarks			: Throughput data member is a loop counter.
 */
int ethernet_get_port_tp_info(ethernet_throughput_info tp_info[MAX_ETHERNET_PORT_CNT])
{
#ifdef SAMPLE_CODE
	// Assume this device have 4 ports, but only 2 ports are active and port index is 2 and 4.
	// Array[0] = port 1
	// Array[1] = port 2 active
	// Array[2] = port 3
	// Array[3] = port 4 active
	ethernet_throughput_info temp_info[4];
	memset(temp_info, 0xFF, sizeof(ethernet_throughput_info) * 4);

	// Assume all data available of port index 2
	temp_info[0].port_state = PORT_INACTIVE;
	temp_info[1].port_state = PORT_ACTIVE;
	temp_info[1].port_speed = ETHERNET_SPEED_100M;
	temp_info[1].tx_packet_count = 100001ULL;
	temp_info[1].rx_packet_count = 200001ULL;
	temp_info[1].tx_packet_error_count = 1001ULL;
	temp_info[1].rx_packet_error_count = 2001ULL;
	temp_info[1].tx_frame_count = 100000001ULL;
	temp_info[1].rx_frame_count = 200000001ULL;
	temp_info[1].tx_frame_error_count = 100001ULL;
	temp_info[1].rx_frame_error_count = 200001ULL;
	temp_info[2].port_state = PORT_INACTIVE;
	// Only speed, packet count and packet error count are available of port index 4,
	// usually this is impossible (one port can get all data items, but the other one cannot.),
	// but here is sample code, so it is ok.
	temp_info[3].port_state = PORT_ACTIVE;
	temp_info[3].port_speed = ETHERNET_SPEED_10M;
	temp_info[3].tx_packet_count = 100001ULL;
	temp_info[3].rx_packet_count = 200001ULL;
	temp_info[3].tx_packet_error_count = 1001ULL;
	temp_info[3].rx_packet_error_count = 2001ULL;

	memcpy(tp_info, temp_info, sizeof(ethernet_throughput_info) * 4);

	return 0;
#else

#endif
	return -1;
}
