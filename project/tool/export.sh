#!/bin/bash

rm -rf project
mkdir project
cp -r ../../project/dinc project
cp -r ../../project/dins project

sed -i s/\$REVISION_ID/"$(git rev-parse HEAD)"/ project/dinc/generic/include/version.c
sed -i s/\$RELEASE_DATE/"$(date -u)"/ project/dinc/generic/include/version.c

./remove.sh project $*
./obfuscate.sh project all

make -C project/dins
mv -f project/dins/DinServer/bin/Release/DinServer.exe project/dinc/dins.exe
make clean -C project/dins

rm -rf dinc.tar.gz

tar -C project -zcvf dinc.tar.gz dinc	\
	--exclude=dinc/doc/DIN\ Packet\ Format*.*

rm -rf project
