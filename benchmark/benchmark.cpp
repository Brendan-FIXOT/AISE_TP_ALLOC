#include "benchmark.h"

// Benchmark pour malloc/free
void benchmark_malloc_free(size_t num_allocations, size_t size) {
    auto start = std::chrono::high_resolution_clock::now();

    // Allocation et désallocation répétées avec malloc/free
    void** pointers = new void*[num_allocations];
    for (size_t i = 0; i < num_allocations; ++i) {
        pointers[i] = malloc(size);
    }
    for (size_t i = 0; i < num_allocations; ++i) {
        free(pointers[i]);
    }
    delete[] pointers;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "malloc/free : " << num_allocations << " allocations et désallocations en " 
              << duration << " µs (" << (num_allocations * 1e6 / duration) << " opérations/sec)\n";
}

// Benchmark pour my_malloc/my_free
void benchmark_my_malloc_free(size_t num_allocations, size_t size) {
    auto start = std::chrono::high_resolution_clock::now();

    // Allocation et désallocation répétées avec my_malloc/my_free
    void** pointers = new void*[num_allocations];
    for (size_t i = 0; i < num_allocations; ++i) {
        pointers[i] = my_malloc(size);
    }
    for (size_t i = 0; i < num_allocations; ++i) {
        my_free(pointers[i], size); // Passer explicitement la taille pour my_free
    }
    delete[] pointers;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "my_malloc/my_free : " << num_allocations << " allocations et désallocations en " 
              << duration << " µs (" << (num_allocations * 1e6 / duration) << " opérations/sec)\n";
}