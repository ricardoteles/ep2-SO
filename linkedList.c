#include "linkedList.h"
#include "simulador.h"
#include <stdlib.h>
#include <stdio.h>

Link initList(int totalMemoria) {
	Link head = Malloc(sizeof(*head));
	Link tail = Malloc(sizeof(*tail));
	
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

	return head;
}

void insertItemList(Link anterior, char info, int base, int tamanho) {
	Link novo = Malloc(sizeof(*novo));
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

void printList(Link head) {
	Link aux;

	printf("Lista: [HEAD] -> ");
	for(aux = head->prox; aux->prox != NULL; aux = aux->prox) {
		printf("[%c | %d | %d] -> ", aux->info, aux->base, aux->tamanho);
	}
	printf("[TAIL]\n\n");
}