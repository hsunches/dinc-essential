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

#ifndef UTIL_NET_H
#define UTIL_NET_H

#include <netinet/in.h>

int query_server_addr(struct sockaddr_in6 addr_list[], int *p_addr_cnt, const char *domain_name, int max_retry);
// int query_txt_rec(char *txt_rec, const char *domain_name);
// REMOVED
#endif
