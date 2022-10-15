#ifndef OS_2_PROJET_GROUPE_3_COURSE_H
#define OS_2_PROJET_GROUPE_3_COURSE_H
#define DEFAULT_VALUE -1

typedef struct Course {
    // les meilleurs temps
    double bestS1;
    double bestS2;
    double bestS3;
    double bestTurn;

    // les voitures qui ont fait le meilleur temps
    Car carS1;
    Car carS2;
    Car carS3;
    Car carTurn;
} Course;

#include <stdio.h>
#include "Car.h"
#include "Tours.h"
#include "Print.h"

Course initCourse();
void beginCourse(Course course, int nbrTurn, Car cars[], int nbrCars);

Course initCourse() {
    Course course;
    course.bestS1 = DEFAULT_VALUE;
    course.bestS2 = DEFAULT_VALUE;
    course.bestS3 = DEFAULT_VALUE;
    course.bestTurn = DEFAULT_VALUE;
    return course;
}

void beginCourse(Course course, int nbrTurn, Car cars[], int nbrCars) {
    if (nbrCars <= 0) {
        printf("Impossibilité de commencer une course sans participant...");
        return;
    }

    for (int i = 0; i < nbrTurn; i++) {
        for (int j = 0; j < nbrCars; j++) {
            Car car = cars[j];
            makeCarTurn(car);
            if (car.currentS1 < course.bestS1 || course.bestS1 == DEFAULT_VALUE) {
                course.bestS1 = car.currentS1;
                course.carS1 = car;
            }
            if (car.currentS2 < course.bestS2 || course.bestS2 == DEFAULT_VALUE) {
                course.bestS2 = car.currentS2;
                course.carS3 = car;
            }
            if (car.currentS3 < course.bestS3 || course.bestS3 == DEFAULT_VALUE) {
                course.bestS3 = car.currentS3;
                course.carS3 = car;
            }
            if (getCurrentTurn(car) < course.bestTurn || course.bestTurn == DEFAULT_VALUE) {
                course.bestTurn = getCurrentTurn(car);
                course.carTurn = car;
            }
        }
        printCourse(course);
    }
}

#undef DEFAULT_VALUE
#endif //OS_2_PROJET_GROUPE_3_COURSE_H
