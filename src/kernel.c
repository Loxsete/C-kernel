#include <stdint.h>
#include <font.h>
#include <multiboot.h>
#include <graphics.h>
#include "info.h"
#include "keyboard.h"
#include "fat32.h"

void kmain(uint32_t mbinfo_ptr) {
    multiboot_tag_framebuffer_t fb;
    multiboot_parse(mbinfo_ptr, &fb);

    if (fb.framebuffer_bpp != 32) {
        for (;;);
    }

    fb_init(&fb);
    clear_screen();
    Color white = 0xFFFFFFFF;
    Color pink = 0xFF00FFFF;

    system_info_t sys_info;
    get_system_info(&sys_info, &fb);

    print_string(10, 20, "Hello, from kernel!", pink, 1);

    idt_init();
    kb_init();
    fat32_init(0);
    print_string(10, 80, "user:", white, 1);

    for (;;) {}
}
