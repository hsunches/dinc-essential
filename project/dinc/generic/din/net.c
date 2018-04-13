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

#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <arpa/inet.h>
#include <resolv.h>
#include "err_code.h"
#include "dns.h"
#include "net.h"
#include "log.h"

int query_server_addr(struct sockaddr_in6 addr_list[], int *p_addr_cnt, const char *domain_name, int max_retry) 
{
	struct addrinfo hints;
	struct addrinfo *result;
	struct addrinfo *p;
	char ip_addr[40];
	int i;
	int addr_cnt;
	int ret;

	LOGG_FUNC_IN();
	addr_cnt = 0;
	ret = DIN_NO_ERR;

	do 
	{
		if (domain_name == NULL) 
		{
			ret =  DIN_INVALID_PARAM;
			break;
		}

		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_UNSPEC;
		hints.ai_flags = AI_CANONNAME;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_addr = NULL;
		hints.ai_canonname = NULL;
		hints.ai_next = NULL;

		for (i = 1; i <= max_retry; i++) 
		{
			LOGG_INFO("Query DNS server for domain name: %s, #%d", domain_name, i);

			if (!getaddrinfo(domain_name, NULL, &hints, &result)) 
			{
				break;
			}
		}

		if (i > max_retry) 
		{
			LOGG_ERRNO("getaddrinfo");
			ret = DIN_QUERY_SERVER_ADDR_FAIL;
			break;
		}

		// if (strcmp(domain_name, result->ai_canonname) != 0) {
		// 	LOGG_INFO("The input and the query result are mismatched.");
		// 	ret = DIN_QUERY_SERVER_ADDR_FAIL;
		// 	break;
		// }

		for (p = result; p != NULL && addr_cnt < *p_addr_cnt; p = p->ai_next) 
		{
			switch (p->ai_family)
			{
				case AF_INET:
				{
					inet_ntop(AF_INET, &((struct sockaddr_in *)p->ai_addr)->sin_addr, ip_addr, sizeof(ip_addr));

					if ((((struct sockaddr_in *)p->ai_addr)->sin_addr.s_addr & 0xFF) == 0x7F)
			        {
			           	p = NULL;
			        }
			        else
			        {
			        	memcpy(&addr_list[addr_cnt++], p->ai_addr, p->ai_addrlen);	
			        }

					LOGG_INFO("IPv4: ip address #%d: %s", addr_cnt + 1, ip_addr);
					break;
				}
				case AF_INET6:
				{
					inet_ntop(AF_INET6, &((struct sockaddr_in6 *)p->ai_addr)->sin6_addr, ip_addr, sizeof(ip_addr));

					if (memcmp(&in6addr_loopback, &((struct sockaddr_in6 *)p->ai_addr)->sin6_addr, sizeof(in6addr_loopback)) == 0)
          			{
            			p = NULL;
          			}
          			else
          			{
						memcpy(&addr_list[addr_cnt++], p->ai_addr, p->ai_addrlen);
					}

					LOGG_INFO("IPv6: ip address #%d: %s", addr_cnt + 1, ip_addr);
					break;
				}
			}

			if (p == NULL)
			{
				addr_cnt = 0;

				break;
			}
		}

		freeaddrinfo(result);
	} while (0);

	*p_addr_cnt = addr_cnt;

	LOGG_FUNC_OUT();
	return ret;
}

// int query_txt_rec(char *txt_rec, const char *domain_name) {
// 	u_char buf[NS_PACKETSZ];
// 	int len;
// 	my_ns_msg handle;
// 	int i;
// 	ns_rr rr;
// 	const u_char *rdata;
// 	int ret;

// 	LOGG_FUNC_IN();
// 	ret = DIN_NO_ERR;

// 	do {
// 		len = res_query(domain_name, ns_c_in, ns_t_txt, buf, sizeof(buf));

// 		if (len < 0) {
// 			LOGG_ERRNO("res_query");
// 			ret = DIN_QUERY_TXT_REC_FAIL;
// 			break;
// 		}

// 		// if (ns_initparse(buf, len, &handle) < 0) {
// 		if (my_ns_initparse(buf, len, &handle) < 0) {
// 			LOGG_ERRNO("ns_initparse");
// 			ret = DIN_QUERY_TXT_REC_FAIL;
// 			break;
// 		}

// 		for (i = 0; i < ns_msg_count(handle, ns_s_an); i++) {
// 	        // if (ns_parserr(&handle, ns_s_an, i, &rr) < 0) {
// 			if (my_ns_parserr(&handle, ns_s_an, i, &rr) < 0) {
// 	        	LOGG_ERRNO("ns_parserr");
// 	        } else if (ns_rr_type(rr) == ns_t_txt) {
// 	        	rdata = ns_rr_rdata(rr);
// 	        	len = rdata[0];
// 	        	memcpy(txt_rec, &rdata[1], len);
// 	        	txt_rec[len] = '\0';
// 	        	LOGG_INFO("TXT record: %s", txt_rec);
// 	        	break;
// 	        }
// 		}

// 		if (i >= ns_msg_count(handle, ns_s_an)) {
// 			ret = DIN_QUERY_TXT_REC_FAIL;
// 		}
// 	} while (0);

// 	LOGG_FUNC_OUT();
// 	return ret;
// }
// REMOVED
