# A Generic Dynamic Array in C

## Introduction

Simply `#define` the type, `T`, and `#include` array.h

`N` can also be defined as the "namespace" with which to prefix the functions.
For example, if `N` is defined as double_array, then the functions will be named as `double_array_push`, `double_array_pop` and so on.

For the first include in a file, `N` doesnt need to be defined, and the namespace defaults to simply `array`, with the functions being called `array_push`, `array_pop`, etc.
For all subsequent includes in the same file, if `N` isn't defined then the namespace defaults to `array_T`, where `T` is the name of the type.

## Building and Running

Building and running the given example file
```console
$ gcc example.c -o example && ./example
```

## Limitations

One of the main limitations of this approach is that types with multiple words (Eg. `unsigned int` or even `int *`) are not supported due to the way macros work in C.
A possible workaround is to use `typedef` to define an alias, like `typedef int *int_ptr` and using that instead. 
`stdint.h` can also be included to get access to the types like `uint32_t`, etc.
