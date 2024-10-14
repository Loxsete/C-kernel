# C-kernel
My C-Kernel
I'm not a super person in C or assembler, I barely found the BIOS bootloader, so please don't hate me :)
I'm just trying to code shit
And now a little about the code, here is a similar Unix kernel, it doesn’t work on a real PC. If anyone wants, you can modify it, and I won’t mind.
How to compile this?
If you are on Windows:
1.Download NASM
2.Download GSS
3.Download GNU LD
4.Download QEMU System 86
4.nasm -f elf32 kernel.asm -o kasm.o
5.gcc -m32 -c kernel.c -o kc.o
6.ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
7. qemu-system-i386 -kernel kernel.bin
(All command on cmd)
In linux maybe you know.
