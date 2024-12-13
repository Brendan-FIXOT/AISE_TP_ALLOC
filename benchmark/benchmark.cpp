#include "benchmark.h"

// Générateur de nombres aléatoires (pour les tailles d'allocations et l'aléatoire des libérations)
std::random_device rd;
std::mt19937 gen(rd());

// Fonction de génération de tailles d'allocations aléatoires.
size_t random_size(size_t min_size, size_t max_size) {
    std::uniform_int_distribution<size_t> dist(min_size, max_size);
    return dist(gen);
}

// Benchmark pour malloc/free
float benchmark_malloc_free(size_t num_allocations, size_t min_size, size_t max_size, float free_probability, int methode_chosen) {
    if (methode_chosen == 1) {
        // Méthode avec des tailles d'allocations aléatoires et des désallocations une fois que tout a été alloué
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<size_t> alloc_size; // Pour un soucis d'égalité entre chaque benchmark, un tableau est implémenté (même si dispensable)

        // Allocation et désallocation répétées avec malloc/free
        void** pointers = new void*[num_allocations];
        for (size_t i = 0; i < num_allocations; ++i) {
            alloc_size.push_back(random_size(min_size, max_size));
            pointers[i] = malloc(alloc_size[i]);
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
        float duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        return duration;
    }
    else if (methode_chosen == 2) {
        // Méthode avec des tailles d'allocations aléatoires et des déallocations directes
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < num_allocations; ++i) {
            size_t alloc_size = random_size(min_size, max_size);
            void* ptr = malloc(alloc_size);
            if (ptr == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
            // Libération du bloc
            free(ptr);
        }

        auto end = std::chrono::high_resolution_clock::now();
        float duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        return duration;
    }
    else if (methode_chosen == 3) {
        // Méthode avec des tailles d'allocations aléatoires et des désallocations conditionnelles aléatoires (méthode réaliste)
        std::vector<void*> active_pointers;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < num_allocations; ++i) {
            size_t alloc_size = random_size(min_size, max_size);
            void* ptr = malloc(alloc_size);
            if (ptr == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
            active_pointers.push_back(ptr);

            // Libération aléatoire des blocs
            if (active_pointers.size() > 10 && ((float)rand() / RAND_MAX) < free_probability) {
                size_t index = rand() % active_pointers.size();
                free(active_pointers[index]);
                active_pointers.erase(active_pointers.begin() + index);
            }
        }

        // Libérer tous les blocs restants
        for (void* ptr : active_pointers) {
            free(ptr);
        }

        auto end = std::chrono::high_resolution_clock::now();
        float duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        return duration;
    }
    else {
        std::cout << "Le choix de la méthode n'est pas bon, il n'y a que la 1 et 2." << std::endl;
        return 0;
    }
}

// Benchmark pour my_malloc/my_free
float benchmark_my_malloc_free(size_t num_allocations, size_t min_size, size_t max_size, float free_probability, int methode_chosen) {
    Allocator allocator;
    if (methode_chosen == 1) {
        // Méthode avec des tailles d'allocations aléatoires et des désallocations une fois que tout a été alloué
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<size_t> alloc_size; // Tableau nécéssaire pour les désallocations

        // Allocation et désallocation répétées avec my_malloc/my_free
        void** pointers = new void*[num_allocations];
        for (size_t i = 0; i < num_allocations; ++i) {
            alloc_size.push_back(random_size(min_size, max_size));
            pointers[i] = allocator.my_malloc(alloc_size[i]);
            if (pointers[i] == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
        }
        for (size_t i = 0; i < num_allocations; ++i) {
            allocator.my_free(pointers[i], alloc_size[i]); // Passer explicitement la taille pour my_free
        }
        delete[] pointers;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        return duration;
    }
    else if (methode_chosen == 2) {
        // Méthode avec des tailles d'allocations aléatoires et des déallocations directes
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < num_allocations; ++i) {
            size_t alloc_size = random_size(min_size, max_size);
            void* ptr = malloc(alloc_size);
            if (ptr == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
            // Libération du bloc
            free(ptr);
        }

        auto end = std::chrono::high_resolution_clock::now();
        float duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        return duration;
    }
    else if (methode_chosen == 3) {
        // Méthode avec des tailles d'allocations aléatoires et des désallocations conditionnelles aléatoires (méthode réaliste)
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < num_allocations; ++i) {
            size_t alloc_size = random_size(min_size, max_size);
            void* ptr = allocator.my_malloc(alloc_size);
            if (ptr == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
            allocator.my_free(ptr, alloc_size);
        }

        auto end = std::chrono::high_resolution_clock::now();
        float duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        return duration;
    }
    else {
        std::cout << "Le choix de la méthode n'est pas bon, il n'y a que la 1 et 2." << std::endl;
        return 0;
    } 
}

// Benchmark pour my_malloc_basic/my_free_basic
float benchmark_my_malloc_free_basic(size_t num_allocations, size_t min_size, size_t max_size, float free_probability, int methode_chosen) {
    if (methode_chosen == 1) {
        // Méthode avec des tailles d'allocations aléatoires et des désallocations une fois que tout a été alloué
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<size_t> alloc_size; // Tableau nécéssaire ici pour les désallocations

        // Allocation et désallocation répétées avec my_malloc/my_free
        void** pointers = new void*[num_allocations];
        for (size_t i = 0; i < num_allocations; ++i) {
            alloc_size.push_back(random_size(min_size, max_size));
            pointers[i] = my_malloc_basic(alloc_size[i]);
            if (pointers[i] == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
        }
        for (size_t i = 0; i < num_allocations; ++i) {
            my_free_basic(pointers[i], alloc_size[i]); // Passer explicitement la taille pour my_free
        }
        delete[] pointers;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        return duration;
    }
    else if (methode_chosen == 2) {
        // Méthode avec des tailles d'allocations aléatoires et des déallocations directes
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < num_allocations; ++i) {
            size_t alloc_size = random_size(min_size, max_size);
            void* ptr = my_malloc_basic(alloc_size);
            if (ptr == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
            // Libération du bloc
            my_free_basic(ptr, alloc_size);
        }

        auto end = std::chrono::high_resolution_clock::now();
        float duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        return duration;
    }
    else if (methode_chosen == 3) {
        // Méthode avec des tailles d'allocations aléatoires et des désallocations conditionnelles aléatoires (méthode réaliste)
        std::vector<void*> active_pointers;

        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < num_allocations; ++i) {
            size_t alloc_size = random_size(min_size, max_size);
            void* ptr = my_malloc_basic(alloc_size);
            if (ptr == nullptr) {
                std::cerr << "Allocation failed at iteration " << i << "\n";
                exit(EXIT_FAILURE);
            }
            active_pointers.push_back(ptr);

            // Libération aléatoire des blocs
            if (active_pointers.size() > 10 && ((float)rand() / RAND_MAX) < free_probability) {
                size_t index = rand() % active_pointers.size();
                my_free_basic(active_pointers[index], alloc_size);
                active_pointers.erase(active_pointers.begin() + index);
            }
        }

        // Libérer tous les blocs restants
        for (void* ptr : active_pointers) {
            my_free_basic(ptr, max_size);
        }

        auto end = std::chrono::high_resolution_clock::now();
        float duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        return duration;
    }
    else {
        std::cout << "Le choix de la méthode n'est pas bon, il n'y a que la 1 et 2." << std::endl;
        return 0;
    }
}