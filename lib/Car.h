#ifndef OS_2_PROJET_GROUPE_3_CAR_H
#define OS_2_PROJET_GROUPE_3_CAR_H
#define CAR_DEFAULT_TIME (-1)
#define MIN_TIME 20
#define MAX_TIME 45
#define TIME_AT_STAND 10
#define FILE_POINT "points"
#include "Random.h"
#include "StrUtil.h"
#include <sys/stat.h>

typedef struct Car {
    int id; // numéro de la voiture
    int pid;
    struct Car* smAddr;
    int point;

    double currentS1;
    double currentS2;
    double currentS3;
    double totalTime;

    int usure;
} Car;

Car getCar(int id);
double getCurrentTurn(Car car);
Car makeCarTurn(Car car, int bonusTime);
void strCar(Car car);
bool isAtStand(Car car);
void sortByLap(Car cars[], int length);
int comp(const void * a, const void *b);
int compTotalTime(const void * a, const void *b);

/*
 * Génération d'une voiture de base
 * Permet de définir les valeurs par défaut de la voiture et éviter des erreurs
 */
Car getCar(int id) {
    Car car;
    car.id = id;
    car.smAddr = NULL;
    car.pid = CAR_DEFAULT_TIME;
    car.currentS1 = CAR_DEFAULT_TIME;
    car.currentS2 = CAR_DEFAULT_TIME;
    car.currentS3 = CAR_DEFAULT_TIME;
    car.usure = 100;
    car.point = 0;
    car.totalTime = 0;

    return car;
}

/*
 * Renvoi le temps actuel du tour de la voiture
 */
double getCurrentTurn(Car car) {
    return car.currentS1 + car.currentS2 + car.currentS3;
}

Car makeCarTurn(Car car, int bonusTime) {
    car.currentS1 = getRandom(MIN_TIME, MAX_TIME, car.id);
    if (isAtStand(car))
        car.currentS1 += TIME_AT_STAND;
    car.currentS2 = getRandom(MIN_TIME, MAX_TIME, car.id);
    if (isAtStand(car))
        car.currentS2 += TIME_AT_STAND;
    car.currentS3 = getRandom(MIN_TIME, MAX_TIME, car.id);
    if (isAtStand(car))
        car.currentS3 += TIME_AT_STAND;
    car.totalTime += car.currentS1 + car.currentS2 + car.currentS3 + bonusTime;
    return car;
}

/*
 * Affiche les informations de la voiture en temps réel
 * (temps du tour pas toujours à jour)
 */
void strCar(Car car) {
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
 * Défini si une voiture va au stand ou pas.
 * Si elle va au stand, son usure est réinitialisée
 * sinon elle est incrémentée.
 */
bool isAtStand(Car car) {
    double stand = getRandom(0, 100, car.id);
    if (stand > car.usure) {
        car.usure = 0;
        return true;
    }
    car.usure += 3;
    return false;
}

int comp(const void * a, const void * b) {
    Car car1 = *((Car *) a);
    Car car2 = *((Car *) b);
    double lap1 = car1.currentS1 + car1.currentS2 + car1.currentS3;
    double lap2 = car2.currentS1 + car2.currentS2 + car2.currentS3;
    return (int) lap1 - lap2;
}

int compTotalTime(const void * a, const void * b) {
    Car car1 = *((Car *) a);
    Car car2 = *((Car *) b);
    return (int) car1.totalTime - car2.totalTime;
}

void getPoints(Car cars[], int length) {
    FILE *file = fopen(FILE_POINT, "r");
    if (file == NULL)
        return;

    struct stat sb;
    stat(FILE_POINT, &sb);
    char line[sb.st_size];

    while(fgets(line, (int) sb.st_size + 10, file) != NULL) {
        char *notUsed;
        char *notUsed2;
        char *ptr = strtok(line, ",");
        int id = (int) strtol(ptr, &notUsed, 10);
        ptr = strtok(NULL, ",");
        int point = (int) strtol(ptr, &notUsed2, 10);
        for (int i = 0; i < length; i++) {
            if (cars[i].id == id) {
                cars[i].point = point;
            }
        }
    }
    fclose(file);
}

void storePoints(Car cars[], int length) {
    FILE *file = fopen(FILE_POINT, "w");
    char str[100];
    sprintf(str, "%d,%d\n", cars[0].id, cars[0].point);
    for (int i = 1; i < length; i++) {
        char strCar[10];
        sprintf(strCar, "%d,%d\n", cars[i].id, cars[i].point);
        strcat(str, strCar);
    }
    fputs(str, file);
    fclose(file);
}
#undef MIN_TIME
#undef MAX_TIME
#undef TIME_AT_STAND
#endif //OS_2_PROJET_GROUPE_3_CAR_H
