## Snippets : 
Quelques bouts de code pratiques à avoir pour le projet

### 1) Utilisation de l'état de course :
Permet de faire tourner les voitures pendant un certain temps
et de les arrêter après ce temps
```c
// enregistrement du PID du processus principal
registerMainPid(getpid());

// init et début de la course
Car cars[] = {getCar(77), getCar(24), getCar(47), getCar(9)};
const int lenCars = 4;
setCourseState(true);

createPid(cars, lenCars);

if (getpid() == getMainPid()) {
    printf("Ici le main\n");
    sleep(5);
    setCourseState(false);
} else {
    while (getCourseState()) {
        printf("%d\n", getpid());
        sleep(1);
    }
}
```

* La première étape est d'enregistrer le PID de ce processus
dans la **mémoire partagée** afin que les autres processus
(*qui n'existent pas encore*) puissent accéder à cette donnée.
Cette première étape permettra de différencier ce processus
des autres, il est spécial, c'est celui qui attendra,
* On initialise la liste de voitures,
* On définit l'état de la course en `true`,
* On crée un processus enfant pour chaque voiture,
* On différencie le processus principal des autres,
* Le processus principal attend quelques secondes avant
définir l'état de la course en `false`,
* Les autres processus font la course tant que l'état de la
course est en `true` (*le *`sleep(1)`* permet de ne pas spam
le terminal de messages*).

### 2) Update une voiture dans la SM :
Permet, à partir de l'attribut `smAddr` d'une structure *Car*,
de modifier les données de sa structure dans la 
**mémoire partagée**.
```c
// init et insertion
Car cars[] = {getCar(77), getCar(24), getCar(47), getCar(9)};
const int lenCars = 4;
insertCarArray(cars, 4);

// modification
cars[0].currentS1 = 10;
printf("%f\n", cars[0].currentS1);
*cars[0].smAddr = cars[0];

// application de la modification sur la copie de la liste
Car carsCopy[4];
getCarArray(carsCopy, 4);
printf("%f\n", carsCopy[0].currentS1);
```

* On va d'abord initialiser une liste de structure *Car*,
* On insère cette liste dans la **mémoire partagée**,
* On modifie une voiture (*on print la modif pour
prouver la modification*),
* On enregistre cette modification dans la **mémoire
partagée** via l'attribut `smAddr` de la structure qui est
un pointeur vers de la voiture dans la mémoire partagée,
* On crée une nouvelle liste afin de s'assurer que les
modifications ont bien eu place dans la mémoire partagée,
* Enfin, on copie la liste de la mémoire partagée vers la
nouvelle liste.

Il est important de différencier 2 pointeurs celui de la 
variable en cours `&car` et le pointeur de la voiture dans
la **mémoire partagée** `car.smAddr`. Il n'y a pas de réel send
d'utiliser le pointeur de la variable en cours comme les
données sont stockées et consultées via la SM.
La différence entre ces 2 pointeurs peut être vue en faisant
`printf("%p %p\n", &car, car.smAddr)`.