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
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "data_dev.h"
// #include "md5.h"

#define MAC_LENGTH 	6
#define BUFF_SIZE 	256

struct din_msg {
    uint32_t type;
    uint32_t dc_id;

    uint8_t content[64];
};

//static void gen_uid(char *uid, const uint8_t *data, int len) {
	// md5_state_t state;
	// md5_byte_t digest[16];
	// int i;

	// md5_init(&state);
	// md5_append(&state, data, len);
	// md5_finish(&state, digest);

	// for (i = 0; i < 8; i++) {	// ignore the lower half
	// 	sprintf(&uid[i + i], "%02X", digest[i]);
	// }
//}

void gen_uid_from_mac_addr(char *uid, uint8_t mac_addr[MAC_LENGTH]) {
    int i;
	memset(uid, '0', DEV_UID_LEN);
    for (i = 0; i < MAC_LENGTH; ++i)
    {
        sprintf(&uid[i + i + 4], "%02X", mac_addr[i]);
    }
}

int send_request_for_uid(uint32_t type, char *ipstr, uint8_t* p_get) 
{
    int ret = 0;
    int fd;
    fd_set readfds;

    struct sockaddr_in addr;
    struct timeval timeout;

    // timeout after 5 seconds
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    int select_cnt;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    struct din_msg msg;
    do {

        fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (fd < 0) 
        {
            break;
        }

        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = (ipstr == NULL) ? htonl(INADDR_LOOPBACK) : inet_addr(ipstr);
        addr.sin_port = htons(56000);
        msg.type = htonl(type);

        ret = sendto(fd, &msg, sizeof(msg.type) + sizeof(msg.dc_id), 0, (struct sockaddr *)&addr, sizeof(addr));

        // ready to read response
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);
        int maxfd = fd;
        while (1)
        {
            select_cnt = select(maxfd + 1, &readfds, NULL, NULL, &timeout);

            if (select_cnt < 0) 
            {
                perror("select");
                break;
            }

            uint8_t rbuf[BUFF_SIZE];
            memset(rbuf, 0, sizeof(rbuf));

            if (select_cnt > 0)
            {
                int recv_len = recvfrom(fd, rbuf, BUFF_SIZE, 0, (struct sockaddr *) &addr, &addr_len);

                if (recv_len == -1)
                {
                    perror("recvfrom\n");
                    break;
                }
                memcpy(p_get, rbuf, recv_len);
                break;
            }
            else
            {
                break; // timeout
            }
        }
        close(fd);
    } while (0);

    return ret;
}