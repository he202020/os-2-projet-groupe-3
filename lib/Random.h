#ifndef OS_2_PROJET_GROUPE_3_RANDOM_H
#define OS_2_PROJET_GROUPE_3_RANDOM_H
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

double getRandom(int min, int max, int seed);


/*
 * La seed est un nombre qui permet de définir l'aléatoire
 * Elle est utilisée pour éviter que 2 nombres généré en même temps soient les mêmes
 * Et time(NULL) est utilisé pour éviter que 2 nombres avec la même seed soient les mêmes
 * La seed serait le numéro de la voiture ou encore le pid du processus
 *
 * Min et max représentent les valeurs à ne pas dépasser pour le nombre à générer
 */
double getRandom(int min, int max, int seed) {
    min *= 1000;
    max *= 1000;
    srand((rand() % time(0)) * seed);
    double random = rand() % ((max + 1) - min) + min;
    return random / 1000;
}
#endif //OS_2_PROJET_GROUPE_3_RANDOM_H