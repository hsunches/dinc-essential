DINC_DIR = ..

include $(DINC_DIR)/common.mk

HAL_MODULES = $(MODULES)
HAL_MODULES_CLEAN = $(addsuffix _clean, $(HAL_MODULES))
HAL_MODULES_UPPER_CASE = $(shell echo $(HAL_MODULES) | tr '[:lower:]' '[:upper:]')

ADD_MAKEFILES = $(addsuffix /$(PROFILE).mk, $(HAL_MODULES))

include $(ADD_MAKEFILES)

INCLUDES = -I$(HAL_INCLUDE_DIR)

CFLAGS = -O2 -Wall

LIBS = $(shell echo $(HAL_MODULES) | sed -E 's/([^ ]+)/\1\/$(PROFILE)\/hal_\1\.a/g')

SO_PPREFIX = libhal.so
SO_PREFIX = $(SO_PPREFIX).1
SO_LIB = $(SO_PREFIX).0
SO_FLAGS = -shared -Wl,-soname,$(SO_PREFIX)
SO_LIBS_FLAGS = -Wl,--whole-archive $(LIBS) -Wl,--no-whole-archive

.PHONY: all
all: $(SO_LIB)
	# cp -a $(SO_PPREFIX) $(SO_PREFIX) $(SO_LIB) $(OUTPUT_DIR)/
	for LIB in $(LIBS); do			\
		cp $$LIB $(TEMPORARY_DIR);	\
	done

$(SO_LIB): $(HAL_MODULES)
	# $(CC) $(SO_FLAGS) -o $@ $(SO_LIBS_FLAGS) $(ADD_LDLIBS)
	# ln -sf $(SO_LIB) $(SO_PREFIX)
	# ln -sf $(SO_LIB) $(SO_PPREFIX)

.PHONY: $(HAL_MODULES)
$(HAL_MODULES):
	make -f module.mk MODULE=$@

.PHONY: $(HAL_MODULES_CLEAN)
$(HAL_MODULES_CLEAN):
	make clean -f module.mk MODULE=$(shell echo $@ | sed s/_clean//)

.PHONY: clean
clean:
	for MODULE in $(HAL_MODULES); do				\
		make clean -f module.mk MODULE=$$MODULE;	\
	done

	rm -f $(OBJS) libhal.so* $(OUTPUT_DIR)/libhal.so*
