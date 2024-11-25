cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(ALLOC_TP_AISE)

# Définir les sources
set(SOURCES1 base/base.cpp)
set(SOURCES2 benchmark/main_bench.cpp benchmark/benchmark.cpp)

# Créer l'exécutable principal
#add_executable(ALLOC ${SOURCES1})

# Ajouter un exécutable pour les tests
add_executable(ALLOC_TEST test.cpp ${SOURCES1})
add_executable(BENCHMARK ${SOURCES1} ${SOURCES2})

find_package(GTest REQUIRED)
target_link_libraries(ALLOC_TEST GTest::GTest GTest::Main)

# Activer le support de testing
enable_testing()

# Lier les tests à l'exécutable (au besoin)
add_test(NAME TestAlloc COMMAND ALLOC_TEST)