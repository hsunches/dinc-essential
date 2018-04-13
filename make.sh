#!/bin/bash

cd project/dinc
make clean
cd ../..

rm -rf output
mkdir output
CUSTOMERS=$(ls ./customer)
if [ ! -z "$1" ]; then
	if [ -d "./customer/$1" ]; then
		CUSTOMERS=("$1")
	fi
fi

for customer in ${CUSTOMERS[@]}
do
    MODULES=(2g 3g ethernet lte voip wifi_ap wifi_sta wmx)
	idx=0
	for keyword in ${MODULES[@]}; do
		for module in $(ls ./customer/${customer})
		do
	      	if [ "${keyword}" = "${module}" ]; then
	      		echo "${keyword}=${module}, unset ${idx}"
	           	unset MODULES[$idx]
	           	break;
	      	fi
		done
	    let idx++
	done
	cd project/tool
	./export.sh ${MODULES[*]}
	mv dinc.tar.gz ../../output/${customer}.tgz
	cd ../..
done