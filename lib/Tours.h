#include <stdio.h>
#include "Random.h"
#include "Car.h"
#ifndef OS_2_PROJET_GROUPE_3_TOURS_H
#define OS_2_PROJET_GROUPE_3_TOURS_H
#define MIN_TIME 20
#define MAX_TIME 45


void makeCarTurn(Car car) {
    // cette variable n'est utilisé que pour le test afin de savoir le nombre de tour qu'une voiture va faire
    // une fois que le système de temps sera implémentée, elle pourra être remplacée
    int nbrTurn = 5;

    if (car.number == -1) {
        printf("La voiture n'a pas enregistré son numéro, elle ne peut donc pas participer à la course");
        return; // lorsque le numéro de la voiture n'a pas été désigné
    }
    for (int i = 0; i < nbrTurn; i++) {
        double s1 = getRandom(MIN_TIME, MAX_TIME, car.number);
        double s2 = getRandom(MIN_TIME, MAX_TIME, car.number);
        double s3 = getRandom(MIN_TIME, MAX_TIME, car.number);
        double turnTime = s1 + s2 + s3;

        // vérifie si la voiture a fait un meilleur temps ou si la voiture est à son premier tour (dans ce cas
        // la valeur des temps est égal à CAR_DEFAULT_VALUE
        if (car.bestS1 == CAR_DEFAULT_TIME || s1 < car.bestS1) car.bestS1 = s1;
        if (car.bestS2 == CAR_DEFAULT_TIME || s2 < car.bestS2) car.bestS2 = s2;
        if (car.bestS3 == CAR_DEFAULT_TIME || s3 < car.bestS3) car.bestS3 = s3;
        if (car.bestTurn == CAR_DEFAULT_TIME || turnTime < car.bestTurn) car.bestTurn = turnTime;
    }

    printf("Performances voiture N° %d: \n"
           "- Meilleur temps secteur 1 : %fs\n"
           "- Meilleur temps secteur 2: %fs\n"
           "- Meilleur temps secteur 3: %fs\n"
           "- Meilleur temps d'un tour : %fs\n",
           car.number, car.bestS1, car.bestS2, car.bestS3, car.bestTurn);
    return;
}

#endif //OS_2_PROJET_GROUPE_3_TOURS_H
