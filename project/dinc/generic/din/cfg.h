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

#ifndef CFG_H
#define CFG_H

#define MAX_SERVER_PREFIX_LEN		16
#define MAX_SERVER_SUFFIX_LEN		16
#define MAX_SERVER_DOMAIN_NAME_LEN	64
#define MAX_SERVER_IP_ADDR_LEN		40

#define SET_CFG_STR(var, val)	strncpy(g_cfg.var, val, sizeof(g_cfg.var) - 1);
#define SET_CFG_INT(var, val)	g_cfg.var = (int)val;
#define GET_CFG(var)			g_cfg.var

void load_cfg_str(const char *s, const char *delim);
int load_cfg_file(const char *path);

extern struct cfg {
	char server_prefix[MAX_SERVER_PREFIX_LEN];
	char server_suffix[MAX_SERVER_SUFFIX_LEN];
	char server_domain_name[MAX_SERVER_DOMAIN_NAME_LEN];
	char server_ip_addr[MAX_SERVER_IP_ADDR_LEN];
	int server_port;
	int server_port_range;
	int max_dns_query;
	int max_handshake;
	int max_latency;
	int remote_msg_timeout;
	int op_mode;
	int idle_threshold;
	int dev_info_report_interval;
} g_cfg;

#endif
