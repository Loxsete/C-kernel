bits 32
section .text
align 4

; ==== Multiboot header ====
dd 0x1BADB002              ; magic
dd 0x00                    ; flags
dd -(0x1BADB002 + 0x00)    ; checksum

global start
global keyboard_handler
global read_port
global write_port
global load_idt

extern kmain
extern keyboard_handler_main

; ==== GDT ====

gdt_start:
    dq 0x0000000000000000             ; null
    dq 0x00CF9A000000FFFF             ; code (offset 0x08)
    dq 0x00CF92000000FFFF             ; data (offset 0x10)
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

load_gdt:
    lgdt [gdt_descriptor]

    ; Обновим сегменты
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:flush_cs     

flush_cs:
    ret

; ==== I/O ====

read_port:
    mov edx, [esp + 4]
    in al, dx
    ret

write_port:
    mov edx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret



load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti
    ret



keyboard_handler:
    call keyboard_handler_main
    iretd



start:
    cli
    call load_gdt

    mov esp, stack_top     

    call kmain             
    hlt                    



section .bss
align 16
resb 8192
stack_top:
