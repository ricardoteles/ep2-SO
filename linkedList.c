#include "linkedList.h"

void initList(int totalMemoria) {
	inicio = (Link) mallocSeguro(sizeof(Segmento));
	inicio->info = 'L';
	inicio->base = 0;
	inicio->tamanho = totalMemoria;	
	inicio->next = NULL;
}

void insertProcessList(int tamanho) {
	Link aux;

	for(aux = inicio; aux != NULL; aux = aux->prox) {
		if(aux->info == 'L') {
			if(aux->tamanho == tamanho) {
				aux->info = 'P'; // ocupa toda lacuna
			}
			else if(aux->tamanho > tamanho) {
				splitSegment_L_in_PL(aux, tamanho);
			}
		}
	}
}

void splitSegment_L_in_PL(Link aux, int tamanho) {
	int tamanhoAntigo = aux->tamanho;

	aux->info = 'P';
	aux->tamanho = tamanho;

	insertList(aux, 'L', aux->base + aux->tamanho, tamanhoAntigo - aux->tamanho);
}

void insertList(Link ant, char info, int base, int tamanho) {
	Link novo = (Link) mallocSeguro(sizeof(Segmento));
	novo->info = info;
	novo->base = base;
	novo->tamanho = tamanho;

	novo->prox = aux->prox;
	aux->prox = novo;
}