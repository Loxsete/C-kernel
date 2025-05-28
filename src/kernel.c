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
	clear_screen();
    Color white = 0xFFFFFFFF;
    Color pink = 0xFF00FFFF;
	
    print_string(10, 20, "Hello, from kernel!", pink, 1);
	// For exemple draw cirle
    draw_circle(100, 300, 50, 0xFF0000FF);
    draw_rectangle(100, 100, 100, 100, 0xFF0000FF);
    system_info_t sys_info;
    get_system_info(&sys_info, &fb);
    display_system_info(&sys_info, 10, 60, white, 1);

    

    for (;;) {}
}
