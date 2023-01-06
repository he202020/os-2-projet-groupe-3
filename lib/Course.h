#ifndef OS_2_PROJET_GROUPE_3_COURSE_H
#define OS_2_PROJET_GROUPE_3_COURSE_H
#define DEFAULT_VALUE (-1)
#include "Car.h"
#include "StrUtil.h"
#include "Displayer.h"
#include "unistd.h"
#include "stdio.h"

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

void display_course_data(WINDOW *win, char list0fTitles[8][10], Course course, int colLg);
Course initCourse();
void beginCourse(Course course, int nbrTurn, Car cars[], int nbrCars);
void strCourse(Course course);

void display_course_data(WINDOW *win, char list0fTitles[8][10], Course course, int colLg) {
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

    int startCol = 1;
    for (int i = 0; i < 8; ++i) {
        mvwprintw(win, 1, startCol, list0fTitles[i]);
        startCol += colLg;
    }
    startCol = 1;
    mvwprintw(win, 2, startCol, lap);
    startCol += colLg;
    mvwprintw(win, 2, startCol, bestLapCar);
    startCol += colLg;
    mvwprintw(win, 2, startCol, s1);
    startCol += colLg;
    mvwprintw(win, 2, startCol, bestS1Car);
    startCol += colLg;
    mvwprintw(win, 2, startCol, s2);
    startCol += colLg;
    mvwprintw(win, 2, startCol, bestS2Car);
    startCol += colLg;
    mvwprintw(win, 2, startCol, s3);
    startCol += colLg;
    mvwprintw(win, 2, startCol, bestS3Car);
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
            car = makeCarTurn(car);
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
        display_course_data(win, titlesCourse, course, largerOfColumns);
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
#undef DEFAULT_VALUE
#endif //OS_2_PROJET_GROUPE_3_COURSE_H
