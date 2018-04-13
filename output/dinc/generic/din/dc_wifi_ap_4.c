#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<netinet/in.h>
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
l13_enum{l773_WIFI_FREQ_2_4G=1,l812_WIFI_FREQ_3_6G=2,
l852_WIFI_FREQ_4_9G=4,l813_WIFI_FREQ_5G=8,l843_WIFI_FREQ_60G=16};
l13_enum{l827_WIFI_MODE_A=1,l828_WIFI_MODE_B=2,l826_WIFI_MODE_G=4,
l824_WIFI_MODE_N=8,l768_WIFI_MODE_AC=16,l769_WIFI_MODE_AD=32};
l13_enum{l886_WIFI_ENCRYPT_WEP=1,l774_WIFI_ENCRYPT_WPA=2,
l808_WIFI_ENCRYPT_WPA2=4};le_struct l296_wifi_ssid_cfg{lj_char
l620_ssid[32+1];la_int l320_encrypt;};le_struct l294_wifi_client{
ll_uint8_t l325_bssid[6];};le_struct l303_wifi_ap{ll_uint8_t
l325_bssid[6];la_int l571_mode;la_int l320_encrypt;la_int l533_ch;
la_int l57_rssi;};la_int l635_wifi_ap_get_country_code(lj_char
l882_code[2]);la_int l647_wifi_ap_get_supp_freqs(la_int*l435_p_freqs);
la_int l724_wifi_ap_get_supp_modes(la_int*l409_p_modes);la_int
l727_wifi_ap_get_supp_encrypts(la_int*l832_p_encrypts);la_int
l698_wifi_ap_get_work_freqs(la_int*l435_p_freqs);la_int
l715_wifi_ap_get_work_modes(la_int*l409_p_modes);la_int
l649_wifi_ap_get_work_chs(la_int l878_chs[8],la_int*l35_p_cnt);la_int
l695_wifi_ap_get_ssid_cfgs(le_struct l296_wifi_ssid_cfg l782_cfgs[4],
la_int*l35_p_cnt);la_int l641_wifi_ap_get_ip_addr(lj_char l74_ip_addr
[40]);la_int l710_wifi_ap_get_clients(le_struct l294_wifi_client
l354_clients[16],la_int*l35_p_cnt);la_int l751_wifi_ap_get_tx_power(
la_int*l847_p_power);la_int l534_wifi_ap_get_tx_byte(lt_uint64_t*
l455_p_byte);la_int l645_wifi_ap_get_tx_fragment_success_cnt(
lt_uint64_t*l35_p_cnt);la_int l652_wifi_ap_get_tx_frame_retry_cnt(
lt_uint64_t*l35_p_cnt);la_int l676_wifi_ap_get_tx_ack_loss_cnt(
lt_uint64_t*l35_p_cnt);la_int l543_wifi_ap_get_rx_byte(lt_uint64_t*
l455_p_byte);la_int l681_wifi_ap_get_rx_fragment_success_cnt(
lt_uint64_t*l35_p_cnt);la_int l667_wifi_ap_get_rx_frame_fcs_err_cnt(
lt_uint64_t*l35_p_cnt);la_int l696_wifi_ap_get_ngbr_infos(le_struct
l303_wifi_ap l144_ngbr_aps[16],la_int*l35_p_cnt);l13_enum{l22_PREV,
l1_CURR};le_struct l51_ip_info{la_int lv_len;ll_uint8_t l29_addr[16];
};l24_typedef le_struct{la_int l218_routine_cnt;la_int l198_idle_count
;lt_uint64_t l44_uid;lj_char l460_country_code[2];la_int
l467_supp_freqs;la_int l498_supp_modes;la_int l513_supp_encrypts;
la_int l485_work_freqs;la_int l494_work_modes;la_int l453_work_ch_cnt
;la_int l529_work_chs[8];la_int l423_ssid_cnt;le_struct
l296_wifi_ssid_cfg l442_ssid_cfgs[4];le_struct l51_ip_info
l276_wan_ip_info;la_int l456_client_cnt;le_struct l294_wifi_client
l354_clients[16];la_int l376_ngbr_ap_cnt;le_struct l303_wifi_ap
l144_ngbr_aps[16];la_int l251_tx_power;lt_uint64_t l84_tx_byte[2];
lt_uint64_t l83_rx_byte[2];la_int l165_ul_rate_cnt;la_int l237_ul_rate
[240];la_int l307_ul_rate_max;la_int l304_ul_rate_min;la_int
l302_ul_rate_mean;lr_double l308_ul_rate_std_dev_plus;lr_double
l309_ul_rate_std_dev_minus;la_int l157_dl_rate_cnt;la_int l263_dl_rate
[240];la_int l305_dl_rate_max;la_int l297_dl_rate_min;la_int
l285_dl_rate_mean;lr_double l310_dl_rate_std_dev_plus;lr_double
l301_dl_rate_std_dev_minus;lt_uint64_t l381_tx_fragment_success_cnt[2
];lt_uint64_t l392_rx_fragment_success_cnt[2];lt_uint64_t
l373_tx_frame_retry_cnt[2];lt_uint64_t l364_tx_ack_loss_cnt[2];
lt_uint64_t l379_rx_frame_fcs_err_cnt[2];}l358_wifi_ap_data_set;
l19_extern l358_wifi_ap_data_set*lx_gp_wifi_ap_data_set;l19_extern
la_int _mb000000002;l24_typedef le_struct{la_int l108_idle_threshold;
}l346_wifi_ap_cfg;l19_extern l346_wifi_ap_cfg*l365_gp_wifi_ap_cfg;
la_int l568_wifi_ap_pack_dev_info(ll_uint8_t*ln_data,lb_void*l41_arg);
la_int l569_wifi_ap_pack_perf_info(ll_uint8_t*ln_data,lb_void*l41_arg
);la_int l870_start_wifi_ap_ipc_routine(lb_void);l24_typedef la_int( *
l90_write_func)(li_const lb_void*ln_data,la_int lv_len);la_int
l814_clct_wifi_ap_dev_info(l90_write_func l52_writer);la_int
l875_clct_wifi_ap_routine_info(l90_write_func l52_writer);le_struct
l14_cmd{lm_uint32_t l9_type;lm_uint32_t l16_dc_id;l54_union{
ll_uint8_t ln_data[20];lm_uint32_t lo_value[6];};};lk_static la_int
l333_write_data_to_ipc_channel(li_const lb_void*ln_data,la_int lv_len
);l19_extern la_int _mb000000006;l19_extern le_struct l104_sockaddr_in
_mb000000005;la_int l870_start_wifi_ap_ipc_routine(lb_void){la_int
l156_enable;l699_fd_set l155_fds;le_struct l146_timeval l89_timeout;
la_int l152_select_cnt;le_struct l14_cmd l14_cmd;la_int l412_cmd_len;
l90_write_func l52_writer;l17_int64_t l101_timeout_usec;l17_int64_t
l389_select_start_usec,l396_select_duration_usec;l17_int64_t
l388_routine_start_usec,l398_routine_duration_usec;l13_enum{l274_INIT
,l627_REG_OK,l287_AUTH_OK,}l65_state;l156_enable=1;l65_state=
l274_INIT;l52_writer=&l333_write_data_to_ipc_channel;
l101_timeout_usec=0;l62_while(l156_enable){FD_ZERO(&l155_fds);FD_SET(
_mb000000006,&l155_fds);lf_if(l101_timeout_usec<=0){l86_memset(&
l89_timeout,0,lw_sizeof(l89_timeout));}l3_else{l89_timeout.
l384_tv_sec=(l4_long)(l101_timeout_usec/1000000);l89_timeout.
l366_tv_usec=(l4_long)(l101_timeout_usec%1000000);}
l389_select_start_usec=_mb000010009();l152_select_cnt=l692_select(
_mb000000006+1,&l155_fds,lu_NULL,lu_NULL,&l89_timeout);lf_if(
l152_select_cnt<0){l508_perror("\x73\x65\x6c\x65\x63\x74");lq_return-
1;}lf_if(l152_select_cnt>0){l396_select_duration_usec=_mb000010009()-
l389_select_start_usec;l101_timeout_usec-=l396_select_duration_usec;
l412_cmd_len=l748_recvfrom(_mb000000006,&l14_cmd,lw_sizeof(l14_cmd),0
,lu_NULL,lu_NULL);lf_if(l412_cmd_len<0){l508_perror("\x72\x65\x63\x76"
"\x66\x72\x6f\x6d");ly_break;}lf_if(l250_ntohl(l14_cmd.l16_dc_id)!=
l119_IPC_DC_WIFI_AP){l288_continue;}l107_switch(l250_ntohl(l14_cmd.
l9_type)){l7_case l154_IPC_MSG_DC_REGISTER_ACK:lf_if(l412_cmd_len==(
lw_sizeof(le_struct l33_data_header)+lw_sizeof(le_struct
l128_dc_register_ack))){l65_state|=l627_REG_OK;}ly_break;l7_case
l125_IPC_MSG_SERVER_LOOKUP_RESULT:{l365_gp_wifi_ap_cfg->
l108_idle_threshold=l14_cmd.lo_value[1];lf_if(!l14_cmd.lo_value[0]){
l156_enable=0;}l3_else{l65_state|=l287_AUTH_OK;
l814_clct_wifi_ap_dev_info(l52_writer);}ly_break;}l7_case
l160_IPC_MSG_DC_SHUT_DOWN:l156_enable=0;ly_break;l7_case
l162_IPC_MSG_DC_STATUS:l14_cmd.l9_type=l68_htonl(
l169_IPC_MSG_DC_STATUS_ACK);l14_cmd.l16_dc_id=l68_htonl(
l119_IPC_DC_WIFI_AP);l333_write_data_to_ipc_channel(&l14_cmd,
lw_sizeof(lm_uint32_t) *2);ly_break;}}l3_else{l107_switch(l65_state){
l7_case l274_INIT:l14_cmd.l9_type=l68_htonl(l163_IPC_MSG_DC_REGISTER);
l14_cmd.l16_dc_id=l68_htonl(l119_IPC_DC_WIFI_AP);
l333_write_data_to_ipc_channel(&l14_cmd,lw_sizeof(lm_uint32_t) *2);
l101_timeout_usec=1000000;ly_break;l238_default:lf_if((l65_state&
l287_AUTH_OK)==l287_AUTH_OK){l388_routine_start_usec=_mb000010009();
l875_clct_wifi_ap_routine_info(l52_writer);l398_routine_duration_usec
=_mb000010009()-l388_routine_start_usec;l101_timeout_usec=1000000-
l398_routine_duration_usec;}ly_break;}}}lq_return 0;}lk_static la_int
l333_write_data_to_ipc_channel(li_const lb_void*ln_data,la_int lv_len
){lq_return l657_sendto(_mb000000006,ln_data,lv_len,0,(le_struct
l103_sockaddr* )&_mb000000005,lw_sizeof(_mb000000005));}
