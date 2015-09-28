#include "linkedList.h"
#include "process.h"

static void splitHoleInPL(Link aux, int tamanho) {
	int tamanhoAntigo = aux->tamanho;

	aux->info = 'P';
	aux->tamanho = tamanho;

	insertItemList(aux, 'L', aux->base + aux->tamanho, tamanhoAntigo - aux->tamanho);
}

int insertProcess(Link aux, int tamanho) {
	if(aux->tamanho == tamanho) {
		aux->info = 'P'; // ocupa toda lacuna
		return 1;
	}
	else if(aux->tamanho > tamanho) {
		splitHoleInPL(aux, tamanho);
		return 1;
	}

	return 0;
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