#ifndef PROMPT_H 
#define PROMPT_H

#include "linkedList.h"


/*********************************************/		//VERIFICAR ONDE COLOCAR ISSO DAQUI, DEPOIS!!!
#define NMAX_PROCS 256

typedef struct {
	int b;
	int t0, tf, pid;
	char nome[50];
	Link myLink;		// ponteiro para a posicao da memoria alocada para o processo
} PROCESS;

/*********************************************/
PROCESS trace[NMAX_PROCS];

int memTotal, memVirtual;
int numGerEspLiv, numSubsPag;
float intervalo;
int nProcs;

void shell();

#endif