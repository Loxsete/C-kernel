#include "fat32.h"
#include "utils.h"
#include "graphics.h"

#define ATA_PRIMARY_IO 0x1F0
#define ATA_PRIMARY_CTRL 0x3F6
#define ATA_DRIVE 0x1F6
#define ATA_SECTOR_COUNT 0x1F2
#define ATA_LBA_LOW 0x1F3
#define ATA_LBA_MID 0x1F4
#define ATA_LBA_HIGH 0x1F5
#define ATA_COMMAND 0x1F7
#define ATA_STATUS 0x1F7

typedef uint32_t Color;
static const Color red = 0xFFFF0000;
static const Color green = 0xFF00FF00;

static fat32_boot_sector_t boot_sector;
static uint32_t fat_start;
static uint32_t data_start;
static char current_path[MAX_PATH] = "/";

extern void outb(uint16_t port, uint8_t value);
extern uint8_t inb(uint16_t port);
extern uint16_t inw(uint16_t port);

static int ata_wait(void) {
    int timeout = 100000;
    unsigned char status;
    debug_print("Waiting for ATA...", green);
    
    while (timeout > 0) {
        status = inb(ATA_STATUS);
        debug_print_hex("ATA status: 0x", status);
        if (!(status & 0x80)) break;
        timeout--;
    }
    if (timeout <= 0) {
        debug_print("ATA BSY timeout", red);
        return 0;
    }
    
    if (status & 0x01) {
        debug_print("ATA error bit set", red);
        return 0;
    }
    
    timeout = 100000;
    while (timeout > 0) {
        status = inb(ATA_STATUS);
        if (status & 0x08) break;
        if (status & 0x01) {
            debug_print("ATA error during DRQ wait", red);
            return 0;
        }
        timeout--;
    }
    if (timeout <= 0) {
        debug_print("ATA DRQ timeout", red);
        return 0;
    }
    
    debug_print("ATA ready", green);
    return 1;
}

static void ata_read_sector(uint32_t lba, uint8_t* buffer) {
    debug_print("Starting sector read...", green);
    debug_print_hex("LBA: 0x", (uint8_t)(lba & 0xFF));
    
    outb(ATA_DRIVE, 0xF0 | ((lba >> 24) & 0x0F));
    
    for (int i = 0; i < 10000; i++) {
        uint8_t status = inb(ATA_STATUS);
        if (!(status & 0x80)) break;
    }
    
    outb(ATA_SECTOR_COUNT, 1);
    outb(ATA_LBA_LOW, lba & 0xFF);
    outb(ATA_LBA_MID, (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH, (lba >> 16) & 0xFF);
    outb(ATA_COMMAND, 0x20);

    if (!ata_wait()) {
        debug_print("ATA read failed", red);
        return;
    }

    for (int i = 0; i < SECTOR_SIZE / 2; i++) {
        uint16_t data = inw(ATA_PRIMARY_IO);
        buffer[i * 2] = data & 0xFF;
        buffer[i * 2 + 1] = (data >> 8) & 0xFF;
    }
    debug_print("Sector read complete", green);
}

void fat32_init(uint32_t lba_start) {
    uint8_t sector[SECTOR_SIZE];
    debug_print("FAT32 initialization started", green);
    
    ata_read_sector(lba_start, sector);
    
    if (sector[510] != 0x55 || sector[511] != 0xAA) {
        debug_print("Invalid boot sector signature", red);
        return;
    }

    boot_sector.bytes_per_sector = *(uint16_t*)(sector + 11);
    boot_sector.sectors_per_cluster = sector[13];
    boot_sector.reserved_sectors = *(uint16_t*)(sector + 14);
    boot_sector.fat_count = sector[16];
    boot_sector.sectors_per_fat = *(uint32_t*)(sector + 36);
    boot_sector.root_cluster = *(uint32_t*)(sector + 44);

    fat_start = lba_start + boot_sector.reserved_sectors;
    data_start = fat_start + boot_sector.fat_count * boot_sector.sectors_per_fat;

    debug_print_hex("Bytes per sector: 0x", (uint8_t)(boot_sector.bytes_per_sector & 0xFF));
    debug_print_hex("Root cluster: 0x", (uint8_t)(boot_sector.root_cluster & 0xFF));
}

static uint32_t fat32_get_next_cluster(uint32_t cluster) {
    uint8_t sector[SECTOR_SIZE];
    uint32_t fat_sector = fat_start + (cluster * 4 / SECTOR_SIZE);
    ata_read_sector(fat_sector, sector);
    uint32_t offset = (cluster * 4) % SECTOR_SIZE;
    return *(uint32_t*)(sector + offset) & 0x0FFFFFFF;
}

uint32_t fat32_get_cluster_chain(uint32_t start_cluster, uint32_t* chain, uint32_t max_length) {
    uint32_t count = 0;
    uint32_t current = start_cluster;

    while (current < 0x0FFFFFF8 && count < max_length) {
        chain[count++] = current;
        current = fat32_get_next_cluster(current);
    }
    return count;
}

static void fat32_read_dir(uint32_t cluster, fat32_dir_entry_t* entries, uint32_t* count) {
    uint8_t sector[SECTOR_SIZE];
    uint32_t chain[128];
    uint32_t chain_length = fat32_get_cluster_chain(cluster, chain, 128);
    *count = 0;

    for (uint32_t i = 0; i < chain_length && *count < MAX_FILES; i++) {
        uint32_t sector_lba = data_start + (chain[i] - 2) * boot_sector.sectors_per_cluster;
        for (uint32_t s = 0; s < boot_sector.sectors_per_cluster; s++) {
            ata_read_sector(sector_lba + s, sector);
            for (int j = 0; j < SECTOR_SIZE / 32 && *count < MAX_FILES; j++) {
                uint8_t* entry = sector + j * 32;
                if (entry[0] == 0 || entry[0] == 0xE5) continue;
                if (entry[11] == 0x0F) continue;

                for (int k = 0; k < 11; k++) {
                    entries[*count].name[k] = entry[k];
                }
                entries[*count].name[11] = '\0';
                entries[*count].cluster = (*(uint16_t*)(entry + 20) << 16) | *(uint16_t*)(entry + 26);
                entries[*count].size = *(uint32_t*)(entry + 28);
                entries[*count].attributes = entry[11];
                (*count)++;
            }
        }
    }
}

void fat32_read_file(const char* path, char* buffer, uint32_t max_size) {
    fat32_dir_entry_t entries[MAX_FILES];
    uint32_t count;
    fat32_list_dir(current_path, entries, &count);

    for (uint32_t i = 0; i < count; i++) {
        if (strncmp(entries[i].name, path, 11) == 0 && !(entries[i].attributes & 0x10)) {
            uint32_t chain[128];
            uint32_t chain_length = fat32_get_cluster_chain(entries[i].cluster, chain, 128);
            uint32_t bytes_read = 0;

            for (uint32_t c = 0; c < chain_length && bytes_read < max_size; c++) {
                uint32_t sector_lba = data_start + (chain[c] - 2) * boot_sector.sectors_per_cluster;
                for (uint32_t s = 0; s < boot_sector.sectors_per_cluster && bytes_read < max_size; s++) {
                    ata_read_sector(sector_lba + s, (uint8_t*)(buffer + bytes_read));
                    bytes_read += SECTOR_SIZE;
                }
            }
            if (bytes_read > max_size) bytes_read = max_size;
            if (bytes_read > 0) buffer[bytes_read - 1] = '\0';
            return;
        }
    }
    buffer[0] = '\0';
}

void fat32_list_dir(const char* path, fat32_dir_entry_t* entries, uint32_t* count) {
    uint32_t cluster = boot_sector.root_cluster;
    fat32_read_dir(cluster, entries, count);
}

void fat32_change_dir(const char* path) {
    fat32_dir_entry_t entries[MAX_FILES];
    uint32_t count;
    fat32_list_dir(current_path, entries, &count);

    for (uint32_t i = 0; i < count; i++) {
        if (strncmp(entries[i].name, path, 11) == 0 && (entries[i].attributes & 0x10)) {
            uint32_t new_cluster = entries[i].cluster;
            str_copy(current_path, path, MAX_PATH);
            boot_sector.root_cluster = new_cluster;
            return;
        }
    }
}

const char* fat32_get_current_path(void) {
    return current_path;
}
