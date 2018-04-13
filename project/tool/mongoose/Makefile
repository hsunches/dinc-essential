DINC_DIR = ..

include $(DINC_DIR)/common.mk

CFLAGS = -Wall -O2
LDLIBS = -pthread

EXEC = mongoose
OBJS = main.o $(EXEC).o
DEPS = $(EXEC).h

.PHONY: all
all: $(EXEC)
	cp $(EXEC) $(OUTPUT_DIR)

$(EXEC): $(OBJS) $(UTIL_LIB)
	$(CC) $(OBJS) $(UTIL_LIB) -o $@ $(LDLIBS)
	$(STRIP) $(EXEC)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OUTPUT_DIR)/$(EXEC) $(EXEC) $(OBJS)
