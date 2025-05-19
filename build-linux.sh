#!/bin/bash

# Compilers and tools
NASM=nasm
GCC=gcc
LD=ld
GRUBMKRESCUE=grub-mkrescue
QEMU=qemu-system-i386

# Flags
NASMFLAGS="-f elf32"
CFLAGS="-m32 -fno-stack-protector -ffreestanding -c -Iinclude"
LDFLAGS="-m elf_i386 -T link.ld"

# Directories
BIN_DIR="bin"
SRC_DIR="src"
INCLUDE_DIR="include"
ISO_DIR="iso/boot/grub"

# Files
KERNEL="$BIN_DIR/kernel.bin"
ISO="loxsete-os.iso"
GRUB_CFG_PATH="$ISO_DIR/grub.cfg"

# Sources
ASM_SRC="$SRC_DIR/kernel.asm"
C_SRC=("$SRC_DIR/kernel.c" "$SRC_DIR/commands.c" "$SRC_DIR/calc.c")

# Objects
ASM_OBJ="$BIN_DIR/boot.o"
C_OBJ=("$BIN_DIR/kmain.o" "$BIN_DIR/commands.o" "$BIN_DIR/calc.o")

mkdir -p "$BIN_DIR"

echo "[1/5] Assembling ASM"
$NASM $NASMFLAGS "$ASM_SRC" -o "$ASM_OBJ"

echo "[2/5] Compiling C"
$GCC $CFLAGS "${C_SRC[0]}" -o "${C_OBJ[0]}"
$GCC $CFLAGS "${C_SRC[1]}" -o "${C_OBJ[1]}"
$GCC $CFLAGS "${C_SRC[2]}" -o "${C_OBJ[2]}"

echo "[3/5] Linking kernel"
$LD $LDFLAGS -o "$KERNEL" "$ASM_OBJ" "${C_OBJ[@]}"

echo "[4/5] Creating grub.cfg"
mkdir -p "$ISO_DIR"
cat > "$GRUB_CFG_PATH" <<EOF
menuentry "Loxsete-OS" {
    multiboot /boot/kernel.bin
    boot
}
EOF

echo "[5/5] Creating ISO"
cp "$KERNEL" iso/boot/
$GRUBMKRESCUE -o "$ISO" iso

# Run if "run" argument is given
if [[ "$1" == "run" ]]; then
    echo "[Running in QEMU]"
    $QEMU -cdrom "$ISO"
fi

# Clean if "clean" argument is given
if [[ "$1" == "clean" ]]; then
    echo "[Cleaning]"
    rm -rf "$BIN_DIR" "$ISO" iso grub.cfg
fi
