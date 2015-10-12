#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "prompt.h"
#include "memoryManager.h"

struct timeval inicio;

FILE *arqMem, *arqVir;
sem_t mutexPrint;
int deadProcs = 0;

void simulador(int numGerEspLiv);
void *Debug(void *a);
void *Gerenciador(void *a);
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

	pthread_t debug, gerenciador;
	int i;

	qsort(tabelaProcessos, nProcs, sizeof(PROCESS), compare_arrive);
	
	for(i = 0; i < nProcs; i++) {
		tabelaProcessos[i].pid = i;	
	}

	if (pthread_create(&debug, NULL, Debug, (void *) NULL)) {
        printf("\n ERROR creating thread Debug\n");
        exit(1);
	}
	if (pthread_create(&gerenciador, NULL, Gerenciador, (void *) NULL)) {
        printf("\n ERROR creating thread Debug\n");
        exit(1);
	}

	inicializaSemaforos();

	gettimeofday(&inicio, NULL);
	
	for (i = 0; i < nProcs; i++) {
		while (tempoDesdeInicio(inicio) < tabelaProcessos[i].t0) usleep(50000);
		
        insereNaMemoriaVirtual(tabelaProcessos[i].b, tabelaProcessos[i].pid);
        // insereNoArquivo ep2.vir
	}

	if (pthread_join(gerenciador, NULL)) {
		printf("\n ERROR joining thread gerenciador\n", i);
		exit(1);
    }
    if (pthread_join(debug, NULL)) {
		printf("\n ERROR joining thread debug\n", i);
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

		sem_wait(&mutexPrint);
		printf("\n--------------------- Status da memoria: ---------------------\n");
		// imprimeMemoria();
		printList();
		printf("\n--------------------------------------------------------------\n");
		sem_post(&mutexPrint);
	}
}

void *Gerenciador(void *a) {
	int i;
	Node aux[nProcs];
	int acabou[nProcs];

	for(i = 0; i < nProcs; i++){
		aux[i] = tabelaProcessos[i].listaTrace->next;
		acabou[i] = 0;
	}
	
	while(deadProcs < nProcs){
		for(i = 0; i < nProcs; i++){			
			if(tempoDesdeInicio(inicio) >= tabelaProcessos[i].tf && !acabou[i]){
				printf("Tempo = %f  %s (TERMINOU)\n", tempoDesdeInicio(inicio), tabelaProcessos[i].nome);
				acabou[i] = 1;
				deadProcs++;
				break;
			}

			if(aux[i] != NULL){
				if (tempoDesdeInicio(inicio) >= aux[i]->t){ 
					printf("Tempo = %f 	parte %d (%s)\n", tempoDesdeInicio(inicio), aux[i]->p, tabelaProcessos[i].nome);
					// insereNaMemoriaFisica();
					//insereNoArquivo ep2.mem
					aux[i] = aux[i]->next;
				}
			}
		}
		usleep(200000);
	}

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

	if (sem_init(&mutexPrint, 0, 1)) {
		fprintf(stderr, "ERRO ao criar semaforo mutexPrint\n");
		exit(0);
	}
}