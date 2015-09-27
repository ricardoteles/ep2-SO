#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedList.h"

struct timeval inicio;

void insertProcessList(int tamanho);
float tempoDesdeInicio();

/*********** GERENCIAMENTO DE MEMORIA ***************/
int main() {
	gettimeofday(&inicio, NULL);

	/*while(tempoDesdeInicio(inicio) < intervalo){
		printf("Oiiii\n");
	}*/

	printf("Devemos simular os algoritmos de memória seus manganões!\n");

	return 0;
}

void insertProcessList(int tamanho) {
	Link aux;

	for(aux = head; aux != NULL; aux = aux->prox) {
		if(aux->info == 'L') {
			if(aux->tamanho == tamanho) {
				aux->info = 'P'; // ocupa toda lacuna
			}
			else if(aux->tamanho > tamanho) {
				splitHoleInPL(aux, tamanho);
			}
		}
	}
}

float tempoDesdeInicio(struct timeval inicio) {
	struct timeval fim;
	float timedif;

	gettimeofday(&fim, NULL);
	timedif = (float)(fim.tv_sec - inicio.tv_sec);
	timedif += (float)(fim.tv_usec - inicio.tv_usec)/1000000;

	return timedif;
}