#!/bin/bash

project_root=$1

if [ ! -d "$project_root/dinc" ]; then
	echo "error! please ensure project/dinc is exist."
	exit 1
fi

ob_exe_root=$(pwd)'/cobf'
ob_exe="$ob_exe_root/cobf"
ob_preprocessor="$ob_exe_root/pp_gnu"

# ---------------------------------------------------------------------------------------------------
total_h1=''
total_s1=''
total_o6=''
total_include=''
dc_mod_list=$(ls $project_root/dinc/generic|grep -E 'dc|din')
for dc_mod in $dc_mod_list; do
	if [ -n "$2" ] && [ "$2" == "$dc_mod" ] || [ "$2" == "all" ]; then
		#header
		if [ "$dc_mod" == "din" ]; then
			header_list=$(ls $project_root/dinc/generic/din|grep '\.h')
		else
			header_list=$(ls $project_root/dinc/generic/$dc_mod|grep '\.h')
		fi
		
		h1=''
		for header in $header_list; do
			if [ -z "$h1" ]; then
				h1="-hi $header"
			else
				h1="$h1 -hi $header"
			fi
		done

		if [ -z "$total_h1" ]; then
			total_h1="$h1"
		else
			total_h1="$total_h1 $h1"
		fi

		# additional header
		hal_mod=''
		if [ "$dc_mod" == "din" ]; then
			h2="$h1 -hi $h_o1 -hi $h_o2 -hi $h_o4"
		elif [ "$dc_mod" == "dc_dev" ]; then
			h2="$h1 -hi $h_o1 -hi $h_o2 -hi $h_o3 -hi $h_o4 -hi $h_o5"
		else
			hal_mod=$(echo "$dc_mod"|cut -b 4-)
			h_o6=$(ls $project_root/dinc/hal/$hal_mod|grep 'data_'"$hal_mod")
			
			if [ -z "$total_o6" ]; then
				total_o6="-hi $h_o6"
			else
				total_o6+=" -hi $h_o6"
			fi
		fi

		# source
		if [ "$dc_mod" == "din" ]; then
			source_list=$(ls $project_root/dinc/generic/din|grep '\.c')
		else
			source_list=$(ls $project_root/dinc/generic/$dc_mod|grep '\.c')
		fi

		s1=''
		for source in $source_list; do
			if [ -z "$s1" ]; then
				s1="$source"
			else
				s1="$s1 $source"
			fi			
		done
		# total_s1+=$s1

		if [ -z "$total_s1" ]; then
			total_s1="$s1"
		else
			total_s1="$total_s1 $s1"
		fi

		# include
		ob_i2="$project_root/dinc/generic/$dc_mod"
		ob_i6="$project_root/dinc/hal/$hal_mod"

		if [ -z "$total_include" ]; then
			total_include="-i $ob_i2 -i $ob_i6"
		else
			total_include+=" -i $ob_i2 -i $ob_i6"
		fi
	fi
done

h_o1=$(ls $project_root/dinc/generic/include|grep 'util.h')
h_o2=$(ls $project_root/dinc/generic/include|grep 'msg_format')
h_o3=$(ls $project_root/dinc/hal/include|grep 'msg_hal')
h_o4=$(ls $project_root/dinc/generic/include|grep 'version.h')
h_o5=$(ls $project_root/dinc/hal/dev|grep 'data_dev.h')
# h_def=$(ls $project_root/dinc/generic/include|grep 'dc_definition')
total_h2="$total_h1 -hi $h_o1 -hi $h_o2 -hi $h_o3 -hi $h_o4 -hi $h_o5 $total_o6"

# add additional source
add_s_o1=$(ls $project_root/dinc/generic/include|grep 'util.c')
add_s_o2=$(ls $project_root/dinc/generic/include|grep 'version.c')
total_s2="$total_s1 $add_s_o1 $add_s_o2"

# token & macro
ob_t1="$ob_exe_root/c.tok"
ob_t2="$ob_exe_root/cansilib.tok"
ob_t3="$ob_exe_root/dc.tok"
ob_m1="$ob_exe_root/c.mak"
ob_m2="$ob_exe_root/dc.mak"
ob_p1="$ob_exe_root/dc.map"
ob_t_m="-t $ob_t1 -t $ob_t2 -t $ob_t3 -m $ob_m1 -m $ob_m2 -mi $ob_p1"
ob_file_list="$total_h2 $total_s2"

ob_i1="$project_root/dinc/generic/din"
ob_i3="$project_root/dinc/generic/include"
ob_i4="$project_root/dinc/hal/include"
ob_i5="$project_root/dinc/hal/dev"
total_include+=" -i $ob_i1 -i $ob_i3 -i $ob_i4 -i $ob_i5"

# output
ob_output="$project_root/dinc/generic_ob/din"
ob_include="$project_root/dinc/generic_ob/include"

mkdir -p $ob_output
mkdir -p $ob_include

# #obfuscation
$ob_exe $ob_t_m -di -v1 -o $ob_output -b -p $ob_preprocessor $ob_file_list $total_include
# $ob_exe $ob_t_m -v1 -o $ob_output -b -p $ob_preprocessor $ob_file_list $total_include
rm $ob_output/cobf.log

# rename
ob_source_list=$(ls $ob_output|grep '\.c')

for dc_mod in $dc_mod_list; do
	ob_name_num=0
	for ob_source in $ob_source_list; do
		if [[ "${ob_source}" == ${dc_mod}* ]]; then
			((ob_name_num++))
			mv "$ob_output/$ob_source" "$ob_output/${dc_mod}_$ob_name_num.c"
		fi
	done
done

### postproc ###
# mv "$project_root/dinc/generic/include" "$project_root/dinc/generic_ob"
# create include folder and move dc_definition.h into it
mv "$project_root/dinc/generic/include/dc_definition.h" "$ob_include/dc_definition.h"
mv "$project_root/dinc/generic/include/log.h" "$ob_include/log.h"
mv "$project_root/dinc/generic/Makefile" "$project_root/dinc/generic_ob"
mv "$project_root/dinc/generic/module.mk" "$project_root/dinc/generic_ob"
rm -rf "$project_root/dinc/generic"
mv "$project_root/dinc/generic_ob" "$project_root/dinc/generic"
# ---------------------------------------------------------------------------------------------------------

#dc_module obfuscation
# dc_mod_list=$(ls $project_root/dinc/generic|grep -E 'dc|din')
# for dc_mod in $dc_mod_list; do
# 	if [ -n "$2" ] && [ "$2" == "$dc_mod" ] || [ "$2" == "all" ]; then
# 		#header
# 		if [ "$dc_mod" == "din" ]; then
# 			header_list=$(ls $project_root/dinc/generic/din|grep '\.h')
# 		else
# 			header_list=$(ls $project_root/dinc/generic/$dc_mod|grep '\.h')
# 		fi
		
# 		h1=''
# 		for header in $header_list; do
# 			if [ -z "$h1" ]; then
# 				h1="-hi $header"
# 			else
# 				h1="$h1 -hi $header"
# 			fi
# 		done

# 		h_o1=$(ls $project_root/dinc/generic/include|grep 'util.h')
# 		h_o2=$(ls $project_root/dinc/generic/include|grep 'msg_format')
# 		h_o3=$(ls $project_root/dinc/hal/include|grep 'msg_hal')
# 		h_o4=$(ls $project_root/dinc/generic/include|grep 'version.h')
# 		h_o5=$(ls $project_root/dinc/hal/dev|grep 'data_dev.h')

# 		#additional header
# 		hal_mod=''
# 		if [ "$dc_mod" == "din" ]; then
# 			h2="$h1 -hi $h_o1 -hi $h_o2 -hi $h_o4"
# 		elif [ "$dc_mod" == "dc_dev" ]; then
# 			h2="$h1 -hi $h_o1 -hi $h_o2 -hi $h_o3 -hi $h_o4 -hi $h_o5"
# 		else
# 			hal_mod=$(echo "$dc_mod"|cut -b 4-)
# 			h_o6=$(ls $project_root/dinc/hal/$hal_mod|grep 'data_'"$hal_mod")

# 			h2="$h1 -hi $h_o1 -hi $h_o2 -hi $h_o3 -hi $h_o4 -hi $h_o5 -hi $h_o6"
# 		fi

# 		#source
# 		if [ "$dc_mod" == "din" ]; then
# 			source_list=$(ls $project_root/dinc/generic/din|grep '\.c')
# 		else
# 			source_list=$(ls $project_root/dinc/generic/$dc_mod|grep '\.c')
# 		fi

# 		s1=''
# 		for source in $source_list; do
# 			if [ -z "$s1" ]; then
# 				s1="$source"
# 			else
# 				s1="$s1 $source"
# 			fi			
# 		done
		
# 		#additional source
# 		s_o1=$(ls $project_root/dinc/generic/include|grep 'util.c')
# 		s_o2=$(ls $project_root/dinc/generic/include|grep 'version.c')
# 		s2="$s1 $s_o1 $s_o2"
		
# 		#token & macro
# 		ob_t1="$ob_exe_root/c.tok"
# 		ob_t2="$ob_exe_root/cansilib.tok"
# 		ob_t3="$ob_exe_root/dc.tok"
# 		ob_m1="$ob_exe_root/c.mak"
# 		ob_m2="$ob_exe_root/dc.mak"
# 		ob_p1="$ob_exe_root/dc.map"
# 		ob_t_m="-t $ob_t1 -t $ob_t2 -t $ob_t3 -m $ob_m1 -m $ob_m2 -mi $ob_p1"

# 		ob_file_list="$h2 $s2"

# 		#log		
# 		#echo "$ob_file_list" > "$dc_mod"_'ob_log'

# 		#include
# 		ob_i1="$project_root/dinc/generic/din"
# 		ob_i2="$project_root/dinc/generic/$dc_mod"
# 		ob_i3="$project_root/dinc/generic/include"
# 		ob_i4="$project_root/dinc/hal/include"
# 		ob_i5="$project_root/dinc/hal/dev"
# 		ob_i6="$project_root/dinc/hal/$hal_mod"


# 		if [ "$dc_mod" == "din" ]; then
# 			ob_include="-i $ob_i1 -i $ob_i3"
# 		elif [ "$dc_mod" == "dc_dev" ]; then
# 			ob_include="-i $ob_i2 -i $ob_i3 -i $ob_i4 -i $ob_i5"
# 		else
# 			ob_include="-i $ob_i2 -i $ob_i3 -i $ob_i4 -i $ob_i5 -i $ob_i6"
# 		fi
		
# 		#output
# 		if [ "$dc_mod" == "din" ]; then
# 			ob_output="$project_root/dinc/generic_ob/din"
# 		else
# 			ob_output="$project_root/dinc/generic_ob/$dc_mod"
# 		fi
# # echo " HSUNCHENGS -- $project_root/dinc/generic_ob/$dc_mod"
# 		mkdir -p $ob_output

# 		# echo " HSUNCHENGS -- $ob_include"

# 		#obfuscation
# 		# $ob_exe $ob_t_m -di -v1 -o $ob_output -b -p $ob_preprocessor $ob_file_list $ob_include
# 		$ob_exe $ob_t_m -v1 -o $ob_output -b -p $ob_preprocessor $ob_file_list $ob_include
# 		# echo "write cobf.logs"
# 		rm $ob_output/cobf.log

# 		#rename
# 		ob_name_num=0
# 		ob_source_list=$(ls $ob_output|grep '\.c')
	
# 		for ob_source in $ob_source_list; do
# 			if [[ "${ob_source}" == ${dc_mod}* ]] ;
# 			then
# 				((ob_name_num++))
# 				mv "$ob_output/$ob_source" "$ob_output/${dc_mod}_$ob_name_num.c"
# 			fi
# 		done
# 	fi
# done

###postproc###
# rm -rf "$project_root/dinc/generic"
# mv "$project_root/dinc/generic_ob" "$project_root/dinc/generic"

maketool_root="$ob_exe_root/maketool"

cp -a "$maketool_root/Makefile" "$project_root/dinc/generic/Makefile"
cp -a "$maketool_root/module.mk" "$project_root/dinc/generic/module.mk"

exit