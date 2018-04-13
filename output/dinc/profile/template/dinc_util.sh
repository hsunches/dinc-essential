#!/bin/sh

################################################################################
# 
# BEGINNING OF THE IMPLEMENTATION PART
#
################################################################################

# Purpose:		Get USB device IP address.
# Parameters:	None.
# Return:		The USB device IP address.
get_usb_dev_ip()
{
	# echo "127.0.0.1"
	echo mobric.not.implemented
	:
}

# Purpose:		Get optional domain name from DHCP server.
# Parameters:	None.
# Return:		The optional domain name.
get_domain_name_from_dhcp()
{
	#echo my.domain.name
	echo mobric.not.implemented
	:
}

# Purpose:		Get the WiMAX NAP-ID.
# Parameters:	None.
# Return:		The NAP-ID in lowercase hex string.
get_wmx_nap_id()
{
	#echo acde48
	echo mobric.not.implemented
	:
}

# Purpose:		Get the MCC of the IMSI.
# Parameters:	None.
# Return:		The MCC.
get_imsi_mcc()
{
	# echo 466
	echo mobric.not.implemented
	:
}

# Purpose:		Get the MNC of the IMSI.
# Parameters:	None.
# Return:		The MNC.
get_imsi_mnc()
{
	# echo 01
	echo mobric.not.implemented
	:
}

# Purpose:		Get the currently activated network interface
# Parameters:	None.
# Return:		The valid return would be one or an array of the followings: 2g, 3g, lte, wmx, wifi_sta, extern_src
# Remark:		Each nif must be delimited by space and included within double quotations if there are more than one availables.
#				The first one will be currently used network.
get_activated_nif()
{
	# echo lte
	# echo "2g 3g lte"
	echo mobric.not.implemented
	:
}

# Purpose:		Get the currently running process ID by command name
# Parameters:	${1} stands for target command name
# Return:		The process ID of all running process by name "cmd" which is a input value (${1}).
# Remark:		The marked example command may not work in certain device. Please test it or implement your command properly.
get_cmd_pid()
{
	cmd=${1}
	# echo `ps -e -o pid -o comm | grep ${cmd} | awk '{print $1}'`
	echo mobric.not.implemented
	:
}

################################################################################
# 
# END OF THE IMPLEMENTATION PART
#
################################################################################

# Purpose:		Call when system started.
# Parameters:	None.
# Return:		None.
on_system_up()
{
	start_client_daemon
	sleep 1
}

# Purpose:		Call when system started on debug mode.
# Parameters:	None.
# Return:		None.
on_system_up_for_debug()
{
	start_client_normal
	sleep 1
}

# Purpose:		Call when searching network.
# Parameters:	The target network type (2g/3g/lte/wmx).
# Return:		None.
on_network_search()
{
	start_client_event_trigger network_search $1
}

# Purpose:		Call when network connectivity changed.
# Parameters:	The list of currently connected networks (2g/3g/lte/wmx/wifi_sta).
# Return:		None.
on_network_change()
{
	if [ -z "$*" ]; then
		stop_all_dcs
		start_client_event_trigger network_down
	elif [ "$(ps -ef | grep '[d]in --' | wc -l)" -eq "1" ]; then
		start_client_event_trigger network_up $1
		local type

		for type in $*; do
			start_dc $type
		done
		start_extra_dcs
	else
		local type

		for type in $*; do
			start_dc $type
		done
	fi
}

# Purpose:		Call when handover began.
# Parameters:	The target network type (2g/3g/lte/wmx).
# Return:		None.
on_handover_begin()
{
	start_client_event_trigger handover_begin $1
}

# Purpose:		Call when handover succeeded.
# Parameters:	The target network type (2g/3g/lte/wmx).
# Return:		None.
on_handover_success()
{
	start_client_event_trigger handover_success $1
}

# Purpose:		Call when handover failed.
# Parameters:	The target network type (2g/3g/lte/wmx).
# Return:		None.
on_handover_fail()
{
	start_client_event_trigger handover_fail $1
}

# Purpose:		Call to get UID from a DINC at a given IP address.
# Parameters:	None.
# Return:		The target's UID.
on_get_extern_device_uid()
{
	echo "$(get_device_uid)"
}

# Purpose:		Call to get domain name from a DINC at a given IP address.
# Parameters:	None.
# Return:		The target's full domain name.
on_get_extern_device_domain()
{
	echo "$(get_full_domain)"
}

on_get_latency_fail_cnt()
{
	echo $(get_latency_fail_cnt)
}

################################################################################
# 
# UTILITY FUNCTIONS
#
################################################################################

DINC_CONFIG_DIR=/etc/dinc

start_client_daemon()
{
	din --daemon --cfg_path=$DINC_CONFIG_DIR/din.cfg
}

start_client_normal()
{
	din --normal --cfg_path=$DINC_CONFIG_DIR/din.cfg &
}

get_latency_fail_cnt()
{
	echo "$(din --latency_fail_cnt=127.0.0.1)"
}

get_full_domain()
{
	echo "$(din --request_full_domain=$(get_usb_dev_ip))"
}

get_device_uid()
{
	echo "$(din --request_dev_uid=$(get_usb_dev_ip))"
}

start_client_event_trigger()
{
	local event_type=$1
	local network_type=$2

	case $event_type in
	network_search)
		din --net_search=$network_type
		;;
	network_up)
		# start_dc dev
		
		case $network_type in
		2g|3g|lte)
			start_dc dev
			din --net_up --domain_name=g$(get_imsi_mcc)-$(get_imsi_mnc)
			;;
		wmx)
			start_dc dev
			din --net_up --domain_name=w$(get_wmx_nap_id)
			;;
		wifi_sta)
			start_dc dev
			din --net_up --domain_name=$(get_domain_name_from_dhcp)
			;;
		extern_src)
			uid=$(get_device_uid)
			din --specify_dev_uid="$uid"
			while [ "$uid" != "$(din -request_dev_uid=127.0.0.1)" ]
			do
				sleep 1
			done
			start_dc dev
			din --net_up --domain_name=$(get_full_domain)

			# din --specify_dev_uid=$(get_device_uid)
			# start_dc dev
			# din --net_up --domain_name=$(get_full_domain)
			;;
		esac
		;;
	network_down)
		din --net_down
		;;
	handover_begin)
		din --event=HOBN -receiver=$network_type
		;;
	handover_success)
		din --event=HOES -receiver=$network_type
		;;
	handover_fail)
		din --event=HOEF -receiver=$network_type
		;;
	esac
}

start_dc()
{
	stop_dc $1
	din --start_dc="$1 -c $DINC_CONFIG_DIR/dc_$1.cfg"
}

stop_dc()
{
	din --stop_dc=$1
	#killall -q dc_$1
}

start_extra_dcs()
{
	local type

	for type in wifi_ap ethernet voip; do
		start_dc $type
	done
}

stop_all_dcs()
{
	local type

	for type in 2g 3g lte wmx wifi_sta wifi_ap ethernet voip; do
		stop_dc $type
	done
}

on_check_implementation()
{
	for impl in get_usb_dev_ip get_domain_name_from_dhcp get_wmx_nap_id get_imsi_mcc get_imsi_mnc get_activated_nif ; do
		result=$($impl)

		trimed=$(echo $result | tr -d ' ')

		if [ "$trimed" = "mobric.not.implemented" -o -z "$trimed" ]; then
			echo "[Warning] function [$impl] is not implemeneted..."
		fi
	done
}

[ "$#" -gt "0" ] && on_$*
