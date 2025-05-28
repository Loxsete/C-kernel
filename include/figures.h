#ifndef FIGURES_H
#define FIGURES_H

#include <stdint.h>

#ifndef COLOR_DEFINED
#define COLOR_DEFINED
typedef uint32_t Color;
#endif

void draw_square(uint32_t x, uint32_t y, uint32_t size, Color color);
void draw_rectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color);
void draw_circle(uint32_t x_center, uint32_t y_center, uint32_t radius, Color color);
void draw_triangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, Color color);

void draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Color color);
void draw_ellipse(uint32_t x_center, uint32_t y_center, uint32_t radius_x, uint32_t radius_y, Color color);
void draw_rounded_rectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t radius, Color color);

void draw_border(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t thickness, Color color);
void draw_dashed_border(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t dash_length, Color color);

#define COLOR_BLACK     0x000000
#define COLOR_WHITE     0xFFFFFF
#define COLOR_RED       0xFF0000
#define COLOR_GREEN     0x00FF00
#define COLOR_BLUE      0x0000FF
#define COLOR_YELLOW    0xFFFF00
#define COLOR_CYAN      0x00FFFF
#define COLOR_MAGENTA   0xFF00FF
#define COLOR_GRAY      0x808080
#define COLOR_DARK_GRAY 0x404040
#define COLOR_LIGHT_GRAY 0xC0C0C0

#define COLOR_UI_BG     0x000020
#define COLOR_UI_BORDER 0xFFFFFF
#define COLOR_UI_TEXT   0x00FF00

#endif
