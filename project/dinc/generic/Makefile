DINC_DIR = ..

include $(DINC_DIR)/common.mk

GENERIC_MODULES = $(addprefix dc_,$(MODULES)) din
GENERIC_MODULES_CLEAN = $(addsuffix _clean,$(GENERIC_MODULES))

DDEFINES = 

.PHONY: all
all:
ifeq ($(DEBUGMODE), ON)
	$(eval DDEFINES = -DDEBUG_MODE)
endif

	for MODULE in $(patsubst %/,%,$(patsubst $(GENERIC_DIR)/%,%,$(dir $(wildcard $(GENERIC_DIR)/*/)))); do		\
		if [ $$MODULE != "include" ]; then						\
			make -f module.mk GENERIC_MODULE=$$MODULE EXTDEFINES="$(DDEFINES)";			\
		fi;														\
	done

	# for MODULE in $(GENERIC_MODULES); do			\
	# 	make -f module.mk GENERIC_MODULE=$$MODULE;	\
	# done
	#make -f module.mk GENERIC_MODULE=din;

.PHONY: lib
lib:
ifeq ($(DEBUGMODE), ON)
	$(eval DDEFINES = -DDEBUG_MODE)
endif

	for MODULE in $(patsubst %/,%,$(patsubst $(GENERIC_DIR)/%,%,$(dir $(wildcard $(GENERIC_DIR)/*/)))); do		\
		if [ $$MODULE != "include" ]; then											\
			make -f module.mk GENERIC_MODULE=$$MODULE EXTCFLAGS=-DLIBDIN EXTDEFINES="$(DDEFINES)" lib;		\
		fi;																			\
	done

	# for MODULE in $(GENERIC_MODULES); do				\
	# 	make -f module.mk GENERIC_MODULE=$$MODULE EXTCFLAGS=-DLIBDIN lib;	\
	# done
	#make -f module.mk GENERIC_MODULE=din EXTCFLAGS=-DLIBDIN lib;
	
.PHONY: clean
clean:
	for MODULE in $(patsubst %/,%,$(patsubst $(GENERIC_DIR)/%,%,$(dir $(wildcard $(GENERIC_DIR)/*/)))); do		\
		if [ $$MODULE != "include" ]; then							\
			make clean -f module.mk GENERIC_MODULE=$$MODULE;		\
		fi;															\
	done

	# for MODULE in $(GENERIC_MODULES); do					\
	# 	make clean -f module.mk GENERIC_MODULE=$$MODULE;	\
	# done
	#make clean -f module.mk GENERIC_MODULE=din;

#.PHONY: $(GENERIC_MODULES)
#$(GENERIC_MODULES):
# 	make -f module.mk GENERIC_MODULE=$@

.PHONY: $(GENERIC_MODULES_CLEAN)
$(GENERIC_MODULES_CLEAN):
	make clean -f module.mk GENERIC_MODULE=$(shell echo $@ | sed s/_clean//)
