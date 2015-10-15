#include "paginacao.h"
#include "simulador.h"
#include <stdio.h>

static int mapeiaPosicaoProcesoParaPagina(Link proc, int p);
static int firstFitMemReal();
static void substituiPagina();
static void imprimeQuadro();

void alocaQuadro(Link proc, int p){
	int indiceQuadro = firstFitMemReal();
	int indicePagina = mapeiaPosicaoProcesoParaPagina(proc, p);

	imprimeQuadro();

	if(indiceQuadro != -1){
		pagina[indicePagina] = indiceQuadro;
		quadrosUsados[indiceQuadro] = 1;
		printf("Indice do Quadro: %d\n", indiceQuadro);
	}
	else{
		substituiPagina();
	}
}

static void substituiPagina(){
	switch(numSubsPag){
		case 1:	//NRU
				printf("NRU\n");
				break;
		case 2: // FIFO();
				printf("FIFO\n");
				break;
		case 3: //SecondChance();
				printf("SecondChance\n");
				break; 
		case 4: //LRU
				printf("LRU\n");
				break;
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