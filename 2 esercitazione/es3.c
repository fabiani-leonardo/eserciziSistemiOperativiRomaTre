/*Esercizio 3: Manipolazione della memoria
Scrivi un programma che alloca memoria per un array di interi, 
usa memset per impostare tutti gli elementi a zero, quindi usa memcpy per copiare 
il contenuto di un altro array nella memoria appena allocata.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int size=0;
	printf("inserisci grandezza array:\n");
	scanf("%d",&size);
	int *array=(int *)malloc(size*sizeof(int));
	if (array == NULL) {
        printf("Errore: allocazione di memoria fallita.\n");
        return 1;
    }

	memset(array, 0, size * sizeof(int));

	int source[] = {1, 2, 3, 4, 5};
    int source_size = sizeof(source) / sizeof(source[0]);

    // Copia il contenuto di `source` nell'array dinamico usando memcpy
    if (size >= source_size) {
        memcpy(array, source, source_size * sizeof(int));
    } else {
        printf("L'array dinamico è più piccolo dell'array sorgente.\n");
        memcpy(array, source, size * sizeof(int)); // Copia solo i primi `size` elementi
    }

    // Stampa il contenuto dell'array dinamico
    printf("Contenuto dell'array dinamico:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Libera la memoria allocata
    free(array);

	return 0;
}
