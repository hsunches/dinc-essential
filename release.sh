sudo killall din
sudo ./make.sh generic

OUT_DIR=$(pwd)/output
CUSTOMER_PACKAGE_LIST=$(ls $OUT_DIR | grep -E '*.tgz')

cd $OUT_DIR
for package in $CUSTOMER_PACKAGE_LIST; do
	rm -rf dinc
	tar -xzf $package
	if [ -d $OUT_DIR/'dinc' ]; then
		cd dinc
		make clean
		make sample DEBUGMODE=ON
		make install
 		make clean
		cd ../
	fi
done