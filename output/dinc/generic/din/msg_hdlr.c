#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<errno.h>
#include<time.h>
#include<unistd.h>
#include<dlfcn.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/resource.h>
#include<limits.h>
#include"mobric.h"
lb_void l873_start_msg_hdlr(lb_void);la_int l243_send_event(
lm_uint32_t l9_type,li_const lb_void*ln_data,la_int lv_len);la_int
l448_send_data(la_int l0_fd,li_const lb_void*ln_data,la_int
l135_data_len,li_const le_struct l103_sockaddr*l67_p_addr,
l265_socklen_t l96_addr_len);le_struct l355_remote_msg{lm_uint32_t
l319_timestamp;lm_uint32_t l14_cmd;lm_uint32_t lo_value;lm_uint32_t
l482_chksum;};l19_extern le_struct l1020_dev_info{la_int lv_len;
ll_uint8_t ln_data[256];}l233_g_dev_info;l19_extern le_struct
l1014_conn_history_info{la_int l668_is_sent;la_int l470_list_size;
le_struct l871_conn_history{la_int lv_len;lm_uint32_t l317_time;
ll_uint8_t ln_data[16];}lz_list[5];}l159_g_conn_history_info;
l19_extern le_struct l914_latency_test_info{la_int l507_is_testing;
la_int l651_test_cnt;l17_int64_t l463_start_time_usec;l17_int64_t
l509_end_time_usec;lm_uint32_t l360_requester;lm_uint32_t
l275_fail_cnt;}l106_g_latency_test_info;la_int l841_parse_remote_msg(
le_struct l355_remote_msg* *l838_pp_msg,lb_void*ln_data,la_int lv_len
,l32_int32_t l477_now);la_int l792_pack_remote_msg(lb_void*l39_msg,
li_const lb_void*ln_data,la_int lv_len);la_int
l862_pack_conn_history_info(ll_uint8_t*ln_data);la_int
l891_pack_latency_test_info(ll_uint8_t*ln_data);l13_enum{
l53_ERR_LV_DBG,l535_ERR_LV_INFO,l234_ERR_LV_WARN,l69_ERR_LV_ERR};
l13_enum{l37_ERR_CAT_GENERAL,l347_ERR_CAT_DAEMON,l575_ERR_CAT_DPM_CFG
,l87_ERR_CAT_MSG,l495_ERR_CAT_NET};lb_void l584_load_cfg_str(li_const
lj_char*l113_s,li_const lj_char*l402_delim);la_int l546_load_cfg_file
(li_const lj_char*l230_path);l19_extern le_struct l375_cfg{lj_char
l441_server_prefix[16];lj_char l314_server_suffix[16];lj_char
l399_server_domain_name[64];lj_char l328_server_ip_addr[40];la_int
l438_server_port;la_int l447_server_port_range;la_int
l315_max_dns_query;la_int l391_max_handshake;la_int l329_max_latency;
la_int l437_remote_msg_timeout;la_int l338_op_mode;la_int
l108_idle_threshold;la_int l449_dev_info_report_interval;}l20_g_cfg;
la_int l560_query_server_addr(le_struct l290_sockaddr_in6
l293_addr_list[],la_int*l669_p_addr_cnt,li_const lj_char*
l76_domain_name,la_int l691_max_retry);
#include"unmobric.h"
#include<pthread.h>
#include"mobric.h"
lb_void l484_randomize(lb_void);la_int l386_get_random(lb_void);
lb_void l731_load_random_list(la_int lz_list[],la_int*l35_p_cnt,
la_int l628_base,la_int l339_range);l17_int64_t
l723_get_usec_from_timeval(li_const le_struct l146_timeval*
l283_p_timeval);lb_void l557_get_timeval_from_usec(le_struct
l146_timeval*l283_p_timeval,l17_int64_t l544_usec);l17_int64_t
l344_get_time_now_usec(lb_void);
#include"unmobric.h"
#include"log.h"
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
lb_void _mb000010000(lb_void);l13_enum{l136_LOCAL,l262_REMOTE};
l13_enum{l938_OPEN_SOCKET,l1011_CLOSE_SOCKET};l13_enum l1161_pipe_opt
{l894_OPEN,l980_GET_READ,l799_CLOSE_READ,l817_GET_WRITE,
l637_CLOSE_WRITE,l636_CLOSE_ALL};l13_enum l1129_handshake_opt{
l907_CONTINUE,l1031_TERMINATE};l13_enum l805_conn_state{
l785_DISCONNECTED,l1069_CONNECTED};l13_enum l859_search_state{
l274_INIT,l853_IN_PROGRESS,l966_WAIT,l659_SUCCESS,l506_FAIL};l13_enum
l1159_dc_info_type{l948_NET_SEARCH_START,l959_NET_SEARCH_END};
lk_static l1102_time_t l820_g_dev_info_last_update_time;lk_static
ll_uint8_t l1029_g_dev_info_last_update_time_init=0;lk_static l13_enum
l805_conn_state l975_g_conn_state;lk_static l17_int64_t
l518_g_select_timeout_usec;lk_static le_struct l595_dc_info{
l433_pid_t l148_pid;le_struct l104_sockaddr_in l29_addr;l17_int64_t
l642_net_search_start_time;lm_uint32_t l141_net_search_latency;
lm_uint32_t l126_net_up_time_list[5];}l746_g_dc_info_list[24];
lk_static le_struct{l13_enum l859_search_state l65_state;la_int l0_fd
[2];lj_char l76_domain_name[128];}l228_g_search_info;lk_static
le_struct{la_int l626_is_active;l265_socklen_t lv_len;l54_union{
le_struct l103_sockaddr l29_addr;le_struct l104_sockaddr_in
l1140_addr_v4;le_struct l290_sockaddr_in6 l1137_addr_v6;};}
l139_g_server_addr;le_struct l708_socket_fd{la_int l0_fd[2];};
l19_extern lm_uint32_t l469_conv_dc_name_to_id(li_const lj_char*
l194_name);l19_extern la_int l779_conv_dc_id_to_name(la_int l110_id,
lj_char*l194_name);lk_static la_int l998_hdl_msg(li_const la_int l0_fd
[],la_int l9_type);lk_static la_int l953_hdl_local_msg(li_const la_int
l0_fd[],le_struct l127_din_local_msg*l38_p_msg,la_int l168_msg_len,
li_const le_struct l104_sockaddr_in*l67_p_addr);lk_static la_int
l986_hdl_remote_msg(li_const la_int l0_fd[],lb_void*ln_data,la_int
l135_data_len,li_const le_struct l103_sockaddr*l67_p_addr,
l265_socklen_t l96_addr_len);lk_static lb_void l553_bcast_cmd(la_int
l0_fd,lm_uint32_t l474_cmd_type,li_const lb_void*ln_data,la_int lv_len
);lk_static la_int l367_send_cmd(la_int l0_fd,lm_uint32_t
l474_cmd_type,lm_uint32_t l16_dc_id,li_const lb_void*ln_data,la_int
lv_len);lk_static la_int l362_send_remote_msg(la_int l0_fd,li_const
lb_void*ln_data,la_int l135_data_len,li_const le_struct l103_sockaddr
 *l67_p_addr,l265_socklen_t l96_addr_len);lk_static la_int
l690_search_server(li_const la_int l0_fd[],li_const lj_char*
l76_domain_name);lk_static la_int l918_handshake(la_int l0_fd,
li_const le_struct l103_sockaddr*l67_p_addr,l265_socklen_t
l96_addr_len);lk_static la_int l868_send_conn_history_info(la_int
l0_fd);lk_static la_int l1004_start_latency_test(la_int l0_fd,
lm_uint32_t l360_requester);lk_static lb_void l721_stop_latency_test(
la_int l0_fd,la_int l483_is_success);lk_static la_int
l697_respond_request(li_const lb_void*ln_data,la_int lv_len,li_const
le_struct l104_sockaddr_in*l67_p_addr);lk_static la_int
l1038_pack_and_send_ext_cmd_ack(lj_char*l14_cmd,lm_uint32_t lo_value,
la_int l8_ret);lk_static lb_void l991_set_dev_info(li_const lb_void*
ln_data,la_int lv_len);lk_static lb_void l759_set_conn_state(l13_enum
l805_conn_state l65_state);lk_static lb_void l444_set_select_timeout(
l17_int64_t l101_timeout_usec);lk_static lb_void l352_set_search_info
(l13_enum l859_search_state l65_state,li_const la_int l0_fd[],
li_const lj_char*l76_domain_name);lk_static lb_void
l861_set_server_addr(li_const le_struct l103_sockaddr*l67_p_addr,
la_int l96_addr_len);lk_static lb_void l738_set_latency_test_info(
la_int l899_is_start,lm_uint32_t l360_requester);lk_static lb_void
l835_set_dc_info(la_int l9_type,lm_uint32_t l110_id,li_const le_struct
l104_sockaddr_in*l67_p_addr);lk_static lb_void
l976_set_conn_history_info(li_const lb_void*ln_data,la_int lv_len);
lk_static lb_void l1008_reset_dc_activity(lb_void);lk_static le_struct
l595_dc_info*l499_get_dc_info(lm_uint32_t l110_id);lk_static la_int
l597_lock_pid_file(li_const lj_char*l462_dc);lk_static la_int
l558_unlock_pid_file(li_const la_int l0_fd);lk_static la_int
l900_parse_standard_options(la_int l31_argc,lj_char*l18_argv[],
lb_void*l28_handle);lk_static l433_pid_t l963_start_dc(la_int l31_argc
,lj_char*l18_argv[]);lk_static lb_void l940_search_server_impl(
lb_void);lk_static la_int l256_search_server_pipe(li_const la_int
l500_option);lk_static le_struct l708_socket_fd*l825_din_socket_fds(
li_const la_int l500_option);lk_static lb_void l973_exit_msg_hdlr(
lb_void);lb_void l452_handle_options(la_int l31_argc,lj_char*l18_argv
[]);lb_void l942_handle_ext_cmd_child_process(lb_void*l133_lib_handle
,lj_char*l440_pid_name,lj_char l14_cmd[5],lm_uint32_t lo_value,la_int
( *l629_prog)(ll_uint8_t,lm_uint32_t));la_int l971_update_dev_info(
la_int l0_fd);lk_static la_int l558_unlock_pid_file(li_const la_int
l0_fd){lf_if(l0_fd<0){l64_LOGG_ERR("\x75\x6e\x6c\x6f\x63\x6b\x20\x70"
"\x61\x72\x61\x6d\x65\x74\x65\x72\x20\x65\x72\x72\x6f\x72");lq_return
-1;}la_int l322_res=l1070_lockf(l0_fd,l1180_F_ULOCK,0);lf_if(l322_res
<0){l64_LOGG_ERR("\x75\x6e\x6c\x6f\x63\x6b\x20\x70\x69\x64\x20\x66"
"\x69\x6c\x65\x20\x66\x61\x69\x6c\x65\x64");}l356_close(l0_fd);
lq_return l322_res;}lk_static la_int l597_lock_pid_file(li_const
lj_char*l462_dc){la_int l0_fd;lj_char l72_buf[32];lj_char
l547_pid_file[32];l219_sprintf(l547_pid_file,"\x2f\x76\x61\x72\x2f"
"\x72\x75\x6e\x2f\x64\x63\x5f\x25\x73\x2e\x70\x69\x64",l462_dc);l0_fd
=l1061_open(l547_pid_file,l1158_O_CREAT|l1146_O_RDWR,0666);lf_if(
l0_fd<0){l64_LOGG_ERR("\x6f\x70\x65\x6e\x20\x70\x69\x64\x20\x66\x69"
"\x6c\x65\x20\x66\x61\x69\x6c\x65\x64\x3a\x20\x28\x25\x64\x29\x25\x73"
,l134_errno,l1075_strerror(l134_errno));lq_return l0_fd;}lf_if(
l1070_lockf(l0_fd,l1144_F_TLOCK,0)<0){l64_LOGG_ERR("\x6c\x6f\x63\x6b"
"\x20\x70\x69\x64\x20\x66\x69\x6c\x65\x20\x66\x61\x69\x6c\x65\x64\x3a"
"\x20\x28\x25\x64\x29\x25\x73",l134_errno,l1075_strerror(l134_errno));
l356_close(l0_fd);lq_return-1;}l219_sprintf(l72_buf,"\x25\x75\n",
l1076_getpid());lf_if(l1005_write(l0_fd,l72_buf,l377_strlen(l72_buf))<
0){l64_LOGG_ERR("\x25\x73",l72_buf);l356_close(l0_fd);lq_return-1;}
lq_return l0_fd;}lb_void l452_handle_options(la_int l31_argc,lj_char*
l18_argv[]){lb_void*l28_handle=l867_dlopen(lu_NULL,l788_RTLD_NOW);
lf_if(!l28_handle){l64_LOGG_ERR("\x25\x73",l260_dlerror());lq_return;
}l900_parse_standard_options(l31_argc,l18_argv,l28_handle);
l221_dlclose(l28_handle);}lk_static la_int l900_parse_standard_options
(la_int l31_argc,lj_char*l18_argv[],lb_void*l28_handle){la_int
l322_res=-1;l62_while(1){la_int l94_opt=l1109_getopt(l31_argc,
l18_argv,"\x63\x3a\x76");lf_if(l94_opt==-1){ly_break;}l107_switch(
l94_opt){l7_case'c':{lj_char l311_func[32];l219_sprintf(l311_func,""
"\x64\x63\x5f\x25\x73\x5f\x6c\x6f\x61\x64\x5f\x63\x6f\x6e\x66\x69\x67"
,l18_argv[0]);l260_dlerror();lb_void( *l834_dc_load_config)(li_const
lj_char* )=l679_dlsym(l28_handle,l311_func);lj_char*l266_error=
l260_dlerror();lf_if(l266_error==lu_NULL){l834_dc_load_config(
l88_optarg);}l322_res=0;}ly_break;l7_case'v':{_mb000010000();lj_char
l311_func[32];l219_sprintf(l311_func,"\x64\x63\x5f\x25\x73\x5f\x76"
"\x65\x72\x73\x69\x6f\x6e",l18_argv[0]);l260_dlerror();lb_void( *
l809_dc_version)(lb_void)=l679_dlsym(l28_handle,l311_func);lj_char*
l266_error=l260_dlerror();lf_if(l266_error==lu_NULL){l809_dc_version(
);}l322_res=-1;}ly_break;l238_default:{}ly_break;}}lq_return l322_res
;}lk_static l433_pid_t l963_start_dc(la_int l31_argc,lj_char*l18_argv
[]){lf_if(l18_argv==lu_NULL){lq_return 0;}lb_void*l133_lib_handle=
l867_dlopen(lu_NULL,l788_RTLD_NOW);lf_if(!l133_lib_handle){
l64_LOGG_ERR("\x25\x73",l260_dlerror());lq_return 0;}lj_char l311_func
[32];l219_sprintf(l311_func,"\x64\x63\x5f\x25\x73\x5f\x6d\x61\x69\x6e"
,l18_argv[0]);l260_dlerror();la_int( *l1081_dc_main)(la_int,lj_char* *
)=l679_dlsym(l133_lib_handle,l311_func);lj_char*l266_error=
l260_dlerror();lf_if(l266_error!=lu_NULL){l64_LOGG_ERR("\x25\x73",
l266_error);l221_dlclose(l133_lib_handle);lq_return 0;}la_int l0_fd=
l597_lock_pid_file(l18_argv[0]);lf_if(l0_fd<0){l221_dlclose(
l133_lib_handle);lq_return 0;}l558_unlock_pid_file(l0_fd);li_const
l433_pid_t l148_pid=l775_fork();lf_if(l148_pid<0){l142_LOGG_ERRNO(""
"\x66\x6f\x72\x6b\x20\x66\x61\x69\x6c\x65\x64");l221_dlclose(
l133_lib_handle);lq_return-1;}lf_if(l148_pid==0){lf_if((l0_fd=
l597_lock_pid_file(l18_argv[0]))<0){l221_dlclose(l133_lib_handle);
l191_LOGG_DBG("\x44\x43\x20\x25\x73\x20\x68\x61\x73\x20\x61\x6c\x72"
"\x65\x61\x64\x79\x20\x73\x74\x61\x72\x74\x65\x64\x2c\x20\x63\x6c\x6f"
"\x73\x65\x20\x74\x68\x69\x73\x20\x63\x61\x6c\x6c",(lj_char* )l18_argv
[0]);l426_exit(0);}li_const la_int l341_r=l1081_dc_main(l31_argc,
l18_argv);l558_unlock_pid_file(l0_fd);l221_dlclose(l133_lib_handle);
l191_LOGG_DBG("\x43\x68\x69\x6c\x64\x20\x70\x72\x6f\x63\x65\x73\x73"
"\x20\x44\x43\x20\x25\x73\x20\x69\x73\x20\x64\x6f\x6e\x65",(lj_char* )l18_argv
[0]);l426_exit(l341_r);}l221_dlclose(l133_lib_handle);lq_return
l148_pid;}lk_static le_struct l708_socket_fd*l825_din_socket_fds(
li_const la_int l500_option){lk_static le_struct l708_socket_fd
l280_sfd;l107_switch(l500_option){l7_case l938_OPEN_SOCKET:{l280_sfd.
l0_fd[l136_LOCAL]=l450_socket(l145_AF_INET,l400_SOCK_DGRAM,
l749_IPPROTO_UDP);l280_sfd.l0_fd[l262_REMOTE]=l450_socket(
l445_AF_INET6,l400_SOCK_DGRAM,l749_IPPROTO_UDP);lf_if(l280_sfd.l0_fd[
l262_REMOTE]<0){l280_sfd.l0_fd[l262_REMOTE]=l450_socket(l145_AF_INET,
l400_SOCK_DGRAM,l749_IPPROTO_UDP);}lf_if(l280_sfd.l0_fd[l136_LOCAL]<0
||l280_sfd.l0_fd[l262_REMOTE]<0){l142_LOGG_ERRNO("\x73\x6f\x63\x6b"
"\x65\x74");lq_return lu_NULL;}}ly_break;l7_case l1011_CLOSE_SOCKET:{
la_int ld_i;l21_for(ld_i=0;ld_i<(lw_sizeof(l280_sfd.l0_fd)/lw_sizeof(
l280_sfd.l0_fd[0]));ld_i++){lf_if(l280_sfd.l0_fd[ld_i]>0){l356_close(
l280_sfd.l0_fd[ld_i]);}}lq_return lu_NULL;}ly_break;}lq_return&
l280_sfd;}lk_static lb_void l973_exit_msg_hdlr(lb_void){
l246_LOGG_FUNC_IN();l256_search_server_pipe(l636_CLOSE_ALL);
l825_din_socket_fds(l1011_CLOSE_SOCKET);l240_LOGG_FUNC_OUT();}lb_void
l873_start_msg_hdlr(lb_void){le_struct l708_socket_fd*l227_p_sfd;
la_int l915_nfds;l699_fd_set l155_fds;la_int l152_select_cnt;
le_struct l104_sockaddr_in l29_addr;le_struct l146_timeval l89_timeout
;le_struct l146_timeval*l425_p_timeout;l17_int64_t
l463_start_time_usec;l17_int64_t l509_end_time_usec;l17_int64_t
l1030_duration_usec;la_int ld_i;l1174_atexit(l973_exit_msg_hdlr);
l759_set_conn_state(l785_DISCONNECTED);l444_set_select_timeout(-1);
l352_set_search_info(l506_FAIL,lu_NULL,lu_NULL);
l738_set_latency_test_info(0,-1);l118_do{lf_if((l227_p_sfd=
l825_din_socket_fds(l938_OPEN_SOCKET))==lu_NULL){ly_break;}l86_memset
(&l29_addr,0,lw_sizeof(le_struct l104_sockaddr_in));l29_addr.
l589_sin_family=l145_AF_INET;l29_addr.l548_sin_port=l503_htons(56000);
l29_addr.l371_sin_addr.l594_s_addr=l68_htonl(l1154_INADDR_ANY);
l27_LOGG_INFO("\x42\x69\x6e\x64\x20\x70\x6f\x72\x74\x20\x25\x64",
56000);lf_if(l1165_bind(l227_p_sfd->l0_fd[l136_LOCAL],(le_struct
l103_sockaddr* )&l29_addr,lw_sizeof(l29_addr))<0){l142_LOGG_ERRNO(""
"\x62\x69\x6e\x64");ly_break;}l425_p_timeout=lu_NULL;l62_while(1){
FD_ZERO(&l155_fds);FD_SET(l227_p_sfd->l0_fd[l136_LOCAL],&l155_fds);
FD_SET(l227_p_sfd->l0_fd[l262_REMOTE],&l155_fds);l915_nfds=(
l227_p_sfd->l0_fd[l136_LOCAL]>l227_p_sfd->l0_fd[l262_REMOTE]?
l227_p_sfd->l0_fd[l136_LOCAL]:l227_p_sfd->l0_fd[l262_REMOTE])+1;
l463_start_time_usec=l344_get_time_now_usec();l152_select_cnt=
l692_select(l915_nfds,&l155_fds,lu_NULL,lu_NULL,l425_p_timeout);
l509_end_time_usec=l344_get_time_now_usec();lf_if(l152_select_cnt<0){
l142_LOGG_ERRNO("\x73\x65\x6c\x65\x63\x74");ly_break;}l21_for(ld_i=0;
ld_i<(lw_sizeof(l227_p_sfd->l0_fd)/lw_sizeof(l227_p_sfd->l0_fd[0]));
ld_i++){lf_if(FD_ISSET(l227_p_sfd->l0_fd[ld_i],&l155_fds)){
l998_hdl_msg(l227_p_sfd->l0_fd,ld_i);}}l971_update_dev_info(
l227_p_sfd->l0_fd[l262_REMOTE]);lf_if(l518_g_select_timeout_usec==-1){
l191_LOGG_DBG("\x54\x69\x6d\x65\x6f\x75\x74\x20\x73\x65\x74\x74\x69"
"\x6e\x67\x20\x66\x6f\x72\x20\x73\x65\x6c\x65\x63\x74\x69\x6e\x67\x20"
"\x73\x6f\x63\x6b\x65\x74\x3a\x20\x69\x6e\x66\x69\x6e\x69\x74\x65");
l425_p_timeout=lu_NULL;}l3_else{lf_if(l425_p_timeout==lu_NULL){
l557_get_timeval_from_usec(&l89_timeout,l518_g_select_timeout_usec);
l191_LOGG_DBG("\x54\x69\x6d\x65\x6f\x75\x74\x20\x73\x65\x74\x74\x69"
"\x6e\x67\x20\x66\x6f\x72\x20\x73\x65\x6c\x65\x63\x74\x69\x6e\x67\x20"
"\x73\x6f\x63\x6b\x65\x74\x28\x69\x6e\x69\x74\x29\x3a\x20\x25\x6c\x64"
"\x2e\x25\x30\x36\x6c\x64",l89_timeout.l384_tv_sec,l89_timeout.
l366_tv_usec);l425_p_timeout=&l89_timeout;}l3_else{
l1030_duration_usec=l509_end_time_usec-l463_start_time_usec;
l518_g_select_timeout_usec-=l1030_duration_usec;lf_if(
l518_g_select_timeout_usec>0){l557_get_timeval_from_usec(&l89_timeout
,l518_g_select_timeout_usec);l191_LOGG_DBG("\x54\x69\x6d\x65\x6f\x75"
"\x74\x20\x73\x65\x74\x74\x69\x6e\x67\x20\x66\x6f\x72\x20\x73\x65\x6c"
"\x65\x63\x74\x69\x6e\x67\x20\x73\x6f\x63\x6b\x65\x74\x28\x6e\x65\x78"
"\x74\x29\x3a\x20\x25\x6c\x64\x2e\x25\x30\x36\x6c\x64",l89_timeout.
l384_tv_sec,l89_timeout.l366_tv_usec);l425_p_timeout=&l89_timeout;}
l3_else{l191_LOGG_DBG("\x54\x69\x6d\x65\x6f\x75\x74\x20\x77\x68\x65"
"\x6e\x20\x73\x65\x6c\x65\x63\x74\x69\x6e\x67\x20\x73\x6f\x63\x6b\x65"
"\x74\x73");lf_if(l106_g_latency_test_info.l507_is_testing){
l721_stop_latency_test(l227_p_sfd->l0_fd[l136_LOCAL],0);}l3_else{
l444_set_select_timeout(-1);l690_search_server(lu_NULL,lu_NULL);}
l425_p_timeout=lu_NULL;}}}}}l62_while(0);}la_int l243_send_event(
lm_uint32_t l9_type,li_const lb_void*ln_data,la_int lv_len){la_int
l0_fd;le_struct l104_sockaddr_in l29_addr;la_int l8_ret;le_struct
l127_din_local_msg l39_msg;l246_LOGG_FUNC_IN();l118_do{lf_if(lv_len>
128){l64_LOGG_ERR("\x43\x6f\x6e\x74\x65\x6e\x74\x20\x74\x6f\x6f\x20"
"\x6c\x61\x72\x67\x65");l8_ret=((1<<31)|(l69_ERR_LV_ERR<<28)|(
l87_ERR_CAT_MSG<<14)|0x11);ly_break;}l0_fd=l450_socket(l145_AF_INET,
l400_SOCK_DGRAM,0);lf_if(l0_fd<0){l142_LOGG_ERRNO("\x73\x6f\x63\x6b"
"\x65\x74");l8_ret=((1<<31)|(l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14
)|0x00);ly_break;}l86_memset(&l29_addr,0,lw_sizeof(l29_addr));
l29_addr.l589_sin_family=l145_AF_INET;l29_addr.l371_sin_addr.
l594_s_addr=l68_htonl(l937_INADDR_LOOPBACK);l29_addr.l548_sin_port=
l503_htons(56000);l39_msg.l30_header.l9_type=l68_htonl(l9_type);lf_if
(ln_data){l109_memcpy(l39_msg.l46_event.l42_content,ln_data,lv_len);}
l8_ret=l448_send_data(l0_fd,&l39_msg,lw_sizeof(l39_msg.l30_header)+
lv_len,(le_struct l103_sockaddr* )&l29_addr,lw_sizeof(l29_addr));
l356_close(l0_fd);}l62_while(0);l240_LOGG_FUNC_OUT();lq_return l8_ret
;}lk_static la_int l697_respond_request(li_const lb_void*ln_data,
la_int lv_len,li_const le_struct l104_sockaddr_in*l67_p_addr){la_int
l0_fd;la_int l8_ret;ll_uint8_t l42_content[128];l86_memset(
l42_content,0,lw_sizeof(l42_content));l246_LOGG_FUNC_IN();l118_do{
lf_if(lv_len>128){l64_LOGG_ERR("\x43\x6f\x6e\x74\x65\x6e\x74\x20\x74"
"\x6f\x6f\x20\x6c\x61\x72\x67\x65");l8_ret=((1<<31)|(l69_ERR_LV_ERR<<
28)|(l87_ERR_CAT_MSG<<14)|0x11);ly_break;}l0_fd=l450_socket(
l145_AF_INET,l400_SOCK_DGRAM,0);lf_if(l0_fd<0){l142_LOGG_ERRNO("\x73"
"\x6f\x63\x6b\x65\x74");l8_ret=((1<<31)|(l69_ERR_LV_ERR<<28)|(
l87_ERR_CAT_MSG<<14)|0x00);ly_break;}lf_if(ln_data){l109_memcpy(
l42_content,ln_data,lv_len);}l8_ret=l448_send_data(l0_fd,&l42_content
,lv_len,(le_struct l103_sockaddr* )l67_p_addr,lw_sizeof(le_struct
l104_sockaddr_in));l356_close(l0_fd);}l62_while(0);l240_LOGG_FUNC_OUT
();lq_return l8_ret;}lk_static la_int l998_hdl_msg(li_const la_int
l0_fd[],la_int l9_type){ll_uint8_t l72_buf[512];la_int l408_buf_usage
;le_struct l290_sockaddr_in6 l29_addr;l265_socklen_t l96_addr_len;
l96_addr_len=lw_sizeof(l29_addr);l408_buf_usage=l748_recvfrom(l0_fd[
l9_type],l72_buf,512,0,(le_struct l103_sockaddr* )&l29_addr,&
l96_addr_len);lf_if(l408_buf_usage<=0){l142_LOGG_ERRNO("\x72\x65\x63"
"\x76\x66\x72\x6f\x6d");lq_return((1<<31)|(l69_ERR_LV_ERR<<28)|(
l87_ERR_CAT_MSG<<14)|0x03);}lf_if(l9_type==l136_LOCAL){lq_return
l953_hdl_local_msg(l0_fd,(le_struct l127_din_local_msg* )l72_buf,
l408_buf_usage,(le_struct l104_sockaddr_in* )&l29_addr);}l3_else{
lq_return l986_hdl_remote_msg(l0_fd,l72_buf,l408_buf_usage,(le_struct
l103_sockaddr* )&l29_addr,l96_addr_len);}}lk_static la_int
l953_hdl_local_msg(li_const la_int l0_fd[],le_struct
l127_din_local_msg*l38_p_msg,la_int l168_msg_len,li_const le_struct
l104_sockaddr_in*l67_p_addr){le_struct l595_dc_info*l140_p_dc_info;
lm_uint32_t l16_dc_id;le_struct l95_dc_data l61_result={};la_int
l8_ret;l246_LOGG_FUNC_IN();l8_ret=((0<<31)|(l53_ERR_LV_DBG<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x00);lf_if(l38_p_msg==lu_NULL){l8_ret=((1<<
31)|(l69_ERR_LV_ERR<<28)|(l37_ERR_CAT_GENERAL<<14)|0x04);}l3_else{
l107_switch(l250_ntohl(l38_p_msg->l30_header.l9_type)){l7_case
l186_IPC_MSG_NETWORK_SEARCH:l27_LOGG_INFO("\x52\x65\x63\x65\x69\x76"
"\x65\x20\x61\x20\x6e\x65\x74\x77\x6f\x72\x6b\x2d\x73\x65\x61\x72\x63"
"\x68\x20\x65\x76\x65\x6e\x74");l16_dc_id=l250_ntohl(l38_p_msg->
l46_event.lo_value[0]);l835_set_dc_info(l948_NET_SEARCH_START,
l16_dc_id,lu_NULL);ly_break;l7_case l192_IPC_MSG_NETWORK_UP:
l27_LOGG_INFO("\x52\x65\x63\x65\x69\x76\x65\x20\x61\x20\x6e\x65\x74"
"\x77\x6f\x72\x6b\x2d\x75\x70\x20\x65\x76\x65\x6e\x74");
l106_g_latency_test_info.l275_fail_cnt=0;l759_set_conn_state(
l1069_CONNECTED);l256_search_server_pipe(l894_OPEN);l8_ret=
l690_search_server(l0_fd,(li_const lj_char* )l38_p_msg->l46_event.
l42_content);ly_break;l7_case l195_IPC_MSG_NETWORK_DOWN:l27_LOGG_INFO
("\x52\x65\x63\x65\x69\x76\x65\x20\x61\x20\x6e\x65\x74\x77\x6f\x72"
"\x6b\x2d\x64\x6f\x77\x6e\x20\x65\x76\x65\x6e\x74");
l759_set_conn_state(l785_DISCONNECTED);l352_set_search_info(l506_FAIL
,lu_NULL,lu_NULL);l861_set_server_addr(lu_NULL,0);
l1008_reset_dc_activity();ly_break;l7_case l200_IPC_MSG_DC_WHO:
l27_LOGG_INFO("\x52\x65\x63\x65\x69\x76\x65\x20\x61\x20\x64\x63\x2d"
"\x77\x68\x6f\x20\x65\x76\x65\x6e\x74");l553_bcast_cmd(l0_fd[
l136_LOCAL],l162_IPC_MSG_DC_STATUS,lu_NULL,0);ly_break;l7_case
l169_IPC_MSG_DC_STATUS_ACK:l27_LOGG_INFO("\x52\x65\x63\x65\x69\x76"
"\x65\x20\x61\x20\x72\x65\x70\x6f\x72\x74\x20\x64\x63\x2d\x73\x74\x61"
"\x74\x75\x73\x20\x61\x63\x6b\x20\x63\x6f\x6d\x6d\x61\x6e\x64");
l16_dc_id=l250_ntohl(l38_p_msg->l30_header.l16_dc_id);l430_printf(""
"\x30\x58\x25\x78\n",l16_dc_id);ly_break;l7_case
l163_IPC_MSG_DC_REGISTER:l27_LOGG_INFO("\x52\x65\x63\x65\x69\x76\x65"
"\x20\x61\x20\x44\x43\x2d\x72\x65\x67\x69\x73\x74\x72\x61\x74\x69\x6f"
"\x6e\x20\x63\x6f\x6d\x6d\x61\x6e\x64");l16_dc_id=l250_ntohl(
l38_p_msg->l30_header.l16_dc_id);l835_set_dc_info(l959_NET_SEARCH_END
,l16_dc_id,l67_p_addr);l140_p_dc_info=l499_get_dc_info(l16_dc_id);
lf_if(l140_p_dc_info!=lu_NULL){le_struct l128_dc_register_ack ln_data
;l109_memcpy(ln_data.l126_net_up_time_list,l140_p_dc_info->
l126_net_up_time_list,lw_sizeof(l140_p_dc_info->l126_net_up_time_list
));ln_data.l141_net_search_latency=l140_p_dc_info->
l141_net_search_latency;l8_ret=l367_send_cmd(l0_fd[l136_LOCAL],
l154_IPC_MSG_DC_REGISTER_ACK,l16_dc_id,&ln_data,lw_sizeof(ln_data));}
lf_if(l20_g_cfg.l338_op_mode==1){lf_if(l228_g_search_info.l65_state==
l659_SUCCESS){l61_result.lo_value[0]=l68_htonl(1);l8_ret=
l367_send_cmd(l0_fd[l136_LOCAL],l125_IPC_MSG_SERVER_LOOKUP_RESULT,
l16_dc_id,&l61_result,lw_sizeof(le_struct l95_dc_data));}l3_else lf_if
(l228_g_search_info.l65_state==l506_FAIL){l61_result.lo_value[0]=0;
l8_ret=l367_send_cmd(l0_fd[l136_LOCAL],
l125_IPC_MSG_SERVER_LOOKUP_RESULT,l16_dc_id,&l61_result,lw_sizeof(
le_struct l95_dc_data));}}l3_else{l61_result.lo_value[0]=0;l8_ret=
l367_send_cmd(l0_fd[l136_LOCAL],l125_IPC_MSG_SERVER_LOOKUP_RESULT,
l16_dc_id,&l61_result,lw_sizeof(le_struct l95_dc_data));}ly_break;
l7_case l187_IPC_MSG_DC_START:{l27_LOGG_INFO("\x52\x65\x63\x65\x69"
"\x76\x65\x20\x61\x20\x73\x74\x61\x72\x74\x2d\x64\x63\x20\x65\x76\x65"
"\x6e\x74");la_int ld_i=0;lj_char*l18_argv[3];lj_char*l98_token=
l292_strtok((lj_char* )l38_p_msg->l46_event.l42_content,"\x20");
l62_while(l98_token!=lu_NULL&&ld_i<3){l18_argv[ld_i++]=l98_token;
l98_token=l292_strtok(lu_NULL,"\x20");}lm_uint32_t l110_id=
l469_conv_dc_name_to_id(l18_argv[0]);l1098_optind=1;l433_pid_t
l925_dc_pid=-1;l925_dc_pid=l963_start_dc((lw_sizeof(l18_argv)/
lw_sizeof(lj_char* )),l18_argv);l140_p_dc_info=l499_get_dc_info(
l110_id);lf_if(l140_p_dc_info!=lu_NULL&&l140_p_dc_info->l148_pid==0){
l140_p_dc_info->l148_pid=l925_dc_pid;}}ly_break;l7_case
l208_IPC_MSG_DC_STOP:{l27_LOGG_INFO("\x52\x65\x63\x65\x69\x76\x65\x20"
"\x61\x20\x73\x74\x6f\x70\x2d\x64\x63\x20\x65\x76\x65\x6e\x74");
lm_uint32_t l110_id=l469_conv_dc_name_to_id((lj_char* )l38_p_msg->
l46_event.l42_content);l140_p_dc_info=l499_get_dc_info(l110_id);lf_if
(l140_p_dc_info!=lu_NULL&&l140_p_dc_info->l148_pid>0){l1135_kill(
l140_p_dc_info->l148_pid,l1179_SIGKILL);l140_p_dc_info->l148_pid=0;}}
ly_break;l7_case l170_IPC_MSG_GET_LATENCY:l27_LOGG_INFO("\x52\x65\x63"
"\x65\x69\x76\x65\x20\x61\x20\x67\x65\x74\x2d\x6c\x61\x74\x65\x6e\x63"
"\x79\x20\x63\x6f\x6d\x6d\x61\x6e\x64");l16_dc_id=l250_ntohl(
l38_p_msg->l30_header.l16_dc_id);lf_if(l1004_start_latency_test(l0_fd
[l262_REMOTE],l16_dc_id)!=((0<<31)|(l53_ERR_LV_DBG<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x00)){l721_stop_latency_test(l0_fd[
l136_LOCAL],0);}ly_break;l7_case l199_IPC_MSG_REPORT_UID:{
l27_LOGG_INFO("\x52\x65\x63\x65\x69\x76\x65\x20\x61\x20\x72\x65\x70"
"\x6f\x72\x74\x2d\x64\x65\x76\x69\x63\x65\x2d\x75\x69\x64\x20\x72\x65"
"\x71\x75\x65\x73\x74");ll_uint8_t ln_data[8];ll_uint8_t*lc_p=ln_data
;{l17_int64_t lg_src=_mb000010003(l123_g_dev_info_report.l44_uid);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),64/8);lc_p+=(64)/8;
};lf_if(l697_respond_request(ln_data,lw_sizeof(ln_data),l67_p_addr)!=
((0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){
l64_LOGG_ERR("\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20"
"\x72\x65\x70\x6f\x72\x74\x5f\x64\x65\x76\x5f\x75\x69\x64");}}
ly_break;l7_case l203_IPC_MSG_SPECIFY_UID:{l27_LOGG_INFO("\x52\x65"
"\x63\x65\x69\x76\x65\x20\x61\x20\x73\x65\x74\x2d\x64\x65\x76\x69\x63"
"\x65\x2d\x75\x69\x64\x20\x65\x76\x65\x6e\x74");l54_union
l1090_t_convert{lt_uint64_t l1120_uid64;ll_uint8_t l332_uid8[8];}
l331_convert;l86_memset(l331_convert.l332_uid8,0,lw_sizeof(
l331_convert.l332_uid8));lj_char*lc_p=(lj_char* )l38_p_msg->l46_event
.l42_content;la_int l967_v,ld_i;l21_for(ld_i=0;ld_i<8;ld_i++){
l1156_sscanf(lc_p,"\x25\x30\x32\x78",&l967_v);l331_convert.l332_uid8[
ld_i]=(ll_uint8_t)l967_v;lc_p+=2;}l123_g_dev_info_report.l44_uid=
_mb000010003(l331_convert.l1120_uid64);}ly_break;l7_case
l206_IPC_MSG_REPORT_FULL_DOMAIN:{l27_LOGG_INFO("\x52\x65\x63\x65\x69"
"\x76\x65\x20\x61\x20\x72\x65\x70\x6f\x72\x74\x2d\x64\x6f\x6d\x61\x69"
"\x6e\x2d\x6e\x61\x6d\x65\x20\x72\x65\x71\x75\x65\x73\x74");lf_if(
l697_respond_request(l228_g_search_info.l76_domain_name,l377_strlen(
l228_g_search_info.l76_domain_name),l67_p_addr)!=((0<<31)|(
l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){l64_LOGG_ERR(""
"\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20\x72\x65\x70\x6f"
"\x72\x74\x5f\x66\x75\x6c\x6c\x5f\x64\x6f\x6d\x61\x69\x6e");}}
ly_break;l7_case l204_IPC_MSG_REPORT_LATENCY_FAIL_CNT:{l27_LOGG_INFO(""
"\x52\x65\x63\x65\x69\x76\x65\x20\x61\x20\x72\x65\x70\x6f\x72\x74\x2d"
"\x73\x65\x72\x76\x65\x72\x2d\x6c\x61\x74\x65\x6e\x63\x79\x2d\x66\x61"
"\x69\x6c\x2d\x63\x6e\x74\x20\x72\x65\x71\x75\x65\x73\x74");lf_if(
l697_respond_request(&l106_g_latency_test_info.l275_fail_cnt,
lw_sizeof(l106_g_latency_test_info.l275_fail_cnt),l67_p_addr)!=((0<<
31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){
l64_LOGG_ERR("\x46\x61\x69\x6c\x20\x74\x6f\x20\x73\x65\x6e\x64\x20"
"\x72\x65\x70\x6f\x72\x74\x5f\x73\x65\x72\x76\x65\x72\x2d\x6c\x61\x74"
"\x65\x6e\x63\x79\x2d\x66\x61\x69\x6c\x2d\x63\x6e\x74");}}ly_break;
l7_case l105_IPC_MSG_SEND_REPORT:l27_LOGG_INFO("\x52\x65\x63\x65\x69"
"\x76\x65\x20\x61\x20\x73\x65\x6e\x64\x2d\x72\x65\x70\x6f\x72\x74\x20"
"\x63\x6f\x6d\x6d\x61\x6e\x64");lf_if(l38_p_msg->l30_header.l16_dc_id
==l68_htonl(l116_IPC_DC_DEV)){l430_printf("\x2a\x2a\x2a\x2a\x2a\x2a"
"\x2a\x2a\x2a\n");l991_set_dev_info(l38_p_msg->l14_cmd.l42_content,
l168_msg_len-lw_sizeof(le_struct l33_data_header));}l3_else{l8_ret=
l362_send_remote_msg(l0_fd[l262_REMOTE],l38_p_msg->l14_cmd.
l42_content,l168_msg_len-lw_sizeof(le_struct l33_data_header),lu_NULL
,0);}ly_break;l7_case l207_IPC_MSG_SET_DEVICE_INFO:{l27_LOGG_INFO(""
"\x52\x65\x63\x65\x69\x76\x65\x20\x61\x20\x64\x65\x76\x69\x63\x65\x2d"
"\x69\x6e\x66\x6f\x72\x6d\x61\x74\x69\x6f\x6e\x20\x72\x65\x70\x6f\x72"
"\x74");lf_if(l38_p_msg->l30_header.l16_dc_id==l68_htonl(
l116_IPC_DC_DEV)){le_struct l132_dev_info_report*l1077_report=(
le_struct l132_dev_info_report* )l38_p_msg->l14_cmd.l42_content;
l123_g_dev_info_report.l44_uid=_mb000010003(l1077_report->l44_uid);}}
ly_break;l7_case l184_IPC_MSG_START_SERVER_HANDSHAKE:{l27_LOGG_INFO(""
"\x52\x65\x63\x65\x69\x76\x65\x20\x61\x20\x73\x74\x61\x72\x74\x2d\x73"
"\x65\x72\x76\x65\x72\x2d\x68\x61\x6e\x64\x73\x68\x61\x6b\x65\x20\x65"
"\x76\x65\x6e\x74");l352_set_search_info(l853_IN_PROGRESS,lu_NULL,
lu_NULL);}ly_break;l7_case l197_IPC_MSG_SEARCH_SERVER_FAIL:
l27_LOGG_INFO("\x52\x65\x63\x65\x69\x76\x65\x20\x61\x20\x73\x65\x61"
"\x72\x63\x68\x2d\x73\x65\x72\x76\x65\x72\x2d\x66\x61\x69\x6c\x20\x65"
"\x76\x65\x6e\x74");l352_set_search_info(l506_FAIL,lu_NULL,lu_NULL);
l106_g_latency_test_info.l275_fail_cnt=65535;l61_result.lo_value[0]=0
;l553_bcast_cmd(l0_fd[l136_LOCAL],l125_IPC_MSG_SERVER_LOOKUP_RESULT,&
l61_result,lw_sizeof(le_struct l95_dc_data));ly_break;l7_case
l196_IPC_MSG_SEARCH_SERVER_WAIT:l27_LOGG_INFO("\x52\x65\x63\x65\x69"
"\x76\x65\x20\x61\x20\x73\x65\x61\x72\x63\x68\x2d\x73\x65\x72\x76\x65"
"\x72\x2d\x77\x61\x69\x74\x20\x65\x76\x65\x6e\x74");
l352_set_search_info(l966_WAIT,lu_NULL,lu_NULL);
l444_set_select_timeout(l20_g_cfg.l329_max_latency*1000);ly_break;
l7_case l178_IPC_MSG_SEND_CONN_HISTORY_INFO:l27_LOGG_INFO("\x52\x65"
"\x63\x65\x69\x76\x65\x20\x61\x20\x73\x65\x6e\x64\x2d\x63\x6f\x6e\x6e"
"\x2d\x68\x69\x73\x74\x6f\x72\x79\x2d\x69\x6e\x66\x6f\x20\x63\x6f\x6d"
"\x6d\x61\x6e\x64");l976_set_conn_history_info(l38_p_msg->l14_cmd.
l42_content,l168_msg_len-lw_sizeof(le_struct l33_data_header));l8_ret
=l868_send_conn_history_info(l0_fd[l262_REMOTE]);ly_break;l7_case
l153_IPC_MSG_CUSTOM_EVENT:l27_LOGG_INFO("\x52\x65\x63\x65\x69\x76\x65"
"\x20\x61\x20\x63\x75\x73\x74\x6f\x6d\x20\x65\x76\x65\x6e\x74");
l16_dc_id=l250_ntohl(l38_p_msg->l46_event.lo_value[0]);l8_ret=
l367_send_cmd(l0_fd[l136_LOCAL],l153_IPC_MSG_CUSTOM_EVENT,l16_dc_id,&
l38_p_msg->l46_event.lo_value[1],lw_sizeof(lm_uint32_t));ly_break;
l238_default:l492_LOGG_WARN("\x52\x65\x63\x65\x69\x76\x65\x20\x61\x6e"
"\x20\x75\x6e\x6b\x6e\x6f\x77\x6e\x20\x6c\x6f\x63\x61\x6c\x20\x6d\x65"
"\x73\x73\x61\x67\x65");l8_ret=((1<<31)|(l234_ERR_LV_WARN<<28)|(
l87_ERR_CAT_MSG<<14)|0x0B);ly_break;}}l240_LOGG_FUNC_OUT();lq_return
l8_ret;}lk_static la_int l986_hdl_remote_msg(li_const la_int l0_fd[],
lb_void*ln_data,la_int l135_data_len,li_const le_struct l103_sockaddr
 *l67_p_addr,l265_socklen_t l96_addr_len){le_struct l355_remote_msg*
l38_p_msg;lj_char l14_cmd[4+1];lm_uint32_t l622_is_auth_ok;le_struct
l95_dc_data l61_result={};la_int l8_ret;l246_LOGG_FUNC_IN();l8_ret=((
0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00);lf_if(
l841_parse_remote_msg(&l38_p_msg,ln_data,l135_data_len,(l32_int32_t)l317_time
(lu_NULL))!=((0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|
0x00)){l8_ret=((1<<31)|(l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14)|
0x14);}l3_else{l109_memcpy(l14_cmd,&l38_p_msg->l14_cmd,lw_sizeof(
l38_p_msg->l14_cmd));l14_cmd[4]='\0';l27_LOGG_INFO("\x52\x65\x63\x65"
"\x69\x76\x65\x20\x25\x73\x20\x63\x6f\x6d\x6d\x61\x6e\x64",l14_cmd);
lf_if(!l273_strcmp(l14_cmd,"\x41\x55\x54\x48")){
l444_set_select_timeout(-1);l622_is_auth_ok=l38_p_msg->lo_value;lf_if
(l622_is_auth_ok){l27_LOGG_INFO("\x41\x75\x74\x68\x65\x6e\x74\x69\x63"
"\x61\x74\x69\x6f\x6e\x20\x4f\x4b");l622_is_auth_ok=l68_htonl(
l622_is_auth_ok);l61_result.lo_value[0]=l68_htonl(l622_is_auth_ok);
l61_result.lo_value[1]=l20_g_cfg.l108_idle_threshold;l553_bcast_cmd(
l0_fd[l136_LOCAL],l125_IPC_MSG_SERVER_LOOKUP_RESULT,&l61_result,
lw_sizeof(le_struct l95_dc_data));l106_g_latency_test_info.
l275_fail_cnt=0;l352_set_search_info(l659_SUCCESS,lu_NULL,lu_NULL);
l861_set_server_addr(l67_p_addr,l96_addr_len);
l868_send_conn_history_info(l0_fd[l262_REMOTE]);}l3_else{
l27_LOGG_INFO("\x41\x75\x74\x68\x65\x6e\x74\x69\x63\x61\x74\x69\x6f"
"\x6e\x20\x66\x61\x69\x6c\x65\x64");l8_ret=l690_search_server(lu_NULL
,lu_NULL);}}l3_else lf_if(!l273_strcmp(l14_cmd,"\x4c\x41\x54\x54")){
lf_if(l38_p_msg->lo_value==l106_g_latency_test_info.l651_test_cnt){
l721_stop_latency_test(l0_fd[l136_LOCAL],1);}}l3_else lf_if(!
l273_strcmp(l14_cmd,"\x44\x4e\x53\x4d")){l20_g_cfg.l315_max_dns_query
=(la_int)l38_p_msg->lo_value;;}l3_else lf_if(!l273_strcmp(l14_cmd,""
"\x48\x41\x4e\x53")){l20_g_cfg.l391_max_handshake=(la_int)l38_p_msg->
lo_value;;}l3_else lf_if(!l273_strcmp(l14_cmd,"\x44\x49\x4e\x4d")){
l20_g_cfg.l338_op_mode=(la_int)l38_p_msg->lo_value;;lf_if(l20_g_cfg.
l338_op_mode==0){l553_bcast_cmd(l0_fd[l136_LOCAL],
l160_IPC_MSG_DC_SHUT_DOWN,lu_NULL,0);}}l3_else lf_if(l14_cmd[0]=='@'){
l860_memmove(l14_cmd,&l14_cmd[1],3);l14_cmd[3]='&';lf_if(l1164_system
(l14_cmd)<0){l492_LOGG_WARN("\x46\x61\x69\x6c\x20\x74\x6f\x20\x65\x78"
"\x65\x63\x75\x74\x65\x20\x25\x2e\x33\x73",l14_cmd);}}l3_else lf_if(
l14_cmd[0]=='>'){lj_char l462_dc[32];lj_char l992_prog_name[64];
lj_char l440_pid_name[16];ll_uint8_t l16_dc_id=l14_cmd[1];ll_uint8_t
l9_type=l14_cmd[2];lf_if(l779_conv_dc_id_to_name(l16_dc_id,l462_dc))lq_return
((1<<31)|(l69_ERR_LV_ERR<<28)|(l37_ERR_CAT_GENERAL<<14)|0x04);
l219_sprintf(l992_prog_name,"\x64\x63\x5f\x25\x73\x5f\x65\x78\x74\x65"
"\x72\x6e\x61\x6c\x5f\x63\x6d\x64\x5f\x65\x78\x65\x63\x75\x74\x65",
l462_dc);l219_sprintf(l440_pid_name,"\x25\x73\x5f\x63\x6d\x64\x5f\x25"
"\x64",l462_dc,l9_type);lb_void*l133_lib_handle=l867_dlopen(lu_NULL,
l788_RTLD_NOW);lf_if(!l133_lib_handle){l64_LOGG_ERR("\x25\x73",
l260_dlerror());lq_return((1<<31)|(l234_ERR_LV_WARN<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x01);}l260_dlerror();la_int( *l629_prog)(
ll_uint8_t,lm_uint32_t)=l679_dlsym(l133_lib_handle,l992_prog_name);
lj_char*l266_error=l260_dlerror();lf_if(l266_error!=lu_NULL){
l64_LOGG_ERR("\x25\x73",l266_error);l221_dlclose(l133_lib_handle);
lq_return((1<<31)|(l234_ERR_LV_WARN<<28)|(l37_ERR_CAT_GENERAL<<14)|
0x02);}la_int l0_fd=l597_lock_pid_file(l440_pid_name);lf_if(l0_fd<0){
l221_dlclose(l133_lib_handle);lq_return((1<<31)|(l234_ERR_LV_WARN<<28
)|(l347_ERR_CAT_DAEMON<<14)|0x00);}l558_unlock_pid_file(l0_fd);
li_const l433_pid_t l148_pid=l775_fork();lf_if(l148_pid<0){
l142_LOGG_ERRNO("\x66\x6f\x72\x6b\x20\x66\x61\x69\x6c\x65\x64");
l221_dlclose(l133_lib_handle);lq_return((1<<31)|(l69_ERR_LV_ERR<<28)|
(l347_ERR_CAT_DAEMON<<14)|0x01);}lf_if(l148_pid==0){
l942_handle_ext_cmd_child_process(l133_lib_handle,l440_pid_name,
l14_cmd,l38_p_msg->lo_value,l629_prog);}l221_dlclose(l133_lib_handle);
}}l240_LOGG_FUNC_OUT();lq_return l8_ret;}lb_void
l942_handle_ext_cmd_child_process(lb_void*l133_lib_handle,lj_char*
l440_pid_name,lj_char l14_cmd[5],lm_uint32_t lo_value,la_int( *
l629_prog)(ll_uint8_t,lm_uint32_t)){la_int l0_fd;lf_if((l0_fd=
l597_lock_pid_file(l440_pid_name))<0){l221_dlclose(l133_lib_handle);
l191_LOGG_DBG("\x50\x72\x6f\x63\x65\x73\x73\x20\x66\x6f\x72\x20\x25"
"\x73\x20\x68\x61\x73\x20\x61\x6c\x72\x65\x61\x64\x79\x20\x73\x74\x61"
"\x72\x74\x65\x64\x2c\x20\x63\x6c\x6f\x73\x65\x20\x74\x68\x69\x73\x20"
"\x63\x61\x6c\x6c",l440_pid_name);l426_exit(0);}la_int l341_r=
l629_prog(l14_cmd[2],lo_value);lf_if(l14_cmd[3]&0x1){lf_if(l341_r!=-1
){l14_cmd[3]|=(0x1<<1);lf_if(l341_r==1)l14_cmd[3]|=(0x1<<2);}}
l558_unlock_pid_file(l0_fd);l221_dlclose(l133_lib_handle);lf_if(
l14_cmd[3]&0x1)l1038_pack_and_send_ext_cmd_ack(l14_cmd,lo_value,
l341_r);l426_exit(l341_r);}lk_static la_int
l1038_pack_and_send_ext_cmd_ack(lj_char l14_cmd[5],lm_uint32_t
lo_value,la_int l8_ret){lf_if(l8_ret!=0||!(l14_cmd[3]&0x01))lq_return
l8_ret;la_int l1018_ack_data_len=13;ll_uint8_t*lc_p;ll_uint8_t ln_data
[l1018_ack_data_len];lc_p=ln_data;{l2_int8_t lg_src=l14_cmd[0];
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{l2_int8_t lg_src=l14_cmd[1];_mb000010004((lb_void* )lc_p,(lb_void* )(
&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=l14_cmd[2];_mb000010004
((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t
lg_src=l14_cmd[3];_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8
/8);lc_p+=(8)/8;};{l32_int32_t lg_src=_mb000010002(lo_value);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;
};lq_return l201_util_send_report_ex(0xC3,l267_DINP_HDR_MASK_UID,
ln_data,l1018_ack_data_len,l14_cmd[1]);}la_int l971_update_dev_info(
la_int l0_fd){lf_if(l1029_g_dev_info_last_update_time_init==0){
l317_time(&l820_g_dev_info_last_update_time);
l1029_g_dev_info_last_update_time_init=1;lq_return((0<<31)|(
l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00);}l1102_time_t
l901_cur_time;l317_time(&l901_cur_time);lr_double l78_diff=
l1163_difftime(l901_cur_time,l820_g_dev_info_last_update_time);la_int
l856_update_interval=l20_g_cfg.l449_dev_info_report_interval;lf_if(
l856_update_interval<60)l856_update_interval=60;lf_if(l233_g_dev_info
.lv_len>0&&l78_diff>=l856_update_interval){l317_time(&
l820_g_dev_info_last_update_time); * (l233_g_dev_info.ln_data+1)=0xC4
;lf_if(l362_send_remote_msg(l0_fd,l233_g_dev_info.ln_data,
l233_g_dev_info.lv_len,&l139_g_server_addr.l29_addr,
l139_g_server_addr.lv_len)!=((0<<31)|(l53_ERR_LV_DBG<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x00)){ * (l233_g_dev_info.ln_data+1)=0x01;
lq_return((1<<31)|(l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14)|0x05);} *
(l233_g_dev_info.ln_data+1)=0x01;}lq_return((0<<31)|(l53_ERR_LV_DBG<<
28)|(l37_ERR_CAT_GENERAL<<14)|0x00);}lk_static lb_void l553_bcast_cmd
(la_int l0_fd,lm_uint32_t l474_cmd_type,li_const lb_void*ln_data,
la_int lv_len){la_int ld_i;l21_for(ld_i=0;ld_i<24;ld_i++){lf_if(
l746_g_dc_info_list[ld_i].l148_pid>0){l367_send_cmd(l0_fd,
l474_cmd_type,l116_IPC_DC_DEV+ld_i,ln_data,lv_len);}}}lk_static la_int
l367_send_cmd(la_int l0_fd,lm_uint32_t l474_cmd_type,lm_uint32_t
l16_dc_id,li_const lb_void*ln_data,la_int lv_len){le_struct
l595_dc_info*l140_p_dc_info;le_struct l127_din_local_msg l39_msg;
la_int l8_ret;l246_LOGG_FUNC_IN();l118_do{lf_if(lv_len>512){l8_ret=((
1<<31)|(l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14)|0x11);ly_break;}
l140_p_dc_info=l499_get_dc_info(l16_dc_id);lf_if(l140_p_dc_info==
lu_NULL){l8_ret=((1<<31)|(l234_ERR_LV_WARN<<28)|(l87_ERR_CAT_MSG<<14)|
0x0A);ly_break;}lf_if(l140_p_dc_info->l148_pid<=0){l8_ret=((1<<31)|(
l234_ERR_LV_WARN<<28)|(l87_ERR_CAT_MSG<<14)|0x09);ly_break;}
l27_LOGG_INFO("\x43\x6f\x6d\x6d\x61\x6e\x64\x20\x54\x79\x70\x65\x3a"
"\x20\x25\x30\x38\x58",l474_cmd_type);l27_LOGG_INFO("\x44\x43\x20\x49"
"\x44\x3a\x20\x25\x30\x38\x58",l16_dc_id);l39_msg.l30_header.l9_type=
l68_htonl(l474_cmd_type);l39_msg.l30_header.l16_dc_id=l68_htonl(
l16_dc_id);lf_if(ln_data){l109_memcpy(l39_msg.l14_cmd.l42_content,
ln_data,lv_len);}l8_ret=l448_send_data(l0_fd,&l39_msg,lw_sizeof(
l39_msg.l30_header)+lv_len,(le_struct l103_sockaddr* )&l140_p_dc_info
->l29_addr,lw_sizeof(le_struct l104_sockaddr_in));}l62_while(0);
l240_LOGG_FUNC_OUT();lq_return l8_ret;}lk_static la_int
l362_send_remote_msg(la_int l0_fd,li_const lb_void*ln_data,la_int
l135_data_len,li_const le_struct l103_sockaddr*l67_p_addr,
l265_socklen_t l96_addr_len){ll_uint8_t l39_msg[512];la_int
l168_msg_len;lf_if(l67_p_addr==lu_NULL){lf_if(!l139_g_server_addr.
l626_is_active){lq_return((1<<31)|(l69_ERR_LV_ERR<<28)|(
l87_ERR_CAT_MSG<<14)|0x08);}l67_p_addr=(le_struct l103_sockaddr* )&
l139_g_server_addr.l29_addr;l96_addr_len=l139_g_server_addr.lv_len;}
l168_msg_len=l792_pack_remote_msg(l39_msg,ln_data,l135_data_len);
lq_return l448_send_data(l0_fd,l39_msg,l168_msg_len,l67_p_addr,
l96_addr_len);}la_int l448_send_data(la_int l0_fd,li_const lb_void*
ln_data,la_int l135_data_len,li_const le_struct l103_sockaddr*
l67_p_addr,l265_socklen_t l96_addr_len){la_int l572_sent_len;
l62_while(l135_data_len>0){l572_sent_len=l657_sendto(l0_fd,ln_data,
l135_data_len,0,l67_p_addr,l96_addr_len);lf_if(l572_sent_len<0){
l142_LOGG_ERRNO("\x73\x65\x6e\x64\x74\x6f");lq_return((1<<31)|(
l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14)|0x05);}lf_if(l572_sent_len
==0){ly_break;}ln_data+=l572_sent_len;l135_data_len-=l572_sent_len;}
lq_return((0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00
);}l13_enum{l614_READ,l606_WRITE};lk_static la_int
l256_search_server_pipe(li_const la_int l500_option){lk_static la_int
l279_pipe_fd[2];l107_switch(l500_option){l7_case l894_OPEN:{lf_if(
l279_pipe_fd[l614_READ]!=-1||l279_pipe_fd[l606_WRITE]!=-1){
l256_search_server_pipe(l636_CLOSE_ALL);}lf_if(l1181_pipe(
l279_pipe_fd)<0){l142_LOGG_ERRNO("\x49\x6e\x69\x74\x69\x61\x6c\x20"
"\x70\x69\x70\x65\x20\x66\x61\x69\x6c\x65\x64");}ly_break;}l7_case
l980_GET_READ:{lq_return l279_pipe_fd[l614_READ];}l7_case
l817_GET_WRITE:{lq_return l279_pipe_fd[l606_WRITE];}l7_case
l799_CLOSE_READ:{lf_if(l279_pipe_fd[l614_READ]!=-1){l356_close(
l279_pipe_fd[l614_READ]);l279_pipe_fd[l614_READ]=-1;}ly_break;}
l7_case l637_CLOSE_WRITE:{lf_if(l279_pipe_fd[l606_WRITE]!=-1){
l356_close(l279_pipe_fd[l606_WRITE]);l279_pipe_fd[l606_WRITE]=-1;}
ly_break;}l7_case l636_CLOSE_ALL:{l256_search_server_pipe(
l799_CLOSE_READ);l256_search_server_pipe(l637_CLOSE_WRITE);ly_break;}
l238_default:{lq_return-1;}}lq_return 0;}lk_static la_int
l690_search_server(li_const la_int l0_fd[],li_const lj_char*
l76_domain_name){l107_switch(l228_g_search_info.l65_state){l7_case
l659_SUCCESS:l7_case l506_FAIL:lf_if(l0_fd==lu_NULL||l76_domain_name
==lu_NULL){lq_return((1<<31)|(l69_ERR_LV_ERR<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x04);}l352_set_search_info(l274_INIT,l0_fd,
l76_domain_name);ly_break;l7_case l966_WAIT:lf_if(l0_fd==lu_NULL&&
l76_domain_name==lu_NULL){l352_set_search_info(l853_IN_PROGRESS,
lu_NULL,lu_NULL);la_int l94_opt=l907_CONTINUE;lf_if(l1005_write(
l256_search_server_pipe(l817_GET_WRITE),&l94_opt,lw_sizeof(l94_opt))<
0){l142_LOGG_ERRNO("\x57\x72\x69\x74\x65\x20\x74\x6f\x20\x70\x69\x70"
"\x65\x20\x66\x61\x69\x6c\x65\x64");lq_return((1<<31)|(l69_ERR_LV_ERR
<<28)|(l37_ERR_CAT_GENERAL<<14)|0x09);}}l7_case l274_INIT:l7_case
l853_IN_PROGRESS:l492_LOGG_WARN("\x53\x65\x61\x72\x63\x68\x20\x6e\x6f"
"\x74\x20\x79\x65\x74\x20\x66\x69\x6e\x69\x73\x68\x65\x64");lq_return
((1<<31)|(l234_ERR_LV_WARN<<28)|(l87_ERR_CAT_MSG<<14)|0x10);
l238_default:lq_return((1<<31)|(l69_ERR_LV_ERR<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x08);}li_const l433_pid_t l148_pid=
l775_fork();lf_if(l148_pid<0){l142_LOGG_ERRNO("\x46\x6f\x72\x6b\x20"
"\x68\x61\x6e\x64\x73\x68\x61\x6b\x65\x20\x70\x72\x6f\x63\x65\x73\x73"
"\x20\x66\x61\x69\x6c\x65\x64");lq_return((1<<31)|(l69_ERR_LV_ERR<<28
)|(l347_ERR_CAT_DAEMON<<14)|0x01);}lf_if(l148_pid==0){
l256_search_server_pipe(l637_CLOSE_WRITE);l940_search_server_impl();
l27_LOGG_INFO("\x4c\x65\x61\x76\x65\x20\x73\x65\x72\x76\x65\x72\x20"
"\x68\x61\x6e\x64\x73\x68\x61\x6b\x65\x20\x70\x72\x6f\x63\x65\x73\x73"
);l426_exit(0);}l3_else{l256_search_server_pipe(l799_CLOSE_READ);}
l27_LOGG_INFO("\x53\x74\x61\x72\x74\x20\x73\x65\x61\x72\x63\x68\x69"
"\x6e\x67\x20\x73\x65\x72\x76\x65\x72");lq_return((0<<31)|(
l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00);}lk_static lb_void
l940_search_server_impl(lb_void){l13_enum{l979_SRC_OPT_DOMAIN_NAME,
l1084_SRC_CFG_DOMAIN_NAME,l1079_SRC_CFG_IP_ADDR,
l1121_SRC_DFLT_DOMAIN_NAME,l1068_SRC_END};le_struct l290_sockaddr_in6
l293_addr_list[16];la_int l833_port_list[16];la_int l504_addr_index;
la_int l427_port_index;la_int l129_addr_cnt;la_int l770_port_cnt;
la_int l1019_src_index;l1085_in_port_t l124_port;lj_char
l76_domain_name[128];lj_char l74_ip_addr[128];lj_char l1152_txt_rec[
128];le_struct l103_sockaddr*l67_p_addr;le_struct l104_sockaddr_in*
l473_p_addr_v4;le_struct l290_sockaddr_in6*l461_p_addr_v6;la_int
l682_cont;l265_socklen_t l96_addr_len;l246_LOGG_FUNC_IN();lf_if(
l228_g_search_info.l65_state==l274_INIT){l243_send_event(
l184_IPC_MSG_START_SERVER_HANDSHAKE,lu_NULL,0);l1019_src_index=
l979_SRC_OPT_DOMAIN_NAME;l504_addr_index=0;l427_port_index=0;
l129_addr_cnt=0;l770_port_cnt=16;l731_load_random_list(l833_port_list
,&l770_port_cnt,l20_g_cfg.l438_server_port,l20_g_cfg.
l447_server_port_range);}l682_cont=1;l62_while(l682_cont){lf_if(
l975_g_conn_state==l785_DISCONNECTED){ly_break;}lf_if(l427_port_index
<l770_port_cnt){lf_if(l504_addr_index<l129_addr_cnt){l67_p_addr=(
le_struct l103_sockaddr* )&l293_addr_list[l504_addr_index];l124_port=
(l1085_in_port_t)l833_port_list[l427_port_index];l191_LOGG_DBG("\x49"
"\x50\x20\x61\x64\x64\x72\x65\x73\x73\x20\x66\x61\x6d\x69\x6c\x79\x3a"
"\x20\x25\x68\x75",l67_p_addr->l1054_sa_family);lf_if(l67_p_addr->
l1054_sa_family==l145_AF_INET){l473_p_addr_v4=(le_struct
l104_sockaddr_in* )l67_p_addr;l473_p_addr_v4->l548_sin_port=
l503_htons(l124_port);l96_addr_len=lw_sizeof(le_struct
l104_sockaddr_in);l790_inet_ntop(l145_AF_INET,&l473_p_addr_v4->
l371_sin_addr,l74_ip_addr,lw_sizeof(l74_ip_addr));}l3_else{
l461_p_addr_v6=(le_struct l290_sockaddr_in6* )l67_p_addr;
l461_p_addr_v6->l1177_sin6_port=l503_htons(l124_port);l96_addr_len=
lw_sizeof(le_struct l290_sockaddr_in6);l790_inet_ntop(l445_AF_INET6,&
l461_p_addr_v6->l795_sin6_addr,l74_ip_addr,lw_sizeof(l74_ip_addr));}
la_int l341_r=l918_handshake(l228_g_search_info.l0_fd[l262_REMOTE],
l67_p_addr,l96_addr_len);l27_LOGG_INFO("\x48\x61\x6e\x64\x73\x68\x61"
"\x6b\x65\x20\x77\x69\x74\x68\x20\x25\x73\x28\x23\x25\x64\x29\x3a\x25"
"\x64\x28\x23\x25\x64\x29\x3b\x20\x72\x65\x73\x75\x6c\x74\x20\x3d\x20"
"\x5b\x25\x64\x5d",l74_ip_addr,l504_addr_index+1,l833_port_list[
l427_port_index],l427_port_index+1,l341_r);l427_port_index++;lf_if(
l341_r==((0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){
l243_send_event(l196_IPC_MSG_SEARCH_SERVER_WAIT,lu_NULL,0);la_int
l94_opt;la_int l726_read_in=l1080_read(l256_search_server_pipe(
l980_GET_READ),&l94_opt,lw_sizeof(l94_opt));lf_if(l726_read_in<=0){
l142_LOGG_ERRNO("\x52\x65\x61\x64\x20\x66\x72\x6f\x6d\x20\x70\x69\x70"
"\x65\x20\x66\x61\x69\x6c\x65\x64");ly_break;}l107_switch(l94_opt){
l7_case l907_CONTINUE:{l191_LOGG_DBG("\x48\x61\x6e\x64\x73\x68\x61"
"\x6b\x65\x20\x70\x72\x6f\x63\x65\x73\x73\x20\x69\x73\x20\x67\x6f\x69"
"\x6e\x67\x20\x74\x6f\x20\x63\x6f\x6e\x74\x69\x6e\x75\x65");}ly_break
;l7_case l1031_TERMINATE:{l191_LOGG_DBG("\x48\x61\x6e\x64\x73\x68\x61"
"\x6b\x65\x20\x70\x72\x6f\x63\x65\x73\x73\x20\x69\x73\x20\x67\x6f\x69"
"\x6e\x67\x20\x74\x6f\x20\x74\x65\x72\x6d\x69\x6e\x61\x74\x65");
l682_cont=0;}ly_break;l238_default:{l64_LOGG_ERR("\x53\x65\x61\x72"
"\x63\x68\x20\x73\x65\x72\x76\x65\x72\x20\x70\x72\x6f\x63\x65\x73\x73"
"\x20\x72\x65\x63\x65\x69\x76\x65\x20\x77\x72\x6f\x6e\x67\x20\x6f\x70"
"\x65\x72\x61\x74\x69\x6f\x6e\x3a\x20\x25\x64",l94_opt);ly_break;}
ly_break;}}}l3_else{l129_addr_cnt=0;l504_addr_index=0;l107_switch(
l1019_src_index++){l7_case l979_SRC_OPT_DOMAIN_NAME:{l27_LOGG_INFO(""
"\x53\x65\x61\x72\x63\x68\x20\x73\x65\x72\x76\x65\x72\x20\x75\x73\x69"
"\x6e\x67\x20\x64\x6f\x6d\x61\x69\x6e\x20\x6e\x61\x6d\x65\x20\x66\x72"
"\x6f\x6d\x20\x63\x6f\x6d\x6d\x61\x6e\x64\x2d\x6c\x69\x6e\x65\x20\x61"
"\x72\x67\x75\x6d\x65\x6e\x74\x3a\x20\x25\x73",l228_g_search_info.
l76_domain_name);lf_if(l377_strlen(l228_g_search_info.l76_domain_name
)>0){l219_sprintf(l76_domain_name,"\x25\x73\x2d\x25\x73",
l228_g_search_info.l76_domain_name,l20_g_cfg.l314_server_suffix);
l129_addr_cnt=16;l560_query_server_addr(l293_addr_list,&l129_addr_cnt
,l76_domain_name,l20_g_cfg.l315_max_dns_query);}ly_break;}l7_case
l1084_SRC_CFG_DOMAIN_NAME:{l27_LOGG_INFO("\x53\x65\x61\x72\x63\x68"
"\x20\x73\x65\x72\x76\x65\x72\x20\x75\x73\x69\x6e\x67\x20\x64\x6f\x6d"
"\x61\x69\x6e\x20\x6e\x61\x6d\x65\x20\x66\x72\x6f\x6d\x20\x63\x6f\x6e"
"\x66\x69\x67\x75\x72\x61\x74\x69\x6f\x6e\x20\x66\x69\x6c\x65\x3a\x20"
"\x25\x73",l20_g_cfg.l399_server_domain_name);lf_if(l377_strlen(
l20_g_cfg.l399_server_domain_name)>0){l219_sprintf(l76_domain_name,""
"\x25\x73\x2d\x25\x73",l20_g_cfg.l399_server_domain_name,l20_g_cfg.
l314_server_suffix);l129_addr_cnt=16;l560_query_server_addr(
l293_addr_list,&l129_addr_cnt,l76_domain_name,l20_g_cfg.
l315_max_dns_query);}ly_break;}l7_case l1079_SRC_CFG_IP_ADDR:{
l27_LOGG_INFO("\x53\x65\x61\x72\x63\x68\x20\x73\x65\x72\x76\x65\x72"
"\x20\x75\x73\x69\x6e\x67\x20\x49\x50\x20\x61\x64\x64\x72\x65\x73\x73"
"\x20\x66\x72\x6f\x6d\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x61\x74\x69"
"\x6f\x6e\x20\x66\x69\x6c\x65\x3a\x20\x25\x73",l20_g_cfg.
l328_server_ip_addr);lf_if(l377_strlen(l20_g_cfg.l328_server_ip_addr)>
0){l473_p_addr_v4=(le_struct l104_sockaddr_in* )&l293_addr_list[0];
lf_if(l798_inet_pton(l145_AF_INET,l20_g_cfg.l328_server_ip_addr,&
l473_p_addr_v4->l371_sin_addr)==1){l473_p_addr_v4->l589_sin_family=
l145_AF_INET;l129_addr_cnt=1;}l3_else{l461_p_addr_v6=(le_struct
l290_sockaddr_in6* )&l293_addr_list[0];lf_if(l798_inet_pton(
l445_AF_INET6,l20_g_cfg.l328_server_ip_addr,&l461_p_addr_v6->
l795_sin6_addr)==1){l461_p_addr_v6->l1162_sin6_family=l445_AF_INET6;
l129_addr_cnt=1;}}}ly_break;}l7_case l1121_SRC_DFLT_DOMAIN_NAME:{
l27_LOGG_INFO("\x53\x65\x61\x72\x63\x68\x20\x73\x65\x72\x76\x65\x72"
"\x20\x75\x73\x69\x6e\x67\x20\x64\x65\x66\x61\x75\x6c\x74\x20\x64\x6f"
"\x6d\x61\x69\x6e\x20\x6e\x61\x6d\x65");l219_sprintf(l76_domain_name,""
"\x64\x65\x66\x61\x75\x6c\x74\x2d\x25\x73",l20_g_cfg.
l314_server_suffix);l129_addr_cnt=16;l560_query_server_addr(
l293_addr_list,&l129_addr_cnt,l76_domain_name,l20_g_cfg.
l315_max_dns_query);ly_break;}l7_case l1068_SRC_END:{l243_send_event(
l197_IPC_MSG_SEARCH_SERVER_FAIL,lu_NULL,0);l682_cont=0;ly_break;}}}}
l3_else{l427_port_index=0;l504_addr_index++;}}l240_LOGG_FUNC_OUT();}
lk_static la_int l918_handshake(la_int l0_fd,li_const le_struct
l103_sockaddr*l67_p_addr,l265_socklen_t l96_addr_len){la_int ld_i;
la_int l8_ret;l246_LOGG_FUNC_IN();l8_ret=((1<<31)|(l69_ERR_LV_ERR<<28
)|(l87_ERR_CAT_MSG<<14)|0x0F);lf_if(l233_g_dev_info.lv_len>0){l21_for
(ld_i=1;ld_i<=l20_g_cfg.l391_max_handshake;ld_i++){l27_LOGG_INFO(""
"\x48\x61\x6e\x64\x73\x68\x61\x6b\x65\x20\x77\x69\x74\x68\x20\x73\x65"
"\x72\x76\x65\x72\x2c\x20\x23\x25\x64",ld_i);lf_if(
l362_send_remote_msg(l0_fd,l233_g_dev_info.ln_data,l233_g_dev_info.
lv_len,l67_p_addr,l96_addr_len)==((0<<31)|(l53_ERR_LV_DBG<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x00)){l8_ret=((0<<31)|(l53_ERR_LV_DBG<<28)|
(l37_ERR_CAT_GENERAL<<14)|0x00);ly_break;}}}l240_LOGG_FUNC_OUT();
lq_return l8_ret;}lk_static la_int l868_send_conn_history_info(la_int
l0_fd){ll_uint8_t ln_data[512];la_int l135_data_len;la_int l8_ret;
l246_LOGG_FUNC_IN();lf_if(!l139_g_server_addr.l626_is_active){
lq_return((1<<31)|(l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14)|0x16);}
l8_ret=((0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00);
lf_if(!l159_g_conn_history_info.l668_is_sent&&
l159_g_conn_history_info.l470_list_size>0){l135_data_len=
l862_pack_conn_history_info(ln_data);l8_ret=l362_send_remote_msg(
l0_fd,ln_data,l135_data_len,&l139_g_server_addr.l29_addr,
l139_g_server_addr.lv_len);lf_if(l8_ret==((0<<31)|(l53_ERR_LV_DBG<<28
)|(l37_ERR_CAT_GENERAL<<14)|0x00)){l159_g_conn_history_info.
l668_is_sent=1;}}l240_LOGG_FUNC_OUT();lq_return l8_ret;}lk_static
la_int l1004_start_latency_test(la_int l0_fd,lm_uint32_t
l360_requester){ll_uint8_t ln_data[512];la_int l135_data_len;lf_if(!
l106_g_latency_test_info.l507_is_testing){l738_set_latency_test_info(
1,l360_requester);lf_if(!l139_g_server_addr.l626_is_active){lq_return
((1<<31)|(l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14)|0x15);}
l135_data_len=l891_pack_latency_test_info(ln_data);lf_if(
l362_send_remote_msg(l0_fd,ln_data,l135_data_len,&l139_g_server_addr.
l29_addr,l139_g_server_addr.lv_len)!=((0<<31)|(l53_ERR_LV_DBG<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x00)){lq_return((1<<31)|(l69_ERR_LV_ERR<<28
)|(l87_ERR_CAT_MSG<<14)|0x15);}lf_if(l362_send_remote_msg(l0_fd,
ln_data,l135_data_len,&l139_g_server_addr.l29_addr,l139_g_server_addr
.lv_len)!=((0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|
0x00)){lq_return((1<<31)|(l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14)|
0x15);}lf_if(l362_send_remote_msg(l0_fd,ln_data,l135_data_len,&
l139_g_server_addr.l29_addr,l139_g_server_addr.lv_len)!=((0<<31)|(
l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00)){lq_return((1<<31
)|(l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14)|0x15);}
l444_set_select_timeout(l20_g_cfg.l329_max_latency*1000);}lq_return((
0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00);}
lk_static lb_void l721_stop_latency_test(la_int l0_fd,la_int
l483_is_success){lm_uint32_t l75_latency;lf_if(
l106_g_latency_test_info.l507_is_testing){l738_set_latency_test_info(
0,-1);lf_if(l483_is_success){l75_latency=(lm_uint32_t)(
l106_g_latency_test_info.l509_end_time_usec-l106_g_latency_test_info.
l463_start_time_usec)/1000;lf_if(l75_latency>l20_g_cfg.
l329_max_latency){l75_latency=-1;}l106_g_latency_test_info.
l275_fail_cnt=0;}l3_else{l75_latency=-1;lf_if(
l106_g_latency_test_info.l275_fail_cnt<65535){
l106_g_latency_test_info.l275_fail_cnt++;}}l367_send_cmd(l0_fd,
l177_IPC_MSG_GET_LATENCY_ACK,l106_g_latency_test_info.l360_requester,
&l75_latency,lw_sizeof(l75_latency));l444_set_select_timeout(-1);}}
lk_static lb_void l991_set_dev_info(li_const lb_void*ln_data,la_int
lv_len){l233_g_dev_info.lv_len=lv_len;l109_memcpy(l233_g_dev_info.
ln_data,ln_data,lv_len);}lk_static lb_void l759_set_conn_state(
l13_enum l805_conn_state l65_state){l975_g_conn_state=l65_state;}
lk_static lb_void l444_set_select_timeout(l17_int64_t
l101_timeout_usec){l518_g_select_timeout_usec=l101_timeout_usec;}
lk_static lb_void l352_set_search_info(l13_enum l859_search_state
l65_state,li_const la_int l0_fd[],li_const lj_char*l76_domain_name){
l246_LOGG_FUNC_IN();l228_g_search_info.l65_state=l65_state;lf_if(
l65_state==l659_SUCCESS){la_int l94_opt=l1031_TERMINATE;lf_if(
l1005_write(l256_search_server_pipe(l817_GET_WRITE),&l94_opt,
lw_sizeof(l94_opt))<0){l142_LOGG_ERRNO("\x57\x72\x69\x74\x65\x20\x74"
"\x6f\x20\x70\x69\x70\x65\x20\x66\x61\x69\x6c\x65\x64");}
l256_search_server_pipe(l637_CLOSE_WRITE);}lf_if(l65_state==l506_FAIL
){l256_search_server_pipe(l636_CLOSE_ALL);}lf_if(l0_fd!=lu_NULL){
l109_memcpy(l228_g_search_info.l0_fd,l0_fd,lw_sizeof(
l228_g_search_info.l0_fd));}lf_if(l76_domain_name!=lu_NULL){
l361_strcpy(l228_g_search_info.l76_domain_name,l76_domain_name);}
l240_LOGG_FUNC_OUT();}lk_static lb_void l861_set_server_addr(li_const
le_struct l103_sockaddr*l67_p_addr,la_int l96_addr_len){lf_if(
l67_p_addr!=lu_NULL){l139_g_server_addr.l626_is_active=1;
l139_g_server_addr.lv_len=l96_addr_len;l109_memcpy(&
l139_g_server_addr.l29_addr,l67_p_addr,l96_addr_len);}l3_else{
l139_g_server_addr.l626_is_active=0;}}lk_static lb_void
l738_set_latency_test_info(la_int l899_is_start,lm_uint32_t
l360_requester){lf_if(l899_is_start){l106_g_latency_test_info.
l507_is_testing=1;l106_g_latency_test_info.l651_test_cnt++;
l106_g_latency_test_info.l463_start_time_usec=l344_get_time_now_usec(
);l106_g_latency_test_info.l360_requester=l360_requester;}l3_else{
l106_g_latency_test_info.l507_is_testing=0;l106_g_latency_test_info.
l509_end_time_usec=l344_get_time_now_usec();}}lk_static lb_void
l835_set_dc_info(la_int l9_type,lm_uint32_t l110_id,li_const le_struct
l104_sockaddr_in*l67_p_addr){le_struct l595_dc_info*l147_p_info=
l499_get_dc_info(l110_id);lf_if(l147_p_info!=lu_NULL){l107_switch(
l9_type){l7_case l948_NET_SEARCH_START:l147_p_info->
l642_net_search_start_time=l344_get_time_now_usec();ly_break;l7_case
l959_NET_SEARCH_END:l147_p_info->l29_addr= *l67_p_addr;l860_memmove(&
l147_p_info->l126_net_up_time_list[1],&l147_p_info->
l126_net_up_time_list[0],(5-1) *lw_sizeof(lm_uint32_t));l147_p_info->
l126_net_up_time_list[0]=l68_htonl((lm_uint32_t)l317_time(lu_NULL));
lf_if(l147_p_info->l642_net_search_start_time==0){l147_p_info->
l141_net_search_latency=-1;}l3_else{l147_p_info->
l141_net_search_latency=l68_htonl((lm_uint32_t)(
l344_get_time_now_usec()-l147_p_info->l642_net_search_start_time)/
1000);}ly_break;}}}lk_static lb_void l976_set_conn_history_info(
li_const lb_void*ln_data,la_int lv_len){le_struct l871_conn_history*
l147_p_info;lf_if(ln_data!=lu_NULL){l159_g_conn_history_info.
l668_is_sent=0;lf_if(l159_g_conn_history_info.l470_list_size<5){
l159_g_conn_history_info.l470_list_size++;}l860_memmove(&
l159_g_conn_history_info.lz_list[1],&l159_g_conn_history_info.lz_list
[0],(5-1) *lw_sizeof(le_struct l871_conn_history));l147_p_info=&
l159_g_conn_history_info.lz_list[0];l147_p_info->lv_len=lv_len;
l147_p_info->l317_time=l68_htonl((lm_uint32_t)l317_time(lu_NULL));
l109_memcpy(l147_p_info->ln_data,ln_data,lv_len);}}lk_static lb_void
l1008_reset_dc_activity(lb_void){la_int ld_i;l21_for(ld_i=0;ld_i<24;
ld_i++){l746_g_dc_info_list[ld_i].l148_pid=0;l746_g_dc_info_list[ld_i
].l642_net_search_start_time=0;}}lk_static le_struct l595_dc_info*
l499_get_dc_info(lm_uint32_t l110_id){lm_uint32_t l264_index;
l264_index=l110_id-l116_IPC_DC_DEV;lf_if(l264_index>=0&&l264_index<24
){lq_return&l746_g_dc_info_list[l264_index];}lq_return lu_NULL;}
