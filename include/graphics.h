#pragma once

#include <multiboot.h>

void fb_init(multiboot_tag_framebuffer_t* fb);
void pixel(int x, int y, uint32_t color);