#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

void initList(int totalMemoria) {
	head = mallocItemList();
	tail = mallocItemList();
	
	head->info = 'P';
	head->base = -1;
	head->tamanho = -1;	
	head->ant = NULL;
	head->prox = tail;
	
	tail->info = 'P';
	tail->base = -1;
	tail->tamanho = -1;
	tail->ant = head;
	tail->prox = NULL;

	insertItemList(head, 'L', 0, totalMemoria);	
}

void insertItemList(Link aux, char info, int base, int tamanho) {
	Link novo = mallocItemList();
	novo->info = info;
	novo->base = base;
	novo->tamanho = tamanho;

	novo->prox = aux->prox;
	aux->prox->ant = novo;
	aux->prox = novo;
	novo->ant = aux;
}

void removeList(Link aux, Link rem) {
	aux->prox = rem->prox;
	rem->prox->ant = aux;

	rem->prox = NULL;
	rem->ant = NULL;

	free(rem); 
}

void printList() {
	Link aux;

	printf("Lista: \n");
	for(aux = head->prox; aux != tail; aux = aux->prox) {
		printf("%c %d %d\n", aux->info, aux->base, aux->tamanho);
	}
	printf("FIM\n\n");
}

Link mallocItemList() {
	Link p = (Link) malloc(sizeof(Segmento));
	if (!p) {
		fprintf(stderr, "Memoria insuficiente!\n");
		exit(1);
	}

	return p;
}