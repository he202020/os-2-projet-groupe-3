
#include "lib/Car.h"
#include "lib/Random.h"
#include "lib/RaceUtils.h"
#include "lib/SHMUtils.h"
#include "lib/TimedRace.h"
#include "lib/Stockage.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "lib/Championship.h"
#include "lib/Race.h"

int main(int argc, char* argv[]) {
    clearSHM();
    registerMainPid(getpid());
    Car cars[] = {
            getCar(44), getCar(63), getCar(1), getCar(11),
            getCar(55), getCar(16), getCar(4), getCar(3),
            getCar(14), getCar(31), getCar(10), getCar(22),
            getCar(5), getCar(18), getCar(6), getCar(23),
            getCar(77), getCar(24), getCar(47), getCar(9)
    };
    int lenCars = 20;
    if (access(FILE_POINT, F_OK) == 0) {
        getPoints(cars, lenCars);
    } else {
        storePoints(cars, lenCars);
    }
    insertCarArray(cars, lenCars);
    char weType[getSize() + 10];
    getWeType(weType);
    // décommenter la fonction pour que le championnat avance
    deleteFirstLine();

    if (strcmp(weType, "classic") == 0 || strcmp(weType, "classic\n") == 0) {

        // vendredi matin
        essaisLibre(cars, lenCars, false, "Essai libre - Classic");
        // vendredi après-midi
        essaisLibre(cars, lenCars, false, "Essai libre - Classic");

        // samedi

        essaisLibre(cars, lenCars, false, "Qualification 1 - Classic");
        qsort(cars, lenCars, sizeof(Car), comp);
        lenCars = 15;
        resetTotalTime(cars, lenCars);
        insertCarArray(cars, lenCars);

        essaisLibre(cars, lenCars, false, "Qualification 2 - Classic");
        qsort(cars, lenCars, sizeof(Car), comp);
        lenCars = 10;
        resetTotalTime(cars, lenCars);
        insertCarArray(cars, lenCars);

        essaisLibre(cars, lenCars, false, "Qualification 3 - Classic");
        qsort(cars, lenCars, sizeof(Car), comp);
        lenCars = 20;
        resetTotalTime(cars, lenCars);
        insertCarArray(cars, lenCars);

        // course du dimanche
        essaisLibre(cars, lenCars, true, "Course finale - Classic");
        qsort(cars, lenCars, sizeof(Car), compTotalTime);
        setPoints(cars);
        storePoints(cars, 20);
        classement(cars, 20);
        clearSHM();
    }

    if (strcmp(weType, "special") == 0 || strcmp(weType, "spacial\n") == 0) {
        // vendredi matin
        essaisLibre(cars, lenCars, 0, "Essais libres - Spécial");

        // vendredi après-midi
        Car *cars2 = cars;
        // Q1
        essaisLibre(cars, lenCars, false, "Qualification 1 - Spécial");
        qsort(cars, lenCars, sizeof(Car), comp);
        lenCars = 15;
        resetTotalTime(cars, lenCars);
        insertCarArray(cars, lenCars);

        // Q2
        essaisLibre(cars, lenCars, false, "Qualification 2 - Spécial");
        qsort(cars, lenCars, sizeof(Car), comp);
        lenCars = 10;
        resetTotalTime(cars, lenCars);
        insertCarArray(cars, lenCars);

        // Q3
        essaisLibre(cars, lenCars, false, "Qualification 3 - Spécial");
        qsort(cars, lenCars, sizeof(Car), comp);
        lenCars = 20;
        resetTotalTime(cars, lenCars);
        insertCarArray(cars, lenCars);


        // Samedi matin
        essaisLibre(cars2, 20, false, "Essais libres - Spécial");

        // Samedi après-midi
        resetTotalTime(cars, 20);
        courseSprint(cars, lenCars, 20);
        qsort(cars, lenCars, sizeof(Car), compTotalTime);
        setPoints(cars);
        storePoints(cars, 20);
        classement(cars, 20);
        exit(0);
    }

    classement(cars, 20);
    exit(0);
}