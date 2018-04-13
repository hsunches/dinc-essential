#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<math.h>
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
l24_typedef la_int( *l90_write_func)(li_const lb_void*ln_data,la_int
lv_len);la_int l793_clct_lte_conn_history_info(l90_write_func
l52_writer);la_int l784_clct_lte_dev_info(l90_write_func l52_writer);
la_int l815_clct_lte_net_entry_info(l90_write_func l52_writer);la_int
l885_clct_lte_routine_info(l90_write_func l52_writer);lb_void
l881_set_lte_net_entry_latency(lm_uint32_t l75_latency);lb_void
l787_notify_lte_handover_start(l17_int64_t l419_time_usec);lb_void
l741_notify_lte_handover_end(la_int l483_is_success,l17_int64_t
l419_time_usec);
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
lo_value[5]);l13_enum{l22_PREV,l1_CURR};l13_enum{
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
#include"unmobric.h"
#include"log.h"
#include"mobric.h"
l24_typedef la_int( *l541_pack_func)(ll_uint8_t*ln_data,lb_void*
l41_arg);lk_static lb_void l911_clct_alert_info(lb_void);lk_static
lb_void l1009_clct_handover_info(lb_void);lk_static lb_void
l958_clct_ip_change_info(lb_void);lk_static lb_void
l583_clct_perf_info(lb_void);lk_static lb_void l385_clct_dev_uid(
lb_void);lk_static lb_void l978_clct_dev_batt_temp(lb_void);lk_static
lb_void l956_clct_dev_temp(lb_void);lk_static lb_void
l923_clct_dev_cpu_usage(lb_void);lk_static lb_void
l952_clct_dev_mem_usage(lb_void);lk_static lb_void
l903_clct_dev_batt_lv(lb_void);lk_static lb_void
l933_clct_lte_supported_freq_band(lb_void);lk_static lb_void
l803_clct_lte_ip_address(lb_void);lk_static lb_void
l1042_clct_lte_network_entry_latency(lb_void);lk_static lb_void
l781_clct_lte_cell_id(lb_void);lk_static lb_void l879_clct_lte_rssi(
lb_void);lk_static lb_void l892_clct_lte_rsrp(lb_void);lk_static
lb_void l890_clct_lte_rsrq(lb_void);lk_static lb_void
l888_clct_lte_cqi(lb_void);lk_static lb_void l910_clct_lte_ul_earfcn(
lb_void);lk_static lb_void l946_clct_lte_dl_earfcn(lb_void);lk_static
lb_void l939_clct_lte_channel_bw(lb_void);lk_static lb_void
l1045_clct_lte_mcc(lb_void);lk_static lb_void l922_clct_lte_mnc(
lb_void);lk_static lb_void l1044_clct_lte_lac(lb_void);lk_static
lb_void l1010_clct_lte_handover_latency(lb_void);lk_static lb_void
l796_clct_lte_handover_success_count(lb_void);lk_static lb_void
l791_clct_lte_handover_failure_count(lb_void);lk_static lb_void
l941_clct_lte_ul_mcs(lb_void);lk_static lb_void l927_clct_lte_dl_mcs(
lb_void);lk_static lb_void l1033_clct_lte_tx_power(lb_void);lk_static
la_int l819_clct_lte_tx_byte(lb_void);lk_static la_int
l866_clct_lte_rx_byte(lb_void);lk_static lb_void
l816_clct_lte_tx_packet_count(lb_void);lk_static lb_void
l778_clct_lte_rx_packet_count(lb_void);lk_static lb_void
l777_clct_lte_tx_packet_error_count(lb_void);lk_static lb_void
l822_clct_lte_rx_packet_error_count(lb_void);lk_static lb_void
l772_clct_lte_tx_frame_count(lb_void);lk_static lb_void
l831_clct_lte_rx_frame_count(lb_void);lk_static lb_void
l846_clct_lte_tx_frame_error_count(lb_void);lk_static lb_void
l869_clct_lte_rx_frame_error_count(lb_void);lk_static lb_void
l1035_clct_lte_disconnect_reason(lb_void);lk_static lb_void
l858_clct_lte_neighboring_cell_info(lb_void);lk_static lb_void
l950_clct_lte_ul_bearer_flow_max_speed(lb_void);lk_static lb_void
l934_clct_lte_dl_bearer_flow_max_speed(lb_void);lk_static lb_void
l783_clct_lte_throughput_byte(lb_void);lk_static lb_void
l545_calc_perf_info(lb_void);lk_static lb_void
l943_clct_lte_scc_aggregated_count(lb_void);lk_static lb_void
l1003_clct_lte_scc_cell_id(lb_void);lk_static lb_void
l1012_clct_lte_scc_channel_bw(lb_void);lk_static lb_void
l990_clct_lte_scc_rsrp(lb_void);lk_static lb_void
l989_clct_lte_scc_rsrq(lb_void);lk_static lb_void
l1023_clct_lte_scc_dl_earfcn(lb_void);lk_static lb_void
l537_update_stat_tbl(la_int l9_type,la_int ln_data);lk_static lb_void
l855_update_report_interval(la_int l57_rssi,la_int l77_rsrp,la_int
l79_rsrq,la_int l205_cqi);lk_static lb_void
l968_lte_current_throughput_update(lb_void);lk_static la_int
l277_send_packed_info(l90_write_func l52_writer,l541_pack_func
l531_packer,lb_void*l41_arg);lk_static la_int
l1039_send_round_trip_latency_req(l90_write_func l52_writer);
lk_static lb_void l359_calc_peak_mean(li_const la_int lz_list[],
la_int l63_cnt,la_int*l298_p_max,la_int*l291_p_min,lr_double*
l253_p_mean);lk_static lb_void l429_calc_std_dev(li_const la_int
lz_list[],la_int l63_cnt,lr_double l45_mean,lr_double*l411_p_plus,
lr_double*l446_p_minus);l19_extern lm_uint32_t _mb000000004;
l19_extern la_int _mb000000002;l19_extern l17_int64_t _mb000000011;
l19_extern lt_uint64_t l418_util_get_dev_uid(lb_void);l19_extern
lr_double l131_util_unsafe_sqrt(lr_double l12_val,la_int l117_digits);
la_int l793_clct_lte_conn_history_info(l90_write_func l52_writer){
la_int l8_ret;la_int l57_rssi;la_int l77_rsrp;la_int l79_rsrq;la_int
l205_cqi;l385_clct_dev_uid();l879_clct_lte_rssi();l892_clct_lte_rsrp(
);l890_clct_lte_rsrq();l888_clct_lte_cqi();l8_ret=
l277_send_packed_info(l52_writer,&l603_lte_pack_conn_history_info,
lu_NULL);l57_rssi=(lh_gp_lte_data_set->l300_rssi_cnt>0)?
lh_gp_lte_data_set->l57_rssi[0]:-1;l77_rsrp=(lh_gp_lte_data_set->
l336_rsrp_cnt>0)?lh_gp_lte_data_set->l77_rsrp[0]:-1;l79_rsrq=(
lh_gp_lte_data_set->l340_rsrq_cnt>0)?lh_gp_lte_data_set->l79_rsrq[0]:
-1;l205_cqi=(lh_gp_lte_data_set->l363_cqi_cnt>0)?lh_gp_lte_data_set->
l205_cqi[0]:-1;l855_update_report_interval(l57_rssi,l77_rsrp,l79_rsrq
,l205_cqi);lh_gp_lte_data_set->l300_rssi_cnt=0;lh_gp_lte_data_set->
l336_rsrp_cnt=0;lh_gp_lte_data_set->l340_rsrq_cnt=0;
lh_gp_lte_data_set->l363_cqi_cnt=0;lq_return l8_ret;}la_int
l784_clct_lte_dev_info(l90_write_func l52_writer){
l933_clct_lte_supported_freq_band();lq_return l277_send_packed_info(
l52_writer,&l565_pack_dev_info,lu_NULL);}la_int
l815_clct_lte_net_entry_info(l90_write_func l52_writer){la_int l8_ret
;l803_clct_lte_ip_address();l781_clct_lte_cell_id();
l1045_clct_lte_mcc();l922_clct_lte_mnc();l1044_clct_lte_lac();
l1042_clct_lte_network_entry_latency();
l1035_clct_lte_disconnect_reason();
l858_clct_lte_neighboring_cell_info();
l950_clct_lte_ul_bearer_flow_max_speed();
l934_clct_lte_dl_bearer_flow_max_speed();
l796_clct_lte_handover_success_count();
l791_clct_lte_handover_failure_count();l819_clct_lte_tx_byte();
l816_clct_lte_tx_packet_count();l777_clct_lte_tx_packet_error_count();
l772_clct_lte_tx_frame_count();l846_clct_lte_tx_frame_error_count();
l866_clct_lte_rx_byte();l778_clct_lte_rx_packet_count();
l822_clct_lte_rx_packet_error_count();l831_clct_lte_rx_frame_count();
l869_clct_lte_rx_frame_error_count();l8_ret=l277_send_packed_info(
l52_writer,&l551_pack_net_entry_info,lu_NULL);lh_gp_lte_data_set->
l165_ul_rate_cnt=0;lh_gp_lte_data_set->l157_dl_rate_cnt=0;lq_return
l8_ret;}la_int l885_clct_lte_routine_info(l90_write_func l52_writer){
la_int ld_i;l978_clct_dev_batt_temp();l956_clct_dev_temp();
l923_clct_dev_cpu_usage();l952_clct_dev_mem_usage();
l803_clct_lte_ip_address();l781_clct_lte_cell_id();l879_clct_lte_rssi
();l892_clct_lte_rsrp();l890_clct_lte_rsrq();l888_clct_lte_cqi();
l941_clct_lte_ul_mcs();l927_clct_lte_dl_mcs();
l783_clct_lte_throughput_byte();l858_clct_lte_neighboring_cell_info();
l943_clct_lte_scc_aggregated_count();l990_clct_lte_scc_rsrp();
l989_clct_lte_scc_rsrq();lh_gp_lte_data_set->l218_routine_cnt++;
l21_for(ld_i=0;ld_i<(lw_sizeof(_mb000000001)/lw_sizeof(_mb000000001[0
]));ld_i++){lf_if(_mb000000001[ld_i].l180_is_alert_needed){
l911_clct_alert_info();l277_send_packed_info(l52_writer,&
l612_pack_alert_info,&ld_i);}}lf_if(lh_gp_lte_data_set->l102_cell_id[
l22_PREV]!=lh_gp_lte_data_set->l102_cell_id[l1_CURR]){
lh_gp_lte_data_set->l514_handover_detected_cnt++;
l1009_clct_handover_info();l277_send_packed_info(l52_writer,&
l615_pack_handover_info,lu_NULL);}lf_if(l273_strcmp(
lh_gp_lte_data_set->l51_ip_info[l22_PREV].l74_ip_addr,
lh_gp_lte_data_set->l51_ip_info[l1_CURR].l74_ip_addr)!=0){
l958_clct_ip_change_info();l277_send_packed_info(l52_writer,&
l609_pack_ip_change_info,lu_NULL);}lf_if(lh_gp_lte_data_set->
l198_idle_count>l71_gp_lte_cfg->l108_idle_threshold&&_mb000000002<240
){_mb000000002++;}lf_if(lh_gp_lte_data_set->l218_routine_cnt==
_mb000000002-5){l1039_send_round_trip_latency_req(l52_writer);}
l3_else lf_if(lh_gp_lte_data_set->l218_routine_cnt==_mb000000002){
l583_clct_perf_info();l545_calc_perf_info();l277_send_packed_info(
l52_writer,&l550_pack_perf_info,lu_NULL);l855_update_report_interval(
lh_gp_lte_data_set->l478_rssi_mean,lh_gp_lte_data_set->l471_rsrp_mean
,lh_gp_lte_data_set->l497_rsrq_mean,lh_gp_lte_data_set->l466_cqi_mean
);lh_gp_lte_data_set->l218_routine_cnt=0;lh_gp_lte_data_set->
l464_activated_time=0;lh_gp_lte_data_set->l198_idle_count=0;
lh_gp_lte_data_set->l300_rssi_cnt=0;lh_gp_lte_data_set->l336_rsrp_cnt
=0;lh_gp_lte_data_set->l340_rsrq_cnt=0;lh_gp_lte_data_set->
l363_cqi_cnt=0;lh_gp_lte_data_set->l434_handover_event_success_cnt=0;
lh_gp_lte_data_set->l431_handover_event_fail_cnt=0;lh_gp_lte_data_set
->l514_handover_detected_cnt=0;lh_gp_lte_data_set->
l401_handover_latency_cnt=0;l86_memset(lh_gp_lte_data_set->
l345_ul_mod_cnt,0,lw_sizeof(lh_gp_lte_data_set->l345_ul_mod_cnt));
l86_memset(lh_gp_lte_data_set->l357_dl_mod_cnt,0,lw_sizeof(
lh_gp_lte_data_set->l357_dl_mod_cnt));lh_gp_lte_data_set->
l165_ul_rate_cnt=0;lh_gp_lte_data_set->l157_dl_rate_cnt=0;
lh_gp_lte_data_set->l516_cpu_usage_cnt=0;lh_gp_lte_data_set->
l501_mem_usage_cnt=0;lh_gp_lte_data_set->l270_scc_count=0;
lh_gp_lte_data_set->l393_scc_rsrp_cnt=0;lh_gp_lte_data_set->
l394_scc_rsrq_cnt=0;l968_lte_current_throughput_update();}lq_return 0
;}lb_void l881_set_lte_net_entry_latency(lm_uint32_t l75_latency){
lh_gp_lte_data_set->l395_net_entry_latency=l75_latency;}lb_void
l787_notify_lte_handover_start(l17_int64_t l419_time_usec){
lh_gp_lte_data_set->l397_handover_event_supportness=1;_mb000000011=
l419_time_usec;}lb_void l741_notify_lte_handover_end(la_int
l483_is_success,l17_int64_t l419_time_usec){la_int
l719_handover_latency_msec;lf_if(l483_is_success){lh_gp_lte_data_set
->l434_handover_event_success_cnt++;l719_handover_latency_msec=(
la_int)(l419_time_usec-_mb000000011)/1000;_mb000000011=0;lf_if(
l719_handover_latency_msec>65535){l719_handover_latency_msec=-1;}
lf_if(lh_gp_lte_data_set->l401_handover_latency_cnt<(lw_sizeof(
lh_gp_lte_data_set->l372_handover_latency)/lw_sizeof(
lh_gp_lte_data_set->l372_handover_latency[0]))){lh_gp_lte_data_set->
l372_handover_latency[lh_gp_lte_data_set->l401_handover_latency_cnt++
]=l719_handover_latency_msec;}}l3_else{lh_gp_lte_data_set->
l431_handover_event_fail_cnt++;}}lk_static lb_void
l911_clct_alert_info(lb_void){}lk_static lb_void
l1009_clct_handover_info(lb_void){l1010_clct_lte_handover_latency();}
lk_static lb_void l958_clct_ip_change_info(lb_void){}lk_static lb_void
l583_clct_perf_info(lb_void){l903_clct_dev_batt_lv();
l910_clct_lte_ul_earfcn();l946_clct_lte_dl_earfcn();
l939_clct_lte_channel_bw();l796_clct_lte_handover_success_count();
l791_clct_lte_handover_failure_count();l1033_clct_lte_tx_power();
l783_clct_lte_throughput_byte();l816_clct_lte_tx_packet_count();
l777_clct_lte_tx_packet_error_count();l772_clct_lte_tx_frame_count();
l846_clct_lte_tx_frame_error_count();l778_clct_lte_rx_packet_count();
l822_clct_lte_rx_packet_error_count();l831_clct_lte_rx_frame_count();
l869_clct_lte_rx_frame_error_count();l1003_clct_lte_scc_cell_id();
l1012_clct_lte_scc_channel_bw();l1023_clct_lte_scc_dl_earfcn();}
lk_static lb_void l385_clct_dev_uid(lb_void){lh_gp_lte_data_set->
l44_uid=l418_util_get_dev_uid();}lk_static lb_void
l978_clct_dev_batt_temp(lb_void){lf_if(l604_dev_get_batt_temp(&
lh_gp_lte_data_set->l380_batt_temp)<0){lh_gp_lte_data_set->
l380_batt_temp=127;}l3_else{l537_update_stat_tbl(l640_STAT_BATT_TEMP,
lh_gp_lte_data_set->l380_batt_temp);}}lk_static lb_void
l956_clct_dev_temp(lb_void){lf_if(l590_dev_get_temp(&
lh_gp_lte_data_set->l173_temp)<0){lh_gp_lte_data_set->l173_temp=127;}
l3_else{l537_update_stat_tbl(l674_STAT_TEMP,lh_gp_lte_data_set->
l173_temp);}}lk_static lb_void l923_clct_dev_cpu_usage(lb_void){
la_int l353_cpu_usage;lf_if(l602_dev_get_cpu_usage(&l353_cpu_usage)==
0){lh_gp_lte_data_set->l353_cpu_usage[lh_gp_lte_data_set->
l516_cpu_usage_cnt++]=l353_cpu_usage;l537_update_stat_tbl(
l415_STAT_CPU_USAGE,l353_cpu_usage);}}lk_static lb_void
l952_clct_dev_mem_usage(lb_void){la_int l327_mem_usage;lf_if(
l540_dev_get_mem_usage(&l327_mem_usage)==0){lh_gp_lte_data_set->
l327_mem_usage[lh_gp_lte_data_set->l501_mem_usage_cnt++]=
l327_mem_usage;l537_update_stat_tbl(l410_STAT_MEM_USAGE,
l327_mem_usage);}}lk_static lb_void l903_clct_dev_batt_lv(lb_void){
lf_if(l598_dev_get_batt_lv(&lh_gp_lte_data_set->l458_batt_lv)<0){
lh_gp_lte_data_set->l458_batt_lv=-1;}}lk_static lb_void
l933_clct_lte_supported_freq_band(lb_void){l4_long l4_long
l348_freq_bitmap=0;lf_if(l725_lte_get_supported_freq_band(&
l348_freq_bitmap)<0){lh_gp_lte_data_set->l348_freq_bitmap=-1;}l3_else
{lh_gp_lte_data_set->l348_freq_bitmap=(lt_uint64_t)l348_freq_bitmap;}
}lk_static lb_void l803_clct_lte_ip_address(lb_void){lj_char
l74_ip_addr[40]="";l109_memcpy(&lh_gp_lte_data_set->l51_ip_info[
l22_PREV],&lh_gp_lte_data_set->l51_ip_info[l1_CURR],lw_sizeof(
le_struct l51_ip_info));lf_if(l717_lte_get_ip_address(l74_ip_addr)<0){
l86_memset(&lh_gp_lte_data_set->l51_ip_info[l1_CURR],-1,lw_sizeof(
le_struct l51_ip_info)); *l74_ip_addr=0;}l3_else{la_int
l414_addr_family;lf_if(l712_strchr(l74_ip_addr,'.')!=lu_NULL){
l414_addr_family=l145_AF_INET;lh_gp_lte_data_set->l51_ip_info[l1_CURR
].lv_len=lw_sizeof(le_struct l1046_in_addr);}l3_else{l414_addr_family
=l445_AF_INET6;lh_gp_lte_data_set->l51_ip_info[l1_CURR].lv_len=
lw_sizeof(le_struct l1111_in6_addr);}l798_inet_pton(l414_addr_family,
l74_ip_addr,lh_gp_lte_data_set->l51_ip_info[l1_CURR].l29_addr);}
l361_strcpy(lh_gp_lte_data_set->l51_ip_info[l1_CURR].l74_ip_addr,
l74_ip_addr);}lk_static lb_void l1042_clct_lte_network_entry_latency(
lb_void){lf_if(lh_gp_lte_data_set->l395_net_entry_latency==-1){lf_if(
l660_lte_get_network_entry_latency(&lh_gp_lte_data_set->
l395_net_entry_latency)<0){lh_gp_lte_data_set->l395_net_entry_latency
=-1;}}}lk_static lb_void l781_clct_lte_cell_id(lb_void){
lh_gp_lte_data_set->l102_cell_id[l22_PREV]=lh_gp_lte_data_set->
l102_cell_id[l1_CURR];lf_if(l742_lte_get_cell_id(&lh_gp_lte_data_set
->l102_cell_id[l1_CURR])<0){lh_gp_lte_data_set->l102_cell_id[l1_CURR]
=-1;}}lk_static lb_void l879_clct_lte_rssi(lb_void){la_int l57_rssi;
lf_if(l662_lte_get_rssi(&l57_rssi)==0){lh_gp_lte_data_set->l57_rssi[
lh_gp_lte_data_set->l300_rssi_cnt++]=l57_rssi;}}lk_static lb_void
l892_clct_lte_rsrp(lb_void){la_int l77_rsrp;lf_if(l665_lte_get_rsrp(&
l77_rsrp)==0){lh_gp_lte_data_set->l77_rsrp[lh_gp_lte_data_set->
l336_rsrp_cnt++]=l77_rsrp;}}lk_static lb_void l890_clct_lte_rsrq(
lb_void){l239_float l79_rsrq;lf_if(l666_lte_get_rsrq(&l79_rsrq)==0){
lh_gp_lte_data_set->l79_rsrq[lh_gp_lte_data_set->l340_rsrq_cnt++]=(
la_int)l79_rsrq;}}lk_static lb_void l888_clct_lte_cqi(lb_void){la_int
l205_cqi;lf_if(l653_lte_get_cqi(&l205_cqi)==0){lh_gp_lte_data_set->
l205_cqi[lh_gp_lte_data_set->l363_cqi_cnt++]=l205_cqi;}}lk_static
lb_void l910_clct_lte_ul_earfcn(lb_void){lf_if(l728_lte_get_ul_earfcn
(&lh_gp_lte_data_set->l502_ul_earfcn)<0){lh_gp_lte_data_set->
l502_ul_earfcn=-1;}}lk_static lb_void l946_clct_lte_dl_earfcn(lb_void
){lf_if(l704_lte_get_dl_earfcn(&lh_gp_lte_data_set->l517_dl_earfcn)<0
){lh_gp_lte_data_set->l517_dl_earfcn=-1;}}lk_static lb_void
l939_clct_lte_channel_bw(lb_void){lf_if(l685_lte_get_channel_bw(&
lh_gp_lte_data_set->l512_ch_bw)<0){lh_gp_lte_data_set->l512_ch_bw=-1;
}}lk_static lb_void l1045_clct_lte_mcc(lb_void){lf_if(
l633_lte_get_mcc(&lh_gp_lte_data_set->l138_mcc)<0){lh_gp_lte_data_set
->l138_mcc=-1;}}lk_static lb_void l922_clct_lte_mnc(lb_void){
l86_memset(lh_gp_lte_data_set->l112_mnc,0,lw_sizeof(
lh_gp_lte_data_set->l112_mnc));l732_lte_get_mnc(lh_gp_lte_data_set->
l112_mnc);}lk_static lb_void l1044_clct_lte_lac(lb_void){lf_if(
l664_lte_get_lac(&lh_gp_lte_data_set->l143_lac)<0){lh_gp_lte_data_set
->l143_lac=-1;}}lk_static lb_void l1010_clct_lte_handover_latency(
lb_void){la_int l75_latency;lf_if(!lh_gp_lte_data_set->
l397_handover_event_supportness){lf_if(l663_lte_get_handover_latency(
&l75_latency)==0){lh_gp_lte_data_set->l372_handover_latency[
lh_gp_lte_data_set->l401_handover_latency_cnt++]=l75_latency;}}}
lk_static lb_void l796_clct_lte_handover_success_count(lb_void){lf_if
(!lh_gp_lte_data_set->l397_handover_event_supportness){
lh_gp_lte_data_set->l278_handover_success_cnt[l22_PREV]=
lh_gp_lte_data_set->l278_handover_success_cnt[l1_CURR];lf_if(
l689_lte_get_handover_success_count(&lh_gp_lte_data_set->
l278_handover_success_cnt[l1_CURR])<0){lh_gp_lte_data_set->
l278_handover_success_cnt[l1_CURR]=-1;}}}lk_static lb_void
l791_clct_lte_handover_failure_count(lb_void){lf_if(!
lh_gp_lte_data_set->l397_handover_event_supportness){
lh_gp_lte_data_set->l281_handover_fail_cnt[l22_PREV]=
lh_gp_lte_data_set->l281_handover_fail_cnt[l1_CURR];lf_if(
l678_lte_get_handover_failure_count(&lh_gp_lte_data_set->
l281_handover_fail_cnt[l1_CURR])<0){lh_gp_lte_data_set->
l281_handover_fail_cnt[l1_CURR]=-1;}}}lk_static lb_void
l941_clct_lte_ul_mcs(lb_void){la_int l621_mod;lf_if(
l634_lte_get_ul_mcs(&l621_mod)==0){l107_switch(l621_mod){l7_case 0x12
:lh_gp_lte_data_set->l345_ul_mod_cnt[l439_MOD_QPSK]++;ly_break;
l7_case 0x24:lh_gp_lte_data_set->l345_ul_mod_cnt[l413_MOD_16QAM]++;
ly_break;l7_case 0x26:lh_gp_lte_data_set->l345_ul_mod_cnt[
l406_MOD_64QAM]++;ly_break;}}}lk_static lb_void l927_clct_lte_dl_mcs(
lb_void){la_int l621_mod;lf_if(l729_lte_get_dl_mcs(&l621_mod)==0){
l107_switch(l621_mod){l7_case 0x12:lh_gp_lte_data_set->
l357_dl_mod_cnt[l439_MOD_QPSK]++;ly_break;l7_case 0x24:
lh_gp_lte_data_set->l357_dl_mod_cnt[l413_MOD_16QAM]++;ly_break;
l7_case 0x26:lh_gp_lte_data_set->l357_dl_mod_cnt[l406_MOD_64QAM]++;
ly_break;}}}lk_static lb_void l783_clct_lte_throughput_byte(lb_void){
la_int l84_tx_byte=l819_clct_lte_tx_byte();la_int l83_rx_byte=
l866_clct_lte_rx_byte();lf_if(l84_tx_byte!=0||l83_rx_byte!=0){
lh_gp_lte_data_set->l464_activated_time++;lh_gp_lte_data_set->
l198_idle_count=0;}l3_else{lh_gp_lte_data_set->l198_idle_count++;}}
lk_static lb_void l968_lte_current_throughput_update(lb_void){
l36_unsigned l4_long l4_long l321_byte=0;lh_gp_lte_data_set->
l84_tx_byte[l22_PREV]=-1;lh_gp_lte_data_set->l83_rx_byte[l22_PREV]=-1
;lf_if(l530_lte_get_tx_byte(&l321_byte)<0){lh_gp_lte_data_set->
l84_tx_byte[l1_CURR]=-1;}l3_else{lh_gp_lte_data_set->l84_tx_byte[
l1_CURR]=(lt_uint64_t)l321_byte;}lf_if(l536_lte_get_rx_byte(&
l321_byte)<0){lh_gp_lte_data_set->l83_rx_byte[l1_CURR]=-1;}l3_else{
lh_gp_lte_data_set->l83_rx_byte[l1_CURR]=(lt_uint64_t)l321_byte;}}
lk_static lb_void l1033_clct_lte_tx_power(lb_void){lf_if(
l737_lte_get_tx_power(&lh_gp_lte_data_set->l251_tx_power)<0){
lh_gp_lte_data_set->l251_tx_power=127;}}lk_static la_int
l819_clct_lte_tx_byte(lb_void){l36_unsigned l4_long l4_long l321_byte
=0;lh_gp_lte_data_set->l84_tx_byte[l22_PREV]=lh_gp_lte_data_set->
l84_tx_byte[l1_CURR];lf_if(l530_lte_get_tx_byte(&l321_byte)<0){
lh_gp_lte_data_set->l84_tx_byte[l1_CURR]=-1;}l3_else{
lh_gp_lte_data_set->l84_tx_byte[l1_CURR]=(lt_uint64_t)l321_byte;lf_if
(lh_gp_lte_data_set->l84_tx_byte[l22_PREV]!=-1){la_int l264_index=
lh_gp_lte_data_set->l165_ul_rate_cnt;lh_gp_lte_data_set->l237_ul_rate
[lh_gp_lte_data_set->l165_ul_rate_cnt++]=(la_int)(lh_gp_lte_data_set
->l84_tx_byte[l1_CURR]-lh_gp_lte_data_set->l84_tx_byte[l22_PREV]);
lq_return lh_gp_lte_data_set->l237_ul_rate[l264_index];}}lq_return 0;
}lk_static lb_void l816_clct_lte_tx_packet_count(lb_void){
l36_unsigned l4_long l4_long l58_count;lh_gp_lte_data_set->
l295_tx_packet_cnt[l22_PREV]=lh_gp_lte_data_set->l295_tx_packet_cnt[
l1_CURR];lf_if(l654_lte_get_tx_packet_count(&l58_count)<0){
lh_gp_lte_data_set->l295_tx_packet_cnt[l1_CURR]=-1;}l3_else{
lh_gp_lte_data_set->l295_tx_packet_cnt[l1_CURR]=(lt_uint64_t)l58_count
;}}lk_static lb_void l777_clct_lte_tx_packet_error_count(lb_void){
l36_unsigned l4_long l4_long l58_count;lh_gp_lte_data_set->
l387_tx_packet_err_cnt[l22_PREV]=lh_gp_lte_data_set->
l387_tx_packet_err_cnt[l1_CURR];lf_if(
l750_lte_get_tx_packet_error_count(&l58_count)<0){lh_gp_lte_data_set
->l387_tx_packet_err_cnt[l1_CURR]=-1;}l3_else{lh_gp_lte_data_set->
l387_tx_packet_err_cnt[l1_CURR]=(lt_uint64_t)l58_count;}}lk_static
lb_void l772_clct_lte_tx_frame_count(lb_void){l36_unsigned l4_long
l4_long l58_count;lh_gp_lte_data_set->l271_tx_frame_cnt[l22_PREV]=
lh_gp_lte_data_set->l271_tx_frame_cnt[l1_CURR];lf_if(
l686_lte_get_tx_frame_count(&l58_count)<0){lh_gp_lte_data_set->
l271_tx_frame_cnt[l1_CURR]=-1;}l3_else{lh_gp_lte_data_set->
l271_tx_frame_cnt[l1_CURR]=(lt_uint64_t)l58_count;}}lk_static lb_void
l846_clct_lte_tx_frame_error_count(lb_void){l36_unsigned l4_long
l4_long l58_count;lh_gp_lte_data_set->l404_tx_frame_err_cnt[l22_PREV]
=lh_gp_lte_data_set->l404_tx_frame_err_cnt[l1_CURR];lf_if(
l677_lte_get_tx_frame_error_count(&l58_count)<0){lh_gp_lte_data_set->
l404_tx_frame_err_cnt[l1_CURR]=-1;}l3_else{lh_gp_lte_data_set->
l271_tx_frame_cnt[l1_CURR]=(lt_uint64_t)l58_count;}}lk_static la_int
l866_clct_lte_rx_byte(lb_void){l36_unsigned l4_long l4_long l321_byte
=0;lh_gp_lte_data_set->l83_rx_byte[l22_PREV]=lh_gp_lte_data_set->
l83_rx_byte[l1_CURR];lf_if(l536_lte_get_rx_byte(&l321_byte)<0){
lh_gp_lte_data_set->l83_rx_byte[l1_CURR]=-1;}l3_else{
lh_gp_lte_data_set->l83_rx_byte[l1_CURR]=(lt_uint64_t)l321_byte;lf_if
(lh_gp_lte_data_set->l83_rx_byte[l22_PREV]!=-1){la_int l264_index=
lh_gp_lte_data_set->l157_dl_rate_cnt;lh_gp_lte_data_set->l263_dl_rate
[lh_gp_lte_data_set->l157_dl_rate_cnt++]=(la_int)(lh_gp_lte_data_set
->l83_rx_byte[l1_CURR]-lh_gp_lte_data_set->l83_rx_byte[l22_PREV]);
lq_return lh_gp_lte_data_set->l263_dl_rate[l264_index];}}lq_return 0;
}lk_static lb_void l778_clct_lte_rx_packet_count(lb_void){
l36_unsigned l4_long l4_long l58_count;lh_gp_lte_data_set->
l299_rx_packet_cnt[l22_PREV]=lh_gp_lte_data_set->l299_rx_packet_cnt[
l1_CURR];lf_if(l740_lte_get_rx_packet_count(&l58_count)<0){
lh_gp_lte_data_set->l299_rx_packet_cnt[l1_CURR]=-1;}l3_else{
lh_gp_lte_data_set->l299_rx_packet_cnt[l1_CURR]=(lt_uint64_t)l58_count
;}}lk_static lb_void l822_clct_lte_rx_packet_error_count(lb_void){
l36_unsigned l4_long l4_long l58_count;lh_gp_lte_data_set->
l368_rx_packet_err_cnt[l22_PREV]=lh_gp_lte_data_set->
l368_rx_packet_err_cnt[l1_CURR];lf_if(
l762_lte_get_rx_packet_error_count(&l58_count)<0){lh_gp_lte_data_set
->l368_rx_packet_err_cnt[l1_CURR]=-1;}l3_else{lh_gp_lte_data_set->
l368_rx_packet_err_cnt[l1_CURR]=(lt_uint64_t)l58_count;}}lk_static
lb_void l831_clct_lte_rx_frame_count(lb_void){l36_unsigned l4_long
l4_long l58_count;lh_gp_lte_data_set->l272_rx_frame_cnt[l22_PREV]=
lh_gp_lte_data_set->l272_rx_frame_cnt[l1_CURR];lf_if(
l760_lte_get_rx_frame_count(&l58_count)<0){lh_gp_lte_data_set->
l272_rx_frame_cnt[l1_CURR]=-1;}l3_else{lh_gp_lte_data_set->
l272_rx_frame_cnt[l1_CURR]=(lt_uint64_t)l58_count;}}lk_static lb_void
l869_clct_lte_rx_frame_error_count(lb_void){l36_unsigned l4_long
l4_long l58_count;lh_gp_lte_data_set->l476_rx_frame_err_cnt[l22_PREV]
=lh_gp_lte_data_set->l476_rx_frame_err_cnt[l1_CURR];lf_if(
l756_lte_get_rx_frame_error_count(&l58_count)<0){lh_gp_lte_data_set->
l476_rx_frame_err_cnt[l1_CURR]=-1;}l3_else{lh_gp_lte_data_set->
l272_rx_frame_cnt[l1_CURR]=(lt_uint64_t)l58_count;}}lk_static lb_void
l1035_clct_lte_disconnect_reason(lb_void){lf_if(
l733_lte_get_disconnect_reason(&lh_gp_lte_data_set->
l465_disconnect_reason)<0){lh_gp_lte_data_set->l465_disconnect_reason
=-1;}}lk_static lb_void l858_clct_lte_neighboring_cell_info(lb_void){
l335_lte_cell_info lz_list[16];la_int ld_i;lh_gp_lte_data_set->
l268_ngbr_cell_cnt[l22_PREV]=lh_gp_lte_data_set->l268_ngbr_cell_cnt[
l1_CURR];l109_memcpy(lh_gp_lte_data_set->l91_ngbr_cells[l22_PREV],
lh_gp_lte_data_set->l91_ngbr_cells[l1_CURR],16*lw_sizeof(
l335_lte_cell_info));l21_for(ld_i=0;ld_i<16;ld_i++){lz_list[ld_i].
l102_cell_id=-1;lz_list[ld_i].l138_mcc=-1;l86_memset(lz_list[ld_i].
l112_mnc,0,4);lz_list[ld_i].l143_lac=-1;lz_list[ld_i].l57_rssi=127;
lz_list[ld_i].l77_rsrp=127;lz_list[ld_i].l79_rsrq=l1096_FLT_MAX;}
lf_if(l763_lte_get_neighboring_cell_info(&lh_gp_lte_data_set->
l268_ngbr_cell_cnt[l1_CURR],lz_list)<0){lh_gp_lte_data_set->
l268_ngbr_cell_cnt[l1_CURR]=-1;}l3_else{l21_for(ld_i=0;ld_i<
lh_gp_lte_data_set->l268_ngbr_cell_cnt[l1_CURR];ld_i++){
lh_gp_lte_data_set->l91_ngbr_cells[l1_CURR][ld_i].l102_cell_id=
lz_list[ld_i].l102_cell_id;lh_gp_lte_data_set->l91_ngbr_cells[l1_CURR
][ld_i].l138_mcc=lz_list[ld_i].l138_mcc;l109_memcpy(
lh_gp_lte_data_set->l91_ngbr_cells[l1_CURR][ld_i].l112_mnc,lz_list[
ld_i].l112_mnc,4);lh_gp_lte_data_set->l91_ngbr_cells[l1_CURR][ld_i].
l143_lac=lz_list[ld_i].l143_lac;lh_gp_lte_data_set->l91_ngbr_cells[
l1_CURR][ld_i].l57_rssi=(la_int)lz_list[ld_i].l57_rssi;
lh_gp_lte_data_set->l91_ngbr_cells[l1_CURR][ld_i].l77_rsrp=(la_int)lz_list
[ld_i].l77_rsrp;lf_if(lz_list[ld_i].l79_rsrq==l1096_FLT_MAX){
lh_gp_lte_data_set->l91_ngbr_cells[l1_CURR][ld_i].l79_rsrq=127;}}}}
lk_static lb_void l950_clct_lte_ul_bearer_flow_max_speed(lb_void){
lf_if(l675_lte_get_ul_bearer_flow_max_speed(&lh_gp_lte_data_set->
l475_ul_max_bearer_speed)<0){lh_gp_lte_data_set->
l475_ul_max_bearer_speed=-1;}}lk_static lb_void
l934_clct_lte_dl_bearer_flow_max_speed(lb_void){lf_if(
l757_lte_get_dl_bearer_flow_max_speed(&lh_gp_lte_data_set->
l505_dl_max_bearer_speed)<0){lh_gp_lte_data_set->
l505_dl_max_bearer_speed=-1;}}lk_static lb_void l545_calc_perf_info(){
la_int ld_i;la_int l59_max,l60_min;lr_double l45_mean;lr_double
l121_std_dev_minus,l120_std_dev_plus;{le_struct{la_int l63_cnt;la_int
 *ln_data;la_int*l298_p_max;la_int*l291_p_min;la_int*l253_p_mean;
lr_double*l872_p_std_dev_plus;lr_double*l806_p_std_dev_minus;la_int
l800_invalid_value;}lz_list[]={{lh_gp_lte_data_set->l300_rssi_cnt,
lh_gp_lte_data_set->l57_rssi,&lh_gp_lte_data_set->l527_rssi_max,&
lh_gp_lte_data_set->l562_rssi_min,&lh_gp_lte_data_set->l478_rssi_mean
,&lh_gp_lte_data_set->l564_rssi_std_dev_plus,&lh_gp_lte_data_set->
l552_rssi_std_dev_minus,127},{lh_gp_lte_data_set->l336_rsrp_cnt,
lh_gp_lte_data_set->l77_rsrp,&lh_gp_lte_data_set->l521_rsrp_max,&
lh_gp_lte_data_set->l618_rsrp_min,&lh_gp_lte_data_set->l471_rsrp_mean
,&lh_gp_lte_data_set->l563_rsrp_std_dev_plus,&lh_gp_lte_data_set->
l542_rsrp_std_dev_minus,127},{lh_gp_lte_data_set->l340_rsrq_cnt,
lh_gp_lte_data_set->l79_rsrq,&lh_gp_lte_data_set->l573_rsrq_max,&
lh_gp_lte_data_set->l578_rsrq_min,&lh_gp_lte_data_set->l497_rsrq_mean
,&lh_gp_lte_data_set->l613_rsrq_std_dev_plus,&lh_gp_lte_data_set->
l608_rsrq_std_dev_minus,127},{lh_gp_lte_data_set->l363_cqi_cnt,
lh_gp_lte_data_set->l205_cqi,&lh_gp_lte_data_set->l588_cqi_max,&
lh_gp_lte_data_set->l593_cqi_min,&lh_gp_lte_data_set->l466_cqi_mean,&
lh_gp_lte_data_set->l577_cqi_std_dev_plus,&lh_gp_lte_data_set->
l559_cqi_std_dev_minus,-1},{lh_gp_lte_data_set->l165_ul_rate_cnt,
lh_gp_lte_data_set->l237_ul_rate,&lh_gp_lte_data_set->
l307_ul_rate_max,&lh_gp_lte_data_set->l304_ul_rate_min,&
lh_gp_lte_data_set->l302_ul_rate_mean,&lh_gp_lte_data_set->
l308_ul_rate_std_dev_plus,&lh_gp_lte_data_set->
l309_ul_rate_std_dev_minus,-1},{lh_gp_lte_data_set->l157_dl_rate_cnt,
lh_gp_lte_data_set->l263_dl_rate,&lh_gp_lte_data_set->
l305_dl_rate_max,&lh_gp_lte_data_set->l297_dl_rate_min,&
lh_gp_lte_data_set->l285_dl_rate_mean,&lh_gp_lte_data_set->
l310_dl_rate_std_dev_plus,&lh_gp_lte_data_set->
l301_dl_rate_std_dev_minus,-1}};l21_for(ld_i=0;ld_i<(lw_sizeof(
lz_list)/lw_sizeof(lz_list[0]));ld_i++){l59_max=lz_list[ld_i].
l800_invalid_value;l60_min=lz_list[ld_i].l800_invalid_value;l45_mean=
lz_list[ld_i].l800_invalid_value;l120_std_dev_plus=-1.0;
l121_std_dev_minus=-1.0;l359_calc_peak_mean(lz_list[ld_i].ln_data,
lz_list[ld_i].l63_cnt,&l59_max,&l60_min,&l45_mean);l429_calc_std_dev(
lz_list[ld_i].ln_data,lz_list[ld_i].l63_cnt,l45_mean,&
l120_std_dev_plus,&l121_std_dev_minus); *lz_list[ld_i].l298_p_max=
l59_max; *lz_list[ld_i].l291_p_min=l60_min; *lz_list[ld_i].
l253_p_mean=(la_int)l45_mean; *lz_list[ld_i].l872_p_std_dev_plus=
l120_std_dev_plus; *lz_list[ld_i].l806_p_std_dev_minus=
l121_std_dev_minus;}}{le_struct{la_int l63_cnt;la_int*ln_data;la_int*
l253_p_mean;}lz_list[]={{lh_gp_lte_data_set->
l401_handover_latency_cnt,lh_gp_lte_data_set->l372_handover_latency,&
lh_gp_lte_data_set->l605_handover_latency_mean},{lh_gp_lte_data_set->
l516_cpu_usage_cnt,lh_gp_lte_data_set->l353_cpu_usage,&
lh_gp_lte_data_set->l528_cpu_usage_mean},{lh_gp_lte_data_set->
l501_mem_usage_cnt,lh_gp_lte_data_set->l327_mem_usage,&
lh_gp_lte_data_set->l592_mem_usage_mean}};l21_for(ld_i=0;ld_i<(
lw_sizeof(lz_list)/lw_sizeof(lz_list[0]));ld_i++){l45_mean=-1.0;
l359_calc_peak_mean(lz_list[ld_i].ln_data,lz_list[ld_i].l63_cnt,
lu_NULL,lu_NULL,&l45_mean); *lz_list[ld_i].l253_p_mean=(la_int)l45_mean
;}}l21_for(ld_i=0;ld_i<lh_gp_lte_data_set->l270_scc_count;ld_i++){
l120_std_dev_plus=-1.0;l121_std_dev_minus=-1.0;l359_calc_peak_mean(
lh_gp_lte_data_set->l493_scc_rsrp[ld_i],lh_gp_lte_data_set->
l393_scc_rsrp_cnt,&lh_gp_lte_data_set->l601_scc_rsrp_max[ld_i],&
lh_gp_lte_data_set->l579_scc_rsrp_min[ld_i],&l45_mean);
l429_calc_std_dev(lh_gp_lte_data_set->l493_scc_rsrp[ld_i],
lh_gp_lte_data_set->l393_scc_rsrp_cnt,l45_mean,&l120_std_dev_plus,&
l121_std_dev_minus);lh_gp_lte_data_set->l566_scc_rsrp_mean[ld_i]=(
la_int)l45_mean;lh_gp_lte_data_set->l486_scc_rsrp_std_dev_plus[ld_i]=
l120_std_dev_plus;lh_gp_lte_data_set->l491_scc_rsrp_std_dev_minus[
ld_i]=l121_std_dev_minus;}l21_for(ld_i=0;ld_i<lh_gp_lte_data_set->
l270_scc_count;ld_i++){l120_std_dev_plus=-1.0;l121_std_dev_minus=-1.0
;l359_calc_peak_mean(lh_gp_lte_data_set->l489_scc_rsrq[ld_i],
lh_gp_lte_data_set->l394_scc_rsrq_cnt,&lh_gp_lte_data_set->
l591_scc_rsrq_max[ld_i],&lh_gp_lte_data_set->l567_scc_rsrq_min[ld_i],
&l45_mean);l429_calc_std_dev(lh_gp_lte_data_set->l489_scc_rsrq[ld_i],
lh_gp_lte_data_set->l394_scc_rsrq_cnt,l45_mean,&l120_std_dev_plus,&
l121_std_dev_minus);lh_gp_lte_data_set->l607_scc_rsrq_mean[ld_i]=(
la_int)l45_mean;lh_gp_lte_data_set->l479_scc_rsrq_std_dev_plus[ld_i]=
l120_std_dev_plus;lh_gp_lte_data_set->l480_scc_rsrq_std_dev_minus[
ld_i]=l121_std_dev_minus;}}lk_static lb_void
l943_clct_lte_scc_aggregated_count(lb_void){lf_if(
l694_lte_get_scc_aggregated_count(&lh_gp_lte_data_set->l270_scc_count
)<0){lh_gp_lte_data_set->l270_scc_count=0;}}lk_static lb_void
l1003_clct_lte_scc_cell_id(lb_void){la_int ld_i=0;lf_if(
l693_lte_get_scc_cell_id(lh_gp_lte_data_set->l488_scc_cell_id)<0){
l21_for(ld_i=0;ld_i<5;ld_i++){lh_gp_lte_data_set->l488_scc_cell_id[
ld_i]=-1;}}}lk_static lb_void l1012_clct_lte_scc_channel_bw(lb_void){
la_int ld_i=0;lf_if(l648_lte_get_scc_channel_bw(lh_gp_lte_data_set->
l459_scc_ch_bw)<0){l21_for(ld_i=0;ld_i<5;ld_i++){lh_gp_lte_data_set->
l459_scc_ch_bw[ld_i]=-1;}}}lk_static lb_void l990_clct_lte_scc_rsrp(
lb_void){la_int l77_rsrp[5];lf_if(l714_lte_get_scc_rsrp(l77_rsrp)==0){
la_int ld_i;l21_for(ld_i=0;ld_i<lh_gp_lte_data_set->l270_scc_count;
ld_i++){lh_gp_lte_data_set->l493_scc_rsrp[ld_i][lh_gp_lte_data_set->
l393_scc_rsrp_cnt]=l77_rsrp[ld_i];}lh_gp_lte_data_set->
l393_scc_rsrp_cnt++;}}lk_static lb_void l989_clct_lte_scc_rsrq(
lb_void){l239_float l79_rsrq[5];lf_if(l713_lte_get_scc_rsrq(l79_rsrq)==
0){la_int ld_i;l21_for(ld_i=0;ld_i<lh_gp_lte_data_set->l270_scc_count
;ld_i++){lh_gp_lte_data_set->l489_scc_rsrq[ld_i][lh_gp_lte_data_set->
l394_scc_rsrq_cnt]=(la_int)l79_rsrq[ld_i];}lh_gp_lte_data_set->
l394_scc_rsrq_cnt++;}}lk_static lb_void l1023_clct_lte_scc_dl_earfcn(
lb_void){la_int ld_i=0;lf_if(l745_lte_get_scc_dl_earfcn(
lh_gp_lte_data_set->l510_scc_dl_earfcn)<0){l21_for(ld_i=0;ld_i<5;ld_i
++){lh_gp_lte_data_set->l510_scc_dl_earfcn[ld_i]=-1;}}}lk_static
lb_void l537_update_stat_tbl(la_int l9_type,la_int ln_data){la_int
l974_data_out;la_int l100_lv;la_int ld_i;l860_memmove(_mb000000001[
l9_type].l149_win+1,_mb000000001[l9_type].l149_win,lw_sizeof(la_int) *
10);l974_data_out=_mb000000001[l9_type].l149_win[10];_mb000000001[
l9_type].l149_win[0]=ln_data;lf_if(_mb000000001[l9_type].
l166_win_usage<=10){_mb000000001[l9_type].l166_win_usage++;}
_mb000000001[l9_type].l180_is_alert_needed=0;l100_lv=-1;l21_for(ld_i=
(lw_sizeof(_mb000000001[l9_type].l167_th)/lw_sizeof(_mb000000001[
l9_type].l167_th[0]))-1;ld_i>=0;ld_i--){lf_if(_mb000000001[l9_type].
l166_win_usage>10&&l974_data_out>_mb000000001[l9_type].l167_th[ld_i]){
_mb000000001[l9_type].l176_over_th_cnt[ld_i]--;}lf_if(ln_data>
_mb000000001[l9_type].l167_th[ld_i]){_mb000000001[l9_type].
l176_over_th_cnt[ld_i]++;}lf_if(l100_lv==-1&&_mb000000001[l9_type].
l176_over_th_cnt[ld_i]>=5){l100_lv=ld_i;}}{la_int l63_cnt=
_mb000000001[l9_type].l166_win_usage;lr_double l45_mean;lf_if(l63_cnt
>10){l63_cnt=10;}l359_calc_peak_mean(_mb000000001[l9_type].l149_win,
l63_cnt,&_mb000000001[l9_type].l59_max,&_mb000000001[l9_type].l60_min
,&l45_mean);_mb000000001[l9_type].l45_mean=(la_int)l45_mean;}
_mb000000001[l9_type].l100_lv[l22_PREV]=_mb000000001[l9_type].l100_lv
[l1_CURR];lf_if(l100_lv==-1){_mb000000001[l9_type].l100_lv[l1_CURR]=-
1;}l3_else lf_if(l100_lv>_mb000000001[l9_type].l100_lv[l22_PREV]){
_mb000000001[l9_type].l180_is_alert_needed=1;_mb000000001[l9_type].
l100_lv[l1_CURR]=l100_lv;}}lk_static lb_void
l855_update_report_interval(la_int l57_rssi,la_int l77_rsrp,la_int
l79_rsrq,la_int l205_cqi){la_int ld_i;la_int l235_indicator;
_mb000000002=l71_gp_lte_cfg->l241_report_intervals[l71_gp_lte_cfg->
l231_threshold_cnt];l107_switch(l71_gp_lte_cfg->l235_indicator){
l7_case l702_REPORT_INTERVAL_INDICATOR_RSSI:l235_indicator=l57_rssi;
ly_break;l7_case l706_REPORT_INTERVAL_INDICATOR_RSRP:l235_indicator=
l77_rsrp;ly_break;l7_case l705_REPORT_INTERVAL_INDICATOR_RSRQ:
l235_indicator=l79_rsrq;ly_break;l7_case
l718_REPORT_INTERVAL_INDICATOR_CQI:l235_indicator=l205_cqi;ly_break;
l238_default:lq_return;}lf_if(l235_indicator==-1){lq_return;}l21_for(
ld_i=0;ld_i<l71_gp_lte_cfg->l231_threshold_cnt;ld_i++){lf_if(
l235_indicator<=l71_gp_lte_cfg->l422_thresholds[ld_i]){_mb000000002=
l71_gp_lte_cfg->l241_report_intervals[ld_i];ly_break;}}lf_if(ld_i==
l71_gp_lte_cfg->l231_threshold_cnt){_mb000000002=l71_gp_lte_cfg->
l241_report_intervals[ld_i];}}lk_static la_int l277_send_packed_info(
l90_write_func l52_writer,l541_pack_func l531_packer,lb_void*l41_arg){
ll_uint8_t ln_data[256];la_int lv_len;lv_len=( *l531_packer)(ln_data,
l41_arg);lq_return( *l52_writer)(ln_data,lv_len);}lk_static la_int
l1039_send_round_trip_latency_req(l90_write_func l52_writer){
le_struct{lm_uint32_t l9_type;lm_uint32_t l16_dc_id;}ln_data;ln_data.
l9_type=l68_htonl(l170_IPC_MSG_GET_LATENCY);ln_data.l16_dc_id=
l68_htonl(l73_IPC_DC_LTE);lq_return( *l52_writer)(&ln_data,lw_sizeof(
ln_data));}lk_static lb_void l359_calc_peak_mean(li_const la_int
lz_list[],la_int l63_cnt,la_int*l298_p_max,la_int*l291_p_min,
lr_double*l253_p_mean){la_int ld_i;la_int l59_max,l60_min;l4_long
l4_long l451_sum;lf_if(l63_cnt<=0){lq_return;}l59_max=lz_list[0];
l60_min=lz_list[0];l451_sum=lz_list[0];l21_for(ld_i=1;ld_i<l63_cnt;
ld_i++){lf_if(l59_max<lz_list[ld_i]){l59_max=lz_list[ld_i];}l3_else
lf_if(l60_min>lz_list[ld_i]){l60_min=lz_list[ld_i];}l451_sum+=lz_list
[ld_i];}lf_if(l298_p_max!=lu_NULL){ *l298_p_max=l59_max;}lf_if(
l291_p_min!=lu_NULL){ *l291_p_min=l60_min;}lf_if(l253_p_mean!=lu_NULL
){ *l253_p_mean=(lr_double)l451_sum/l63_cnt;}}lk_static lb_void
l429_calc_std_dev(li_const la_int lz_list[],la_int l63_cnt,lr_double
l45_mean,lr_double*l411_p_plus,lr_double*l446_p_minus){la_int ld_i;
lr_double l421_sqr_plus,l417_sqr_minus;la_int l342_cnt_plus,
l330_cnt_minus;lr_double l78_diff;lf_if(l63_cnt<=0){lq_return;}
l421_sqr_plus=0.0;l417_sqr_minus=0.0;l342_cnt_plus=0;l330_cnt_minus=0
;l21_for(ld_i=0;ld_i<l63_cnt;ld_i++){l78_diff=lz_list[ld_i]-l45_mean;
lf_if(l78_diff>0){l342_cnt_plus++;l421_sqr_plus+=l78_diff*l78_diff;}
l3_else lf_if(l78_diff<0){l330_cnt_minus++;l417_sqr_minus+=l78_diff*
l78_diff;}}lf_if(l411_p_plus!=lu_NULL){ *l411_p_plus=(l342_cnt_plus>0
)?l131_util_unsafe_sqrt(l421_sqr_plus/l342_cnt_plus,2):0;}lf_if(
l446_p_minus!=lu_NULL){ *l446_p_minus=(l330_cnt_minus>0)?
l131_util_unsafe_sqrt(l417_sqr_minus/l330_cnt_minus,2):0;}}
