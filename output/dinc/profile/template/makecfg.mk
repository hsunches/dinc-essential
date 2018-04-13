################################################################################
#
# The cross compiler prefix of the toolchain.
# 
# For example, if the binary path is "/opt/gcc/bin/mips-linux-gcc",
# the prefix should be "/opt/gcc/bin/mips-linux-".
#
################################################################################

CROSS_COMPILE_PREFIX = /usr/bin/

################################################################################
#
# The header directory of the toolchain.
#
################################################################################

C_INCLUDE_PATH = /usr/include

################################################################################
#
# The library directory of the toolchain.
#
################################################################################

LIBRARY_PATH = /usr/lib

################################################################################
#
# The directories containing the required libraries by the toolchain.
#
################################################################################

LD_LIBRARY_PATH = /usr/lib

################################################################################
#
# The data collection modules supported by your device.
#
# The example shows all possible choices.
#
# For details, see dinc/hal/$module/template/data_$module.c.
#
################################################################################

MODULES = wifi_ap lte 

################################################################################
#
# The ROOT path of your device (very important!!!)
#
# For example, if you want to do local test, please set it to "",
# but if you are going to install this package into your device,
# please set it to "your firmware root"
#
################################################################################

INSTALL_ROOT = 

################################################################################
#
# The directories for DINC in your device
#
# For example:	local test is "/usr/bin"
#		your device is "your firmware root/usr/bin"
#
################################################################################

INSTALL_DINC_PATH = $(INSTALL_ROOT)/usr/bin

################################################################################
#
# The directories for DINC Shared Library (HAL) in your device
#
# For example:	local test is "/usr/lib"
#		your device is "your firmware root/usr/lib"
#
################################################################################

INSTALL_DINC_LIB_PATH = $(INSTALL_ROOT)/usr/lib

################################################################################
#
# ATTENTION!!!
# DO NOT CHANGE this setting, this directory is necessary of DINC
#
################################################################################

INSTALL_DINC_CFG_PATH = $(INSTALL_ROOT)/etc/dinc

