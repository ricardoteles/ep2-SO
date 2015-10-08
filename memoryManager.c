#include <stdlib.h>
#include "process.h"
#include "linkedList.h"
#include "memoryManager.h"

void firstFit(int tamanho, int pid) {
	Link aux;

	for(aux = head->prox; aux != tail; aux = aux->prox) {
		if(aux->info == 'L') {
			if(insertProcess(aux, tamanho, pid)) break;
		}
	}
}

void nextFit(int tamanho, int pid) {
	static Link inicioNextFit = NULL;
	
	if (!inicioNextFit) 
	 	inicioNextFit = head->prox;

	Link aux = inicioNextFit;

	do {
		if(aux->info == 'L') {					/* aux nunca sera o head e nem o tail*/
			if(insertProcess(aux, tamanho, pid)) {	
				inicioNextFit = aux;
				break;
			}
		}

		aux = aux->prox;

		if(aux == tail) aux = head->prox;

	} while (aux != inicioNextFit);	
}