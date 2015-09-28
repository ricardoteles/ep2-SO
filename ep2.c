#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "memoryManager.h"

#define LINMAX 10
#define COLMAX 50

FILE* arqEntrada;
int numGerEspLiv, numSubsPag;
float intervalo;

char word[LINMAX][COLMAX];
struct timeval inicio;

void shell();
int interpretaComandosShell();
/******************* UTILS **************************/
void parserArgumentosEntrada(int argc, char* argv[]);
void limpaMatriz();
void parserCommandShell(char *line);
float tempoDesdeInicio();
/***************************************************/

int main(int argc, char* argv[]) {
	parserArgumentosEntrada(argc, argv);

	return 0;
}

void shell() {
	printf("\n--------------------- SHELL EP2 ---------------------\n\n");
	char* line;
	int ret = 1;

	while (ret) {
		line = readline("[ep2]: ");
		add_history (line);
		limpaMatriz();
		parserCommandShell(line);
		ret = interpretaComandosShell();
	}
}

int interpretaComandosShell() {
	if (strcmp(word[0],"carrega") == 0) {
		arqEntrada = fopen(word[1], "r");

		if (!arqEntrada) {
			fprintf(stderr, "ERRO ao abrir o arquivo %s\n", word[1]);
		}
	}
	else if (strcmp(word[0],"espaco") == 0) {
		if(atoi(word[1]) < 1 || atoi(word[1]) > 3) {
			printf("Numero de gerenciamento de espaco livre invalido\n");
		}
		else {
			numGerEspLiv = atoi(word[1]);
		}
		
	}
	else if (strcmp(word[0], "substitui") == 0) {
		if(atoi(word[1]) < 1 || atoi(word[1]) > 4) {
			printf("Numero de substituicao de paginas invalido\n");
		}
		else {
			numSubsPag = atoi(word[1]);
		}
	}
	else if (strcmp(word[0], "executa") == 0) {
	 	if(atof(word[1]) <= 0){
			printf("Intervalo de tempo invalido\n");
		}
		else {
			intervalo = atof(word[1]);
			
			printf("Arquivo: %s\nGerencia Espaco Livre: %d\nSubstituicao Pagina: %d\nIntervalo: %f\n", 
			"", numGerEspLiv, numSubsPag, intervalo);

			simulador(numGerEspLiv);
		}
	}
	else if (strcmp(word[0], "sai") == 0) {
		return 0;
	}
	else {
		fprintf(stderr, "comando %s inválido!\n", word[0]);
	}

	return 1;
}

/******************* UTILS **************************/
void parserArgumentosEntrada(int argc, char* argv[]) {
	if(argc == 1) {
		shell();
	}

	/*else if (argc == 5) {			
		arqEntrada = fopen(argv[1], "r");
		numGerEspLiv = atoi(argv[2]);
		numSubsPag = atoi(argv[3]);
		intervalo = atof(argv[4]);

		if (!arqEntrada) {
			fprintf(stderr, "ERRO ao abrir o arquivo %s\n", argv[2]);
			exit(0);
		}

		printf("Arquivo: %s\nGerencia Espaco Livre: %d\nSubstituicao Pagina: %d\nIntervalo: %f\n", 
			argv[1], numGerEspLiv, numSubsPag, intervalo);
	} */
	else {
		printf("Formato esperado:\n./ep2\n");
		exit(0);
	}
}

void limpaMatriz() {
	int i, j;

	for (i = 0; i < LINMAX; i++) {
		for (j = 0; j < COLMAX; j++) {
			word[i][j] = 0;
		}
	}
}

void parserCommandShell(char *line) {
	int i, lin = 0, col = 0;

	for(i = 0; line[i] != '\0'; i++) {
		if(line[i] != ' ') {
			word[lin][col++] = line[i];
		}
		else if(col != 0) {
			lin++;
			col = 0;
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