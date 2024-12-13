#include "benchmark.h"

int main() {
    // Paramètres généraux
    size_t min_size = 16;
    size_t max_size = 1024;
    float free_probability = 0.2;
    int repetitions = 10; // Pour prendre une moyenne sur plusieurs exécutions

    /* ------------------------------------------------------------------------- /
    // 1) Plot du temps en fonction de num_allocations pour la méthode 3 et 4   //
    / ------------------------------------------------------------------------- */
    {
        if (std::filesystem::create_directories("../ploting/data/")) {
            std::cout << "Dossier créé avec succès : " << "../ploting/data/" << std::endl;
        } else {
            std::cout << "Le dossier existe déjà ou dans certains cas rare il y a une erreur lors de sa création." << std::endl;
        }

        std::ofstream file_num_allocation("../ploting/data/plot_num_allocations.csv");

        // Vérifie si le fichier s'ouvre correctement
        if (!file_num_allocation.is_open()) {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier '../ploting/data/plot_num_allocations.csv'" << std::endl;
            return 1; // Quitte le programme avec un code d'erreur
        }

        file_num_allocation << "num_allocations,method,duration_malloc_free,duration_my_malloc_free,duration_my_malloc_free_basic\n";

        // On fait varier le nombre d'allocations
        for (size_t num_allocations : {1000, 5000, 10000, 20000, 50000}) {
            for (int methode : {1, 2, 3}) {
                double duration1 = 0.0;
                double duration2 = 0.0;
                double duration3 = 0.0;

                for (int i = 0; i < repetitions; ++i) {
                    duration1 += benchmark_malloc_free(num_allocations, min_size, max_size, free_probability, methode);
                    duration2 += benchmark_my_malloc_free(num_allocations, min_size, max_size, free_probability, methode);
                    duration3 += benchmark_my_malloc_free_basic(num_allocations, min_size, max_size, free_probability, methode);
                }

                double duration1_mean = duration1 / (double)repetitions;
                double duration2_mean = duration2 / (double)repetitions;
                double duration3_mean = duration3 / (double)repetitions;

                // On écrit dans le fichier CSV
                file_num_allocation << num_allocations << "," << methode << "," 
                                    << duration1_mean << "," << duration2_mean << "," << duration3_mean << std::endl;

                // On écrit en sortie terminal (pour les commits)
                std::cout << "Durée moyenne sur " << repetitions << " repetitions (méthode " << methode << ") avec " << num_allocations << " allocations et désallocations de " << min_size << " à " << max_size << " octets pour :" << std::endl
                        << "- malloc/free : " << duration1_mean << " µs (" << (num_allocations * 1e6 / duration1) << " opérations/sec)"<< std::endl
                        << "- my_malloc/my_free : " << duration2_mean << " µs (" << (num_allocations * 1e6 / duration2) << " opérations/sec)"<< std::endl
                        << "- my_malloc_basic/my_free_basic : " << duration3_mean << " µs (" << (num_allocations * 1e6 / duration3) << " opérations/sec)\n"<< std::endl;
            }
        }
    }

    /* ---------------------------------------------------------------------------- /
    // 2) Plot du temps en fonction de la taille max_size pour la méthode 3 et 4   //
    / ---------------------------------------------------------------------------- */
    {
        if (std::filesystem::create_directories("../ploting/data/")) {
            std::cout << "Dossier créé avec succès : " << "../ploting/data/" << std::endl;
        } else {
            std::cout << "Le dossier existe déjà ou dans certains cas rare il y a une erreur lors de sa création." << std::endl;
        }

        std::ofstream file_sizes("../ploting/data/plot_sizes.csv");

        // Vérifie si le fichier s'ouvre correctement
        if (!file_sizes.is_open()) {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier '../ploting/data/plot_sizes.csv'" << std::endl;
            return 1; // Quitte le programme avec un code d'erreur
        }

        file_sizes << "max_size,method,duration_malloc_free,duration_my_malloc_free,duration_my_malloc_free_basic\n";

        size_t num_allocations = 10000; // Fixe
        for (size_t current_max_size : {64, 128, 256, 512, 1024, 2048}) {
            for (int methode : {1, 2, 3}) {
                double duration1 = 0.0;
                double duration2 = 0.0;
                double duration3 = 0.0;

                for (int i = 0; i < repetitions; ++i) {
                    duration1 += benchmark_malloc_free(num_allocations, min_size, current_max_size, free_probability, methode);
                    duration2 += benchmark_my_malloc_free(num_allocations, min_size, current_max_size, free_probability, methode);
                    duration3 += benchmark_my_malloc_free_basic(num_allocations, min_size, current_max_size, free_probability, methode);
                }

                double duration1_mean = duration1 / (double)repetitions;
                double duration2_mean = duration2 / (double)repetitions;
                double duration3_mean = duration3 / (double)repetitions;

                // On écrit dans le fichier CSV
                file_sizes << current_max_size << "," << methode << "," 
                           << duration1_mean << "," << duration2_mean << "," << duration3_mean << std::endl;
                
                // On écrit en sortie terminal (pour les commits)
                std::cout << "Durée moyenne sur " << repetitions << " repetitions (méthode " << methode << ") avec " << num_allocations << " allocations et désallocations (nombre fixe) de " << min_size << " à " << current_max_size << " octets pour :" << std::endl
                        << "- malloc/free : " << duration1_mean << " µs (" << (num_allocations * 1e6 / duration1) << " opérations/sec)"<< std::endl
                        << "- my_malloc/my_free : " << duration2_mean << " µs (" << (num_allocations * 1e6 / duration2) << " opérations/sec)"<< std::endl
                        << "- my_malloc_basic/my_free_basic : " << duration3_mean << " µs (" << (num_allocations * 1e6 / duration3) << " opérations/sec)\n"<< std::endl;
            }
        }
    }
    return 0;
}