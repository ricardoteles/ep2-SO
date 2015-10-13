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

Link inicioNextFit;

void firstFit(int tamanho);
void nextFit(int tamanho);

void initList(int totalMemoria);
void splitHoleInPL(Link aux, int tamanho);
void insertItemList(Link aux, char info, int base, int tamanho);
void removeItemList(Link aux, Link rem);
void printList();
Link mallocItemList();

void *Processo(void *a);
int insertProcess(Link aux, int tamanho);
void removeProcess(Link aux);

/********************* MAIN ****************************************/

int main(int argc, char* argv[]){
	initList(13);

	/* inicializacao de um caso teste*/
	firstFit(3);
	firstFit(2);
	firstFit(2);
	firstFit(4);
	firstFit(1);

	removeProcess(head->prox->prox);
	removeProcess(head->prox->prox->prox->prox);
	printList();
	/********************************/

	if(argc == 2 && atoi(argv[1]) == 1){
		printf("First Fit!!!\n");

		firstFit(3);
		firstFit(1);
		firstFit(1);
	
		printList();
	}
	else if(argc == 2 && atoi(argv[1]) == 2) {
		printf("Next Fit!!!\n");
		
		inicioNextFit = head->prox;

		nextFit(3);
		nextFit(1);
		nextFit(1);

		printList();
	}
	else {
		printf("Ta errado sua anta!!!\n");
		exit(-1);
	}

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

void firstFit(int tamanho) {
	Link aux;

	for(aux = head->prox; aux != tail; aux = aux->prox) {
		if(aux->info == 'L') {
			if(insertProcess(aux, tamanho))	break;
		}
	}
}

void nextFit(int tamanho) {
	Link aux = inicioNextFit;

	do{
		if(aux->info == 'L') {					/* aux nunca sera o head e nem o tail*/
			if(insertProcess(aux, tamanho)) {	
				inicioNextFit = aux;
				break;
			}
		}

		aux = aux->prox;

		if(aux == tail) aux = head->prox;

	} while(aux != inicioNextFit);	
}

int insertProcess(Link aux, int tamanho) {
	if(aux->tamanho == tamanho) {
		aux->info = 'P'; // ocupa toda lacuna
		return 1;
	}
	else if(aux->tamanho > tamanho) {
		splitHoleInPL(aux, tamanho);
		return 1;
	}

	return 0;
}

void removeProcess(Link meio) {
	Link esq = meio->ant;
 	Link dir = meio->prox;

	if(esq->info == 'P' && dir->info == 'P') {		/* PPP vira PLP */
		meio->info = 'L';
	}
	else if(esq->info == 'P' && dir->info == 'L') {	/* PPL vira PL */
		meio->info = 'L';
		meio->tamanho += dir->tamanho;

		removeItemList(meio, dir);
	}
	else if(esq->info == 'L' && dir->info == 'P') {	/* LPP vira LP */
		esq->tamanho += meio->tamanho;

		removeItemList(esq, meio); 
	}
	else if(esq->info == 'L' && dir->info == 'L') {	/* LPL vira L */
		esq->tamanho = esq->tamanho + meio->tamanho + dir->tamanho;

		removeItemList(meio, dir); 
		removeItemList(esq, meio); 
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

void removeItemList(Link aux, Link rem) {
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


// modelo de processo abandonado 
void *Processo(void *a) {
	int* id = (int*) a;
	int pid = (*id);
	Node aux = tabelaProcessos[pid].listaTrace->next;

	sem_wait(&semThread[pid]);

	while (tempoDesdeInicio(inicioProg) < tabelaProcessos[pid].tf){
		if(aux == NULL){
			while (tempoDesdeInicio(inicioProg) < tabelaProcessos[pid].tf) usleep(50000);
			break;
		}

		while (tempoDesdeInicio(inicioProg) < aux->t) usleep(50000);
	
		// sem_wait(&mutex);
		// printf("Eu sou o %s. p = %d t = %f \n", tabelaProcessos[pid].nome, aux->p, tempoDesdeInicio(inicioProg));
		// sem_post(&mutex);
	
		aux = aux->next;
	}
	
	// printf("Eu sou o %s.	tf = %f (ACABEI)\n", tabelaProcessos[pid].nome, tempoDesdeInicio(inicioProg));

	sem_wait(&mutex);
	deadProcs++;
	sem_post(&mutex);

	return NULL;
}