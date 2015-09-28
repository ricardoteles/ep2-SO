#include <stdio.h>
#include "linkedList.h"
#include "process.h"
#include "memoryManager.h"

Link inicioNextFit;


void simulador(int numGerEspLiv){
	initList(13);

	/* inicializacao de um caso teste*/
	firstFit(3);
	firstFit(2);
	firstFit(2);
	firstFit(4);
	firstFit(1);

	removeProcess(head->prox->prox);
	removeProcess(head->prox->prox->prox->prox);
	printList();
	/********************************/

	if(numGerEspLiv == 1){
		printf("First Fit!!!\n");

		firstFit(3);
		firstFit(1);
		firstFit(1);
	
		printList();
	}
	else if(numGerEspLiv == 2){
		printf("Next Fit!!!\n");
		
		inicioNextFit = head->prox;

		nextFit(3);
		nextFit(1);
		nextFit(1);

		printList();
	}
}

void firstFit(int tamanho) {
	Link aux;

	for(aux = head->prox; aux != tail; aux = aux->prox) {
		if(aux->info == 'L') {
			if(insertProcess(aux, tamanho))	break;
		}
	}
}

void nextFit(int tamanho) {
	Link aux = inicioNextFit;

	do{
		if(aux->info == 'L') {					/* aux nunca sera o head e nem o tail*/
			if(insertProcess(aux, tamanho)) {	
				inicioNextFit = aux;
				break;
			}
		}

		aux = aux->prox;

		if(aux == tail) aux = head->prox;

	} while(aux != inicioNextFit);	
}