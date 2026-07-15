/*
processor.h - заголовочный файл модуля processor.c

Смоликов Роман
МК-101
*/
#pragma once
#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stddef.h>
#include <stdint.h>

int find_pattern(const uint8_t *data, size_t data_len,
    const uint8_t *pattern, size_t pattern_len);

size_t partial_match_length(const uint8_t *data, size_t data_len,
    const uint8_t *pattern, size_t pattern_len);

int process_file(const char *input_path,
    const char *output_path,
    const uint8_t *pattern,
    size_t pattern_len,
    const uint8_t *replacement,
    size_t replacement_len);

#endif