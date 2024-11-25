# Allocateur Mémoire Personnalisé

Ce projet est une implémentation d'un allocateur mémoire personnalisé en C, utilisant les appels système bas niveau `mmap` et `munmap`. L'objectif est de créer un allocateur fonctionnel, semblable à `malloc` et `free`, tout en explorant les concepts de gestion de mémoire bas niveau.

---

## **Objectifs**

1. Comprendre et manipuler les appels système `mmap` et `munmap`.
2. Implémenter des fonctions d'allocation (`my_malloc`) et de désallocation (`my_free`).
3. Approcher les performances de l'allocateur système en explorant des optimisations.
4. Mettre en place des tests unitaires pour valider le fonctionnement.
