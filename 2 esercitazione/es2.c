/*Esercizio 2: Gestione di vettori dinamici
Implementa una struttura dati per un vettore 
dinamico di interi. Includi funzioni per aggiungere 
un elemento, rimuovere un elemento e stampare tutti gli
 elementi del vettore. Assicurati che il vettore aumenti la
  sua capacità quando necessario.*/

#include <stdio.h>
#include <stdlib.h>

// Funzione per stampare l'array
void printArray(int *array, int size) {
    if (size == 0) {
        printf("Array vuoto.\n");
        return;
    }
    printf("Array: ");
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Funzione per aggiungere un elemento
void addElement(int **array, int *size, int *sizemax, int value) {
    if (*size == *sizemax) {
        *sizemax *= 2;
        *array = (int *)realloc(*array, (*sizemax) * sizeof(int));
        if (*array == NULL) {
            printf("Errore: realloc fallito.\n");
            exit(1);
        }
    }
    (*array)[(*size)++] = value;
}

// Funzione per rimuovere un elemento
void removeElement(int *array, int *size, int index) {
    if (index < 0 || index >= *size) {
        printf("Indice non valido.\n");
        return;
    }
    for (int i = index; i < (*size) - 1; ++i) {
        array[i] = array[i + 1];
    }
    (*size)--;
}

int main() {
    int *array = (int *)malloc(1 * sizeof(int));
    if (array == NULL) {
        printf("Errore: malloc fallito.\n");
        return 1;
    }
    int size = 0;      // Numero di elementi nell'array
    int sizemax = 1;   // Capacità iniziale dell'array
    int scelta = 1;

    while (scelta != 0) {
        printf("\n1 - Stampa\n2 - Inserisci\n3 - Rimuovi\n0 - Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1: // Stampa
                printArray(array, size);
                break;
            case 2: { // Inserisci
                int value;
                printf("Inserisci un numero: ");
                scanf("%d", &value);
                addElement(&array, &size, &sizemax, value);
                break;
            }
            case 3: { // Rimuovi
                int index;
                printf("Inserisci l'indice dell'elemento da rimuovere: ");
                scanf("%d", &index);
                removeElement(array, &size, index);
                break;
            }
            case 0: // Esci
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida. Riprova.\n");
        }
    }

    free(array);
    return 0;
}
