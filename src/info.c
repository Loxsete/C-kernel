#include "info.h"
#include <font.h>
#include <graphics.h>

static inline void cpuid(uint32_t leaf, uint32_t* eax, uint32_t* ebx, uint32_t* ecx, uint32_t* edx) {
    __asm__ volatile("cpuid"
                     : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
                     : "a"(leaf));
}

static inline uint64_t rdtsc() {
    uint32_t low, high;
    __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
    return ((uint64_t)high << 32) | low;
}

void delay_ms(uint32_t ms) {
    volatile uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 1000; j++) {
            __asm__ volatile("nop");
        }
    }
}

void get_cpu_info(system_info_t* info) {
    uint32_t eax, ebx, ecx, edx;
    
    cpuid(0, &eax, &ebx, &ecx, &edx);
    
    *((uint32_t*)&info->cpu_vendor[0]) = ebx;
    *((uint32_t*)&info->cpu_vendor[4]) = edx;
    *((uint32_t*)&info->cpu_vendor[8]) = ecx;
    info->cpu_vendor[12] = '\0';
    
    cpuid(0x80000000, &eax, &ebx, &ecx, &edx);
    if (eax >= 0x80000004) {
        cpuid(0x80000002, &eax, &ebx, &ecx, &edx);
        *((uint32_t*)&info->cpu_brand[0]) = eax;
        *((uint32_t*)&info->cpu_brand[4]) = ebx;
        *((uint32_t*)&info->cpu_brand[8]) = ecx;
        *((uint32_t*)&info->cpu_brand[12]) = edx;
        
        cpuid(0x80000003, &eax, &ebx, &ecx, &edx);
        *((uint32_t*)&info->cpu_brand[16]) = eax;
        *((uint32_t*)&info->cpu_brand[20]) = ebx;
        *((uint32_t*)&info->cpu_brand[24]) = ecx;
        *((uint32_t*)&info->cpu_brand[28]) = edx;
        
        cpuid(0x80000004, &eax, &ebx, &ecx, &edx);
        *((uint32_t*)&info->cpu_brand[32]) = eax;
        *((uint32_t*)&info->cpu_brand[36]) = ebx;
        *((uint32_t*)&info->cpu_brand[40]) = ecx;
        *((uint32_t*)&info->cpu_brand[44]) = edx;
        
        info->cpu_brand[48] = '\0';
    } else {
        for (int i = 0; i < 12 && i < 48; i++) {
            info->cpu_brand[i] = info->cpu_vendor[i];
        }
        info->cpu_brand[12] = '\0';
    }
}

uint32_t estimate_cpu_frequency() {
    uint64_t start_tsc, end_tsc;
    
    start_tsc = rdtsc();
    delay_ms(100);
    end_tsc = rdtsc();
    
    uint64_t cycles = end_tsc - start_tsc;
    uint32_t freq_mhz = (uint32_t)(cycles / 100000);
    
    return freq_mhz;
}

void get_system_info(system_info_t* info, multiboot_tag_framebuffer_t* fb) {
    info->screen_width = fb->framebuffer_width;
    info->screen_height = fb->framebuffer_height;
    info->screen_bpp = fb->framebuffer_bpp;
    
    get_cpu_info(info);
    info->cpu_freq_mhz = estimate_cpu_frequency();
}

static void uint_to_str(uint32_t value, char* buffer) {
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

static void trim_string(char* str) {
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

void display_system_info(system_info_t* info, uint32_t x, uint32_t y, uint32_t color, uint32_t scale) {
    char buffer[64];
    uint32_t line_height = 20 * scale;
    uint32_t current_y = y;
    
    print_string(x, current_y, "=== SYSTEM INFO ===", color, scale);
    current_y += line_height;
    
    print_string(x, current_y, "Screen: ", color, scale);
    uint_to_str(info->screen_width, buffer);
    print_string(x + 80 * scale, current_y, buffer, color, scale);
    print_string(x + 80 * scale + my_strlen(buffer) * 8 * scale, current_y, "x", color, scale);
    
    uint_to_str(info->screen_height, buffer);
    print_string(x + 80 * scale + (my_strlen(buffer) + 1) * 8 * scale, current_y, buffer, color, scale);
    
    uint_to_str(info->screen_bpp, buffer);
    print_string(x + 180 * scale, current_y, " (", color, scale);
    print_string(x + 200 * scale, current_y, buffer, color, scale);
    print_string(x + 200 * scale + my_strlen(buffer) * 8 * scale, current_y, " bpp)", color, scale);
    current_y += line_height;
    
    print_string(x, current_y, "CPU Freq: ~", color, scale);
    uint_to_str(info->cpu_freq_mhz, buffer);
    print_string(x + 88 * scale, current_y, buffer, color, scale);
    print_string(x + 88 * scale + my_strlen(buffer) * 8 * scale, current_y, " MHz", color, scale);
    current_y += line_height;
    
    print_string(x, current_y, "CPU Vendor: ", color, scale);
    print_string(x + 96 * scale, current_y, info->cpu_vendor, color, scale);
    current_y += line_height;
    
    trim_string(info->cpu_brand);
    if (my_strlen(info->cpu_brand) > 0 && info->cpu_brand[0] != '\0') {
        print_string(x, current_y, "CPU Model: ", color, scale);
        print_string(x + 88 * scale, current_y, info->cpu_brand, color, scale);
    }
}
