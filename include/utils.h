#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

int my_strlen(const char* str);
void uint_to_str(uint32_t value, char* buffer);
void uint64_to_str(uint64_t value, char* buffer);
void trim_string(char* str);
unsigned int str_len(const char *str);
int str_cmp(const char *s1, const char *s2);
void str_copy(char *dest, const char *src, unsigned int max_len);
int strncmp(const char *s1, const char *s2, unsigned int n);

#endif // UTILS_H
