#include <graphics.h>

uint32_t* framebuffer;
uint32_t pitch;
uint16_t width;
uint16_t height;

void fb_init(multiboot_tag_framebuffer_t* fb)
{
    framebuffer = (uint32_t*)fb->framebuffer_addr;
    pitch = fb->framebuffer_pitch / 4;
    width = fb->framebuffer_width;
    height = fb->framebuffer_height;
}

void pixel(int x, int y, uint32_t color)
{
    if (x > width || y > height) return;
    framebuffer[y * pitch + x] = color;
}

void clear_screen(void)
{
	uint32_t dark_blue = 0x008080;
	for (uint16_t y = 0; y < height; y++) {
		for (uint16_t x = 0; x < width; x++) {
			framebuffer[y * pitch + x] = dark_blue;
		}
	}
}
