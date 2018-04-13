#include<stdint.h>
#include<float.h>
#include"mobric.h"
l24_typedef le_struct l877__lte_cell_info{l32_int32_t l102_cell_id;
l32_int32_t l138_mcc;ll_uint8_t l112_mnc[4];l32_int32_t l143_lac;
l32_int32_t l57_rssi;l32_int32_t l77_rsrp;l239_float l79_rsrq;}
l335_lte_cell_info;la_int l725_lte_get_supported_freq_band(l4_long
l4_long*lo_value);la_int l717_lte_get_ip_address(lj_char l420_buff[16
]);la_int l660_lte_get_network_entry_latency(la_int*lo_value);la_int
l742_lte_get_cell_id(la_int*lo_value);la_int l662_lte_get_rssi(la_int
 *lo_value);la_int l665_lte_get_rsrp(la_int*lo_value);la_int
l666_lte_get_rsrq(l239_float*lo_value);la_int l653_lte_get_cqi(la_int
 *lo_value);la_int l728_lte_get_ul_earfcn(la_int*lo_value);la_int
l704_lte_get_dl_earfcn(la_int*lo_value);la_int l685_lte_get_channel_bw
(la_int*lo_value);la_int l633_lte_get_mcc(la_int*lo_value);la_int
l732_lte_get_mnc(lj_char l420_buff[4]);la_int l664_lte_get_lac(la_int
 *lo_value);la_int l663_lte_get_handover_latency(la_int*lo_value);
la_int l689_lte_get_handover_success_count(la_int*lo_value);la_int
l678_lte_get_handover_failure_count(la_int*lo_value);la_int
l634_lte_get_ul_mcs(la_int*lo_value);la_int l729_lte_get_dl_mcs(
la_int*lo_value);la_int l737_lte_get_tx_power(la_int*lo_value);la_int
l530_lte_get_tx_byte(l36_unsigned l4_long l4_long*lo_value);la_int
l536_lte_get_rx_byte(l36_unsigned l4_long l4_long*lo_value);la_int
l654_lte_get_tx_packet_count(l36_unsigned l4_long l4_long*lo_value);
la_int l740_lte_get_rx_packet_count(l36_unsigned l4_long l4_long*
lo_value);la_int l750_lte_get_tx_packet_error_count(l36_unsigned
l4_long l4_long*lo_value);la_int l762_lte_get_rx_packet_error_count(
l36_unsigned l4_long l4_long*lo_value);la_int
l686_lte_get_tx_frame_count(l36_unsigned l4_long l4_long*lo_value);
la_int l760_lte_get_rx_frame_count(l36_unsigned l4_long l4_long*
lo_value);la_int l677_lte_get_tx_frame_error_count(l36_unsigned
l4_long l4_long*lo_value);la_int l756_lte_get_rx_frame_error_count(
l36_unsigned l4_long l4_long*lo_value);la_int
l733_lte_get_disconnect_reason(la_int*lo_value);la_int
l763_lte_get_neighboring_cell_info(la_int*l58_count,
l335_lte_cell_info lz_list[16]);la_int
l675_lte_get_ul_bearer_flow_max_speed(la_int*lo_value);la_int
l757_lte_get_dl_bearer_flow_max_speed(la_int*lo_value);la_int
l694_lte_get_scc_aggregated_count(ll_uint8_t*lo_value);la_int
l693_lte_get_scc_cell_id(la_int lo_value[5]);la_int
l648_lte_get_scc_channel_bw(la_int lo_value[5]);la_int
l714_lte_get_scc_rsrp(la_int lo_value[5]);la_int l713_lte_get_scc_rsrq
(l239_float lo_value[5]);la_int l745_lte_get_scc_dl_earfcn(la_int
lo_value[5]);
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
l117_digits);l13_enum{l22_PREV,l1_CURR};l13_enum{
l730_REPORT_INTERVAL_INDICATOR_NONE,
l702_REPORT_INTERVAL_INDICATOR_RSSI,
l706_REPORT_INTERVAL_INDICATOR_RSRP,
l705_REPORT_INTERVAL_INDICATOR_RSRQ,
l718_REPORT_INTERVAL_INDICATOR_CQI};l13_enum{l439_MOD_QPSK,
l413_MOD_16QAM,l406_MOD_64QAM};l13_enum{l415_STAT_CPU_USAGE,
l410_STAT_MEM_USAGE,l674_STAT_TEMP,l640_STAT_BATT_TEMP};le_struct
l51_ip_info{la_int lv_len;lj_char l74_ip_addr[40];ll_uint8_t l29_addr
[16];};le_struct l443_ngbr_cell{la_int l102_cell_id;la_int l138_mcc;
lj_char l112_mnc[4];la_int l143_lac;la_int l57_rssi;la_int l77_rsrp;
la_int l79_rsrq;};l24_typedef le_struct{la_int l804_report_interval;
la_int l218_routine_cnt;la_int l464_activated_time;la_int
l198_idle_count;lt_uint64_t l44_uid;lt_uint64_t l348_freq_bitmap;
le_struct l51_ip_info l51_ip_info[2];la_int l395_net_entry_latency;
la_int l102_cell_id[2];la_int l475_ul_max_bearer_speed;la_int
l505_dl_max_bearer_speed;la_int l300_rssi_cnt;la_int l57_rssi[240];
la_int l527_rssi_max;la_int l562_rssi_min;la_int l478_rssi_mean;
lr_double l564_rssi_std_dev_plus;lr_double l552_rssi_std_dev_minus;
la_int l336_rsrp_cnt;la_int l77_rsrp[240];la_int l521_rsrp_max;la_int
l618_rsrp_min;la_int l471_rsrp_mean;lr_double l563_rsrp_std_dev_plus;
lr_double l542_rsrp_std_dev_minus;la_int l340_rsrq_cnt;la_int l79_rsrq
[240];la_int l573_rsrq_max;la_int l578_rsrq_min;la_int l497_rsrq_mean
;lr_double l613_rsrq_std_dev_plus;lr_double l608_rsrq_std_dev_minus;
la_int l363_cqi_cnt;la_int l205_cqi[240];la_int l588_cqi_max;la_int
l593_cqi_min;la_int l466_cqi_mean;lr_double l577_cqi_std_dev_plus;
lr_double l559_cqi_std_dev_minus;la_int l502_ul_earfcn;la_int
l517_dl_earfcn;la_int l512_ch_bw;la_int l138_mcc;lj_char l112_mnc[4];
la_int l143_lac;la_int l397_handover_event_supportness;la_int
l434_handover_event_success_cnt;la_int l431_handover_event_fail_cnt;
la_int l401_handover_latency_cnt;la_int l372_handover_latency[240];
la_int l605_handover_latency_mean;la_int l514_handover_detected_cnt;
la_int l278_handover_success_cnt[2];la_int l281_handover_fail_cnt[2];
la_int l345_ul_mod_cnt[3];la_int l357_dl_mod_cnt[3];la_int
l251_tx_power;lt_uint64_t l84_tx_byte[2];lt_uint64_t l83_rx_byte[2];
la_int l165_ul_rate_cnt;la_int l237_ul_rate[240];la_int
l307_ul_rate_max;la_int l304_ul_rate_min;la_int l302_ul_rate_mean;
lr_double l308_ul_rate_std_dev_plus;lr_double
l309_ul_rate_std_dev_minus;la_int l157_dl_rate_cnt;la_int l263_dl_rate
[240];la_int l305_dl_rate_max;la_int l297_dl_rate_min;la_int
l285_dl_rate_mean;lr_double l310_dl_rate_std_dev_plus;lr_double
l301_dl_rate_std_dev_minus;lt_uint64_t l295_tx_packet_cnt[2];
lt_uint64_t l299_rx_packet_cnt[2];lt_uint64_t l387_tx_packet_err_cnt[
2];lt_uint64_t l368_rx_packet_err_cnt[2];lt_uint64_t l271_tx_frame_cnt
[2];lt_uint64_t l272_rx_frame_cnt[2];lt_uint64_t l404_tx_frame_err_cnt
[2];lt_uint64_t l476_rx_frame_err_cnt[2];la_int l465_disconnect_reason
;la_int l268_ngbr_cell_cnt[2];le_struct l443_ngbr_cell l91_ngbr_cells
[2][16];la_int l173_temp;la_int l380_batt_temp;la_int
l516_cpu_usage_cnt;la_int l353_cpu_usage[240];la_int
l528_cpu_usage_mean;la_int l501_mem_usage_cnt;la_int l327_mem_usage[
240];la_int l592_mem_usage_mean;la_int l458_batt_lv;ll_uint8_t
l270_scc_count;la_int l488_scc_cell_id[5];la_int l459_scc_ch_bw[5];
lr_double l857_scc_rssi_std_dev_plus[5];lr_double
l802_scc_rssi_std_dev_minus[5];la_int l393_scc_rsrp_cnt;la_int
l493_scc_rsrp[5][240];la_int l601_scc_rsrp_max[5];la_int
l579_scc_rsrp_min[5];la_int l566_scc_rsrp_mean[5];lr_double
l486_scc_rsrp_std_dev_plus[5];lr_double l491_scc_rsrp_std_dev_minus[5
];la_int l394_scc_rsrq_cnt;la_int l489_scc_rsrq[5][240];la_int
l591_scc_rsrq_max[5];la_int l567_scc_rsrq_min[5];la_int
l607_scc_rsrq_mean[5];lr_double l479_scc_rsrq_std_dev_plus[5];
lr_double l480_scc_rsrq_std_dev_minus[5];la_int l510_scc_dl_earfcn[5]
;}l323_lte_data_set;l19_extern l323_lte_data_set*lh_gp_lte_data_set;
l24_typedef le_struct{la_int l235_indicator;la_int l108_idle_threshold
;la_int l231_threshold_cnt;la_int l422_thresholds[8-1];la_int
l241_report_intervals[8];}l312_lte_cfg;l19_extern l312_lte_cfg*
l71_gp_lte_cfg;la_int l603_lte_pack_conn_history_info(ll_uint8_t*
ln_data,lb_void*l41_arg);la_int l565_pack_dev_info(ll_uint8_t*ln_data
,lb_void*l41_arg);la_int l551_pack_net_entry_info(ll_uint8_t*ln_data,
lb_void*l41_arg);la_int l612_pack_alert_info(ll_uint8_t*ln_data,
lb_void*l41_arg);la_int l615_pack_handover_info(ll_uint8_t*ln_data,
lb_void*l41_arg);la_int l609_pack_ip_change_info(ll_uint8_t*ln_data,
lb_void*l41_arg);la_int l550_pack_perf_info(ll_uint8_t*ln_data,
lb_void*l41_arg);
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
l323_lte_data_set*lh_gp_lte_data_set;l312_lte_cfg*l71_gp_lte_cfg;
l19_extern lm_uint32_t _mb000000003[5];l19_extern lm_uint32_t
_mb000000004;l19_extern la_int _mb000000002;la_int
l603_lte_pack_conn_history_info(ll_uint8_t*ln_data,lb_void*l41_arg){
ll_uint8_t*lc_p;lc_p=ln_data;{l32_int32_t lg_src=_mb000010002(
l178_IPC_MSG_SEND_CONN_HISTORY_INFO);_mb000010004((lb_void* )lc_p,(
lb_void* )(&lg_src),32/8);lc_p+=(32)/8;};{l32_int32_t lg_src=
_mb000010002(l73_IPC_DC_LTE);_mb000010004((lb_void* )lc_p,(lb_void* )(
&lg_src),32/8);lc_p+=(32)/8;};{l2_int8_t lg_src=(l73_IPC_DC_LTE&0x3F);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{l2_int8_t lg_src=0x02;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),8/8);lc_p+=(8)/8;};lf_if(lh_gp_lte_data_set->l300_rssi_cnt==0
){{l2_int8_t lg_src=127;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),8/8);lc_p+=(8)/8;};}l3_else{{l2_int8_t lg_src=
lh_gp_lte_data_set->l57_rssi[0];_mb000010004((lb_void* )lc_p,(lb_void
 * )(&lg_src),8/8);lc_p+=(8)/8;};}lf_if(lh_gp_lte_data_set->
l336_rsrp_cnt==0){{l2_int8_t lg_src=127;_mb000010004((lb_void* )lc_p,
(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};}l3_else{{l2_int8_t lg_src=
lh_gp_lte_data_set->l77_rsrp[0];_mb000010004((lb_void* )lc_p,(lb_void
 * )(&lg_src),8/8);lc_p+=(8)/8;};}lf_if(lh_gp_lte_data_set->
l340_rsrq_cnt==0){{l2_int8_t lg_src=127;_mb000010004((lb_void* )lc_p,
(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};}l3_else{{l2_int8_t lg_src=
lh_gp_lte_data_set->l79_rsrq[0];_mb000010004((lb_void* )lc_p,(lb_void
 * )(&lg_src),8/8);lc_p+=(8)/8;};}lq_return lc_p-ln_data;}la_int
l565_pack_dev_info(ll_uint8_t*ln_data,lb_void*l41_arg){ll_uint8_t*
lc_p;lt_uint64_t l993_freq_bitmap_be;lc_p=ln_data;{l32_int32_t lg_src
=_mb000010002(l105_IPC_MSG_SEND_REPORT);_mb000010004((lb_void* )lc_p,
(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;};{l32_int32_t lg_src=
_mb000010002(l73_IPC_DC_LTE);_mb000010004((lb_void* )lc_p,(lb_void* )(
&lg_src),32/8);lc_p+=(32)/8;};{l2_int8_t lg_src=(l73_IPC_DC_LTE&0x3F)|
l267_DINP_HDR_MASK_UID;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=0x01;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l17_int64_t
lg_src=_mb000010003(lh_gp_lte_data_set->l44_uid);_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),64/8);lc_p+=(64)/8;};
l993_freq_bitmap_be=_mb000010003(lh_gp_lte_data_set->l348_freq_bitmap
);{_mb000010004(lc_p,((ll_uint8_t* )&l993_freq_bitmap_be)+2,6);lc_p+=
6;};lq_return lc_p-ln_data;}la_int l551_pack_net_entry_info(
ll_uint8_t*ln_data,lb_void*l41_arg){ll_uint8_t*lc_p;la_int l81_role;
la_int ld_i;lc_p=ln_data;{l32_int32_t lg_src=_mb000010002(
l105_IPC_MSG_SEND_REPORT);_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),32/8);lc_p+=(32)/8;};{l32_int32_t lg_src=_mb000010002(
l73_IPC_DC_LTE);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/
8);lc_p+=(32)/8;};l81_role=(l73_IPC_DC_LTE&0x3F)|
l267_DINP_HDR_MASK_UID;{l2_int8_t lg_src=l81_role;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t
lg_src=0x03;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{l17_int64_t lg_src=_mb000010003(lh_gp_lte_data_set->
l44_uid);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),64/8);lc_p
+=(64)/8;};{l2_int8_t lg_src=lh_gp_lte_data_set->l51_ip_info[l1_CURR]
.lv_len;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=
(8)/8;};lf_if(lh_gp_lte_data_set->l51_ip_info[l1_CURR].lv_len!=-1){{
_mb000010004(lc_p,lh_gp_lte_data_set->l51_ip_info[l1_CURR].l29_addr,
lh_gp_lte_data_set->l51_ip_info[l1_CURR].lv_len);lc_p+=
lh_gp_lte_data_set->l51_ip_info[l1_CURR].lv_len;};}{l32_int32_t lg_src
=_mb000010002((lm_uint32_t)lh_gp_lte_data_set->l102_cell_id[l1_CURR]);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;
};{l47_int16_t lg_src=_mb000010005((l25_uint16_t)lh_gp_lte_data_set->
l138_mcc);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);
lc_p+=(16)/8;};{la_int l55__len=_mb000010006((lj_char* )lh_gp_lte_data_set
->l112_mnc);{l2_int8_t lg_src=l55__len?l55__len:-1;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{_mb000010004(
lc_p,(lj_char* )lh_gp_lte_data_set->l112_mnc,l55__len);lc_p+=l55__len
;};};{l47_int16_t lg_src=_mb000010005((l25_uint16_t)lh_gp_lte_data_set
->l143_lac);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);
lc_p+=(16)/8;};{l47_int16_t lg_src=_mb000010005((l25_uint16_t)lh_gp_lte_data_set
->l395_net_entry_latency);_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),16/8);lc_p+=(16)/8;};{_mb000010004(lc_p,_mb000000003,
lw_sizeof(_mb000000003));lc_p+=lw_sizeof(_mb000000003);};{l2_int8_t
lg_src=lh_gp_lte_data_set->l465_disconnect_reason;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t
lg_src=lh_gp_lte_data_set->l268_ngbr_cell_cnt[l1_CURR];_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};l21_for(ld_i=0
;ld_i<lh_gp_lte_data_set->l268_ngbr_cell_cnt[l1_CURR];ld_i++){{
l32_int32_t lg_src=_mb000010002((lm_uint32_t)lh_gp_lte_data_set->
l91_ngbr_cells[l1_CURR][ld_i].l102_cell_id);_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;};{l47_int16_t lg_src=
_mb000010005((l25_uint16_t)lh_gp_lte_data_set->l91_ngbr_cells[l1_CURR
][ld_i].l138_mcc);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),
16/8);lc_p+=(16)/8;};{la_int l55__len=_mb000010006((lj_char* )lh_gp_lte_data_set
->l91_ngbr_cells[l1_CURR][ld_i].l112_mnc);{l2_int8_t lg_src=l55__len?
l55__len:-1;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{_mb000010004(lc_p,(lj_char* )lh_gp_lte_data_set->
l91_ngbr_cells[l1_CURR][ld_i].l112_mnc,l55__len);lc_p+=l55__len;};};{
l47_int16_t lg_src=_mb000010005((l25_uint16_t)lh_gp_lte_data_set->
l91_ngbr_cells[l1_CURR][ld_i].l143_lac);_mb000010004((lb_void* )lc_p,
(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};{l2_int8_t lg_src=
lh_gp_lte_data_set->l91_ngbr_cells[l1_CURR][ld_i].l57_rssi;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{l2_int8_t lg_src=lh_gp_lte_data_set->l91_ngbr_cells[l1_CURR][ld_i].
l77_rsrp;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p
+=(8)/8;};{l2_int8_t lg_src=lh_gp_lte_data_set->l91_ngbr_cells[
l1_CURR][ld_i].l79_rsrq;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),8/8);lc_p+=(8)/8;};}{l47_int16_t lg_src=_mb000010005((
l25_uint16_t)lh_gp_lte_data_set->l475_ul_max_bearer_speed);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;
};{l47_int16_t lg_src=_mb000010005((l25_uint16_t)lh_gp_lte_data_set->
l505_dl_max_bearer_speed);_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),16/8);lc_p+=(16)/8;};lq_return lc_p-ln_data;}la_int
l612_pack_alert_info(ll_uint8_t*ln_data,lb_void*l41_arg){ll_uint8_t*
lc_p;la_int l81_role;lc_p=ln_data;{l32_int32_t lg_src=_mb000010002(
l105_IPC_MSG_SEND_REPORT);_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),32/8);lc_p+=(32)/8;};{l32_int32_t lg_src=_mb000010002(
l73_IPC_DC_LTE);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/
8);lc_p+=(32)/8;};l81_role=(l73_IPC_DC_LTE&0x3F)|
l267_DINP_HDR_MASK_UID;{l2_int8_t lg_src=l81_role;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t
lg_src=0x04;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{l17_int64_t lg_src=_mb000010003(lh_gp_lte_data_set->
l44_uid);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),64/8);lc_p
+=(64)/8;};{la_int l638_stat_index;la_int l683_stat_and_lv;
l638_stat_index= * (la_int* )l41_arg;l683_stat_and_lv=l638_stat_index
<<6;l683_stat_and_lv|=(_mb000000001[l638_stat_index].l100_lv[l22_PREV
]+1)<<3;l683_stat_and_lv|=(_mb000000001[l638_stat_index].l100_lv[
l1_CURR]+1);{l2_int8_t lg_src=l683_stat_and_lv;_mb000010004((lb_void*
)lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};}{l2_int8_t lg_src=
_mb000000001[l415_STAT_CPU_USAGE].l59_max;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
_mb000000001[l415_STAT_CPU_USAGE].l60_min;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
_mb000000001[l415_STAT_CPU_USAGE].l45_mean;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
_mb000000001[l410_STAT_MEM_USAGE].l59_max;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
_mb000000001[l410_STAT_MEM_USAGE].l60_min;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
_mb000000001[l410_STAT_MEM_USAGE].l45_mean;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
lh_gp_lte_data_set->l173_temp;_mb000010004((lb_void* )lc_p,(lb_void* )(
&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=lh_gp_lte_data_set->
l380_batt_temp;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};lq_return lc_p-ln_data;}la_int l615_pack_handover_info(
ll_uint8_t*ln_data,lb_void*l41_arg){ll_uint8_t*lc_p;la_int l81_role;
la_int ld_i;lc_p=ln_data;{l32_int32_t lg_src=_mb000010002(
l105_IPC_MSG_SEND_REPORT);_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),32/8);lc_p+=(32)/8;};{l32_int32_t lg_src=_mb000010002(
l73_IPC_DC_LTE);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/
8);lc_p+=(32)/8;};l81_role=(l73_IPC_DC_LTE&0x3F)|
l267_DINP_HDR_MASK_UID;{l2_int8_t lg_src=l81_role;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t
lg_src=0x05;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{l17_int64_t lg_src=_mb000010003(lh_gp_lte_data_set->
l44_uid);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),64/8);lc_p
+=(64)/8;};{l32_int32_t lg_src=_mb000010002((lm_uint32_t)lh_gp_lte_data_set
->l102_cell_id[l22_PREV]);_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),32/8);lc_p+=(32)/8;};lf_if(lh_gp_lte_data_set->l300_rssi_cnt
<=1){{l2_int8_t lg_src=127;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),8/8);lc_p+=(8)/8;};}l3_else{{l2_int8_t lg_src=
lh_gp_lte_data_set->l57_rssi[lh_gp_lte_data_set->l300_rssi_cnt-2];
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
}{l2_int8_t lg_src=lh_gp_lte_data_set->l268_ngbr_cell_cnt[l22_PREV];
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
l21_for(ld_i=0;ld_i<lh_gp_lte_data_set->l268_ngbr_cell_cnt[l22_PREV];
ld_i++){{l32_int32_t lg_src=_mb000010005((lm_uint32_t)lh_gp_lte_data_set
->l91_ngbr_cells[l22_PREV][ld_i].l102_cell_id);_mb000010004((lb_void*
)lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;};{l47_int16_t lg_src=
_mb000010005((l25_uint16_t)lh_gp_lte_data_set->l91_ngbr_cells[
l22_PREV][ld_i].l138_mcc);_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),16/8);lc_p+=(16)/8;};{la_int l55__len=_mb000010006((lj_char* )lh_gp_lte_data_set
->l91_ngbr_cells[l22_PREV][ld_i].l112_mnc);{l2_int8_t lg_src=l55__len
?l55__len:-1;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{_mb000010004(lc_p,(lj_char* )lh_gp_lte_data_set->
l91_ngbr_cells[l22_PREV][ld_i].l112_mnc,l55__len);lc_p+=l55__len;};};
{l47_int16_t lg_src=_mb000010005((l25_uint16_t)lh_gp_lte_data_set->
l91_ngbr_cells[l22_PREV][ld_i].l143_lac);_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};{l2_int8_t lg_src=
lh_gp_lte_data_set->l91_ngbr_cells[l22_PREV][ld_i].l57_rssi;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{l2_int8_t lg_src=lh_gp_lte_data_set->l91_ngbr_cells[l22_PREV][ld_i].
l77_rsrp;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p
+=(8)/8;};{l2_int8_t lg_src=lh_gp_lte_data_set->l91_ngbr_cells[
l22_PREV][ld_i].l79_rsrq;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),8/8);lc_p+=(8)/8;};}{l32_int32_t lg_src=_mb000010002((
lm_uint32_t)lh_gp_lte_data_set->l102_cell_id[l1_CURR]);_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;};lq_return
lc_p-ln_data;}la_int l609_pack_ip_change_info(ll_uint8_t*ln_data,
lb_void*l41_arg){ll_uint8_t*lc_p;la_int l81_role;la_int ld_i;lc_p=
ln_data;{l32_int32_t lg_src=_mb000010002(l105_IPC_MSG_SEND_REPORT);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;
};{l32_int32_t lg_src=_mb000010002(l73_IPC_DC_LTE);_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;};l81_role=(
l73_IPC_DC_LTE&0x3F)|l267_DINP_HDR_MASK_UID;{l2_int8_t lg_src=
l81_role;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p
+=(8)/8;};{l2_int8_t lg_src=0x06;_mb000010004((lb_void* )lc_p,(
lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l17_int64_t lg_src=
_mb000010003(lh_gp_lte_data_set->l44_uid);_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),64/8);lc_p+=(64)/8;};l21_for(ld_i=l22_PREV;ld_i
<=l1_CURR;ld_i++){{l2_int8_t lg_src=lh_gp_lte_data_set->l51_ip_info[
ld_i].lv_len;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};lf_if(lh_gp_lte_data_set->l51_ip_info[ld_i].lv_len!=-1){
{_mb000010004(lc_p,lh_gp_lte_data_set->l51_ip_info[ld_i].l29_addr,
lh_gp_lte_data_set->l51_ip_info[ld_i].lv_len);lc_p+=
lh_gp_lte_data_set->l51_ip_info[ld_i].lv_len;};}}lq_return lc_p-
ln_data;}la_int l550_pack_perf_info(ll_uint8_t*ln_data,lb_void*
l41_arg){ll_uint8_t*lc_p;la_int l81_role;la_int ld_i;lc_p=ln_data;{
l32_int32_t lg_src=_mb000010002(l105_IPC_MSG_SEND_REPORT);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;
};{l32_int32_t lg_src=_mb000010002(l73_IPC_DC_LTE);_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;};l81_role=(
l73_IPC_DC_LTE&0x3F)|l267_DINP_HDR_MASK_UID;{l2_int8_t lg_src=
l81_role;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p
+=(8)/8;};{l2_int8_t lg_src=0x07;_mb000010004((lb_void* )lc_p,(
lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l17_int64_t lg_src=
_mb000010003(lh_gp_lte_data_set->l44_uid);_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),64/8);lc_p+=(64)/8;};{l2_int8_t lg_src=
lh_gp_lte_data_set->l51_ip_info[l1_CURR].lv_len;_mb000010004((lb_void
 * )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};lf_if(
lh_gp_lte_data_set->l51_ip_info[l1_CURR].lv_len!=-1){{_mb000010004(
lc_p,lh_gp_lte_data_set->l51_ip_info[l1_CURR].l29_addr,
lh_gp_lte_data_set->l51_ip_info[l1_CURR].lv_len);lc_p+=
lh_gp_lte_data_set->l51_ip_info[l1_CURR].lv_len;};}{l32_int32_t lg_src
=_mb000010002((lm_uint32_t)lh_gp_lte_data_set->l102_cell_id[l1_CURR]);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;
};{l32_int32_t lg_src=_mb000010002((lm_uint32_t)lh_gp_lte_data_set->
l502_ul_earfcn);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/
8);lc_p+=(32)/8;};{l32_int32_t lg_src=_mb000010002((lm_uint32_t)lh_gp_lte_data_set
->l517_dl_earfcn);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),
32/8);lc_p+=(32)/8;};{l2_int8_t lg_src=lh_gp_lte_data_set->l512_ch_bw
;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;}
;{le_struct{la_int l59_max;la_int l60_min;la_int l45_mean;lr_double
l120_std_dev_plus;lr_double l121_std_dev_minus;}lz_list[]={{
lh_gp_lte_data_set->l527_rssi_max,lh_gp_lte_data_set->l562_rssi_min,
lh_gp_lte_data_set->l478_rssi_mean,lh_gp_lte_data_set->
l564_rssi_std_dev_plus,lh_gp_lte_data_set->l552_rssi_std_dev_minus},{
lh_gp_lte_data_set->l521_rsrp_max,lh_gp_lte_data_set->l618_rsrp_min,
lh_gp_lte_data_set->l471_rsrp_mean,lh_gp_lte_data_set->
l563_rsrp_std_dev_plus,lh_gp_lte_data_set->l542_rsrp_std_dev_minus},{
lh_gp_lte_data_set->l573_rsrq_max,lh_gp_lte_data_set->l578_rsrq_min,
lh_gp_lte_data_set->l497_rsrq_mean,lh_gp_lte_data_set->
l613_rsrq_std_dev_plus,lh_gp_lte_data_set->l608_rsrq_std_dev_minus},{
lh_gp_lte_data_set->l588_cqi_max,lh_gp_lte_data_set->l593_cqi_min,
lh_gp_lte_data_set->l466_cqi_mean,lh_gp_lte_data_set->
l577_cqi_std_dev_plus,lh_gp_lte_data_set->l559_cqi_std_dev_minus},};
l21_for(ld_i=0;ld_i<(lw_sizeof(lz_list)/lw_sizeof(lz_list[0]));ld_i++
){{l2_int8_t lg_src=lz_list[ld_i].l59_max;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=lz_list[
ld_i].l60_min;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{l2_int8_t lg_src=lz_list[ld_i].l45_mean;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};lf_if(lz_list[
ld_i].l121_std_dev_minus>=0){{l47_int16_t lg_src=_mb000010005((
l25_uint16_t)(lz_list[ld_i].l121_std_dev_minus*100.0));_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};}l3_else{{
l47_int16_t lg_src=-1;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),16/8);lc_p+=(16)/8;};}lf_if(lz_list[ld_i].l120_std_dev_plus>=
0){{l47_int16_t lg_src=_mb000010005((l25_uint16_t)(lz_list[ld_i].
l120_std_dev_plus*100.0));_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),16/8);lc_p+=(16)/8;};}l3_else{{l47_int16_t lg_src=-1;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;
};}}}{la_int*lz_list[]={lh_gp_lte_data_set->l345_ul_mod_cnt,
lh_gp_lte_data_set->l357_dl_mod_cnt};l21_for(ld_i=0;ld_i<(lw_sizeof(
lz_list)/lw_sizeof(lz_list[0]));ld_i++){lf_if(lz_list[ld_i][
l439_MOD_QPSK]==0&&lz_list[ld_i][l413_MOD_16QAM]==0&&lz_list[ld_i][
l406_MOD_64QAM]==0){{l2_int8_t lg_src=-1;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=-1;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{l2_int8_t lg_src=-1;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src
),8/8);lc_p+=(8)/8;};}l3_else{{l2_int8_t lg_src=lz_list[ld_i][
l439_MOD_QPSK];_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{l2_int8_t lg_src=lz_list[ld_i][l413_MOD_16QAM];
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{l2_int8_t lg_src=lz_list[ld_i][l406_MOD_64QAM];_mb000010004((lb_void
 * )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};}}}{le_struct{la_int
l59_max;la_int l60_min;la_int l45_mean;la_int l120_std_dev_plus;
la_int l121_std_dev_minus;}lz_list[]={{lh_gp_lte_data_set->
l307_ul_rate_max,lh_gp_lte_data_set->l304_ul_rate_min,
lh_gp_lte_data_set->l302_ul_rate_mean,lh_gp_lte_data_set->
l308_ul_rate_std_dev_plus,lh_gp_lte_data_set->
l309_ul_rate_std_dev_minus},{lh_gp_lte_data_set->l305_dl_rate_max,
lh_gp_lte_data_set->l297_dl_rate_min,lh_gp_lte_data_set->
l285_dl_rate_mean,lh_gp_lte_data_set->l310_dl_rate_std_dev_plus,
lh_gp_lte_data_set->l301_dl_rate_std_dev_minus},};l21_for(ld_i=0;ld_i
<(lw_sizeof(lz_list)/lw_sizeof(lz_list[0]));ld_i++){lf_if(lz_list[
ld_i].l59_max>=0){{l47_int16_t lg_src=_mb000010005((l25_uint16_t)(
lz_list[ld_i].l59_max/1024));_mb000010004((lb_void* )lc_p,(lb_void* )(
&lg_src),16/8);lc_p+=(16)/8;};}l3_else{{l47_int16_t lg_src=-1;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;
};}lf_if(lz_list[ld_i].l60_min>=0){{l47_int16_t lg_src=_mb000010005((
l25_uint16_t)(lz_list[ld_i].l60_min/1024));_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};}l3_else{{l47_int16_t
lg_src=-1;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);
lc_p+=(16)/8;};}lf_if(lz_list[ld_i].l45_mean>=0){{l47_int16_t lg_src=
_mb000010005((l25_uint16_t)(lz_list[ld_i].l45_mean/1024));
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;
};}l3_else{{l47_int16_t lg_src=-1;_mb000010004((lb_void* )lc_p,(
lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};}lf_if(lz_list[ld_i].
l121_std_dev_minus>=0.0){{l47_int16_t lg_src=_mb000010005((
l25_uint16_t)(lz_list[ld_i].l121_std_dev_minus/1024.0));_mb000010004(
(lb_void* )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};}l3_else{{
l47_int16_t lg_src=-1;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),16/8);lc_p+=(16)/8;};}lf_if(lz_list[ld_i].l120_std_dev_plus>=
0.0){{l47_int16_t lg_src=_mb000010005((l25_uint16_t)(lz_list[ld_i].
l120_std_dev_plus/1024.0));_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),16/8);lc_p+=(16)/8;};}l3_else{{l47_int16_t lg_src=-1;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;
};}}}{lt_uint64_t*lz_list[]={lh_gp_lte_data_set->l295_tx_packet_cnt,
lh_gp_lte_data_set->l299_rx_packet_cnt,lh_gp_lte_data_set->
l271_tx_frame_cnt,lh_gp_lte_data_set->l272_rx_frame_cnt};lt_uint64_t*
l753_err_list[]={lh_gp_lte_data_set->l387_tx_packet_err_cnt,
lh_gp_lte_data_set->l368_rx_packet_err_cnt,lh_gp_lte_data_set->
l404_tx_frame_err_cnt,lh_gp_lte_data_set->l404_tx_frame_err_cnt,};
la_int l295_tx_packet_cnt,l299_rx_packet_cnt;la_int l271_tx_frame_cnt
,l272_rx_frame_cnt;la_int*l1057_p_cnt_list[]={&l295_tx_packet_cnt,&
l299_rx_packet_cnt,&l271_tx_frame_cnt,&l272_rx_frame_cnt};la_int
l1043_tx_packet_err_rate,l970_rx_packet_err_rate;la_int
l898_tx_frame_err_rate,l931_rx_frame_err_rate;la_int*
l1097_p_err_rate_list[]={&l1043_tx_packet_err_rate,&
l970_rx_packet_err_rate,&l898_tx_frame_err_rate,&
l931_rx_frame_err_rate,};la_int l63_cnt;la_int l735_err_cnt;lr_double
l454_err_rate;l21_for(ld_i=0;ld_i<(lw_sizeof(lz_list)/lw_sizeof(
lz_list[0]));ld_i++){lf_if(lz_list[ld_i][l1_CURR]==-1||lz_list[ld_i][
l22_PREV]==-1){l63_cnt=-1;}l3_else{l63_cnt=(la_int)(lz_list[ld_i][
l1_CURR]-lz_list[ld_i][l22_PREV]);}lf_if(l753_err_list[ld_i][l1_CURR]
==-1||l753_err_list[ld_i][l22_PREV]==-1){l735_err_cnt=-1;}l3_else{
l735_err_cnt=(la_int)(l753_err_list[ld_i][l1_CURR]-l753_err_list[ld_i
][l22_PREV]);}lf_if(l63_cnt==-1||l735_err_cnt==-1){l454_err_rate=-1.0
;}l3_else lf_if(l63_cnt==0){l454_err_rate=0.0;}l3_else{l454_err_rate=
100.0*l735_err_cnt/l63_cnt;lf_if(l454_err_rate<1.0){l454_err_rate*=
100.0;l454_err_rate+=0x80;}} *l1057_p_cnt_list[ld_i]=l63_cnt; *
l1097_p_err_rate_list[ld_i]=(la_int)l454_err_rate;}{l47_int16_t lg_src
=_mb000010005((l25_uint16_t)l295_tx_packet_cnt);_mb000010004((lb_void
 * )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};{l47_int16_t lg_src
=_mb000010005((l25_uint16_t)l299_rx_packet_cnt);_mb000010004((lb_void
 * )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};{l2_int8_t lg_src=
l1043_tx_packet_err_rate;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=l970_rx_packet_err_rate;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{l47_int16_t lg_src=_mb000010005((l25_uint16_t)l271_tx_frame_cnt);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;
};{l47_int16_t lg_src=_mb000010005((l25_uint16_t)l272_rx_frame_cnt);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;
};{l2_int8_t lg_src=l898_tx_frame_err_rate;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
l931_rx_frame_err_rate;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),8/8);lc_p+=(8)/8;};}lf_if(lh_gp_lte_data_set->
l397_handover_event_supportness){lf_if(lh_gp_lte_data_set->
l434_handover_event_success_cnt>=255){{l2_int8_t lg_src=254;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
}l3_else{{l2_int8_t lg_src=lh_gp_lte_data_set->
l434_handover_event_success_cnt;_mb000010004((lb_void* )lc_p,(lb_void
 * )(&lg_src),8/8);lc_p+=(8)/8;};}lf_if(lh_gp_lte_data_set->
l431_handover_event_fail_cnt>=255){{l2_int8_t lg_src=254;_mb000010004
((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};}l3_else{{
l2_int8_t lg_src=lh_gp_lte_data_set->l431_handover_event_fail_cnt;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
}}l3_else{lf_if(lh_gp_lte_data_set->l278_handover_success_cnt[
l22_PREV]==-1||lh_gp_lte_data_set->l278_handover_success_cnt[l1_CURR]
==-1){{l2_int8_t lg_src=lh_gp_lte_data_set->
l514_handover_detected_cnt;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),8/8);lc_p+=(8)/8;};}l3_else{la_int l1032_success_cnt=
lh_gp_lte_data_set->l278_handover_success_cnt[l1_CURR]-
lh_gp_lte_data_set->l278_handover_success_cnt[l22_PREV];lf_if(
l1032_success_cnt>=255){{l2_int8_t lg_src=254;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};}l3_else{{l2_int8_t lg_src=
l1032_success_cnt;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8
/8);lc_p+=(8)/8;};}}lf_if(lh_gp_lte_data_set->l281_handover_fail_cnt[
l22_PREV]==-1||lh_gp_lte_data_set->l281_handover_fail_cnt[l1_CURR]==-
1){{l2_int8_t lg_src=-1;_mb000010004((lb_void* )lc_p,(lb_void* )(&
lg_src),8/8);lc_p+=(8)/8;};}l3_else{la_int l275_fail_cnt=
lh_gp_lte_data_set->l281_handover_fail_cnt[l1_CURR]-
lh_gp_lte_data_set->l281_handover_fail_cnt[l22_PREV];lf_if(
l275_fail_cnt>=255){{l2_int8_t lg_src=254;_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};}l3_else{{l2_int8_t lg_src=
l275_fail_cnt;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};}}}{l47_int16_t lg_src=_mb000010005((l25_uint16_t)lh_gp_lte_data_set
->l605_handover_latency_mean);_mb000010004((lb_void* )lc_p,(lb_void* )(
&lg_src),16/8);lc_p+=(16)/8;};{l2_int8_t lg_src=lh_gp_lte_data_set->
l251_tx_power;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);
lc_p+=(8)/8;};{l2_int8_t lg_src=lh_gp_lte_data_set->l173_temp;
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{l2_int8_t lg_src=lh_gp_lte_data_set->l380_batt_temp;_mb000010004((
lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t
lg_src=lh_gp_lte_data_set->l458_batt_lv;_mb000010004((lb_void* )lc_p,
(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
lh_gp_lte_data_set->l528_cpu_usage_mean;_mb000010004((lb_void* )lc_p,
(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
lh_gp_lte_data_set->l592_mem_usage_mean;_mb000010004((lb_void* )lc_p,
(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
lh_gp_lte_data_set->l464_activated_time;_mb000010004((lb_void* )lc_p,
(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l47_int16_t lg_src=
_mb000010005((l25_uint16_t)_mb000000004);_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};{l2_int8_t lg_src=
lh_gp_lte_data_set->l270_scc_count;_mb000010004((lb_void* )lc_p,(
lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};l21_for(ld_i=0;ld_i<
lh_gp_lte_data_set->l270_scc_count;ld_i++){{l32_int32_t lg_src=
_mb000010002((lm_uint32_t)lh_gp_lte_data_set->l488_scc_cell_id[ld_i]);
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/8;
};{l2_int8_t lg_src=lh_gp_lte_data_set->l459_scc_ch_bw[ld_i];
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{l2_int8_t lg_src=lh_gp_lte_data_set->l601_scc_rsrp_max[ld_i];
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{l2_int8_t lg_src=lh_gp_lte_data_set->l579_scc_rsrp_min[ld_i];
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
{l2_int8_t lg_src=lh_gp_lte_data_set->l566_scc_rsrp_mean[ld_i];
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};
lf_if(lh_gp_lte_data_set->l491_scc_rsrp_std_dev_minus[ld_i]>=0){{
l47_int16_t lg_src=_mb000010005((l25_uint16_t)(lh_gp_lte_data_set->
l491_scc_rsrp_std_dev_minus[ld_i] *100.0));_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};}l3_else{{l47_int16_t
lg_src=-1;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);
lc_p+=(16)/8;};}lf_if(lh_gp_lte_data_set->l486_scc_rsrp_std_dev_plus[
ld_i]>=0){{l47_int16_t lg_src=_mb000010005((l25_uint16_t)(
lh_gp_lte_data_set->l486_scc_rsrp_std_dev_plus[ld_i] *100.0));
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;
};}l3_else{{l47_int16_t lg_src=-1;_mb000010004((lb_void* )lc_p,(
lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};}{l2_int8_t lg_src=
lh_gp_lte_data_set->l591_scc_rsrq_max[ld_i];_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
lh_gp_lte_data_set->l567_scc_rsrq_min[ld_i];_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};{l2_int8_t lg_src=
lh_gp_lte_data_set->l607_scc_rsrq_mean[ld_i];_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),8/8);lc_p+=(8)/8;};lf_if(lh_gp_lte_data_set->
l480_scc_rsrq_std_dev_minus[ld_i]>=0){{l47_int16_t lg_src=
_mb000010005((l25_uint16_t)(lh_gp_lte_data_set->
l480_scc_rsrq_std_dev_minus[ld_i] *100.0));_mb000010004((lb_void* )lc_p
,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};}l3_else{{l47_int16_t
lg_src=-1;_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);
lc_p+=(16)/8;};}lf_if(lh_gp_lte_data_set->l479_scc_rsrq_std_dev_plus[
ld_i]>=0){{l47_int16_t lg_src=_mb000010005((l25_uint16_t)(
lh_gp_lte_data_set->l479_scc_rsrq_std_dev_plus[ld_i] *100.0));
_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),16/8);lc_p+=(16)/8;
};}l3_else{{l47_int16_t lg_src=-1;_mb000010004((lb_void* )lc_p,(
lb_void* )(&lg_src),16/8);lc_p+=(16)/8;};}{l32_int32_t lg_src=
_mb000010002((lm_uint32_t)lh_gp_lte_data_set->l510_scc_dl_earfcn[ld_i
]);_mb000010004((lb_void* )lc_p,(lb_void* )(&lg_src),32/8);lc_p+=(32)/
8;};}lq_return lc_p-ln_data;}
