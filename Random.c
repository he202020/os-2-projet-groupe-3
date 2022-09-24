#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    //pseudo random numbers
    int number;
    int lower = 0, upper = 25;

    srand(time(NULL));

    number = (rand() % (upper - lower+1)) + lower;
    printf("%d\n", number);
    //
    return 0;
}

int main()
{
    //pseudo random numbers
    srand(time(NULL));
    printf("%d\n", rand()%25);
    printf("%d\n", rand()%20);
    printf("%d\n", rand()%10);
    //
    return 0;
}


int main(){
   int i, n; 
   n = 5;
   // Intializes
   srand(time(NULL));
   // Print 5 random numbers btw 20 - 25
   for( i = 0 ; i < n ; i++ ) {
      printf("%d\n", rand() % 5 + 20);
   }
   
   return(0);
}