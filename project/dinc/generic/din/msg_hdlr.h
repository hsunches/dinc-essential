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

#ifndef MSG_HDLR_H
#define MSG_HDLR_H

void start_msg_hdlr(void);
int send_event(uint32_t type, const void *data, int len);
int send_data(int fd, const void *data, int data_len, const struct sockaddr *p_addr, socklen_t addr_len);

#endif
