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
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define STACK_SIZE 10

int stack[STACK_SIZE];
int count = 0;

void push(int value) {
    if (count < STACK_SIZE) {
        stack[count++] = value;
    }
}

int pop() {
    if (count > 0) {
        return stack[--count];
    }
    return -1; // Errore, stack vuoto
}

int stackIsFull() {
    return count == STACK_SIZE;
}

int stackIsEmpty() {
    return count == 0;
}

int stackSize() {
    return count;
}

void *producer(void *arg) {
    while (1) {
        usleep(rand() % 1000000); // Attende un tempo casuale < 1 secondo
        
        while (stackIsFull()) {
            continue;
        }
        
        int items_to_add = rand() % (STACK_SIZE - count) + 1;
        printf("Produttore: aggiunge %d elementi\n", items_to_add);
        for (int i = 0; i < items_to_add; i++) {
            int value = rand() % 100;
            push(value);
            printf("Produttore ha aggiunto: %d\n", value);
        }
    }
    return NULL;
}

void *consumer(void *arg) {
    while (1) {
        usleep(rand() % 1000000); // Attende un tempo casuale < 1 secondo
        
        while (stackIsEmpty()) {
            continue;
        }
        
        int items_to_remove = rand() % stackSize() + 1;
        printf("Consumatore: rimuove %d elementi\n", items_to_remove);
        for (int i = 0; i < items_to_remove; i++) {
            int value = pop();
            printf("Consumatore ha rimosso: %d\n", value);
        }
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t prod, cons;
    
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    
    return 0;
}
