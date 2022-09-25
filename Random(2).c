#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getRandom(int min, int max, int seed) {
    /*
     * La seed est un nombre qui permet de définir l'aléatoire
     * Elle est utilisée pour éviter que 2 nombres généré en même temps soient les mêmes
     * Et time(NULL) est utilisé pour éviter que 2 nombres avec la même seed soient les mêmes
     * La seed serait le numéro de la voiture ou encore le pid du processus
     *
     * Min et max représentent les valeurs à ne pas dépasser pour le nombre à générer
     */

    srand((rand() % seed) * time(0));
    int random = rand() % ((max + 1) - min) + min;
    return random;
}

int main() {
    /*
     * Exemple d'utilisation avec 2 seed différentes (à chaque fois 3 nombres sont générés par seed)
     */
    int min = 20;
    int max = 45;
    int seed = 50;
    for (int i = 0; i < 3; i++) {
        printf("seed : %d -> nombre généré :  %d\n", seed,  getRandom(min, max, seed));
    }

    seed = 45;
    for (int i = 0; i < 3; i++) {
        printf("seed : %d -> nombre généré :  %d\n", seed,  getRandom(min, max, seed));
    }
    return 0;
}

/*
 * Résultats lors des tests :
 * seed : 50 -> nombre généré :  29
 * seed : 50 -> nombre généré :  32
 * seed : 50 -> nombre généré :  36
 *
 * seed : 45 -> nombre généré :  31
 * seed : 45 -> nombre généré :  20
 * seed : 45 -> nombre généré :  28
 */

