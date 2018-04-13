#include<stdint.h>
#include"mobric.h"
le_struct l355_remote_msg{lm_uint32_t l319_timestamp;lm_uint32_t
l14_cmd;lm_uint32_t lo_value;lm_uint32_t l482_chksum;};l19_extern
le_struct l1020_dev_info{la_int lv_len;ll_uint8_t ln_data[256];}
l233_g_dev_info;l19_extern le_struct l1014_conn_history_info{la_int
l668_is_sent;la_int l470_list_size;le_struct l871_conn_history{la_int
lv_len;lm_uint32_t l317_time;ll_uint8_t ln_data[16];}lz_list[5];}
l159_g_conn_history_info;l19_extern le_struct l914_latency_test_info{
la_int l507_is_testing;la_int l651_test_cnt;l17_int64_t
l463_start_time_usec;l17_int64_t l509_end_time_usec;lm_uint32_t
l360_requester;lm_uint32_t l275_fail_cnt;}l106_g_latency_test_info;
la_int l841_parse_remote_msg(le_struct l355_remote_msg* *l838_pp_msg,
lb_void*ln_data,la_int lv_len,l32_int32_t l477_now);la_int
l792_pack_remote_msg(lb_void*l39_msg,li_const lb_void*ln_data,la_int
lv_len);la_int l862_pack_conn_history_info(ll_uint8_t*ln_data);la_int
l891_pack_latency_test_info(ll_uint8_t*ln_data);
#include"unmobric.h"
#include<sys/time.h>
#include"mobric.h"
lb_void l484_randomize(lb_void);la_int l386_get_random(lb_void);
lb_void l731_load_random_list(la_int lz_list[],la_int*l35_p_cnt,
la_int l628_base,la_int l339_range);l17_int64_t
l723_get_usec_from_timeval(li_const le_struct l146_timeval*
l283_p_timeval);lb_void l557_get_timeval_from_usec(le_struct
l146_timeval*l283_p_timeval,l17_int64_t l544_usec);l17_int64_t
l344_get_time_now_usec(lb_void);
#include"unmobric.h"
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
#include"unmobric.h"
#include"log.h"
#include"mobric.h"
l24_typedef l36_unsigned lj_char l115_md5_byte_t;l24_typedef
l36_unsigned la_int l34_md5_word_t;l24_typedef le_struct
l1114_md5_state_s{l34_md5_word_t l58_count[2];l34_md5_word_t l229_abcd
[4];l115_md5_byte_t l72_buf[64];}l249_md5_state_t;
#ifdef __cplusplus
l19_extern"\x43"{
#endif
lb_void l631_md5_init(l249_md5_state_t*l66_pms);lb_void
l407_md5_append(l249_md5_state_t*l66_pms,li_const l115_md5_byte_t*
ln_data,la_int l383_nbytes);lb_void l680_md5_finish(l249_md5_state_t*
l66_pms,l115_md5_byte_t l261_digest[16]);
#ifdef __cplusplus
}
#endif
lb_void l584_load_cfg_str(li_const lj_char*l113_s,li_const lj_char*
l402_delim);la_int l546_load_cfg_file(li_const lj_char*l230_path);
l19_extern le_struct l375_cfg{lj_char l441_server_prefix[16];lj_char
l314_server_suffix[16];lj_char l399_server_domain_name[64];lj_char
l328_server_ip_addr[40];la_int l438_server_port;la_int
l447_server_port_range;la_int l315_max_dns_query;la_int
l391_max_handshake;la_int l329_max_latency;la_int
l437_remote_msg_timeout;la_int l338_op_mode;la_int l108_idle_threshold
;la_int l449_dev_info_report_interval;}l20_g_cfg;l13_enum{
l53_ERR_LV_DBG,l535_ERR_LV_INFO,l234_ERR_LV_WARN,l69_ERR_LV_ERR};
l13_enum{l37_ERR_CAT_GENERAL,l347_ERR_CAT_DAEMON,l575_ERR_CAT_DPM_CFG
,l87_ERR_CAT_MSG,l495_ERR_CAT_NET};
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
le_struct l1020_dev_info l233_g_dev_info;le_struct
l1014_conn_history_info l159_g_conn_history_info;le_struct
l914_latency_test_info l106_g_latency_test_info;lk_static la_int
l957_scrmb_data(ll_uint8_t*l580_dst_buf,ll_uint8_t*l960_src_buf,
la_int l767_src_len);lk_static ll_uint8_t*l982_descrmb_data(
ll_uint8_t*l72_buf,la_int*l688_p_len);lk_static la_int l957_scrmb_data
(ll_uint8_t*l580_dst_buf,ll_uint8_t*l960_src_buf,la_int l767_src_len){
la_int ld_i;ll_uint8_t l656_rand_buf[8];la_int l242_rand_len;la_int
l369_xor_index;la_int l823_dst_len;l484_randomize();l242_rand_len=
l386_get_random()%8+1;l21_for(ld_i=0;ld_i<l242_rand_len;ld_i++){
l656_rand_buf[ld_i]=(ll_uint8_t)(l386_get_random()%256);}
l369_xor_index=l386_get_random()%l242_rand_len;l191_LOGG_DBG("\x52"
"\x61\x6e\x64\x6f\x6d\x20\x61\x72\x72\x61\x79\x20\x6c\x65\x6e\x67\x74"
"\x68\x3a\x20\x25\x64\x2c\x20\x58\x4f\x52\x20\x62\x79\x74\x65\x20\x69"
"\x6e\x64\x65\x78\x3a\x20\x25\x64\x2c\x20\x58\x4f\x52\x20\x62\x79\x74"
"\x65\x3a\x20\x25\x64",l242_rand_len,l369_xor_index,l656_rand_buf[
l369_xor_index]);l580_dst_buf[0]=(ll_uint8_t)((l242_rand_len<<4)|
l369_xor_index);_mb000010004(&l580_dst_buf[1],l656_rand_buf,
l242_rand_len);_mb000010004(&l580_dst_buf[1+l242_rand_len],
l960_src_buf,l767_src_len);l823_dst_len=1+l242_rand_len+l767_src_len;
l21_for(ld_i=1+l242_rand_len;ld_i<l823_dst_len;ld_i++){l580_dst_buf[
ld_i]^=l656_rand_buf[l369_xor_index];}lq_return l823_dst_len;}
lk_static ll_uint8_t*l982_descrmb_data(ll_uint8_t*l72_buf,la_int*
l688_p_len){la_int l242_rand_len=0;la_int l369_xor_index=0;ll_uint8_t
l985_operand=0;la_int ld_i=0;la_int l326_offset=0;lf_if(l72_buf==
lu_NULL||l688_p_len==lu_NULL){lq_return lu_NULL;}l242_rand_len=
l72_buf[0]>>4;l369_xor_index=l72_buf[0]&0xf;l985_operand=l72_buf[1+
l369_xor_index];l326_offset=1+l242_rand_len;l21_for(ld_i=l326_offset;
ld_i< *l688_p_len;ld_i++){l72_buf[ld_i-l326_offset]=l72_buf[ld_i]^
l985_operand;} *l688_p_len-=1+l242_rand_len;lq_return&l72_buf[0];}
la_int l841_parse_remote_msg(le_struct l355_remote_msg* *l838_pp_msg,
lb_void*ln_data,la_int lv_len,l32_int32_t l477_now){le_struct
l355_remote_msg*l38_p_msg;li_const lj_char*l570_private_key;
l249_md5_state_t l65_state;l115_md5_byte_t l261_digest[16];l38_p_msg=
(le_struct l355_remote_msg* )l982_descrmb_data((ll_uint8_t* )ln_data,
&lv_len);lf_if(lv_len!=lw_sizeof(le_struct l355_remote_msg)){
l64_LOGG_ERR("\x52\x65\x6d\x6f\x74\x65\x20\x6d\x65\x73\x73\x61\x67"
"\x65\x20\x6c\x65\x6e\x67\x74\x68\x20\x69\x73\x20\x25\x64\x2c\x20\x73"
"\x68\x6f\x75\x6c\x64\x20\x62\x65\x20\x25\x75",lv_len,(lm_uint32_t)lw_sizeof
(le_struct l355_remote_msg));lq_return((1<<31)|(l69_ERR_LV_ERR<<28)|(
l87_ERR_CAT_MSG<<14)|0x04);}l38_p_msg->l319_timestamp^=l38_p_msg->
l482_chksum;l38_p_msg->l14_cmd^=l38_p_msg->l482_chksum;l38_p_msg->
lo_value^=l38_p_msg->l482_chksum;l570_private_key="\x4e\x45\x49\x4c";
l631_md5_init(&l65_state);l407_md5_append(&l65_state,(li_const
l115_md5_byte_t* )l570_private_key,4);l407_md5_append(&l65_state,(
li_const l115_md5_byte_t* )l38_p_msg,12);l680_md5_finish(&l65_state,
l261_digest);l191_LOGG_DBG("\x54\x69\x6d\x65\x73\x74\x61\x6d\x70\x20"
"\x3a\x20\x30\x78\x25\x30\x38\x58",_mb000010002(l38_p_msg->
l319_timestamp));l191_LOGG_DBG("\x43\x6f\x6d\x6d\x61\x6e\x64\x20\x20"
"\x20\x3a\x20\x30\x78\x25\x30\x38\x58",_mb000010002(l38_p_msg->
l14_cmd));l191_LOGG_DBG("\x56\x61\x6c\x75\x65\x20\x20\x20\x20\x20\x3a"
"\x20\x30\x78\x25\x30\x38\x58",_mb000010002(l38_p_msg->lo_value));
l191_LOGG_DBG("\x43\x68\x65\x63\x6b\x73\x75\x6d\x20\x20\x3a\x20\x30"
"\x78\x25\x30\x38\x58",_mb000010002(l38_p_msg->l482_chksum));
l191_LOGG_DBG("\x44\x69\x67\x65\x73\x74\x20\x20\x20\x20\x3a\x20\x30"
"\x78\x25\x30\x32\x58\x25\x30\x32\x58\x25\x30\x32\x58\x25\x30\x32\x58"
,l261_digest[0],l261_digest[1],l261_digest[2],l261_digest[3]);lf_if(
l215_util_memcmp(l261_digest,&l38_p_msg->l482_chksum,4)){l64_LOGG_ERR
("\x52\x65\x6d\x6f\x74\x65\x20\x6d\x65\x73\x73\x61\x67\x65\x20\x63"
"\x68\x65\x63\x6b\x73\x75\x6d\x20\x65\x72\x72\x6f\x72");lq_return((1
<<31)|(l69_ERR_LV_ERR<<28)|(l87_ERR_CAT_MSG<<14)|0x13);}lf_if(
l477_now-(l32_int32_t)_mb000010002(l38_p_msg->l319_timestamp)>(
l32_int32_t)l20_g_cfg.l437_remote_msg_timeout){l492_LOGG_WARN("\x52"
"\x65\x6d\x6f\x74\x65\x20\x6d\x65\x73\x73\x61\x67\x65\x20\x74\x69\x6d"
"\x65\x6f\x75\x74");lq_return((1<<31)|(l69_ERR_LV_ERR<<28)|(
l87_ERR_CAT_MSG<<14)|0x12);}l38_p_msg->lo_value=_mb000010002(
l38_p_msg->lo_value); *l838_pp_msg=l38_p_msg;lq_return((0<<31)|(
l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00);}la_int
l792_pack_remote_msg(lb_void*l39_msg,li_const lb_void*ln_data,la_int
lv_len){li_const lj_char*l570_private_key;ll_uint8_t l519_data_ext[
512];la_int ld_i;l249_md5_state_t l65_state;l115_md5_byte_t
l261_digest[16];l570_private_key="\x52\x4e\x43\x45";_mb000010004(
l519_data_ext,l570_private_key,4);l484_randomize();l21_for(ld_i=4;
ld_i<8;ld_i++){l519_data_ext[ld_i]=(ll_uint8_t)(l386_get_random()%256
);}_mb000010004(l519_data_ext+8,ln_data,lv_len);l631_md5_init(&
l65_state);l407_md5_append(&l65_state,(li_const l115_md5_byte_t* )l519_data_ext
,8+lv_len);l680_md5_finish(&l65_state,l261_digest);_mb000010004(
l519_data_ext,l261_digest,4);lq_return l957_scrmb_data((ll_uint8_t* )l39_msg
,l519_data_ext,8+lv_len);}la_int l862_pack_conn_history_info(
ll_uint8_t*ln_data){ll_uint8_t*lc_p;la_int ld_i;lc_p=ln_data;{
l2_int8_t lg_src=0x00|l267_DINP_HDR_MASK_UID;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=0xC2;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{_mb000010004(lc_p,l233_g_dev_info.ln_data+2,8);lc_p+=8;};{l2_int8_t
lg_src=l159_g_conn_history_info.l470_list_size;_mb000010004((lb_void*
)lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};l21_for(ld_i=0;ld_i<
l159_g_conn_history_info.l470_list_size;ld_i++){{l32_int32_t lg_src=
l159_g_conn_history_info.lz_list[ld_i].l317_time;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;};{
_mb000010004(lc_p,l159_g_conn_history_info.lz_list[ld_i].ln_data,
l159_g_conn_history_info.lz_list[ld_i].lv_len);lc_p+=
l159_g_conn_history_info.lz_list[ld_i].lv_len;};}lq_return lc_p-
ln_data;}la_int l891_pack_latency_test_info(ll_uint8_t*ln_data){
ll_uint8_t*lc_p;lc_p=ln_data;{l2_int8_t lg_src=0x00;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t
lg_src=0xC1;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{l2_int8_t lg_src=l106_g_latency_test_info.
l651_test_cnt;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};ll_uint8_t l1071_empty_data=0;la_int ld_i=0;l21_for(
ld_i=0;ld_i<29;ld_i++){{l2_int8_t lg_src=l1071_empty_data;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
}lq_return lc_p-ln_data;}
