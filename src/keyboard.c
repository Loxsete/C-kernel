#include "keyboard.h"
#include "keyboard_map.h"
#include "graphics.h"
#include "font.h"
#include "utils.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E
#define COM1_PORT 0x3F8

extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);
extern void keyboard_handler(void);

static char input_buffer[256];
static unsigned int buffer_index = 0;
static int shift_pressed = 0;
static char com_buffer[256];
static unsigned int com_buffer_index = 0;
static int y_pos = 100;
static Color white = 0xFFFFFFFF;
static Color green = 0xFF00FF00;
static Color red = 0xFFFF0000;
static Color yellow = 0xFFFFFF00;
static int debug_y = 600;

static struct IDT_entry IDT[IDT_SIZE];

void debug_print(const char *msg, Color color) {
    if (debug_y >= 760) {
        draw_rectangle(0, 600, 1024, 168, 0x00000000);
        debug_y = 600;
    }
    print_string(10, debug_y, msg, color, 1);
    debug_y += 15;
}

void debug_print_hex(const char *prefix, unsigned char value) {
    char hex_str[32];
    str_copy(hex_str, prefix, sizeof(hex_str));
    unsigned int len = str_len(hex_str);
    
    char hex_chars[] = "0123456789ABCDEF";
    hex_str[len] = hex_chars[(value >> 4) & 0xF];
    hex_str[len + 1] = hex_chars[value & 0xF];
    hex_str[len + 2] = '\0';
    
    debug_print(hex_str, yellow);
}

void com_init(void) {
    debug_print("COM1 init started", green);
    
    write_port(COM1_PORT + 1, 0x00);
    debug_print("Interrupts disabled", green);
    
    write_port(COM1_PORT + 3, 0x80);
    debug_print("DLAB enabled", green);
    
    write_port(COM1_PORT + 0, 0x0C);
    write_port(COM1_PORT + 1, 0x00);
    debug_print("Baud 9600 set", green);
    
    write_port(COM1_PORT + 3, 0x03);
    debug_print("8N1 configured", green);
    
    write_port(COM1_PORT + 2, 0xC7);
    debug_print("FIFO enabled", green);
    
    write_port(COM1_PORT + 4, 0x0B);
    debug_print("RTS/DTR set", green);
    
    unsigned char status = read_port(COM1_PORT + 5);
    debug_print_hex("COM1 status: 0x", status);
    
    debug_print("COM1 init complete", green);
}

void com_send_char(char c) {
    int timeout = 0;
    while (!(read_port(COM1_PORT + 5) & 0x20)) {
        timeout++;
        if (timeout > 100000) {
            debug_print("Send timeout", red);
            return;
        }
    }
    write_port(COM1_PORT, c);
    debug_print_hex("Sent char: 0x", (unsigned char)c);
}

void com_send_string(const char *str) {
    debug_print("Sending string", green);
    while (*str) {
        com_send_char(*str++);
    }
    com_send_char('\n');
    debug_print("String sent", green);
}

int com_data_available(void) {
    unsigned char status = read_port(COM1_PORT + 5);
    int available = status & 0x01;
    if (available) {
        debug_print_hex("Data available, status: 0x", status);
    }
    return available;
}

char com_read_char(void) {
    int timeout = 0;
    while (timeout < 50000) {
        unsigned char status = read_port(COM1_PORT + 5);
        if (status & 0x01) {
            char c = read_port(COM1_PORT);
            debug_print_hex("Received char: 0x", (unsigned char)c);
            if (c >= 32 && c <= 126) {
                char readable[16] = "Char: ";
                readable[6] = c;
                readable[7] = '\0';
                debug_print(readable, green);
            }
            return c;
        }
        timeout++;
        if (timeout % 10000 == 0) {
            debug_print_hex("Waiting data, status: 0x", status);
        }
    }
    debug_print("Read timeout", red);
    return 0;
}

void process_command(char *cmd) {
    if (y_pos >= 700) y_pos = 100;
    draw_rectangle(10, y_pos, 400, 20, 0x00000000);

    if (str_cmp(cmd, "clear") == 0) {
        draw_rectangle(0, 0, 1024, 768, 0x00000000);
        y_pos = 100;
        debug_y = 600;
    } else if (str_cmp(cmd, "help") == 0) {
        print_string(10, y_pos, "Commands:", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "1. help - show help", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "2. com <text> - send text", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "3. comtest - test COM", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "4. comstatus - COM status", white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "info") == 0) {
        print_string(10, y_pos, "Hello, World!", white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "comtest") == 0) {
        debug_print("Testing COM port", green);
        com_send_string("TEST MESSAGE FROM OS");
        print_string(10, y_pos, "Test message sent", white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "comstatus") == 0) {
        unsigned char status = read_port(COM1_PORT + 5);
        debug_print_hex("Current COM1 status: 0x", status);
        print_string(10, y_pos, "Status output to debug", white, 1);
        y_pos += 20;

    } else if (str_cmp(cmd, "comcrush") == 0) {
        debug_print("Sending garbage...", red);
        for (int i = 0; i < 512; i++) {
            com_send_char(0xFF);  
        }
        debug_print("Garbage sent.", red);
        print_string(10, y_pos, "Sent garbage to COM", white, 1);
        y_pos += 20;
    	debug_print("Garbage sent.", red);
    	print_string(10, y_pos, "Sent garbage to COM", white, 1);
    	y_pos += 20;
    } else if (strncmp(cmd, "com ", 4) == 0 && cmd[4] != '\0') {
        debug_print("COM command received", green);
        com_send_string(cmd + 4);
        print_string(10, y_pos, "Sent: ", white, 1);
        print_string(110, y_pos, cmd + 4, white, 1);
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
    com_init();
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

    if (com_data_available()) {
        debug_print("COM data detected!", green);
        char c = com_read_char();
        if (c == 0) {
            debug_print("No data received!", red);
            return;
        }
        if (y_pos >= 700) y_pos = 100;
        if (c == '\n' || c == '\r' || com_buffer_index >= sizeof(com_buffer) - 1) {
            com_buffer[com_buffer_index] = '\0';
            if (com_buffer_index > 0) {
                print_string(10, y_pos + 40, "Received: ", white, 1);
                print_string(90, y_pos + 40, com_buffer, white, 1);
                debug_print("String processed", green);
                y_pos += 20;
            }
            com_buffer_index = 0;
        } else if (c >= 32 && c <= 126) {
            com_buffer[com_buffer_index++] = c;
            debug_print("Char added to buffer", green);
        }
    }
}
