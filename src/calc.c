#include "calc.h"
#include "kernel.h" // For kprint

// Helper function to convert string to integer (simple, no error handling for non-digits)
int atoi(const char *str) {
    int result = 0;
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}

// Calculate function: expects input like "calc 2+2"
void calc(const char *input) {
    // Skip "calc " (5 characters)
    while (*input && *input != ' ') input++;
    if (*input == ' ') input++; // Move past space

    if (!*input) {
        kprint("Error: No expression provided.\n");
        return;
    }

    // Parse first number
    int num1 = atoi(input);
    while (*input >= '0' && *input <= '9') input++;

    // Parse operator
    char op = *input;
    if (op != '+' && op != '-' && op != '*' && op != '/') {
        kprint("Error: Invalid operator. Use +, -, *, or /.\n");
        return;
    }
    input++;

    // Parse second number
    int num2 = atoi(input);
    while (*input >= '0' && *input <= '9') input++;

    // Check for trailing characters
    if (*input) {
        kprint("Error: Invalid expression format.\n");
        return;
    }

    // Perform calculation
    int result;
    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                kprint("Error: Division by zero.\n");
                return;
            }
            result = num1 / num2;
            break;
        default:
            kprint("Error: Unknown operator.\n");
            return;
    }

    // Convert result to string for printing
    char buffer[16];
    int i = 0;
    if (result < 0) {
        buffer[i++] = '-';
        result = -result;
    }
    // Handle digits
    int temp = result;
    int digits[16];
    int digit_count = 0;
    do {
        digits[digit_count++] = temp % 10;
        temp /= 10;
    } while (temp);
    // Append digits in reverse order
    for (int j = digit_count - 1; j >= 0; j--) {
        buffer[i++] = digits[j] + '0';
    }
    buffer[i] = '\0';

    kprint("Result: ");
    kprint(buffer);
    kprint("\n");
}
