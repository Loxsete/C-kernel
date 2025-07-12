#include "keyboard.h"
#include "keyboard_map.h"
#include "graphics.h"
#include "font.h"
#include "utils.h"
#include "memory_viewer.h"
#include "fat32.h"
#include "debug.h"
#include "com.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E

extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);
extern void keyboard_handler(void);

static char input_buffer[256];
static unsigned int buffer_index = 0;
static int shift_pressed = 0;
static char com_buffer[256];
static unsigned int com_buffer_index = 0;
static int y_pos = 100;
static Color white = 0xFFFFFFFF;
static Color green = 0xFF00FF00;
static Color red = 0xFFFF0000;
static Color yellow = 0xFFFFFF00;

static struct IDT_entry IDT[IDT_SIZE];

void process_command(char *cmd);

void idt_init(void) {
    unsigned long keyboard_address;
    unsigned long idt_address;
    unsigned long idt_ptr[2];
    keyboard_address = (unsigned long)keyboard_handler;
    IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
    IDT[0x21].selector = 0x08;
    IDT[0x21].zero = 0;
    IDT[0x21].type_attr = 0x8e;
    IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

    debug_print("IDT[0x21] setup:", green);
    debug_print_hex("offset_low: 0x", IDT[0x21].offset_lowerbits & 0xFF);
    debug_print_hex("offset_low_hi: 0x", (IDT[0x21].offset_lowerbits >> 8) & 0xFF);

    debug_print_hex("offset_high: 0x", IDT[0x21].offset_higherbits & 0xFF);
    debug_print_hex("offset_high_hi: 0x", (IDT[0x21].offset_higherbits >> 8) & 0xFF);

    debug_print_hex("selector: 0x", IDT[0x21].selector);
    debug_print_hex("type_attr: 0x", IDT[0x21].type_attr);

    write_port(0x20, 0x11);
    write_port(0xA0, 0x11);
    write_port(0x21, 0x20);
    write_port(0xA1, 0x28);
    write_port(0x21, 0x00);
    write_port(0xA1, 0x00);
    write_port(0x21, 0x01);
    write_port(0xA1, 0x01);
    write_port(0x21, 0xff);
    write_port(0xA1, 0xff);

    idt_address = (unsigned long)IDT;
    idt_ptr[0] = (sizeof(struct IDT_entry) * 256) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
    debug_print("IDT loaded.", green);
}

void kb_init(void) {
    write_port(0x21, 0xFD);
    com_init();
    memory_viewer_init();
}

void keyboard_handler_main(void) {
    unsigned char status;
    unsigned char keycode;

    write_port(0x20, 0x20);

    status = read_port(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);

        if (memory_viewer_is_active()) {
            memory_viewer_handle_key(keycode);
            return;
        }

        if (keycode == 0x2A || keycode == 0x36) {
            shift_pressed = 1;
            return;
        }
        if (keycode == 0xAA || keycode == 0xB6) {
            shift_pressed = 0;
            return;
        }

        if (keycode >= 0x80) {
            return;
        }

        unsigned char *current_map = shift_pressed ? shifted_keyboard_map : keyboard_map;
        char ascii = current_map[keycode];

        if (keycode == ENTER_KEY_CODE) {
            input_buffer[buffer_index] = '\0';
            process_command(input_buffer);
            buffer_index = 0;
            draw_rectangle(10, y_pos, 200, 20, 0x00000000);
            print_string(10, y_pos, input_buffer, white, 1);
        } else if (keycode == BACKSPACE_KEY_CODE && buffer_index > 0) {
            buffer_index--;
            input_buffer[buffer_index] = '\0';
            draw_rectangle(10, y_pos, 200, 20, 0x00000000);
            print_string(10, y_pos, input_buffer, white, 1);
        } else if (ascii != 0 && ascii < 0x80) {
            if (buffer_index < sizeof(input_buffer) - 1) {
                input_buffer[buffer_index++] = ascii;
                input_buffer[buffer_index] = '\0';
                draw_rectangle(10, y_pos, 200, 20, 0x00000000);
                print_string(10, y_pos, input_buffer, white, 1);
            }
        }
    }

    if (com_data_available()) {
        debug_print("COM data detected!", green);
        char c = com_read_char();
        if (c == 0) {
            debug_print("No data received!", red);
            return;
        }
        if (y_pos >= 700) y_pos = 100;
        if (c == '\n' || c == '\r' || com_buffer_index >= sizeof(com_buffer) - 1) {
            com_buffer[com_buffer_index] = '\0';
            if (com_buffer_index > 0) {
                print_string(10, y_pos + 40, "Received: ", white, 1);
                print_string(90, y_pos + 40, com_buffer, white, 1);
                debug_print("String processed", green);
                y_pos += 20;
            }
            com_buffer_index = 0;
        } else if (c >= 32 && c <= 126) {
            com_buffer[com_buffer_index++] = c;
            debug_print("Char added to buffer", green);
        }
    }
}

void process_command(char *cmd) {
    if (y_pos >= 700) y_pos = 100;
    draw_rectangle(10, y_pos, 400, 20, 0x00000000);

    if (str_cmp(cmd, "clear") == 0) {
        draw_rectangle(0, 0, 1024, 768, 0x00000000);
        y_pos = 100;
        debug_y = 600;
    } else if (str_cmp(cmd, "help") == 0) {
        print_string(10, y_pos, "Commands:", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "1. help - show help", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "2. com <text> - send text", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "3. comtest - test COM", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "4. comstatus - COM status", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "5. comcrush - COM crusher", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "6. mem - memory viewer", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "7. mem <addr> - view at address", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "8. vidcrush - video memory crush", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "9. reboot - reboot system", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "10. beep - play beep sound", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "11. ls - list directory contents", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "12. cat <filename> - display file contents", white, 1);
        y_pos += 20;
        print_string(10, y_pos, "13. cd <dirname> - change directory", white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "info") == 0) {
        print_string(10, y_pos, "Hello, World!", white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "comtest") == 0) {
        debug_print("Testing COM port", green);
        com_send_string("TEST MESSAGE FROM OS");
        print_string(10, y_pos, "Test message sent", white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "comstatus") == 0) {
        unsigned char status = read_port(COM1_PORT + 5);
        debug_print_hex("Current COM1 status: 0x", status);
        print_string(10, y_pos, "Status output to debug", white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "comcrush") == 0) {
        debug_print("Sending garbage...", red);
        for (int i = 0; i < 4048; i++) {
            com_send_char(0xFF);
        }
        debug_print("Garbage sent.", red);
        print_string(10, y_pos, "Sent garbage to COM", white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "mem") == 0) {
        print_string(10, y_pos, "Memory viewer started", white, 1);
        y_pos += 20;
        memory_viewer_start();
    } else if (strncmp(cmd, "mem ", 4) == 0 && cmd[4] != '\0') {
        uint32_t addr = parse_hex_address(cmd + 4);
        memory_viewer_set_address(addr);
        print_string(10, y_pos, "Memory viewer at address", white, 1);
        y_pos += 20;
        memory_viewer_start();
    } else if (strncmp(cmd, "com ", 4) == 0 && cmd[4] != '\0') {
        debug_print("COM command received", green);
        com_send_string(cmd + 4);
        print_string(10, y_pos, "Sent: ", white, 1);
        print_string(110, y_pos, cmd + 4, white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "vidcrush") == 0) {
        debug_print("Video crusher!", red);
        print_string(10, y_pos, "Crushing video memory...", red, 1);
        y_pos += 20;
        volatile char *video_mem = (char*)0xA0000;
        for (int i = 0; i < 0x20000; i++) {
            video_mem[i] = (i % 256);
        }
        debug_print("Video memory crushed!", red);
        for (int i = 0; i < 10000; i++) {
            volatile uint32_t *ptr = (uint32_t*)(0x100000 + (i * 4096));
            *ptr = 0xDEADBEEF;
        }
        debug_print("Memory crushed!", red);
    } else if (str_cmp(cmd, "reboot") == 0) {
        debug_print("Rebooting...", yellow);
        write_port(0x64, 0xFE);
        print_string(10, y_pos, "System reboot triggered", white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "beep") == 0) {
        debug_print("Beeping...", green);
        write_port(0x43, 0xB6);
        write_port(0x42, 1193180 / 1000 & 0xFF);
        write_port(0x42, 1193180 / 1000 >> 8);
        write_port(0x61, read_port(0x61) | 0x03);
        for (volatile int i = 0; i < 100000; i++);
        write_port(0x61, read_port(0x61) & 0xFC);
        print_string(10, y_pos, "Beep!", white, 1);
        y_pos += 20;
    } else if (str_cmp(cmd, "ls") == 0) {
        debug_print("Attempting to list directory", green);
        fat32_dir_entry_t entries[MAX_FILES];
        uint32_t count;
        fat32_list_dir(fat32_get_current_path(), entries, &count);
        debug_print_hex("Directory entries found: 0x", (uint8_t)count);
        
        if (count == 0) {
            print_string(10, y_pos, "Directory is empty or FAT32 not initialized", white, 1);
            y_pos += 20;
        } else {
            char current_dir[64] = "Directory: ";
            str_copy(current_dir + str_len(current_dir), fat32_get_current_path(), sizeof(current_dir) - str_len(current_dir));
            print_string(10, y_pos, current_dir, white, 1);
            y_pos += 20;
            
            for (uint32_t i = 0; i < count; i++) {
                char formatted_name[13];
                char entry_info[80];
                
                format_filename_display(entries[i].name, formatted_name);
                str_copy(entry_info, formatted_name, sizeof(entry_info));
                
                if (entries[i].attributes & 0x10) {
                    str_copy(entry_info + str_len(entry_info), "  <DIR>", sizeof(entry_info) - str_len(entry_info));
                } else {
                    str_copy(entry_info + str_len(entry_info), "  ", sizeof(entry_info) - str_len(entry_info));
                    char size_str[16];
                    uint32_to_str(entries[i].size, size_str, sizeof(size_str));
                    str_copy(entry_info + str_len(entry_info), size_str, sizeof(entry_info) - str_len(entry_info));
                    str_copy(entry_info + str_len(entry_info), " bytes", sizeof(entry_info) - str_len(entry_info));
                }
                
                print_string(10, y_pos, entry_info, white, 1);
                y_pos += 20;
            }
        }
        debug_print("Directory listed", green);
    } else if (strncmp(cmd, "cat ", 4) == 0 && cmd[4] != '\0') {
        debug_print("Attempting to read file", green);
        char file_buffer[2048];
        fat32_read_file(cmd + 4, file_buffer, sizeof(file_buffer) - 1);
        
        if (file_buffer[0] == '\0') {
            char error_msg[256] = "Cannot read file: ";
            str_copy(error_msg + str_len(error_msg), cmd + 4, sizeof(error_msg) - str_len(error_msg));
            print_string(10, y_pos, error_msg, red, 1);
            y_pos += 20;
        } else {
            print_string(10, y_pos, "File contents:", white, 1);
            y_pos += 20;
            
            char* line_start = file_buffer;
            char* line_end;
            
            while (*line_start && y_pos < 650) {
                line_end = line_start;
                while (*line_end && *line_end != '\n' && *line_end != '\r') {
                    line_end++;
                }
                
                char line[128];
                int len = line_end - line_start;
                if (len > 127) len = 127;
                
                for (int i = 0; i < len; i++) {
                    line[i] = line_start[i];
                }
                line[len] = '\0';
                
                print_string(10, y_pos, line, white, 1);
                y_pos += 15;
                
                if (*line_end == '\n' || *line_end == '\r') {
                    line_start = line_end + 1;
                    if (*line_start == '\n' || *line_start == '\r') {
                        line_start++;
                    }
                } else {
                    break;
                }
            }
            
            debug_print("File contents displayed", green);
        }
    
    } else if (strncmp(cmd, "cd ", 3) == 0 && cmd[3] != '\0') {
        debug_print("Attempting to change directory", green);
        fat32_change_dir(cmd + 3);
        
        char path_msg[256] = "Current directory: ";
        str_copy(path_msg + str_len(path_msg), fat32_get_current_path(), sizeof(path_msg) - str_len(path_msg));
        print_string(10, y_pos, path_msg, white, 1);
        y_pos += 20;
        debug_print("Directory changed", green);
    
    } else if (cmd[0] != '\0') {
        char msg[256] = "Unknown command: ";
        unsigned int msg_len = str_len(msg);
        str_copy(msg + msg_len, cmd, sizeof(msg) - msg_len);
        print_string(10, y_pos, msg, white, 1);
        y_pos += 20;
    }
}
