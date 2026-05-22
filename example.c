// Dynamic Array in C using C++ template-like generics
// Simply define the type, T, and #include array.h
// N can also be defined as the "namespace" with which to prefix the functions
// For example, if N is defined as double_array, then the functions will be double_array_push and so on
//
// For the first include in a file, N doesnt need to be defined, and the namespace defaults to simple "array"
// For all subsequent includes in the same file, if N isnt defined then the namespace defaults to "array_T"
#include <stdio.h>

#define T int
#include "array.h"

#define T double
#define N darray
#include "array.h"

int main() {
    Array_int a = {0};
    for (size_t i = 0; i < 10; i++) {
        array_push(&a, i);
    }

    for (size_t i = 0; i < a.length; i++) {
        printf("%d ", a.data[i]);
    }
    printf("\n");

    int i;
    i = array_pop(&a); printf("Popped: %d\n", i);
    i = array_pop(&a); printf("Popped: %d\n", i);
    i = array_pop(&a); printf("Popped: %d\n", i);

    printf("New length: %zu\n", a.length);

    Array_double b = {0};
    for (size_t i = 0; i < 10; i++) {
        darray_push(&b, i);
    }

    for (size_t i = 0; i < b.length; i++) {
        printf("%.2f ", b.data[i]);
    }
    printf("\n");

    double d;
    d = darray_swap_remove(&b, 4);              printf("Removed: %.2f\n", d);
    d = darray_swap_remove(&b, 2);              printf("Removed: %.2f\n", d);
    d = darray_swap_remove(&b, b.length - 1);   printf("Removed: %.2f\n", d);

    printf("New length: %zu\n", b.length);

    Array_int i1 = {0};
    Array_int i2 = {0};
    for (size_t i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            printf("i1.push: %d\n", *array_push(&i1, i));
        } else {
            printf("i2.push: %d\n", *array_push(&i2, i));
        }
    }

    array_extend(&i1, &i2);
    for (size_t i = 0; i < i1.length; i++) {
        printf("%d ", i1.data[i]);
    }
    printf("\n");

    array_free(&a);
    darray_free(&b);
    array_free(&i1);
    array_free(&i2);

    return 0;
}
