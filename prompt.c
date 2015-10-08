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
	
	/*carrega*/
	if (strcmp(word[0],"c") == 0) {
		arqEntrada = fopen(word[1], "r");
		leArquivoEntrada();

		if (!arqEntrada) {
			fprintf(stderr, "ERRO ao abrir o arquivo %s\n", word[1]);
		}
	}
	/*espaco*/
	else if (strcmp(word[0],"e") == 0) {
		aux = atoi(word[1]);

		if (aux < 1 || aux > 3) {
			printf("Numero de gerenciamento de espaco livre invalido\n");
		}
		else {
			numGerEspLiv = aux; 
		}
	}
	/*substitui*/
	else if (strcmp(word[0], "s") == 0) {
		aux = atoi(word[1]);
		
		if (aux < 1 || aux > 4) {
			printf("Numero de substituicao de paginas invalido\n");
		}
		else {
			numSubsPag = aux;
		}
	}
	/*executa*/
	else if (strcmp(word[0], "x") == 0) {
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
	char *p, *t;
	char line[100], *search = " ";
	Node cauda = NULL;
	// char c;

	fscanf(arqEntrada,"%d %d", &memTotal, &memVirtual); 

	while (fscanf(arqEntrada,"%d %s %d %d %[^\n]s", &tabelaProcessos[i].t0, tabelaProcessos[i].nome, 
		&tabelaProcessos[i].tf, &tabelaProcessos[i].b, line) != EOF) {
	
		tabelaProcessos[i].listaTrace = iniciaLista();
		cauda = tabelaProcessos[i].listaTrace;

		p = strtok(line, search);
		t = strtok(NULL, search);

		while(p != NULL){
			cauda = insertNodeList(cauda, atoi(p), atoi(t));
			// printf("%d: %d %d\n", i, atoi(p), atoi(t));
			p = strtok(NULL, search);
			t = strtok(NULL, search);
		}

		// c = getchar();	
		i++;
	}

	nProcs = i;
}

/*************** LISTA para os P's do arqEntrada **********************/

Node iniciaLista() {
	Node cab = mallocNodeList();
	
	cab->p = -1;
	cab->t = -1;
	cab->next = NULL;

	return cab;	
}

Node insertNodeList(Node aux, int p, int t) {
	Node novo = mallocNodeList();
	novo->p = p;
	novo->t = t;

	novo->next = aux->next;
	aux->next = novo;

	return aux->next;
}

Node mallocNodeList() {
	Node p = (Node) malloc(sizeof(Trace));
	if (!p) {
		fprintf(stderr, "Memoria insuficiente!\n");
		exit(1);
	}

	return p;
} 