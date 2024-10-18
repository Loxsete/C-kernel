#include "keyboard_map.h"
#include <string.h>

#define LINES 25
#define COLUMNS_IN_LINE 80
#define BYTES_FOR_EACH_ELEMENT 2
#define SCREENSIZE (BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE * LINES)

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E

extern unsigned char keyboard_map[128];

static inline void write_port(unsigned short port, unsigned char data) {
    asm volatile ("outb %0, %1" :: "a"(data), "Nd"(port));
}

static inline unsigned char read_port(unsigned short port) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

unsigned int current_loc = 0; // Текущая позиция курсора
char *vidptr = (char*)0xb8000; // Начало видео памяти
char input_buffer[256]; // Буфер для ввода команды
unsigned int input_pos = 0; // Позиция в буфере ввода

void shutdown(void) {
    asm volatile ("movl $0, %eax\n\t"
                  "int $0x19");
}
void restart(void) {
    // Установка прерывания BIOS для перезагрузки системы
    asm volatile ("movl $0, %eax\n\t"
                  "int $0x19");
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void clear_screen(void) {
    for (int i = 0; i < COLUMNS_IN_LINE * LINES; i++) {
        vidptr[i * BYTES_FOR_EACH_ELEMENT] = ' '; // Заполняем пробелами
        vidptr[i * BYTES_FOR_EACH_ELEMENT + 1] = 0x07; // Устанавливаем атрибут
    }
    current_loc = 0; // Сбрасываем текущую позицию курсора
}

void display_prompt(void) {
    const char *prompt = "Loxsete $: ";
    for (unsigned int i = 0; prompt[i] != '\0'; i++) {
        vidptr[current_loc++] = prompt[i];
        vidptr[current_loc++] = 0x07;
    }
}

int check_shutdown_command(void) {
    if (my_strcmp(input_buffer, "shutdown") == 0) {
        shutdown();
        return 1; // Команда shutdown найдена
    } else if (my_strcmp(input_buffer, "restart") == 0) {
        restart();
        return 1; // Команда restart найдена
    }
    return 0; // Команда не найдена
}

void process_command(void) {
    input_buffer[input_pos] = '\0'; // Завершаем строку
    if (check_shutdown_command()) {
        clear_screen();
        const char *shutdown_msg = "Shutting down...";
        for (unsigned int i = 0; shutdown_msg[i] != '\0'; i++) {
            vidptr[current_loc++] = shutdown_msg[i];
            vidptr[current_loc++] = 0x07;
        }
        while (1); // Бесконечный цикл для симуляции завершения работы
    }
    // Очищаем строку после выполнения команды
    unsigned int line_start = (current_loc / (BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE)) * (BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE) + 12;
    for (unsigned int i = line_start + 2; i < current_loc; i += 2) {
        vidptr[i] = ' '; // Заменяем символ на пробел
        vidptr[i + 1] = 0x07; // Восстанавливаем атрибут
    }
    current_loc = line_start + 2; // Сброс позиции курсора для следующего ввода
    input_pos = 0; // Сбрасываем буфер ввода
    display_prompt(); // Повторно отображаем приглашение
}

void keyboard_handler_main(void) {
    unsigned char status;
    char keycode;

    // Проверяем наличие данных перед чтением
    status = read_port(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        keycode = read_port(KEYBOARD_DATA_PORT);
        // Проверяем код клавиши
        if (keycode < 0 || keycode >= 128) return; // Проверка диапазона

        // Обработка нажатия клавиш
        if (keycode == ENTER_KEY_CODE) {
            process_command(); // Обработка команды после нажатия Enter
            return;
        }
        else if (keycode == BACKSPACE_KEY_CODE) {
            if (input_pos > 0 && current_loc > 12) { // Предотвращаем удаление приглашения
                input_pos--;
                current_loc -= 2;
                vidptr[current_loc] = ' '; // Удаляем символ
                vidptr[current_loc + 1] = 0x07; // Восстанавливаем атрибут
            }
            return;
        }

        // Проверяем, можно ли вводить символ
        if (input_pos < sizeof(input_buffer) - 1 && current_loc < (BYTES_FOR_EACH_ELEMENT * COLUMNS_IN_LINE)) {
            char c = keyboard_map[(unsigned char)keycode];
            if (c != 0) { // Если нажатая клавиша отображается на клавиатуре
                vidptr[current_loc++] = c;
                vidptr[current_loc++] = 0x07; // Стандартный атрибут текста
                input_buffer[input_pos++] = c; // Добавляем символ в буфер
            }
        }
    }

    write_port(0x20, 0x20); // Завершаем прерывание
}

void kmain(void) {
    clear_screen();
    display_prompt(); // Отображаем "Loxsete $: "

    while (1) {
        keyboard_handler_main(); // Обрабатываем ввод с клавиатуры
    }
}
