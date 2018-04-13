#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<sys/time.h>
#include"mobric.h"
lb_void l484_randomize(lb_void);la_int l386_get_random(lb_void);
lb_void l731_load_random_list(la_int lz_list[],la_int*l35_p_cnt,
la_int l628_base,la_int l339_range);l17_int64_t
l723_get_usec_from_timeval(li_const le_struct l146_timeval*
l283_p_timeval);lb_void l557_get_timeval_from_usec(le_struct
l146_timeval*l283_p_timeval,l17_int64_t l544_usec);l17_int64_t
l344_get_time_now_usec(lb_void);l13_enum{l53_ERR_LV_DBG,
l535_ERR_LV_INFO,l234_ERR_LV_WARN,l69_ERR_LV_ERR};l13_enum{
l37_ERR_CAT_GENERAL,l347_ERR_CAT_DAEMON,l575_ERR_CAT_DPM_CFG,
l87_ERR_CAT_MSG,l495_ERR_CAT_NET};
#include"unmobric.h"
#include"log.h"
#include"mobric.h"
lb_void l484_randomize(lb_void){l1136_srand(l317_time(lu_NULL));}
la_int l386_get_random(lb_void){lq_return l1131_rand();}lb_void
l731_load_random_list(la_int lz_list[],la_int*l35_p_cnt,la_int
l628_base,la_int l339_range){la_int ld_i;la_int l639_swap_index;
la_int l173_temp;lf_if(l339_range> *l35_p_cnt){l339_range= *l35_p_cnt
;}l21_for(ld_i=0;ld_i<l339_range;ld_i++){lz_list[ld_i]=l628_base+ld_i
;}l484_randomize();l21_for(ld_i=0;ld_i<l339_range;ld_i++){
l639_swap_index=l386_get_random()%l339_range;lf_if(ld_i!=
l639_swap_index){l173_temp=lz_list[ld_i];lz_list[ld_i]=lz_list[
l639_swap_index];lz_list[l639_swap_index]=l173_temp;}} *l35_p_cnt=
l339_range;}l17_int64_t l723_get_usec_from_timeval(li_const le_struct
l146_timeval*l283_p_timeval){lq_return(l17_int64_t)l283_p_timeval->
l384_tv_sec*1000000+(l17_int64_t)l283_p_timeval->l366_tv_usec;}
lb_void l557_get_timeval_from_usec(le_struct l146_timeval*
l283_p_timeval,l17_int64_t l544_usec){l283_p_timeval->l384_tv_sec=
l544_usec/1000000;l283_p_timeval->l366_tv_usec=l544_usec%1000000;}
l17_int64_t l344_get_time_now_usec(lb_void){le_struct l146_timeval
l477_now;l1086_gettimeofday(&l477_now,lu_NULL);lq_return
l723_get_usec_from_timeval(&l477_now);}
