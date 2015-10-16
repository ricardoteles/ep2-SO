#ifndef LINKEDLIST_H 
#define LINKEDLIST_H

typedef struct segmento* Link;

typedef struct segmento {
	char info;    // L ou P
	int base;
	int tamanho;
	Link prox;
	Link ant;
} Segmento;

Link initList(int totalMemoria);
void insertItemList(Link anterior, char info, int base, int tamanho);
void removeItemList(Link removido);
void printList(Link head);

#endif