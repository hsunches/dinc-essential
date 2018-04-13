#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<arpa/nameser.h>
#include<resolv.h>
#include"mobric.h"
l24_typedef le_struct l1108___my_ns_msg{li_const l97_u_char*l766__msg
, *l436__eom;l1113_u_int16_t l994__id,l1036__flags,l481__counts[
l370_ns_s_max];li_const l97_u_char*l736__sections[l370_ns_s_max];
l313_ns_sect l876__sect;la_int l350__rrnum;li_const l97_u_char*
l172__msg_ptr;}l351_my_ns_msg;la_int l969_my_ns_initparse(li_const
l97_u_char*l39_msg,la_int l865_msglen,l351_my_ns_msg*l28_handle);
la_int l917_my_ns_parserr(l351_my_ns_msg*l28_handle,l313_ns_sect
l193_section,la_int l316_rrnum,l916_ns_rr*l252_rr);lk_static la_int
l842_my_ns_skiprr(li_const l97_u_char*l212_ptr,li_const l97_u_char*
l150_eom,l313_ns_sect l193_section,la_int l58_count);lk_static la_int
l944_my_dn_skipname(li_const l97_u_char*l212_ptr,li_const l97_u_char*
l150_eom);lk_static la_int l913_my_ns_name_skip(li_const l97_u_char* *
l794_ptrptr,li_const l97_u_char*l150_eom);lk_static la_int
l1007_my_labellen(li_const l97_u_char*l765_lp);lk_static lb_void
l576_my_setsection(l351_my_ns_msg*l39_msg,l313_ns_sect l754_sect);
la_int l969_my_ns_initparse(li_const l97_u_char*l39_msg,la_int
l865_msglen,l351_my_ns_msg*l28_handle){li_const l97_u_char*l150_eom=
l39_msg+l865_msglen;la_int ld_i;l86_memset(l28_handle,0x5e,lw_sizeof*
l28_handle);l28_handle->l766__msg=l39_msg;l28_handle->l436__eom=
l150_eom;lf_if(l39_msg+l374_NS_INT16SZ>l150_eom)l118_do{l134_errno=
l269_EMSGSIZE;lq_return(-1);}l62_while(0);l496_NS_GET16(l28_handle->
l994__id,l39_msg);lf_if(l39_msg+l374_NS_INT16SZ>l150_eom)l118_do{
l134_errno=l269_EMSGSIZE;lq_return(-1);}l62_while(0);l496_NS_GET16(
l28_handle->l1036__flags,l39_msg);l21_for(ld_i=0;ld_i<l370_ns_s_max;
ld_i++){lf_if(l39_msg+l374_NS_INT16SZ>l150_eom)l118_do{l134_errno=
l269_EMSGSIZE;lq_return(-1);}l62_while(0);l496_NS_GET16(l28_handle->
l481__counts[ld_i],l39_msg);}l21_for(ld_i=0;ld_i<l370_ns_s_max;ld_i++
)lf_if(l28_handle->l481__counts[ld_i]==0)l28_handle->l736__sections[
ld_i]=lu_NULL;l3_else{la_int l5_b=l842_my_ns_skiprr(l39_msg,l150_eom,
(l313_ns_sect)ld_i,l28_handle->l481__counts[ld_i]);lf_if(l5_b<0)lq_return
(-1);l28_handle->l736__sections[ld_i]=l39_msg;l39_msg+=l5_b;}lf_if(
l39_msg!=l150_eom)l118_do{l134_errno=l269_EMSGSIZE;lq_return(-1);}
l62_while(0);l576_my_setsection(l28_handle,l370_ns_s_max);lq_return(0
);}la_int l917_my_ns_parserr(l351_my_ns_msg*l28_handle,l313_ns_sect
l193_section,la_int l316_rrnum,l916_ns_rr*l252_rr){la_int l5_b;la_int
l935_tmp;l935_tmp=l193_section;lf_if(l935_tmp<0||l193_section>=
l370_ns_s_max)l118_do{l134_errno=l1047_ENODEV;lq_return(-1);}
l62_while(0);lf_if(l193_section!=l28_handle->l876__sect)l576_my_setsection
(l28_handle,l193_section);lf_if(l316_rrnum==-1)l316_rrnum=l28_handle
->l350__rrnum;lf_if(l316_rrnum<0||l316_rrnum>=l28_handle->
l481__counts[(la_int)l193_section])l118_do{l134_errno=l1047_ENODEV;
lq_return(-1);}l62_while(0);lf_if(l316_rrnum<l28_handle->l350__rrnum)l576_my_setsection
(l28_handle,l193_section);lf_if(l316_rrnum>l28_handle->l350__rrnum){
l5_b=l842_my_ns_skiprr(l28_handle->l172__msg_ptr,l28_handle->
l436__eom,l193_section,l316_rrnum-l28_handle->l350__rrnum);lf_if(l5_b
<0)lq_return(-1);l28_handle->l172__msg_ptr+=l5_b;l28_handle->
l350__rrnum=l316_rrnum;}l5_b=l1166_dn_expand(l28_handle->l766__msg,
l28_handle->l436__eom,l28_handle->l172__msg_ptr,l252_rr->l194_name,
l1173_NS_MAXDNAME);lf_if(l5_b<0)lq_return(-1);l28_handle->
l172__msg_ptr+=l5_b;lf_if(l28_handle->l172__msg_ptr+l374_NS_INT16SZ+
l374_NS_INT16SZ>l28_handle->l436__eom)l118_do{l134_errno=
l269_EMSGSIZE;lq_return(-1);}l62_while(0);l496_NS_GET16(l252_rr->
l9_type,l28_handle->l172__msg_ptr);l496_NS_GET16(l252_rr->
l1139_rr_class,l28_handle->l172__msg_ptr);lf_if(l193_section==
l1110_ns_s_qd){l252_rr->l1094_ttl=0;l252_rr->l472_rdlength=0;l252_rr
->l1117_rdata=lu_NULL;}l3_else{lf_if(l28_handle->l172__msg_ptr+
l902_NS_INT32SZ+l374_NS_INT16SZ>l28_handle->l436__eom)l118_do{
l134_errno=l269_EMSGSIZE;lq_return(-1);}l62_while(0);l1153_NS_GET32(
l252_rr->l1094_ttl,l28_handle->l172__msg_ptr);l496_NS_GET16(l252_rr->
l472_rdlength,l28_handle->l172__msg_ptr);lf_if(l28_handle->
l172__msg_ptr+l252_rr->l472_rdlength>l28_handle->l436__eom)l118_do{
l134_errno=l269_EMSGSIZE;lq_return(-1);}l62_while(0);l252_rr->
l1117_rdata=l28_handle->l172__msg_ptr;l28_handle->l172__msg_ptr+=
l252_rr->l472_rdlength;}lf_if(++l28_handle->l350__rrnum>l28_handle->
l481__counts[(la_int)l193_section])l576_my_setsection(l28_handle,(
l313_ns_sect)((la_int)l193_section+1));lq_return(0);}lk_static la_int
l842_my_ns_skiprr(li_const l97_u_char*l212_ptr,li_const l97_u_char*
l150_eom,l313_ns_sect l193_section,la_int l58_count){li_const
l97_u_char*l1101_optr=l212_ptr;l21_for(;l58_count>0;l58_count--){
la_int l5_b,l472_rdlength;l5_b=l944_my_dn_skipname(l212_ptr,l150_eom);
lf_if(l5_b<0){l118_do{l134_errno=l269_EMSGSIZE;lq_return(-1);}
l62_while(0);}l212_ptr+=l5_b+l374_NS_INT16SZ+l374_NS_INT16SZ;lf_if(
l193_section!=l1110_ns_s_qd){lf_if(l212_ptr+l902_NS_INT32SZ+
l374_NS_INT16SZ>l150_eom){l118_do{l134_errno=l269_EMSGSIZE;lq_return(
-1);}l62_while(0);}l212_ptr+=l902_NS_INT32SZ;l496_NS_GET16(
l472_rdlength,l212_ptr);l212_ptr+=l472_rdlength;}}lf_if(l212_ptr>
l150_eom){l118_do{l134_errno=l269_EMSGSIZE;lq_return(-1);}l62_while(0
);}lq_return(l212_ptr-l1101_optr);}lk_static la_int
l944_my_dn_skipname(li_const l97_u_char*l212_ptr,li_const l97_u_char*
l150_eom){li_const l97_u_char*l1093_saveptr=l212_ptr;lf_if(
l913_my_ns_name_skip(&l212_ptr,l150_eom)==-1)lq_return(-1);lq_return(
l212_ptr-l1093_saveptr);}lk_static la_int l913_my_ns_name_skip(
li_const l97_u_char* *l794_ptrptr,li_const l97_u_char*l150_eom){
li_const l97_u_char*l324_cp;l1145_u_int l70_n;la_int l405_l;l324_cp= *
l794_ptrptr;l62_while(l324_cp<l150_eom&&(l70_n= *l324_cp++)!=0){
l107_switch(l70_n&l643_NS_CMPRSFLGS){l7_case 0:l324_cp+=l70_n;
l288_continue;l7_case 0x40:lf_if((l405_l=l1007_my_labellen(l324_cp-1))<
0){l118_do{l134_errno=l269_EMSGSIZE;lq_return(-1);}l62_while(0);}
l324_cp+=l405_l;l288_continue;l7_case l643_NS_CMPRSFLGS:l324_cp++;
ly_break;l238_default:l118_do{l134_errno=l269_EMSGSIZE;lq_return(-1);
}l62_while(0);ly_break;}ly_break;}lf_if(l324_cp>l150_eom){l118_do{
l134_errno=l269_EMSGSIZE;lq_return(-1);}l62_while(0);} *l794_ptrptr=
l324_cp;lq_return(0);}lk_static la_int l1007_my_labellen(li_const
l97_u_char*l765_lp){la_int l883_bitlen;l97_u_char l405_l= *l765_lp;
lf_if((l405_l&l643_NS_CMPRSFLGS)==l643_NS_CMPRSFLGS){lq_return(-1);}
lf_if((l405_l&l643_NS_CMPRSFLGS)==0x40){lf_if(l405_l==0x41){lf_if((
l883_bitlen= * (l765_lp+1))==0)l883_bitlen=256;lq_return((l883_bitlen
+7)/8+1);}lq_return(-1);}lq_return(l405_l);}lk_static lb_void
l576_my_setsection(l351_my_ns_msg*l39_msg,l313_ns_sect l754_sect){
l39_msg->l876__sect=l754_sect;lf_if(l754_sect==l370_ns_s_max){l39_msg
->l350__rrnum=-1;l39_msg->l172__msg_ptr=lu_NULL;}l3_else{l39_msg->
l350__rrnum=0;l39_msg->l172__msg_ptr=l39_msg->l736__sections[(la_int)l754_sect
];}}
