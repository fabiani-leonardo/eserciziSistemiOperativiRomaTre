/*Una pila di 10 elementi interi è condivisa tra due thread: un produttore ed un consumatore

1)     Il produttore deve essere implementato secondo la seguente logica. In un ciclo infinito:

Deve attendere una quantità di tempo casuale inferiore al secondo
Una volta scaduta l’attesa, se la pila è piena, deve attendere che qualche elemento venga rimosso dal consumatore
Quando si libera dello spazio nello stack, deve inserire un numero casuale di elementi (senza andare in overflow)
2)     Il consumatore deve essere implementato secondo la seguente logica. In un ciclo infinito:

Deve attendere una quantità di tempo casuale inferiore al secondo
Una volta scaduta l’attesa, se lo stack è vuoto, deve attendere che qualche elemento venga inserito dal produttore
Quando lo stack non è vuoto, deve leggere un numero casuale di elementi (inferiore o uguale al numero di elementi presenti nello stack) 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	pthread_t prod,cons;

	pthread_create(&prod,NULL, producer,NULL);
	pthread_create(&cons,NULL, consumer,NULL);
	
	//prinwdfdds

	return 0;
}

