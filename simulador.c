#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include "simulador.h"
#include "memoryManager.h"
#include "paginacao.h"

struct timeval inicio;
sem_t mutexPrint;
int deadProcs;

static void alocaEspacoLivre(int tamanho, int pid);
static int compare_arrive(const void *a, const void *b);
static float tempoDesdeInicio();
static void inicializaGlobais();

void *Debug(void *a);
void *Gerenciador(void *a);

void simulador() {
	gettimeofday(&inicio, NULL);

	int i, pid, resto;
	inicializaGlobais();
	inicializaMemoriaVirtual(memVirtual);
	initList(memVirtual/16);

	pthread_t debug, gerenciador;

	qsort(tabelaProcessos, nProcs, sizeof(Process), compare_arrive);
	
	for (i = 0; i < nProcs; i++) {
		tabelaProcessos[i].pid = i;	
		tabelaProcessos[i].start = tabelaProcessos[i].end = 0;
		tabelaProcessos[i].myLink = NULL;
		resto = tabelaProcessos[i].b % 16;
		tabelaProcessos[i].nbytes = tabelaProcessos[i].b;
		if (resto)
			tabelaProcessos[i].nbytes += (16 - resto);
	}

	// printf("nProcs = %d\n", nProcs);
	// if (pthread_create(&debug, NULL, Debug, (void *) NULL)) {
 //        printf("\n ERROR creating thread debug.\n");
 //        exit(1);
	// }
	if (pthread_create(&gerenciador, NULL, Gerenciador, (void *) &inicio)) {
        printf("\n ERROR creating thread Debug\n");
        exit(1);
	}

	if (pthread_join(gerenciador, NULL)) {
		printf("\n ERROR joining thread gerenciador\n");
		exit(1);
    }

 //    if (pthread_join(debug, NULL)) {
	// 	printf("\n ERROR joining thread debug\n");
	// 	exit(1);
	// }

	if (sem_destroy(&mutexPrint) != 0) {
		printf("\n ERROR destroying mutexPrint\n");
		exit(1);	
	}

	freeList();
}

void *Gerenciador(void *a) {
	int menorTempoProx, pidDoMenor;
	int i;
	Node cab;
	Node removido;
	initQueue();

	struct timeval inicio = *((struct timeval*) a);

	while (deadProcs < nProcs) {
		menorTempoProx = 100;
		int tempoProx;

		for (i = 0; i < nProcs; i++) {
			if (tabelaProcessos[i].end == 1)
				continue;

			cab = tabelaProcessos[i].listaTrace;
			
			if (emptyNodeList(cab)) {
				printf("Lista vazia ? Indice estranho: %d\n", i);
				exit(0);
			}

			tempoProx = cab->next->t;

			if (tempoProx < menorTempoProx) {
				menorTempoProx = tempoProx;
				pidDoMenor = i; // proprio indice eh o pid
			}	
		}

		// dorme ate o tempo mais proximo
		while (tempoDesdeInicio(inicio) < menorTempoProx)
			usleep(500000);
		
		cab = tabelaProcessos[pidDoMenor].listaTrace;
		removido = removeNodeList(cab);
			
		// alocação do processo
		if (tabelaProcessos[pidDoMenor].start == 0) {
			tabelaProcessos[pidDoMenor].start = 1;

			int inicio;
			int nbytes = tabelaProcessos[pidDoMenor].nbytes;
	        
	        // aloca por unidades de alocação = 1 pagina
	        alocaEspacoLivre(nbytes/16, pidDoMenor);

	    	// ja precisa ter o link definido após alocação 
			inicio = tabelaProcessos[pidDoMenor].myLink->base;
	        escreveNoArquivoVirtual((char) pidDoMenor, inicio * 16, nbytes);
			
			sem_wait(&mutexPrint);
			printf("[PROCESSO %d ALOCADO].\n", pidDoMenor);
			sem_post(&mutexPrint);
		}

		// acesso a posicao (pagina)
		else if (!emptyNodeList(cab)) {
			// escreveNoArquivoReal();
			alocaQuadro(tabelaProcessos[pidDoMenor].myLink, removido->p);

			sem_wait(&mutexPrint);
			printf("[PROCESSO %d ACESSOU POSICAO %d].\n", pidDoMenor, removido->p);
			sem_post(&mutexPrint);
		}

		// desalocação do processo
		else {
			int nbytes = tabelaProcessos[pidDoMenor].nbytes;
			int inicio = tabelaProcessos[pidDoMenor].myLink->base;			
			
			// ja tem o link, basta remover da memoria
			escreveNoArquivoVirtual((char)-1, inicio*16, nbytes);
			removeProcess(tabelaProcessos[pidDoMenor].myLink);
			
			tabelaProcessos[pidDoMenor].end = 1;
			deadProcs++;
			
			sem_wait(&mutexPrint);
			printf("[PROCESSO %d DESALOCADO].\n", pidDoMenor);
			sem_post(&mutexPrint);
		}
	}

	return NULL;
}

static void inicializaGlobais() {
	deadProcs = 0;

	if (sem_init(&mutexPrint, 0, 1)) {
		fprintf(stderr, "ERRO ao criar semaforo mutexPrint\n");
		exit(0);
	}
}

void alocaEspacoLivre(int tamanho, int pid) {
	switch(numGerEspLiv) {
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
	struct timeval inicio;

	while (deadProcs < nProcs) {
		gettimeofday(&inicio, NULL);

		// (int)(intervalo-wait)*1000000 ?
		while ((wait = tempoDesdeInicio(inicio)) < intervalo) 
			usleep(10000);

		sem_wait(&mutexPrint);
		printf("\n--------------------- Status da memoria: ---------------------\n");
		printList();
		imprimeMemoriaVirtual();
		printf("\n--------------------------------------------------------------\n");
		sem_post(&mutexPrint);
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

int compare_arrive(const void *a, const void *b) {
	Process *x = (Process *) a;
	Process *y = (Process *) b;
	if (x->t0 < y->t0) return -1;
	else if (x->t0 > y->t0) return 1;
	else return 0;
}

void* Malloc(size_t bytes) {
	void* p = malloc(bytes);

	if (!p) {
		fprintf(stderr, "Memoria insuficiente!\n");
		exit(0);
	}

	return p;
}

/*************** LISTA para os P's do arqEntrada **********************/

Node initNodeList() {
	Node cab = Malloc(sizeof(*cab));
	
	cab->p = -1;
	cab->t = -1;
	cab->next = NULL;

	return cab;	
}

Node insertNodeList(Node ant, int p, int t) {
	Node novo = Malloc(sizeof(*novo));
	novo->p = p;
	novo->t = t;

	//novo->next = aux->next;
	novo->next = NULL;
	ant->next = novo;

	return novo;
}

Node removeNodeList(Node cab) {	
	Node removido;

	if (!emptyNodeList(cab)) {
		removido = cab->next;
		cab->next = removido->next;
	} else {
		printf("Não era pra estar vazia a lista!\n");
		exit(0);
	}

	return removido;
}

int emptyNodeList(Node cab) {
	return cab->next == NULL;
}