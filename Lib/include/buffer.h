/*
buffer.h - заголовочный файл модуля buffer.c

Смоликов Роман
МК-101
*/
#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *data;
    size_t capacity;
    size_t size;
    size_t offset;
} Buffer;

Buffer* buffer_create(size_t capacity);
void buffer_destroy(Buffer *buf);
void buffer_add(Buffer *buf, const uint8_t *data, size_t len);
const uint8_t* buffer_data(const Buffer *buf);
size_t buffer_size(const Buffer *buf);
void buffer_remove(Buffer *buf, size_t len);

#endif