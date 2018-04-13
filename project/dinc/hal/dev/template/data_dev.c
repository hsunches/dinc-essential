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
#include <string.h>
#include <stdint.h>
#include "msg_hal.h"
#include "data_dev.h"

extern void gen_uid_from_mac_addr(char *uid, uint8_t mac_addr[6]);
extern int send_request_for_uid(uint32_t type, char *ipstr, uint8_t* p_get);

/*
 * Description      : Get the unique ID of the device.
 *
 *                    Use gen_uid_from_mac_addr() to generate an unique ID from MAC address.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : Text Format. Only accept [0-9], [A-F], [a-f].
 *
 *                    The string length should be DEV_UID_LEN.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_uid(char uid[DEV_UID_LEN + 1]) {

#ifdef SAMPLE_CODE
    uint8_t mac_addr[] = {
        0x12,
        0x23,
        0x12,
        0x23,
        0x12,
        0x23
    };

    gen_uid_from_mac_addr(uid, mac_addr);

    /*  Or you can retrieve UID from another DIN which is running on another machine by indicating its IP address (assume 
        IP address is 127.0.0.1). For detailed sample code please refer to the following code segment:

        uint8_t  getter[8];
        memset(getter, 0, sizeof(getter));

        send_request_for_uid(0x80AA000E, "127.0.0.1", getter);
        int i;
        memset(uid, '0', DEV_UID_LEN);
        for (i = 0; i < sizeof(getter); ++i)
        {
            sprintf(&uid[i + i], "%02X", getter[i]);
        }
    */
    
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the vendor name.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The string length is 1 ~ MAX_DEV_VENDOR_LEN.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_vendor(char vendor[MAX_DEV_VENDOR_LEN + 1]) {

#ifdef SAMPLE_CODE
    strcpy(vendor, "Mobric");
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the model name.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The string length is 1 ~ MAX_DEV_MODEL_LEN.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_model(char model[MAX_DEV_MODEL_LEN + 1]) {

#ifdef SAMPLE_CODE
    strcpy(model, "MIFX-N2-009");
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the firmware version.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The string length is 1 ~ MAX_DEV_FW_VER_LEN.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_fw_ver(char ver[MAX_DEV_FW_VER_LEN + 1]) {

#ifdef SAMPLE_CODE
    strcpy(ver, "1.0.6");
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the serial number.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The string length is 1 ~ MAX_DEV_SN_LEN.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_sn(char sn[MAX_DEV_SN_LEN + 1]) {

#ifdef SAMPLE_CODE
    strcpy(sn, "857234600");
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the chipset revision.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The string length is 1 ~ MAX_DEV_CHIP_REV_LEN.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_chip_rev(char rev[MAX_DEV_CHIP_REV_LEN + 1]) {

#ifdef SAMPLE_CODE
    strcpy(rev, "1.0.0");
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the CPU core count.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 1 ~ 4
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_cpu_core_cnt(int *p_cnt) {

#ifdef SAMPLE_CODE
    *p_cnt = 1;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the CPU clock rate in MHz.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 1 ~ 65535
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_cpu_clk(int *p_clk) {

#ifdef SAMPLE_CODE
    *p_clk = 600;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the main memory capacity in MB.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 1 ~ 65535
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_mem_cap(int *p_cap) {

#ifdef SAMPLE_CODE
    *p_cap = 256;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the flash memory capacity in MB.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 1 ~ 65535
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_flash_cap(int *p_cap) {

#ifdef SAMPLE_CODE
    *p_cap = 1024;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the battery capacity in mAh.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 1 ~ 65535
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_batt_cap(int *p_cap) {

#ifdef SAMPLE_CODE
    *p_cap = 3000;
    return 0;

#else
    return -1;

#endif

}

/*
 * Description      : Get the battery temperature in Celsius.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : -127 ~ 128
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_batt_temp(int *p_temp) {

#ifdef SAMPLE_CODE
    *p_temp = 35;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the device temperature in Celsius.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : -127 ~ 128
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_temp(int *p_temp) {

#ifdef SAMPLE_CODE
    *p_temp = 39;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the current CPU usage in percentage.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 100
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_cpu_usage(int *p_usage) {

#ifdef SAMPLE_CODE
    *p_usage = 30;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the current main memory usage in percentage.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 100
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_mem_usage(int *p_usage) {

#ifdef SAMPLE_CODE
    *p_usage = 23;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the current battery level in percentage.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : 0 ~ 100
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_batt_lv(int *p_lv) {

#ifdef SAMPLE_CODE
    *p_lv = 69;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the device types on all USB ports.
 *
 *                    Possible USB device types
 *                    -------------------------
 *                    DEV_USB_NOT_CONNECTED
 *                    DEV_USB_AUDIO
 *                    DEV_USB_AUDIO_VIDEO
 *                    DEV_USB_IMAGE
 *                    DEV_USB_NIF
 *                    DEV_USB_PRINTER
 *                    DEV_USB_MASS_STOARAGE
 *                    DEV_USB_HUB
 *                    DEV_USB_OTHER
 *                    DEV_USB_DEV_PORT
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The USB port count is up to MAX_DEV_USB_DEV_CNT.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_usb_devs(int class_codes[MAX_DEV_USB_DEV_CNT], int *p_cnt) {

#ifdef SAMPLE_CODE
    int codes[] = {
        DEV_USB_AUDIO,
        DEV_USB_MASS_STOARAGE
    };

    memcpy(class_codes, codes, sizeof(codes));
    *p_cnt = sizeof(codes) / sizeof(codes[0]);
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get the information of NIFs (network interfaces).
 *
 *                    Possible NIF types
 *                    ------------------
 *                    NIF_TYPE_WIFI
 *                    NIF_TYPE_2G
 *                    NIF_TYPE_WCDMA
 *                    NIF_TYPE_CDMA2K
 *                    NIF_TYPE_WMX
 *                    NIF_TYPE_LTE
 *                    NIF_TYPE_ETHERNET
 *
 *                    If the NIF type is NIF_TYPE_WIFI, NIF_TYPE_WIMAX or NIF_TYPE_ETHERNET, fill the MAC address field of the nif structure.
 *
 *                    Otherwise, fill both the MAC address, the IMSI (international mobile subscriber identity) and the IMEI
 *
 *                    (international mobile station equipment identity) fields.
 *
 *                    If the IMSI is not available, leave it unchanged.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : The NIF count is up to MAX_DEV_NIF_CNT.
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_nifs(struct nif nifs[MAX_DEV_NIF_CNT], int *p_cnt) {

#ifdef SAMPLE_CODE
    uint8_t mac_addr[] = {
        0x12,
        0x23,
        0x12,
        0x23,
        0x12,
        0x23
    };

    nifs[0].type = NIF_TYPE_WMX;
    memcpy(nifs[0].mac_addr, mac_addr, sizeof(mac_addr));
    
    nifs[1].type = NIF_TYPE_LTE;
    memcpy(nifs[1].mac_addr, mac_addr, sizeof(mac_addr));
    nifs[1].imsi = 460001234567890ULL;
    nifs[1].imei = 123451234567890ULL;

    nifs[2].type = NIF_TYPE_WIFI;
    memcpy(nifs[2].mac_addr, mac_addr, sizeof(mac_addr));
    nifs[2].rssi = -65;

    *p_cnt = 3;
    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : Get one neighboring WiFi information.
 *
 * Return Code      : 0 for success, -1 for failure or unsupported.
 *
 * Data Valid Range : Assign the one which owns the highest rssi value of all neighbors
 *
 * Reference        : 
 *
 * Remarks          : 
 *
 */
int dev_get_neighbor_wifi_info(struct nif* neighbor) {

#ifdef SAMPLE_CODE
    uint8_t mac_addr[] = {
        0x01,
        0x23,
        0x45,
        0x67,
        0x89,
        0xAB
    };

    memcpy(neighbor->mac_addr, mac_addr, sizeof(mac_addr));

    neighbor->rssi = -65;

    return 0;

#else

#endif
    return -1;
}

/*
 * Description      : FTP auto firmware upgrade
 *
 * Return Code      : 1 for failure, 0 for success and -1 for unsupported.
 *
 * Data Valid Range :
 *
 * Reference        :
 *
 * Remarks          :
 *
 */
int dev_run_ftp_auto_firmware_upgrade(void) {
    return -1;
}
 
/*
 * Description      : Enable Web access from WAN for a certain period (in seconds)
 *
 * Return Code      : 1 for failure, 0 for success and -1 for unsupported.
 *
 * Data Valid Range :
 *
 * Reference        :
 *
 * Remarks          :
 *
 */
int dev_allow_web_access_from_wan(int sec) {
    return -1;
}