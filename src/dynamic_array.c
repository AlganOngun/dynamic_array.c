#include "dynamic_array.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffers.h"

struct dynamic_array {
  size_t allocated;
  size_t length;
  size_t stride;
  enum BUFFER_TYPE buffer_type;
  void* array;
};

dynamic_array* _dynamic_array_create(size_t stride) {
  if (buffer_32->capacity == 0) buffer_32 = buffer_allocate(32);
  void* array = buffer_reserve(buffer_32, stride * 4);

  dynamic_array* dynamic_array = malloc(sizeof(size_t) * 3 + sizeof(enum BUFFER_TYPE));

  dynamic_array->array = array;
  dynamic_array->allocated = 4;
  dynamic_array->length = 0;
  dynamic_array->stride = stride;
  dynamic_array->buffer_type = BUFFER_32;

  return dynamic_array;
}

void* dynamic_array_get(dynamic_array* dynamic_array, int index) {
  if (index >= dynamic_array->length) {
    perror("Index Out Of Bounds! | dynamic_array_get()\n");
    exit(1);
  }
  return dynamic_array->array + (index * dynamic_array->stride);
}

void dynamic_array_set(dynamic_array* dynamic_array, int index, void* value) {
  if (index >= dynamic_array->length) {
    perror("Index Out Of Bounds! | dynamic_array_set()\n");
    exit(1);
  }
  memcpy(dynamic_array->array + (index * dynamic_array->stride), value, dynamic_array->stride);
}

void dynamic_array_push(dynamic_array* dynamic_array, void* element) {
  if (dynamic_array->length >= dynamic_array->allocated) {
    void* temp = dynamic_array->array;

    if (dynamic_array->buffer_type == BUFFER_32) {
      if (buffer_64->capacity == 0) buffer_64 = buffer_allocate(64);
      dynamic_array->array = buffer_reserve(buffer_64, dynamic_array->stride * 8);
      memcpy(dynamic_array->array, temp, dynamic_array->allocated * dynamic_array->stride);
      buffer_clear(temp, dynamic_array->stride * dynamic_array->length);

      dynamic_array->buffer_type = BUFFER_64;
      dynamic_array->allocated = 8;
    } else if (dynamic_array->buffer_type == BUFFER_64) {
      if (buffer_128->capacity == 0) buffer_128 = buffer_allocate(128);
      dynamic_array->array = buffer_reserve(buffer_128, dynamic_array->stride * 16);
      memcpy(dynamic_array->array, temp, dynamic_array->allocated * dynamic_array->stride);
      buffer_clear(temp, dynamic_array->stride * dynamic_array->length);

      dynamic_array->buffer_type = BUFFER_128;
      dynamic_array->allocated = 16;
    }
  }

  dynamic_array->length++;
  dynamic_array_set(dynamic_array, dynamic_array->length - 1, element);
}

void dynamic_array_destroy(dynamic_array* dynamic_array) {
  buffer_clear(dynamic_array->array, dynamic_array->allocated);

  free(dynamic_array);
}

void dynamic_array_remove(dynamic_array* dynamic_array, int index) {
  if (index >= dynamic_array->length) {
    perror("Index Out Of Bounds! | dynamic_array_remove()\n");
    exit(1);
  }

  void* after = dynamic_array->array + ((index + 1) * dynamic_array->stride);

  for (void* element = after;
       element < dynamic_array->array + (dynamic_array->length * dynamic_array->stride);
       element += dynamic_array->stride) {
    memmove(element - dynamic_array->stride, element, dynamic_array->stride);
  }

  dynamic_array->length--;
}
