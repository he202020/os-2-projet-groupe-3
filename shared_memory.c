/*shared memory -> info : tab de voiture et ajouter a la fin du tab meilleur tours s1 s2 s3

prochaine etape: local -> mem partagée (cela ne change pas a ce qu'on a fait en local):
int shmid = shmget(key (int > 1), taille(20*sizeof(voiture)), perm (IPC_CREAT | 0666)) -> clé (la mm) permet d'acceder zone de mem partagé
addr = shmat(shmid, 0 ou NULL, 0(flag))-> attacher zone a mon programme, reçu d'une adresse  
addr -> struct voiture*circuit;

shared memory -> regarder pr mettre le tableau de voiture et les infos de la course (pas le tri dans la mem partagée) et voir pour vider la mem partagée
com it */

int shm_id = shmget(SHM_KEY, sizeof(20*sizeof(voiture)), 0666|IPC_CREAT) //clé (la mm) permet d'acceder zone de mem partagé - Create the shared memory segment or use an already created shared memory segment (shmget()). ARG ==> recognizes the shared memory segment, the size of the shared memory segment rounded to multiple of PAGE_SIZE, specifies the required shared memory flag/s
 if (shm_id == -1) {
      perror("Shared memory");
      return 1;
   }

shm_addr = shmat(shmid, 0 ou NULL, 0(flag)) //La fonction shmat() attache le segment de mémoire partagée System V identifié par shmid au segment de données du processus appelant.
if (!shm_addr) { /* operation failed. */
    perror("shmat: ");
    exit(1);
}

int shmdt(const void *shmaddr) // La  fonction shmdt() détache le segment de mémoire partagée situé à l'adresse indiquée par shmaddr. Le segment doit être effectivement attaché, et l'adresse shmaddr doit être  celle renvoyée précédemment par shmat().

int shmctl(int shmid, int cmd, struct shmid_ds *buf) //clear Shared memory

