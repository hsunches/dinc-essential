#!/bin/bash

project_root=$1

if [ ! -d "$project_root/dinc" ]; then
	echo "error! please ensure project/dinc is exist."
	exit 1
fi

#argument list
for hal_target in $*; do
	#hal
	hal_list=$(ls -F $project_root/dinc/hal|grep '/')
	for hal in $hal_list; do
		if [ "$hal" == "$hal_target/" ]; then
			rm -rf "$project_root/dinc/hal/$hal_target/"
			dc_target="dc_$hal_target"
			cfg_target="dc_$hal_target.cfg"
		fi
	done

	#dc
	dc_mod_list=$(ls $project_root/dinc/generic|grep -E 'dc')
	for dc_mod in $dc_mod_list; do
		if [ "$dc_mod" == "$dc_target" ]; then
			rm -rf "$project_root/dinc/generic/$dc_target/"
		fi
	done

	#cfg
	cfg_list=$(ls $project_root/dinc/profile/template/config|grep -E 'dc')
	for cfg in $cfg_list; do
		if [ "$cfg" == "$cfg_target" ]; then
			rm -rf "$project_root/dinc/profile/template/config/$cfg_target"
		fi
	done

	sed -i "s/$hal_target //g" $project_root/dinc/profile/template/makecfg.mk
done

