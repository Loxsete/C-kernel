#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define IDT_SIZE 256

struct IDT_entry {
    unsigned short offset_lowerbits;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short offset_higherbits;
};

void idt_init(void);
void kb_init(void);
void keyboard_handler_main(void);

#endif
