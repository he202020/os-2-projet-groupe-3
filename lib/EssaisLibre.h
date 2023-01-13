//
// Created by moers on 13/01/23.
//

#ifndef OS_2_PROJET_GROUPE_3_ESSAISLIBRE_H
#define OS_2_PROJET_GROUPE_3_ESSAISLIBRE_H
#include "Car.h"

void essaisLibre(Car cars[], int lenCars, bool bonusTime) {
    setCourseState(true);
    createPid(cars, lenCars);

    if (getpid() == getMainPid()) {
        WINDOW *win = display_init();
        Course  course = initCourse();
        int largerOfColumns = 14;
        sleep(2);
        for (int i = 0; i < 10; i++) {

            Car curr_car[lenCars];

            char titlesCars[5][10] = { "Id", "S1", "S2", "S3", "Lap" };
            char titlesCourse[8][10] = {
                    "Best Lap", "Car", "Best S1", "Car", "Best S2", "Car", "Best S3", "Car"
            };
            display_titles(win, titlesCars, largerOfColumns);

            getCarArray(curr_car, lenCars);
            qsort(curr_car, lenCars, sizeof(Car), comp);

            for (int j = 0; j < lenCars; j++) {
                display_data(win, curr_car[j], j + 5, largerOfColumns);
            }
            course = updateCourse(curr_car, lenCars, course);
            display_course_data(win, titlesCourse, course, largerOfColumns);

            wrefresh(win);

            sleep(1);
            //wgetch(win);
        }
        display_end(win);
    } else {
        Car carUpdate[lenCars];
        while (getCourseState()) {
            getCarArray(carUpdate, lenCars);
            for (int i = 0; i < lenCars; ++i) {
                if (cars[i].pid==getpid()) {
                    if (bonusTime) {
                        carUpdate[i] = makeCarTurn(cars[i], i);
                    } else {
                        carUpdate[i] = makeCarTurn(cars[i], 0);
                    }

                    insertCarArray(carUpdate, lenCars);
                }
            }
        }
        exit(0);
    }
}

#endif //OS_2_PROJET_GROUPE_3_ESSAISLIBRE_H
