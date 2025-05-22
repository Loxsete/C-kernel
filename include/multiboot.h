#pragma once

#include <stdint.h>

typedef struct {
    uint32_t type;
    uint32_t size;
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    uint8_t framebuffer_type;
    uint16_t reserved;
} __attribute__((packed)) multiboot_tag_framebuffer_t;

void multiboot_parse(uint32_t mb_addr, multiboot_tag_framebuffer_t* buffer);