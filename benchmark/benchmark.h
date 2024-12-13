#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <iostream>
#include <chrono> // Pour mesurer le temps
#include <cstdlib> // Pour malloc/free
#include <random>
#include <fstream>
#include <vector>
#include <filesystem> // Permet de créer des dossiers à travers des programmes
#include "../myAllocator/myAllocator.h" // Pour my_malloc/my_free
#include "../myAllocatorBasic/myAllocatorBasic.h" // Pour my_malloc_basic/my_free_basic

size_t random_size(size_t min_size, size_t max_size);

float benchmark_malloc_free(size_t num_allocations, size_t min_size, size_t max_size, float free_probability, int methode_chosen);

float benchmark_my_malloc_free(size_t num_allocations, size_t min_size, size_t max_size, float free_probability, int methode_chosen);

float benchmark_my_malloc_free_basic(size_t num_allocations, size_t min_size, size_t max_size, float free_probability, int methode_chosen);

#endif // BENCHMARK_H