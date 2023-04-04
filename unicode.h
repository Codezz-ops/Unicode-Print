/*
* Author: Codezz-Ops <Codezz-ops@protonmail.com>
*/

#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>
#include <locale.h>

int uniprint(const wchar_t* format, ...) {
    va_list args;
    va_start(args, format);

    wchar_t buffer[4096];
    int size = vswprintf(buffer, sizeof(buffer), format, args);
    if (size < 0) {
        va_end(args);
        return -1;
    }

    setlocale(LC_ALL, "en_US.UTF-8");
    for (int i = 0; i < size; i++) {
        if (buffer[i] == L'\\' && buffer[i + 1] == 'u') {
            // Parse the Unicode code point value from the string
            wchar_t hex_str[5] = { buffer[i + 2], buffer[i + 3], buffer[i + 4], buffer[i + 5], L'\0' };
            wint_t code_point = (wint_t)wcstoul(hex_str, NULL, 16);

            // Print the Unicode character to the console
            putwchar(code_point);

            // Skip the Unicode escape sequence in the input buffer
            i += 5;
        } else {
            // Print the regular character to the console
            putwchar(buffer[i]);
        }
    }

    va_end(args);
    return size;
}
