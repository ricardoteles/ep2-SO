#ifndef PAGINACAO_H
#define PAGINACAO_H

#include "linkedList.h"

typedef struct quadro* LinkQ;

struct quadro{
	int num;
	int bitR;
	int contador;
	LinkQ prox;
} Quadro;

LinkQ headQ, tailQ;

void alocaQuadro(Link proc, int p, int pid);
void desalocaQuadros(int base, int tam);

int FIFO();
int SecondChance();
int NRU();
int LRU();

void initQueue();

#endif