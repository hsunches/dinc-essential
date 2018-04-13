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

.PHONY: clean
clean:
	for MODULE in $(patsubst %/,%,$(patsubst $(GENERIC_DIR)/%,%,$(dir $(wildcard $(GENERIC_DIR)/*/)))); do		\
		if [ $$MODULE != "include" ]; then							\
			make clean -f module.mk GENERIC_MODULE=$$MODULE;		\
		fi;															\
	done

.PHONY: $(GENERIC_MODULES_CLEAN)
$(GENERIC_MODULES_CLEAN):
	make clean -f module.mk GENERIC_MODULE=$(shell echo $@ | sed s/_clean//)
