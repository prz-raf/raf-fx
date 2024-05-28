# raf-fx Makefile

# Directories
BOOTLOADER_DIR := boot
OUTPUT_DIR := out

# Include bootloader Makefile
include $(BOOTLOADER_DIR)/Makefile

# Ensure that output directory exists
$(OUTPUT_DIR):
	@echo "Creating output directory"
	mkdir -p $(OUTPUT_DIR)

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

