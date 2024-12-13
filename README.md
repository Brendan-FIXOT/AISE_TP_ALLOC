# README - Projet Allocateur Mémoire

## **Instructions de Compilation et d'Exécution**

### **Compilation**

Pour compiler le projet, assurez-vous d'avoir **CMake** et **Make** installés sur votre système.

1. **Créez le répertoire de construction**

   ```bash
   mkdir build && cd build
   ```

2. **Générez les fichiers de construction avec CMake**

   ```bash
   cmake ..
   ```

3. **Compilez le projet**

   ```bash
   make
   ```

> **Remarque** : La compilation générera deux exécutables principaux :

- **ALLOC\_TEST** : Exécute les tests unitaires de l'allocateur.
- **BENCHMARK** : Lance les benchmarks pour comparer les performances de l'allocateur personnalisé avec malloc/free.

---

### **Exécution**

1. **Exécution des tests**

   ```bash
   make test
   ```

2. **Exécution des benchmarks**

   ```bash
   ./BENCHMARK
   ```

3. **Exécution des benchmarks avec gprof**

   ```bash
   make benchmark_gprof
   ```

4. **Génération des plots** (nécessite Python et les bibliothèques `pandas` et `matplotlib`)

   Pour générer les plots (si besoin), il est nécessaire de se déplacer dans le dossier ploting/ et d’exécuter manuellement le programme Python plot.py de la manière suivante

   ```bash
   cd ploting/
   python3 plot.py
   ```

5. **Nettoyage des fichiers de données et des plots**

   - **Nettoyer les données** :
     ```bash
     make clean_data
     ```
   - **Nettoyer les plots** :
     ```bash
     make clean_plot
     ```

6. **Reconfiguration du projet**

   ```bash
   make recmake
   ```

---

## **Choix d’Implémentation**

### **1. Structure Générale**

Le programme est organisé de manière modulaire pour assurer la clarté et la facilité de maintenance. Voici les différentes parties qui composent l'implémentation :

- **Fichiers source principaux** :
  - `myAllocator.cpp` et `myAllocator.h` : Contiennent la logique d'allocation, la gestion des blocs libres et les optimisations.
  - `myAllocatorBasic.cpp` et `myAllocatorBasic.h` : Contiennent l'implémentation basique initiale de l'allocateur, permettant de comparer l'avancée des optimisations par rapport à la version de base.
  - `benchmark.cpp` et `benchmark.h` : Contiennent les fonctions permettant d'exécuter des benchmarks pour comparer les performances de l'allocateur à celles de malloc/free.
  - `main_bench.cpp` : Lance l'exécution des benchmarks et enregistre les résultats dans des fichiers CSV.
  - `test.cpp` : Contient les tests unitaires permettant de valider le bon fonctionnement de l'allocateur.

- **Structure des répertoires** :
  - `myAllocator/` : Contient les fichiers sources et d'en-tête relatifs à l'allocateur optimisé.
  - `myAllocatorBasic/` : Contient les fichiers de l'implémentation de l'allocateur de base.
  - `benchmark/` : Contient les fichiers de benchmark et les scripts associés.
  - `ploting/` : Contient le script Python pour générer des plots, ainsi que les fichiers CSV et images de sortie.

### **2. Gestion des Blocs**

- **Alignement des tailles** : Les tailles sont alignées à des puissances de 2.
- **Classes de tailles** : Les tailles sont classées en **16, 32, 64, 128, etc.** jusqu'à une taille maximale prédéfinie.
- **Listes chaînées de blocs libres** : Chaque classe de taille a une liste de blocs libres.
- **Verrouillage par mutex** : Chaque liste est protégée par un mutex **pthread**.

### **3. Mécanisme de Recherche de Bloc**

- **Best-Fit** : Recherche du bloc libre le plus proche de la taille demandée.

### **4. Fusion de Blocs Libres (Coalescence)**

- Les blocs adjacents sont fusionnés pour réduire la fragmentation.

### **5. Nettoyage des Listes**

- Lorsqu’une liste contient trop de blocs libres, certains sont renvoyés au système via `munmap`.

---

## **Optimisations Réalisées**

### 1. **Segmentation en Classes de Tailles**

- Chaque classe de taille a sa propre liste de blocs libres.
- Cette méthode évite de trop fragmenter la mémoire et réduit le nombre d’appels à `mmap`.

### 2. **Recyclage des Blocs Libérés**

- Les blocs libérés sont réinsérés dans la liste de la classe de tailles correspondante.

### 3. **Best-Fit Allocation**

- Les blocs de la liste chaînée sont parcourus pour trouver le meilleur ajustement possible.

### 4. **Verrouillage Multi-thread**

- Chaque classe de taille dispose d’un mutex indépendant pour limiter la contention multi-thread.

### 5. **Coalescence des Blocs**

- Les blocs adjacents sont fusionnés, réduisant la fragmentation externe.

---

## **Résultats des Benchmarks**

Les benchmarks ont été réalisés sur plusieurs scénarios pour comparer les performances de l'allocateur personnalisé avec **malloc/free**.

### 1. **Temps d'allocation en fonction du nombre d'allocations**

#### Méthode 1

| Nombre d'allocations | malloc/free (µs) | my_malloc (µs) | my_malloc_basic (µs) |
| -------------------- | ------------------ | ----------------- | ------------------------ |
| 1000                 | 234.2              | 7197              | 2363.5                   |
| 5000                 | 1746.8             | 42274             | 11865.6                  |
| 10000                | 3542.3             | 104405            | 26290                    |
| 20000                | 7898.5             | 202424            | 50805.5                  |
| 50000                | 19142.6            | 517830            | 124658                   |

| Nombre d'allocations | malloc/free (op/s) | my_malloc (op/s) | my_malloc_basic (op/s) |
| -------------------- | ------------------ | ---------------- | ----------------------- |
| 1000                 | 426985             | 13894.7          | 42310.1                 |
| 5000                 | 286238             | 11827.6          | 42138.6                 |
| 10000                | 282302             | 9578.09          | 38037.3                 |
| 20000                | 253213             | 9880.25          | 39365.8                 |
| 50000                | 261198             | 9655.69          | 40109.8                 |

#### Méthode 2

| Nombre d'allocations | malloc/free (µs) | my_malloc (µs) | my_malloc_basic (µs) |
| -------------------- | ------------------ | ----------------- | ------------------------ |
| 1000                 | 58.1               | 56.8              | 2172.2                   |
| 5000                 | 297.2              | 323.1             | 10381.6                  |
| 10000                | 610                | 611.5             | 22042.4                  |
| 20000                | 1164.1             | 1215.9            | 44019.7                  |
| 50000                | 2848.6             | 2891.6            | 103860                   |

| Nombre d'allocations | malloc/free (op/s) | my_malloc (op/s) | my_malloc_basic (op/s) |
| -------------------- | ------------------ | ---------------- | ----------------------- |
| 1000                 | 1721170            | 1760560          | 46036.3                 |
| 5000                 | 1682370            | 1547510          | 48162.1                 |
| 10000                | 1639340            | 1635320          | 45367.1                 |
| 20000                | 1718070            | 1644870          | 45434.2                 |
| 50000                | 1755250            | 1729150          | 48141.9                 |

#### Méthode 3

| Nombre d'allocations | malloc/free (µs) | my_malloc (µs) | my_malloc_basic (µs) |
| -------------------- | ------------------ | ----------------- | ------------------------ |
| 1000                 | 216.3              | 195.4             | 2764.6                   |
| 5000                 | 1232.9             | 793.2             | 13524.6                  |
| 10000                | 3088.2             | 1796.9            | 31810                    |
| 20000                | 9498.2             | 3464.3            | 68024.2                  |
| 50000                | 30716.3            | 7981              | 165150                   |

| Nombre d'allocations | malloc/free (op/s) | my_malloc (op/s) | my_malloc_basic (op/s) |
| -------------------- | ------------------ | ---------------- | ----------------------- |
| 1000                 | 462321             | 511771            | 36171.6                 |
| 5000                 | 405548             | 630358            | 36969.7                 |
| 10000                | 323813             | 556514            | 31436.7                 |
| 20000                | 210566             | 577317            | 29401.3                 |
| 50000                | 162780             | 626488            | 30275.4                 |

### 2. **Temps d'allocation en fonction de la taille maximale des allocations**

#### Méthode 1

| Taille max (octets) | malloc/free (µs) | my_malloc (µs) | my_malloc_basic (µs) |
|--------------------|---------------------|-------------------|--------------------------|
| 64                 | 1499.2              | 91266.8           | 25292.3                  |
| 128                | 1615                | 90238.8           | 216556                   |
| 256                | 1555.5              | 86327.7           | 23401.6                  |
| 512                | 1684.3              | 87480.4           | 23481.3                  |
| 1024               | 1804.6              | 86435.9           | 23887.1                  |
| 2048               | 2337.2              | 93144.9           | 24154.3                  |

| Taille max (octets) | malloc/free (ops/sec) | my_malloc (ops/sec) | my_malloc_basic (ops/sec) |
|--------------------|-----------------------|---------------------|----------------------------|
| 64                 | 667022                 | 10956.9             | 39537.7                    |
| 128                | 619195                 | 11081.7             | 4617.75                    |
| 256                | 642880                 | 11583.8             | 42732.1                    |
| 512                | 593718                 | 11431.1             | 42587.1                    |
| 1024               | 554139                 | 11569.3             | 41863.6                    |
| 2048               | 427862                 | 10736               | 41400.5                    |

#### Méthode 2

| Taille max (octets) | malloc/free (µs) | my_malloc (µs) | my_malloc_basic (µs) |
|--------------------|---------------------|-------------------|--------------------------|
| 64                 | 575.8               | 569.8             | 21931.7                  |
| 128                | 579.8               | 602.9             | 20430.4                  |
| 256                | 642.1               | 584.4             | 20375.5                  |
| 512                | 626.1               | 640.4             | 20763.3                  |
| 1024               | 590.6               | 638               | 20406.7                  |
| 2048               | 976.8               | 923.1             | 21159.5                  |

| Taille max (octets) | malloc/free (ops/sec) | my_malloc (ops/sec) | my_malloc_basic (ops/sec) |
|--------------------|-----------------------|---------------------|----------------------------|
| 64                 | 1736710                | 1755000             | 45596.1                    |
| 128                | 1724730                | 1658650             | 48946.7                    |
| 256                | 1557390                | 1711160             | 49078.6                    |
| 512                | 1597190                | 1561520             | 48161.9                    |
| 1024               | 1693190                | 1567400             | 49003.5                    |
| 2048               | 1023750                | 1083310             | 47260.1                    |

#### Méthode 3

| Taille max (octets) | malloc/free (µs) | my_malloc (µs) | my_malloc_basic (µs) |
|--------------------|---------------------|-------------------|--------------------------|
| 64                 | 2350.5              | 1468.2            | 28387.3                  |
| 128                | 2086.5              | 1373.5            | 26529.8                  |
| 256                | 2213.7              | 1352.2            | 26510                    |
| 512                | 2387.1              | 1495.2            | 26423.6                  |
| 1024               | 2546                | 1539.7            | 26251.7                  |
| 2048               | 3094.9              | 1713              | 27495                    |

| Taille max (octets) | malloc/free (ops/sec) | my_malloc (ops/sec) | my_malloc_basic (ops/sec) |
|--------------------|-----------------------|---------------------|----------------------------|
| 64                 | 425441                 | 681106              | 35227                      |
| 128                | 479272                 | 728067              | 37693.5                    |
| 256                | 451732                 | 739536              | 37721.6                    |
| 512                | 418918                 | 668807              | 37845                      |
| 1024               | 392773                 | 649477              | 38092.8                    |
| 2048               | 323112                 | 583771              | 36370.2                    |
