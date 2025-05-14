#include "keyboard_map.h"
#include "mystddef.h"
#include "commands.h"
#include "kernel.h"

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E

#define WHITE_ON_BLACK 0x0F

extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);

unsigned int current_loc = 0;
char *vidptr = (char*)0xb8000;

char input_buffer[256];
unsigned int buffer_index = 0;

#define IDT_SIZE 256

struct IDT_entry {
    unsigned short offset_lowerbits;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

// Track Shift state
static int shift_pressed = 0;

int my_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

void kprint(const char *str) {
    unsigned int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            kprint_newline();
        } else {
            if (current_loc >= SCREENSIZE) {
                current_loc = 0;
                clear_screen();
            }
            vidptr[current_loc++] = str[i];
            vidptr[current_loc++] = WHITE_ON_BLACK;
        }
        i++;
    }
}

void clear_screen(void) {
    unsigned int i = 0;
    while (i < SCREENSIZE) {
        vidptr[i++] = ' ';
        vidptr[i++] = WHITE_ON_BLACK;
    }
    current_loc = 0;
}

void kprint_newline(void) {
    unsigned int line_size = BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE;
    current_loc = current_loc + (line_size - current_loc % (line_size));
}

void idt_init(void) {
    unsigned long keyboard_address;
    unsigned long idt_address;
    unsigned long idt_ptr[2];
    keyboard_address = (unsigned long)keyboard_handler;
    IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
    IDT[0x21].selector = 0x08;
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = 0x8e;
    IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

    write_port(0x20, 0x11);
    write_port(0xA0, 0x11);
    write_port(0x21, 0x20);
    write_port(0xA1, 0x28);
    write_port(0x21, 0x00);
    write_port(0xA1, 0x00);
    write_port(0x21, 0x01);
    write_port(0xA1, 0x01);
    write_port(0x21, 0xff);
    write_port(0xA1, 0xff);

    idt_address = (unsigned long)IDT;
    idt_ptr[0] = (sizeof(struct IDT_entry) * 256) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
}

void kb_init(void) {
    write_port(0x21, 0xFD);
}

void keyboard_handler_main(void) {
    unsigned char status;
    unsigned char keycode; 

    write_port(0x20, 0x20);

    status = read_port(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);

        // Handle Shift press/release
        if (keycode == 0x2A || keycode == 0x36) { // Left Shift or Right Shift
            shift_pressed = 1;
            return;
        }
        if (keycode == 0xAA || keycode == 0xB6) { // Left Shift release or Right Shift release
            shift_pressed = 0;
            return;
        }

        // Ignore key release codes (0x80 and above) for non-Shift keys
        if (keycode >= 0x80) {
            return;
        }

        // Select keyboard map based on Shift state
        unsigned char *current_map = shift_pressed ? shifted_keyboard_map : keyboard_map;
        char ascii = current_map[keycode];

        if (keycode == ENTER_KEY_CODE) {
            input_buffer[buffer_index] = '\0';
            kprint("\n");

            if (buffer_index > 0) {
                if (my_strcmp(input_buffer, "help") == 0) {
                    help();
                } else if (my_strcmp(input_buffer, "clear") == 0) {
                    clear_screen();
                } else if (my_strcmp(input_buffer, "info") == 0) {
                    info();
                } else if (my_strcmp(input_buffer, "calc") == 0) {
                    kprint("Error: Provide an expression, e.g., calc 2+2\n");
                } else if (input_buffer[0] == 'c' && input_buffer[1] == 'a' && 
                           input_buffer[2] == 'l' && input_buffer[3] == 'c' && 
                           input_buffer[4] == ' ') {
                    calc(input_buffer);
                } else {
                    kprint("Unknown command.\n");
                }
            }
            buffer_index = 0;
        } else if (keycode == BACKSPACE_KEY_CODE && buffer_index > 0) {
            buffer_index--;
            current_loc -= 2;
            vidptr[current_loc] = ' ';
        } else if (ascii != 0 && ascii < 0x80) { // Only process printable ASCII
            input_buffer[buffer_index++] = ascii;
            vidptr[current_loc++] = ascii;
            vidptr[current_loc++] = WHITE_ON_BLACK;
        }
    }
}

void kmain(void) {
    idt_init();
    kb_init();
    clear_screen();
    info();
    kprint("Welcome to Loxsete-OS!\n");
    kprint("Type 'help' to see the list of commands.\n");
    kprint("\n");

    while (1) {
    }
}
