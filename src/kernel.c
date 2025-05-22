#include <stdint.h>

#include <multiboot.h>
#include <graphics.h>

void kmain(uint32_t mbinfo_ptr)
{
    multiboot_tag_framebuffer_t fb;
    multiboot_parse(mbinfo_ptr, &fb);

    if (fb.framebuffer_bpp != 32) {
        for (;;); // unsupported
    }

    fb_init(&fb);

    // Draw 100x100 magenta square at (100, 100)
    for (uint32_t y = 100; y < 200; ++y) {
        for (uint32_t x = 100; x < 200; ++x) {
            pixel(x, y, 0x00FF00FF);
        }
    }

    for (;;) {}
}
