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
void insertProcessList(int tamanho);
void removeProcessList(Link aux);
void splitSegment_L_in_PL(Link aux, int tamanho);
void insertList(Link ant, char info, int base, int tamanho);
void printList();
void* mallocSeguro(size_t bytes);

/********************* MAIN ****************************************/

int main(){
	initList(100);

	insertProcessList(20);
	insertProcessList(50);
	insertProcessList(15);
	insertProcessList(5);
	printList();


	removeProcessList(head->prox);
	printList();

	removeProcessList(head->prox->prox->prox);
	printList();
	
	removeProcessList(head->prox->prox);
	printList();

	removeProcessList(head->prox->prox);
	printList();
	return 0;
}

/********************* FUNCOES ****************************************/
void initList(int totalMemoria) {
	/*head <-> novo <-> tail*/
	Link novo = (Link) mallocSeguro(sizeof(Segmento));
	head = (Link) mallocSeguro(sizeof(Segmento));
	tail = (Link) mallocSeguro(sizeof(Segmento));
	
	head->info = 'P';
	head->base = -1;
	head->tamanho = -1;	
	head->ant = NULL;
	head->prox = novo;

	novo->info = 'L';
	novo->base = 0;
	novo->tamanho = totalMemoria;	
	novo->ant = head;
	novo->prox = tail;

	tail->info = 'P';
	tail->base = -1;
	tail->tamanho = -1;
	tail->ant = novo;
	tail->prox = NULL;
}

void insertProcessList(int tamanho) {
	Link aux;

	for(aux = head->prox; aux != tail; aux = aux->prox) {
		if(aux->info == 'L') {
			if(aux->tamanho == tamanho) {
				aux->info = 'P'; // ocupa toda lacuna
				break;
			}
			else if(aux->tamanho > tamanho) {
				splitSegment_L_in_PL(aux, tamanho);
				break;
			}
		}
	}
}

void removeProcessList(Link aux){
	if(aux->ant->info == 'P' && aux->prox->info == 'P') {		/* PPP vira PLP */
		aux->info = 'L';
	}
	else if(aux->ant->info == 'P' && aux->prox->info == 'L') {	/* PPL vira PL */
		Link rem = aux->prox;

		aux->info = 'L';
		aux->tamanho += rem->tamanho;

		aux->prox = rem->prox;
		rem->prox->ant = aux;

		rem->prox = NULL;
		rem->ant = NULL;

		free(rem); 
	}
	else if(aux->ant->info == 'L' && aux->prox->info == 'P') {	/* LPP vira LP */
		aux->ant->tamanho += aux->tamanho;

		aux->ant->prox = aux->prox;
		aux->prox->ant = aux->ant;

		aux->prox = NULL;
		aux->ant = NULL;

		free(aux); 
	}
	else if(aux->ant->info == 'L' && aux->prox->info == 'L') {	/* LPL vira L */
		Link rem = aux->prox; 

		aux->ant->tamanho = aux->ant->tamanho + aux->tamanho + rem->tamanho;

		aux->ant->prox = rem->prox;
		rem->prox->ant = aux->ant;

		rem->prox = NULL;
		rem->ant = NULL;
		aux->prox = NULL;
		aux->ant = NULL;

		free(rem); 
		free(aux); 
	} 

}

void splitSegment_L_in_PL(Link aux, int tamanho) {
	int tamanhoAntigo = aux->tamanho;

	aux->info = 'P';
	aux->tamanho = tamanho;

	insertList(aux, 'L', aux->base + aux->tamanho, tamanhoAntigo - aux->tamanho);
}

void insertList(Link aux, char info, int base, int tamanho) {
	Link novo = (Link) mallocSeguro(sizeof(Segmento));
	novo->info = info;
	novo->base = base;
	novo->tamanho = tamanho;

	novo->prox = aux->prox;
	aux->prox->ant = novo;
	aux->prox = novo;
	novo->ant = aux;
}

void printList(){
	Link aux;

	printf("Lista: \n");
	for(aux = head->prox; aux != tail; aux = aux->prox) {
		printf("%c %d %d\n", aux->info, aux->base, aux->tamanho);
	}
	printf("FIM\n\n");
}

void* mallocSeguro(size_t bytes) {
	void* p = malloc(bytes);
	if (!p) {
		fprintf(stderr, "ERRO na alocação de memória!\n");
		exit(0);
	}
	return p;
}