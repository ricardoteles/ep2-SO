#include <stdio.h>
#include "paginacao.h"
#include "simulador.h"

static int mapeiaPosicaoProcesoParaPagina(Link proc, int p);
static int firstFitMemReal();
static int substituiPagina();
static void imprimeQuadro();

void alocaQuadro(Link proc, int p){
	int indiceQuadro = firstFitMemReal();
	int indicePagina = mapeiaPosicaoProcesoParaPagina(proc, p);

	if(indiceQuadro == -1){
		indiceQuadro = substituiPagina();
	}

	pagina[indicePagina] = indiceQuadro;
	quadrosUsados[indiceQuadro] = 1;
	insertItemQueue(tailQ, indiceQuadro, 1);
}

static int substituiPagina(){

	switch(numSubsPag){
		case 1:	printf("NRU\n");
				return NRU();

		case 2: printf("FIFO\n");
				return FIFO();

		case 3: printf("SecondChance\n");
				return SecondChance();
			
		case 4: return LRU();
				printf("LRU\n");
	}
}

static int firstFitMemReal(){
	int i;

	for(i = 0; i < (memTotal/16); i++){
		if(quadrosUsados[i] == 0) {
			return i;
		}
	}

	return -1;
}

static int mapeiaPosicaoProcesoParaPagina(Link proc, int p){
	return (proc->base + p)/16;
}

static void imprimeQuadro(){
	int i;

	printf("Quadros: ");
	for(i = 0; i < (memTotal/16); i++){
		printf("%d ", quadrosUsados[i]);
	}
	printf("\n");
}

int NRU(){	/*TO DO: precisa implementar*/
	return 0;
}

int FIFO(){
	return removeItemQueue(headQ);
}

int SecondChance(){
	LinkQ aux;
	int num;

	for(aux = headQ->prox; ; aux = headQ->prox){
		if(aux->bitR == 1){
			num = removeItemQueue(headQ);			
			insertItemQueue(tailQ, num, 0);
		}
		else{
			return FIFO();
		}
	}
}

int LRU(){  /*TO DO: precisa implementar*/
	return 0;
}

/********************* FUNCOES ****************************************/
void initQueue() {
	headQ = mallocItemQueue();
	
	headQ->num = -1;
	headQ->prox = NULL;
	tailQ = headQ;
}

void insertItemQueue(LinkQ aux, int num, int bitR) {
	LinkQ novo = mallocItemQueue();
	novo->num = num;
	novo->bitR = bitR;
	
	novo->prox = aux->prox;
	aux->prox = novo;

	if(aux == tailQ){
		tailQ = novo;
	}
}

void printQueue() {
	LinkQ aux;

	printf("Queue: \n");
	for(aux = headQ->prox; aux != NULL; aux = aux->prox) {
		printf("%d  ", aux->num);
	}
	printf("FIM\n\n");
}

LinkQ mallocItemQueue() {
	LinkQ p = (LinkQ) malloc(sizeof(Quadro));
	if (!p) {
		fprintf(stderr, "Memoria insuficiente!\n");
		exit(1);
	}

	return p;
}

int removeItemQueue(LinkQ aux) {
	LinkQ rem = aux->prox;
	int num;

	aux->prox = rem->prox;
	rem->prox = NULL;
	
	num = rem->num;

	free(rem); 

	return num;
}