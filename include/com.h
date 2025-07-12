#ifndef COM_H
#define COM_H

#define COM1_PORT 0x3F8

void com_init(void);
void com_send_char(char c);
void com_send_string(const char *str);
int com_data_available(void);
char com_read_char(void);

#endif
