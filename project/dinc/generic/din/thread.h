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

#ifndef UTIL_THREAD_H
#define UTIL_THREAD_H

#include <pthread.h>

#define CREATE_THREAD(id, func, arg)	pthread_create(id, NULL, func, arg)
#define CREATE_THREAD_RET				int
#define CREATE_THREAD_RET_ERR			-1

#define THREAD_ID				pthread_t
#define THREAD_FUNC_RET			void *
#define THREAD_FUNC_RET_VALUE	NULL
#define THREAD_FUNC_ARG			void *
#define THREAD_FUNC	_PTR		THREAD_ROUTINE_RET (*THREAD_ROUTINE)(THREAD_ROUTINE_ARG)

#endif
