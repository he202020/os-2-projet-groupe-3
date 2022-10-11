#include <stdlib.h>
#include "simon.h"
#include "car.h"

int main() {
    Car car = getCar(20);
    turn_car(car, 5);
}

/*
 * Résulats :
 * Performances voiture N° 20:
 * - Meilleur temps secteur 1 : 21s
 * - Meilleur temps secteur 2: 33s
 * - Meilleur temps secteur 3: 20s
 * - Meilleur temps d'un tour : 77s
 */