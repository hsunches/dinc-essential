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

#ifndef MSG_HAL_H
#define MSG_HAL_H

// MCS Type List
#define MCS_TYPE_GMSK		0x01
#define MCS_TYPE_BPSK		0x11
#define MCS_TYPE_QPSK		0x12
#define MCS_TYPE_8PSK		0x13
#define MCS_TYPE_16PSK		0x14
#define MCS_TYPE_32PSK		0x15
#define MCS_TYPE_64PSK		0x16
#define MCS_TYPE_4QAM		0x22
#define MCS_TYPE_8QAM		0x23
#define MCS_TYPE_16QAM		0x24
#define MCS_TYPE_32QAM		0x25
#define MCS_TYPE_64QAM		0x26
#define MCS_TYPE_128QAM		0x27

// NIF Type List
#define NIF_TYPE_WIFI		0x10
#define NIF_TYPE_2G			0x20
#define NIF_TYPE_WCDMA		0x30
#define NIF_TYPE_CDMA2K		0x40
#define NIF_TYPE_WMX		0x50
#define NIF_TYPE_LTE		0x60
#define NIF_TYPE_ETHERNET	0x70

// HAL Disconnect Reason
#define DC_REASON_DISCONNECT_BY_USER				1
#define DC_REASON_DISCONNECT_BY_BS					2
#define DC_REASON_SYNCHRONIZATION_LOST				3
#define DC_REASON_NO_CIRCUIT_OR_CHANNEL_AVAILABLE	4
#define DC_REASON_NETWORK_ENTRY_FAILURE				5
#define DC_REASON_AUTHENTICATION_FAILURE			6
#define DC_REASON_USER_SUSPEND_NETWORK_ENTRY		7
#define DC_REASON_HANDOVER_FAILURE					8
#define DC_REASON_MISC_FAILURE						9

#endif /* MSG_HAL_H */
