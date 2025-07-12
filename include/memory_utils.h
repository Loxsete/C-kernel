#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <stdint.h>

void memory_dump(uint32_t start_addr, uint32_t size, int x, int y);
void memory_search(uint32_t start_addr, uint32_t size, uint8_t *pattern, uint32_t pattern_size);
void memory_fill(uint32_t start_addr, uint32_t size, uint8_t value);
void memory_copy(uint32_t dest_addr, uint32_t src_addr, uint32_t size);
int memory_compare(uint32_t addr1, uint32_t addr2, uint32_t size);
void memory_stats(uint32_t start_addr, uint32_t size);

#endif
