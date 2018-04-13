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

#ifndef UTIL_MISC_H
#define UTIL_MISC_H

#include <stdint.h>
#include <sys/time.h>

void randomize(void);
int get_random(void);
void load_random_list(int list[], int *p_cnt, int base, int range);
int64_t get_usec_from_timeval(const struct timeval *p_timeval);
void get_timeval_from_usec(struct timeval *p_timeval, int64_t usec);
int64_t get_time_now_usec(void);

#endif
