#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

int my_strlen(const char* str);
void uint_to_str(uint32_t value, char* buffer);
void uint64_to_str(uint64_t value, char* buffer);
void trim_string(char* str);

#endif // UTILS_H
