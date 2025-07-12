#include "com.h"
#include "debug.h"
#include "utils.h"

#define COM1_PORT 0x3F8

extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);

int debug_y = 600;


void com_init(void) {
    debug_print("COM1 init started", 0xFF00FF00);

    write_port(COM1_PORT + 1, 0x00);
    write_port(COM1_PORT + 3, 0x80);
    write_port(COM1_PORT + 0, 0x0C);
    write_port(COM1_PORT + 1, 0x00);
    write_port(COM1_PORT + 3, 0x03);
    write_port(COM1_PORT + 2, 0xC7);
    write_port(COM1_PORT + 4, 0x0B);

    unsigned char status = read_port(COM1_PORT + 5);
    debug_print_hex("COM1 status: 0x", status);

    debug_print("COM1 init complete", 0xFF00FF00);
}

void com_send_char(char c) {
    int timeout = 0;
    while (!(read_port(COM1_PORT + 5) & 0x20)) {
        timeout++;
        if (timeout > 100000) {
            debug_print("Send timeout", 0xFFFF0000);
            return;
        }
    }
    write_port(COM1_PORT, c);
    debug_print_hex("Sent char: 0x", (unsigned char)c);
}

void com_send_string(const char *str) {
    debug_print("Sending string", 0xFF00FF00);
    while (*str) {
        com_send_char(*str++);
    }
    com_send_char('\n');
    debug_print("String sent", 0xFF00FF00);
}

int com_data_available(void) {
    unsigned char status = read_port(COM1_PORT + 5);
    if (status & 0x01) {
        debug_print_hex("Data available, status: 0x", status);
    }
    return status & 0x01;
}

char com_read_char(void) {
    int timeout = 0;
    while (timeout < 50000) {
        unsigned char status = read_port(COM1_PORT + 5);
        if (status & 0x01) {
            char c = read_port(COM1_PORT);
            debug_print_hex("Received char: 0x", (unsigned char)c);
            return c;
        }
        timeout++;
    }
    debug_print("Read timeout", 0xFFFF0000);
    return 0;
}
