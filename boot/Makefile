# boot/Makefile
# raf-fx bootloader Makefile

# build configuration
include $(CONFIG_FILE)

# convert absolute paths to relative paths for printing
relpath = $(patsubst $(MAKE_DIR)/%,%,$(1))

# bootloader files
BOOTLOADER_SRC := $(BOOTLOADER_DIR)/boot.asm

# tools
ASM := nasm
ASM_FLAGS := -f bin

all: $(BOOTLOADER_IMG)

# assemble bootloader to bootloader image
$(BOOTLOADER_IMG): $(BOOTLOADER_SRC) | $(OBJ_DIR)
ifeq ($(CREATE_BOOTABLE_IMAGE), y)
	@echo "Assembling\t\t$(call relpath, $(BOOTLOADER_SRC)) to $(call relpath, $(BOOTLOADER_IMG))"
	@$(ASM) $(ASM_FLAGS) -o $@ $<
endif

.PHONY: all
