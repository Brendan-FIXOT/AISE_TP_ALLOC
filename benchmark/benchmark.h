#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <iostream>
#include <chrono> // Pour mesurer le temps
#include <cstdlib> // Pour malloc/free
#include "../myAllocator/myAllocator.h" // Pour my_malloc/my_free
#include "../myAllocatorBasic/myAllocatorBasic.h" // Pour my_malloc_basic/my_free_basic

void benchmark_malloc_free(size_t num_allocations, size_t size, int methode_chosen);

void benchmark_my_malloc_free(size_t num_allocations, size_t size, int methode_chosen);

void benchmark_my_malloc_free_basic(size_t num_allocations, size_t size, int methode_chosen);

#endif // BENCHMARK_H