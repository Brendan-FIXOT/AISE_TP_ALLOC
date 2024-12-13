import pandas as pd
import matplotlib.pyplot as plt

# Chargement des données
df_num_allocation = pd.read_csv('data/plot_num_allocations.csv')
df_sizes = pd.read_csv('data/plot_sizes.csv')

# Structure des CSV (rappel) :
# plot_num_allocations.csv : num_allocations,method,duration_malloc_free,duration_my_malloc_free,duration_my_malloc_free_basic
# plot_sizes.csv : max_size,method,duration_malloc_free,duration_my_malloc_free,duration_my_malloc_free_basic

# 1) Plot du temps en fonction du nombre d'allocations pour les méthodes 3 et 4
# On va créer un plot pour méthode = 3 et un autre pour méthode = 4
for method_val in [1, 2, 3]:
    df_m = df_num_allocation[df_num_allocation['method'] == method_val]

    # On a plusieurs points correspondant à différents num_allocations
    # On va tracer trois courbes :
    # - malloc/free vs num_allocations
    # - my_malloc/my_free vs num_allocations
    # - my_malloc_basic/my_free_basic vs num_allocations

    plt.figure(figsize=(8,6))
    plt.plot(df_m['num_allocations'], df_m['duration_malloc_free'], marker='o', label='malloc/free')
    plt.plot(df_m['num_allocations'], df_m['duration_my_malloc_free'], marker='o', label='my_malloc/my_free')
    plt.plot(df_m['num_allocations'], df_m['duration_my_malloc_free_basic'], marker='o', label='my_malloc_basic/my_free_basic')
    plt.title(f"Durée en fonction de num_allocations pour des tailles entre 16 et 1024 (méthode {method_val})")
    plt.xlabel('num_allocations')
    plt.ylabel('Durée (µs)')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"plot/methode{method_val}/plot_num_allocations_method_{method_val}.png")
    plt.close()
    
    # Tracer seulement avec my_malloc/my_free et malloc/free
    plt.figure(figsize=(8,6))
    plt.plot(df_m['num_allocations'], df_m['duration_malloc_free'], marker='o', label='malloc/free')
    plt.plot(df_m['num_allocations'], df_m['duration_my_malloc_free'], marker='o', label='my_malloc/my_free')
    plt.title(f"Durée en fonction de num_allocations pour des tailles entre 16 et 1024 (méthode {method_val})")
    plt.xlabel('num_allocations')
    plt.ylabel('Durée (µs)')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"plot/methode{method_val}/plot_num_allocations_method_{method_val}_without_alloc_basic.png")
    plt.close()

# 2) Plot du temps en fonction de la taille max_size pour les méthodes 3 et 4
for method_val in [1, 2, 3]:
    df_m = df_sizes[df_sizes['method'] == method_val]

    plt.figure(figsize=(8,6))
    plt.plot(df_m['max_size'], df_m['duration_malloc_free'], marker='o', label='malloc/free')
    plt.plot(df_m['max_size'], df_m['duration_my_malloc_free'], marker='o', label='my_malloc/my_free')
    plt.plot(df_m['max_size'], df_m['duration_my_malloc_free_basic'], marker='o', label='my_malloc_basic/my_free_basic')
    plt.title(f"Durée en fonction de max_size pour 10000 allocations/déallocations (méthode {method_val})")
    plt.xlabel('max_size')
    plt.ylabel('Durée (µs)')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"plot/methode{method_val}/plot_sizes_method_{method_val}.png")
    plt.close()
    
    # Tracer seulement avec my_malloc/my_free et malloc/free
    
    plt.figure(figsize=(8,6))
    plt.plot(df_m['max_size'], df_m['duration_malloc_free'], marker='o', label='malloc/free')
    plt.plot(df_m['max_size'], df_m['duration_my_malloc_free'], marker='o', label='my_malloc/my_free')
    plt.title(f"Durée en fonction de max_size pour 10000 allocations/déallocations (méthode {method_val})")
    plt.xlabel('max_size')
    plt.ylabel('Durée (µs)')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"plot/methode{method_val}/plot_sizes_method_{method_val}_without_alloc_basic.png")
    plt.close()
    
print("Les plots ont été générés et sauvegardés sous forme de fichiers PNG.")
