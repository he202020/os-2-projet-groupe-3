#include "lib/Car.h"
#include "lib/Random.h"
#include "lib/Course.h"
#include "lib/SHMUtils.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    registerMainPid(getpid());
    Car cars[] = {
//            getCar(44), getCar(63), getCar(1), getCar(11),
//            getCar(55), getCar(16), getCar(4), getCar(3),
//            getCar(14), getCar(31), getCar(10), getCar(22),
//            getCar(5), getCar(18), getCar(6), getCar(23),
            getCar(77), getCar(24), getCar(47), getCar(9)};
    int lenCars = 4;
    setCourseState(true);
    createPid(cars, lenCars);


    // Exmple d'une course en très très gros
    if (getpid() == getMainPid()) {
        printf("Ici le main\n");
        sleep(5);
        setCourseState(false);
    } else {
        while (getCourseState()) {
            printf("%d\n", getpid());
            sleep(1);
        }
    }

    printf("Fini pour : %d\n", getpid());
    clearSHM();
}

