#ifndef OS_2_PROJET_GROUPE_3_CHAMPIONNAT_H
#define OS_2_PROJET_GROUPE_3_CHAMPIONNAT_H
#define FILE_NAME "calendar"
#define TEMP_FILE_NAME "temp"
#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>

void deleteFirstLine();
void getWeType(char* weType);
int getSize();
void setPoints(Car cars[]);

/*
 * Renvoi le type de weekend parmi 'classic', 'special' ou NULL
 * et supprime la première ligne du fichier de championnat
 */
void deleteFirstLine() {
    FILE* file = fopen(FILE_NAME, "r");
    char c;
    struct stat sb;
    stat(FILE_NAME, &sb);
    if (sb.st_size == 0) {
        fclose(file);
        return;
    }
    int countLine = 1;
    while ((c = getc(file)) != EOF)
        if (c == '\n')
            countLine++;

    if (countLine == 1) {
        file = fopen(FILE_NAME, "w");
        fclose(file);
        return;
    }
    fclose(file);

    file = fopen(FILE_NAME, "r");
    FILE* temp = fopen(TEMP_FILE_NAME, "w");
    stat(FILE_NAME, &sb);
    char line[sb.st_size];

    while (fgets(line, (int) sb.st_size, file) != NULL) {
        fputs(line, temp);
    }
    fclose(file);
    fclose(temp);

    file = fopen(FILE_NAME, "w");
    temp = fopen(TEMP_FILE_NAME, "r");
    bool isFirstLine = true;
    char line_copy[sb.st_size];
    while (fgets(line_copy, (int) sb.st_size, temp) != NULL) {
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        fputs(line_copy, file);
    }

    fclose(file);
    fclose(temp);
    remove(TEMP_FILE_NAME);
}


void getWeType(char weType[]) {
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        weType = NULL;
        return;
    }
    struct stat sb;
    stat(FILE_NAME, &sb);
    fgets(weType, (int) sb.st_size + 10, file);
    fclose(file);
}

int getSize() {
    struct stat sb;
    stat(FILE_NAME, &sb);
    return (int) sb.st_size;
}

void setPoints(Car cars[]) {
    cars[0].point += 25;
    cars[1].point += 20;
    cars[2].point += 15;
    cars[3].point += 10;
    cars[4].point += 8;
    cars[5].point += 6;
    cars[6].point += 5;
    cars[7].point += 3;
    cars[8].point += 2;
    cars[9].point += 1;
}



void classement(Car cars[], int length) {
    system("clear");
    qsort(cars, length, sizeof(Car), compPoint);
    printf("\n\n\n\n\n\n\n\n\nClassement du championnat :\n");
    printf("---------------------------\n");
    printf(" Premier : %d - %d points\n", cars[0].id, cars[0].point);
    printf(" Second : %d - %d points\n", cars[1].id, cars[1].point);
    printf(" Troisième : %d - %d points\n", cars[2].id, cars[2].point);
    printf("---------------------------\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}


#undef FILE_NAME
#undef TEMP_FILE_NAME
#endif //OS_2_PROJET_GROUPE_3_CHAMPIONNAT_H
