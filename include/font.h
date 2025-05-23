#pragma once
#include <stdint.h>

typedef uint32_t Color; 

void character(uint16_t x, uint16_t y, char c, Color color, uint16_t size);
void print_string(uint16_t x, uint16_t y, const char* str, Color color, uint16_t size);
