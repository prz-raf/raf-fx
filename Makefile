# raf-fx Makefile

# dirs
BOOTLOADER_DIR := boot
KERNEL_DIR := kernel
INCLUDE_DIR := $(KERNEL_DIR)/include
OUTPUT_DIR := out
OBJ_DIR := $(OUTPUT_DIR)/obj

# bootloader files
BOOTLOADER_SRC := $(BOOTLOADER_DIR)/boot.asm
BOOTLOADER_IMG := $(OUTPUT_DIR)/boot.img

# kernel files
KERNEL_SRC := $(KERNEL_DIR)/kernel.c $(KERNEL_DIR)/print.c
KERNEL_OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(KERNEL_SRC:.c=.o)))
KERNEL_BIN := $(OUTPUT_DIR)/kernel.bin

# result file
RESULT_IMG := $(OUTPUT_DIR)/raf-fx

# tools
ASM := nasm
ASM_FLAGS := -f bin
CC := gcc
CFLAGS := -m32 -ffreestanding -fno-pic -O2 -Wall -Wextra -I$(INCLUDE_DIR)
LD := ld
LDFLAGS := -m elf_i386 -Ttext 0x1000 --oformat binary -e _start

# default target
all: $(OUTPUT_DIR) $(OBJ_DIR) $(RESULT_IMG)

# ensure that output directory exists
$(OUTPUT_DIR):
	@echo "Creating output directory"
	@mkdir -p $(OUTPUT_DIR)
	
# ensure that object directory exists
$(OBJ_DIR):
	@echo "Creating object directory"
	@mkdir -p $(OBJ_DIR)

# compile bootloader assembly to bootloader image
$(BOOTLOADER_IMG): $(BOOTLOADER_SRC) | $(OBJ_DIR)
	@echo "Compiling $(BOOTLOADER_SRC) to $(BOOTLOADER_IMG)"
	@$(ASM) $(ASM_FLAGS) -o $@ $<

# compile kernel source files to kernel object files
$(OBJ_DIR)/%.o: $(KERNEL_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling $< to $@"
	@$(CC) $(CFLAGS) -c -o $@ $<

# link kernel object files to create the kernel binary
$(KERNEL_BIN): $(KERNEL_OBJS)
	@echo "Linking $(KERNEL_OBJS) to create $(KERNEL_BIN)"
	@$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJS)

# create final system image 	
$(RESULT_IMG): $(BOOTLOADER_IMG) $(KERNEL_BIN)
	@echo "Creating system image $(RESULT_IMG)"
	@dd if=$(BOOTLOADER_IMG) of=$@ bs=512 count=1 > /dev/null 2>&1
	@dd if=$(KERNEL_BIN) of=$@ bs=512 seek=1 > /dev/null 2>&1
	@rm -f $(BOOTLOADER_IMG) $(KERNEL_BIN)

# rlean the output directory
clean:
	@rm -r $(OUTPUT_DIR)
	@echo "Removed $(OUTPUT_DIR) directory"

# defconfig (to be implemented), set the default configuration
defconfig:
	@echo "Defconfig is yet to be implemented..."

# menuconfig (to be implemented), let user set the configuration 
# manually using interactive menu
menuconfig:
	@echo "Menuconfig is yet to be implemented..."

.PHONY: all clean defconfig menuconfig

