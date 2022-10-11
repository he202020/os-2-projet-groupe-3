#include <stdlib.h>
#include "simon.h"
#include "car.h"

int cars[] = {44, 63, 1, 11, 55, 16, 4, 3, 14, 31, 10, 22, 5, 18, 6, 23, 77, 24, 47, 9};
int length = sizeof(cars)/sizeof(cars[0])

int main() {
    for (int i = 0; i < length; i++) {
        Car car = getCar(cars[i]);
        turn_car(car, 5);
    }
}

/*
 * Résulats :
 * Performances voiture N° 20:
 * - Meilleur temps secteur 1 : 21s
 * - Meilleur temps secteur 2: 33s
 * - Meilleur temps secteur 3: 20s
 * - Meilleur temps d'un tour : 77s
 */