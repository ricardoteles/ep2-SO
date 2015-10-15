#include <stdio.h>
#include <stdlib.h>

typedef struct quadro* Link;

struct quadro{
	int num;
	int bitR;
	Link prox;
} Quadro;

Link head, tail;

void initList();
void insertItemList(Link aux, int num, int bitR);
void printList();
Link mallocItemList();
void removeItemList(Link aux, Link rem);

void substPagina(int numSubsPag, int quadroInserido);
void FIFO(int quadroInserido);
void SecondChance(int quadroInserido);
void NRU();

/********************* MAIN ****************************************/

int main(int argc, char* argv[]){
	initList();

	insertItemList(tail, 0, 0);
	insertItemList(tail, 1, 0);
	insertItemList(tail, 2, 0);
	
	printList();

	substPagina(2, 0);

	printList();

	/********************************/


	return 0;
}

void substPagina(int numSubsPag, int quadroInserido){
	switch(numSubsPag){
		case 1:	//NRU
				break;
		case 2: FIFO(quadroInserido);
				break;
		case 3: SecondChance(quadroInserido);
				break;
		case 4: //LRU
				break;

	}
}

void NRU(){

}

void FIFO(int quadroInserido){
	removeItemList(head, head->prox);
	insertItemList(tail, quadroInserido, 1);
}

void SecondChance(int quadroInserido){
	Link aux;
	char c;
	
	for(aux = head->prox; ; aux = aux->prox){
		if(aux->bitR == 1){
			head->prox = aux->prox;

			insertItemList(tail, aux->num, 0);
			printList();
			// c = getchar();
		}
		else{
			FIFO(quadroInserido);
			break;	
		}
	}
}

void LRU(){

}

/********************* FUNCOES ****************************************/
void initList() {
	head = mallocItemList();
	
	head->num = -1;
	head->prox = NULL;
	tail = head;
}

void insertItemList(Link aux, int num, int bitR) {
	Link novo = mallocItemList();
	novo->num = num;
	novo->bitR = bitR;
	
	novo->prox = aux->prox;
	aux->prox = novo;

	if(aux == tail){
		tail = novo;
	}
}


void printList() {
	Link aux;

	printf("Lista: \n");
	for(aux = head->prox; aux != NULL; aux = aux->prox) {
		printf("%d  ", aux->num);
	}
	printf("FIM\n\n");
}

Link mallocItemList() {
	Link p = (Link) malloc(sizeof(Quadro));
	if (!p) {
		fprintf(stderr, "Memoria insuficiente!\n");
		exit(1);
	}

	return p;
}

void removeItemList(Link aux, Link rem) {
	aux->prox = rem->prox;
	
	rem->prox = NULL;
	
	free(rem); 
}