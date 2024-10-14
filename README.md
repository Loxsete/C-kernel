

My C-Kernel

Welcome to my simple C-based kernel project! I’m not an expert in C or assembly, and I barely managed to get a BIOS bootloader working. So, please be patient as I’m just experimenting and learning here. Feel free to contribute or modify the code if you'd like—any help is appreciated!

About the Project

This project is a basic attempt at creating a kernel similar to a Unix-like system. However, it is not functional on real hardware at the moment and serves primarily for learning purposes.

Features

A basic bootloader in assembly.

Simple kernel logic written in C.

Cross-compilation support.


How to Build and Run

On Windows

To compile the kernel on Windows, follow these steps:

1. Download and install the following tools:

NASM (for assembly code) 
https://www.nasm.us/

GCC (for compiling C code)
https://gcc.gnu.org/

GNU LD (for linking)
https://sourceware.org/binutils/docs/ld/

QEMU (for emulating the kernel)
https://www.qemu.org/


2. Open cmd (Command Prompt) and run the following commands:



nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kc.o
ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
qemu-system-i386 -kernel kernel

On Linux

If you're on Linux, you're probably familiar with the necessary tools. The steps are similar, just make sure you have nasm, gcc, ld, and qemu installed. You can use the same commands as above in your terminal.

Contributing

Contributions are welcome! If you have improvements, ideas, or bug fixes, feel free to fork the repository and open a pull request. I'm happy to review and merge them.



