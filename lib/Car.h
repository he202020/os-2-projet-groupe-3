#ifndef OS_2_PROJET_GROUPE_3_CAR_H
#define OS_2_PROJET_GROUPE_3_CAR_H
#define CAR_DEFAULT_TIME -1 // valeur par défaut des meilleurs temps d'une voiture lors de la génération

typedef struct Car {
    int id; // numéro de la voiture

    double currentS1; // meilleur temps secteur 1
    double currentS2; // meilleur temps secteur 2
    double currentS3; // meilleur temps secteur 3
} Car;

Car getCar(int number);
double getCurrentTurn(Car car);

/*
 * Génération d'une voiture de base
 * Permet de définir les valeurs par défaut de la voiture et éviter des erreurs
 */
Car getCar(int id) {
    Car car;
    car.id = id;
    car.currentS1 = CAR_DEFAULT_TIME;
    car.currentS1 = CAR_DEFAULT_TIME;
    return car;
}

/*
 * Renvoit le temps actuel du tour de la voiture
 */
double getCurrentTurn(Car car) {
    return car.currentS1 + car.currentS2 + car.currentS3;
}
#endif //OS_2_PROJET_GROUPE_3_CAR_H
