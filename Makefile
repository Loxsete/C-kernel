# Компиляторы и утилиты
NASM = nasm
GCC = gcc
LD = ld
GRUBMKRESCUE = grub-mkrescue
QEMU = qemu-system-i386

# Флаги
NASMFLAGS = -f elf32
CFLAGS = -m32 -fno-stack-protector -ffreestanding -c -Iinclude
LDFLAGS = -m elf_i386 -T link.ld

# Директории
BIN_DIR = bin
SRC_DIR = src
INCLUDE_DIR = include
ISO_DIR = iso/boot/grub

# Файлы
KERNEL = $(BIN_DIR)/kernel.bin
ISO = loxsete-os.iso
GRUB_CFG_PATH = iso/boot/grub/grub.cfg

# Исходники
ASM_SRC = $(SRC_DIR)/kernel.asm
C_SRC = $(SRC_DIR)/kernel.c $(SRC_DIR)/commands.c $(SRC_DIR)/calc.c

# Объекты
ASM_OBJ = $(BIN_DIR)/boot.o
C_OBJ = $(BIN_DIR)/kmain.o $(BIN_DIR)/commands.o $(BIN_DIR)/calc.o

# Основная цель
all: $(ISO)

# Создание директории bin
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Компиляция ASM
$(ASM_OBJ): $(ASM_SRC) | $(BIN_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@

# Компиляция C
$(BIN_DIR)/kmain.o: $(SRC_DIR)/kernel.c | $(BIN_DIR)
	$(GCC) $(CFLAGS) $< -o $@

$(BIN_DIR)/commands.o: $(SRC_DIR)/commands.c | $(BIN_DIR)
	$(GCC) $(CFLAGS) $< -o $@

$(BIN_DIR)/calc.o: $(SRC_DIR)/calc.c | $(BIN_DIR)
	$(GCC) $(CFLAGS) $< -o $@

# Линковка ядра
$(KERNEL): $(ASM_OBJ) $(C_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Создание ISO
$(ISO): $(KERNEL) grub.cfg
	mkdir -p iso/boot/grub
	cp $(KERNEL) iso/boot/
	cp grub.cfg $(GRUB_CFG_PATH)
	$(GRUBMKRESCUE) -o $(ISO) iso

# Запуск
run: all
	$(QEMU) -cdrom $(ISO)

# Очистка
clean:
	rm -rf $(BIN_DIR) *.o $(ISO) iso

# Создание grub.cfg
grub.cfg:
	echo 'menuentry "Loxsete-OS" {' > grub.cfg
	echo '    multiboot /boot/kernel.bin' >> grub.cfg
	echo '    boot' >> grub.cfg
	echo '}' >> grub.cfg

.PHONY: all run clean
