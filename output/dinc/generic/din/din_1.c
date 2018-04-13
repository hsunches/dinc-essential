#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<getopt.h>
#include<arpa/inet.h>
#include<dlfcn.h>
#include<fcntl.h>
#include<signal.h>
#include"mobric.h"
lb_void l584_load_cfg_str(li_const lj_char*l113_s,li_const lj_char*
l402_delim);la_int l546_load_cfg_file(li_const lj_char*l230_path);
l19_extern le_struct l375_cfg{lj_char l441_server_prefix[16];lj_char
l314_server_suffix[16];lj_char l399_server_domain_name[64];lj_char
l328_server_ip_addr[40];la_int l438_server_port;la_int
l447_server_port_range;la_int l315_max_dns_query;la_int
l391_max_handshake;la_int l329_max_latency;la_int
l437_remote_msg_timeout;la_int l338_op_mode;la_int l108_idle_threshold
;la_int l449_dev_info_report_interval;}l20_g_cfg;la_int
l1116_start_din()l189___attribute((l202_used));lb_void
l873_start_msg_hdlr(lb_void);la_int l243_send_event(lm_uint32_t
l9_type,li_const lb_void*ln_data,la_int lv_len);la_int l448_send_data
(la_int l0_fd,li_const lb_void*ln_data,la_int l135_data_len,li_const
le_struct l103_sockaddr*l67_p_addr,l265_socklen_t l96_addr_len);
l13_enum{l53_ERR_LV_DBG,l535_ERR_LV_INFO,l234_ERR_LV_WARN,
l69_ERR_LV_ERR};l13_enum{l37_ERR_CAT_GENERAL,l347_ERR_CAT_DAEMON,
l575_ERR_CAT_DPM_CFG,l87_ERR_CAT_MSG,l495_ERR_CAT_NET};
#include"unmobric.h"
#include"log.h"
#include<stdint.h>
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
lb_void _mb000010000(lb_void);lk_static la_int l988_fork_daemon(
lb_void);lm_uint32_t l469_conv_dc_name_to_id(li_const lj_char*
l194_name);la_int l779_conv_dc_id_to_name(la_int l110_id,lj_char*
l194_name);la_int l1013_din_main(la_int l31_argc,lj_char*l18_argv[]);
la_int l711_send_data_wait_response(lm_uint32_t l9_type,lj_char*
l111_ipstr,li_const lb_void*ln_data,la_int lv_len,ll_uint8_t*
l1037_p_get);la_int l1116_start_din(){l1172_signal(l1125_SIGCHLD,
l1143_SIG_IGN);lj_char l547_pid_file[128];l219_sprintf(l547_pid_file,""
"\x2f\x70\x72\x6f\x63\x2f\x25\x64\x2f\x63\x6d\x64\x6c\x69\x6e\x65",
l1076_getpid());la_int l0_fd=l1061_open(l547_pid_file,l1171_O_RDONLY);
lf_if(l0_fd==-1){l64_LOGG_ERR("\x6f\x70\x65\x6e\x20\x63\x6d\x64\x6c"
"\x69\x6e\x65\x20\x66\x69\x6c\x65\x20\x66\x61\x69\x6c\x65\x64");
lq_return-1;}lj_char l122_buffer[128];la_int l726_read_in=l1080_read(
l0_fd,&l122_buffer,128);l356_close(l0_fd);lf_if(l726_read_in<=0){
l64_LOGG_ERR("\x72\x65\x61\x64\x20\x63\x6d\x64\x6c\x69\x6e\x65\x20"
"\x66\x69\x6c\x65\x20\x66\x61\x69\x6c\x65\x64");lq_return-2;}lj_char*
l18_argv[16];la_int l31_argc=0;la_int ld_i=0;l62_while(ld_i<
l726_read_in&&l31_argc<(lw_sizeof(l18_argv)/lw_sizeof(lj_char* ))){
l18_argv[l31_argc++]=&l122_buffer[ld_i];ld_i+=(l377_strlen(&
l122_buffer[ld_i])+1);}lq_return l1013_din_main(l31_argc,l18_argv);}
la_int l711_send_data_wait_response(lm_uint32_t l9_type,lj_char*
l111_ipstr,li_const lb_void*ln_data,la_int lv_len,ll_uint8_t*
l1037_p_get){la_int l8_ret=((0<<31)|(l53_ERR_LV_DBG<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x00);la_int l0_fd;l699_fd_set l840_readfds;
le_struct l104_sockaddr_in l29_addr;le_struct l146_timeval l89_timeout
;l89_timeout.l384_tv_sec=5;l89_timeout.l366_tv_usec=0;la_int
l152_select_cnt;l265_socklen_t l96_addr_len=lw_sizeof(le_struct
l104_sockaddr_in);le_struct l127_din_local_msg l39_msg;
l246_LOGG_FUNC_IN();l118_do{lf_if(lv_len>128){l64_LOGG_ERR("\x43\x6f"
"\x6e\x74\x65\x6e\x74\x20\x74\x6f\x6f\x20\x6c\x61\x72\x67\x65");
l8_ret=((1<<31)|(l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14)|0x11);
ly_break;}l0_fd=l450_socket(l145_AF_INET,l400_SOCK_DGRAM,
l749_IPPROTO_UDP);lf_if(l0_fd<0){l142_LOGG_ERRNO("\x73\x6f\x63\x6b"
"\x65\x74");l8_ret=((1<<31)|(l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14
)|0x00);ly_break;}l86_memset(&l29_addr,0,lw_sizeof(l29_addr));
l29_addr.l589_sin_family=l145_AF_INET;l29_addr.l371_sin_addr.
l594_s_addr=(l111_ipstr==lu_NULL)?l68_htonl(l937_INADDR_LOOPBACK):
l1056_inet_addr(l111_ipstr);l29_addr.l548_sin_port=l503_htons(56000);
l39_msg.l30_header.l9_type=l68_htonl(l9_type);lf_if(ln_data){
l109_memcpy(l39_msg.l46_event.l42_content,ln_data,lv_len);}l8_ret=
l448_send_data(l0_fd,&l39_msg,lw_sizeof(l39_msg.l30_header)+lv_len,(
le_struct l103_sockaddr* )&l29_addr,lw_sizeof(l29_addr));lf_if(l8_ret
!=((0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){
l64_LOGG_ERR("\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20"
"\x64\x61\x74\x61\x20\x74\x6f\x20\x49\x50\x3a\x20\x25\x73",l111_ipstr
);ly_break;}FD_ZERO(&l840_readfds);FD_SET(l0_fd,&l840_readfds);la_int
l1087_maxfd=l0_fd;l62_while(1){l152_select_cnt=l692_select(
l1087_maxfd+1,&l840_readfds,lu_NULL,lu_NULL,&l89_timeout);lf_if(
l152_select_cnt<0){l508_perror("\x73\x65\x6c\x65\x63\x74");ly_break;}
ll_uint8_t l734_rbuf[128];l86_memset(l734_rbuf,0,lw_sizeof(l734_rbuf));
lf_if(l152_select_cnt>0){la_int l995_recv_len=l748_recvfrom(l0_fd,
l734_rbuf,128,0,(le_struct l103_sockaddr* )&l29_addr,&l96_addr_len);
lf_if(l995_recv_len==-1){l142_LOGG_ERRNO("\x72\x65\x63\x76\x66\x72"
"\x6f\x6d");ly_break;}l109_memcpy(l1037_p_get,l734_rbuf,l995_recv_len
);ly_break;}l3_else{ly_break;}}l356_close(l0_fd);}l62_while(0);
l240_LOGG_FUNC_OUT();lq_return l8_ret;}la_int l1013_din_main(la_int
l31_argc,lj_char*l18_argv[]){l13_enum{l863_OPT_NORMAL=1,
l830_OPT_DAEMON,l921_OPT_NET_SEARCH,l864_OPT_NET_UP,l955_OPT_NET_DOWN
,l964_OPT_DOMAIN_NAME,l1006_OPT_CFG_PATH,l797_OPT_EVENT,
l1034_OPT_RECEIVER,l1016_OPT_VERSION,l801_OPT_START_DC,
l789_OPT_STOP_DC,l936_OPT_REQUEST_UID,l844_OPT_SPECIFY_UID,
l999_OPT_REQUEST_DOMAIN,l1015_OPT_LATENCY_FAIL_CNT,
l1027_OPT_REPORT_WHO};le_struct l500_option l1063_opt_tbl[]={{"\x6e"
"\x6f\x72\x6d\x61\x6c",0,lu_NULL,l863_OPT_NORMAL},{"\x64\x61\x65\x6d"
"\x6f\x6e",0,lu_NULL,l830_OPT_DAEMON},{"\x6e\x65\x74\x5f\x73\x65\x61"
"\x72\x63\x68",1,lu_NULL,l921_OPT_NET_SEARCH},{"\x6e\x65\x74\x5f\x75"
"\x70",0,lu_NULL,l864_OPT_NET_UP},{"\x6e\x65\x74\x5f\x64\x6f\x77\x6e"
,0,lu_NULL,l955_OPT_NET_DOWN},{"\x64\x6f\x6d\x61\x69\x6e\x5f\x6e\x61"
"\x6d\x65",1,lu_NULL,l964_OPT_DOMAIN_NAME},{"\x63\x66\x67\x5f\x70\x61"
"\x74\x68",1,lu_NULL,l1006_OPT_CFG_PATH},{"\x65\x76\x65\x6e\x74",1,
lu_NULL,l797_OPT_EVENT},{"\x72\x65\x63\x65\x69\x76\x65\x72",1,lu_NULL
,l1034_OPT_RECEIVER},{"\x76\x65\x72\x73\x69\x6f\x6e",0,lu_NULL,
l1016_OPT_VERSION},{"\x73\x74\x61\x72\x74\x5f\x64\x63",1,lu_NULL,
l801_OPT_START_DC},{"\x73\x74\x6f\x70\x5f\x64\x63",1,lu_NULL,
l789_OPT_STOP_DC},{"\x72\x65\x71\x75\x65\x73\x74\x5f\x64\x65\x76\x5f"
"\x75\x69\x64",1,lu_NULL,l936_OPT_REQUEST_UID},{"\x73\x70\x65\x63\x69"
"\x66\x79\x5f\x64\x65\x76\x5f\x75\x69\x64",1,lu_NULL,
l844_OPT_SPECIFY_UID},{"\x72\x65\x71\x75\x65\x73\x74\x5f\x66\x75\x6c"
"\x6c\x5f\x64\x6f\x6d\x61\x69\x6e",1,lu_NULL,l999_OPT_REQUEST_DOMAIN}
,{"\x6c\x61\x74\x65\x6e\x63\x79\x5f\x66\x61\x69\x6c\x5f\x63\x6e\x74",
1,lu_NULL,l1015_OPT_LATENCY_FAIL_CNT},{"\x77\x68\x6f",0,lu_NULL,
l1027_OPT_REPORT_WHO},{lu_NULL,0,lu_NULL,0}};la_int l94_opt;
l1098_optind=1;la_int l1099_opt_index=0;la_int l349_extra_opt;lj_char
l72_buf[256];lj_char*l810_cfg_path;le_struct l93_din_private_event
l46_event;la_int l8_ret;l1126_OPEN_LOGG("\x44\x49\x4e");
l246_LOGG_FUNC_IN();l8_ret=0;l349_extra_opt=-1;l810_cfg_path=lu_NULL;
l86_memset(&l46_event,0,lw_sizeof(l46_event));l86_memset(&
l123_g_dev_info_report,0,lw_sizeof(l123_g_dev_info_report));l62_while
(1){l94_opt=l1133_getopt_long_only(l31_argc,l18_argv,"",l1063_opt_tbl
,&l1099_opt_index);lf_if(l94_opt==-1){ly_break;}l107_switch(l94_opt){
l7_case l863_OPT_NORMAL:l27_LOGG_INFO("\x53\x70\x65\x63\x69\x66\x79"
"\x20\x6e\x6f\x72\x6d\x61\x6c\x20\x6d\x6f\x64\x65");l349_extra_opt=
l94_opt;ly_break;l7_case l830_OPT_DAEMON:l27_LOGG_INFO("\x53\x70\x65"
"\x63\x69\x66\x79\x20\x64\x61\x65\x6d\x6f\x6e\x20\x6d\x6f\x64\x65");
lf_if(l988_fork_daemon()!=((0<<31)|(l53_ERR_LV_DBG<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x00)){l64_LOGG_ERR("\x46\x61\x69\x6c\x20"
"\x74\x6f\x20\x66\x6f\x72\x6b\x20\x61\x73\x20\x61\x20\x66\x6f\x72\x6b"
"\x5f\x64\x61\x65\x6d\x6f\x6e");lq_return-1;}l27_LOGG_INFO("\x46\x6f"
"\x72\x6b\x20\x61\x73\x20\x61\x20\x64\x61\x65\x6d\x6f\x6e\x20\x73\x75"
"\x63\x63\x65\x73\x73\x66\x75\x6c\x6c\x79");l349_extra_opt=l94_opt;
ly_break;l7_case l921_OPT_NET_SEARCH:l27_LOGG_INFO("\x53\x70\x65\x63"
"\x69\x66\x79\x20\x6e\x65\x74\x2d\x73\x65\x61\x72\x63\x68\x20\x65\x76"
"\x65\x6e\x74\x3a\x20\x25\x73",l88_optarg);l46_event.lo_value[0]=
l469_conv_dc_name_to_id(l88_optarg);lf_if(l46_event.lo_value[0]==
l161_IPC_DC_MAX){l64_LOGG_ERR("\x54\x68\x65\x20\x6e\x65\x74\x77\x6f"
"\x72\x6b\x20\x74\x79\x70\x65\x20\x69\x73\x20\x6e\x6f\x74\x20\x63\x6f"
"\x72\x72\x65\x63\x74\x3a\x20\x25\x73",l88_optarg);l8_ret=-2;ly_break
;}l46_event.lo_value[0]=l68_htonl(l46_event.lo_value[0]);lf_if(
l243_send_event(l186_IPC_MSG_NETWORK_SEARCH,&l46_event,lw_sizeof(
l46_event.lo_value[0]))!=((0<<31)|(l53_ERR_LV_DBG<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x00)){l64_LOGG_ERR("\x46\x61\x69\x6c\x20"
"\x74\x6f\x20\x73\x65\x6e\x64\x20\x61\x20\x6e\x65\x74\x2d\x73\x65\x61"
"\x72\x63\x68\x20\x65\x76\x65\x6e\x74");l8_ret=-3;ly_break;}
l27_LOGG_INFO("\x53\x65\x6e\x64\x20\x61\x20\x6e\x65\x74\x2d\x73\x65"
"\x61\x72\x63\x68\x20\x65\x76\x65\x6e\x74\x20\x73\x75\x63\x63\x65\x73"
"\x73\x66\x75\x6c\x6c\x79");ly_break;l7_case l864_OPT_NET_UP:
l27_LOGG_INFO("\x53\x70\x65\x63\x69\x66\x79\x20\x6e\x65\x74\x77\x6f"
"\x72\x6b\x2d\x75\x70\x20\x65\x76\x65\x6e\x74");l349_extra_opt=
l94_opt;ly_break;l7_case l936_OPT_REQUEST_UID:l27_LOGG_INFO("\x53\x70"
"\x65\x63\x69\x66\x79\x20\x72\x65\x71\x75\x65\x73\x74\x2d\x64\x65\x76"
"\x2d\x75\x69\x64\x20\x65\x76\x65\x6e\x74\x20\x74\x6f\x20\x49\x50\x20"
"\x25\x73",l88_optarg);ll_uint8_t l332_uid8[8];l86_memset(l332_uid8,0
,lw_sizeof(l332_uid8));lf_if(l711_send_data_wait_response(
l199_IPC_MSG_REPORT_UID,l88_optarg,lu_NULL,0,l332_uid8)!=((0<<31)|(
l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){l64_LOGG_ERR(""
"\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20\x61\x20\x72\x65"
"\x71\x75\x65\x73\x74\x5f\x64\x65\x76\x5f\x75\x69\x64\x20\x65\x76\x65"
"\x6e\x74\x20\x74\x6f\x20\x49\x50\x20\x25\x73",l88_optarg);l8_ret=-10
;}la_int ld_i=0;l21_for(ld_i=0;ld_i<lw_sizeof(l332_uid8);ld_i++){
l430_printf("\x25\x30\x32\x78",l332_uid8[ld_i]);}ly_break;l7_case
l999_OPT_REQUEST_DOMAIN:l27_LOGG_INFO("\x53\x70\x65\x63\x69\x66\x79"
"\x20\x72\x65\x71\x75\x65\x73\x74\x2d\x64\x6f\x6d\x61\x69\x6e\x2d\x6e"
"\x61\x6d\x65\x20\x65\x76\x65\x6e\x74\x20\x74\x6f\x20\x49\x50\x20\x25"
"\x73",l88_optarg);lj_char l76_domain_name[64];l86_memset(
l76_domain_name,0,lw_sizeof(l76_domain_name));lf_if(
l711_send_data_wait_response(l206_IPC_MSG_REPORT_FULL_DOMAIN,
l88_optarg,lu_NULL,0,(ll_uint8_t* )l76_domain_name)!=((0<<31)|(
l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){l64_LOGG_ERR(""
"\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20\x61\x20\x72\x65"
"\x70\x6f\x72\x74\x5f\x66\x75\x6c\x6c\x5f\x64\x6f\x6d\x61\x69\x6e\x20"
"\x65\x76\x65\x6e\x74\x20\x74\x6f\x20\x49\x50\x20\x25\x73",l88_optarg
);l8_ret=-11;}l430_printf("\x25\x73\n",l76_domain_name);ly_break;
l7_case l1015_OPT_LATENCY_FAIL_CNT:l27_LOGG_INFO("\x53\x70\x65\x63"
"\x69\x66\x79\x20\x73\x65\x72\x76\x65\x72\x2d\x6c\x61\x74\x65\x6e\x63"
"\x79\x2d\x66\x61\x69\x6c\x2d\x63\x6e\x74\x20\x65\x76\x65\x6e\x74\x20"
"\x74\x6f\x20\x49\x50\x20\x25\x73",l88_optarg);l54_union
l1090_t_convert{lm_uint32_t l1052_fail_cnt32;ll_uint8_t l850_fail_cnt8
[4];}l331_convert;l86_memset(l331_convert.l850_fail_cnt8,0,lw_sizeof(
l331_convert.l850_fail_cnt8));lf_if(l711_send_data_wait_response(
l204_IPC_MSG_REPORT_LATENCY_FAIL_CNT,l88_optarg,lu_NULL,0,
l331_convert.l850_fail_cnt8)!=((0<<31)|(l53_ERR_LV_DBG<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x00)){l64_LOGG_ERR("\x46\x61\x69\x6c\x20"
"\x74\x6f\x20\x73\x65\x6e\x64\x20\x61\x20\x72\x65\x70\x6f\x72\x74\x2d"
"\x73\x65\x72\x76\x65\x72\x2d\x6c\x61\x74\x65\x6e\x63\x79\x2d\x66\x61"
"\x69\x6c\x2d\x63\x6e\x74\x20\x65\x76\x65\x6e\x74\x20\x74\x6f\x20\x49"
"\x50\x20\x25\x73",l88_optarg);l8_ret=-13;}l430_printf("\x25\x75\n",
l331_convert.l1052_fail_cnt32);ly_break;l7_case l955_OPT_NET_DOWN:
l27_LOGG_INFO("\x53\x70\x65\x63\x69\x66\x79\x20\x6e\x65\x74\x77\x6f"
"\x72\x6b\x2d\x64\x6f\x77\x6e\x20\x65\x76\x65\x6e\x74");lf_if(
l243_send_event(l195_IPC_MSG_NETWORK_DOWN,lu_NULL,0)!=((0<<31)|(
l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){l64_LOGG_ERR(""
"\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20\x61\x20\x6e\x65"
"\x74\x77\x6f\x72\x6b\x2d\x64\x6f\x77\x6e\x20\x65\x76\x65\x6e\x74");
l8_ret=-4;ly_break;}l27_LOGG_INFO("\x53\x65\x6e\x64\x20\x61\x20\x6e"
"\x65\x74\x77\x6f\x72\x6b\x2d\x64\x6f\x77\x6e\x20\x65\x76\x65\x6e\x74"
"\x20\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x6c\x79");ly_break;
l7_case l964_OPT_DOMAIN_NAME:l27_LOGG_INFO("\x53\x70\x65\x63\x69\x66"
"\x79\x20\x64\x6f\x6d\x61\x69\x6e\x20\x6e\x61\x6d\x65\x3a\x20\x25\x73"
,l88_optarg);lf_if(l377_strlen(l88_optarg)<128){l361_strcpy((lj_char*
)l46_event.l42_content,l88_optarg);}l3_else{l492_LOGG_WARN("\x44\x6f"
"\x6d\x61\x69\x6e\x20\x6e\x61\x6d\x65\x20\x6c\x65\x67\x6e\x74\x68\x20"
"\x69\x73\x20\x74\x6f\x6f\x20\x6c\x6f\x6e\x67");l46_event.l42_content
[0]=0;}ly_break;l7_case l844_OPT_SPECIFY_UID:l27_LOGG_INFO("\x53\x70"
"\x65\x63\x69\x66\x79\x20\x64\x65\x76\x69\x63\x65\x20\x55\x49\x44\x3a"
"\x20\x25\x73",l88_optarg);l361_strcpy((lj_char* )l46_event.
l42_content,l88_optarg);l349_extra_opt=l94_opt;ly_break;l7_case
l1006_OPT_CFG_PATH:l27_LOGG_INFO("\x53\x70\x65\x63\x69\x66\x79\x20"
"\x63\x6f\x6e\x66\x69\x67\x75\x72\x61\x74\x69\x6f\x6e\x20\x66\x69\x6c"
"\x65\x20\x70\x61\x74\x68\x3a\x20\x25\x73",l88_optarg);lf_if(
l377_strlen(l88_optarg)<lw_sizeof(l72_buf)){l361_strcpy(l72_buf,
l88_optarg);l810_cfg_path=l72_buf;}l3_else{l492_LOGG_WARN("\x54\x68"
"\x65\x20\x6c\x65\x6e\x67\x74\x68\x20\x6f\x66\x20\x63\x6f\x6e\x66\x69"
"\x67\x75\x72\x61\x74\x69\x6f\x6e\x20\x66\x69\x6c\x65\x20\x70\x61\x74"
"\x68\x20\x69\x73\x20\x74\x6f\x6f\x20\x6c\x6f\x6e\x67");}ly_break;
l7_case l797_OPT_EVENT:l27_LOGG_INFO("\x53\x70\x65\x63\x69\x66\x79"
"\x20\x63\x75\x73\x74\x6f\x6d\x20\x65\x76\x65\x6e\x74\x3a\x20\x25\x73"
,l88_optarg);l658_strncpy((lj_char* )&l46_event.lo_value[1],
l88_optarg,4);l349_extra_opt=l94_opt;ly_break;l7_case
l1034_OPT_RECEIVER:l27_LOGG_INFO("\x53\x70\x65\x63\x69\x66\x79\x20"
"\x63\x75\x73\x74\x6f\x6d\x2d\x65\x76\x65\x6e\x74\x20\x72\x65\x63\x65"
"\x69\x76\x65\x72\x3a\x20\x25\x73",l88_optarg);l46_event.lo_value[0]=
l469_conv_dc_name_to_id(l88_optarg);ly_break;l7_case l1016_OPT_VERSION
:_mb000010000();lq_return 0;l7_case l801_OPT_START_DC:l27_LOGG_INFO(""
"\x53\x74\x61\x72\x74\x20\x64\x61\x74\x61\x20\x63\x6f\x6c\x6c\x65\x63"
"\x74\x6f\x72\x3a\x20\x25\x73",l88_optarg);l361_strcpy((lj_char* )l46_event
.l42_content,l88_optarg);l349_extra_opt=l94_opt;ly_break;l7_case
l789_OPT_STOP_DC:l27_LOGG_INFO("\x53\x74\x6f\x70\x20\x64\x61\x74\x61"
"\x20\x63\x6f\x6c\x6c\x65\x63\x74\x6f\x72\x3a\x20\x25\x73",l88_optarg
);l361_strcpy((lj_char* )l46_event.l42_content,l88_optarg);
l349_extra_opt=l94_opt;ly_break;l7_case l1027_OPT_REPORT_WHO:
l27_LOGG_INFO("\x57\x68\x6f\x20\x69\x73\x20\x6f\x6e\x20\x64\x75\x74"
"\x79\x3f");lf_if(l243_send_event(l200_IPC_MSG_DC_WHO,lu_NULL,0)!=((0
<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){
l64_LOGG_ERR("\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20"
"\x61\x20\x64\x63\x2d\x77\x68\x6f\x20\x65\x76\x65\x6e\x74");l8_ret=-4
;ly_break;}l27_LOGG_INFO("\x53\x65\x6e\x64\x20\x61\x20\x64\x63\x2d"
"\x77\x68\x6f\x20\x65\x76\x65\x6e\x74\x20\x73\x75\x63\x63\x65\x73\x73"
"\x66\x75\x6c\x6c\x79");ly_break;}}l107_switch(l349_extra_opt){
l7_case l863_OPT_NORMAL:l7_case l830_OPT_DAEMON:lf_if(
l546_load_cfg_file(l810_cfg_path)!=((0<<31)|(l53_ERR_LV_DBG<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x00)){l492_LOGG_WARN("\x46\x61\x69\x6c\x20"
"\x74\x6f\x20\x6c\x6f\x61\x64\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x61"
"\x74\x69\x6f\x6e\x20\x66\x69\x6c\x65");}l873_start_msg_hdlr();
ly_break;l7_case l864_OPT_NET_UP:lf_if(l243_send_event(
l192_IPC_MSG_NETWORK_UP,&l46_event,lw_sizeof(l46_event.l42_content))!=
((0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){
l64_LOGG_ERR("\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20"
"\x61\x20\x6e\x65\x74\x77\x6f\x72\x6b\x2d\x75\x70\x20\x65\x76\x65\x6e"
"\x74");l8_ret=-5;ly_break;}l27_LOGG_INFO("\x53\x65\x6e\x64\x20\x61"
"\x20\x6e\x65\x74\x77\x6f\x72\x6b\x2d\x75\x70\x20\x65\x76\x65\x6e\x74"
"\x20\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x6c\x79");ly_break;
l7_case l801_OPT_START_DC:lf_if(l243_send_event(l187_IPC_MSG_DC_START
,&l46_event,lw_sizeof(l46_event.l42_content))!=((0<<31)|(
l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){l64_LOGG_ERR(""
"\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20\x61\x20\x73\x74"
"\x61\x72\x74\x20\x64\x63\x20\x65\x76\x65\x6e\x74");l8_ret=-6;}
ly_break;l7_case l789_OPT_STOP_DC:lf_if(l243_send_event(
l208_IPC_MSG_DC_STOP,&l46_event,lw_sizeof(l46_event.l42_content))!=((
0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){
l64_LOGG_ERR("\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20"
"\x61\x20\x73\x74\x6f\x70\x20\x64\x63\x20\x65\x76\x65\x6e\x74");
l8_ret=-7;}ly_break;l7_case l797_OPT_EVENT:lf_if(l46_event.lo_value[0
]==l161_IPC_DC_MAX){l64_LOGG_ERR("\x54\x68\x65\x20\x6e\x65\x74\x77"
"\x6f\x72\x6b\x20\x74\x79\x70\x65\x20\x69\x73\x20\x6e\x6f\x74\x20\x63"
"\x6f\x72\x72\x65\x63\x74\x3a\x20\x25\x73",l88_optarg);l8_ret=-8;
ly_break;}l46_event.lo_value[0]=l68_htonl(l46_event.lo_value[0]);
lf_if(l243_send_event(l153_IPC_MSG_CUSTOM_EVENT,&l46_event,lw_sizeof(
l46_event.lo_value))!=((0<<31)|(l53_ERR_LV_DBG<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x00)){l64_LOGG_ERR("\x46\x61\x69\x6c\x20"
"\x74\x6f\x20\x73\x65\x6e\x64\x20\x61\x20\x63\x75\x73\x74\x6f\x6d\x20"
"\x65\x76\x65\x6e\x74");l8_ret=-9;ly_break;}l27_LOGG_INFO("\x53\x65"
"\x6e\x64\x20\x61\x20\x63\x75\x73\x74\x6f\x6d\x20\x65\x76\x65\x6e\x74"
"\x20\x73\x75\x63\x63\x65\x73\x73\x66\x75\x6c\x6c\x79");ly_break;
l7_case l844_OPT_SPECIFY_UID:lf_if(l243_send_event(
l203_IPC_MSG_SPECIFY_UID,&l46_event,lw_sizeof(l46_event.l42_content))!=
((0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){
l64_LOGG_ERR("\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20"
"\x61\x20\x73\x65\x74\x20\x75\x69\x64\x20\x65\x76\x65\x6e\x74");
l8_ret=-12;}ly_break;}l240_LOGG_FUNC_OUT();lq_return l8_ret;}
lm_uint32_t l1072_get_dc_id(li_const lj_char*l194_name){lm_uint32_t
l110_id=l161_IPC_DC_MAX;lb_void*l28_handle=l867_dlopen(lu_NULL,
l788_RTLD_NOW);lf_if(!l28_handle){l64_LOGG_ERR("\x25\x73",
l260_dlerror());lq_return l110_id;}lj_char l311_func[32];l219_sprintf
(l311_func,"\x64\x63\x5f\x25\x73\x5f\x69\x64",l194_name);l260_dlerror
();lm_uint32_t( *l16_dc_id)(lb_void)=l679_dlsym(l28_handle,l311_func);
lj_char*l266_error=l260_dlerror();lf_if(l266_error!=lu_NULL){
l64_LOGG_ERR("\x25\x73",l266_error);l221_dlclose(l28_handle);
lq_return l110_id;}l110_id=l16_dc_id();l221_dlclose(l28_handle);
lq_return l110_id;}le_struct{lj_char*l194_name;lm_uint32_t l110_id;}
lk_static li_const l390_conv_tbl[]={{"\x64\x65\x76",l116_IPC_DC_DEV},
{"\x77\x69\x66\x69\x5f\x73\x74\x61",l232_IPC_DC_WIFI_STA},{"\x77\x69"
"\x66\x69\x5f\x61\x70",l119_IPC_DC_WIFI_AP},{"\x77\x6d\x78",
l220_IPC_DC_WIMAX},{"\x32\x67",l222_IPC_DC_2G},{"\x33\x67",
l224_IPC_DC_3G},{"\x6c\x74\x65",l73_IPC_DC_LTE},{"\x76\x6f\x69\x70",
l225_IPC_DC_VOIP},{"\x65\x74\x68\x65\x72\x6e\x65\x74",
l217_IPC_DC_ETHERNET}};lm_uint32_t l469_conv_dc_name_to_id(li_const
lj_char*l194_name){la_int ld_i;l21_for(ld_i=0;ld_i<(lw_sizeof(
l390_conv_tbl)/lw_sizeof(l390_conv_tbl[0]));ld_i++){lf_if(!
l273_strcmp(l194_name,l390_conv_tbl[ld_i].l194_name)){lq_return
l390_conv_tbl[ld_i].l110_id;}}li_const lm_uint32_t l110_id=
l1072_get_dc_id(l194_name);lf_if(l110_id==l116_IPC_DC_DEV){lq_return
l161_IPC_DC_MAX;}lq_return l110_id;}la_int l779_conv_dc_id_to_name(
la_int l110_id,lj_char*l194_name){la_int ld_i;l219_sprintf(l194_name,""
"\x64\x65\x76");l21_for(ld_i=0;ld_i<(lw_sizeof(l390_conv_tbl)/
lw_sizeof(l390_conv_tbl[0]));ld_i++){lf_if((l110_id|0x80BB0000)==
l390_conv_tbl[ld_i].l110_id){l361_strcpy(l194_name,l390_conv_tbl[ld_i
].l194_name);lq_return 0;}}lq_return 1;}lk_static la_int
l988_fork_daemon(lb_void){la_int l8_ret;l246_LOGG_FUNC_IN();l8_ret=((
0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00);lf_if(
l1124_daemon(0,0)<0){l142_LOGG_ERRNO("\x64\x61\x65\x6d\x6f\x6e");
l8_ret=((1<<31)|(l69_ERR_LV_ERR<<28)|(l347_ERR_CAT_DAEMON<<14)|0x03);
}l240_LOGG_FUNC_OUT();lq_return l8_ret;}
