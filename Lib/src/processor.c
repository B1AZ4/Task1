/*
 Модуль для поиска и замены последовательности

Смоликов Роман
МК-101
*/
#include "processor.h"
#include <string.h>
#include <stdio.h>

int find_pattern(const uint8_t *data, size_t data_len,
    const uint8_t *pattern, size_t pattern_len) {
    if (pattern_len == 0 || data_len < pattern_len) return -1;

    for (size_t i = 0; i <= data_len - pattern_len; i++) {
        if (memcmp(data + i, pattern, pattern_len) == 0) {
            return (int)i;
        }
    }
    return -1;
}
size_t partial_match_length(const uint8_t *data, size_t data_len,
    const uint8_t *pattern, size_t pattern_len) {
    size_t max_check = (data_len < pattern_len - 1) ? data_len : pattern_len - 1;

    for (size_t len = max_check; len > 0; len--) {
        if (memcmp(data + data_len - len, pattern, len) == 0) {
            return len;
        }
    }
    return 0;
}
#ifndef BLOCK_SIZE
#define BLOCK_SIZE 1024
#endif

int process_file(const char* input_path, const char* output_path,
    const uint8_t* pattern, size_t pattern_len,
    const uint8_t* replacement, size_t replacement_len) {
    if (pattern_len == 0) {
        fprintf(stderr, "Error: pattern length cannot be zero\n");
        return 1;
    }

    if (pattern_len > 2 * BLOCK_SIZE) {
        fprintf(stderr, "Error: pattern length (%zu) exceeds 2*N (%d)\n",
            pattern_len, 2 * BLOCK_SIZE);
        return 1;
    }

    FILE* fin = fopen(input_path, "rb");
    if (!fin) {
        perror("Failed to open input file");
        return 1;
    }

    FILE* fout = fopen(output_path, "wb");
    if (!fout) {
        perror("Failed to open output file");
        fclose(fin);
        return 1;
    }

    Buffer* buf = buffer_create(4 * BLOCK_SIZE);
    if (!buf) {
        fclose(fin);
        fclose(fout);
        return 1;
    }

    uint8_t temp[BLOCK_SIZE];
    size_t bytes_read;
    int result = 0;

    while ((bytes_read = fread(temp, 1, BLOCK_SIZE, fin)) > 0) {
        buffer_add(buf, temp, bytes_read);

        int pos;
        while ((pos = find_pattern(buffer_data(buf), buffer_size(buf),
            pattern, pattern_len)) != -1) {
            if (fwrite(buffer_data(buf), 1, pos, fout) != pos) {
                result = 1;
                goto cleanup;
            }
            buffer_remove(buf, pos);

            if (fwrite(replacement, 1, replacement_len, fout) != replacement_len) {
                result = 1;
                goto cleanup;
            }
            buffer_remove(buf, pattern_len);
        }

        if (buffer_size(buf) > BLOCK_SIZE) {
            size_t keep = (pattern_len > 1) ? pattern_len - 1 : 0;
            size_t write_size = buffer_size(buf) - keep;

            if (fwrite(buffer_data(buf), 1, write_size, fout) != write_size) {
                result = 1;
                goto cleanup;
            }
            buffer_remove(buf, write_size);
        }
    }

    if (buffer_size(buf) > 0) {
        if (fwrite(buffer_data(buf), 1, buffer_size(buf), fout) != buffer_size(buf)) {
            result = 1;
        }
    }

cleanup:
    buffer_destroy(buf);
    fclose(fin);
    fclose(fout);
    return result;
}