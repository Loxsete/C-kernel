#include "keyboard.h"
#include "keyboard_map.h"
#include "graphics.h"
#include "font.h"
#include "utils.h"


#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E

extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);
extern void keyboard_handler(void);

static char input_buffer[256];
static unsigned int buffer_index = 0;
static int shift_pressed = 0;

static struct IDT_entry IDT[IDT_SIZE];

void process_command(char *cmd) {
    Color white = 0xFFFFFFFF;
    static int y_pos = 120;

    draw_rectangle(10, y_pos, 400, 20, 0x00000000);

    if (str_cmp(cmd, "clear") == 0) {
        draw_rectangle(0, 0, 1024, 768, 0x00000000);
        y_pos = 100;
    } else if (str_cmp(cmd, "help") == 0) {
        print_string(10, y_pos, "Commands:", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "1.help", white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "info") == 0) {
            print_string(10, y_pos, "Hello, World!", white, 1);
            y_pos += 20;
    } else if (cmd[0] != '\0') {
        char msg[256] = "Unknown command: ";
        unsigned int msg_len = str_len(msg);
        str_copy(msg + msg_len, cmd, sizeof(msg) - msg_len);
        print_string(10, y_pos, msg, white, 1);
        y_pos += 20;
    }
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

        if (keycode == 0x2A || keycode == 0x36) {
            shift_pressed = 1;
            return;
        }
        if (keycode == 0xAA || keycode == 0xB6) {
            shift_pressed = 0;
            return;
        }

        if (keycode >= 0x80) {
            return;
        }

        unsigned char *current_map = shift_pressed ? shifted_keyboard_map : keyboard_map;
        char ascii = current_map[keycode];

        static int y_pos = 100;
        Color white = 0xFFFFFFFF;

        if (keycode == ENTER_KEY_CODE) {
            input_buffer[buffer_index] = '\0';
            process_command(input_buffer);
            buffer_index = 0;
            draw_rectangle(10, y_pos, 200, 20, 0x00000000);
            print_string(10, y_pos, input_buffer, white, 1);
        } else if (keycode == BACKSPACE_KEY_CODE && buffer_index > 0) {
            buffer_index--;
            input_buffer[buffer_index] = '\0';
            draw_rectangle(10, y_pos, 200, 20, 0x00000000);
            print_string(10, y_pos, input_buffer, white, 1);
        } else if (ascii != 0 && ascii < 0x80) {
            if (buffer_index < sizeof(input_buffer) - 1) {
                input_buffer[buffer_index++] = ascii;
                input_buffer[buffer_index] = '\0';
                draw_rectangle(10, y_pos, 200, 20, 0x00000000);
                print_string(10, y_pos, input_buffer, white, 1);
            }
        }
    }
}
