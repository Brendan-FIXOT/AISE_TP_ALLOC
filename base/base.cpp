#include "base.h"

void* my_malloc(size_t size) {
    // On suppose un appel avec un élément non nul
    if (size == 0) {
        return NULL;
    }

    // Allocation la mémoire avec mmap
    void* ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    // Vérifier si l'allocation a réussi
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return NULL;
    }

    return ptr;
}

void my_free(void* ptr, size_t size) {
    if (ptr == NULL || size == 0) {
        return;
    }

    if (munmap(ptr, size) != 0) {
        perror("munmap failed");
    }
}
