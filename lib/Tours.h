#ifndef OS_2_PROJET_GROUPE_3_TOURS_H
#define OS_2_PROJET_GROUPE_3_TOURS_H

#include <stdio.h>
#include "Random.h"
#include "Car.h"
#include "Course.h"
#define MIN_TIME 20
#define MAX_TIME 45

void makeCarTurn(Car car);

void makeCarTurn(Car car) {
    if (car.id == -1) {
        printf("La voiture n'a pas enregistré son numéro, elle ne peut donc pas participer à la course");
        return; // lorsque le numéro de la voiture n'a pas été désigné
    }
    car.currentS1 = getRandom(MIN_TIME, MAX_TIME, car.id);
    printCar(car);
    car.currentS2 = getRandom(MIN_TIME, MAX_TIME, car.id);
    printCar(car);
    car.currentS3 = getRandom(MIN_TIME, MAX_TIME, car.id);
    printCar(car);
    return;
}

#undef MIN_TIME
#undef MAX_TIME
#endif //OS_2_PROJET_GROUPE_3_TOURS_H
