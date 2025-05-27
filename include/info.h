#ifndef INFO_H
#define INFO_H

#include <stdint.h>
#include <multiboot.h>

// Структура для хранения информации о системе
typedef struct {
    uint32_t screen_width;
    uint32_t screen_height;
    uint32_t screen_bpp;
    uint32_t cpu_freq_mhz;
    char cpu_vendor[13];
    char cpu_brand[49];
    uint64_t total_memory;
    uint64_t available_memory;
} system_info_t;

// Функции для получения системной информации
void get_system_info(system_info_t* info, multiboot_tag_framebuffer_t* fb);
void display_system_info(system_info_t* info, uint32_t x, uint32_t y, uint32_t color, uint32_t scale);
void get_cpu_info(system_info_t* info);
void get_memory_info(system_info_t* info, uint32_t mbinfo_ptr);
uint32_t estimate_cpu_frequency();

#endif // INFO_H
