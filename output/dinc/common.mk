DINC_DIR ?= .

# variable PROFILE should be overwrited
PROFILE = template
DEBUGMODE = OFF

include $(DINC_DIR)/profile/$(PROFILE)/makecfg.mk

export C_INCLUDE_PATH
export LIBRARY_PATH
export LD_LIBRARY_PATH

PROFILE_IMPL_DIR = ./profile-impl
HAL_DIR = $(DINC_DIR)/hal
HAL_INCLUDE_DIR = $(HAL_DIR)/include
GENERIC_DIR = $(DINC_DIR)/generic
GENERIC_INCLUDE_DIR = $(GENERIC_DIR)/include
PROFILE_DIR = $(DINC_DIR)/profile/${PROFILE}
CONFIG_DIR = $(PROFILE_DIR)/config
OUTPUT_DIR = $(DINC_DIR)/output
TEMPORARY_DIR = $(DINC_DIR)/temporary

MODULES += dev

DINC_CONFIG = $(wildcard $(CONFIG_DIR)/*.cfg)
DINC_SO_LIB = $(wildcard $(OUTPUT_DIR)/libhal*)
DINC_BINARY = $(filter-out $(DINC_SO_LIB), $(wildcard $(OUTPUT_DIR)/*))

CC = $(CROSS_COMPILE_PREFIX)gcc
AR = $(CROSS_COMPILE_PREFIX)ar
STRIP = $(CROSS_COMPILE_PREFIX)strip
LDLIBS = -lresolv -pthread -ldl -lssl -lcrypto
