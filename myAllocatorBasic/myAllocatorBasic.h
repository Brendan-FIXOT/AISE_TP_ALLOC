#ifndef MYALLOCATORBASIC_H
#define MYALLOCATORBASIC_H

#include <sys/mman.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void* my_malloc_basic(size_t size);

void my_free_basic(void* ptr, size_t size);

#endif // MYALLOCATORBASIC_H