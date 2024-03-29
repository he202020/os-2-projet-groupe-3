#ifndef OS_2_PROJET_GROUPE_3_COURSE_H
#define OS_2_PROJET_GROUPE_3_COURSE_H
#define DEFAULT_VALUE (-1)
#include "Car.h"
#include "StrUtil.h"
#include "Displayer.h"
#include "unistd.h"
#include "SHMUtils.h"
#include <stdio.h>

typedef struct Course {
    double bestS1;
    double bestS2;
    double bestS3;
    double bestLap;

    Car carS1;
    Car carS2;
    Car carS3;
    Car carLap;
} Course;

void display_course_data(WINDOW *win, char list0fTitles[8][10], Course course, int colLg, char raceType[]);
Course initCourse();
void beginCourse(Course course, int nbrTurn, Car cars[], int nbrCars);
void beginTimedCourse(Course course, int time, Car cars[], int length);
void strCourse(Course course);

void display_course_data(WINDOW *win, char list0fTitles[8][10], Course course, int colLg, char raceType[]) {
    char s1[sizeForTimeToStr(course.bestS1)];
    char s2[sizeForTimeToStr(course.bestS2)];
    char s3[sizeForTimeToStr(course.bestS3)];
    char lap[sizeForTimeToStr(course.bestLap)];
    timeToStr(s1, course.bestS1);
    timeToStr(s2, course.bestS2);
    timeToStr(s3, course.bestS3);
    timeToStr(lap, course.bestLap);

    char bestLapCar[20];
    char bestS1Car[20];
    char bestS2Car[20];
    char bestS3Car[20];
    sprintf(bestLapCar, "%d", course.carLap.id);
    sprintf(bestS1Car, "%d", course.carS1.id);
    sprintf(bestS2Car, "%d", course.carS2.id);
    sprintf(bestS3Car, "%d", course.carS3.id);

    mvwprintw(win, 1, 1, "%s", raceType);

    int startCol = 1;
    for (int i = 0; i < 8; ++i) {
        mvwprintw(win, 3, startCol, "%s", list0fTitles[i]);
        startCol += colLg;
    }
    startCol = 1;
    mvwprintw(win, 4, startCol, "%s", lap);
    startCol += colLg;
    mvwprintw(win, 4, startCol, "%s", bestLapCar);
    startCol += colLg;
    mvwprintw(win, 4, startCol, "%s", s1);
    startCol += colLg;
    mvwprintw(win, 4, startCol, "%s", bestS1Car);
    startCol += colLg;
    mvwprintw(win, 4, startCol, "%s", s2);
    startCol += colLg;
    mvwprintw(win, 4, startCol, "%s", bestS2Car);
    startCol += colLg;
    mvwprintw(win, 4, startCol, "%s", s3);
    startCol += colLg;
    mvwprintw(win, 4, startCol, "%s", bestS3Car);
}

Course initCourse() {
    Course course;
    course.bestS1 = DEFAULT_VALUE;
    course.bestS2 = DEFAULT_VALUE;
    course.bestS3 = DEFAULT_VALUE;
    course.bestLap = DEFAULT_VALUE;
    return course;
}

void beginCourse(Course course, int nbrTurn, Car cars[], int nbrCars) {
    if (nbrCars <= 0) {
        printf("Impossibilité de commencer une course sans participant...");
        return;
    }


    for (int i = 0; i < nbrTurn; i++) {

        createPid(cars, nbrCars);
        if (getpid() == getMainPid()) {

        }
        WINDOW *win = display_init();

        char titlesCars[5][10] = { "Id", "S1", "S2", "S3", "Lap" };
        char titlesCourse[8][10] = {
                "Best Lap", "Car", "Best S1", "Car", "Best S2", "Car", "Best S3", "Car"
        };

        int largerOfColumns = 14;

        display_titles(win, titlesCars, largerOfColumns);

        int currRow = 5;
        for (int j = 0; j < nbrCars; j++) {
            Car car = cars[j];
            car = makeCarTurn(car, 0);
            if (car.currentS1 < course.bestS1 || course.bestS1 == DEFAULT_VALUE) {
                course.bestS1 = car.currentS1;
                course.carS1 = car;
            }
            if (car.currentS2 < course.bestS2 || course.bestS2 == DEFAULT_VALUE) {
                course.bestS2 = car.currentS2;
                course.carS2 = car;
            }
            if (car.currentS3 < course.bestS3 || course.bestS3 == DEFAULT_VALUE) {
                course.bestS3 = car.currentS3;
                course.carS3 = car;
            }
            if (getCurrentTurn(car) < course.bestLap || course.bestLap == DEFAULT_VALUE) {
                course.bestLap = getCurrentTurn(car);
                course.carLap = car;
            }
            display_data(win, car, currRow, largerOfColumns);
            currRow += 1;
        }
        display_course_data(win, titlesCourse, course, largerOfColumns, "zizi");
        wrefresh(win);
        //sleep(1);
        display_end(win);
        //strCourse(course);
    }
}

/*
 * Affiche les informations de la course en temps réel
 */
void strCourse(Course course) {
    char s1[sizeForTimeToStr(course.bestS1)];
    char s2[sizeForTimeToStr(course.bestS2)];
    char s3[sizeForTimeToStr(course.bestS3)];
    char lap[sizeForTimeToStr(course.bestLap)];
    timeToStr(s1, course.bestS1);
    timeToStr(s2, course.bestS2);
    timeToStr(s3, course.bestS3);
    timeToStr(lap, course.bestLap);
    printf("Résumé du tour : %s (%d) | %s (%d) | %s(%d) | %s(%d)\n",
           s1, course.carS1.id, s2, course.carS2.id, s3, course.carS3.id, lap, course.carLap.id);
}

Course updateCourse(Car *cars, int length, Course course) {
    for (int i = 0; i < length; i++) {
        Car car = cars[i];
        if (car.currentS1 < course.bestS1 || course.bestS1 == -1) {
            course.bestS1 = car.currentS1;
            course.carS1 = car;
        }
        if (car.currentS2 < course.bestS2 || course.bestS2 == -1) {
            course.bestS2 = car.currentS2;
            course.carS2 = car;
        }
        if (car.currentS3 < course.bestS3 || course.bestS3 == -1) {
            course.bestS3 = car.currentS3;
            course.carS3 = car;
        }
        double lap = car.currentS1 + car.currentS2 + car.currentS3;
        if (lap < course.bestLap || course.bestLap < 0) {
            course.bestLap = lap;
            course.carLap = cars[i];
        }

        return course;
    }
}

void resetTotalTime(Car cars[], int length) {
    for (int i = 0; i < length; i++)
        cars[i].totalTime = 0;
}
#undef DEFAULT_VALUE
#endif //OS_2_PROJET_GROUPE_3_COURSE_H
