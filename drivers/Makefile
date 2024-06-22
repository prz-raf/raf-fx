# drivers
# raf-fx drivers Makefile

# build configuration
include $(CONFIG_FILE)

# convert absolute paths to relative paths for printing
relpath = $(patsubst $(MAKE_DIR)/%,%,$(1))


# dirs
DRIVERS_DIR := $(MAKE_DIR)/drivers
KEYBOARD_DIR := $(DRIVERS_DIR)/keyboard
LD_DIR := $(KERNEL_DIR)/ld


# all C and ASM kernel files
KERNEL_SRC := $(wildcard $(KERNEL_DIR)/*.c)
KERNEL_ASM := $(wildcard $(ASM_DIR)/*.asm)


# generate object file names from source file names
KERNEL_OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(KERNEL_SRC:.c=.o))) \
               $(addprefix $(OBJ_DIR)/, $(notdir $(KERNEL_ASM:.asm=.o)))


# tools
ASM := nasm
ASM_FLAGS := -f elf32
LD := ld
LDFLAGS := -m elf_i386 -T $(LD_DIR)/linker.ld --oformat binary
CC := gcc
CFLAGS := -m32 -ffreestanding -fno-pic -Wall -Wextra -I$(INCLUDE_DIR)
ifeq ($(OPTIMIZE_DEBUG), y)
	CFLAGS += -O2 -g
else
	CFLAGS += -O2
endif


all: $(KERNEL_BIN)

# compile kernel C source files to object files
$(OBJ_DIR)/%.o: $(KERNEL_DIR)/%.c | $(OBJ_DIR)
	@echo "Compiling\t\t$(call relpath, $<) to $(call relpath, $@)"
	@$(CC) $(CFLAGS) -c -o $@ $<

# assemble kernel assembly source files to object files
$(OBJ_DIR)/%.o: $(ASM_DIR)/%.asm | $(OBJ_DIR)
	@echo "Assembling\t\t$(call relpath, $<) to $(call relpath, $@)"
	@$(ASM) $(ASM_FLAGS) -o $@ $<

# link kernel object files to create the kernel binary
$(KERNEL_BIN): $(KERNEL_OBJS)
	@echo "Linking\t\t\t$(call relpath, $(KERNEL_OBJS)) to create $(call relpath, $(KERNEL_BIN))"
	@$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJS)

.PHONY: all
