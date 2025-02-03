#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h> //necessario per in rand()

int main(int argc, char const *argv[])
{
	int *array;		//inizializzo puntatore ad array
	int size=0;		//inizializzo size

	printf("Inserisci la dimensione dell'array: ");
    scanf("%d", &size);
	
	if (size<=0)
	{
		printf("grandezza troppo piccola\n");
		return 1;

	}else{
		array=(int *)malloc(size*sizeof(int));	//allocazione memoria per l'array
		if (array==NULL)
		{
			printf("malloc fallita\n");
			return 1;
		}else{

			srand(time(NULL));	//inserisce il seme di generazione del random

			for (int i = 0; i < size; ++i)
			{
				array[i]=rand() % 100;//generazione di un numero casuale ra 0 e 99
				printf("%d ", array[i]);
			}
			printf("\n");
		}
	}
	free(array);
	return 0;
}