
#include "lib/Car.h"
#include "lib/Random.h"
#include "lib/Course.h"
#include "lib/SHMUtils.h"
#include "lib/EssaisLibre.h"
#include "lib/Stockage.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "lib/Championnat.h"

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
    char weType[getSize()];
    getWeType(weType);
    // décommenter la fonction pour que le championnat avance
//    deleteFirstLine();


    if (strcmp(weType, "classic") == 0) {

        // vendredi matin
        essaisLibre(cars, lenCars, false, "Essai libre");
        printf("ici\n");
        // vendredi après-midi
        essaisLibre(cars, lenCars, false, "Essai libre");

        // samedi

        essaisLibre(cars, lenCars, false, "Qualification 1");
        qsort(cars, lenCars, sizeof(Car), comp);
        lenCars = 15;
        resetTotalTime(cars, lenCars);
        insertCarArray(cars, lenCars);

        essaisLibre(cars, lenCars, false, "Qualification 2");
        qsort(cars, lenCars, sizeof(Car), comp);
        lenCars = 10;
        resetTotalTime(cars, lenCars);
        insertCarArray(cars, lenCars);

        essaisLibre(cars, lenCars, false, "Qualification 3");
        qsort(cars, lenCars, sizeof(Car), comp);
        lenCars = 20;
        resetTotalTime(cars, lenCars);
        insertCarArray(cars, lenCars);

        // course du dimanche
        essaisLibre(cars, lenCars, true, "Course finale");
        qsort(cars, lenCars, sizeof(Car), compTotalTime);
        cars[0].point += 25;
        cars[1].point += 20;
        cars[2].point += 15;
        cars[3].point += 10;
        cars[4].point += 8;
        cars[5].point += 6;
        cars[6].point += 5;
        cars[7].point += 3;
        cars[8].point += 2;
        cars[9].point += 1;
        storePoints(cars, 20);
        insertCarArray(cars, 20);

        clearSHM();
    }

    if (strcmp(weType, "special") == 0 ) {
        printf("Week-end spécial\n");
        exit(0);
    }

    printf("Plus de week-end\n");
    exit(0);




    setCourseState(true);
    createPid(cars, lenCars);
    if (getpid() == getMainPid()) {
        printf("Ici le main\n");
        Course course1 = initCourse();
        beginCourse(course1, 3, cars, 4);
        setCourseState(false);
    } else {
        while (getCourseState()) {
            //printf("%d\n", getpid());
            //sleep(1);
        }
    }
    clearSHM();
}