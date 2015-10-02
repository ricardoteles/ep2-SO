#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include "prompt.h"

#define LINMAX 10
#define COLMAX 50

int interpretaComandosShell();
void limpaMatriz();
void parserCommandShell(char *line);
void leArquivoEntrada();

FILE* arqEntrada;
char word[LINMAX][COLMAX];

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
		leArquivoEntrada();

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

void leArquivoEntrada() {
	int i = 0;

	fscanf(arqEntrada,"%d %d", &memTotal, &memVirtual); 

	while (fscanf(arqEntrada,"%d %s %d %d", &trace[i].t0, trace[i].nome, 
		&trace[i].tf, &trace[i].b) != EOF) {		
		i++;
	}

	nProcs = i;
}