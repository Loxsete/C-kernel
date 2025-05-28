#include "utils.h"

int my_strlen(const char* str) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

void uint_to_str(uint32_t value, char* buffer) {
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    
    char temp[12];
    int i = 0;
    
    while (value > 0) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }
    
    int j = 0;
    while (i > 0) {
        buffer[j++] = temp[--i];
    }
    buffer[j] = '\0';
}

void uint64_to_str(uint64_t value, char* buffer) {
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    
    char temp[21];
    int i = 0;
    
    while (value > 0) {
        temp[i++] = '0' + (value % 10);
        value /= 10;
    }
    
    int j = 0;
    while (i > 0) {
        buffer[j++] = temp[--i];
    }
    buffer[j] = '\0';
}

void trim_string(char* str) {
    char* start = str;
    char* end;
    
    while (*start == ' ') start++;
    
    if (*start == '\0') {
        str[0] = '\0';
        return;
    }
    
    end = start + my_strlen(start) - 1;
    while (end > start && *end == ' ') end--;
    
    int len = end - start + 1;
    for (int i = 0; i < len; i++) {
        str[i] = start[i];
    }
    str[len] = '\0';
}

static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}
