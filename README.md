

---

My C-Kernel

Welcome to my simple C-based kernel project! I’m not an expert in C or assembly, and I barely managed to get a BIOS bootloader working. This project is a learning experiment, so feel free to explore and contribute if you'd like to improve or expand upon it. Any help is appreciated!

About the Project

This project is an attempt to create a basic kernel similar to a Unix-like system. It is not currently functional on real hardware and serves primarily for learning purposes. The code is intentionally simple, making it easier to understand how basic system booting works.

Features

Basic Bootloader in Assembly – A simple BIOS bootloader that prepares the system to load the kernel.

Simple Kernel Logic in C – Basic kernel logic written in C, ready to be expanded.

Cross-Compilation Support – Build and run on different platforms.


How to Build and Run

On Windows

1. Download and install the following tools:

NASM (assembler): nasm.us

GCC (C compiler): gcc.gnu.org

GNU LD (linker): sourceware.org

QEMU (emulator): qemu.org



2. Open Command Prompt and run the following commands:

nasm -f elf32 kernel.asm -o kasm.o

gcc -m32 -c kernel.c -o kc.o

ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o

qemu-system-i386 -kernel kernel



On Linux

1. Install the necessary tools:

sudo apt update

sudo apt install nasm gcc qemu-system-i386 binutils


2. Build the Kernel:

nasm -f elf32 kernel.asm -o kasm.o

gcc -m32 -c kernel.c -o kc.o

ld -m elf_i386 -T link.ld -o kernel kasm.o 
kc.o



3. Run the Kernel in QEMU:

qemu-system-i386 -kernel kernel



Project Structure

kernel.asm – Assembly code for the bootloader, which initializes the system and hands off control to the C code.

kernel.c – Core kernel code in C with basic logic (e.g., printing text).

link.ld – Linker script specifying how to combine object files and set the load address.


Future Improvements

I/O Support – Add support for keyboard and screen I/O.

Memory Management – Implement memory allocation and deallocation.

Multitasking Support – Enable multiple tasks to run simultaneously.

File Manager – Develop support for file systems.



---

Contributing

Contributions are welcome! If you have improvements, ideas, or bug fixes, feel free to fork the repository and open a pull request. I’m happy to review and merge your changes!


---

Tags

#CKernel #Assembly #CProgramming #OperatingSystem #KernelDevelopment #Bootloader #BIOS #LowLevelProgramming #CrossPlatform #LearningProject #QEMU #GCC #NASM #Linux #Windows #UnixLike #SystemsProgramming #MemoryManagement #ProcessScheduling #FileSystem #KernelHacking #EmbeddedSystems #BareMetalProgramming #x86Assembly #OpenSource #CodeLearning #CCompiler #LinkerScript #Emulation #VirtualMachine #SystemCalls #TaskManagement #InterruptHandling #ProtectedMode #RealMode #Ring0

My discord: @bratxz
