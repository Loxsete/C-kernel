#include "keyboard_map.h"

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E

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

void kprint(const char *str);
void clear_screen(void);
void kprint_newline(void);
void idt_init(void);
void kb_init(void);
void keyboard_handler_main(void);

int my_strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

int simple_atoi(const char *str) {
    int res = 0;
    while (*str) {
        res = res * 10 + (*str - '0');
        str++;
    }
    return res;
}

void simple_itoa(int num, char *str) {
    int i = 0;
    int is_negative = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    while (num != 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    if (is_negative) str[i++] = '-';
    str[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
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
            vidptr[current_loc++] = 0x07;
        }
        i++;
    }
}

void clear_screen(void) {
    unsigned int i = 0;
    while (i < SCREENSIZE) {
        vidptr[i++] = ' ';
        vidptr[i++] = 0x07;
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
    char keycode;

    write_port(0x20, 0x20);

    status = read_port(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        if (keycode < 0) return;

        if (keycode == ENTER_KEY_CODE) {
            input_buffer[buffer_index] = '\0';
            kprint("\n");

            if (buffer_index > 0) {
                if (my_strcmp(input_buffer, "help") == 0) {
                    kprint("Available commands:\n");
                    kprint("1. help - Show this help message\n");
                    kprint("2. clear - Clear the screen\n");
                    kprint("3. info - Show system information\n");
                    kprint("4. shutdown - Shutdown the system\n");
                } 
                else if (my_strcmp(input_buffer, "clear") == 0) {
                    clear_screen();
                }
                else if (my_strcmp(input_buffer, "info") == 0) {
                    kprint("Loxsete-OS version 1.0\n");
                    kprint("Architecture: x86_64\n");
                    kprint("Kernel: Custom kernel\n");
                }
                else if (my_strcmp(input_buffer, "shutdown") == 0) {
                    kprint("Shutting down...\n");
                    asm volatile ("movl $0, %eax\n\t"
                                  "int $0x19");
                } else {
                    kprint("Unknown command.\n");
                }
            }
            buffer_index = 0;
        } 
        else if (keycode == BACKSPACE_KEY_CODE && buffer_index > 0) {
            buffer_index--;
            current_loc -= 2;
            vidptr[current_loc] = ' ';
        } 
        else {
            char ascii = keyboard_map[(unsigned char)keycode];
            if (ascii != 0) {
                input_buffer[buffer_index++] = ascii;
                vidptr[current_loc++] = ascii;
                vidptr[current_loc++] = 0x07;
            }
        }
    }
}

void kmain(void) {
    clear_screen();
    kprint("Welcome to Loxsete-OS!\n");
    kprint("Type 'help' to see available commands.\n\n");

    idt_init();
    kb_init();
    
    while (1) {
        // Основной цикл работы ОС
    }
}
