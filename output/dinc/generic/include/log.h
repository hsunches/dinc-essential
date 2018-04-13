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

#ifndef UTIL_LOG_H
#define UTIL_LOG_H

#ifdef DEBUG_MODE
#	include <unistd.h>
#	include <syslog.h>
#	include <errno.h>
#	include <sys/syscall.h>

#	define OPEN_LOGG(label)			openlog(label " ", LOG_PID | LOG_PERROR, LOG_DAEMON)
#	define LOGG_BASE(lv, fmt, ...)	syslog(LOG_##lv, "[%ld][" #lv "] " fmt "%s", syscall(SYS_gettid), __VA_ARGS__)
#	define LOGG(lv, ...)			LOGG_BASE(lv, __VA_ARGS__, "")

#	define LOGG_DBG(...)			LOGG(DEBUG, __VA_ARGS__)
#	define LOGG_INFO(...)			LOGG(INFO, __VA_ARGS__)
#	define LOGG_WARN(...)			LOGG(WARNING, __VA_ARGS__)
#	define LOGG_ERR(...)			LOGG(ERR, __VA_ARGS__)

#	define LOGG_ERRNO(s)			LOGG_ERR("%s: %s", s, strerror(errno))

#	define LOGG_FUNC_IN()			LOGG_DBG(">> %s()", __FUNCTION__)
#	define LOGG_FUNC_OUT()			LOGG_DBG("<< %s()", __FUNCTION__)
#else
#	define OPEN_LOGG(label)
#	define LOGG_BASE(lv, fmt, ...)
#	define LOGG(lv, ...)

#	define LOGG_DBG(...)
#	define LOGG_INFO(...)
#	define LOGG_WARN(...)
#	define LOGG_ERR(...)

#	define LOGG_ERRNO(s)

#	define LOGG_FUNC_IN()
#	define LOGG_FUNC_OUT()
#endif

#endif
