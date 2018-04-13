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
#include"unmobric.h"
#include<string.h>
#include"mobric.h"
lk_static lb_void l904_md5_process(l249_md5_state_t*l66_pms,li_const
l115_md5_byte_t*ln_data){l34_md5_word_t l10_a=l66_pms->l229_abcd[0],
l5_b=l66_pms->l229_abcd[1],l11_c=l66_pms->l229_abcd[2],l6_d=l66_pms->
l229_abcd[3];l34_md5_word_t ls_t;l34_md5_word_t l671_xbuf[16];
li_const l34_md5_word_t*l23_X;{lk_static li_const la_int l1083_w=1;
lf_if( * ((li_const l115_md5_byte_t* )&l1083_w)){lf_if(!((ln_data-(
li_const l115_md5_byte_t* )0)&3)){l23_X=(li_const l34_md5_word_t* )ln_data
;}l3_else{l109_memcpy(l671_xbuf,ln_data,64);l23_X=l671_xbuf;}}l3_else
{li_const l115_md5_byte_t*l611_xp=ln_data;la_int ld_i;l23_X=l671_xbuf
;l21_for(ld_i=0;ld_i<16;++ld_i,l611_xp+=4)l671_xbuf[ld_i]=l611_xp[0]+
(l611_xp[1]<<8)+(l611_xp[2]<<16)+(l611_xp[3]<<24);}}ls_t=l10_a+(((
l5_b)&(l11_c))|(~(l5_b)&(l6_d)))+l23_X[0]+(((l34_md5_word_t)~0)^
0x28955b87);l10_a=(((ls_t)<<(7))|((ls_t)>>(32-(7))))+l5_b;ls_t=l6_d+(
((l10_a)&(l5_b))|(~(l10_a)&(l11_c)))+l23_X[1]+(((l34_md5_word_t)~0)^
0x173848a9);l6_d=(((ls_t)<<(12))|((ls_t)>>(32-(12))))+l10_a;ls_t=
l11_c+(((l6_d)&(l10_a))|(~(l6_d)&(l5_b)))+l23_X[2]+0x242070db;l11_c=(
((ls_t)<<(17))|((ls_t)>>(32-(17))))+l6_d;ls_t=l5_b+(((l11_c)&(l6_d))|
(~(l11_c)&(l10_a)))+l23_X[3]+(((l34_md5_word_t)~0)^0x3e423111);l5_b=(
((ls_t)<<(22))|((ls_t)>>(32-(22))))+l11_c;ls_t=l10_a+(((l5_b)&(l11_c))|
(~(l5_b)&(l6_d)))+l23_X[4]+(((l34_md5_word_t)~0)^0x0a83f050);l10_a=((
(ls_t)<<(7))|((ls_t)>>(32-(7))))+l5_b;ls_t=l6_d+(((l10_a)&(l5_b))|(~(
l10_a)&(l11_c)))+l23_X[5]+0x4787c62a;l6_d=(((ls_t)<<(12))|((ls_t)>>(
32-(12))))+l10_a;ls_t=l11_c+(((l6_d)&(l10_a))|(~(l6_d)&(l5_b)))+l23_X
[6]+(((l34_md5_word_t)~0)^0x57cfb9ec);l11_c=(((ls_t)<<(17))|((ls_t)>>
(32-(17))))+l6_d;ls_t=l5_b+(((l11_c)&(l6_d))|(~(l11_c)&(l10_a)))+
l23_X[7]+(((l34_md5_word_t)~0)^0x02b96afe);l5_b=(((ls_t)<<(22))|((
ls_t)>>(32-(22))))+l11_c;ls_t=l10_a+(((l5_b)&(l11_c))|(~(l5_b)&(l6_d)))+
l23_X[8]+0x698098d8;l10_a=(((ls_t)<<(7))|((ls_t)>>(32-(7))))+l5_b;
ls_t=l6_d+(((l10_a)&(l5_b))|(~(l10_a)&(l11_c)))+l23_X[9]+(((
l34_md5_word_t)~0)^0x74bb0850);l6_d=(((ls_t)<<(12))|((ls_t)>>(32-(12))))+
l10_a;ls_t=l11_c+(((l6_d)&(l10_a))|(~(l6_d)&(l5_b)))+l23_X[10]+(((
l34_md5_word_t)~0)^0x0000a44e);l11_c=(((ls_t)<<(17))|((ls_t)>>(32-(17
))))+l6_d;ls_t=l5_b+(((l11_c)&(l6_d))|(~(l11_c)&(l10_a)))+l23_X[11]+(
((l34_md5_word_t)~0)^0x76a32841);l5_b=(((ls_t)<<(22))|((ls_t)>>(32-(
22))))+l11_c;ls_t=l10_a+(((l5_b)&(l11_c))|(~(l5_b)&(l6_d)))+l23_X[12]
+0x6b901122;l10_a=(((ls_t)<<(7))|((ls_t)>>(32-(7))))+l5_b;ls_t=l6_d+(
((l10_a)&(l5_b))|(~(l10_a)&(l11_c)))+l23_X[13]+(((l34_md5_word_t)~0)^
0x02678e6c);l6_d=(((ls_t)<<(12))|((ls_t)>>(32-(12))))+l10_a;ls_t=
l11_c+(((l6_d)&(l10_a))|(~(l6_d)&(l5_b)))+l23_X[14]+(((l34_md5_word_t
)~0)^0x5986bc71);l11_c=(((ls_t)<<(17))|((ls_t)>>(32-(17))))+l6_d;ls_t
=l5_b+(((l11_c)&(l6_d))|(~(l11_c)&(l10_a)))+l23_X[15]+0x49b40821;l5_b
=(((ls_t)<<(22))|((ls_t)>>(32-(22))))+l11_c;ls_t=l10_a+(((l5_b)&(l6_d
))|((l11_c)&~(l6_d)))+l23_X[1]+(((l34_md5_word_t)~0)^0x09e1da9d);
l10_a=(((ls_t)<<(5))|((ls_t)>>(32-(5))))+l5_b;ls_t=l6_d+(((l10_a)&(
l11_c))|((l5_b)&~(l11_c)))+l23_X[6]+(((l34_md5_word_t)~0)^0x3fbf4cbf);
l6_d=(((ls_t)<<(9))|((ls_t)>>(32-(9))))+l10_a;ls_t=l11_c+(((l6_d)&(
l5_b))|((l10_a)&~(l5_b)))+l23_X[11]+0x265e5a51;l11_c=(((ls_t)<<(14))|
((ls_t)>>(32-(14))))+l6_d;ls_t=l5_b+(((l11_c)&(l10_a))|((l6_d)&~(
l10_a)))+l23_X[0]+(((l34_md5_word_t)~0)^0x16493855);l5_b=(((ls_t)<<(
20))|((ls_t)>>(32-(20))))+l11_c;ls_t=l10_a+(((l5_b)&(l6_d))|((l11_c)&
~(l6_d)))+l23_X[5]+(((l34_md5_word_t)~0)^0x29d0efa2);l10_a=(((ls_t)<<
(5))|((ls_t)>>(32-(5))))+l5_b;ls_t=l6_d+(((l10_a)&(l11_c))|((l5_b)&~(
l11_c)))+l23_X[10]+0x02441453;l6_d=(((ls_t)<<(9))|((ls_t)>>(32-(9))))+
l10_a;ls_t=l11_c+(((l6_d)&(l5_b))|((l10_a)&~(l5_b)))+l23_X[15]+(((
l34_md5_word_t)~0)^0x275e197e);l11_c=(((ls_t)<<(14))|((ls_t)>>(32-(14
))))+l6_d;ls_t=l5_b+(((l11_c)&(l10_a))|((l6_d)&~(l10_a)))+l23_X[4]+((
(l34_md5_word_t)~0)^0x182c0437);l5_b=(((ls_t)<<(20))|((ls_t)>>(32-(20
))))+l11_c;ls_t=l10_a+(((l5_b)&(l6_d))|((l11_c)&~(l6_d)))+l23_X[9]+
0x21e1cde6;l10_a=(((ls_t)<<(5))|((ls_t)>>(32-(5))))+l5_b;ls_t=l6_d+((
(l10_a)&(l11_c))|((l5_b)&~(l11_c)))+l23_X[14]+(((l34_md5_word_t)~0)^
0x3cc8f829);l6_d=(((ls_t)<<(9))|((ls_t)>>(32-(9))))+l10_a;ls_t=l11_c+
(((l6_d)&(l5_b))|((l10_a)&~(l5_b)))+l23_X[3]+(((l34_md5_word_t)~0)^
0x0b2af278);l11_c=(((ls_t)<<(14))|((ls_t)>>(32-(14))))+l6_d;ls_t=l5_b
+(((l11_c)&(l10_a))|((l6_d)&~(l10_a)))+l23_X[8]+0x455a14ed;l5_b=(((
ls_t)<<(20))|((ls_t)>>(32-(20))))+l11_c;ls_t=l10_a+(((l5_b)&(l6_d))|(
(l11_c)&~(l6_d)))+l23_X[13]+(((l34_md5_word_t)~0)^0x561c16fa);l10_a=(
((ls_t)<<(5))|((ls_t)>>(32-(5))))+l5_b;ls_t=l6_d+(((l10_a)&(l11_c))|(
(l5_b)&~(l11_c)))+l23_X[2]+(((l34_md5_word_t)~0)^0x03105c07);l6_d=(((
ls_t)<<(9))|((ls_t)>>(32-(9))))+l10_a;ls_t=l11_c+(((l6_d)&(l5_b))|((
l10_a)&~(l5_b)))+l23_X[7]+0x676f02d9;l11_c=(((ls_t)<<(14))|((ls_t)>>(
32-(14))))+l6_d;ls_t=l5_b+(((l11_c)&(l10_a))|((l6_d)&~(l10_a)))+l23_X
[12]+(((l34_md5_word_t)~0)^0x72d5b375);l5_b=(((ls_t)<<(20))|((ls_t)>>
(32-(20))))+l11_c;ls_t=l10_a+((l5_b)^(l11_c)^(l6_d))+l23_X[5]+(((
l34_md5_word_t)~0)^0x0005c6bd);l10_a=(((ls_t)<<(4))|((ls_t)>>(32-(4))))+
l5_b;ls_t=l6_d+((l10_a)^(l5_b)^(l11_c))+l23_X[8]+(((l34_md5_word_t)~0
)^0x788e097e);l6_d=(((ls_t)<<(11))|((ls_t)>>(32-(11))))+l10_a;ls_t=
l11_c+((l6_d)^(l10_a)^(l5_b))+l23_X[11]+0x6d9d6122;l11_c=(((ls_t)<<(
16))|((ls_t)>>(32-(16))))+l6_d;ls_t=l5_b+((l11_c)^(l6_d)^(l10_a))+
l23_X[14]+(((l34_md5_word_t)~0)^0x021ac7f3);l5_b=(((ls_t)<<(23))|((
ls_t)>>(32-(23))))+l11_c;ls_t=l10_a+((l5_b)^(l11_c)^(l6_d))+l23_X[1]+
(((l34_md5_word_t)~0)^0x5b4115bb);l10_a=(((ls_t)<<(4))|((ls_t)>>(32-(
4))))+l5_b;ls_t=l6_d+((l10_a)^(l5_b)^(l11_c))+l23_X[4]+0x4bdecfa9;
l6_d=(((ls_t)<<(11))|((ls_t)>>(32-(11))))+l10_a;ls_t=l11_c+((l6_d)^(
l10_a)^(l5_b))+l23_X[7]+(((l34_md5_word_t)~0)^0x0944b49f);l11_c=(((
ls_t)<<(16))|((ls_t)>>(32-(16))))+l6_d;ls_t=l5_b+((l11_c)^(l6_d)^(
l10_a))+l23_X[10]+(((l34_md5_word_t)~0)^0x4140438f);l5_b=(((ls_t)<<(
23))|((ls_t)>>(32-(23))))+l11_c;ls_t=l10_a+((l5_b)^(l11_c)^(l6_d))+
l23_X[13]+0x289b7ec6;l10_a=(((ls_t)<<(4))|((ls_t)>>(32-(4))))+l5_b;
ls_t=l6_d+((l10_a)^(l5_b)^(l11_c))+l23_X[0]+(((l34_md5_word_t)~0)^
0x155ed805);l6_d=(((ls_t)<<(11))|((ls_t)>>(32-(11))))+l10_a;ls_t=
l11_c+((l6_d)^(l10_a)^(l5_b))+l23_X[3]+(((l34_md5_word_t)~0)^
0x2b10cf7a);l11_c=(((ls_t)<<(16))|((ls_t)>>(32-(16))))+l6_d;ls_t=l5_b
+((l11_c)^(l6_d)^(l10_a))+l23_X[6]+0x04881d05;l5_b=(((ls_t)<<(23))|((
ls_t)>>(32-(23))))+l11_c;ls_t=l10_a+((l5_b)^(l11_c)^(l6_d))+l23_X[9]+
(((l34_md5_word_t)~0)^0x262b2fc6);l10_a=(((ls_t)<<(4))|((ls_t)>>(32-(
4))))+l5_b;ls_t=l6_d+((l10_a)^(l5_b)^(l11_c))+l23_X[12]+(((
l34_md5_word_t)~0)^0x1924661a);l6_d=(((ls_t)<<(11))|((ls_t)>>(32-(11))))+
l10_a;ls_t=l11_c+((l6_d)^(l10_a)^(l5_b))+l23_X[15]+0x1fa27cf8;l11_c=(
((ls_t)<<(16))|((ls_t)>>(32-(16))))+l6_d;ls_t=l5_b+((l11_c)^(l6_d)^(
l10_a))+l23_X[2]+(((l34_md5_word_t)~0)^0x3b53a99a);l5_b=(((ls_t)<<(23
))|((ls_t)>>(32-(23))))+l11_c;ls_t=l10_a+((l11_c)^((l5_b)|~(l6_d)))+
l23_X[0]+(((l34_md5_word_t)~0)^0x0bd6ddbb);l10_a=(((ls_t)<<(6))|((
ls_t)>>(32-(6))))+l5_b;ls_t=l6_d+((l5_b)^((l10_a)|~(l11_c)))+l23_X[7]
+0x432aff97;l6_d=(((ls_t)<<(10))|((ls_t)>>(32-(10))))+l10_a;ls_t=
l11_c+((l10_a)^((l6_d)|~(l5_b)))+l23_X[14]+(((l34_md5_word_t)~0)^
0x546bdc58);l11_c=(((ls_t)<<(15))|((ls_t)>>(32-(15))))+l6_d;ls_t=l5_b
+((l6_d)^((l11_c)|~(l10_a)))+l23_X[5]+(((l34_md5_word_t)~0)^
0x036c5fc6);l5_b=(((ls_t)<<(21))|((ls_t)>>(32-(21))))+l11_c;ls_t=
l10_a+((l11_c)^((l5_b)|~(l6_d)))+l23_X[12]+0x655b59c3;l10_a=(((ls_t)<<
(6))|((ls_t)>>(32-(6))))+l5_b;ls_t=l6_d+((l5_b)^((l10_a)|~(l11_c)))+
l23_X[3]+(((l34_md5_word_t)~0)^0x70f3336d);l6_d=(((ls_t)<<(10))|((
ls_t)>>(32-(10))))+l10_a;ls_t=l11_c+((l10_a)^((l6_d)|~(l5_b)))+l23_X[
10]+(((l34_md5_word_t)~0)^0x00100b82);l11_c=(((ls_t)<<(15))|((ls_t)>>
(32-(15))))+l6_d;ls_t=l5_b+((l6_d)^((l11_c)|~(l10_a)))+l23_X[1]+(((
l34_md5_word_t)~0)^0x7a7ba22e);l5_b=(((ls_t)<<(21))|((ls_t)>>(32-(21))))+
l11_c;ls_t=l10_a+((l11_c)^((l5_b)|~(l6_d)))+l23_X[8]+0x6fa87e4f;l10_a
=(((ls_t)<<(6))|((ls_t)>>(32-(6))))+l5_b;ls_t=l6_d+((l5_b)^((l10_a)|~
(l11_c)))+l23_X[15]+(((l34_md5_word_t)~0)^0x01d3191f);l6_d=(((ls_t)<<
(10))|((ls_t)>>(32-(10))))+l10_a;ls_t=l11_c+((l10_a)^((l6_d)|~(l5_b)))+
l23_X[6]+(((l34_md5_word_t)~0)^0x5cfebceb);l11_c=(((ls_t)<<(15))|((
ls_t)>>(32-(15))))+l6_d;ls_t=l5_b+((l6_d)^((l11_c)|~(l10_a)))+l23_X[
13]+0x4e0811a1;l5_b=(((ls_t)<<(21))|((ls_t)>>(32-(21))))+l11_c;ls_t=
l10_a+((l11_c)^((l5_b)|~(l6_d)))+l23_X[4]+(((l34_md5_word_t)~0)^
0x08ac817d);l10_a=(((ls_t)<<(6))|((ls_t)>>(32-(6))))+l5_b;ls_t=l6_d+(
(l5_b)^((l10_a)|~(l11_c)))+l23_X[11]+(((l34_md5_word_t)~0)^0x42c50dca
);l6_d=(((ls_t)<<(10))|((ls_t)>>(32-(10))))+l10_a;ls_t=l11_c+((l10_a)^
((l6_d)|~(l5_b)))+l23_X[2]+0x2ad7d2bb;l11_c=(((ls_t)<<(15))|((ls_t)>>
(32-(15))))+l6_d;ls_t=l5_b+((l6_d)^((l11_c)|~(l10_a)))+l23_X[9]+(((
l34_md5_word_t)~0)^0x14792c6e);l5_b=(((ls_t)<<(21))|((ls_t)>>(32-(21))))+
l11_c;l66_pms->l229_abcd[0]+=l10_a;l66_pms->l229_abcd[1]+=l5_b;
l66_pms->l229_abcd[2]+=l11_c;l66_pms->l229_abcd[3]+=l6_d;}lb_void
l631_md5_init(l249_md5_state_t*l66_pms){l66_pms->l58_count[0]=l66_pms
->l58_count[1]=0;l66_pms->l229_abcd[0]=0x67452301;l66_pms->l229_abcd[
1]=((l34_md5_word_t)~0)^0x10325476;l66_pms->l229_abcd[2]=((
l34_md5_word_t)~0)^0x67452301;l66_pms->l229_abcd[3]=0x10325476;}
lb_void l407_md5_append(l249_md5_state_t*l66_pms,li_const
l115_md5_byte_t*ln_data,la_int l383_nbytes){li_const l115_md5_byte_t*
lc_p=ln_data;la_int l610_left=l383_nbytes;la_int l326_offset=(l66_pms
->l58_count[0]>>3)&63;l34_md5_word_t l1024_nbits=(l34_md5_word_t)(
l383_nbytes<<3);lf_if(l383_nbytes<=0)lq_return;l66_pms->l58_count[1]
+=l383_nbytes>>29;l66_pms->l58_count[0]+=l1024_nbits;lf_if(l66_pms->
l58_count[0]<l1024_nbits)l66_pms->l58_count[1]++;lf_if(l326_offset){
la_int l684_copy=(l326_offset+l383_nbytes>64?64-l326_offset:
l383_nbytes);l109_memcpy(l66_pms->l72_buf+l326_offset,lc_p,l684_copy);
lf_if(l326_offset+l684_copy<64)lq_return;lc_p+=l684_copy;l610_left-=
l684_copy;l904_md5_process(l66_pms,l66_pms->l72_buf);}l21_for(;
l610_left>=64;lc_p+=64,l610_left-=64)l904_md5_process(l66_pms,lc_p);
lf_if(l610_left)l109_memcpy(l66_pms->l72_buf,lc_p,l610_left);}lb_void
l680_md5_finish(l249_md5_state_t*l66_pms,l115_md5_byte_t l261_digest[
16]){lk_static li_const l115_md5_byte_t l1049_pad[64]={0x80,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};l115_md5_byte_t
ln_data[8];la_int ld_i;l21_for(ld_i=0;ld_i<8;++ld_i)ln_data[ld_i]=(
l115_md5_byte_t)(l66_pms->l58_count[ld_i>>2]>>((ld_i&3)<<3));
l407_md5_append(l66_pms,l1049_pad,((55-(l66_pms->l58_count[0]>>3))&63
)+1);l407_md5_append(l66_pms,ln_data,8);l21_for(ld_i=0;ld_i<16;++ld_i
)l261_digest[ld_i]=(l115_md5_byte_t)(l66_pms->l229_abcd[ld_i>>2]>>((
ld_i&3)<<3));}
