#ifndef OS_2_PROJET_GROUPE_3_STOCKAGE_H
#define OS_2_PROJET_GROUPE_3_STOCKAGE_H
#include "Car.h"
#include "NumberUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define FILE_NAME "../SaveResult"

void save(Car cars[], int length);
void load(Car cars[20]);


void save(Car cars[], int length) {
    FILE* file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("Le fichier ne peut pas être ouvert\n");
        exit(7);
    }

    for (int i = 0; i < length; i++) {
        char idToStr[lenInt(cars[i].id)];
        if (i == length-1) {
            sprintf(idToStr, "%d", cars[i].id);
        } else {
            sprintf(idToStr, "%d\n", cars[i].id);
        }
        fputs(idToStr, file);
    }

    fclose(file);
}

void load(Car cars[20]) {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Le fichier ne peut pas être ouvert\n");
        exit(8);
    }
    struct stat sb;
    stat(FILE_NAME, &sb);
    char line[sb.st_size];
    int index = 0;

    while(fgets(line, (int) sb.st_size, file) != NULL) {
        char *notUsed;
        int id = (int) strtol(line, &notUsed, 10);
        cars[index] = getCar(id);
        index++;
    }
//    fclose(file);
}

#undef FILE_NAME
#endif //OS_2_PROJET_GROUPE_3_STOCKAGE_H
