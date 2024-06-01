# raf-fx Makefile

# convert absolute paths to relative paths for printing
relpath = $(patsubst $(MAKE_DIR)/%,%,$(1))

# dirs
MAKE_DIR = $(PWD)
BOOTLOADER_DIR := $(MAKE_DIR)/boot
CONFIG_DIR := $(MAKE_DIR)/config
KERNEL_DIR := $(MAKE_DIR)/kernel
OUTPUT_DIR := $(MAKE_DIR)/out
INCLUDE_DIR := $(KERNEL_DIR)/include
OBJ_DIR := $(OUTPUT_DIR)/obj


# shared files
BOOTLOADER_IMG := $(OUTPUT_DIR)/boot.img
KERNEL_BIN := $(OUTPUT_DIR)/system


# config file
CONFIG_FILE := $(CONFIG_DIR)/make.cfg
DEFAULT_CONFIG_FILE := $(CONFIG_DIR)/default.cfg


# build configuration
include $(CONFIG_FILE)


# result file
RESULT_IMG := $(OUTPUT_DIR)/system-image


export MAKE_DIR BOOTLOADER_DIR CONFIG_DIR KERNEL_DIR OUTPUT_DIR OBJ_DIR CONFIG_FILE KERNEL_BIN BOOTLOADER_IMG RELATIVE_PATH_CMD


all: $(OUTPUT_DIR) $(OBJ_DIR) $(RESULT_IMG)

$(BOOTLOADER_IMG):
	@$(MAKE) -C boot --no-print-directory
	
$(KERNEL_BIN):
	@$(MAKE) -C kernel --no-print-directory

# ensure that output directory exists
$(OUTPUT_DIR):
	@echo "Creating\t\t$(call relpath, $(OUTPUT_DIR)) directory"
	@mkdir -p $(OUTPUT_DIR)
	
# ensure that object directory exists
$(OBJ_DIR):
	@echo "Creating\t\t$(call relpath, $(OBJ_DIR)) directory"
	@mkdir -p $(OBJ_DIR)

# create full system image with bootloader
$(RESULT_IMG): $(BOOTLOADER_IMG) $(KERNEL_BIN)
ifeq ($(CREATE_BOOTABLE_IMAGE), y)
		@echo "Creating\t\tsystem image $(call relpath,$(RESULT_IMG))"
		@cat $^ > $@
		@rm -f $(BOOTLOADER_IMG) $(KERNEL_BIN)
endif


# clean the output directory
clean:
	@rm -r $(OUTPUT_DIR)
	@echo "Removed\t\t$(call relpath, $(OUTPUT_DIR)) directory"


# defconfig, set the default configuration
defconfig:
	@cp $(DEFAULT_CONFIG_FILE) $(CONFIG_FILE)
	@echo "$(call relpath, $(CONFIG_FILE)) has been updated with $(call relpath, $(DEFAULT_CONFIG_FILE))"


# menuconfig (to be implemented), let user set the configuration 
# manually using interactive menu
menuconfig:
	@echo "Menuconfig is yet to be implemented..."




.PHONY: all clean defconfig menuconfig

