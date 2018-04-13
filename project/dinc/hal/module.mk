DINC_DIR = ..

include $(DINC_DIR)/common.mk

HAL_MODULE_DIR = $(HAL_DIR)/$(MODULE)

INCLUDES  = -I$(HAL_INCLUDE_DIR)
INCLUDES += -I$(HAL_MODULE_DIR)
INCLUDES += -I$(HAL_MODULE_DIR)/$(PROFILE)

CFLAGS = -Wall -O2

LIB_HAL = $(HAL_MODULE_DIR)/$(PROFILE)/hal_$(MODULE).a
EXEC_UT = $(HAL_MODULE_DIR)/$(PROFILE)/utest_$(MODULE)

include $(HAL_MODULE_DIR)/$(PROFILE).mk

ADD_OBJS = $(patsubst %.c,%.o,$(ADD_SRCS))

OBJS  = $(addprefix $(HAL_MODULE_DIR)/, $(ADD_OBJS))
OBJS += $(HAL_MODULE_DIR)/$(PROFILE)/data_$(MODULE).o

OBJS_HAL = $(OBJS)

OBJS_UT  = $(OBJS)
OBJS_UT += $(HAL_MODULE_DIR)/utest_$(MODULE).o
OBJS_UT += $(HAL_INCLUDE_DIR)/ut_util.o

DEPS  = $(addprefix $(HAL_MODULE_DIR)/, $(ADD_DEPS))
DEPS += $(HAL_MODULE_DIR)/data_$(MODULE).h
DEPS += $(HAL_INCLUDE_DIR)/msg_hal.h
DEPS += $(HAL_INCLUDE_DIR)/ut_util.h

.PHONY: all
all: $(LIB_HAL) $(EXEC_UT)

$(LIB_HAL): $(OBJS_HAL)
	$(AR) rcs $@ $(OBJS_HAL)

$(EXEC_UT): $(OBJS_UT)
	$(CC) $(OBJS_UT) -o $@ $(ADD_LDLIBS)
	$(STRIP) $(EXEC_UT)

%.o: %.c $(DEPS)
	$(CC) $(INCLUDES) $(DEFINES) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(LIB_HAL) $(EXEC_UT) $(OBJS_HAL) $(OBJS_UT)
