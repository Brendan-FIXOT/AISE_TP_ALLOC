#include <gtest/gtest.h>
#include "myAllocatorBasic/myAllocatorBasic.h"
#include "myAllocator/myAllocator.h"

Allocator allocator;

// Test d'allocation mémoire
TEST(MyAllocatorTest, AllocBasic) {
    void* ptr = allocator.my_malloc(128);
    ASSERT_NE(ptr, nullptr); // Vérifie que le pointeur n'est pas NULL

    char* data = (char*)ptr;
    for (size_t i = 0; i < 128; ++i) {
        data[i] = 42;
    }

    for (size_t i = 0; i < 128; ++i) {
        EXPECT_EQ(data[i], 42); // Vérifie que chaque octet est bien 42
    }

    allocator.my_free(ptr, 128);
}

// Test avec allocation de taille nulle
TEST(MyAllocatorTest, AllocZeroSize) {
    void* ptr = allocator.my_malloc(0);
    EXPECT_EQ(ptr, nullptr); // On s'attend à un pointeur nul
}

// Test d'allocation mémoire
TEST(MyAllocatorBasicTest, AllocBasic) {
    void* ptr = my_malloc_basic(128);
    ASSERT_NE(ptr, nullptr); // Vérifie que le pointeur n'est pas NULL

    char* data = (char*)ptr;
    for (size_t i = 0; i < 128; ++i) {
        data[i] = 42;
    }

    for (size_t i = 0; i < 128; ++i) {
        EXPECT_EQ(data[i], 42); // Vérifie que chaque octet est bien 42
    }

    my_free_basic(ptr, 128);
}

// Test avec allocation de taille nulle
TEST(MyAllocatorBasicTest, AllocZeroSize) {
    void* ptr = my_malloc_basic(0);
    EXPECT_EQ(ptr, nullptr); // On s'attend à un pointeur nul
}

// Main pour lancer les tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
