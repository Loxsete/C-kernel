#include "memory_viewer.h"
#include "graphics.h"
#include "font.h"
#include "utils.h"

#define MEMORY_VIEWER_X 10
#define MEMORY_VIEWER_Y 100
#define BYTES_PER_LINE 16
#define LINES_PER_PAGE 20
#define VIEWER_WIDTH 800
#define VIEWER_HEIGHT 400

static uint32_t current_address = 0x00000000;
static int viewer_active = 0;
static Color white = 0xFFFFFFFF;
static Color gray = 0xFF808080;
static Color red = 0xFFFF0000;
static Color green = 0xFF00FF00;
static Color blue = 0xFF0000FF;
static Color yellow = 0xFFFFFF00;

void memory_viewer_init(void) {
    current_address = 0x00000000;
    viewer_active = 0;
}

void memory_viewer_set_address(uint32_t addr) {
    current_address = addr;
}

uint32_t memory_viewer_get_address(void) {
    return current_address;
}

void memory_viewer_start(void) {
    viewer_active = 1;
    memory_viewer_refresh();
}

void memory_viewer_stop(void) {
    viewer_active = 0;
    draw_rectangle(MEMORY_VIEWER_X, MEMORY_VIEWER_Y, VIEWER_WIDTH, VIEWER_HEIGHT, 0x00000000);
}

int memory_viewer_is_active(void) {
    return viewer_active;
}

void memory_viewer_page_up(void) {
    if (current_address >= (BYTES_PER_LINE * LINES_PER_PAGE)) {
        current_address -= (BYTES_PER_LINE * LINES_PER_PAGE);
    } else {
        current_address = 0;
    }
    memory_viewer_refresh();
}

void memory_viewer_page_down(void) {
    current_address += (BYTES_PER_LINE * LINES_PER_PAGE);
    memory_viewer_refresh();
}

void memory_viewer_line_up(void) {
    if (current_address >= BYTES_PER_LINE) {
        current_address -= BYTES_PER_LINE;
    } else {
        current_address = 0;
    }
    memory_viewer_refresh();
}

void memory_viewer_line_down(void) {
    current_address += BYTES_PER_LINE;
    memory_viewer_refresh();
}

static void draw_hex_byte(int x, int y, uint8_t byte) {
    char hex_str[3];
    char hex_chars[] = "0123456789ABCDEF";
    hex_str[0] = hex_chars[(byte >> 4) & 0xF];
    hex_str[1] = hex_chars[byte & 0xF];
    hex_str[2] = '\0';
    
    Color color = white;
    if (byte == 0x00) color = gray;
    else if (byte == 0xFF) color = red;
    else if (byte >= 0x20 && byte <= 0x7E) color = green;
    
    print_string(x, y, hex_str, color, 1);
}

static void draw_ascii_char(int x, int y, uint8_t byte) {
    char ascii_str[2];
    if (byte >= 0x20 && byte <= 0x7E) {
        ascii_str[0] = byte;
        ascii_str[1] = '\0';
        print_string(x, y, ascii_str, green, 1);
    } else {
        print_string(x, y, ".", gray, 1);
    }
}

static void draw_address(int x, int y, uint32_t addr) {
    char addr_str[12];
    char hex_chars[] = "0123456789ABCDEF";
    
    addr_str[0] = '0';
    addr_str[1] = 'x';
    
    for (int i = 0; i < 8; i++) {
        addr_str[2 + i] = hex_chars[(addr >> (28 - i * 4)) & 0xF];
    }
    addr_str[10] = ':';
    addr_str[11] = '\0';
    
    print_string(x, y, addr_str, yellow, 1);
}

void memory_viewer_refresh(void) {
    if (!viewer_active) return;
    
    draw_rectangle(MEMORY_VIEWER_X, MEMORY_VIEWER_Y, VIEWER_WIDTH, VIEWER_HEIGHT, 0x00000000);
    
    char title[64];
    str_copy(title, "Memory Viewer - Address: 0x", sizeof(title));
    char hex_chars[] = "0123456789ABCDEF";
    int title_len = str_len(title);
    
    for (int i = 0; i < 8; i++) {
        title[title_len + i] = hex_chars[(current_address >> (28 - i * 4)) & 0xF];
    }
    title[title_len + 8] = '\0';
    
    print_string(MEMORY_VIEWER_X, MEMORY_VIEWER_Y - 20, title, white, 1);
    
    print_string(MEMORY_VIEWER_X + 650, MEMORY_VIEWER_Y - 20, "Q: Quit", white, 1);
    
    uint32_t addr = current_address;
    int y_offset = 0;
    
    for (int line = 0; line < LINES_PER_PAGE; line++) {
        int y = MEMORY_VIEWER_Y + y_offset;
        
        draw_address(MEMORY_VIEWER_X, y, addr);
        
        int hex_x = MEMORY_VIEWER_X + 100;
        for (int byte = 0; byte < BYTES_PER_LINE; byte++) {
            uint8_t *mem_ptr = (uint8_t *)(addr + byte);
            uint8_t value = *mem_ptr;
            
            draw_hex_byte(hex_x + byte * 24, y, value);
            
            if (byte == 7) {
                print_string(hex_x + byte * 24 + 18, y, "-", white, 1);
            }
        }
        
        print_string(hex_x + BYTES_PER_LINE * 24 + 20, y, "|", white, 1);
        
        int ascii_x = hex_x + BYTES_PER_LINE * 24 + 40;
        for (int byte = 0; byte < BYTES_PER_LINE; byte++) {
            uint8_t *mem_ptr = (uint8_t *)(addr + byte);
            uint8_t value = *mem_ptr;
            
            draw_ascii_char(ascii_x + byte * 8, y, value);
        }
        
        print_string(ascii_x + BYTES_PER_LINE * 8 + 10, y, "|", white, 1);
        
        addr += BYTES_PER_LINE;
        y_offset += 15;
    }
}

void memory_viewer_handle_key(unsigned char keycode) {
    if (!viewer_active) return;
    
    switch (keycode) {
        case 0x49:
            memory_viewer_page_up();
            break;
        case 0x51:
            memory_viewer_page_down();
            break;
        case 0x48:
            memory_viewer_line_up();
            break;
        case 0x50:
            memory_viewer_line_down();
            break;
        case 0x10:
            memory_viewer_stop();
            break;
    }
}

uint32_t parse_hex_address(const char *hex_str) {
    uint32_t result = 0;
    int i = 0;
    
    if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X')) {
        i = 2;
    }
    
    while (hex_str[i] != '\0') {
        char c = hex_str[i];
        uint8_t digit = 0;
        
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            digit = c - 'A' + 10;
        } else if (c >= 'a' && c <= 'f') {
            digit = c - 'a' + 10;
        } else {
            break;
        }
        
        result = (result << 4) | digit;
        i++;
    }
    
    return result;
}
