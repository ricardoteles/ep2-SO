#include <stdio.h>
#include <stdlib.h>

typedef struct segmento* Link;

struct segmento{
	char info;
	int base;
	int tamanho;
	Link prox;
	Link ant;
} Segmento;

Link head, tail;

void initList(int totalMemoria);
void splitHoleInPL(Link aux, int tamanho);
void insertItemList(Link aux, char info, int base, int tamanho);
void removeList(Link aux, Link rem);
void printList();
Link mallocItemList();

void insertProcess(int tamanho);
void removeProcess(Link aux);

/********************* MAIN ****************************************/

int main(){
	initList(100);

	insertProcess(20);
	insertProcess(50);
	insertProcess(15);
	insertProcess(5);
	printList();


	removeProcess(head->prox);
	printList();

	removeProcess(head->prox->prox->prox);
	printList();
	
	removeProcess(head->prox->prox);
	printList();

	removeProcess(head->prox->prox);
	printList();
	return 0;
}

/********************* FUNCOES ****************************************/
void initList(int totalMemoria) {
	Link novo = mallocItemList();
	head = mallocItemList();
	tail = mallocItemList();
	
	head->info = 'P';
	head->base = -1;
	head->tamanho = -1;	
	head->ant = NULL;
	head->prox = tail;
	
	tail->info = 'P';
	tail->base = -1;
	tail->tamanho = -1;
	tail->ant = head;
	tail->prox = NULL;

	insertItemList(head, 'L', 0, totalMemoria);	
}

void insertProcess(int tamanho) {
	Link aux;

	for(aux = head->prox; aux != tail; aux = aux->prox) {
		if(aux->info == 'L') {
			if(aux->tamanho == tamanho) {
				aux->info = 'P'; // ocupa toda lacuna
				break;
			}
			else if(aux->tamanho > tamanho) {
				splitHoleInPL(aux, tamanho);
				break;
			}
		}
	}
}

void removeProcess(Link meio){
	Link esq = meio->ant;
 	Link dir = meio->prox;

	if(esq->info == 'P' && dir->info == 'P') {		/* PPP vira PLP */
		meio->info = 'L';
	}
	else if(esq->info == 'P' && dir->info == 'L') {	/* PPL vira PL */
		meio->info = 'L';
		meio->tamanho += dir->tamanho;

		removeList(meio, dir);
	}
	else if(esq->info == 'L' && dir->info == 'P') {	/* LPP vira LP */
		esq->tamanho += meio->tamanho;

		removeList(esq, meio); 
	}
	else if(esq->info == 'L' && dir->info == 'L') {	/* LPL vira L */
		esq->tamanho = esq->tamanho + meio->tamanho + dir->tamanho;

		removeList(meio, dir); 
		removeList(esq, meio); 
	} 
}

void splitHoleInPL(Link aux, int tamanho) {
	int tamanhoAntigo = aux->tamanho;

	aux->info = 'P';
	aux->tamanho = tamanho;

	insertItemList(aux, 'L', aux->base + aux->tamanho, tamanhoAntigo - aux->tamanho);
}

void insertItemList(Link aux, char info, int base, int tamanho) {
	Link novo = mallocItemList();
	novo->info = info;
	novo->base = base;
	novo->tamanho = tamanho;

	novo->prox = aux->prox;
	aux->prox->ant = novo;
	aux->prox = novo;
	novo->ant = aux;
}

void removeList(Link aux, Link rem) {
	aux->prox = rem->prox;
	rem->prox->ant = aux;

	rem->prox = NULL;
	rem->ant = NULL;

	free(rem); 
}

void printList() {
	Link aux;

	printf("Lista: \n");
	for(aux = head->prox; aux != tail; aux = aux->prox) {
		printf("%c %d %d\n", aux->info, aux->base, aux->tamanho);
	}
	printf("FIM\n\n");
}

Link mallocItemList() {
	Link p = (Link) malloc(sizeof(Segmento));
	if (!p) {
		fprintf(stderr, "Memoria insuficiente!\n");
		exit(1);
	}

	return p;
}