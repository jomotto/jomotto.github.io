#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 3

int main() {
  srand(time(NULL)); //El mayordomo pone a girar la diana
  int index;
  int vector[MAX];
  int contador;
  int aleatorio;
  int gap;
  int suma;

  memset(&vector, '\0', sizeof(vector));

  int test = rand(); //Primer disparo del robot
  gap = RAND_MAX / MAX;

  for (contador=0; contador < 20; contador++)
  {
	aleatorio = rand();
        index = aleatorio%MAX;
//        vector[index]++;
  	//printf ("%d [%02d] %i\n", aleatorio, index,  vector[index]) ;
  	printf ("[%02d]\n", index) ;
  }

  suma = 0;
//  for (contador=0; contador < MAX; contador++)
//  {
 // 	printf ("[%02d] %i\n", contador, vector[contador]) ;
  //      suma += vector[contador];
 // }


  printf("El total de nros %d\n", suma);


  return 0;
}
