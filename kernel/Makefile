# raf-fx kernel Makefile

# build configuration
include $(CONFIG_FILE)

# convert absolute paths to relative paths for printing
relpath = $(patsubst $(MAKE_DIR)/%,%,$(1))


# dirs
INCLUDE_DIR := $(KERNEL_DIR)/include


# kernel files
KERNEL_SRC := $(KERNEL_DIR)/kernel.c
KERNEL_ASM := $(KERNEL_DIR)/entry.asm
KERNEL_OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(KERNEL_SRC:.c=.o))) $(addprefix $(OBJ_DIR)/, $(notdir $(KERNEL_ASM:.asm=.o)))


# tools
ASM := nasm
ASM_FLAGS := -f elf32
LD := ld
LDFLAGS := -m elf_i386 -Ttext 0x1000 --oformat binary -e _start
CC := gcc
CFLAGS := -m32 -ffreestanding -fno-pic -Wall -Wextra -I$(INCLUDE_DIR)
ifeq ($(OPTIMIZE_DEBUG), y)
	CFLAGS += -Og
else
	CFLAGS += -O2
endif


all: $(KERNEL_BIN)

# compile kernel C source files to object files
$(OBJ_DIR)/%.o: $(KERNEL_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling\t\t$(call relpath, $<) to $(call relpath, $@)"
	@$(CC) $(CFLAGS) -c -o $@ $<

# assemble kernel assembly source files to object files
$(OBJ_DIR)/%.o: $(KERNEL_DIR)/%.asm | $(OBJ_DIR)
	@echo "Assembling\t\t$(call relpath, $<) to $(call relpath, $@)"
	@$(ASM) $(ASM_FLAGS) -o $@ $<

# link kernel object files to create the kernel binary
$(KERNEL_BIN): $(KERNEL_OBJS)
	@echo "Linking\t\t\t$(call relpath, $(KERNEL_OBJS)) to create $(call relpath, $(KERNEL_BIN))"
	@$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJS)
	

.PHONY: all
