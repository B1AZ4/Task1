/*
cli_parser.h - заголовочный файл модуля cli_parser.c

Смоликов Роман
МК-101
*/
#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <stddef.h>
#include <stdint.h>

int hex_decode(const char *hex_str, uint8_t **out, size_t *out_len);
void hex_free(uint8_t *data);

#endif