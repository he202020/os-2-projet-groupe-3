#ifndef OS_2_PROJET_GROUPE_3_COURSESPRINT_H
#define OS_2_PROJET_GROUPE_3_COURSESPRINT_H

#include "Car.h"
#include "SHMUtils.h"
#include "Course.h"

void courseSprint(Car cars[], int length, int tour);

void courseSprint(Car cars[], int length, int tour) {
    setFinishedCar(0);
    createPid(cars, length);
    insertCarArray(cars, length);

    if (getMainPid() == getpid()) {
        WINDOW *win = display_init();
        Course  course = initCourse();
        int largerOfColumns = 14;
        sleep(2);
        Car cars2[length];
        int debug = 0;
        while (getFinishedCars() < 19 && debug < 20) {
            getCarArray(cars2, length);
            qsort(cars2, length, sizeof(Car), comp);
            char titlesCars[5][10] = { "Id", "S1", "S2", "S3", "Lap" };
            char titlesCourse[8][10] = {
                    "Best Lap", "Car", "Best S1", "Car", "Best S2", "Car", "Best S3", "Car"
            };
            display_titles(win, titlesCars, largerOfColumns);
            for (int i = 0; i < length; i++) {
                display_data(win, cars2[i], i + 7, largerOfColumns);
            }
            course = updateCourse(cars2, length, course);
            display_course_data(win, titlesCourse, course, largerOfColumns,
                                "Course Sprint - Spécial");
            wrefresh(win);
            debug++;
            sleep(1);
        }
        display_end(win);
        getCarArray(cars, length);
    } else {
        int index;
        for (int i = 0; i < length; i++) {
            if (getpid() == cars [i].pid) {
                index = i;
                break;
            }
        }
        for (int i = 0; i < tour; i++) {
            getCarArray(cars, length);
            cars[index] = makeCarTurn(cars[index], index);
            insertCarArray(cars, length);
            sleep(1);
        }
        setFinishedCar(getFinishedCars() + 1);
        exit(0);
    }
}

#endif //OS_2_PROJET_GROUPE_3_COURSESPRINT_H
