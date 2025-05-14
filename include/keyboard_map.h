/* The following array is adapted from 
   http://www.osdever.net/bkerndev/Docs/keyboard.htm
   All credits where due
*/

unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 0–9 */
  '9', '0', '-', '=', '\b',  /* Backspace */
  '\t',          /* Tab */
  'q', 'w', 'e', 'r', /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,          /* 29 - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0,        /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',        /* 49 */
  'm', ',', '.', '/',   0,        /* Right shift */
  '*',          /* Keypad * */
    0,          /* Alt */
  ' ',          /* Space bar */
    0,          /* Caps lock */
    0,          /* 59 - F1 key */
    0, 0, 0, 0, 0, 0, 0, 0, 0, /* F2–F10 */
    0,          /* 69 - Num lock */
    0,          /* Scroll Lock */
  0x80,         /* Home key */
  0x81,         /* Up Arrow */
  0x82,         /* Page Up */
  '-',          /* Keypad - */
  0x83,         /* Left Arrow */
    0,          /* 75 - Reserved */
  0x84,         /* Right Arrow */
  '+',          /* Keypad + */
  0x85,         /* End key */
  0x86,         /* Down Arrow */
  0x87,         /* Page Down */
  0x88,         /* Insert Key */
  0x89,         /* Delete Key */
    0, 0, 0,    /* 86–88 - Undefined */
    0,          /* F11 Key */
    0,          /* F12 Key */
    0,          /* 91 - All other keys are undefined */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 92–101 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 102–111 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 112–121 */
    0, 0, 0, 0, 0, 0           /* 122–127 */
};

unsigned char shifted_keyboard_map[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 0–9 */
  '(', ')', '_', '+', '\b',  /* Backspace */
  '\t',          /* Tab */
  'Q', 'W', 'E', 'R', /* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter key */
    0,          /* 29 - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
 '\"', '~',   0,        /* Left shift */
  '|', 'Z', 'X', 'C', 'V', 'B', 'N',        /* 49 */
  'M', '<', '>', '?',   0,        /* Right shift */
  '*',          /* Keypad * */
    0,          /* Alt */
  ' ',          /* Space bar */
    0,          /* Caps lock */
    0,          /* 59 - F1 key */
    0, 0, 0, 0, 0, 0, 0, 0, 0, /* F2–F10 */
    0,          /* 69 - Num lock */
    0,          /* Scroll Lock */
  0x80,         /* Home key */
  0x81,         /* Up Arrow */
  0x82,         /* Page Up */
  '-',          /* Keypad - */
  0x83,         /* Left Arrow */
    0,          /* 75 - Reserved */
  0x84,         /* Right Arrow */
  '+',          /* Keypad + */
  0x85,         /* End key */
  0x86,         /* Down Arrow */
  0x87,         /* Page Down */
  0x88,         /* Insert Key */
  0x89,         /* Delete Key */
    0, 0, 0,    /* 86–88 - Undefined */
    0,          /* F11 Key */
    0,          /* F12 Key */
    0,          /* 91 - All other keys are undefined */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 92–101 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 102–111 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* 112–121 */
    0, 0, 0, 0, 0, 0           /* 122–127 */
};
