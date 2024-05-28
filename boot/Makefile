# Bootloader Makefile

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
all: $(BOOTLOADER_IMG)

# Compile bootloader assembly to bootloader image
$(BOOTLOADER_IMG): $(BOOTLOADER_SRC) | $(OUTPUT_DIR)
	@echo "Compiling $(BOOTLOADER_SRC) to $(BOOTLOADER_IMG)"
	$(ASM) $(ASM_FLAGS) -o $@ $<

.PHONY: all

