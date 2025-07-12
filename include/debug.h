#ifndef DEBUG_H
#define DEBUG_H

#include "graphics.h"

void debug_print(const char *msg, Color color);
void debug_print_hex(const char *prefix, unsigned char value);

extern int debug_y;

#endif
