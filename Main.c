#include <stdlib.h>
#include "lib/Tours.h"
#include "lib/Car.h"
#include "lib/StrUtil.h"
#include <stdbool.h>
#include "lib/Random.h"
#include "lib/Course.h"

int main() {
    Car cars[] = {
//            getCar(44), getCar(63), getCar(1), getCar(11),
//            getCar(55), getCar(16), getCar(4), getCar(3),
//            getCar(14), getCar(31), getCar(10), getCar(22),
//            getCar(5), getCar(18), getCar(6), getCar(23),
            getCar(77), getCar(24), getCar(47), getCar(9)};

    Course course = initCourse();
    beginCourse(course, 1, cars, 4);
}