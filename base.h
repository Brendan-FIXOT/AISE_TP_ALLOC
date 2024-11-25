#ifndef BASE_H
#define BASE_H

#include <sys/mman.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void* my_malloc(size_t size);

void my_free(void* ptr, size_t size);

#endif // BASE_H