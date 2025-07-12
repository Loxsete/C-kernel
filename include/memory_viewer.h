#ifndef MEMORY_VIEWER_H
#define MEMORY_VIEWER_H

#include <stdint.h>

void memory_viewer_init(void);
void memory_viewer_set_address(uint32_t addr);
uint32_t memory_viewer_get_address(void);
void memory_viewer_start(void);
void memory_viewer_stop(void);
int memory_viewer_is_active(void);
void memory_viewer_page_up(void);
void memory_viewer_page_down(void);
void memory_viewer_line_up(void);
void memory_viewer_line_down(void);
void memory_viewer_refresh(void);
void memory_viewer_handle_key(unsigned char keycode);
uint32_t parse_hex_address(const char *hex_str);

#endif
