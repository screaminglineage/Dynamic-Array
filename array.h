#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#ifndef T
#error "define T as a specific type before including this file"
#endif

#ifndef N
    #ifndef ARRAY_INCLUDED
        #define N array
    #else
        #define N macro_concat(array_, T)
    #endif
#endif

#define macro__concat(A, B) A ## B
#define macro_concat(A, B) macro__concat(A, B)

#ifndef ARRAY_INIT_CAP
#define ARRAY_INIT_CAP 8
#endif

typedef struct {
    T *data;
    size_t length;
    size_t capacity;
} macro_concat(Array_, T);

// Available functions:
//
// void array_reserve(array, amount)
// T *array_push(array, item)
// Array_T *array_extend(array, tail)
// T array_pop(array)
// T array_swap_remove(array)
// void array_free(array)


#define next_power_of_two(n) \
    n--, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8, n |= n >> 16, n |= n >> 32, ++n

void macro_concat(N, _reserve)(macro_concat(Array_, T) *arr, size_t len) {
    size_t new_length = arr->length + (len);
    if (new_length > arr->capacity) {
        if (arr->capacity == 0 && new_length < ARRAY_INIT_CAP) {
            arr->capacity = ARRAY_INIT_CAP;
        } else {
            arr->capacity = next_power_of_two(new_length);
        }
        arr->data = realloc(arr->data, sizeof(arr->data[0]) * arr->capacity); 
        assert(arr->data && "array_reserve: allocation failed");
    }
}

T *macro_concat(N, _push)(macro_concat(Array_, T) *arr, T item) {
    macro_concat(N, _reserve)(arr, 1);
    arr->data[arr->length++] = item;
    return &arr->data[arr->length - 1];
}

macro_concat(Array_, T) *macro_concat(N, _extend)(macro_concat(Array_, T) *arr, macro_concat(Array_, T) *tail) {
    macro_concat(N, _reserve)(arr, tail->length);
    memcpy(arr->data + arr->length, tail->data, sizeof(tail->data[0]) * tail->length);
    arr->length += tail->length;
    return arr;
}

T macro_concat(N, _pop)(macro_concat(Array_, T) *arr) {
    return arr->data[--arr->length];
}

T macro_concat(N, _swap_remove)(macro_concat(Array_, T) *arr, size_t index) {
    assert(index < arr->length && "index of out bounds");

    T tmp = arr->data[index];
    arr->data[index] = arr->data[arr->length - 1];
    arr->data[arr->length - 1] = tmp;
    return arr->data[--arr->length];
}

void macro_concat(N, _free)(macro_concat(Array_, T) *arr) {
    free(arr->data);
    memset(arr, 0, sizeof(*arr));
}

#ifndef ARRAY_INCLUDED
#define ARRAY_INCLUDED
#endif

#undef T
#undef N
#undef ARRAY_INIT_CAP
#undef macro__concat
#undef macro_concat
#undef next_power_of_two


