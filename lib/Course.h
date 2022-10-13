#ifndef OS_2_PROJET_GROUPE_3_COURSE_H
#include <stdio.h>
#include "Car.h"
#include "Tours.h"

#define OS_2_PROJET_GROUPE_3_COURSE_H
#define DEFAULT_VALUE -1

typedef struct Course {
    // les meilleurs temps
    double bestS1;
    double bestS2;
    double bestS3;
    double bestTurn;

    // les voitures qui ont fait le meilleur temps
    int carS1;
    int carS2;
    int carS3;
    int carTurn;
} Course;

Course initCourse() {
    Course  course;
    course.bestS1 = DEFAULT_VALUE;
    course.bestS2 = DEFAULT_VALUE;
    course.bestS3 = DEFAULT_VALUE;
    course.bestTurn = DEFAULT_VALUE;
    course.carS1 = DEFAULT_VALUE;
    course.carS2 = DEFAULT_VALUE;
    course.carS3 = DEFAULT_VALUE;
    course.carTurn = DEFAULT_VALUE;
    return course;
}

Course beginCourse(Car cars[], int nbrCars, int nbrTurn) {
    Course course = initCourse();
    if (nbrCars <= 0) {
        printf("Impossibilité de commencer une course avec aucun participant...");
        return course;
    }

    for (int i = 0; i < nbrTurn; i++) {
        for (int j = 0; j < nbrCars; j++) {
            Car car = cars[j];
            makeCarTurn(car);
            if (car.s1 > course.bestS1) {}
        }
    }

}

#undef DEFAULT_VALUE
#endif //OS_2_PROJET_GROUPE_3_COURSE_H
