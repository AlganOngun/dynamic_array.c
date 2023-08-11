#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

typedef struct dynamic_array dynamic_array;

dynamic_array* _dynamic_array_create(size_t stride);
void dynamic_array_push(dynamic_array* dynamic_array, void* element);
void dynamic_array_destroy(dynamic_array* dynamic_array);
void* dynamic_array_get(dynamic_array* dynamic_array, int index);
void dynamic_array_set(dynamic_array* dynamic_array, int index, void* value);
void dynamic_array_remove(dynamic_array* dynamic_array, int index);

#define dynamic_array_create(type) _dynamic_array_create(sizeof(type))

#endif
