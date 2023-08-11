#include "buffers.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

buffer* buffer_allocate(size_t size) {
  char* buf = malloc(size);
  buffer* buffer = malloc(sizeof(size_t));

  buffer->buffer = buf;
  buffer->capacity = size;

  for (size_t i = 0; i < buffer->capacity; i++) {
    buffer->buffer[i] = '\0';
  }

  return buffer;
}

buffer* buffer_32 = &((buffer) {NULL, 0});
buffer* buffer_64 = &((buffer) {NULL, 0});
buffer* buffer_128 = &((buffer) {NULL, 0});

void* buffer_reserve(buffer* buffer, size_t size) {
  for (size_t i = 0; i < buffer->capacity; i++) {
    if (buffer->buffer[i] == '\0') return buffer->buffer + i;
  }

  perror("BUFFER FULL!");
  exit(1);
}

void buffer_clear(void* starting_point, size_t size) {
  for (size_t i = 0; i < size; i++) {
    ((char*)starting_point)[i] = '\0';
  }
}
