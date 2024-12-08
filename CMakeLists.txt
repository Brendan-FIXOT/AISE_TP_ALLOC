cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(ALLOC_TP_AISE)

# Définir les sources
set(SOURCES1 myAllocator/myAllocator.cpp myAllocatorBasic/myAllocatorBasic.cpp)
set(SOURCES2 benchmark/main_bench.cpp benchmark/benchmark.cpp)

# Option pour activer le profiling
option(PROFILE "Activer le profiling avec gprof" OFF)

# Créer l'exécutable pour les tests
add_executable(ALLOC_TEST test.cpp ${SOURCES1})

# Créer l'exécutable pour les benchmarks
add_executable(BENCHMARK ${SOURCES1} ${SOURCES2})

# Trouver GTest et lier à l'exécutable de test
find_package(GTest REQUIRED)

# Utiliser la signature "keyword" partout avec "PRIVATE" pour lier les bibliothèques
target_link_libraries(ALLOC_TEST PRIVATE GTest::GTest GTest::Main)

# Activer le support de testing dans CMake
enable_testing()

# Lier les tests à l'exécutable de test
add_test(NAME TestAlloc COMMAND ALLOC_TEST)

# Si le profiling est activé, ajouter les options de compilation pour gprof
if(PROFILE)
    message(STATUS "Profiling avec gprof activé")

    # Ajouter les options de compilation pour gprof
    target_compile_options(ALLOC_TEST PRIVATE -pg)
    target_compile_options(BENCHMARK PRIVATE -pg)

    # Lier les bibliothèques avec gprof en utilisant la signature avec "PRIVATE"
    target_link_libraries(ALLOC_TEST PRIVATE -pg)
    target_link_libraries(BENCHMARK PRIVATE -pg)
endif()

# Cible pour exécuter le programme avec gprof
add_custom_target(benchmark_gprof
    COMMAND cmake -DPROFILE=ON ..
    COMMAND make
    COMMAND ./BENCHMARK
    COMMAND gprof BENCHMARK gmon.out > ../analyse/analyse.txt
    COMMENT "Exécution des tests de performance avec gprof"
)