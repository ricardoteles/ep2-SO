#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

void initList(int totalMemoria) {
	head = (Link) mallocItemList();
	head->info = 'L';
	head->base = 0;
	head->tamanho = totalMemoria;	
	head->prox = NULL;
}

void splitHoleInPL(Link aux, int tamanho) {
	int tamanhoAntigo = aux->tamanho;

	aux->info = 'P';
	aux->tamanho = tamanho;

	insertItemList(aux, 'L', aux->base + aux->tamanho, tamanhoAntigo - aux->tamanho);
}

void setContentItemList(Link p, char info, int base, int tamanho) {
	p->info = info;
	p->base = base;
	p->tamanho = tamanho;
}

void insertItemList(Link ant, char info, int base, int tamanho) {
	Link novo = mallocItemList();
	novo->info = info;
	novo->base = base;
	novo->tamanho = tamanho;

	novo->prox = ant->prox;
	ant->prox = novo;
}

Link mallocItemList() {
	Link p = (Link) malloc(sizeof(Segmento));
	if (!p) {
		fprintf(stderr, "Memoria insuficiente!\n");
		exit(1);
	}

	return p;
}