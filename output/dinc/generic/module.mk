DINC_DIR = ..

include $(DINC_DIR)/common.mk

HAL_MODULE = $(subst dc_,,$(GENERIC_MODULE))
HAL_MODULE_DIR = $(HAL_DIR)/$(HAL_MODULE)
HAL_MODULE_DEV_DIR = $(HAL_DIR)/dev

INCLUDES =	-I$(GENERIC_INCLUDE_DIR)	\
			-I$(HAL_INCLUDE_DIR)		\
			-I$(HAL_MODULE_DIR)			\
			-I$(HAL_MODULE_DEV_DIR)

EXTDEFINES =
EXTCFLAGS =
CFLAGS = -Wall -O2 $(EXTCFLAGS)

LDLIBS = -lresolv -pthread -ldl -lm

EXEC = $(GENERIC_MODULE)/$(GENERIC_MODULE)
A_LIB = $(GENERIC_MODULE)/$(GENERIC_MODULE).a

ALL_OBJS =	$(patsubst %.c,%.o,$(wildcard $(GENERIC_MODULE)/*.c))		\
		$(patsubst %.c,%.o,$(wildcard $(GENERIC_INCLUDE_DIR)/*.c))

# remove modules if is not defined in makecfg.mk
REMOVED_MODULES =	$(filter-out $(MODULES),$(patsubst %/,%,$(patsubst $(HAL_DIR)/%,%,$(dir $(wildcard $(HAL_DIR)/*/)))))

FILTER_OUT =	$(foreach obj,$(ALL_OBJS),$(foreach removed,$(REMOVED_MODULES),$(if $(findstring $(removed),$(obj)),$(obj))))
OBJS =	$(filter-out $(FILTER_OUT),$(ALL_OBJS))

HAL_SO_LIB = $(HAL_DIR)/libhal.so.1.0

HAL_SO_FLAGS = -L$(HAL_DIR) -lhal

.PHONY: all
all: $(EXEC)
	cp $(EXEC) $(OUTPUT_DIR)

.PHONY: lib
lib: $(A_LIB)
	cp $(A_LIB) $(TEMPORARY_DIR)

$(EXEC): $(OBJS) $(HAL_SO_LIB)
	$(CC) $(OBJS) -o $@ $(LDLIBS) $(HAL_SO_FLAGS)
	$(STRIP) $(EXEC)

$(A_LIB): $(OBJS) $(HAL_SO_LIB)
	$(AR) rcs $@ $(OBJS)

%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) $(EXTDEFINES) -c $< -o $@

$(HAL_SO_LIB):
	if [ ! -e $(HAL_SO_LIB) ]; then	\
		make -C $(HAL_DIR); 		\
	fi

.PHONY: clean
clean:
	rm -f $(OUTPUT_DIR)/$(GENERIC_MODULE) $(EXEC) $(OBJS) $(A_LIB)
