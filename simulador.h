#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "linkedList.h"

#define NMAX_PROCS 256  /* numero maximo de processos permitidos (1 BYTE) */

typedef struct position* Node;

typedef struct position {
	int p, t;
	Node next;
} Position;

typedef struct {
	int t0, tf, pid, b;
	char nome[50];
	Node listaTrace;
	Link myLink;		// ponteiro para o processo alocado, na lista
	int start, end;
	int nbytes;  
} Process; // nome trace parece melhor :)


/***************  VARIAVEIS DE ENTRADA DO SIMULADOR ***************************/
Process tabelaProcessos[NMAX_PROCS];
int memTotal, memVirtual;
int numGerEspLiv, numSubsPag;
float intervalo;
int nProcs;

void simulador();

#endif