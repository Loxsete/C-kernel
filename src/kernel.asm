bits 32
section .multiboot
align 8
mb2_header_start:
    ; === Multiboot2 Header (type = 0) ===
    dd 0xE85250D6               ; magic
    dd 0                        ; architecture = i386
    dd mb2_header_end - mb2_header_start ; length
    dd 0x100000000 - (0xE85250D6 + 0 + (mb2_header_end - mb2_header_start)) ; checksum
    ; === Framebuffer Tag (type = 5) ===
    align 8
    dw 5                        ; type = framebuffer
    dw 0                        ; flags = 0 (optional)
    dd 20                       ; size of this tag
    dd 1280                     ; width
    dd 720                      ; height
    dd 32                       ; depth (bits per pixel)
    ; === End Tag (type = 0) ===
    align 8
    dd 0                        ; type = 0
    dd 8                        ; size = 8
align 8
mb2_header_end:

section .text
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
    push ebx   
    call kmain         
    hlt    
.halt:
    jmp .halt

section .bss
align 16
resb 8192
stack_top:
