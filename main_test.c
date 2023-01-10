
#include "lib/Car.h"
#include "lib/Random.h"
#include "lib/Course.h"
#include "lib/SHMUtils.h"
#include "lib/Stockage.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "lib/Championnat.h"

int main(int argc, char* argv[]) {
    registerMainPid(getpid());
    Car cars[] = {
            getCar(44), getCar(63), getCar(1), getCar(11),
            getCar(55), getCar(16), getCar(4), getCar(3),
            getCar(14), getCar(31), getCar(10), getCar(22),
            getCar(5), getCar(18), getCar(6), getCar(23),
            getCar(77), getCar(24), getCar(47), getCar(9)
    };
    const int lenCars = 20;
    char weType[getSize()];
    getWeType(weType);
    // décommenter la fonction pour que le championnat avance
//    deleteFirstLine();


    if (strcmp(weType, "classic") == 0) {
        printf("Week-end classic\n");

        // vendredi matin : séance d'essais libre
        setCourseState(true);
        while (getCourseState()) {
            if (getpid() == getMainPid()) {
                for (int i = 0; i < 10; i++) {
                    sleep(6);

                }
            }
        }

        // supprimer les processus après leurs utilisations
        if (getpid() != getMainPid())
            exit(0);
        exit(0);
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