#include <stdint.h>
#include <font.h>
#include <multiboot.h>
#include <graphics.h>
#include "info.h"


void kmain(uint32_t mbinfo_ptr) {
    multiboot_tag_framebuffer_t fb;
    multiboot_parse(mbinfo_ptr, &fb);
    
    if (fb.framebuffer_bpp != 32) {
        for (;;);
    }
    
    fb_init(&fb);

    Color white = 0xFFFFFFFF;
    Color pink = 0xFF00FFFF;

    print_string(10, 20, "Hello, from kernel!", pink, 1);

    system_info_t sys_info;
    get_system_info(&sys_info, &fb);
    display_system_info(&sys_info, 10, 60, white, 1);

    

    for (;;) {}
}
