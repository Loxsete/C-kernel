#include "keyboard_map.h"
#include <string.h>

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE (BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES)

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E

extern unsigned char keyboard_map[128];

static inline void write_port(unsigned short port, unsigned char data) {
    asm volatile ("outb %0, %1" :: "a"(data), "Nd"(port));
}

static inline unsigned char read_port(unsigned short port) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

unsigned int current_loc = 0;
char *vidptr = (char*)0xb8000;
char input_buffer[256];
unsigned int input_pos = 0;

void shutdown(void) {
    asm volatile ("movl $0, %eax\n\t"
                  "int $0x19");
}

void restart(void) {
    asm volatile ("movl $0, %eax\n\t"
                  "int $0x19");
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void clear_screen(void) {
    for (int i = 0; i < COLUMNS_IN_LINE * LINES; i++) {
        vidptr[i * BYTES_FOR_EACH_ELEMENT] = ' ';
        vidptr[i * BYTES_FOR_EACH_ELEMENT + 1] = 0x07;
    }
    current_loc = 0;
}

void display_prompt(void) {
    const char *prompt = "Loxsete $: ";
    for (unsigned int i = 0; prompt[i] != '\0'; i++) {
        vidptr[current_loc++] = prompt[i];
        vidptr[current_loc++] = 0x07;
    }
}

int check_shutdown_command(void) {
    if (my_strcmp(input_buffer, "shutdown") == 0) {
        shutdown();
        return 1;
    } else if (my_strcmp(input_buffer, "restart") == 0) {
        restart();
        return 1;
    }
    return 0;
}

void process_command(void) {
    input_buffer[input_pos] = '\0';
    if (check_shutdown_command()) {
        clear_screen();
        const char *shutdown_msg = "Shutting down...";
        for (unsigned int i = 0; shutdown_msg[i] != '\0'; i++) {
            vidptr[current_loc++] = shutdown_msg[i];
            vidptr[current_loc++] = 0x07;
        }
        while (1);
    }
    unsigned int line_start = (current_loc / (BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE)) * (BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE) + 12;
    for (unsigned int i = line_start + 2; i < current_loc; i += 2) {
        vidptr[i] = ' ';
        vidptr[i + 1] = 0x07;
    }
    current_loc = line_start + 2;
    input_pos = 0;
    display_prompt();
}

void keyboard_handler_main(void) {
    unsigned char status;
    char keycode;

    status = read_port(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        if (keycode < 0 || keycode >= 128) return;

        if (keycode == ENTER_KEY_CODE) {
            process_command();
            return;
        }
        else if (keycode == BACKSPACE_KEY_CODE) {
            if (input_pos > 0 && current_loc > 12) {
                input_pos--;
                current_loc -= 2;
                vidptr[current_loc] = ' ';
                vidptr[current_loc + 1] = 0x07;
            }
            return;
        }

        if (input_pos < sizeof(input_buffer) - 1 && current_loc < (BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE)) {
            char c = keyboard_map[(unsigned char)keycode];
            if (c != 0) {
                vidptr[current_loc++] = c;
                vidptr[current_loc++] = 0x07;
                input_buffer[input_pos++] = c;
            }
        }
    }

    write_port(0x20, 0x20);
}

void kmain(void) {
    clear_screen();
    display_prompt();

    while (1) {
        keyboard_handler_main();
    }
}
