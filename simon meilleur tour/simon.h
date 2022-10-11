/*But: afficher le temps de chaque secteur pour X voitures et le meilleur temps (comparé au precedent a chaques tours) */
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "car.h"
#ifndef OS_2_PROJET_GROUPE_3_RANDOM_H
#define OS_2_PROJET_GROUPE_3_RANDOM_H
#define MIN_TIME 20
#define MAX_TIME 45

#endif //OS_2_PROJET_GROUPE_3_RANDOM_H
//Nombre "aléatoire"
double getRandom(int min, int max, int seed) {
    min *= 1000;
    max *= 1000;
    srand((rand() % time(0)) * seed);
    double random = rand() % ((max + 1) - min) + min;
    return random / 1000;
}

//random S1 S2 S3 et tour pour une voiture sur X tours
void turn_car(Car car,int nbrTurn){

    double bestTime = 0;
    for (int i = 0; i < nbrTurn; i++) {
        double s1 = getRandom(MIN_TIME, MAX_TIME, car.number);
        double s2 = getRandom(MIN_TIME, MAX_TIME, car.number);
        double s3 = getRandom(MIN_TIME, MAX_TIME, car.number);
        double turnTime = s1 + s2 + s3;

        if (turnTime < bestTime || bestTime == 0){
            bestTime = turnTime;
        }

        car.S1 = s1;
        car.S2 = s2;
        car.S3 = s3;
        car.Turn = turnTime;
        car.bestTurn = bestTime;

        printf("Performances voiture N° %d: \n"
           "- temps secteur 1 : %fs\n"
           "- temps secteur 2: %fs\n"
           "- temps secteur 3: %fs\n"
           "- temps d'un tour : %fs\n"
           "- meilleur temps d'un tour : %fs\n",
           car.number, car.S1, car.S2, car.S3, car.Turn, car.bestTurn);
        fflush(stdout);
        sleep(1);
  }
}

