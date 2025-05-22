#include <multiboot.h>

#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER 8

void multiboot_parse(uint32_t mb_addr, multiboot_tag_framebuffer_t* buffer)
{
    uint32_t total_size = *(uint32_t*)mb_addr;
    uint8_t* ptr = (uint8_t*)(mb_addr + 8);

    while ((uintptr_t)ptr < (mb_addr + total_size)) {
        uint32_t type = *(uint32_t*)ptr;
        uint32_t size = *(uint32_t*)(ptr + 4);

        if (type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER) {
            multiboot_tag_framebuffer_t* fb = (multiboot_tag_framebuffer_t*)ptr;
            *buffer = *fb;
            return;
        }

        ptr += (size + 7) & ~7;
    }
}