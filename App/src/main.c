/*
main.c - главный модуль программы

Смоликов Роман
МК-101
*/
#include "cli_parser.h"
#include "processor.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <input_file> <output_file> <pattern_hex> <replacement_hex>\n",
            argv[0]);
        fprintf(stderr, "Example: %s input.bin output.bin 48656c6c6f 576f726c64\n",
            argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    const char *pattern_hex = argv[3];
    const char *replacement_hex = argv[4];

    FILE* test = fopen(input_file, "rb");
    if (!test) {
        fprintf(stderr, "Error: cannot open input file '%s'\n", input_file);
        return 1;
    }
    fclose(test);

    uint8_t *pattern = NULL;
    uint8_t *replacement = NULL;
    size_t pattern_len, replacement_len;

    if (hex_decode(pattern_hex, &pattern, &pattern_len) != 0) {
        fprintf(stderr, "Error: invalid hex pattern '%s'\n", pattern_hex);
        return 1;
    }

    if (hex_decode(replacement_hex, &replacement, &replacement_len) != 0) {
        fprintf(stderr, "Error: invalid hex replacement '%s'\n", replacement_hex);
        hex_free(pattern);
        return 1;
    }

    printf("Processing file: %s\n", input_file);
    printf("Pattern length: %zu bytes\n", pattern_len);
    printf("Replacement length: %zu bytes\n", replacement_len);

    int result = process_file(input_file, output_file,
        pattern, pattern_len,
        replacement, replacement_len);

    hex_free(pattern);
    hex_free(replacement);

    if (result == 0) {
        printf("Success! Output written to: %s\n", output_file);
    }
    else {
        fprintf(stderr, "Error processing file\n");
    }

    return result;
}