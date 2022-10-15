#ifndef OS_2_PROJET_GROUPE_3_COURSE_H
#define OS_2_PROJET_GROUPE_3_COURSE_H
#define DEFAULT_VALUE (-1)
#include "Car.h"
#include "StrUtil.h"

typedef struct Course {
    double bestS1;
    double bestS2;
    double bestS3;
    double bestTurn;

    Car carS1;
    Car carS2;
    Car carS3;
    Car carTurn;
} Course;


Course initCourse();
void beginCourse(Course course, int nbrTurn, Car cars[], int nbrCars);
void strCourse(Course course);

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
            car = makeCarTurn(car);
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
        strCourse(course);
    }
}

/*
 * Affiche les informations de la course en temps réel
 */
void strCourse(Course course) {
    char s1[sizeForTimeToStr(course.bestS1)];
    char s2[sizeForTimeToStr(course.bestS2)];
    char s3[sizeForTimeToStr(course.bestS3)];
    char turn[sizeForTimeToStr(course.bestTurn)];
    timeToStr(s1, course.bestS1);
    timeToStr(s2, course.bestS2);
    timeToStr(s3, course.bestS3);
    timeToStr(turn, course.bestTurn);
    printf("Résumé du tour : %s (%d) | %s (%d) | %s(%d) | %s(%d)\n",
           s1, course.carS1.id, s2, course.carS2.id, s3, course.carS3.id, turn, course.carTurn.id);
}
#undef DEFAULT_VALUE
#endif //OS_2_PROJET_GROUPE_3_COURSE_H
