#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "inicializacao.h"

struct timeval inicio;
sem_t mutex;

void simulador(int numGerEspLiv);
void *Processo(void *a);
int compare_arrive(const void *a,const void *b);
void parserArgumentosEntrada(int argc, char* argv[]);
float tempoDesdeInicio();


int main(int argc, char* argv[]) {
	parserArgumentosEntrada(argc, argv);

	return 0;
}

void simulador(int numGerEspLiv){
	initList(memTotal);

	pthread_t procs[NMAX_PROCS];
	long i;
	int pos;

	qsort(trace, nProcs, sizeof(PROCESS), compare_arrive);
	
	for(pos = 0; pos < nProcs; pos++) {
		trace[pos].pid = pos;	
	}

	if (sem_init(&mutex, 0, 1)) {
		fprintf(stderr, "ERRO ao criar semaforo mutexQueue\n");
		exit(0);
	}

	gettimeofday(&inicio, NULL);
	
	for (i = 0; i < nProcs; i++) {
		while (tempoDesdeInicio(inicio) < trace[i].t0) usleep(50000);	// TODO: ver tempo inteiro
		
		if (pthread_create(&procs[i], NULL, Processo, (void *) &trace[i].pid)) {
            printf("\n ERROR creating thread procs[%ld]\n", i);
            exit(1);
        }
	}
	
	for (i = 0; i < nProcs; i++) {
        if (pthread_join(procs[i], NULL)) {
			printf("\n ERROR joining thread procs[%ld]\n", i);
			exit(1);
        }
    }

    printf("\n\nAgora vem a lista\n\n");
    printList();
}


			

void *Processo(void *a) {
	int* id = (int*) a;
	int pid = (*id);


	sem_wait(&mutex);
	printf("Ola eu sou a thread: %d\n", pid);
	firstFit(trace[pid].b, pid);
	sem_post(&mutex);

	while(tempoDesdeInicio(inicio) < trace[pid].tf) usleep(50000);

	if(pid != 5) removeProcess(trace[pid].myLink, pid);	//TODO: analisar esse caso

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

	/*else if (argc == 5) {			
		arqEntrada = fopen(argv[1], "r");
		numGerEspLiv = atoi(argv[2]);
		numSubsPag = atoi(argv[3]);
		intervalo = atof(argv[4]);

		if (!arqEntrada) {
			fprintf(stderr, "ERRO ao abrir o arquivo %s\n", argv[2]);
			exit(0);
		}

		printf("Arquivo: %s\nGerencia Espaco Livre: %d\nSubstituicao Pagina: %d\nIntervalo: %f\n", 
			argv[1], numGerEspLiv, numSubsPag, intervalo);
	} */
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

// void simulador(int numGerEspLiv){
// 	initList(13);

// 	/* inicializacao de um caso teste*/
// 	firstFit(3);
// 	firstFit(2);
// 	firstFit(2);
// 	firstFit(4);
// 	firstFit(1);

// 	removeProcess(head->prox->prox);
// 	removeProcess(head->prox->prox->prox->prox);
// 	printList();
// 	******************************

// 	if(numGerEspLiv == 1){
// 		printf("First Fit!!!\n");

// 		firstFit(3);
// 		firstFit(1);
// 		firstFit(1);
	
// 		printList();
// 	}
// 	else if(numGerEspLiv == 2){
// 		printf("Next Fit!!!\n");
		
// 		inicioNextFit = head->prox;

// 		nextFit(3);
// 		nextFit(1);
// 		nextFit(1);

// 		printList();
// 	}
// }