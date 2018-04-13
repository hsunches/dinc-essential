#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>
#include<float.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stddef.h>
#include"dc_definition.h"
#include"mobric.h"
l19_extern le_struct l158_stat_tbl{la_int l180_is_alert_needed;la_int
l100_lv[2];la_int l167_th[4];la_int l176_over_th_cnt[4];la_int
l149_win[10+1];la_int l166_win_usage;la_int l59_max;la_int l60_min;
la_int l45_mean;}_mb000000001[4];l25_uint16_t _mb000010005(
l25_uint16_t l12_val);lm_uint32_t _mb000010002(lm_uint32_t l12_val);
lt_uint64_t _mb000010003(lt_uint64_t l12_val);l17_int64_t _mb000010009
(lb_void);lb_void _mb000010008(li_const lm_uint32_t l209_conn_time[]);
lb_void _mb000010007(li_const lm_uint32_t l75_latency);la_int
l137_util_write_data_to_ipc_channel(li_const lb_void*ln_data,la_int
lv_len);la_int l185_util_start_ipc_routine(l56_dc_routine_definition*
l15_def);la_int _mb000010001(lj_char*l111_ipstr,la_int l124_port);
la_int l188_util_parse_options(la_int l31_argc,lj_char*l18_argv[],
l56_dc_routine_definition*l15_def);la_int util_start_dc_routine(
la_int l31_argc,lj_char*l18_argv[],l56_dc_routine_definition*l15_def);
la_int l210_util_send_round_trip_latency_request(lb_void);la_int
_mb000010011(li_const la_int l49_msg_type,li_const la_int
l82_extra_role,li_const ll_uint8_t*ln_data,li_const la_int lv_len);
la_int l201_util_send_report_ex(li_const la_int l49_msg_type,li_const
la_int l82_extra_role,li_const ll_uint8_t*ln_data,li_const la_int
lv_len,li_const la_int l16_dc_id);la_int _mb000010010(li_const
ll_uint8_t*ln_data,li_const la_int lv_len);lb_void*_mb000010004(
lb_void*l171_dst,li_const lb_void*lg_src,l48_size_t l70_n);la_int
l215_util_memcmp(li_const lb_void*l211_s1,li_const lb_void*l214_s2,
l48_size_t l70_n);l48_size_t _mb000010006(li_const lj_char*l113_s);
lr_double l216_util_simple_sqrt(lr_double l12_val,lr_double
l179_errors);lr_double l131_util_unsafe_sqrt(lr_double l12_val,la_int
l117_digits);
l24_typedef l13_enum l244__ipc_msg_type{l186_IPC_MSG_NETWORK_SEARCH=
0x80AA0001,l192_IPC_MSG_NETWORK_UP,l195_IPC_MSG_NETWORK_DOWN,
l163_IPC_MSG_DC_REGISTER,l154_IPC_MSG_DC_REGISTER_ACK,
l160_IPC_MSG_DC_SHUT_DOWN,l187_IPC_MSG_DC_START,l208_IPC_MSG_DC_STOP,
l162_IPC_MSG_DC_STATUS,l169_IPC_MSG_DC_STATUS_ACK,
l196_IPC_MSG_SEARCH_SERVER_WAIT,l197_IPC_MSG_SEARCH_SERVER_FAIL,
l125_IPC_MSG_SERVER_LOOKUP_RESULT,l170_IPC_MSG_GET_LATENCY,
l177_IPC_MSG_GET_LATENCY_ACK,l199_IPC_MSG_REPORT_UID,
l203_IPC_MSG_SPECIFY_UID,l206_IPC_MSG_REPORT_FULL_DOMAIN,
l204_IPC_MSG_REPORT_LATENCY_FAIL_CNT,
l178_IPC_MSG_SEND_CONN_HISTORY_INFO,l105_IPC_MSG_SEND_REPORT,
l207_IPC_MSG_SET_DEVICE_INFO,l184_IPC_MSG_START_SERVER_HANDSHAKE,
l200_IPC_MSG_DC_WHO,l153_IPC_MSG_CUSTOM_EVENT=0x80AA0001+1024,
l254_IPC_MSG_MAX=0x80AA0001+65534}l255_ipc_msg_type;l24_typedef
l13_enum l258__ipc_dc_type{l116_IPC_DC_DEV=0x80BB0001,
l232_IPC_DC_WIFI_STA,l119_IPC_DC_WIFI_AP,l220_IPC_DC_WIMAX,
l222_IPC_DC_2G,l224_IPC_DC_3G,l73_IPC_DC_LTE,l225_IPC_DC_VOIP,
l217_IPC_DC_ETHERNET,l257_IPC_DC_CUSTOM_BASE=0x80BB0001+16,
l161_IPC_DC_MAX=0x80BB0001+24}l245_ipc_dc_type;le_struct
l247_event_header{lm_uint32_t l9_type;};le_struct
l93_din_private_event{l54_union{ll_uint8_t l42_content[128];
lm_uint32_t lo_value[2];};};le_struct l99_din_command{l54_union{
ll_uint8_t l42_content[512];lm_uint32_t lo_value[6];};};
#pragma pack(1)
le_struct l132_dev_info_report{lt_uint64_t l44_uid;}
l123_g_dev_info_report;le_struct l95_dc_data{lm_uint32_t lo_value[6];
ll_uint8_t l259_extra[128];};le_struct l33_data_header{lm_uint32_t
l9_type;lm_uint32_t l16_dc_id;};le_struct l130_dc_report_header{
le_struct l33_data_header l30_header;ll_uint8_t l81_role;ll_uint8_t
l49_msg_type;};le_struct l128_dc_register_ack{lm_uint32_t
l126_net_up_time_list[5];lm_uint32_t l141_net_search_latency;};
le_struct l127_din_local_msg{le_struct l33_data_header l30_header;
l54_union{le_struct l93_din_private_event l46_event;le_struct
l99_din_command l14_cmd;};};
#pragma pack()
l13_enum{l650_DEV_USB_NOT_CONNECTED,l703_DEV_USB_AUDIO,
l720_DEV_USB_AUDIO_VIDEO,l764_DEV_USB_IMAGE,l632_DEV_USB_NIF,
l744_DEV_USB_PRINTER,l655_DEV_USB_MASS_STOARAGE,l707_DEV_USB_HUB,
l646_DEV_USB_OTHER=0xFE,l644_DEV_USB_DEV_PORT=0xFF};le_struct l151_nif
{la_int l9_type;la_int l57_rssi;le_struct{ll_uint8_t l432_mac_addr[6]
;lt_uint64_t l556_imsi;lt_uint64_t l596_imei;};};la_int
l623_dev_get_uid(lj_char l44_uid[16+1]);la_int l587_dev_get_vendor(
lj_char l284_vendor[32+1]);la_int l522_dev_get_model(lj_char
l289_model[32+1]);la_int l526_dev_get_fw_ver(lj_char l743_ver[32+1]);
la_int l524_dev_get_sn(lj_char l286_sn[32+1]);la_int
l582_dev_get_chip_rev(lj_char l722_rev[32+1]);la_int
l574_dev_get_cpu_core_cnt(la_int*l35_p_cnt);la_int
l581_dev_get_cpu_clk(la_int*l716_p_clk);la_int l523_dev_get_mem_cap(
la_int*l226_p_cap);la_int l554_dev_get_flash_cap(la_int*l226_p_cap);
la_int l538_dev_get_batt_cap(la_int*l226_p_cap);la_int
l604_dev_get_batt_temp(la_int*l334_p_temp);la_int l590_dev_get_temp(
la_int*l334_p_temp);la_int l602_dev_get_cpu_usage(la_int*l343_p_usage
);la_int l540_dev_get_mem_usage(la_int*l343_p_usage);la_int
l598_dev_get_batt_lv(la_int*l661_p_lv);la_int l616_dev_get_usb_devs(
la_int l670_class_codes[4],la_int*l35_p_cnt);la_int l539_dev_get_nifs
(le_struct l151_nif l236_nifs[4],la_int*l35_p_cnt);la_int
l630_dev_get_neighbor_wifi_info(le_struct l151_nif*l672_neighbor);
la_int l600_dev_run_ftp_auto_firmware_upgrade(lb_void);la_int
l624_dev_allow_web_access_from_wan(la_int l403_sec);
l24_typedef le_struct{lt_uint64_t l44_uid;lj_char l284_vendor[32+1];
lj_char l289_model[32+1];lj_char l490_fw_ver[32+1];lj_char l286_sn[32
+1];lj_char l468_chip_rev[32+1];la_int l673_cpu_core_cnt;la_int
l755_cpu_clk;la_int l687_mem_cap;la_int l758_flash_cap;la_int
l747_batt_cap;la_int l555_usb_dev_cnt;la_int l837_usb_devs[4];la_int
l525_nif_cnt;le_struct l151_nif l236_nifs[4];}l549_dev_data_set;
l24_typedef l13_enum{l1001_RUN_FTP_AUTO_FIRMWARE_UPGRADE=0,
l1000_ALLOW_WEB_ACCESS_FROM_WAN}l1104_dev_external_cmd_type;
l19_extern l549_dev_data_set*l26_gp_dev_data_set;la_int
l807_dev_pack_info(ll_uint8_t ln_data[]);la_int l771_dev_pack_report(
ll_uint8_t ln_data[]);lb_void _mb000010000(lb_void);
#include"unmobric.h"
#include"log.h"
#include"mobric.h"
lk_static la_int l945_clct_dev_info(ll_uint8_t*l147_p_info);lk_static
lb_void l385_clct_dev_uid(lb_void);lk_static lb_void
l926_clct_dev_vendor(lb_void);lk_static lb_void l905_clct_dev_model(
lb_void);lk_static lb_void l965_clct_dev_fw_ver(lb_void);lk_static
lb_void l1002_clct_dev_sn(lb_void);lk_static lb_void
l908_clct_dev_chip_rev(lb_void);lk_static lb_void
l912_clct_dev_cpu_core_cnt(lb_void);lk_static lb_void
l1040_clct_dev_cpu_clk(lb_void);lk_static lb_void
l981_clct_dev_mem_cap(lb_void);lk_static lb_void
l1026_clct_dev_flash_cap(lb_void);lk_static lb_void
l961_clct_dev_batt_cap(lb_void);lk_static lb_void
l932_clct_dev_usb_devs(lb_void);lk_static lb_void l1041_clct_dev_nifs
(lb_void);lk_static la_int l887_send_dev_info_msg(ll_uint8_t*
l38_p_msg,la_int lv_len);l19_extern lb_void l452_handle_options(
la_int l31_argc,lj_char*l18_argv[]);l19_extern lt_uint64_t
l418_util_get_dev_uid(lb_void);l19_extern lm_uint32_t
l428_util_string_replace_token(lj_char*l487_pstr,li_const lj_char
l98_token,li_const lj_char l776_replent);lb_void l1122_dc_dev_version
(lb_void)l189___attribute((l202_used));lb_void l930_dc_dev_init(
lb_void)l189___attribute((l202_used));lm_uint32_t l1051_dc_dev_id(
lb_void)l189___attribute((l202_used));la_int l1048_dc_dev_main(la_int
l31_argc,lj_char*l18_argv[])l189___attribute((l202_used));la_int
l1092_dc_dev_external_cmd_execute(ll_uint8_t l9_type,lm_uint32_t
l403_sec)l189___attribute((l202_used));la_int l1048_dc_dev_main(
la_int l31_argc,lj_char*l18_argv[]){l549_dev_data_set l282_ds={};
l86_memset(&l282_ds,0,lw_sizeof(l282_ds));l26_gp_dev_data_set=&
l282_ds;l930_dc_dev_init();ll_uint8_t l701_dev_info_msg[256];
ll_uint8_t l132_dev_info_report[256];ll_uint8_t*l38_p_msg;la_int
lv_len;l452_handle_options(l31_argc,l18_argv);l86_memset(
l701_dev_info_msg,0,lw_sizeof(l701_dev_info_msg));l38_p_msg=
l701_dev_info_msg;lv_len=l945_clct_dev_info(l38_p_msg);lf_if(lv_len<0
||l887_send_dev_info_msg(l701_dev_info_msg,lv_len)<0){lq_return 1;}
l86_memset(l132_dev_info_report,0,lw_sizeof(l132_dev_info_report));
l38_p_msg=l132_dev_info_report;lv_len=l771_dev_pack_report(l38_p_msg);
lf_if(lv_len<0||l887_send_dev_info_msg(l132_dev_info_report,lv_len)<0
){lq_return 1;}lq_return 0;}la_int l1092_dc_dev_external_cmd_execute(
ll_uint8_t l9_type,lm_uint32_t lo_value){la_int l8_ret=0;l107_switch(
l9_type){l7_case l1001_RUN_FTP_AUTO_FIRMWARE_UPGRADE:l8_ret=
l600_dev_run_ftp_auto_firmware_upgrade();ly_break;l7_case
l1000_ALLOW_WEB_ACCESS_FROM_WAN:l8_ret=
l624_dev_allow_web_access_from_wan((la_int)lo_value);ly_break;
l238_default:l64_LOGG_ERR("\x55\x6e\x73\x75\x70\x70\x6f\x72\x74\x65"
"\x64\x20\x45\x78\x74\x65\x72\x6e\x61\x6c\x20\x43\x6d\x64\x2e");
l8_ret=1;ly_break;}lq_return l8_ret;}lm_uint32_t l1051_dc_dev_id(
lb_void){lq_return l116_IPC_DC_DEV;}lb_void l1122_dc_dev_version(
lb_void){}lb_void l930_dc_dev_init(lb_void){}la_int l945_clct_dev_info
(ll_uint8_t*l147_p_info){l385_clct_dev_uid();l926_clct_dev_vendor();
l905_clct_dev_model();l965_clct_dev_fw_ver();l1002_clct_dev_sn();
l908_clct_dev_chip_rev();l912_clct_dev_cpu_core_cnt();
l1040_clct_dev_cpu_clk();l981_clct_dev_mem_cap();
l1026_clct_dev_flash_cap();l961_clct_dev_batt_cap();
l932_clct_dev_usb_devs();l1041_clct_dev_nifs();lq_return
l807_dev_pack_info(l147_p_info);}lk_static lb_void l385_clct_dev_uid(
lb_void){l26_gp_dev_data_set->l44_uid=l418_util_get_dev_uid();}
lk_static lb_void l926_clct_dev_vendor(lb_void){lf_if(
l587_dev_get_vendor(l26_gp_dev_data_set->l284_vendor)<0){ *
l26_gp_dev_data_set->l284_vendor=0;}l428_util_string_replace_token(
l26_gp_dev_data_set->l284_vendor,'\n',' ');}lk_static lb_void
l905_clct_dev_model(lb_void){lf_if(l522_dev_get_model(
l26_gp_dev_data_set->l289_model)<0){ *l26_gp_dev_data_set->l289_model
=0;}l428_util_string_replace_token(l26_gp_dev_data_set->l289_model,
'\n',' ');}lk_static lb_void l965_clct_dev_fw_ver(lb_void){lf_if(
l526_dev_get_fw_ver(l26_gp_dev_data_set->l490_fw_ver)<0){ *
l26_gp_dev_data_set->l490_fw_ver=0;}l428_util_string_replace_token(
l26_gp_dev_data_set->l490_fw_ver,'\n',' ');}lk_static lb_void
l1002_clct_dev_sn(lb_void){lf_if(l524_dev_get_sn(l26_gp_dev_data_set
->l286_sn)<0){ *l26_gp_dev_data_set->l286_sn=0;}
l428_util_string_replace_token(l26_gp_dev_data_set->l286_sn,'\n',' ');
}lk_static lb_void l908_clct_dev_chip_rev(lb_void){lf_if(
l582_dev_get_chip_rev(l26_gp_dev_data_set->l468_chip_rev)<0){ *
l26_gp_dev_data_set->l468_chip_rev=0;}l428_util_string_replace_token(
l26_gp_dev_data_set->l468_chip_rev,'\n',' ');}lk_static lb_void
l912_clct_dev_cpu_core_cnt(lb_void){lf_if(l574_dev_get_cpu_core_cnt(&
l26_gp_dev_data_set->l673_cpu_core_cnt)<0){l26_gp_dev_data_set->
l673_cpu_core_cnt=-1;}}lk_static lb_void l1040_clct_dev_cpu_clk(
lb_void){lf_if(l581_dev_get_cpu_clk(&l26_gp_dev_data_set->
l755_cpu_clk)<0){l26_gp_dev_data_set->l755_cpu_clk=-1;}}lk_static
lb_void l981_clct_dev_mem_cap(lb_void){lf_if(l523_dev_get_mem_cap(&
l26_gp_dev_data_set->l687_mem_cap)<0){l26_gp_dev_data_set->
l687_mem_cap=-1;}}lk_static lb_void l1026_clct_dev_flash_cap(lb_void){
lf_if(l554_dev_get_flash_cap(&l26_gp_dev_data_set->l758_flash_cap)<0){
l26_gp_dev_data_set->l758_flash_cap=-1;}}lk_static lb_void
l961_clct_dev_batt_cap(lb_void){lf_if(l538_dev_get_batt_cap(&
l26_gp_dev_data_set->l747_batt_cap)<0){l26_gp_dev_data_set->
l747_batt_cap=-1;}}lk_static lb_void l932_clct_dev_usb_devs(lb_void){
lf_if(l616_dev_get_usb_devs(l26_gp_dev_data_set->l837_usb_devs,&
l26_gp_dev_data_set->l555_usb_dev_cnt)<0){l26_gp_dev_data_set->
l555_usb_dev_cnt=-1;}}lk_static lb_void l1041_clct_dev_nifs(lb_void){
l86_memset(l26_gp_dev_data_set->l236_nifs,0xFF,lw_sizeof(
l26_gp_dev_data_set->l236_nifs));lf_if(l539_dev_get_nifs(
l26_gp_dev_data_set->l236_nifs,&l26_gp_dev_data_set->l525_nif_cnt)<0){
l26_gp_dev_data_set->l525_nif_cnt=-1;}}la_int l887_send_dev_info_msg(
ll_uint8_t*l38_p_msg,la_int l168_msg_len){la_int l0_fd;le_struct
l104_sockaddr_in l29_addr;l0_fd=l450_socket(l145_AF_INET,
l400_SOCK_DGRAM,0);lf_if(l0_fd<0){lq_return-1;}l86_memset(&l29_addr,0
,lw_sizeof(l29_addr));l29_addr.l589_sin_family=l145_AF_INET;l29_addr.
l548_sin_port=l503_htons(56000);l29_addr.l371_sin_addr.l594_s_addr=
l68_htonl(l937_INADDR_LOOPBACK);lf_if(l657_sendto(l0_fd,l38_p_msg,
l168_msg_len,0,(le_struct l103_sockaddr* )&l29_addr,lw_sizeof(
l29_addr))<0){lq_return-1;}lq_return 0;}
