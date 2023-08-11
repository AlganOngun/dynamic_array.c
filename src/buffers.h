#ifndef BUFFERS_H
#define BUFFERS_H

#include <stdbool.h>
#include <stddef.h>

enum BUFFER_TYPE { BUFFER_32, BUFFER_64, BUFFER_128 };

typedef struct buffer {
  char* buffer;
  size_t capacity;
} buffer;

extern buffer* buffer_32;
extern buffer* buffer_64;
extern buffer* buffer_128;

buffer* buffer_allocate(size_t size);
void buffer_clear(void* starting_point, size_t size);
void* buffer_reserve(buffer* buffer, size_t size);

#endif
