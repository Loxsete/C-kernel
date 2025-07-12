#include "memory_utils.h"
#include "graphics.h"
#include "font.h"
#include "utils.h"

static Color white = 0xFFFFFFFF;
static Color red = 0xFFFF0000;
static Color green = 0xFF00FF00;
static Color blue = 0xFF0000FF;
static Color yellow = 0xFFFFFF00;

void memory_dump(uint32_t start_addr, uint32_t size, int x, int y) {
    char title[64];
    str_copy(title, "Memory Dump at 0x", sizeof(title));
    int title_len = str_len(title);
    
    char hex_chars[] = "0123456789ABCDEF";
    for (int i = 0; i < 8; i++) {
        title[title_len + i] = hex_chars[(start_addr >> (28 - i * 4)) & 0xF];
    }
    title[title_len + 8] = '\0';
    
    print_string(x, y, title, white, 1);
    y += 20;
    
    uint8_t *ptr = (uint8_t *)start_addr;
    for (uint32_t i = 0; i < size; i++) {
        if (i % 16 == 0) {
            if (i > 0) {
                y += 15;
            }
            char addr_str[12];
            addr_str[0] = '0';
            addr_str[1] = 'x';
            uint32_t addr = start_addr + i;
            for (int j = 0; j < 8; j++) {
                addr_str[2 + j] = hex_chars[(addr >> (28 - j * 4)) & 0xF];
            }
            addr_str[10] = ':';
            addr_str[11] = '\0';
            print_string(x, y, addr_str, yellow, 1);
        }
        
        char byte_str[4];
        byte_str[0] = ' ';
        byte_str[1] = hex_chars[(ptr[i] >> 4) & 0xF];
        byte_str[2] = hex_chars[ptr[i] & 0xF];
        byte_str[3] = '\0';
        
        int byte_x = x + 90 + (i % 16) * 24;
        Color color = white;
        if (ptr[i] == 0x00) color = 0xFF808080;
        else if (ptr[i] == 0xFF) color = red;
        else if (ptr[i] >= 0x20 && ptr[i] <= 0x7E) color = green;
        
        print_string(byte_x, y, byte_str, color, 1);
    }
}

void memory_search(uint32_t start_addr, uint32_t size, uint8_t *pattern, uint32_t pattern_size) {
    uint8_t *memory = (uint8_t *)start_addr;
    uint32_t matches = 0;
    
    for (uint32_t i = 0; i <= size - pattern_size; i++) {
        int match = 1;
        for (uint32_t j = 0; j < pattern_size; j++) {
            if (memory[i + j] != pattern[j]) {
                match = 0;
                break;
            }
        }
        
        if (match) {
            matches++;
            if (matches <= 10) {
                char match_str[64];
                str_copy(match_str, "Match found at 0x", sizeof(match_str));
                int str_len_val = str_len(match_str);
                
                char hex_chars[] = "0123456789ABCDEF";
                uint32_t addr = start_addr + i;
                for (int k = 0; k < 8; k++) {
                    match_str[str_len_val + k] = hex_chars[(addr >> (28 - k * 4)) & 0xF];
                }
                match_str[str_len_val + 8] = '\0';
                
                print_string(10, 200 + matches * 15, match_str, green, 1);
            }
        }
    }
    
    if (matches == 0) {
        print_string(10, 200, "No matches found", red, 1);
    } else if (matches > 10) {
        char more_str[64];
        str_copy(more_str, "... and ", sizeof(more_str));
        int str_len_val = str_len(more_str);
        
        uint32_t remaining = matches - 10;
        char num_str[16];
        int num_len = 0;
        if (remaining == 0) {
            num_str[num_len++] = '0';
        } else {
            while (remaining > 0) {
                num_str[num_len++] = '0' + (remaining % 10);
                remaining /= 10;
            }
            for (int i = 0; i < num_len / 2; i++) {
                char temp = num_str[i];
                num_str[i] = num_str[num_len - 1 - i];
                num_str[num_len - 1 - i] = temp;
            }
        }
        
        for (int i = 0; i < num_len; i++) {
            more_str[str_len_val + i] = num_str[i];
        }
        str_copy(more_str + str_len_val + num_len, " more matches", sizeof(more_str) - str_len_val - num_len);
        
        print_string(10, 200 + 11 * 15, more_str, yellow, 1);
    }
}

void memory_fill(uint32_t start_addr, uint32_t size, uint8_t value) {
    uint8_t *ptr = (uint8_t *)start_addr;
    for (uint32_t i = 0; i < size; i++) {
        ptr[i] = value;
    }
}

void memory_copy(uint32_t dest_addr, uint32_t src_addr, uint32_t size) {
    uint8_t *dest = (uint8_t *)dest_addr;
    uint8_t *src = (uint8_t *)src_addr;
    
    for (uint32_t i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int memory_compare(uint32_t addr1, uint32_t addr2, uint32_t size) {
    uint8_t *ptr1 = (uint8_t *)addr1;
    uint8_t *ptr2 = (uint8_t *)addr2;
    
    for (uint32_t i = 0; i < size; i++) {
        if (ptr1[i] != ptr2[i]) {
            return 0;
        }
    }
    return 1;
}

void memory_stats(uint32_t start_addr, uint32_t size) {
    uint8_t *memory = (uint8_t *)start_addr;
    uint32_t zero_count = 0;
    uint32_t ff_count = 0;
    uint32_t printable_count = 0;
    
    for (uint32_t i = 0; i < size; i++) {
        if (memory[i] == 0x00) zero_count++;
        else if (memory[i] == 0xFF) ff_count++;
        else if (memory[i] >= 0x20 && memory[i] <= 0x7E) printable_count++;
    }
    
    char stats_str[128];
    
    str_copy(stats_str, "Zero bytes: ", sizeof(stats_str));
    int len = str_len(stats_str);
    uint32_t temp = zero_count;
    int digits = 0;
    if (temp == 0) {
        stats_str[len++] = '0';
    } else {
        while (temp > 0) {
            stats_str[len + digits] = '0' + (temp % 10);
            temp /= 10;
            digits++;
        }
        for (int i = 0; i < digits / 2; i++) {
            char swap = stats_str[len + i];
            stats_str[len + i] = stats_str[len + digits - 1 - i];
            stats_str[len + digits - 1 - i] = swap;
        }
        len += digits;
    }
    stats_str[len] = '\0';
    
    print_string(10, 150, stats_str, white, 1);
    
    str_copy(stats_str, "FF bytes: ", sizeof(stats_str));
    len = str_len(stats_str);
    temp = ff_count;
    digits = 0;
    if (temp == 0) {
        stats_str[len++] = '0';
    } else {
        while (temp > 0) {
            stats_str[len + digits] = '0' + (temp % 10);
            temp /= 10;
            digits++;
        }
        for (int i = 0; i < digits / 2; i++) {
            char swap = stats_str[len + i];
            stats_str[len + i] = stats_str[len + digits - 1 - i];
            stats_str[len + digits - 1 - i] = swap;
        }
        len += digits;
    }
    stats_str[len] = '\0';
    
    print_string(10, 165, stats_str, white, 1);
    
    str_copy(stats_str, "Printable bytes: ", sizeof(stats_str));
    len = str_len(stats_str);
    temp = printable_count;
    digits = 0;
    if (temp == 0) {
        stats_str[len++] = '0';
    } else {
        while (temp > 0) {
            stats_str[len + digits] = '0' + (temp % 10);
            temp /= 10;
            digits++;
        }
        for (int i = 0; i < digits / 2; i++) {
            char swap = stats_str[len + i];
            stats_str[len + i] = stats_str[len + digits - 1 - i];
            stats_str[len + digits - 1 - i] = swap;
        }
        len += digits;
    }
    stats_str[len] = '\0';
    
    print_string(10, 180, stats_str, white, 1);
}
