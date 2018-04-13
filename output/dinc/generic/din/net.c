#include<stdint.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/nameser.h>
#include<arpa/inet.h>
#include<resolv.h>
#include"mobric.h"
l13_enum{l53_ERR_LV_DBG,l535_ERR_LV_INFO,l234_ERR_LV_WARN,
l69_ERR_LV_ERR};l13_enum{l37_ERR_CAT_GENERAL,l347_ERR_CAT_DAEMON,
l575_ERR_CAT_DPM_CFG,l87_ERR_CAT_MSG,l495_ERR_CAT_NET};
l24_typedef le_struct l1108___my_ns_msg{li_const l97_u_char*l766__msg
, *l436__eom;l1113_u_int16_t l994__id,l1036__flags,l481__counts[
l370_ns_s_max];li_const l97_u_char*l736__sections[l370_ns_s_max];
l313_ns_sect l876__sect;la_int l350__rrnum;li_const l97_u_char*
l172__msg_ptr;}l351_my_ns_msg;la_int l969_my_ns_initparse(li_const
l97_u_char*l39_msg,la_int l865_msglen,l351_my_ns_msg*l28_handle);
la_int l917_my_ns_parserr(l351_my_ns_msg*l28_handle,l313_ns_sect
l193_section,la_int l316_rrnum,l916_ns_rr*l252_rr);
la_int l560_query_server_addr(le_struct l290_sockaddr_in6
l293_addr_list[],la_int*l669_p_addr_cnt,li_const lj_char*
l76_domain_name,la_int l691_max_retry);
#include"unmobric.h"
#include"log.h"
#include"mobric.h"
la_int l560_query_server_addr(le_struct l290_sockaddr_in6
l293_addr_list[],la_int*l669_p_addr_cnt,li_const lj_char*
l76_domain_name,la_int l691_max_retry){le_struct l854_addrinfo
l378_hints;le_struct l854_addrinfo*l61_result;le_struct l854_addrinfo
 *lc_p;lj_char l74_ip_addr[40];la_int ld_i;la_int l129_addr_cnt;
la_int l8_ret;l246_LOGG_FUNC_IN();l129_addr_cnt=0;l8_ret=((0<<31)|(
l53_ERR_LV_DBG<<28)|(l37_ERR_CAT_GENERAL<<14)|0x00);l118_do{lf_if(
l76_domain_name==lu_NULL){l8_ret=((1<<31)|(l69_ERR_LV_ERR<<28)|(
l37_ERR_CAT_GENERAL<<14)|0x04);ly_break;}l86_memset(&l378_hints,0,
lw_sizeof(le_struct l854_addrinfo));l378_hints.l1105_ai_family=
l1176_AF_UNSPEC;l378_hints.l1167_ai_flags=l1142_AI_CANONNAME;
l378_hints.l1127_ai_socktype=l400_SOCK_DGRAM;l378_hints.l520_ai_addr=
lu_NULL;l378_hints.l1150_ai_canonname=lu_NULL;l378_hints.
l1055_ai_next=lu_NULL;l21_for(ld_i=1;ld_i<=l691_max_retry;ld_i++){
l27_LOGG_INFO("\x51\x75\x65\x72\x79\x20\x44\x4e\x53\x20\x73\x65\x72"
"\x76\x65\x72\x20\x66\x6f\x72\x20\x64\x6f\x6d\x61\x69\x6e\x20\x6e\x61"
"\x6d\x65\x3a\x20\x25\x73\x2c\x20\x23\x25\x64",l76_domain_name,ld_i);
lf_if(!l1149_getaddrinfo(l76_domain_name,lu_NULL,&l378_hints,&
l61_result)){ly_break;}}lf_if(ld_i>l691_max_retry){l142_LOGG_ERRNO(""
"\x67\x65\x74\x61\x64\x64\x72\x69\x6e\x66\x6f");l8_ret=((1<<31)|(
l69_ERR_LV_ERR<<28)|(l495_ERR_CAT_NET<<14)|0x00);ly_break;}l21_for(
lc_p=l61_result;lc_p!=lu_NULL&&l129_addr_cnt< *l669_p_addr_cnt;lc_p=
lc_p->l1055_ai_next){l107_switch(lc_p->l1105_ai_family){l7_case
l145_AF_INET:{l790_inet_ntop(l145_AF_INET,&((le_struct
l104_sockaddr_in* )lc_p->l520_ai_addr)->l371_sin_addr,l74_ip_addr,
lw_sizeof(l74_ip_addr));lf_if((((le_struct l104_sockaddr_in* )lc_p->
l520_ai_addr)->l371_sin_addr.l594_s_addr&0xFF)==0x7F){lc_p=lu_NULL;}
l3_else{l109_memcpy(&l293_addr_list[l129_addr_cnt++],lc_p->
l520_ai_addr,lc_p->l1103_ai_addrlen);}l27_LOGG_INFO("\x49\x50\x76\x34"
"\x3a\x20\x69\x70\x20\x61\x64\x64\x72\x65\x73\x73\x20\x23\x25\x64\x3a"
"\x20\x25\x73",l129_addr_cnt+1,l74_ip_addr);ly_break;}l7_case
l445_AF_INET6:{l790_inet_ntop(l445_AF_INET6,&((le_struct
l290_sockaddr_in6* )lc_p->l520_ai_addr)->l795_sin6_addr,l74_ip_addr,
lw_sizeof(l74_ip_addr));lf_if(l1168_memcmp(&l1118_in6addr_loopback,&(
(le_struct l290_sockaddr_in6* )lc_p->l520_ai_addr)->l795_sin6_addr,
lw_sizeof(l1118_in6addr_loopback))==0){lc_p=lu_NULL;}l3_else{
l109_memcpy(&l293_addr_list[l129_addr_cnt++],lc_p->l520_ai_addr,lc_p
->l1103_ai_addrlen);}l27_LOGG_INFO("\x49\x50\x76\x36\x3a\x20\x69\x70"
"\x20\x61\x64\x64\x72\x65\x73\x73\x20\x23\x25\x64\x3a\x20\x25\x73",
l129_addr_cnt+1,l74_ip_addr);ly_break;}}lf_if(lc_p==lu_NULL){
l129_addr_cnt=0;ly_break;}}l1141_freeaddrinfo(l61_result);}l62_while(
0); *l669_p_addr_cnt=l129_addr_cnt;l240_LOGG_FUNC_OUT();lq_return
l8_ret;}
