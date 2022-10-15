#ifndef OS_2_PROJET_GROUPE_3_PRINT_H
#define OS_2_PROJET_GROUPE_3_PRINT_H

#include <stdio.h>
#include "Car.h"
#include "StrUtil.h"
#include "Course.h"

void printCar(Car car);
void printCourse(Course course);

/*
 * Affiche les informations de la voiture en temps réel
 * (temps du tour pas toujours à jour)
 */
void printCar(Car car) {
    char s1[sizeForTimeToStr(car.currentS1)];
    char s2[sizeForTimeToStr(car.currentS2)];
    char s3[sizeForTimeToStr(car.currentS3)];
    char turn[sizeForTimeToStr(getCurrentTurn(car))];
    timeToStr(s1, car.currentS1);
    timeToStr(s2, car.currentS2);
    timeToStr(s3, car.currentS3);
    timeToStr(turn, getCurrentTurn(car));
    printf("%d : %s | %s | %s -- %s\n", car.id, s1, s2, s3, turn);
}

/*
 * Affiche les informations de la course en temps réel
 */
void printCourse(Course course) {
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
#endif //OS_2_PROJET_GROUPE_3_PRINT_H
