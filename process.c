#include "process.h"
#include "simulador.h"
#include <stdio.h>

static void splitHoleInPL(Link aux, int tamanho) {
	int tamanhoAntigo = aux->tamanho;

	aux->info = 'P';
	aux->tamanho = tamanho;

	insertItemList(aux, 'L', aux->base + aux->tamanho, tamanhoAntigo - aux->tamanho);
}

int insertProcess(Link inserido, int tamanho, int pid) {
	if(inserido->tamanho == tamanho) {
		inserido->info = 'P'; // ocupa toda lacuna
		tabelaProcessos[pid].myLink = inserido;
		return 1;
	}
	else if(inserido->tamanho > tamanho) {
		splitHoleInPL(inserido, tamanho);
		tabelaProcessos[pid].myLink = inserido;
		return 1;
	}

	return 0;
}

void removeProcess(Link meio) {
	if (!meio) {
		fprintf(stderr, "Link a ser removido eh NULL!\n");
		return;
	}

	Link esq = meio->ant;
	Link dir = meio->prox;

	if(esq->info == 'P' && dir->info == 'P') {		/* PPP vira PLP */
		meio->info = 'L';
	}
	else if(esq->info == 'P' && dir->info == 'L') {	/* PPL vira PL */
		meio->info = 'L';
		meio->tamanho += dir->tamanho;

		removeItemList(dir);
	}
	else if(esq->info == 'L' && dir->info == 'P') {	/* LPP vira LP */
		esq->tamanho += meio->tamanho;

		removeItemList(meio); 
	}
	else if(esq->info == 'L' && dir->info == 'L') {	/* LPL vira L */
		esq->tamanho = esq->tamanho + meio->tamanho + dir->tamanho;

		removeItemList(dir); 
		removeItemList(meio); 
	}
}