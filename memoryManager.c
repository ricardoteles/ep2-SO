#include <stdlib.h>
#include <math.h>
#include "process.h"
#include "linkedList.h"
#include "memoryManager.h"

#define SIZE_QUICK 10 

typedef struct qt* LinkQT;

typedef struct qt{
	Link p;
	LinkQT nextQT;
} QT;

static QT quickTable[SIZE_QUICK];

void firstFit(Link head, int tamanho, int pid) {
	Link aux;

	for (aux = head->prox; aux->prox != NULL; aux = aux->prox) {
		if (aux->info == 'L') {
			if (insertProcess(aux, tamanho, pid)) break;
		}
	}
}

void nextFit(Link head, int tamanho, int pid) {
	static Link inicioNextFit = NULL;
	
	if (!inicioNextFit) 
	 	inicioNextFit = head->prox;

	Link aux = inicioNextFit;

	do {
		if (aux->info == 'L') {					/* aux nunca sera o head e nem o tail*/
			if (insertProcess(aux, tamanho, pid)) {	
				inicioNextFit = aux;
				break;
			}
		}

		aux = aux->prox;

		if (aux->prox == NULL) aux = head->prox;

	} while (aux != inicioNextFit);	
}

void quickFit(int tamanho, int pid) {
	
}

void inicializaTabelaQuick() {
	int i;

	for (i = 1; i < SIZE_QUICK; i++) {
		quickTable[i].nextQT = NULL;
	}
}

void inserePonteiroTabelaQuick(int tamanhoLacuna, Link p){
	int tamanho, i;
	LinkQT novo = Malloc(sizeof(*novo));

	for(i = 0; i < SIZE_QUICK; i++){
		tamanho = pow(2, i)*16;

		if(tamanhoLacuna <= tamanho){
			novo->p = p;
			novo->nextQT = quickTable[i].nextQT;
			quickTable[i].nextQT = novo;
		}
	}
}

void removePonteiroTabelaQuick(int tamAntigo, Link p){
	int i, tamanho;
	LinkQT aux, rem;

	for(i = 0; i < SIZE_QUICK; i++){
		tamanho = pow(2, i)*16;

		if(tamAntigo <= tamanho){
			for(aux = quickTable[i].nextQT; aux != NULL; aux = aux->nextQT){
				if(aux->nextQT->p == p){
					rem = aux->nextQT;
					aux = rem->nextQT;
					free(rem);
					break;
				}
			}
		}
	}
}