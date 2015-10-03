#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include "prompt.h"

#define LINMAX 10
#define COLMAX 50

static int interpretaComandosShell();
static void limpaMatriz();
static void parserCommandShell(char *line);
static void leArquivoEntrada();
static void criaArquivosMemoria();
static void imprimeArquivos();

FILE* arqEntrada = NULL;
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

static void criaArquivosMemoria() {
	FILE* arqMem = fopen("/tmp/ep2.mem", "a+b");
	FILE* arqVir = fopen("/tmp/ep2.vir", "a+b");
	
	char val = -1;
	int i;

	if (!arqMem) {
		fprintf(stderr, "ERRO ao abrir o arquivo /tmp/ep2.mem .\n");
		exit(0);
	}

	if (!arqVir) {
		fprintf(stderr, "ERRO ao abrir o arquivo /tmp/ep2.vir .\n");
		exit(0);
	}

	for (i = 0; i < memTotal; i++)
		fwrite(&val, sizeof(char), 1, arqMem); 

	for (i = 0; i < memVirtual; i++)
		fwrite(&val, sizeof(char), 1, arqVir);

	fclose(arqMem);
	fclose(arqVir);
}
 
static void imprimeArquivos() {
	char val;
	int i;

	FILE* arqMem = fopen("/tmp/ep2.mem", "a+b");
	FILE* arqVir = fopen("/tmp/ep2.vir", "a+b");

	printf("Memoria real:\n");

	for (i = 0; i < memTotal; i++) {
		fread(&val, sizeof(char), 1, arqMem);
		printf("%d ", val);
	}
	printf("\n");

	for (i = 0; i < memVirtual; i++) {
		fread(&val, sizeof(char), 1, arqMem);
		printf("%d ", val);
	}
	printf("\n");

	fclose(arqMem);
	fclose(arqVir);
}


static int interpretaComandosShell() {
	int aux; 
	
	if (strcmp(word[0],"carrega") == 0) {
		arqEntrada = fopen(word[1], "r");
		leArquivoEntrada();

		if (!arqEntrada) {
			fprintf(stderr, "ERRO ao abrir o arquivo %s\n", word[1]);
		}
	}
	else if (strcmp(word[0],"espaco") == 0) {
		aux = atoi(word[1]);

		if (aux < 1 || aux > 3) {
			printf("Numero de gerenciamento de espaco livre invalido\n");
		}
		else {
			numGerEspLiv = aux; 
		}
	}
	else if (strcmp(word[0], "substitui") == 0) {
		aux = atoi(word[1]);
		
		if (aux < 1 || aux > 4) {
			printf("Numero de substituicao de paginas invalido\n");
		}
		else {
			numSubsPag = aux;
		}
	}
	else if (strcmp(word[0], "executa") == 0) {
		intervalo = atof(word[1]);

	 	if (intervalo <= 0) {
			printf("Intervalo de tempo invalido\n");
		}
		else {
			if (numGerEspLiv && arqEntrada) {
				printf("Arquivo: %s\nGerencia Espaco Livre: %d\nSubstituicao Pagina: %d\nIntervalo: %f\n", 
				"", numGerEspLiv, numSubsPag, intervalo);
				simulador(numGerEspLiv);
			}
			else {
				printf("Faltou definir algum parâmetro!\n");
			}
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

static void limpaMatriz() {
	int i, j;

	for (i = 0; i < LINMAX; i++) {
		for (j = 0; j < COLMAX; j++) {
			word[i][j] = 0;
		}
	}
}

static void parserCommandShell(char *line) {
	int i, lin = 0, col = 0;

	for (i = 0; line[i] != '\0'; i++) {
		if (line[i] != ' ') {
			word[lin][col++] = line[i];
		}
		else if (col != 0) {
			lin++;
			col = 0;
		}
	}
}

static void leArquivoEntrada() {
	int i = 0;

	fscanf(arqEntrada,"%d %d", &memTotal, &memVirtual); 

	while (fscanf(arqEntrada,"%d %s %d %d", &trace[i].t0, trace[i].nome, 
		&trace[i].tf, &trace[i].b) != EOF) {		
		i++;
	}

	nProcs = i;
}