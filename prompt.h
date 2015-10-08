#ifndef PROMPT_H 
#define PROMPT_H

#include "linkedList.h"


/*********************************************/		//VERIFICAR ONDE COLOCAR ISSO DAQUI, DEPOIS!!!
#define NMAX_PROCS 256

typedef struct trace* Node;

struct trace{
	int p, t;
	Node next;
} Trace;

typedef struct {
	int b;
	int t0, tf, pid;
	char nome[50];
	Node listaTrace;
	Link myLink;		// ponteiro para a posicao da memoria alocada para o processo
} PROCESS;

/*********************************************/
PROCESS tabelaProcessos[NMAX_PROCS];

int memTotal, memVirtual;
int numGerEspLiv, numSubsPag;
float intervalo;
int nProcs;

void shell();

/*************** LISTA para os P's do arqEntrada **********************/

Node iniciaLista();
Node insertNodeList(Node aux, int p, int t);
Node mallocNodeList();

#endif