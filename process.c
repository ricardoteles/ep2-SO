#include "linkedList.h"

void insertProcess(int tamanho) {
	Link aux;

	for(aux = head->prox; aux != tail; aux = aux->prox) {
		if(aux->info == 'L') {
			if(aux->tamanho == tamanho) {
				aux->info = 'P'; // ocupa toda lacuna
				break;
			}
			else if(aux->tamanho > tamanho) {
				splitHoleInPL(aux, tamanho);
				break;
			}
		}
	}
}

void removeProcess(Link meio){
	Link esq = meio->ant;
 	Link dir = meio->prox;

	if(esq->info == 'P' && dir->info == 'P') {		/* PPP vira PLP */
		meio->info = 'L';
	}
	else if(esq->info == 'P' && dir->info == 'L') {	/* PPL vira PL */
		meio->info = 'L';
		meio->tamanho += dir->tamanho;

		removeList(meio, dir);
	}
	else if(esq->info == 'L' && dir->info == 'P') {	/* LPP vira LP */
		esq->tamanho += meio->tamanho;

		removeList(esq, meio); 
	}
	else if(esq->info == 'L' && dir->info == 'L') {	/* LPL vira L */
		esq->tamanho = esq->tamanho + meio->tamanho + dir->tamanho;

		removeList(meio, dir); 
		removeList(esq, meio); 
	} 
}