#include "lib/Car.h"
#include "lib/Random.h"
#include "lib/Course.h"
#include "lib/SHMUtils.h"
#include "lib/Stockage.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main() {
    registerMainPid(getpid());
    Car cars[] = {
            getCar(44), getCar(63), getCar(1), getCar(11),
            getCar(55), getCar(16), getCar(4), getCar(3),
            getCar(14), getCar(31), getCar(10), getCar(22),
            getCar(5), getCar(18), getCar(6), getCar(23),
            getCar(77), getCar(24), getCar(47), getCar(9)};

    save(cars, 20);
    Car cars2[20];
    load(cars2, 20);
}

