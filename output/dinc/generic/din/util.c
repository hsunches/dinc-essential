#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdarg.h>
#include<limits.h>
#include<math.h>
#include<float.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<arpa/inet.h>
#include<openssl/ssl.h>
#include<errno.h>
#include<netinet/in.h>
#include<netinet/tcp.h>
#include<netdb.h>
#include<fcntl.h>
#include<signal.h>
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
l117_digits);l24_typedef l13_enum l244__ipc_msg_type{
l186_IPC_MSG_NETWORK_SEARCH=0x80AA0001,l192_IPC_MSG_NETWORK_UP,
l195_IPC_MSG_NETWORK_DOWN,l163_IPC_MSG_DC_REGISTER,
l154_IPC_MSG_DC_REGISTER_ACK,l160_IPC_MSG_DC_SHUT_DOWN,
l187_IPC_MSG_DC_START,l208_IPC_MSG_DC_STOP,l162_IPC_MSG_DC_STATUS,
l169_IPC_MSG_DC_STATUS_ACK,l196_IPC_MSG_SEARCH_SERVER_WAIT,
l197_IPC_MSG_SEARCH_SERVER_FAIL,l125_IPC_MSG_SERVER_LOOKUP_RESULT,
l170_IPC_MSG_GET_LATENCY,l177_IPC_MSG_GET_LATENCY_ACK,
l199_IPC_MSG_REPORT_UID,l203_IPC_MSG_SPECIFY_UID,
l206_IPC_MSG_REPORT_FULL_DOMAIN,l204_IPC_MSG_REPORT_LATENCY_FAIL_CNT,
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
#include"unmobric.h"
#include"log.h"
#include"mobric.h"
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
l624_dev_allow_web_access_from_wan(la_int l403_sec);lb_void
_mb000010000(lb_void);lt_uint64_t l418_util_get_dev_uid(lb_void);
la_int l1115_util_allow_web_access_from_wan(la_int( *
l811_allow_access)(la_int l156_enable),la_int l403_sec);lm_uint32_t
l428_util_string_replace_token(lj_char*l487_pstr,li_const lj_char
l98_token,li_const lj_char l776_replent);le_struct l158_stat_tbl
_mb000000001[4];la_int _mb000000006=0;le_struct l104_sockaddr_in
_mb000000005;lm_uint32_t _mb000000003[5];lm_uint32_t _mb000000004;
l17_int64_t _mb000000011;la_int _mb000000008=0;la_int _mb000000010=0;
la_int _mb000000009=0;la_int _mb000000007=0;la_int _mb000000002=0;
lk_static la_int l416_g_dc_id;lk_static lm_uint32_t
l949_util_get_round_trip_latency(lb_void);lm_uint32_t
l428_util_string_replace_token(lj_char*l487_pstr,li_const lj_char
l98_token,li_const lj_char l776_replent){lm_uint32_t l63_cnt=0;lf_if(
l487_pstr==lu_NULL){lq_return l63_cnt;}l48_size_t lv_len=l377_strlen(
l487_pstr);lm_uint32_t ld_i=0;l21_for(ld_i=0;ld_i<lv_len;ld_i++){
lf_if(l487_pstr[ld_i]==l98_token){l487_pstr[ld_i]=l776_replent;
l63_cnt++;}}lq_return l63_cnt;}la_int l188_util_parse_options(la_int
l31_argc,lj_char*l18_argv[],l56_dc_routine_definition*l15_def){la_int
l322_res=-1;la_int l94_opt;lf_if(l15_def->l1058_dc_ext_cmd==1){
lq_return 0;}l62_while((l94_opt=l1109_getopt(l31_argc,l18_argv,"\x63"
"\x3a\x76"))!=-1){lf_if(l94_opt==-1){ly_break;}l107_switch(l94_opt){
l7_case'c':{lf_if(l15_def->l834_dc_load_config!=lu_NULL){l15_def->
l834_dc_load_config(l88_optarg);}l322_res=0;}ly_break;l7_case'v':{
_mb000010000();lf_if(l15_def->l809_dc_version!=lu_NULL){l15_def->
l809_dc_version();}l322_res=-1;}ly_break;l238_default:{}ly_break;}}
lq_return l322_res;}la_int l137_util_write_data_to_ipc_channel(
li_const lb_void*ln_data,la_int lv_len){lq_return l657_sendto(
_mb000000006,ln_data,lv_len,0,(le_struct l103_sockaddr* )&
_mb000000005,lw_sizeof(_mb000000005));}lk_static lm_uint32_t
l949_util_get_round_trip_latency(lb_void){lq_return _mb000000004;}
la_int l185_util_start_ipc_routine(l56_dc_routine_definition*l15_def){
la_int l156_enable;l699_fd_set l155_fds;le_struct l146_timeval
l89_timeout;la_int l152_select_cnt;lj_char l122_buffer[1024];la_int
l168_msg_len;la_int l586_dc_report_interval=0;la_int
l108_idle_threshold=0;l1123_dc_routine_context l190_context={};
l17_int64_t l457_handover_start_usec;l17_int64_t l101_timeout_usec;
l17_int64_t l389_select_start_usec=0;l17_int64_t
l396_select_duration_usec=0;l17_int64_t l388_routine_start_usec=0;
l17_int64_t l398_routine_duration_usec=0;l13_enum{l274_INIT,
l627_REG_OK,l287_AUTH_OK,}l65_state;l156_enable=1;l65_state=l274_INIT
;l457_handover_start_usec=0;l101_timeout_usec=0;l416_g_dc_id=l15_def
->l16_dc_id;l190_context.l1155_send_dc_report=&_mb000010011;
l190_context.l1134_send_dc_round_trip_latency_request=&
l210_util_send_round_trip_latency_request;l190_context.
l1169_send_dc_connection_history_information=&_mb000010010;
l190_context.l1175_get_dc_latest_round_trip_latency=&
l949_util_get_round_trip_latency;l62_while(l156_enable){FD_ZERO(&
l155_fds);FD_SET(_mb000000006,&l155_fds);lf_if(
l586_dc_report_interval==0&&l15_def->l619_dc_generate_report_interval
!=lu_NULL){la_int l382_interval=l15_def->
l619_dc_generate_report_interval();l190_context.
l709_report_interval_countdown=l586_dc_report_interval=(l382_interval
>0)?l382_interval:0;}lf_if(l101_timeout_usec<=0){l86_memset(&
l89_timeout,0,lw_sizeof(l89_timeout));}l3_else{l89_timeout.
l384_tv_sec=(l4_long)(l101_timeout_usec/1000000);l89_timeout.
l366_tv_usec=(l4_long)(l101_timeout_usec%1000000);}
l389_select_start_usec=_mb000010009();l152_select_cnt=l692_select(
_mb000000006+1,&l155_fds,lu_NULL,lu_NULL,&l89_timeout);lf_if(
l152_select_cnt<0){l508_perror("\x73\x65\x6c\x65\x63\x74");lq_return-
1;}lf_if(l152_select_cnt>0){l396_select_duration_usec=_mb000010009()-
l389_select_start_usec;l101_timeout_usec-=l396_select_duration_usec;
l168_msg_len=l748_recvfrom(_mb000000006,&l122_buffer,lw_sizeof(
l122_buffer),0,lu_NULL,lu_NULL);lf_if(l168_msg_len<0){l508_perror(""
"\x72\x65\x63\x76\x66\x72\x6f\x6d");ly_break;}lf_if(l168_msg_len<
lw_sizeof(le_struct l33_data_header)){l288_continue;}le_struct
l33_data_header*l30_header=(le_struct l33_data_header* )l122_buffer;
lf_if(l250_ntohl(l30_header->l16_dc_id)!=l15_def->l16_dc_id){
l288_continue;}l107_switch(l250_ntohl(l30_header->l9_type)){l7_case
l154_IPC_MSG_DC_REGISTER_ACK:{lf_if(l168_msg_len<lw_sizeof(le_struct
l33_data_header)+lw_sizeof(le_struct l128_dc_register_ack)){
l288_continue;}le_struct l128_dc_register_ack*ln_data=(le_struct
l128_dc_register_ack* )(l122_buffer+lw_sizeof(le_struct
l33_data_header));lf_if(l168_msg_len==(lw_sizeof(le_struct
l33_data_header)+lw_sizeof(le_struct l128_dc_register_ack))){
l65_state|=l627_REG_OK;_mb000010008(ln_data->l126_net_up_time_list);
lf_if(l15_def->l1065_on_network_entry_complete!=lu_NULL){l15_def->
l1065_on_network_entry_complete(&l190_context,ln_data->
l141_net_search_latency);}lf_if(l15_def->
l619_dc_generate_report_interval!=lu_NULL){la_int l382_interval=
l15_def->l619_dc_generate_report_interval();lf_if(l382_interval>0){
l190_context.l709_report_interval_countdown=l586_dc_report_interval=
l382_interval;}}}}ly_break;l7_case l125_IPC_MSG_SERVER_LOOKUP_RESULT:
{lf_if(l168_msg_len<lw_sizeof(le_struct l33_data_header)+lw_sizeof(
le_struct l95_dc_data)){l288_continue;}le_struct l95_dc_data*
l61_result=(le_struct l95_dc_data* )(l122_buffer+lw_sizeof(le_struct
l33_data_header));l108_idle_threshold=l61_result->lo_value[1];lf_if(!
l61_result->lo_value[0]){l156_enable=0;lf_if(l15_def->
l1088_on_server_lookup_failed!=lu_NULL){l15_def->
l1088_on_server_lookup_failed(&l190_context);}}l3_else{l65_state|=
l287_AUTH_OK;lf_if(l15_def->l1091_on_server_lookup_success!=lu_NULL){
l15_def->l1091_on_server_lookup_success(&l190_context);}}}ly_break;
l7_case l177_IPC_MSG_GET_LATENCY_ACK:{le_struct l95_dc_data*
l61_result=(le_struct l95_dc_data* )(l122_buffer+lw_sizeof(le_struct
l33_data_header));lf_if(l15_def->l1073_on_check_latency_ack!=lu_NULL){
l15_def->l1073_on_check_latency_ack(&l190_context,l61_result->
lo_value[0]);}_mb000010007(l61_result->lo_value[0]);}ly_break;l7_case
l160_IPC_MSG_DC_SHUT_DOWN:{l156_enable=0;}ly_break;l7_case
l162_IPC_MSG_DC_STATUS:{le_struct l127_din_local_msg l39_msg;l39_msg.
l30_header.l9_type=l68_htonl(l169_IPC_MSG_DC_STATUS_ACK);l39_msg.
l30_header.l16_dc_id=l68_htonl(l15_def->l16_dc_id);
l137_util_write_data_to_ipc_channel(&l39_msg,lw_sizeof(l39_msg.
l30_header));}ly_break;l7_case l153_IPC_MSG_CUSTOM_EVENT:{lf_if(
l168_msg_len<lw_sizeof(le_struct l33_data_header)+lw_sizeof(le_struct
l95_dc_data)){l288_continue;}le_struct l95_dc_data*l61_result=(
le_struct l95_dc_data* )(l122_buffer+lw_sizeof(le_struct
l33_data_header));lf_if(!l599_strncmp("\x48\x4f\x42\x4e",(lj_char* )&
l61_result->lo_value[0],4)&&(l15_def->l1050_on_handover_start!=
lu_NULL)){l457_handover_start_usec=_mb000010009();l15_def->
l1050_on_handover_start(_mb000010009());}l3_else lf_if(!l599_strncmp(""
"\x48\x4f\x45\x53",(lj_char* )&l61_result->lo_value[0],4)&&(l15_def->
l818_on_handover_end!=lu_NULL)){li_const l17_int64_t l319_timestamp=
_mb000010009();li_const l17_int64_t l75_latency=l319_timestamp-
l457_handover_start_usec;l15_def->l818_on_handover_end(1,
l319_timestamp,l75_latency);l457_handover_start_usec=0;}l3_else lf_if
(!l599_strncmp("\x48\x4f\x45\x46",(lj_char* )&l61_result->lo_value[0]
,4)&&(l15_def->l818_on_handover_end!=lu_NULL)){li_const l17_int64_t
l319_timestamp=_mb000010009();li_const l17_int64_t l75_latency=
l319_timestamp-l457_handover_start_usec;l15_def->l818_on_handover_end
(0,l319_timestamp,l75_latency);l457_handover_start_usec=0;}}ly_break;
l238_default:{l15_def->l1138_handle_extra_ipc_message(&l190_context,
l250_ntohl(l30_header->l9_type));}ly_break;}}l3_else{l107_switch(
l65_state){l7_case l274_INIT:{le_struct l127_din_local_msg l39_msg;
l39_msg.l30_header.l9_type=l68_htonl(l163_IPC_MSG_DC_REGISTER);
l39_msg.l30_header.l16_dc_id=l68_htonl(l15_def->l16_dc_id);
l137_util_write_data_to_ipc_channel(&l39_msg,lw_sizeof(l39_msg.
l30_header));l101_timeout_usec=1000000;lf_if(l15_def->
l1058_dc_ext_cmd==1){l156_enable=0;ly_break;}}ly_break;l238_default:{
lf_if((l65_state&l287_AUTH_OK)==l287_AUTH_OK){l388_routine_start_usec
=_mb000010009();lf_if(l15_def->l1119_collect_dc_routine_info!=lu_NULL
){l190_context.l709_report_interval_countdown--;l15_def->
l1119_collect_dc_routine_info(&l190_context,l586_dc_report_interval,
l108_idle_threshold);}lf_if(l190_context.
l709_report_interval_countdown<=0&&l15_def->
l619_dc_generate_report_interval!=lu_NULL){la_int l382_interval=
l15_def->l619_dc_generate_report_interval();lf_if(l382_interval>0){
l190_context.l709_report_interval_countdown=l586_dc_report_interval=
l382_interval;}}l398_routine_duration_usec=_mb000010009()-
l388_routine_start_usec;l101_timeout_usec=1000000-
l398_routine_duration_usec;}}ly_break;}}}lq_return 0;}lt_uint64_t
l418_util_get_dev_uid(lb_void){lf_if(l123_g_dev_info_report.l44_uid==
0){lj_char l44_uid[16+1];lf_if(l623_dev_get_uid(l44_uid)<0){lq_return
-1;}l3_else{l123_g_dev_info_report.l44_uid=(lt_uint64_t)l1160_strtoull
(l44_uid,lu_NULL,16);}}lq_return l123_g_dev_info_report.l44_uid;}
la_int l201_util_send_report_ex(li_const la_int l49_msg_type,li_const
la_int l82_extra_role,li_const ll_uint8_t*ln_data,li_const la_int
lv_len,li_const la_int l16_dc_id){l416_g_dc_id=l16_dc_id;lq_return
_mb000010011(l49_msg_type,l82_extra_role,ln_data,lv_len);}la_int
_mb000010011(li_const la_int l49_msg_type,li_const la_int
l82_extra_role,li_const ll_uint8_t*ln_data,li_const la_int lv_len){
ll_uint8_t l122_buffer[1024];le_struct l130_dc_report_header*
l30_header=(le_struct l130_dc_report_header* )(l122_buffer);
l30_header->l30_header.l9_type=l68_htonl(l105_IPC_MSG_SEND_REPORT);
l30_header->l30_header.l16_dc_id=l68_htonl(l416_g_dc_id);l30_header->
l81_role=(l416_g_dc_id&0x3F)|l82_extra_role;l30_header->l49_msg_type=
l49_msg_type;ll_uint8_t*lc_p=l122_buffer+lw_sizeof(le_struct
l130_dc_report_header);lf_if((l30_header->l81_role&
l267_DINP_HDR_MASK_UID)==l267_DINP_HDR_MASK_UID){{l17_int64_t lg_src=
_mb000010003(l123_g_dev_info_report.l44_uid);_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),64/8);lc_p+=(64)/8;};}l109_memcpy(l122_buffer+(
lc_p-l122_buffer),ln_data,lv_len);lq_return
l137_util_write_data_to_ipc_channel(l122_buffer,lc_p-l122_buffer+
lv_len);}la_int _mb000010010(li_const ll_uint8_t*ln_data,li_const
la_int lv_len){ll_uint8_t l122_buffer[1024];le_struct
l130_dc_report_header*l700_info=(le_struct l130_dc_report_header* )(
l122_buffer);l700_info->l30_header.l9_type=l68_htonl(
l178_IPC_MSG_SEND_CONN_HISTORY_INFO);l700_info->l30_header.l16_dc_id=
l68_htonl(l416_g_dc_id);l700_info->l81_role=(l416_g_dc_id&0x3F);
l700_info->l49_msg_type=0x02;l109_memcpy(l122_buffer+lw_sizeof(
le_struct l130_dc_report_header),ln_data,lv_len);lq_return
l137_util_write_data_to_ipc_channel(l122_buffer,lw_sizeof(le_struct
l130_dc_report_header)+lv_len);}la_int
l210_util_send_round_trip_latency_request(lb_void){le_struct
l33_data_header ln_data;ln_data.l9_type=l68_htonl(
l170_IPC_MSG_GET_LATENCY);ln_data.l16_dc_id=l68_htonl(l416_g_dc_id);
lq_return l137_util_write_data_to_ipc_channel(&ln_data,lw_sizeof(
ln_data));}la_int util_start_dc_routine(la_int l31_argc,lj_char*
l18_argv[],l56_dc_routine_definition*l15_def){lf_if(l15_def->
l1089_dc_init!=lu_NULL){l15_def->l1089_dc_init();}lf_if(
l188_util_parse_options(l31_argc,l18_argv,l15_def)!=0){lq_return 1;}
lf_if(_mb000010001(l15_def->l1182_dc_ip,l15_def->l1130_dc_port)<0){
lq_return 1;}lf_if(l185_util_start_ipc_routine(l15_def)<0){lq_return 1
;}lq_return 0;}la_int _mb000010001(lj_char*l111_ipstr,la_int l124_port
){l111_ipstr=(l111_ipstr==lu_NULL)?"\x31\x32\x37\x2e\x30\x2e\x30\x2e"
"\x31":l111_ipstr;l124_port=(l124_port==0)?56000:l124_port;
_mb000000006=l450_socket(l145_AF_INET,l400_SOCK_DGRAM,
l749_IPPROTO_UDP);lf_if(_mb000000006==-1){lq_return(-1);}l86_memset(&
_mb000000005,0,lw_sizeof(_mb000000005));_mb000000005.l589_sin_family=
l145_AF_INET;_mb000000005.l548_sin_port=l503_htons((l36_unsigned
l1157_short)l124_port);_mb000000005.l371_sin_addr.l594_s_addr=
l1056_inet_addr(l111_ipstr);lq_return 0;}l17_int64_t _mb000010009(
lb_void){le_struct l146_timeval l146_timeval={0,0};lf_if(
l1086_gettimeofday(&l146_timeval,lu_NULL)==-1){l142_LOGG_ERRNO("\x67"
"\x65\x74\x74\x69\x6d\x65\x6f\x66\x64\x61\x79");lq_return-1;}
lq_return(l17_int64_t)((l17_int64_t)l146_timeval.l384_tv_sec*1000000+
l146_timeval.l366_tv_usec);}lb_void _mb000010008(li_const lm_uint32_t
l209_conn_time[]){l109_memcpy(_mb000000003,l209_conn_time,lw_sizeof(
_mb000000003));}lb_void _mb000010007(li_const lm_uint32_t l75_latency
){_mb000000004=l75_latency;}l25_uint16_t _mb000010005(l25_uint16_t
l12_val){lf_if(( * (l25_uint16_t* )"\x0\x1">>8)){l12_val=(
l25_uint16_t)(((l12_val&0xFF00)>>8)|((l12_val&0x00FF)<<8));}lq_return
l12_val;}lm_uint32_t _mb000010002(lm_uint32_t l12_val){lf_if(( * (
l25_uint16_t* )"\x0\x1">>8)){l12_val=(lm_uint32_t)(((l12_val&
0xFF000000)>>24)|((l12_val&0x00FF0000)>>8)|((l12_val&0x0000FF00)<<8)|
((l12_val&0x000000FF)<<24));}lq_return l12_val;}lt_uint64_t
_mb000010003(lt_uint64_t l12_val){lf_if(( * (l25_uint16_t* )"\x0\x1"
>>8)){l12_val=(lt_uint64_t)(((l12_val&0xFF00000000000000ULL)>>56)|((
l12_val&0x00FF000000000000ULL)>>40)|((l12_val&0x0000FF0000000000ULL)>>
24)|((l12_val&0x000000FF00000000ULL)>>8)|((l12_val&
0x00000000FF000000ULL)<<8)|((l12_val&0x0000000000FF0000ULL)<<24)|((
l12_val&0x000000000000FF00ULL)<<40)|((l12_val&0x00000000000000FFULL)<<
56));}lq_return l12_val;}lb_void*_mb000010004(lb_void*l171_dst,
li_const lb_void*lg_src,l48_size_t l70_n){l48_size_t ld_i;l21_for(
ld_i=0;ld_i<l70_n;ld_i++){ * ((lj_char* )l171_dst+ld_i)= * ((lj_char*
)lg_src+ld_i);}lq_return l171_dst;}la_int l215_util_memcmp(li_const
lb_void*l211_s1,li_const lb_void*l214_s2,l48_size_t l70_n){li_const
ll_uint8_t*l1067_a1=(li_const ll_uint8_t* )l211_s1;li_const ll_uint8_t
 *l1066_a2=(li_const ll_uint8_t* )l214_s2;l48_size_t ld_i;l21_for(
ld_i=0;ld_i<l70_n;ld_i++){la_int l78_diff=(la_int)l1067_a1[ld_i]-(
la_int)l1066_a2[ld_i];lf_if(l78_diff!=0){lq_return l78_diff;}}
lq_return 0;}l48_size_t _mb000010006(li_const lj_char*l113_s){
li_const lj_char*lc_p=l113_s-1;l62_while( * ++lc_p);lq_return lc_p-
l113_s;}lr_double l216_util_simple_sqrt(lr_double l12_val,lr_double
l179_errors){lf_if(l12_val<0){lq_return 0;}lr_double l532_top=(
l12_val>1)?l12_val:1;lr_double l561_bottom=0;lr_double l61_result=0;
lr_double l78_diff=0;l118_do{l61_result=(l532_top+l561_bottom)/2;
l78_diff=(l61_result*l61_result)-l12_val;lf_if(l78_diff>0){l532_top=
l61_result;}l3_else lf_if(l78_diff<0){l561_bottom=l61_result;l78_diff
 *=-1;}lf_if(l78_diff==0||l78_diff<l179_errors)ly_break;}l62_while(
l78_diff>l179_errors);lq_return l61_result;}la_int
l1115_util_allow_web_access_from_wan(la_int( *l811_allow_access)(
la_int l156_enable),la_int l403_sec){la_int l8_ret=0;li_const
l433_pid_t l962_cpid=l775_fork();lf_if(l962_cpid<0){l8_ret=-1;}lf_if(
l962_cpid==0){la_int l8_ret=0;lf_if((l8_ret=l811_allow_access(1))!=0){
l64_LOGG_ERR("\x45\x6e\x61\x62\x6c\x65\x20\x61\x63\x63\x65\x73\x73"
"\x20\x66\x72\x6f\x6d\x20\x57\x41\x4e\x20\x66\x75\x6e\x63\x74\x69\x6f"
"\x6e\x20\x66\x61\x69\x6c\x65\x64\x2e\x20\x52\x65\x73\x75\x6c\x74\x3a"
"\x20\x25\x64",l8_ret);l426_exit(l8_ret);}l27_LOGG_INFO("\x45\x6e\x61"
"\x62\x6c\x65\x20\x61\x63\x63\x65\x73\x73\x20\x66\x72\x6f\x6d\x20\x57"
"\x41\x4e\x2e\x20\x52\x65\x73\x75\x6c\x74\x3a\x20\x25\x64",l8_ret);
l27_LOGG_INFO("\x53\x74\x61\x72\x74\x20\x74\x6f\x20\x73\x6c\x65\x65"
"\x70\x2e\x2e\x2e");l1170_sleep(l403_sec);l27_LOGG_INFO("\x53\x74\x6f"
"\x70\x20\x73\x6c\x65\x65\x70\x69\x6e\x67\x2e\x2e\x2e");l8_ret=
l811_allow_access(0);l27_LOGG_INFO("\x44\x69\x73\x61\x62\x6c\x65\x20"
"\x61\x63\x63\x65\x73\x73\x20\x66\x72\x6f\x6d\x20\x57\x41\x4e\x2e\x20"
"\x52\x65\x73\x75\x6c\x74\x3a\x20\x25\x64",l8_ret);l426_exit(l8_ret);
}lq_return l8_ret;}lr_double l131_util_unsafe_sqrt(lr_double l12_val,
la_int l117_digits){lf_if(l972_INT_MAX!=0x7FFFFFFF){l64_LOGG_ERR(""
"\x4f\x6e\x6c\x79\x20\x33\x32\x62\x69\x74\x20\x49\x4e\x54\x20\x73\x75"
"\x70\x70\x6f\x72\x74\x65\x64\x20\x6e\x6f\x77");l426_exit(1);}lf_if(
l12_val<0||l117_digits<0){lq_return 0;}lf_if(l12_val>926){l117_digits
=0;}l3_else lf_if(l12_val>9){l117_digits=1;}l3_else lf_if(l117_digits
>2){l117_digits=2;}la_int l821_pow10=1;la_int l780_pow100=1;la_int
ld_i=0;l21_for(ld_i=0;ld_i<l117_digits;ld_i++){l780_pow100*=100;
l821_pow10*=10;}la_int l983_ival=(la_int)(l12_val*l780_pow100);la_int
l532_top=(l12_val>1)?l983_ival:l780_pow100;la_int l561_bottom=0;
la_int l61_result=0;la_int l78_diff=0;l118_do{l61_result=(l532_top+
l561_bottom)/2;la_int l6_d=(l61_result*l61_result)-l983_ival;lf_if(
l6_d>0){l532_top=l61_result;}l3_else lf_if(l6_d<0){l561_bottom=
l61_result;l6_d*=-1;}lf_if(l6_d==0||l6_d==l78_diff){ly_break;}
l78_diff=l6_d;}l62_while(l78_diff>l821_pow10);lq_return(lr_double)l61_result
/l821_pow10;}
