include config.mk

# Directories
SRC_DIR := src
BUILD_DIR := build
BUILD_C := $(BUILD_DIR)/c
BUILD_ASM := $(BUILD_DIR)/asm
ISO_DIR := iso

# Compiler/Assembler/Linker Flags
TARGET_ASMFLAGS += -f elf
TARGET_CFLAGS += -nostdlib -ffreestanding -m32 -Iinclude
TARGET_LINKFLAGS += -T link.ld -nostdlib
TARGET_LIBS += -lgcc

# Sources and headers
SOURCES_C := $(shell find $(SRC_DIR) -type f -name "*.c")
SOURCES_ASM := $(shell find $(SRC_DIR) -type f -name "*.asm")
HEADERS_C := $(shell find $(SRC_DIR) -type f -name "*.h")
HEADERS_ASM := $(shell find $(SRC_DIR) -type f -name "*.inc")

# Object files
OBJECTS_C := $(patsubst $(SRC_DIR)/%.c, $(BUILD_C)/%.o, $(SOURCES_C))
OBJECTS_ASM := $(patsubst $(SRC_DIR)/%.asm, $(BUILD_ASM)/%.o, $(SOURCES_ASM))

# Final targets
ISO_IMAGE := loxsete-os.iso
KERNEL_ELF := $(BUILD_DIR)/kernel.bin

.PHONY: all clean run always

all: $(ISO_IMAGE)

$(ISO_IMAGE): $(KERNEL_ELF) grub.cfg
	@echo "Creating ISO..."
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp $< $(ISO_DIR)/boot/kernel.bin
	@cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	@grub-mkrescue $(ISO_DIR) -o $@
	@echo "Build done!"

$(KERNEL_ELF): $(OBJECTS_ASM) $(OBJECTS_C)
	@echo "Linking $@"
	@$(TARGET_LD) $(TARGET_LINKFLAGS) -Wl,-Map=$(BUILD_DIR)/image.map -o $@ $^ $(TARGET_LIBS)

# C compilation
$(BUILD_C)/%.o: $(SRC_DIR)/%.c $(HEADERS_C)
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@$(TARGET_CC) $(TARGET_CFLAGS) -c -o $@ $<

# ASM compilation
$(BUILD_ASM)/%.o: $(SRC_DIR)/%.asm $(HEADERS_ASM)
	@echo "Assembling $<"
	@mkdir -p $(@D)
	@$(TARGET_ASM) $(TARGET_ASMFLAGS) -o $@ $<

run: all
	@qemu-system-i386 -cdrom $(ISO_IMAGE) -m 1024M --enable-kvm -serial stdio
clean:
	@rm -rf $(BUILD_DIR) $(ISO_IMAGE) $(ISO_DIR) bin
