/*
 Модуль для парсинга аргументов командной строки

Смоликов Роман
МК-101
*/
#include "cli_parser.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int hex_decode(const char *hex_str, uint8_t **out, size_t *out_len) {
    size_t len = strlen(hex_str);

    if (len % 2 != 0) return -1;
    if (len == 0) {
        *out_len = 0;
        *out = NULL;
        return 0;
    }

    *out_len = len / 2;
    *out = (uint8_t*)malloc(*out_len);
    if (!*out) return -1;

    for (size_t i = 0; i < len; i += 2) {
        if (!isxdigit(hex_str[i]) || !isxdigit(hex_str[i + 1])) {
            free(*out);
            return -1;
        }

        char hex_byte[3] = { hex_str[i], hex_str[i + 1], '\0' };
        (*out)[i / 2] = (uint8_t)strtol(hex_byte, NULL, 16);
    }

    return 0;
}

void hex_free(uint8_t *data) {
    free(data);
}