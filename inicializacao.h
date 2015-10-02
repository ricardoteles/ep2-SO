#ifndef INICIALIZACAO_H 
#define INICIALIZACAO_H

#include "linkedList.h"
#include <stdio.h>

#define LINMAX 10
#define COLMAX 50

/*********************************************/		//VERIFICAR ONDE COLOCAR ISSO DAQUI, DEPOIS!!!
#define NMAX_PROCS 256

typedef struct {
	int b;
	int t0, tf, pid;
	char nome[50];
	Link myLink;		// ponteiro para a posicao da memoria alocada para o processo
} PROCESS;

PROCESS trace[NMAX_PROCS];
/*********************************************/

FILE* arqEntrada;
int memTotal, memVirtual;
int numGerEspLiv, numSubsPag;
float intervalo;
int nProcs;

void shell();
int interpretaComandosShell();
void limpaMatriz();
void parserCommandShell(char *line);
void leArquivoEntrada();

#endif