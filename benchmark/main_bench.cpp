#include "benchmark.h"

int main() {
    size_t num_allocations = 100000; // Nombre d'allocations
    size_t size = 128;              // Taille de chaque allocation

    for (int methode = 1; methode < 3; ++methode) {
        // Benchmark avec malloc/free
        benchmark_malloc_free(num_allocations, size, methode);

        // Benchmark avec my_malloc/my_free
        benchmark_my_malloc_free(num_allocations, size, methode);

        // Benchmark avec my_malloc_basic/my_free_basic (servant de témoin pour my_malloc/my_free)
        benchmark_my_malloc_free_basic(num_allocations, size, methode);

        std::cout << std::endl;
    }

    return 0;
}