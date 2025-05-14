# Loxsete-OS: A Minimal x86 Kernel

## Overview

Loxsete-OS is a minimal operating system kernel written in C, targeting the x86 architecture. It provides basic functionality such as keyboard input handling, a simple command-line interface, and text output to a VGA display. This project is designed for educational purposes, demonstrating low-level system programming concepts like interrupt handling, IDT setup, and direct hardware interaction.

## Features

- Basic VGA text mode output for displaying text on the screen.
- Keyboard input processing with support for Shift key modifiers.
- Command-line interface with a dynamic input buffer.
- Interrupt-driven keyboard handling via IDT.
- Simple command execution framework for basic interactivity.

## Prerequisites

To build and run Loxsete-OS, you need the following tools:

- A Linux environment (e.g., Ubuntu) or WSL on Windows.
- gcc (GNU C Compiler).
- nasm (Netwide Assembler).
- grub-mkrescue for creating the bootable ISO.
- qemu-system-i386 for emulation.
- make to automate the build process.

Install these on a Debian-based system with:

```bash
sudo apt update
sudo apt install gcc nasm grub-pc-bin grub-efi qemu-system-x86 make
```

## Building the Kernel

1. Clone or download the project repository.
2. Navigate to the project directory.
3. Run the following command to compile the kernel and create a bootable ISO:

```bash
make
```

## Running the Kernel

To test the kernel in QEMU:

After building, run:

```bash
make run
```

This launches QEMU with the generated ISO, booting Loxsete-OS.

## Using Loxsete-OS

Upon booting, the kernel initializes and displays a welcome message. You can interact with the system via the command-line interface:

- Type commands and press Enter to execute them.
- Use the `help` command to see a list of available commands.
- The kernel supports basic text input, backspace, and Shift for uppercase characters.

## Project Structure

- `kernel.c`: Main kernel code, including initialization, keyboard handling, and command processing.
- `keyboard_map.h`: Defines the keyboard scancode-to-ASCII mapping.
- `mystddef.h`: Custom type definitions.
- `commands.h`: Command-related functions and logic.
- `Makefile`: Automates building and running the kernel.

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a feature branch.
3. Submit a pull request with clear descriptions of your changes.

## Notes

- This is a minimal kernel and does not include advanced features like memory management or multitasking.
- The project is designed for x86 32-bit systems and uses legacy BIOS booting via GRUB.
- For debugging, you can modify the QEMU command in the Makefile to include `-d int,cpu` for detailed logs.

## License

This project is licensed under the MIT License. See the LICENSE file for details (if added).
