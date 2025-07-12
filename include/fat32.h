#ifndef FAT32_H
#define FAT32_H

#include <stdint.h>

#define SECTOR_SIZE 512
#define MAX_FILES 256
#define MAX_PATH 256

// FAT32 boot sector structure
typedef struct {
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t fat_count;
    uint32_t sectors_per_fat;
    uint32_t root_cluster;
} fat32_boot_sector_t;

// FAT32 directory entry structure
typedef struct {
    char name[12]; // 8.3 format + null terminator
    uint32_t cluster;
    uint32_t size;
    uint8_t attributes;
} fat32_dir_entry_t;

// Function prototypes
void fat32_init(uint32_t lba_start);
void fat32_read_file(const char* path, char* buffer, uint32_t max_size);
void fat32_list_dir(const char* path, fat32_dir_entry_t* entries, uint32_t* count);
void fat32_change_dir(const char* path);
const char* fat32_get_current_path(void);

#endif // FAT32_H
