#include "commands.h"
#include "kernel.h"

void info(void) {
    const char *ascii_art[] = {
        "  ####     #####  ",
        " ##  ##   ##      ",
        " ##  ##    #####  ",
        " ##  ##        ## ",
        "  ####    ######  "
    };

    const char *sys_info[] = {
        "OS: Loxsete-OS",
        "Author: Loxsete",
        "Arch: x86",
        "Kernel: 0.1.0",
        "Shell: Basic CLI"
    };

    for (int i = 0; i < 5; i++) {
        kprint(ascii_art[i]);
        kprint("     ");
        kprint(sys_info[i]);
        kprint_newline();
    }
}

void help(void) {
    kprint("Commands:\n");
    kprint("1. help - this command\n");
    kprint("2. clear - clear screen\n");
    kprint("3. info - info about Os\n");
    kprint("4. calc - calculate expression, e.g., calc 2+2\n");
    kprint("Note: Hold Shift for uppercase letters or alternate symbols (e.g., Shift+= for +). Release Shift to return to lowercase/standard symbols.\n");
}
