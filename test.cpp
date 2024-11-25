#include <gtest/gtest.h>
#include "base/base.h"

// Test d'allocation mémoire
TEST(MyAllocatorTest, AllocBasic) {
    void* ptr = my_malloc(128);
    ASSERT_NE(ptr, nullptr); // Vérifie que le pointeur n'est pas NULL

    char* data = (char*)ptr;
    for (size_t i = 0; i < 128; ++i) {
        data[i] = 42;
    }

    for (size_t i = 0; i < 128; ++i) {
        EXPECT_EQ(data[i], 42); // Vérifie que chaque octet est bien 42
    }

    my_free(ptr, 128);
}

// Test avec allocation de taille nulle
TEST(MyAllocatorTest, AllocZeroSize) {
    void* ptr = my_malloc(0);
    EXPECT_EQ(ptr, nullptr); // On s'attend à un pointeur nul
}

// Main pour lancer les tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
