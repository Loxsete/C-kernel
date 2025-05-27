#pragma once

#include <multiboot.h>

void fb_init(multiboot_tag_framebuffer_t* fb);
void pixel(int x, int y, uint32_t color);
extern uint32_t* framebuffer;
extern uint32_t pitch;
extern uint16_t width;
extern uint16_t height;
void clear_screen(void);

