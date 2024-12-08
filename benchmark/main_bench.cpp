#include "benchmark.h"

int main() {
    size_t num_allocations = 10000; // Nombre d'allocations
    size_t size = 128;              // Taille de chaque allocation

    // Benchmark avec malloc/free
    benchmark_malloc_free(num_allocations, size);

    // Benchmark avec my_malloc/my_free
    benchmark_my_malloc_free(num_allocations, size);

    // Benchmark avec my_malloc_basic/my_free_basic (servant de témoin pour my_malloc/my_free)
    benchmark_my_malloc_free_basic(num_allocations, size);

    return 0;
}