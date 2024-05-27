# RafOS Makefile
#
# Directories
BOOTLOADER_DIR := boot
OUTPUT_DIR := out

# Files
BOOTLOADER_SRC := $(BOOTLOADER_DIR)/boot.asm
BOOTLOADER_IMG := $(OUTPUT_DIR)/boot.img

# Assembler
ASM := nasm
ASM_FLAGS := -f bin

# Default target
all: $(OUTPUT_DIR) $(BOOTLOADER_IMG)

# Ensure that output directory exists
$(OUTPUT_DIR):
	@echo "Creating output directory"
	mkdir -p $(OUTPUT_DIR)

# Compile bootloader assembly to bootloader image
$(BOOTLOADER_IMG): $(BOOTLOADER_SRC) | $(OUTPUT_DIR)
	@echo "Compiling $(BOOTLOADER_SRC) to $(BOOTLOADER_IMG)"
	$(ASM) $(ASM_FLAGS) -o $@ $<

# Clean the output directory
clean:
	rm -rf $(OUTPUT_DIR)/*

# Defconfig (to be implemented), set the default configuration
defconfig:
	@echo "Defconfig is yet to be implemented..."

# Menuconfig (to be implemented), let user set the configuration 
# manually using interactive menu
menuconfig:
	@echo "Menuconfig is yet to be implemented..."

.PHONY: all clean defconfig menuconfig
