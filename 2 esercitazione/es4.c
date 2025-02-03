/*Esercizio 4: Implementazione di my_malloc() e my_free()
Scrivi un programma che implementi le funzioni my_malloc() e my_free(). 
Queste funzioni devono comportarsi rispettivamente come le funzioni malloc() e free(),
 cioè: la prima deve ritornare un puntatore void ad una area di memoria utilizzabile della
  dimensione specificata come parametro; la seconda deve liberare l'area di memoria alla quale
   fa riferimento il puntatore passato come parametro. L'intero programma deve essere 
   realizzato senza utilizzare le funzioni malloc() e free(). E' possibile utilizzare una sola
    volta mmap() e munmap(), per le quali sono disponibili le pagine di man.*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

#define HEAP_SIZE 4096 // Dimensione della memoria gestita

// Struttura per i metadati dei blocchi
typedef struct Block {
    size_t size;
    int free;
    struct Block *next
} Block;

static void *heap_start = NULL;
static Block *free_list = NULL;

void my_malloc_init() {
    heap_start = mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (heap_start == MAP_FAILED) {
        perror("mmap");
        return;
    }
    free_list = (Block *)heap_start;
    free_list->size = HEAP_SIZE - sizeof(Block);
    free_list->free = 1;
    free_list->next = NULL;
}

void *my_malloc(size_t size) {
    if (!heap_start) {
        my_malloc_init();
    }

    Block *curr = free_list;
    while (curr) {
        if (curr->free && curr->size >= size) {
            curr->free = 0;
            return (void *)(curr + 1);
        }
        curr = curr->next;
    }
    return NULL; // Memoria esaurita
}

void my_free(void *ptr) {
    if (!ptr) return;
    Block *block = (Block *)ptr - 1;
    block->free = 1;
}

void my_malloc_cleanup() {
    if (heap_start) {
        munmap(heap_start, HEAP_SIZE);
        heap_start = NULL;
        free_list = NULL;
    }
}

int main(int argc, char const *argv[]) {
    int size = 0;

    // Chiede all'utente la dimensione dell'array
    printf("Inserire dimensione array:\n");
    scanf("%d", &size);

    // Allocazione dinamica dell'array
    int *array = (int *)malloc(size * sizeof(int));
    if (array == NULL) {
        printf("Errore: allocazione memoria fallita.\n");
        return 1;
    }

    // Array da copiare
    int array2[] = {0, 1, 2, 3, 4, 5};
    size_t array2_size = sizeof(array2) / sizeof(array2[0]);

    // Copia i valori da array2 a array usando memcpy
    size_t copy_size = size < array2_size ? size : array2_size;
    memcpy(array, array2, copy_size * sizeof(int));

    // Stampa dell'array copiato
    printf("Array copiato:\n");
    for (int i = 0; i < copy_size; ++i) {
        printf("%d\n", array[i]);
    }

    // Liberazione della memoria
    free(array);

    return 0;
}

