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

#ifndef UTIL_DNS_H
#define UTIL_DNS_H

#include <sys/types.h>
#include <arpa/nameser.h>

typedef struct __my_ns_msg {
	const u_char	*_msg, *_eom;
	u_int16_t	_id, _flags, _counts[ns_s_max];
	const u_char	*_sections[ns_s_max];
	ns_sect		_sect;
	int		_rrnum;
	const u_char	*_msg_ptr;
} my_ns_msg;

int my_ns_initparse(const u_char *msg, int msglen, my_ns_msg *handle);
int my_ns_parserr(my_ns_msg *handle, ns_sect section, int rrnum, ns_rr *rr);

#endif
