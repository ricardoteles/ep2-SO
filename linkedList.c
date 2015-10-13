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

void freeList() {
	free(tail);
	free(head);
	tail = NULL;
	head = NULL;
}

void insertItemList(Link anterior, char info, int base, int tamanho) {
	Link novo = mallocItemList();
	novo->info = info;
	novo->base = base;
	novo->tamanho = tamanho;

	novo->prox = anterior->prox;
	anterior->prox->ant = novo;
	anterior->prox = novo;
	novo->ant = anterior;
}

void removeItemList(Link removido) {
	Link aux = removido->ant;

	aux->prox = removido->prox;
	removido->prox->ant = aux;

	free(removido); 
	removido = NULL;
}

void printList() {
	Link aux;

	printf("HEAD: \n");
	for(aux = head->prox; aux != tail; aux = aux->prox) {
		printf("%c %d %d\n", aux->info, aux->base, aux->tamanho);
	}
	printf("TAIL\n\n");
}

Link mallocItemList() {
	Link p = (Link) malloc(sizeof(Segmento));
	if (!p) {
		fprintf(stderr, "Memoria insuficiente!\n");
		exit(1);
	}

	return p;
}