#include <stdio.h>
#include "paginacao.h"
#include "simulador.h"

static int substituiPagina();
static int firstFitMemReal();
static int mapeiaPosicaoProcesoParaPagina(Link proc, int p);

static void insertItemQueue(LinkQ aux, int num, int bitR);
static int removeItemQueue(LinkQ aux);


void alocaQuadro(Link proc, int p, int pid){
	int indiceQuadro;
	int indicePagina = mapeiaPosicaoProcesoParaPagina(proc, p);
	int i;

	if(pagina[indicePagina] == -1){						/*pagina nao referenciada*/
		indiceQuadro = firstFitMemReal();
	
		if(indiceQuadro == -1){							/*memFisica lotada*/
			indiceQuadro = substituiPagina();

			for(i = 0; i < (memVirtual/16); i++){		/*seta a pagina antiga para -1*/
				if(pagina[i] == indiceQuadro) {
					pagina[i] = -1;
				}
			}		
		}
		
		pagina[indicePagina] = indiceQuadro;
		quadrosUsados[indiceQuadro] = 1;
		escreveNoArquivoFisico((char) pid, indiceQuadro*16, 16);
		insertItemQueue(tailQ, indiceQuadro, 1);
	}	
}

void desalocaQuadros(int base, int tam) {
	int i;
	LinkQ aux;

	for(i = (base/16); i < (base+tam)/16; i++){

		if(pagina[i] != -1){					/*desaloca*/
			for(aux = headQ; aux->prox != NULL; aux = aux->prox){
				if(aux->prox->num == pagina[i]){ 
					removeItemQueue(aux);
					break;
				}
			}	

			quadrosUsados[pagina[i]] = 0;
			escreveNoArquivoFisico((char) -1, pagina[i]*16, 16);
			
			pagina[i] = -1;			
		}
	}
}

static int substituiPagina(){

	switch(numSubsPag){
		case 1:	
				return NRU();

		case 2: 
				return FIFO();

		case 3:
				return SecondChance();
			
		case 4: return LRU();
			
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


int NRU(){	
	int pag = 0;
	LinkQ aux;

	for (aux = headQ; aux->prox != NULL; aux = aux->prox) {
		if (aux->prox->bitR == 0) { 
			pag = removeItemQueue(aux);
			printf("[NRU] Pag: %d\n", pag);
			return pag;
		}
	}

	pag = removeItemQueue(headQ);
	printf("[NRU] Pag: %d\n", pag);
	
	return pag;
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

int LRU(){ 
	return 0;
}

/********************* Lista ligada simples para os quadros de PAginas ******************************/
void initQueue() {
	headQ = Malloc(sizeof(*headQ));
	
	headQ->num = -1;
	headQ->prox = NULL;
	tailQ = headQ;
}

static void insertItemQueue(LinkQ aux, int num, int bitR) {
	LinkQ novo = Malloc(sizeof(*novo));
	novo->num = num;
	novo->bitR = bitR;
	
	novo->prox = aux->prox;
	aux->prox = novo;

	if(aux == tailQ){
		tailQ = novo;
	}
}

static int removeItemQueue(LinkQ aux) {
	LinkQ rem = aux->prox;
	int num;

	aux->prox = rem->prox;
	rem->prox = NULL;
	
	num = rem->num;

	free(rem); 

	return num;
}