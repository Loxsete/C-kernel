#include "debug.h"
#include "graphics.h"
#include "font.h"
#include "utils.h"

#define DEBUG_LINES 16
#define DEBUG_LINE_LENGTH 128
#define DEBUG_X_RIGHT 800 

static char debug_lines[DEBUG_LINES][DEBUG_LINE_LENGTH];
static Color debug_colors[DEBUG_LINES];
static int debug_line_count = 0;

void debug_print(const char *msg, Color color) {
    if (debug_line_count < DEBUG_LINES) {
        debug_line_count++;
    }
    for (int i = DEBUG_LINES - 1; i > 0; i--) {
        str_copy(debug_lines[i], debug_lines[i - 1], DEBUG_LINE_LENGTH);
        debug_colors[i] = debug_colors[i - 1];
    }

    str_copy(debug_lines[0], msg, DEBUG_LINE_LENGTH);
    debug_colors[0] = color;

    draw_rectangle(DEBUG_X_RIGHT, 0, 1024 - DEBUG_X_RIGHT, DEBUG_LINES * 15, 0x00000000);

    for (int i = 0; i < debug_line_count; i++) {
        print_string(DEBUG_X_RIGHT, i * 15, debug_lines[i], debug_colors[i], 1);
    }
}

void debug_print_hex(const char *prefix, unsigned char value) {
    char hex_str[32];
    str_copy(hex_str, prefix, sizeof(hex_str));
    unsigned int len = str_len(hex_str);

    char hex_chars[] = "0123456789ABCDEF";
    hex_str[len] = hex_chars[(value >> 4) & 0xF];
    hex_str[len + 1] = hex_chars[value & 0xF];
    hex_str[len + 2] = '\0';

    debug_print(hex_str, 0xFFFFFF00);
}
