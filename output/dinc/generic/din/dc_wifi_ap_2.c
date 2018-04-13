#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<math.h>
#include<limits.h>
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
lv_len);la_int l814_clct_wifi_ap_dev_info(l90_write_func l52_writer);
la_int l875_clct_wifi_ap_routine_info(l90_write_func l52_writer);
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
);
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
l624_dev_allow_web_access_from_wan(la_int l403_sec);l24_typedef la_int
( *l541_pack_func)(ll_uint8_t*ln_data,lb_void*l41_arg);lk_static
lb_void l583_clct_perf_info(lb_void);lk_static lb_void
l385_clct_dev_uid(lb_void);lk_static lb_void
l909_clct_wifi_ap_country_code(lb_void);lk_static lb_void
l1021_clct_wifi_ap_supp_freqs(lb_void);lk_static lb_void
l1017_clct_wifi_ap_supp_modes(lb_void);lk_static lb_void
l954_clct_wifi_ap_supp_encrypts(lb_void);lk_static lb_void
l947_clct_wifi_ap_work_freqs(lb_void);lk_static lb_void
l906_clct_wifi_ap_work_modes(lb_void);lk_static lb_void
l895_clct_wifi_ap_work_chs(lb_void);lk_static lb_void
l897_clct_wifi_ap_ssid_cfgs(lb_void);lk_static lb_void
l919_clct_wifi_ap_wan_ip_addr(lb_void);lk_static lb_void
l929_clct_wifi_ap_clients(lb_void);lk_static lb_void
l1025_clct_wifi_ap_tx_power(lb_void);lk_static la_int
l889_clct_wifi_ap_tx_byte(lb_void);lk_static lb_void
l786_clct_wifi_ap_tx_fragment_success_cnt(lb_void);lk_static lb_void
l848_clct_wifi_ap_tx_frame_retry_cnt(lb_void);lk_static lb_void
l884_clct_wifi_ap_tx_ack_loss_cnt(lb_void);lk_static la_int
l880_clct_wifi_ap_rx_byte(lb_void);lk_static lb_void
l829_clct_wifi_ap_rx_fragment_success_cnt(lb_void);lk_static lb_void
l845_clct_wifi_ap_rx_frame_fcs_err_cnt(lb_void);lk_static lb_void
l996_clct_wifi_ap_ngbr_infos(lb_void);lk_static lb_void
l987_clct_wifi_ap_throughput_byte(lb_void);lk_static lb_void
l545_calc_perf_info(lb_void);lk_static la_int l277_send_packed_info(
l90_write_func l52_writer,l541_pack_func l531_packer,lb_void*l41_arg);
lk_static lb_void l359_calc_peak_mean(li_const la_int lz_list[],
la_int l63_cnt,la_int*l298_p_max,la_int*l291_p_min,lr_double*
l253_p_mean);lk_static lb_void l429_calc_std_dev(li_const la_int
lz_list[],la_int l63_cnt,lr_double l45_mean,lr_double*l411_p_plus,
lr_double*l446_p_minus);lk_static lb_void
l920_wifi_ap_current_throughput_update(lb_void);l19_extern lt_uint64_t
l418_util_get_dev_uid(lb_void);l19_extern lr_double
l131_util_unsafe_sqrt(lr_double l12_val,la_int l117_digits);la_int
l814_clct_wifi_ap_dev_info(l90_write_func l52_writer){la_int l8_ret;
l385_clct_dev_uid();l909_clct_wifi_ap_country_code();
l1021_clct_wifi_ap_supp_freqs();l1017_clct_wifi_ap_supp_modes();
l954_clct_wifi_ap_supp_encrypts();l889_clct_wifi_ap_tx_byte();
l786_clct_wifi_ap_tx_fragment_success_cnt();
l848_clct_wifi_ap_tx_frame_retry_cnt();
l884_clct_wifi_ap_tx_ack_loss_cnt();l880_clct_wifi_ap_rx_byte();
l829_clct_wifi_ap_rx_fragment_success_cnt();
l845_clct_wifi_ap_rx_frame_fcs_err_cnt();l996_clct_wifi_ap_ngbr_infos
();l8_ret=l277_send_packed_info(l52_writer,&
l568_wifi_ap_pack_dev_info,lu_NULL);lx_gp_wifi_ap_data_set->
l165_ul_rate_cnt=0;lx_gp_wifi_ap_data_set->l157_dl_rate_cnt=0;
lq_return l8_ret;}la_int l875_clct_wifi_ap_routine_info(
l90_write_func l52_writer){l987_clct_wifi_ap_throughput_byte();
lx_gp_wifi_ap_data_set->l218_routine_cnt++;lf_if(
lx_gp_wifi_ap_data_set->l198_idle_count>l365_gp_wifi_ap_cfg->
l108_idle_threshold&&_mb000000002<240){_mb000000002++;}lf_if(
lx_gp_wifi_ap_data_set->l218_routine_cnt==_mb000000002){
l583_clct_perf_info();l545_calc_perf_info();l277_send_packed_info(
l52_writer,&l569_wifi_ap_pack_perf_info,lu_NULL);_mb000000002=60;
lx_gp_wifi_ap_data_set->l218_routine_cnt=0;lx_gp_wifi_ap_data_set->
l198_idle_count=0;lx_gp_wifi_ap_data_set->l165_ul_rate_cnt=0;
lx_gp_wifi_ap_data_set->l157_dl_rate_cnt=0;
l920_wifi_ap_current_throughput_update();}lq_return 0;}lk_static
lb_void l987_clct_wifi_ap_throughput_byte(lb_void){la_int l84_tx_byte
=l889_clct_wifi_ap_tx_byte();la_int l83_rx_byte=
l880_clct_wifi_ap_rx_byte();lf_if(l84_tx_byte!=0||l83_rx_byte!=0){
lx_gp_wifi_ap_data_set->l198_idle_count=0;}l3_else{
lx_gp_wifi_ap_data_set->l198_idle_count++;}}lk_static lb_void
l583_clct_perf_info(lb_void){l947_clct_wifi_ap_work_freqs();
l906_clct_wifi_ap_work_modes();l895_clct_wifi_ap_work_chs();
l897_clct_wifi_ap_ssid_cfgs();l919_clct_wifi_ap_wan_ip_addr();
l929_clct_wifi_ap_clients();l1025_clct_wifi_ap_tx_power();
l786_clct_wifi_ap_tx_fragment_success_cnt();
l848_clct_wifi_ap_tx_frame_retry_cnt();
l884_clct_wifi_ap_tx_ack_loss_cnt();
l829_clct_wifi_ap_rx_fragment_success_cnt();
l845_clct_wifi_ap_rx_frame_fcs_err_cnt();}lk_static lb_void
l385_clct_dev_uid(lb_void){lx_gp_wifi_ap_data_set->l44_uid=
l418_util_get_dev_uid();}lk_static lb_void
l909_clct_wifi_ap_country_code(lb_void){lf_if(
l635_wifi_ap_get_country_code(lx_gp_wifi_ap_data_set->
l460_country_code)<0){l86_memset(lx_gp_wifi_ap_data_set->
l460_country_code,-1,2);}}lk_static lb_void
l1021_clct_wifi_ap_supp_freqs(lb_void){lf_if(
l647_wifi_ap_get_supp_freqs(&lx_gp_wifi_ap_data_set->l467_supp_freqs)<
0){lx_gp_wifi_ap_data_set->l467_supp_freqs=-1;}}lk_static lb_void
l1017_clct_wifi_ap_supp_modes(lb_void){lf_if(
l724_wifi_ap_get_supp_modes(&lx_gp_wifi_ap_data_set->l498_supp_modes)<
0){lx_gp_wifi_ap_data_set->l498_supp_modes=-1;}}lk_static lb_void
l954_clct_wifi_ap_supp_encrypts(lb_void){lf_if(
l727_wifi_ap_get_supp_encrypts(&lx_gp_wifi_ap_data_set->
l513_supp_encrypts)<0){lx_gp_wifi_ap_data_set->l513_supp_encrypts=-1;
}}lk_static lb_void l947_clct_wifi_ap_work_freqs(lb_void){lf_if(
l698_wifi_ap_get_work_freqs(&lx_gp_wifi_ap_data_set->l485_work_freqs)<
0){lx_gp_wifi_ap_data_set->l485_work_freqs=-1;}}lk_static lb_void
l906_clct_wifi_ap_work_modes(lb_void){lf_if(
l715_wifi_ap_get_work_modes(&lx_gp_wifi_ap_data_set->l494_work_modes)<
0){lx_gp_wifi_ap_data_set->l494_work_modes=-1;}}lk_static lb_void
l895_clct_wifi_ap_work_chs(lb_void){lf_if(l649_wifi_ap_get_work_chs(
lx_gp_wifi_ap_data_set->l529_work_chs,&lx_gp_wifi_ap_data_set->
l453_work_ch_cnt)<0){lx_gp_wifi_ap_data_set->l453_work_ch_cnt=-1;}}
lk_static lb_void l897_clct_wifi_ap_ssid_cfgs(lb_void){lf_if(
l695_wifi_ap_get_ssid_cfgs(lx_gp_wifi_ap_data_set->l442_ssid_cfgs,&
lx_gp_wifi_ap_data_set->l423_ssid_cnt)<0){lx_gp_wifi_ap_data_set->
l423_ssid_cnt=-1;}}lk_static lb_void l919_clct_wifi_ap_wan_ip_addr(
lb_void){lj_char l74_ip_addr[40];lf_if(l641_wifi_ap_get_ip_addr(
l74_ip_addr)<0){l86_memset(&lx_gp_wifi_ap_data_set->l276_wan_ip_info,
-1,lw_sizeof(le_struct l51_ip_info));}l3_else{la_int l414_addr_family
;lf_if(l712_strchr(l74_ip_addr,'.')!=lu_NULL){l414_addr_family=
l145_AF_INET;lx_gp_wifi_ap_data_set->l276_wan_ip_info.lv_len=
lw_sizeof(le_struct l1046_in_addr);}l3_else{l414_addr_family=
l445_AF_INET6;lx_gp_wifi_ap_data_set->l276_wan_ip_info.lv_len=
lw_sizeof(le_struct l1111_in6_addr);}l798_inet_pton(l414_addr_family,
l74_ip_addr,&lx_gp_wifi_ap_data_set->l276_wan_ip_info.l29_addr);}}
lk_static lb_void l929_clct_wifi_ap_clients(lb_void){lf_if(
l710_wifi_ap_get_clients(lx_gp_wifi_ap_data_set->l354_clients,&
lx_gp_wifi_ap_data_set->l456_client_cnt)<0){lx_gp_wifi_ap_data_set->
l456_client_cnt=-1;}}lk_static lb_void l1025_clct_wifi_ap_tx_power(
lb_void){lf_if(l751_wifi_ap_get_tx_power(&lx_gp_wifi_ap_data_set->
l251_tx_power)<0){lx_gp_wifi_ap_data_set->l251_tx_power=127;}}
lk_static la_int l889_clct_wifi_ap_tx_byte(lb_void){
lx_gp_wifi_ap_data_set->l84_tx_byte[l22_PREV]=lx_gp_wifi_ap_data_set
->l84_tx_byte[l1_CURR];lf_if(l534_wifi_ap_get_tx_byte(&
lx_gp_wifi_ap_data_set->l84_tx_byte[l1_CURR])<0){
lx_gp_wifi_ap_data_set->l84_tx_byte[l1_CURR]=-1;}l3_else lf_if(
lx_gp_wifi_ap_data_set->l84_tx_byte[l22_PREV]!=-1){la_int l264_index=
lx_gp_wifi_ap_data_set->l165_ul_rate_cnt;lx_gp_wifi_ap_data_set->
l237_ul_rate[lx_gp_wifi_ap_data_set->l165_ul_rate_cnt++]=(la_int)(
lx_gp_wifi_ap_data_set->l84_tx_byte[l1_CURR]-lx_gp_wifi_ap_data_set->
l84_tx_byte[l22_PREV]);lq_return lx_gp_wifi_ap_data_set->l237_ul_rate
[l264_index];}lq_return 0;}lk_static lb_void
l786_clct_wifi_ap_tx_fragment_success_cnt(lb_void){
lx_gp_wifi_ap_data_set->l381_tx_fragment_success_cnt[l22_PREV]=
lx_gp_wifi_ap_data_set->l381_tx_fragment_success_cnt[l1_CURR];lf_if(
l645_wifi_ap_get_tx_fragment_success_cnt(&lx_gp_wifi_ap_data_set->
l381_tx_fragment_success_cnt[l1_CURR])<0){lx_gp_wifi_ap_data_set->
l381_tx_fragment_success_cnt[l1_CURR]=-1;}}lk_static lb_void
l848_clct_wifi_ap_tx_frame_retry_cnt(lb_void){lx_gp_wifi_ap_data_set
->l373_tx_frame_retry_cnt[l22_PREV]=lx_gp_wifi_ap_data_set->
l373_tx_frame_retry_cnt[l1_CURR];lf_if(
l652_wifi_ap_get_tx_frame_retry_cnt(&lx_gp_wifi_ap_data_set->
l373_tx_frame_retry_cnt[l1_CURR])<0){lx_gp_wifi_ap_data_set->
l373_tx_frame_retry_cnt[l1_CURR]=-1;}}lk_static lb_void
l884_clct_wifi_ap_tx_ack_loss_cnt(lb_void){lx_gp_wifi_ap_data_set->
l364_tx_ack_loss_cnt[l22_PREV]=lx_gp_wifi_ap_data_set->
l364_tx_ack_loss_cnt[l1_CURR];lf_if(l676_wifi_ap_get_tx_ack_loss_cnt(
&lx_gp_wifi_ap_data_set->l364_tx_ack_loss_cnt[l1_CURR])<0){
lx_gp_wifi_ap_data_set->l364_tx_ack_loss_cnt[l1_CURR]=-1;}}lk_static
la_int l880_clct_wifi_ap_rx_byte(lb_void){lx_gp_wifi_ap_data_set->
l83_rx_byte[l22_PREV]=lx_gp_wifi_ap_data_set->l83_rx_byte[l1_CURR];
lf_if(l543_wifi_ap_get_rx_byte(&lx_gp_wifi_ap_data_set->l83_rx_byte[
l1_CURR])<0){lx_gp_wifi_ap_data_set->l83_rx_byte[l1_CURR]=-1;}l3_else
lf_if(lx_gp_wifi_ap_data_set->l83_rx_byte[l22_PREV]!=-1){la_int
l264_index=lx_gp_wifi_ap_data_set->l157_dl_rate_cnt;
lx_gp_wifi_ap_data_set->l263_dl_rate[lx_gp_wifi_ap_data_set->
l157_dl_rate_cnt++]=(la_int)(lx_gp_wifi_ap_data_set->l83_rx_byte[
l1_CURR]-lx_gp_wifi_ap_data_set->l83_rx_byte[l22_PREV]);lq_return
lx_gp_wifi_ap_data_set->l263_dl_rate[l264_index];}lq_return 0;}
lk_static lb_void l920_wifi_ap_current_throughput_update(lb_void){
lx_gp_wifi_ap_data_set->l84_tx_byte[l22_PREV]=-1;
lx_gp_wifi_ap_data_set->l83_rx_byte[l22_PREV]=-1;lf_if(
l534_wifi_ap_get_tx_byte(&lx_gp_wifi_ap_data_set->l84_tx_byte[l1_CURR
])<0){lx_gp_wifi_ap_data_set->l84_tx_byte[l1_CURR]=-1;}lf_if(
l543_wifi_ap_get_rx_byte(&lx_gp_wifi_ap_data_set->l83_rx_byte[l1_CURR
])<0){lx_gp_wifi_ap_data_set->l83_rx_byte[l1_CURR]=-1;}}lk_static
lb_void l829_clct_wifi_ap_rx_fragment_success_cnt(lb_void){
lx_gp_wifi_ap_data_set->l392_rx_fragment_success_cnt[l22_PREV]=
lx_gp_wifi_ap_data_set->l392_rx_fragment_success_cnt[l1_CURR];lf_if(
l681_wifi_ap_get_rx_fragment_success_cnt(&lx_gp_wifi_ap_data_set->
l392_rx_fragment_success_cnt[l1_CURR])<0){lx_gp_wifi_ap_data_set->
l392_rx_fragment_success_cnt[l1_CURR]=-1;}}lk_static lb_void
l845_clct_wifi_ap_rx_frame_fcs_err_cnt(lb_void){
lx_gp_wifi_ap_data_set->l379_rx_frame_fcs_err_cnt[l22_PREV]=
lx_gp_wifi_ap_data_set->l379_rx_frame_fcs_err_cnt[l1_CURR];lf_if(
l667_wifi_ap_get_rx_frame_fcs_err_cnt(&lx_gp_wifi_ap_data_set->
l379_rx_frame_fcs_err_cnt[l1_CURR])<0){lx_gp_wifi_ap_data_set->
l379_rx_frame_fcs_err_cnt[l1_CURR]=-1;}}lk_static lb_void
l996_clct_wifi_ap_ngbr_infos(lb_void){la_int ld_i;l21_for(ld_i=0;ld_i
<16;ld_i++){lx_gp_wifi_ap_data_set->l144_ngbr_aps[ld_i].l571_mode=-1;
lx_gp_wifi_ap_data_set->l144_ngbr_aps[ld_i].l320_encrypt=-1;
lx_gp_wifi_ap_data_set->l144_ngbr_aps[ld_i].l533_ch=-1;
lx_gp_wifi_ap_data_set->l144_ngbr_aps[ld_i].l57_rssi=l972_INT_MAX;}
lf_if(l696_wifi_ap_get_ngbr_infos(lx_gp_wifi_ap_data_set->
l144_ngbr_aps,&lx_gp_wifi_ap_data_set->l376_ngbr_ap_cnt)<0){
lx_gp_wifi_ap_data_set->l376_ngbr_ap_cnt=-1;}l3_else{l21_for(ld_i=0;
ld_i<lx_gp_wifi_ap_data_set->l376_ngbr_ap_cnt;ld_i++){lf_if(
lx_gp_wifi_ap_data_set->l144_ngbr_aps[ld_i].l57_rssi==l972_INT_MAX){
lx_gp_wifi_ap_data_set->l144_ngbr_aps[ld_i].l57_rssi=127;}}}}
lk_static lb_void l545_calc_perf_info(){la_int ld_i;la_int l59_max,
l60_min;lr_double l45_mean;lr_double l121_std_dev_minus,
l120_std_dev_plus;{le_struct{la_int l63_cnt;la_int*ln_data;la_int*
l298_p_max;la_int*l291_p_min;la_int*l253_p_mean;lr_double*
l872_p_std_dev_plus;lr_double*l806_p_std_dev_minus;}lz_list[]={{
lx_gp_wifi_ap_data_set->l165_ul_rate_cnt,lx_gp_wifi_ap_data_set->
l237_ul_rate,&lx_gp_wifi_ap_data_set->l307_ul_rate_max,&
lx_gp_wifi_ap_data_set->l304_ul_rate_min,&lx_gp_wifi_ap_data_set->
l302_ul_rate_mean,&lx_gp_wifi_ap_data_set->l308_ul_rate_std_dev_plus,
&lx_gp_wifi_ap_data_set->l309_ul_rate_std_dev_minus},{
lx_gp_wifi_ap_data_set->l157_dl_rate_cnt,lx_gp_wifi_ap_data_set->
l263_dl_rate,&lx_gp_wifi_ap_data_set->l305_dl_rate_max,&
lx_gp_wifi_ap_data_set->l297_dl_rate_min,&lx_gp_wifi_ap_data_set->
l285_dl_rate_mean,&lx_gp_wifi_ap_data_set->l310_dl_rate_std_dev_plus,
&lx_gp_wifi_ap_data_set->l301_dl_rate_std_dev_minus}};l21_for(ld_i=0;
ld_i<(lw_sizeof(lz_list)/lw_sizeof(lz_list[0]));ld_i++){l59_max=-1;
l60_min=-1;l45_mean=-1.0;l120_std_dev_plus=-1.0;l121_std_dev_minus=-
1.0;l359_calc_peak_mean(lz_list[ld_i].ln_data,lz_list[ld_i].l63_cnt,&
l59_max,&l60_min,&l45_mean);l429_calc_std_dev(lz_list[ld_i].ln_data,
lz_list[ld_i].l63_cnt,l45_mean,&l120_std_dev_plus,&l121_std_dev_minus
); *lz_list[ld_i].l298_p_max=l59_max; *lz_list[ld_i].l291_p_min=
l60_min; *lz_list[ld_i].l253_p_mean=(la_int)l45_mean; *lz_list[ld_i].
l872_p_std_dev_plus=l120_std_dev_plus; *lz_list[ld_i].
l806_p_std_dev_minus=l121_std_dev_minus;}}}lk_static la_int
l277_send_packed_info(l90_write_func l52_writer,l541_pack_func
l531_packer,lb_void*l41_arg){ll_uint8_t ln_data[256];la_int lv_len;
lv_len=( *l531_packer)(ln_data,l41_arg);lq_return( *l52_writer)(
ln_data,lv_len);}lk_static lb_void l359_calc_peak_mean(li_const la_int
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
