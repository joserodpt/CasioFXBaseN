#include <gint/gint.h>
#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/hardware.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_INPUT_LENGTH 32

char* decimalToHexadecimal(const char* decimalString) {
    char* endptr;
    long decimalNumber = strtol(decimalString, &endptr, 10);

    // Check for conversion errors
    if (*endptr != '\0') {
        return NULL; // Invalid decimal string
    }

    // Calculate the length of the hexadecimal string
    size_t hexLength = snprintf(NULL, 0, "%lX", decimalNumber);

    // Allocate memory for the hexadecimal string
    char* hexString = (char*)malloc(hexLength + 1);
    if (hexString == NULL) {
        return NULL; // Memory allocation failed
    }

    // Print the hexadecimal representation into the allocated string
    snprintf(hexString, hexLength + 1, "%lX", decimalNumber);

    return hexString;
}


char* decimalToBinary(const char* decimalString) {
    char* endptr;
    long decimalNumber = strtol(decimalString, &endptr, 10);

    // Check for conversion errors
    if (*endptr != '\0') {
        return NULL; // Invalid decimal string
    }
    size_t binaryLength = sizeof(long) * 8;

    // Allocate memory for the binary string (plus one for the null terminator)
    char* binaryString = (char*)malloc(binaryLength + 1);
    if (binaryString == NULL) {
        return NULL; // Memory allocation failed
    }

    // Set the null terminator
    binaryString[binaryLength] = '\0';

    // Convert decimal to binary
    for (size_t i = binaryLength; i > 0; i--) {
        binaryString[i - 1] = (decimalNumber & 1) ? '1' : '0';
        decimalNumber >>= 1;
    }

    // Find the first '1' to remove leading zeros
    char* firstOne = strchr(binaryString, '1');
    if (firstOne == NULL) {
        // If no '1' found, the number is 0
        strcpy(binaryString, "0");
    } else {
        // Move the string to remove leading zeros
        memmove(binaryString, firstOne, strlen(firstOne) + 1);
    }

    return binaryString;
}


char* hexadecimalToDecimal(const char* hexString) {
    char* endptr;
    long long decimalNumber = strtoll(hexString, &endptr, 16);

    // Check for conversion errors
    if (*endptr != '\0') {
        return NULL; // Invalid hexadecimal string
    }

    // Calculate the length of the decimal string
    size_t decimalLength = snprintf(NULL, 0, "%lld", decimalNumber);

    // Allocate memory for the decimal string
    char* decimalString = (char*)malloc(decimalLength + 1);
    if (decimalString == NULL) {
        return NULL; // Memory allocation failed
    }

    // Print the decimal representation into the allocated string
    snprintf(decimalString, decimalLength + 1, "%lld", decimalNumber);

    return decimalString;
}

char* hexadecimalToBinary(const char* hexString) {
    char* endptr;
    long long decimalNumber = strtoll(hexString, &endptr, 16);

    // Check for conversion errors
    if (*endptr != '\0') {
        return NULL; // Invalid hexadecimal string
    }

    // Calculate the maximum length of the binary string
    size_t binaryLength = sizeof(long long) * 8;

    // Allocate memory for the binary string (plus one for the null terminator)
    char* binaryString = (char*)malloc(binaryLength + 1);
    if (binaryString == NULL) {
        return NULL; // Memory allocation failed
    }

    // Set the null terminator
    binaryString[binaryLength] = '\0';

    // Convert decimal to binary
    for (size_t i = binaryLength; i > 0; i--) {
        binaryString[i - 1] = (decimalNumber & 1) ? '1' : '0';
        decimalNumber >>= 1;
    }

    // Find the first '1' to remove leading zeros
    char* firstOne = strchr(binaryString, '1');
    if (firstOne == NULL) {
        // If no '1' found, the number is 0
        strcpy(binaryString, "0");
    } else {
        // Move the string to remove leading zeros
        memmove(binaryString, firstOne, strlen(firstOne) + 1);
    }

    return binaryString;
}

char* binaryToHexadecimal(const char* binaryString) {
    char* endptr;
    long long decimalNumber = strtoll(binaryString, &endptr, 2);

    // Check for conversion errors
    if (*endptr != '\0') {
        return NULL; // Invalid binary string
    }

    // Calculate the length of the hexadecimal string
    size_t hexLength = snprintf(NULL, 0, "%llX", decimalNumber);

    // Allocate memory for the hexadecimal string
    char* hexString = (char*)malloc(hexLength + 1);
    if (hexString == NULL) {
        return NULL; // Memory allocation failed
    }

    // Print the hexadecimal representation into the allocated string
    snprintf(hexString, hexLength + 1, "%llX", decimalNumber);

    return hexString;
}

char* binaryToDecimal(const char* binaryString) {
    char* endptr;
    long long decimalNumber = strtoll(binaryString, &endptr, 2);

    // Check for conversion errors
    if (*endptr != '\0') {
        return NULL; // Invalid binary string
    }

    // Calculate the length of the decimal string
    size_t decimalLength = snprintf(NULL, 0, "%lld", decimalNumber);

    // Allocate memory for the decimal string
    char* decimalString = (char*)malloc(decimalLength + 1);
    if (decimalString == NULL) {
        return NULL; // Memory allocation failed
    }

    // Print the decimal representation into the allocated string
    snprintf(decimalString, decimalLength + 1, "%lld", decimalNumber);

    return decimalString;
}

int modeSelector;
//0 - decimal
//1 - hexadecimal
//2 - binario

int main(void)
{
    //REFERENCIA: https://git.planet-casio.com/Lephenixnoir/gint/src/branch/master/include/gint


    dclear(C_WHITE);
    char input[MAX_INPUT_LENGTH];
    int length = 0;
    input[0] = '\0'; // Initialize the input string as empty

    while (1) {
        // Update the display
        dclear(C_WHITE);

        row_title("Base-N Converter      v1.0       Coded in Portugal :)");

        row_print(1, 2, "Input > %s", input);

        if (modeSelector == 0) {
            row_print(3, 2, "Hexadecimal: 0x%s", decimalToHexadecimal(input));
            row_print(4, 2, "Binary:");
            row_print(5, 2, "%s", decimalToBinary(input));

            fkey_button_selected(1, "DEC");
            fkey_button(2, "HEX");
            fkey_button(3, "BIN");
        } else if (modeSelector == 1) {
            row_print(3, 2, "Decimal: %s", hexadecimalToDecimal(input));            
            row_print(4, 2, "Binary:");
            row_print(5, 2, "%s", hexadecimalToBinary(input));

            fkey_button(1, "DEC");
            fkey_button_selected(2, "HEX");
            fkey_button(3, "BIN");
        } else if (modeSelector == 2) {
            row_print(3, 2, "Decimal: %s", binaryToDecimal(input));           
            row_print(4, 2, "Hexadecimal: 0x%s", binaryToHexadecimal(input));

            fkey_button(1, "DEC");
            fkey_button(2, "HEX");
            fkey_button_selected(3, "BIN");
        }

        dupdate();

        // Get the key press
        key_event_t key = getkey();

        if (key.type == KEYEV_DOWN) {
            if (key.key == KEY_F1) {
                modeSelector = 0;
                input[0] = '\0'; length = 0;
            } else if (key.key == KEY_F2) {
                modeSelector = 1;
                input[0] = '\0'; length = 0;
            } else if (key.key == KEY_F3) {
                modeSelector = 2;
                input[0] = '\0'; length = 0;
            } else if (key.key == KEY_DEL && length > 0) {
                // Handle backspace
                length--;
                input[length] = '\0';
            } else if (length < MAX_INPUT_LENGTH - 1) {
                char ch = '\0';

                if (modeSelector == 0) {
                    switch (key.key) {
                        case KEY_0: ch = '0'; break;
                        case KEY_1: ch = '1'; break;
                        case KEY_2: ch = '2'; break;
                        case KEY_3: ch = '3'; break;
                        case KEY_4: ch = '4'; break;
                        case KEY_5: ch = '5'; break;
                        case KEY_6: ch = '6'; break;
                        case KEY_7: ch = '7'; break;
                        case KEY_8: ch = '8'; break;
                        case KEY_9: ch = '9'; break;
                    }
                } else if (modeSelector == 1) {
                    switch (key.key) {
                        case KEY_0: ch = '0'; break;
                        case KEY_1: ch = '1'; break;
                        case KEY_2: ch = '2'; break;
                        case KEY_3: ch = '3'; break;
                        case KEY_4: ch = '4'; break;
                        case KEY_5: ch = '5'; break;
                        case KEY_6: ch = '6'; break;
                        case KEY_7: ch = '7'; break;
                        case KEY_8: ch = '8'; break;
                        case KEY_9: ch = '9'; break;
                        case KEY_XOT: ch = 'a'; break;
                        case KEY_LOG: ch = 'b'; break;
                        case KEY_LN: ch = 'c'; break;
                        case KEY_SIN: ch = 'd'; break;
                        case KEY_COS: ch = 'e'; break;
                        case KEY_TAN: ch = 'f'; break;
                    }
                } else if (modeSelector == 2) {
                    switch (key.key) {
                        case KEY_0: ch = '0'; break;
                        case KEY_1: ch = '1'; break;
                    }
                }

                if (ch != '\0') {
                    input[length] = ch;
                    length++;
                    input[length] = '\0';
                }
            }
        }
    }

    return 1;
}