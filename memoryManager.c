#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkedList.h"
#include "process.h"

struct timeval inicio;

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

float tempoDesdeInicio(struct timeval inicio) {
	struct timeval fim;
	float timedif;

	gettimeofday(&fim, NULL);
	timedif = (float)(fim.tv_sec - inicio.tv_sec);
	timedif += (float)(fim.tv_usec - inicio.tv_usec)/1000000;

	return timedif;
}