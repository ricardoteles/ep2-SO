#include <stdlib.h>
#include "process.h"
#include "linkedList.h"
#include "memoryManager.h"

#define SIZE_QUICK 10 

typedef struct {
	int tamanho;
	Link cabList;
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
	// inicializaTabelaQuick();
}

static inicializaTabelaQuick() {
	int i;

	quickTable[0].tamanho = 16;

	for (i = 1; i < SIZE_QUICK; i++) {
		quickTable[i].tamanho = quickTable[i-1].tamanho * 2; 
	}
}