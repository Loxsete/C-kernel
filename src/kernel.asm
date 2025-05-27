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
extern kmain
start:
    cli
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
