#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <iostream>
#include <chrono> // Pour mesurer le temps
#include <cstdlib> // Pour malloc/free
#include "../base/base.h" // Pour my_malloc/my_free

void benchmark_malloc_free(size_t num_allocations, size_t size);

void benchmark_my_malloc_free(size_t num_allocations, size_t size);

#endif // BENCHMARK_H