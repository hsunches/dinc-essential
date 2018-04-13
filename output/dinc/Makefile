include common.mk

.PHONY: all
all: lib final-build

.PHONY: sample
sample: BUILD_DEFINES = -DSAMPLE_CODE
sample: lib final-build

PHONY: final-build
final-build: 	
	#$(CC) main.c dinc.a $(LDLIBS) 

	$(CC) -c main.c
	
	# $(CC) -shared -o libdinc.so -Wl,--whole-archive libdinc.a -Wl,--no-whole-archive -ldl -lresolv -lpthread -lm	
	$(CC) -o $(OUTPUT_DIR)/din main.o -L./ -Wl,--export-dynamic -Wl,--whole-archive $(OUTPUT_DIR)/libdinc.a -Wl,--no-whole-archive $(LDLIBS) -lm	
	$(STRIP) $(OUTPUT_DIR)/din

	# check function customer implementations
	@profile/$(PROFILE)/dinc_util.sh check_implementation

	rm main.o	

.PHONY: create-profile
create-profile:
	@cp -fr profile/template profile/${NAME}

	@for MODULE in $(dir $(wildcard $(HAL_DIR)/*/)); do			\
		if [ -d $$MODULE"template/" ]; then						\
			cp -fr $$MODULE"template" $$MODULE"${NAME}";		\
			if [ -f $$MODULE"template.mk" ]; then				\
				cp $$MODULE"template.mk" $$MODULE"${NAME}.mk";	\
			fi													\
		fi														\
	done

.PHONY: archieve-profile
archieve-profile:
	@if [ ! -d ${PROFILE_IMPL_DIR} ]; then 	\
		mkdir ${PROFILE_IMPL_DIR}; 			\
	fi 

	@rm -rf ${PROFILE_IMPL_DIR}/${NAME}
	@mkdir ${PROFILE_IMPL_DIR}/${NAME}

	@for MODULE in $(dir $(wildcard $(HAL_DIR)/*/)); do \
		PROFILE_HAL_DIR=$$MODULE"${NAME}"; 				\
		if [ -d $$PROFILE_HAL_DIR ]; then 				\
			for CFILE in $$PROFILE_HAL_DIR/*.c; do 		\
				cp -f $$CFILE ${PROFILE_IMPL_DIR}/${NAME}; 	\
			done 										\
		fi 												\
	done

	@if [ -f $(DINC_DIR)/profile/${NAME}/dinc_util.sh ]; then 					\
		cp -f $(DINC_DIR)/profile/${NAME}/dinc_util.sh ${PROFILE_IMPL_DIR}/${NAME}; \
		cd ${PROFILE_IMPL_DIR}; 													\
		tar -zcvf ${NAME}.tar.gz ${NAME}; 										\
		mv ${NAME}.tar.gz ${NAME}_$(shell date +"%Y%m%d_%H%M%S").tgz; 			\
	else 																		\
		echo "Profile ${NAME} does not exist..."; 								\
	fi
	
	@rm -rf ${PROFILE_IMPL_DIR}/${NAME}

.PHONY: libsub
libsub:
	rm -rf $(TEMPORARY_DIR)
	rm -rf $(OUTPUT_DIR)
	mkdir $(TEMPORARY_DIR)
	mkdir $(OUTPUT_DIR)

	make -C $(HAL_DIR) DEFINES=$(BUILD_DEFINES)
	make -C $(GENERIC_DIR) lib
	# make -C $(GENERIC_DIR)

.PHONY: lib
lib: libsub

	# extract *.o from all *.a
	cd $(TEMPORARY_DIR);							\
	for LIB in $(wildcard $(TEMPORARY_DIR)/*.a); do	\
		$(AR) -x ../$$LIB;							\
	done

	$(AR) rcs $(OUTPUT_DIR)/libdinc.a $(TEMPORARY_DIR)/*.o
	chmod 755 $(OUTPUT_DIR)/libdinc.a
	rm -rf $(TEMPORARY_DIR)

.PHONY: clean
clean:
	make clean -C $(GENERIC_DIR)
	make clean -C $(HAL_DIR)
	rm -f $(OUTPUT_DIR)/*.cfg

.PHONY: install
install: all
	sudo mkdir -p $(INSTALL_DINC_CFG_PATH)
	sudo cp -a $(DINC_CONFIG) $(INSTALL_DINC_CFG_PATH)/
	# sudo mkdir -p $(INSTALL_DINC_LIB_PATH)
	# sudo cp -a $(DINC_SO_LIB) $(INSTALL_DINC_LIB_PATH)/
	sudo chmod 755 $(OUTPUT_DIR)/*
	sudo mkdir -p $(INSTALL_DINC_PATH)
	sudo cp -a $(DINC_BINARY) $(INSTALL_DINC_PATH)/
	sudo cp $(PROFILE_DIR)/dinc_util.sh $(INSTALL_DINC_PATH)/
