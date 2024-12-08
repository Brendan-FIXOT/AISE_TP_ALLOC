#include "benchmark.h"

// Benchmark pour malloc/free
void benchmark_malloc_free(size_t num_allocations, size_t size, int methode_chosen) {
    if (methode_chosen == 1) {
        auto start = std::chrono::high_resolution_clock::now();

        // Allocation et désallocation répétées avec malloc/free
        void** pointers = new void*[num_allocations];
        for (size_t i = 0; i < num_allocations; ++i) {
            pointers[i] = malloc(size);
            if (pointers[i] == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
        }
        for (size_t i = 0; i < num_allocations; ++i) {
            free(pointers[i]);
        }
        delete[] pointers;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "malloc/free (méthode 1) : " << num_allocations << " allocations et désallocations de "
                  << size << " octets en " << duration << " µs ("
                  << (num_allocations * 1e6 / duration) << " opérations/sec)\n";
    } 
    else if (methode_chosen == 2) {
        auto start = std::chrono::high_resolution_clock::now();

        // Allocation et désallocation répétées avec malloc/free
        for (size_t i = 0; i < num_allocations; ++i) {
            void* ptr = malloc(size);
            if (ptr == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
            free(ptr);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "malloc/free (méthode 2) : " << num_allocations << " allocations et désallocations de "
                  << size << " octets en " << duration << " µs ("
                  << (num_allocations * 1e6 / duration) << " opérations/sec)\n";
    } 
    else {
        std::cout << "Le choix de la méthode n'est pas bon, il n'y a que la 1 et 2." << std::endl;
    }
}

// Benchmark pour my_malloc/my_free
void benchmark_my_malloc_free(size_t num_allocations, size_t size, int methode_chosen) {
    Allocator allocator;
    if (methode_chosen == 1) {
        auto start = std::chrono::high_resolution_clock::now();

        // Allocation et désallocation répétées avec my_malloc/my_free
        void** pointers = new void*[num_allocations];
        for (size_t i = 0; i < num_allocations; ++i) {
            pointers[i] = allocator.my_malloc(size);
            if (pointers[i] == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
        }
        for (size_t i = 0; i < num_allocations; ++i) {
            allocator.my_free(pointers[i], size); // Passer explicitement la taille pour my_free
        }
        delete[] pointers;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "my_malloc/my_free (méthode 1) : " << num_allocations << " allocations et désallocations de "
                  << size << " octets en " << duration << " µs ("
                  << (num_allocations * 1e6 / duration) << " opérations/sec)\n";
    }
    else if (methode_chosen == 2)
    {
        auto start = std::chrono::high_resolution_clock::now();

        // Allocation et désallocation répétées avec my_malloc/my_free
        for (size_t i = 0; i < num_allocations; ++i) {
            void* ptr = allocator.my_malloc(size);
            if (ptr == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
            allocator.my_free(ptr, size); // Passer explicitement la taille pour my_free
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "my_malloc/my_free (méthode 2) : " << num_allocations << " allocations et désallocations de "
                  << size << " octets en " << duration << " µs ("
                  << (num_allocations * 1e6 / duration) << " opérations/sec)\n";
    }
    else {
        std::cout << "Le choix de la méthode n'est pas bon, il n'y a que la 1 et 2." << std::endl;
    } 
}

// Benchmark pour my_malloc_basic/my_free_basic
void benchmark_my_malloc_free_basic(size_t num_allocations, size_t size, int methode_chosen) {
    if (methode_chosen == 1) {
        auto start = std::chrono::high_resolution_clock::now();

        // Allocation et désallocation répétées avec my_malloc/my_free
        void** pointers = new void*[num_allocations];
        for (size_t i = 0; i < num_allocations; ++i) {
            pointers[i] = my_malloc_basic(size);
            if (pointers[i] == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
        }
        for (size_t i = 0; i < num_allocations; ++i) {
            my_free_basic(pointers[i], size); // Passer explicitement la taille pour my_free
        }
        delete[] pointers;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "my_malloc_basic/my_free_basic (méthode 1) : " << num_allocations << " allocations et désallocations de "
                  << size << " octets en " << duration << " µs ("
                  << (num_allocations * 1e6 / duration) << " opérations/sec)\n";
    }
    else if (methode_chosen == 2) {
        auto start = std::chrono::high_resolution_clock::now();

        // Allocation et désallocation répétées avec my_malloc/my_free
        for (size_t i = 0; i < num_allocations; ++i) {
            void* ptr = my_malloc_basic(size);
            if (ptr == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
            my_free_basic(ptr, size); // Passer explicitement la taille pour my_free
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        std::cout << "my_malloc_basic/my_free_basic (méthode 2) : " << num_allocations << " allocations et désallocations de "
                  << size << " octets en " << duration << " µs ("
                  << (num_allocations * 1e6 / duration) << " opérations/sec)\n";
    }
    else {
        std::cout << "Le choix de la méthode n'est pas bon, il n'y a que la 1 et 2." << std::endl;
    }
}