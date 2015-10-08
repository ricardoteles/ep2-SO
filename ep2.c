#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "prompt.h"
#include "memoryManager.h"

struct timeval inicio;

FILE *arqMem, *arqVir;
sem_t mutex, semThread[NMAX_PROCS], semLiberouEspaco;
int deadProcs = 0;

void simulador(int numGerEspLiv);
void *Debug(void *a);
void *Processo(void *a);
void insereNaMemoriaVirtual(int tamanho, int pid);
int compare_arrive(const void *a,const void *b);
void parserArgumentosEntrada(int argc, char* argv[]);
float tempoDesdeInicio();
void inicializaSemaforos();

int main(int argc, char* argv[]) {
	parserArgumentosEntrada(argc, argv);

	return 0;
}

void simulador(int numGerEspLiv) {
	initList(memVirtual);

	pthread_t procs[NMAX_PROCS];
	pthread_t debug;
	int i, pos;

	qsort(tabelaProcessos, nProcs, sizeof(PROCESS), compare_arrive);
	
	for(pos = 0; pos < nProcs; pos++) {
		tabelaProcessos[pos].pid = pos;	
	}

	inicializaSemaforos();

	if (pthread_create(&debug, NULL, Debug, (void *) NULL)) {
        printf("\n ERROR creating thread Debug\n");
        exit(1);
	}


	gettimeofday(&inicio, NULL);
	
	for (i = 0; i < nProcs; i++) {
		while (tempoDesdeInicio(inicio) < tabelaProcessos[i].t0) usleep(50000);
		
		if (pthread_create(&procs[i], NULL, Processo, (void *) &tabelaProcessos[i].pid)) {
            printf("\n ERROR creating thread procs[%d]\n", i);
            exit(1);
        }

        insereNaMemoriaVirtual(tabelaProcessos[i].b, tabelaProcessos[i].pid);
        sem_post(&semThread[tabelaProcessos[i].pid]);
	}

	for (i = 0; i < nProcs; i++) {
        if (pthread_join(procs[i], NULL)) {
			printf("\n ERROR joining thread procs[%d]\n", i);
			exit(1);
        }
    }

    if (pthread_join(debug, NULL)) {
		printf("\n ERROR joining thread procs[%d]\n", i);
		exit(1);
    }
}

void insereNaMemoriaVirtual(int tamanho, int pid) {
	switch(numGerEspLiv){
		case 1: firstFit(tamanho, pid);
				break;
		
		case 2:	nextFit(tamanho, pid);
				break;

		case 3:	/*quickFit(tamanho, pid);*/
				break;
	}
}

void *Debug(void *a) {
	float wait;
	struct timeval inicioDebug;

	while (deadProcs < nProcs) {
		gettimeofday(&inicioDebug, NULL);

		// (int)(intervalo-wait)*1000000 ?
		while ((wait = tempoDesdeInicio(inicioDebug)) < intervalo) 
			usleep(10000);

		sem_wait(&mutex);
		printf("\n--------------------- Status da memoria: ---------------------\n");
		// imprimeMemoria();
		printList();
		printf("\n--------------------------------------------------------------\n");
		sem_post(&mutex);
	}
}

void *Processo(void *a) {
	int* id = (int*) a;
	int pid = (*id);
	Node aux = tabelaProcessos[pid].listaTrace->next;

	sem_wait(&semThread[pid]);

	while (tempoDesdeInicio(inicio) < tabelaProcessos[pid].tf){
		if(aux == NULL){
			while (tempoDesdeInicio(inicio) < tabelaProcessos[pid].tf) usleep(50000);
			break;
		}

		while (tempoDesdeInicio(inicio) < aux->t) usleep(50000);
	
		// sem_wait(&mutex);
		// printf("Eu sou o %s. p = %d t = %f \n", tabelaProcessos[pid].nome, aux->p, tempoDesdeInicio(inicio));
		// sem_post(&mutex);
	
		aux = aux->next;
	}
	
	// printf("Eu sou o %s.	tf = %f (ACABEI)\n", tabelaProcessos[pid].nome, tempoDesdeInicio(inicio));

	sem_wait(&mutex);
	deadProcs++;
	sem_post(&mutex);

	return NULL;
}

int compare_arrive(const void *a,const void *b) {
	PROCESS *x = (PROCESS *) a;
	PROCESS *y = (PROCESS *) b;

	if (x->t0 < y->t0) return -1;
	else if (x->t0 > y->t0) return 1;
	else return 0;
}

void parserArgumentosEntrada(int argc, char* argv[]) {
	if(argc == 1) {
		shell();
	}
	else {
		printf("Formato esperado:\n./ep2\n");
		exit(0);
	}
}

float tempoDesdeInicio(struct timeval inicio) {
	struct timeval fim;
	float timedif;

	gettimeofday(&fim, NULL);
	timedif = (float)(fim.tv_sec - inicio.tv_sec);
	timedif += (float)(fim.tv_usec - inicio.tv_usec)/1000000;

	return timedif;
}

void inicializaSemaforos() {
	int i;

	if (sem_init(&mutex, 0, 1)) {
		fprintf(stderr, "ERRO ao criar semaforo mutex\n");
		exit(0);
	}

	if (sem_init(&semLiberouEspaco, 0, 0)) {
		fprintf(stderr, "ERRO ao criar semaforo semLiberouEspaco\n");
		exit(0);
	}

	for (i = 0; i < NMAX_PROCS; i++) {
		if (sem_init(&semThread[i], 0, 0)) {
			fprintf(stderr, "ERRO ao criar semaforo semThread[%d]\n", i);
			exit(0);
		}
	}
}