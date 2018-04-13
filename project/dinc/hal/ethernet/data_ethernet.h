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

#ifndef DATA_ETHERNET_H
#define DATA_ETHERNET_H

#include <stdint.h>

#define MAX_ETHERNET_PORT_CNT	16

// Port State
#define PORT_ACTIVE				0x11
#define PORT_INACTIVE			0x10

// Ethernet Speed
#define ETHERNET_SPEED_10M		0x01
#define ETHERNET_SPEED_100M		0x02
#define ETHERNET_SPEED_1000M	0x04

typedef struct _ethernet_byte_info
{
	int port_state;
	unsigned long long tx_byte;
	unsigned long long rx_byte;
} ethernet_byte_info;

typedef struct _ethernet_throughput_info
{
	int port_state;
	int port_speed;
	unsigned long long tx_packet_count;
	unsigned long long rx_packet_count;
	unsigned long long tx_packet_error_count;
	unsigned long long rx_packet_error_count;
	unsigned long long tx_frame_count;
	unsigned long long rx_frame_count;
	unsigned long long tx_frame_error_count;
	unsigned long long rx_frame_error_count;
} ethernet_throughput_info;

/*
 * Ethernet Info
 */
int ethernet_get_port_byte_info(ethernet_byte_info byte_info[MAX_ETHERNET_PORT_CNT]);
int ethernet_get_port_tp_info(ethernet_throughput_info tp_info[MAX_ETHERNET_PORT_CNT]);

#endif /* DATA_ETHERNET_H */
