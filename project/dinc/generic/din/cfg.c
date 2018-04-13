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
#include <errno.h>
#include <netinet/in.h>
#include "cfg.h"
#include "err_code.h"
#include "log.h"

#define DFLT_CFG_PATH	"din.cfg"

#define BUF_SIZE	512

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

#define CFG_ATTR_STR(var)	{#var, CFG_STR, sizeof(g_cfg.var), g_cfg.var}
#define CFG_ATTR_INT(var)	{#var, CFG_INT, sizeof(g_cfg.var), &g_cfg.var}

enum {
	CFG_STR,
	CFG_INT
};

static const struct {
	const char *key;
	int type;
	int len;
	void *p;
} g_cfg_attr[] = {
		CFG_ATTR_STR(server_prefix),
		CFG_ATTR_STR(server_suffix),
		CFG_ATTR_STR(server_domain_name),
		CFG_ATTR_STR(server_ip_addr),
		CFG_ATTR_INT(server_port),
		CFG_ATTR_INT(server_port_range),
		CFG_ATTR_INT(max_dns_query),
		CFG_ATTR_INT(max_handshake),
		CFG_ATTR_INT(max_latency),
		CFG_ATTR_INT(remote_msg_timeout),
		CFG_ATTR_INT(op_mode),
		CFG_ATTR_INT(idle_threshold),
		CFG_ATTR_INT(dev_info_report_interval)
};

struct cfg g_cfg;

static void load_dflt_cfg(void);

void load_cfg_str(const char *s, const char *delim) 
{
	char buf[BUF_SIZE];
	char *assignment;
	char *p;
	char *key;
	int value;
	int i;

	if (s == NULL) {
		return;
	}

	if (delim == NULL) {
		delim = " ";
	}

	strncpy(buf, s, BUF_SIZE - 1);
	buf[BUF_SIZE - 1] = '\0';
	
	for (assignment = strtok(buf, delim); assignment != NULL; assignment = strtok(NULL, delim))
	{
		p = strchr(key = assignment, '=');

		if (p == NULL) 
		{
			continue;
		}

		*p++ = '\0';

		for (i = 0; i < ARRAY_SIZE(g_cfg_attr); i++) 
		{
			if (!strcmp(key, g_cfg_attr[i].key)) 
			{
				switch (g_cfg_attr[i].type) 
				{
				case CFG_STR:
					strncpy((char *)g_cfg_attr[i].p, p, g_cfg_attr[i].len - 1);
					break;
				case CFG_INT:
					errno = 0;
					value = (int)strtol(p, NULL, 10);

					if (!errno) 
					{
						*(int *)g_cfg_attr[i].p = value;
					}
					break;
				}
			}
		}
	}
}

int load_cfg_file(const char *path) 
{
	FILE *file;
	char buf[BUF_SIZE];
	int buf_usage;
	int ret;

	load_dflt_cfg();

	if (path == NULL) 
	{
		path = DFLT_CFG_PATH;
	}

	LOGG_INFO("Open configuration file: %s", path);
	file = fopen(path, "r");

	if (file == NULL) 
	{
		LOGG_ERRNO("fopen");
		return DIN_OPEN_FILE_FAIL;
	}

	buf_usage = fread(buf, 1, BUF_SIZE - 1, file);

	if (ferror(file)) 
	{
		ret = DIN_READ_FILE_FAIL;
	} 
	else 
	{
		buf[buf_usage] = '\0';
		load_cfg_str(buf, "\r\n");
		ret = DIN_NO_ERR;
	}

	fclose(file);
	return ret;
}

static void load_dflt_cfg(void) 
{
	memset(&g_cfg, 0, sizeof(g_cfg));

	SET_CFG_STR(server_prefix,		"cfg"					);
	SET_CFG_STR(server_suffix,		"dpm.mobric.com"		);
	SET_CFG_INT(server_port,		52888					);
	SET_CFG_INT(server_port_range,	10						);
	SET_CFG_INT(max_dns_query,		5						);
	SET_CFG_INT(max_handshake,		5						);
	SET_CFG_INT(max_latency,		3000					);
	SET_CFG_INT(remote_msg_timeout,	30						);
	SET_CFG_INT(op_mode,			1						);
	SET_CFG_INT(idle_threshold,		15						);
	SET_CFG_INT(dev_info_report_interval,	86400			);
}
