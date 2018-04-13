#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<netinet/in.h>
#include"mobric.h"
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
#include"unmobric.h"
#include"log.h"
#include"mobric.h"
l13_enum{l617_CFG_STR,l318_CFG_INT};lk_static li_const le_struct{
li_const lj_char*l752_key;la_int l9_type;la_int lv_len;lb_void*lc_p;}
l424_g_cfg_attr[]={{"\x73\x65\x72\x76\x65\x72\x5f\x70\x72\x65\x66\x69"
"\x78",l617_CFG_STR,lw_sizeof(l20_g_cfg.l441_server_prefix),l20_g_cfg
.l441_server_prefix},{"\x73\x65\x72\x76\x65\x72\x5f\x73\x75\x66\x66"
"\x69\x78",l617_CFG_STR,lw_sizeof(l20_g_cfg.l314_server_suffix),
l20_g_cfg.l314_server_suffix},{"\x73\x65\x72\x76\x65\x72\x5f\x64\x6f"
"\x6d\x61\x69\x6e\x5f\x6e\x61\x6d\x65",l617_CFG_STR,lw_sizeof(
l20_g_cfg.l399_server_domain_name),l20_g_cfg.l399_server_domain_name}
,{"\x73\x65\x72\x76\x65\x72\x5f\x69\x70\x5f\x61\x64\x64\x72",
l617_CFG_STR,lw_sizeof(l20_g_cfg.l328_server_ip_addr),l20_g_cfg.
l328_server_ip_addr},{"\x73\x65\x72\x76\x65\x72\x5f\x70\x6f\x72\x74",
l318_CFG_INT,lw_sizeof(l20_g_cfg.l438_server_port),&l20_g_cfg.
l438_server_port},{"\x73\x65\x72\x76\x65\x72\x5f\x70\x6f\x72\x74\x5f"
"\x72\x61\x6e\x67\x65",l318_CFG_INT,lw_sizeof(l20_g_cfg.
l447_server_port_range),&l20_g_cfg.l447_server_port_range},{"\x6d\x61"
"\x78\x5f\x64\x6e\x73\x5f\x71\x75\x65\x72\x79",l318_CFG_INT,lw_sizeof
(l20_g_cfg.l315_max_dns_query),&l20_g_cfg.l315_max_dns_query},{"\x6d"
"\x61\x78\x5f\x68\x61\x6e\x64\x73\x68\x61\x6b\x65",l318_CFG_INT,
lw_sizeof(l20_g_cfg.l391_max_handshake),&l20_g_cfg.l391_max_handshake
},{"\x6d\x61\x78\x5f\x6c\x61\x74\x65\x6e\x63\x79",l318_CFG_INT,
lw_sizeof(l20_g_cfg.l329_max_latency),&l20_g_cfg.l329_max_latency},{""
"\x72\x65\x6d\x6f\x74\x65\x5f\x6d\x73\x67\x5f\x74\x69\x6d\x65\x6f\x75"
"\x74",l318_CFG_INT,lw_sizeof(l20_g_cfg.l437_remote_msg_timeout),&
l20_g_cfg.l437_remote_msg_timeout},{"\x6f\x70\x5f\x6d\x6f\x64\x65",
l318_CFG_INT,lw_sizeof(l20_g_cfg.l338_op_mode),&l20_g_cfg.
l338_op_mode},{"\x69\x64\x6c\x65\x5f\x74\x68\x72\x65\x73\x68\x6f\x6c"
"\x64",l318_CFG_INT,lw_sizeof(l20_g_cfg.l108_idle_threshold),&
l20_g_cfg.l108_idle_threshold},{"\x64\x65\x76\x5f\x69\x6e\x66\x6f\x5f"
"\x72\x65\x70\x6f\x72\x74\x5f\x69\x6e\x74\x65\x72\x76\x61\x6c",
l318_CFG_INT,lw_sizeof(l20_g_cfg.l449_dev_info_report_interval),&
l20_g_cfg.l449_dev_info_report_interval}};le_struct l375_cfg l20_g_cfg
;lk_static lb_void l928_load_dflt_cfg(lb_void);lb_void
l584_load_cfg_str(li_const lj_char*l113_s,li_const lj_char*l402_delim
){lj_char l72_buf[512];lj_char*l761_assignment;lj_char*lc_p;lj_char*
l752_key;la_int lo_value;la_int ld_i;lf_if(l113_s==lu_NULL){lq_return
;}lf_if(l402_delim==lu_NULL){l402_delim="\x20";}l658_strncpy(l72_buf,
l113_s,512-1);l72_buf[512-1]='\0';l21_for(l761_assignment=l292_strtok
(l72_buf,l402_delim);l761_assignment!=lu_NULL;l761_assignment=
l292_strtok(lu_NULL,l402_delim)){lc_p=l712_strchr(l752_key=
l761_assignment,'=');lf_if(lc_p==lu_NULL){l288_continue;} *lc_p++=
'\0';l21_for(ld_i=0;ld_i<(lw_sizeof(l424_g_cfg_attr)/lw_sizeof(
l424_g_cfg_attr[0]));ld_i++){lf_if(!l273_strcmp(l752_key,
l424_g_cfg_attr[ld_i].l752_key)){l107_switch(l424_g_cfg_attr[ld_i].
l9_type){l7_case l617_CFG_STR:l658_strncpy((lj_char* )l424_g_cfg_attr
[ld_i].lc_p,lc_p,l424_g_cfg_attr[ld_i].lv_len-1);ly_break;l7_case
l318_CFG_INT:l134_errno=0;lo_value=(la_int)l836_strtol(lc_p,lu_NULL,
10);lf_if(!l134_errno){ * (la_int* )l424_g_cfg_attr[ld_i].lc_p=
lo_value;}ly_break;}}}}}la_int l546_load_cfg_file(li_const lj_char*
l230_path){l893_FILE*l213_file;lj_char l72_buf[512];la_int
l408_buf_usage;la_int l8_ret;l928_load_dflt_cfg();lf_if(l230_path==
lu_NULL){l230_path="\x64\x69\x6e\x2e\x63\x66\x67";}l27_LOGG_INFO(""
"\x4f\x70\x65\x6e\x20\x63\x6f\x6e\x66\x69\x67\x75\x72\x61\x74\x69\x6f"
"\x6e\x20\x66\x69\x6c\x65\x3a\x20\x25\x73",l230_path);l213_file=
l1022_fopen(l230_path,"\x72");lf_if(l213_file==lu_NULL){
l142_LOGG_ERRNO("\x66\x6f\x70\x65\x6e");lq_return((1<<31)|(
l234_ERR_LV_WARN<<28)|(l37_ERR_CAT_GENERAL<<14)|0x01);}l408_buf_usage
=l1178_fread(l72_buf,1,512-1,l213_file);lf_if(l1148_ferror(l213_file)){
l8_ret=((1<<31)|(l234_ERR_LV_WARN<<28)|(l37_ERR_CAT_GENERAL<<14)|0x02
);}l3_else{l72_buf[l408_buf_usage]='\0';l584_load_cfg_str(l72_buf,""
"\r\n");l8_ret=((0<<31)|(l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14
)|0x00);}l896_fclose(l213_file);lq_return l8_ret;}lk_static lb_void
l928_load_dflt_cfg(lb_void){l86_memset(&l20_g_cfg,0,lw_sizeof(
l20_g_cfg));l658_strncpy(l20_g_cfg.l441_server_prefix,"\x63\x66\x67",
lw_sizeof(l20_g_cfg.l441_server_prefix)-1);;l658_strncpy(l20_g_cfg.
l314_server_suffix,"\x64\x70\x6d\x2e\x6d\x6f\x62\x72\x69\x63\x2e\x63"
"\x6f\x6d",lw_sizeof(l20_g_cfg.l314_server_suffix)-1);;l20_g_cfg.
l438_server_port=(la_int)52888;;l20_g_cfg.l447_server_port_range=(
la_int)10;;l20_g_cfg.l315_max_dns_query=(la_int)5;;l20_g_cfg.
l391_max_handshake=(la_int)5;;l20_g_cfg.l329_max_latency=(la_int)3000
;;l20_g_cfg.l437_remote_msg_timeout=(la_int)30;;l20_g_cfg.
l338_op_mode=(la_int)1;;l20_g_cfg.l108_idle_threshold=(la_int)15;;
l20_g_cfg.l449_dev_info_report_interval=(la_int)86400;;}
