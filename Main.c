#include <stdlib.h>
//#include "lib/Tours.h"
//#include "lib/Car.h"
#include "lib/StrUtil.h"
#include <stdbool.h>
#include "lib/Random.h"

int main() {
//    Car cars[] = {
//            getCar(44), getCar(63), getCar(1), getCar(11),
//            getCar(55), getCar(16), getCar(4), getCar(3),
//            getCar(14), getCar(31), getCar(10), getCar(22),
//            getCar(5), getCar(18), getCar(6), getCar(23),
//            getCar(77), getCar(24), getCar(47), getCar(9)};

    char buffer[20];
    double rd = getRandom(100, 1000, 54);
    printf("%f\n", rd);
    timeToStr(buffer, rd);
    printf("%s\n", buffer);

}

/*
 * Résulats :
 * Performances voiture N° 20:
 * - Meilleur temps secteur 1 : 21s
 * - Meilleur temps secteur 2: 33s
 * - Meilleur temps secteur 3: 20s
 * - Meilleur temps d'un tour : 77s
 */