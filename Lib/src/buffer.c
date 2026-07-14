/*
 Модуль для работы с буфером данных

Смоликов Роман
МК-101
*/
#include "buffer.h"
#include <stdlib.h>
#include <string.h>

Buffer* buffer_create(size_t capacity) {
    Buffer *buf = (Buffer*)malloc(sizeof(Buffer));
    if (!buf) return NULL;

    buf->data = (uint8_t*)malloc(capacity);
    if (!buf->data) {
        free(buf);
        return NULL;
    }

    buf->capacity = capacity;
    buf->size = 0;
    buf->offset = 0;
    return buf;
}

void buffer_destroy(Buffer *buf) {
    if (buf) {
        free(buf->data);
        free(buf);
    }
}

const uint8_t* buffer_data(const Buffer *buf) {
    return buf->data + buf->offset;
}

size_t buffer_size(const Buffer* buf) {
    return buf->size;
}


void buffer_add(Buffer *buf, const uint8_t *data, size_t len) {
    if (buf->size + len > buf->capacity) {
        if (buf->offset > 0) {
            memmove(buf->data, buf->data + buf->offset, buf->size);
            buf->offset = 0;
        }
        if (buf->size + len > buf->capacity) {
            len = buf->capacity - buf->size;
        }
    }

    memcpy(buf->data + buf->offset + buf->size, data, len);
    buf->size += len;
}

void buffer_remove(Buffer *buf, size_t len) {
    if (len >= buf->size) {
        buf->size = 0;
        buf->offset = 0;
    }
    else {
        buf->offset += len;
        buf->size -= len;
    }
}