#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <sys/mman.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <string.h>

// Structure pour représenter un bloc libre
struct FreeBlock {
    FreeBlock* next;
};
    
class Allocator {
private:
    // Méthodes utilitaires
    size_t align_size(size_t size);
    size_t get_class_index(size_t size);

    // Tableau de listes chaînées pour les blocs libres
    static const size_t NUM_CLASSES = 32; // Nombre de classes de tailles (par exemple, 2^5 à 2^36)
    std::vector<FreeBlock*> free_lists;

    // Politique pour gérer les blocs libres (exemple : taille maximale d'une liste)
    static const size_t MAX_FREE_BLOCKS = 100;
    
    // Nettoyer les blocs inutilisés si nécessaire
    void cleanup_free_list(size_t class_index, size_t block_size);
public:
    Allocator();
    ~Allocator();

    // Fonctions d'allocation et de désallocation
    void* my_malloc(size_t size);
    void my_free(void* ptr, size_t size);
};

#endif // ALLOCATOR_H