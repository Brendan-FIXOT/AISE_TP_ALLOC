#include "myAllocator.h"
#include <cassert>

// Constructeur : initialise les listes chaînées
Allocator::Allocator() 
    : free_lists(NUM_CLASSES, nullptr), list_mutexes(NUM_CLASSES), freeblock_count(NUM_CLASSES, 0) {}

// Destructeur : nettoie les blocs restants (appel optionnel à munmap)
Allocator::~Allocator() {
    for (size_t i = 0; i < NUM_CLASSES; i++) {
        FreeBlock* current = free_lists[i];
        while (current != nullptr) {
            FreeBlock* next = current->next;
            munmap(current, 1 << i); // Désallouer chaque bloc
            current = next;
        }
        free_lists[i] = nullptr;
    }
}

size_t Allocator::align_size(size_t size) {
    size_t aligned_size = 16;
    while (aligned_size <= size) {
        aligned_size *= 2;
    }
    return aligned_size;
}

size_t Allocator::get_class_index(size_t size) {
    size_t index = 0;
    size_t aligned_size = 16;
    while (aligned_size < size) {
        aligned_size *= 2;
        index++;
    }
    assert(index < NUM_CLASSES); // Vérifie que l'indice est valide
    return index;
}

void* Allocator::my_malloc(size_t size) {
    // On suppose un appel avec un élément non nul
    if (size == 0) {
        return nullptr;
    }

    // Aligner la taille et trouver la classe correspondante
    size_t aligned_size = align_size(size);
    size_t total_size = aligned_size + sizeof(FreeBlock); // Inclure l'en-tête
    size_t class_index = get_class_index(aligned_size);

    {
        // Lock pour protéger l'accès à la liste chaînée
        std::lock_guard<std::mutex> lock(list_mutexes[class_index]);

        // Si un bloc est disponible dans la liste, réutiliser
        if (free_lists[class_index] != nullptr) {
            FreeBlock* block = free_lists[class_index];
            free_lists[class_index] = block->next; // Retirer le bloc de la liste
            freeblock_count[class_index]--;  // Mise à jour du compteur de blocs
            return (void*)((char*)block + sizeof(FreeBlock)); // Retourner la mémoire après l'en-tête
        }
    }

    // Allocation la mémoire avec mmap
    void* ptr = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    // Vérifier si l'allocation a réussi
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return nullptr;
    }
    return (void*)((char*)ptr + sizeof(FreeBlock)); // Retourner la mémoire après l'en-tête
}

void Allocator::my_free(void* ptr, size_t size) {
    if (ptr == NULL || size == 0) {
        return;
    }

    // Aligner la taille et trouver la classe correspondante
    size_t aligned_size = align_size(size);
    size_t total_size = aligned_size + sizeof(FreeBlock);
    size_t class_index = get_class_index(aligned_size);

    // Récupérer l'adresse de l'en-tête
    FreeBlock* block = (FreeBlock*)((char*)ptr - sizeof(FreeBlock));
    block->size = total_size;

    {
        // Lock pour protéger l'accès à la liste chaînée
        std::lock_guard<std::mutex> lock(list_mutexes[class_index]);

        // Ajouter le bloc à la liste chaînée
        block->next = free_lists[class_index];
        // Insérer dans la liste chaînée
        free_lists[class_index] = block;

        // Mise à jour du compteur
        freeblock_count[class_index]++;

        // Fusionner les blocs adjacents
        coalesce_blocks(class_index);
    }
    // Nettoyer la liste si elle devient trop grande
    if (freeblock_count[class_index] > MAX_FREE_BLOCKS) {
        cleanup_free_list(class_index, aligned_size);
    }
}

// Fonction pour limiter la taille d'une liste chaînée
void Allocator::cleanup_free_list(size_t class_index, size_t block_size) {
    size_t free_count = 0;

    std::lock_guard<std::mutex> lock(list_mutexes[class_index]); // Protection de la liste chaînée

    FreeBlock* current = free_lists[class_index];
    FreeBlock* prev = nullptr;

    while (current != nullptr) {
        free_count++;
        if (free_count > MAX_FREE_BLOCKS) {
            // Désallouer les blocs restants avec munmap
            FreeBlock* next = current->next;
            munmap(current, block_size);
            if (prev != nullptr) {
                prev->next = next;
            } else {
                free_lists[class_index] = next;
            }
            current = next;
            // Mise à jour du compteur global de blocs
            freeblock_count[class_index]--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void Allocator::coalesce_blocks(size_t class_index) {
    FreeBlock* current = free_lists[class_index];
    FreeBlock* prev = nullptr;

    while (current != nullptr) {
        if (prev && (char*)prev + prev->size == (char*)current) {
            prev->size += current->size;
            prev->next = current->next;
        } else {
            prev = current;
        }
        current = current->next;
    }
}