#ifndef OS_2_PROJET_GROUPE_3_SHMUTILS_H
#define OS_2_PROJET_GROUPE_3_SHMUTILS_H
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include "Car.h"

#define SHM_MAIN_PID_KEY 5678
#define SHM_COURSE_STATE_KEY 4579
#define SHM_COURSE_KEY 5421
#define SHM_CAR_ARRAY_KEY 1515

void createPid(Car cars[], int length);
void clearSHM();
void registerMainPid(int pid);
int getMainPid();
void setCourseState(bool state);
bool getCourseState();
void registerCourse(Course course);
Course getCourse();
void insertCarArray(Car cars[], int length);
void getCarArray(Car cars[], int length);
void updateCarInSM(Car car, int length);

/*
 * Créer tous les processus enfants et en associe un à chaque voiture
 * (voir car.pid)
 */
void createPid(Car cars[], int length) {
    for (int i = 0; i < length; i++) {
        if (fork() == 0) cars[i].pid = getpid();
    }
}

/*
 * Permet de détacher tous les segments de la SM au processus utilisant cette fonction
 */
void clearSHM() {
    int shmid;
    if ((shmid = shmget(SHM_MAIN_PID_KEY, sizeof(int), IPC_CREAT | 0666)) != -1) {
        int* addr = (int*) shmat(shmid, NULL, 0666);
        shmdt(addr);
        shmctl(shmid, IPC_RMID, NULL);
    }

    if ((shmid = shmget(SHM_COURSE_STATE_KEY, sizeof(bool), IPC_CREAT | 0666)) != -1) {
        shmctl(shmid, IPC_RMID, NULL);
        bool* addr = (bool*) shmat(shmid, NULL, 0666);
        shmdt(addr);
    }

    if ((shmid = shmget(SHM_COURSE_KEY, sizeof(Course), IPC_CREAT | 0666)) != -1) {
        Course* addr = (Course*) shmat(shmid, NULL, 0666);
        shmdt(addr);
        shmctl(shmid, IPC_RMID, NULL);
    }

    if ((shmid = shmget(SHM_CAR_ARRAY_KEY, sizeof(Car[20]), IPC_CREAT | 0666)) != -1) {
        Car* addr = shmat(shmid, NULL, 0666);
        shmdt(addr);
        shmctl(shmid, IPC_RMID, NULL);
    }
}

/*
 * Enregistre le PID principale dans la SM
 * A utiliser avant un fork() sinon, l'insersion sera biaisée
 */
void registerMainPid(int pid) {
    int shmid = shmget(SHM_MAIN_PID_KEY, sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) exit(1);

    int* shm = (int*) shmat(shmid, NULL, 0);
    int* i = shm;
    *shm++ = pid;
}

/*
 * Renvoit le PID stocké dans la SM
 */
int getMainPid() {
    int shmid = shmget(SHM_MAIN_PID_KEY, sizeof(int), 0666);
    if (shmid == -1) exit(2);
    int* shm = (int*) shmat(shmid, NULL, 0);
    return *shm;
}

/*
 * Définis le status de la course :
 * true : en cours
 * false : finie
 */
void setCourseState(bool state) {
    int shmid = shmget(SHM_COURSE_STATE_KEY, sizeof(bool), IPC_CREAT | 0666);
    if (shmid < 0) exit(3);
    bool* shm = (bool*) shmat(shmid, NULL, 0);
    bool* b = shm;
    *b++ = state;
}

/*
 * Renvoit l'état de la course
 * TRUE : la course est toujours en cours
 * FALSE : elle est finie
 */
bool getCourseState() {
    int shmid = shmget(SHM_COURSE_STATE_KEY, sizeof(bool), 0666);
    if (shmid == -1) exit(4);
    bool* shm = (bool*) shmat(shmid, NULL, 0);
    return *shm;
}

/*
 * Permet d'enregister une structure course dans la SM
 */
void registerCourse(Course course) {
    int shmid = shmget(SHM_COURSE_KEY, sizeof(Course), IPC_CREAT | 0666);
    if (shmid == -1) exit(5);
    Course* shm = (Course*) shmat(shmid, NULL, 0);
    Course* c = shm;
    *c++ = course;
}

/*
 * Permet de récupérer la course mise dans la SM
 */
Course getCourse() {
    int shmid = shmget(SHM_COURSE_KEY, sizeof(Course), 0666);
    if (shmid == -1) exit(6);
    Course* shm = (Course*) shmat(shmid, NULL, 0);
    return *shm;
}

/*
 * Insère une liste de structure "Car" dans la SM
 * Définit aussi l'attribut "smAddr" comme l'addresse de la structure Car stockée dans la SM
 */
void insertCarArray(Car cars[], int length) {
    int shhmid = shmget(SHM_CAR_ARRAY_KEY, sizeof(Car[length]), IPC_CREAT | 0666);
    Car* shm = (Car*) shmat(shhmid, NULL, 0);
    Car* c = shm;
    for (int i = 0; i < length; i++) {
        cars[i].smAddr = c;
        *c++ = cars[i];
    }
}

/*
 * Renvoit la liste de la liste de structure "Car" stockée dans la SM et l'insère dans la liste
 * mise en paramètre
 */
void getCarArray(Car cars[], int length) {
    int shmid = shmget(SHM_CAR_ARRAY_KEY, sizeof(Car[length]), IPC_CREAT | 0666);
    Car* shm = (Car*) shmat(shmid, NULL, 0);
    for (int i = 0; i < length; i++) {
        cars[i] = *shm;
        shm++;
    }
}

void updateCarInSM(Car car, int length) {
    int shmid = shmget(SHM_CAR_ARRAY_KEY, sizeof(Car[length]), IPC_CREAT | 0666);
    Car* shm = (Car*) shmat(shmid, NULL, 0);
    *shm = car;
}

#undef SHM_CAR_ARRAY_KEY
#undef SHM_MAIN_PID_KEY
#undef SHM_COURSE_STATE_KEY
#undef SHM_COURSE_KEY
#endif //OS_2_PROJET_GROUPE_3_SHMUTILS_H
