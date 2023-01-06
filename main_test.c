
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
    //deleteFirstLine();
    registerMainPid(getpid());
    Car cars[] = {getCar(77), getCar(24), getCar(47), getCar(9)};
    const int lenCars = 4;
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