#include<stdint.h>
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
l624_dev_allow_web_access_from_wan(la_int l403_sec);l24_typedef
le_struct{lt_uint64_t l44_uid;lj_char l284_vendor[32+1];lj_char
l289_model[32+1];lj_char l490_fw_ver[32+1];lj_char l286_sn[32+1];
lj_char l468_chip_rev[32+1];la_int l673_cpu_core_cnt;la_int
l755_cpu_clk;la_int l687_mem_cap;la_int l758_flash_cap;la_int
l747_batt_cap;la_int l555_usb_dev_cnt;la_int l837_usb_devs[4];la_int
l525_nif_cnt;le_struct l151_nif l236_nifs[4];}l549_dev_data_set;
l24_typedef l13_enum{l1001_RUN_FTP_AUTO_FIRMWARE_UPGRADE=0,
l1000_ALLOW_WEB_ACCESS_FROM_WAN}l1104_dev_external_cmd_type;
l19_extern l549_dev_data_set*l26_gp_dev_data_set;la_int
l807_dev_pack_info(ll_uint8_t ln_data[]);la_int l771_dev_pack_report(
ll_uint8_t ln_data[]);
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
l549_dev_data_set*l26_gp_dev_data_set;la_int l807_dev_pack_info(
ll_uint8_t ln_data[]){ll_uint8_t*lc_p;la_int ld_i;lc_p=ln_data;{
l32_int32_t lg_src=_mb000010002(l105_IPC_MSG_SEND_REPORT);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;
};{l32_int32_t lg_src=_mb000010002(l116_IPC_DC_DEV);_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;};{l2_int8_t
lg_src=(l116_IPC_DC_DEV&0x3F)|l267_DINP_HDR_MASK_UID;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t
lg_src=0x01;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{l17_int64_t lg_src=_mb000010003(l26_gp_dev_data_set->
l44_uid);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),64/8);lc_p
+=(64)/8;};{la_int l55__len=_mb000010006(l26_gp_dev_data_set->
l284_vendor);{l2_int8_t lg_src=l55__len?l55__len:-1;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{_mb000010004(
lc_p,l26_gp_dev_data_set->l284_vendor,l55__len);lc_p+=l55__len;};};{
la_int l55__len=_mb000010006(l26_gp_dev_data_set->l289_model);{
l2_int8_t lg_src=l55__len?l55__len:-1;_mb000010004((lb_void* )lc_p,(
lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{_mb000010004(lc_p,
l26_gp_dev_data_set->l289_model,l55__len);lc_p+=l55__len;};};{la_int
l55__len=_mb000010006(l26_gp_dev_data_set->l490_fw_ver);{l2_int8_t
lg_src=l55__len?l55__len:-1;_mb000010004((lb_void* )lc_p,(lb_void* )(
&lg_src),8/8);lc_p+=(8)/8;};{_mb000010004(lc_p,l26_gp_dev_data_set->
l490_fw_ver,l55__len);lc_p+=l55__len;};};{la_int l55__len=
_mb000010006(l26_gp_dev_data_set->l286_sn);{l2_int8_t lg_src=l55__len
?l55__len:-1;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{_mb000010004(lc_p,l26_gp_dev_data_set->l286_sn,
l55__len);lc_p+=l55__len;};};{la_int l55__len=_mb000010006(
l26_gp_dev_data_set->l468_chip_rev);{l2_int8_t lg_src=l55__len?
l55__len:-1;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{_mb000010004(lc_p,l26_gp_dev_data_set->l468_chip_rev,
l55__len);lc_p+=l55__len;};};{l2_int8_t lg_src=l26_gp_dev_data_set->
l673_cpu_core_cnt;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8
/8);lc_p+=(8)/8;};{l47_int16_t lg_src=_mb000010005((l25_uint16_t)l26_gp_dev_data_set
->l755_cpu_clk);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/
8);lc_p+=(16)/8;};{l47_int16_t lg_src=_mb000010005((l25_uint16_t)l26_gp_dev_data_set
->l687_mem_cap);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/
8);lc_p+=(16)/8;};{l47_int16_t lg_src=_mb000010005((l25_uint16_t)l26_gp_dev_data_set
->l758_flash_cap);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),
16/8);lc_p+=(16)/8;};{l47_int16_t lg_src=_mb000010005((l25_uint16_t)l26_gp_dev_data_set
->l747_batt_cap);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16
/8);lc_p+=(16)/8;};{l2_int8_t lg_src=l26_gp_dev_data_set->
l555_usb_dev_cnt;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/
8);lc_p+=(8)/8;};l21_for(ld_i=0;ld_i<l26_gp_dev_data_set->
l555_usb_dev_cnt;ld_i++){{l2_int8_t lg_src=l26_gp_dev_data_set->
l837_usb_devs[ld_i];_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),
8/8);lc_p+=(8)/8;};}{l2_int8_t lg_src=l26_gp_dev_data_set->
l525_nif_cnt;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};l21_for(ld_i=0;ld_i<l26_gp_dev_data_set->l525_nif_cnt;
ld_i++){{l2_int8_t lg_src=l26_gp_dev_data_set->l236_nifs[ld_i].
l9_type;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=
(8)/8;};{_mb000010004(lc_p,l26_gp_dev_data_set->l236_nifs[ld_i].
l432_mac_addr,lw_sizeof(((le_struct l151_nif* )lu_NULL)->
l432_mac_addr));lc_p+=lw_sizeof(((le_struct l151_nif* )lu_NULL)->
l432_mac_addr);};l107_switch(l26_gp_dev_data_set->l236_nifs[ld_i].
l9_type){l7_case 0x10:l7_case 0x50:l7_case 0x70:ly_break;l238_default
:{l17_int64_t lg_src=_mb000010003(l26_gp_dev_data_set->l236_nifs[ld_i
].l556_imsi);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),64/8);
lc_p+=(64)/8;};{l17_int64_t lg_src=_mb000010003(l26_gp_dev_data_set->
l236_nifs[ld_i].l596_imei);_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),64/8);lc_p+=(64)/8;};ly_break;}}lq_return lc_p-ln_data;}
la_int l771_dev_pack_report(ll_uint8_t ln_data[]){ll_uint8_t*lc_p=
ln_data;{l32_int32_t lg_src=_mb000010002(l207_IPC_MSG_SET_DEVICE_INFO
);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/
8;};{l32_int32_t lg_src=_mb000010002(l116_IPC_DC_DEV);_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;};{l17_int64_t
lg_src=_mb000010003(l26_gp_dev_data_set->l44_uid);_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),64/8);lc_p+=(64)/8;};lq_return
lc_p-ln_data;}
