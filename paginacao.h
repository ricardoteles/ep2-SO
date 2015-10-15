#ifndef PAGINACAO_H
#define PAGINACAO_H

#include "linkedList.h"

typedef struct quadro* LinkQ;

struct quadro{
	int num;
	int bitR;
	LinkQ prox;
} Quadro;

LinkQ headQ, tailQ;

void initQueue();
void insertItemQueue(LinkQ aux, int num, int bitR);
void printQueue();
LinkQ mallocItemQueue();
int removeItemQueue(LinkQ aux);

int FIFO();
int SecondChance();
int NRU();
int LRU();

void alocaQuadro(Link proc, int p);

#endif