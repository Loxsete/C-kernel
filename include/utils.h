#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

// Порты I/O
void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

// Строковые функции
unsigned int str_len(const char *str);
int my_strlen(const char* str);
int str_cmp(const char *s1, const char *s2);
void str_copy(char *dest, const char *src, unsigned int max_len);
int strncmp(const char *s1, const char *s2, unsigned int n);
void trim_string(char* str);

// Конвертация чисел
void uint32_to_str(uint32_t value, char *buffer, uint32_t buffer_size);
void uint_to_str(uint32_t value, char* buffer);
void uint64_to_str(uint64_t value, char* buffer);

#endif
