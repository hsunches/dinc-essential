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
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "misc.h"
#include "err_code.h"
#include "log.h"

void randomize(void) {
	srand(time(NULL));
}

int get_random(void) {
	return rand();
}

void load_random_list(int list[], int *p_cnt, int base, int range) {
	int i;
	int swap_index;
	int temp;

	if (range > *p_cnt) {
		range = *p_cnt;
	}

	for (i = 0; i < range; i++) {
		list[i] = base + i;
	}

	randomize();

	for (i = 0; i < range; i++) {
		swap_index = get_random() % range;

		if (i != swap_index) {
			temp = list[i];
			list[i] = list[swap_index];
			list[swap_index] = temp;
		}
	}

	*p_cnt = range;
}

int64_t get_usec_from_timeval(const struct timeval *p_timeval) {
	return (int64_t)p_timeval->tv_sec * 1000000 + (int64_t)p_timeval->tv_usec;
}

void get_timeval_from_usec(struct timeval *p_timeval, int64_t usec) {
	p_timeval->tv_sec = usec / 1000000;
	p_timeval->tv_usec = usec % 1000000;
}

int64_t get_time_now_usec(void) {
	struct timeval now;

	gettimeofday(&now, NULL);
	return get_usec_from_timeval(&now);
}
