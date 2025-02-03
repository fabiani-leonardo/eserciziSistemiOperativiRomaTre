/*Il seguente esercizio ha lo scopo di simulare lo scheduler di un sistema operativo e l’esecuzione di processi (job), nel caso semplificato in cui l’esecuzione di 
un processo non può essere interrotta e non è necessario accedere a risorse oltre la CPU.

Si consideri il seguente scenario. Si dispone di un computer dove:

-          Il tasso di arrivi dei processi è pari a 10 processi al secondo. In altre parole, è come se venissero eseguite sul computer considerato 10 applicazioni al secondo

-          Il tempo di esecuzione di ogni processo è un valore casuale sempre inferiore a 1 secondo

-          Lo scheduler non supporta più di 1000 processi in coda. Ciò vuol dire che, se la coda è piena, non vengono ricevuti nuovi processi

-          Lo scheduler implementa la politica FIFO

Scrivere un simulatore che implementi il comportamento dello scenario descritto e che calcoli il turnaround time medio al variare dei seguenti parametri:

-          Durata della simulazione: il numero di job che arrivano all’interno del sistema è pari a 10, 20, 30.

-          Numero delle CPU: il computer in considerazione può avere 1, 2, 4 CPU.

 

Si suggerisce di utilizzare come base di partenza l’implementazione del produttore-consumatore. La struttura dati rappresentante la coda di processi è disponibile nel file queue.h

 

Suggerimenti su queue.h:

Prendere familiarità con le strutture dati definite in queue.h, in particolare con la struct Process. Quest’ultima può essere utilizzata per memorizzare informazioni 
utili quali l’ID del processo, il suo tempo di esecuzione, il tempo di arrivo all’interno del sistema, il tempo di avvio ed il tempo di completamento. Questa struct 
Process è utilizzata per costruire una lista bidirezionale che può essere acceduta con diverse funzioni, tra le quali: enqueue(Queue* queue, Process* data) e 
dequeue(Queue* queue): la prima aggiunge un processo in coda alla lista, la seconda rimuove e restituisce il processo in testa alla lista. Per poter inizializzare 
la coda è necessario utilizzare la funzione initializeQueue(Queue* queue).

Suggerimenti sulla simulazione:

E’ possibile implementare la simulazione estendendo il problema del produttore-consumatore, in particolare:

-          Il thread produttore può essere implementato in modo tale da generare processi alla velocità indicata in precedenza

-          Il thread consumatore può rappresentare una CPU che estrae un processo dalla coda e lo esegue.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "queue.h"
#include <pthread.h>
#include <stdbool.h>


#define MAXPROC 100
#define NARRIVI 110
#define THREADS 2

int idProgressivo=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
double tempoTotale=0;
int processiServiti=0;
int inCoda=0;
Queue q;
int flag=0;


void *arrivo(void *arg){
	//devono arrivare 10 processi al secondo
	//un processo ogni 0.1 secondi o 100000 usecondi
	for (int i = 0; i < NARRIVI; ++i)
	{
		usleep(100000);
		pthread_mutex_lock(&mutex);

		

		if (inCoda<MAXPROC){
			Process *p=(Process *)malloc(sizeof(Process));
			p->id=idProgressivo++;
			gettimeofday(&p->arrival, NULL);
			enqueue(&q,p);
			printf("in attesa: %ld\n",p->id );
			inCoda++;
			
		}else{
			i--;
		}
		pthread_mutex_unlock(&mutex);
		usleep(5000);

	}
	pthread_mutex_lock(&mutex);
	flag=1;
	printf("flag impostata\n");
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *servizio(void *arg){
	int tempoServizio=0;
	while(1){
		pthread_mutex_lock(&mutex);
		if (isQueueEmpty(&q)!=1){
			printf("eccomi2\n");
			Process *p=dequeue(&q);
			printf("servo: %ld\n",p->id );
			gettimeofday(&p->start, NULL);
			tempoServizio=rand()%1000000;	//fingo di servire il processo
			gettimeofday(&p->end, NULL);
			tempoTotale=tempoTotale+((p->end.tv_usec)-(p->arrival.tv_usec));
			processiServiti++;
			inCoda--;
		} else if (flag == 1) {
            pthread_mutex_unlock(&mutex);
            printf("finito\n");
            return NULL;
        }

		pthread_mutex_unlock(&mutex);
		usleep(5000);
	}
}


int main(int argc, char const *argv[])
{
    initializeQueue(&q);
    srand(time(NULL));

    pthread_t a;
    pthread_t s[THREADS];  // Array di thread per il servizio

    // Crea il thread per la gestione degli arrivi
    pthread_create(&a, NULL, arrivo, NULL);

    // Crea i thread per la gestione del servizio
    for (int i = 0; i < THREADS; i++) {
        pthread_create(&s[i], NULL, servizio, NULL);
    }

    // Attendi la terminazione del thread di arrivo
    pthread_join(a, NULL);

    // Attendi la terminazione di tutti i thread di servizio
    for (int i = 0; i < THREADS; i++) {
        pthread_join(s[i], NULL);
    }


    printf("numero di processi eseguiti= %d\n", processiServiti);
    printf("tempo totale di esecuzione= %f\n", tempoTotale/1000000);
    printf("numero threads utilizzati= %d\n", THREADS);
    printf("sono stati eseguiti %f processi al secondo\n", (double)processiServiti/(tempoTotale/1000000));
    

    return 0;
}