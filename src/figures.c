#include <stdint.h>
#include "graphics.h"
#include "figures.h"

void draw_square(uint32_t x, uint32_t y, uint32_t size, Color color) {
    for (uint32_t py = y; py < y + size; ++py) {
        for (uint32_t px = x; px < x + size; ++px) {
            pixel(px, py, color);
        }
    }
}

void draw_rectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, Color color) {
    for (uint32_t py = y; py < y + height; ++py) {
        for (uint32_t px = x; px < x + width; ++px) {
            pixel(px, py, color);
        }
    }
}

void draw_circle(uint32_t x_center, uint32_t y_center, uint32_t radius, Color color) {
    for (int32_t y = -radius; y <= (int32_t)radius; ++y) {
        for (int32_t x = -radius; x <= (int32_t)radius; ++x) {
            if (x * x + y * y <= radius * radius) {
                pixel(x_center + x, y_center + y, color);
            }
        }
    }
}

static void swap(uint32_t *a, uint32_t *b) {
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
}

void draw_triangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, Color color) {
    if (y1 > y2) { swap(&x1, &x2); swap(&y1, &y2); }
    if (y1 > y3) { swap(&x1, &x3); swap(&y1, &y3); }
    if (y2 > y3) { swap(&x2, &x3); swap(&y2, &y3); }

    if (y1 == y3) return;

    float dx12 = (y2 > y1) ? (float)(x2 - x1) / (y2 - y1) : 0;
    float dx13 = (float)(x3 - x1) / (y3 - y1);
    float dx23 = (y3 > y2) ? (float)(x3 - x2) / (y3 - y2) : 0;

    for (uint32_t y = y1; y <= y2; ++y) {
        int32_t x_start = x1 + (int32_t)((y - y1) * dx13);
        int32_t x_end = (y <= y2 && y2 > y1) ? x1 + (int32_t)((y - y1) * dx12) : x2;
        if (x_start > x_end) swap(&x_start, &x_end);
        for (int32_t x = x_start; x <= x_end; ++x) {
            pixel(x, y, color);
        }
    }

    for (uint32_t y = y2; y <= y3; ++y) {
        int32_t x_start = x1 + (int32_t)((y - y1) * dx13);
        int32_t x_end = x2 + (int32_t)((y - y2) * dx23);
        if (x_start > x_end) swap(&x_start, &x_end);
        for (int32_t x = x_start; x <= x_end; ++x) {
            pixel(x, y, color);
        }
    }
}
