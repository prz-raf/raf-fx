# Makefile
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
LD_DIR := $(MAKE_DIR)/ld


# shared files
BOOTLOADER_IMG := $(OUTPUT_DIR)/boot.img
KERNEL_BIN := $(OUTPUT_DIR)/system


# config file
CONFIG_FILE := $(CONFIG_DIR)/make.cfg
DEFAULT_CONFIG_FILE := $(CONFIG_DIR)/default.cfg


# all objects that need to be linked in the end
FINAL_OBJS := $(wildcard $(OBJ_DIR)/*.o)


# build configuration
include $(CONFIG_FILE)


# tools
LD := ld
LDFLAGS := -m elf_i386 -T $(LD_DIR)/linker.ld --oformat binary


# result file
RESULT_IMG := $(OUTPUT_DIR)/system-boot


export MAKE_DIR BOOTLOADER_DIR CONFIG_DIR KERNEL_DIR OUTPUT_DIR OBJ_DIR CONFIG_FILE KERNEL_BIN BOOTLOADER_IMG RELATIVE_PATH_CMD


all: $(OUTPUT_DIR) $(OBJ_DIR) $(BOOTLOADER_IMG) kernel_objs $(KERNEL_BIN) $(RESULT_IMG)


# ensure that output directory exists
$(OUTPUT_DIR):
	@echo "Creating\t\t$(call relpath, $(OUTPUT_DIR)) directory"
	@mkdir -p $(OUTPUT_DIR)
	
# ensure that object directory exists
$(OBJ_DIR):
	@echo "Creating\t\t$(call relpath, $(OBJ_DIR)) directory"
	@mkdir -p $(OBJ_DIR)
	
$(BOOTLOADER_IMG):
	@$(MAKE) -C boot --no-print-directory
	
kernel_objs:
	@$(MAKE) -C kernel --no-print-directory

# link all object files to create the kernel binary
$(KERNEL_BIN):
	@echo "Linking\t\t\tobject files to create $(KERNEL_BIN)"
	@$(LD) $(LDFLAGS) -o $@ `ls $(OBJ_DIR)/*.o`

# create full system image with bootloader
$(RESULT_IMG): $(BOOTLOADER_IMG) $(KERNEL_BIN)
ifeq ($(CREATE_BOOTABLE_IMAGE), y)
		@echo "Creating\t\t$(call relpath,$(RESULT_IMG)) system image"
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
