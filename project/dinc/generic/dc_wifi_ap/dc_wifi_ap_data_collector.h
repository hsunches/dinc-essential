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

#ifndef DC_DATA_COLLECTOR_H
#define DC_DATA_COLLECTOR_H

typedef int (*write_func)(const void *data, int len);

int clct_wifi_ap_dev_info(write_func writer);
int clct_wifi_ap_routine_info(write_func writer);

#endif
