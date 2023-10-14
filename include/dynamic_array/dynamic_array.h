#include <blog/blog.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define DYNAMIC_ARRAY_CREATE(type) dynamic_array_create(sizeof(type))

typedef struct dynamic_array {
  size_t allocated;
  size_t length;
  size_t stride;
  void* array;
} dynamic_array;

dynamic_array* dynamic_array_create(size_t stride) {
  void* array = malloc(stride * 4);

  dynamic_array* dynamic_array = malloc(3 * sizeof(size_t) + stride * 4);

  dynamic_array->array = array;
  dynamic_array->allocated = 4;
  dynamic_array->length = 0;
  dynamic_array->stride = stride;

  return dynamic_array;
}

void* dynamic_array_get(dynamic_array* dynamic_array, int index) {
  if (index >= dynamic_array->length) {
    blog_log("Index Out Of Bounds! | dynamic_array_get()\n");
    exit(1);
  }
  return dynamic_array->array + index * dynamic_array->stride;
}

void dynamic_array_set(dynamic_array* dynamic_array, int index, void* value) {
  if (index >= dynamic_array->length) {
    blog_log("Index Out Of Bounds! | dynamic_array_set()\n");
    exit(1);
  }
  memcpy(dynamic_array->array + (index * dynamic_array->stride), value, dynamic_array->stride);
}

void dynamic_array_push(dynamic_array* dynamic_array, void* element) {
  if (dynamic_array->length >= dynamic_array->allocated) {
    void* old = dynamic_array->array;
    dynamic_array->array = malloc(dynamic_array->allocated * dynamic_array->stride);

    memcpy(dynamic_array->array, old, dynamic_array->allocated * dynamic_array->stride);

    free(old);
    dynamic_array->allocated *= 2;
  }

  dynamic_array->length++;
  dynamic_array_set(dynamic_array, dynamic_array->length - 1, element);
}

void dynamic_array_destroy(dynamic_array* dynamic_array) {
  free(dynamic_array->array);
  free(dynamic_array);
}

void dynamic_array_remove(dynamic_array* dynamic_array, int index) {
  if (index >= dynamic_array->length) {
    blog_log("Index Out Of Bounds! | dynamic_array_remove()\n");
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
