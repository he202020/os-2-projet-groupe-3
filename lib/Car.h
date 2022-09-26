#ifndef OS_2_PROJET_GROUPE_3_CAR_H
#define OS_2_PROJET_GROUPE_3_CAR_H
#define CAR_DEFAULT_TIME -1 // valeur par défaut des meilleurs temps d'une voiture lors de la génération

typedef struct Car {
    int number; // numéro de la voiture

    int bestS1; // meilleur temps secteur 1
    int bestS2; // meilleur temps secteur 2
    int bestS3; // meilleur temps secteur 3
    int bestTurn; // meilleur temps d'un tour
} Car;

/*
 * Génération d'une voiture de base
 * Permet de définir les valeurs par défaut de la voiture et éviter des erreurs
 */
Car getCar(int number) {
    Car car;
    car.number = number;
    car.bestS1 = CAR_DEFAULT_TIME;
    car.bestS2 = CAR_DEFAULT_TIME;
    car.bestS3 = CAR_DEFAULT_TIME;
    car.bestTurn = CAR_DEFAULT_TIME;
    return car;
}
#endif //OS_2_PROJET_GROUPE_3_CAR_H
