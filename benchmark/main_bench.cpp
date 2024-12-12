#include "benchmark.h"

int main() {
    size_t num_allocations = 10000; // Nombre d'allocations
    size_t size = 128; // Taille de chaque allocation
    size_t min_size = 16;
    size_t max_size = 1024;
    float free_probability = 0.2; // 20% de chances de libérer un bloc existant
    int repetitions = 10;

    for (int methode = 1; methode < 4; ++methode) {
        double duration1_mean, duration2_mean, duration3_mean;

        double duration1 = 0.0;
        double duration2 = 0.0;
        double duration3 = 0.0;

        for (int i = 0; i < repetitions; ++i) {
            // Benchmark avec malloc/free
            duration1 += benchmark_malloc_free(num_allocations, size, min_size, max_size, free_probability, methode);

            // Benchmark avec my_malloc/my_free
            duration2 += benchmark_my_malloc_free(num_allocations, size, min_size, max_size, free_probability, methode);

            // Benchmark avec my_malloc_basic/my_free_basic (servant de témoin pour my_malloc/my_free)
            duration3 += benchmark_my_malloc_free_basic(num_allocations, size, min_size, max_size, free_probability,     methode);

        }
        duration1_mean = duration1/(double)repetitions;
        duration2_mean = duration2/(double)repetitions;
        duration3_mean = duration3/(double)repetitions;

        std::cout << "Durée moyenne sur " << repetitions << " repetitions (méthode " << methode << ") avec " << num_allocations << " allocations et désallocations de " << size << " octets pour :" << std::endl
                  << "- malloc/free : " << duration1_mean << " µs (" << (num_allocations * 1e6 / duration1) << " opérations/sec)"<< std::endl
                  << "- my_malloc/my_free : " << duration2_mean << " µs (" << (num_allocations * 1e6 / duration2) << " opérations/sec)"<< std::endl
                  << "- my_malloc_basic/my_free_basic : " << duration3_mean << " µs (" << (num_allocations * 1e6 / duration3) << " opérations/sec)\n"<< std::endl;
    }
    return 0;
}