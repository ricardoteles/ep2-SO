#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include "simulador.h"

#define LINMAX 10
#define COLMAX 50

FILE* arqEntrada;
char word[LINMAX][COLMAX];
static Process myTable[NMAX_PROCS];

/*================================= PROTOTIPOS ========================================*/
static void copiaLinhaTabela(int linha, Process t1[NMAX_PROCS], Process t2[NMAX_PROCS]);
int interpretaComandosShell();
void limpaMatriz();
void parserCommandShell(char *line);
void leArquivoEntrada();
void criaArquivosMemoria();
void imprimeArquivos();


int main() {
	int status = 1;
	char* line;
	printf("\n--------------------- SHELL EP2 ---------------------\n\n");

	while (status) {
		line = readline("[ep2]: ");
		limpaMatriz();
		parserCommandShell(line);
		status = interpretaComandosShell();

		if (word[0][0] != '\0')
			add_history (line);
	}

	return 0;
}

int interpretaComandosShell() {
	int aux, i;
	
	/*carrega*/
	if (strcmp(word[0], "c") == 0) {
		arqEntrada = fopen(word[1], "r");

		if (!arqEntrada) {
			fprintf(stderr, "ERRO ao abrir o arquivo %s\n", word[1]);
		}

		leArquivoEntrada();
	}

	/*espaco*/
	else if (strcmp(word[0], "e") == 0) {
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

	/* executa */
	else if (strcmp(word[0], "x") == 0) {
		intervalo = atof(word[1]);
		int i;

	 	if (intervalo <= 0) {
			printf("Intervalo de tempo invalido\n");
		}
		else {
			if (numGerEspLiv && numSubsPag && arqEntrada) {
				for(i = 0; i < (memVirtual/16); i++){
					pagina[i] = -1;
				}
				
				for(i = 0; i < (memTotal/16); i++){
					quadrosUsados[i] = 0;
				}
				
				for (i = 0; i < nProcs; i++) {
					copiaLinhaTabela(i, tabelaProcessos, myTable);
				}

				simulador();
			}
			else {
				printf("Faltou definir algum parâmetro!\n");
			}
		}
	}

	else if (strcmp(word[0], "sai") == 0) {
		return 0;		
	}
	
	else if (word[0][0] != '\0'){
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

void leArquivoEntrada() {
	int i = 0;
	char *p, *t;
	char line[100], *search = " ";
	Node cauda;
	// char c;

	fscanf(arqEntrada,"%d %d", &memTotal, &memVirtual); 

	while (fscanf(arqEntrada,"%d %s %d %d %[^\n]s", &tabelaProcessos[i].t0, tabelaProcessos[i].nome, 
		&tabelaProcessos[i].tf, &tabelaProcessos[i].b, line) != EOF) {
	
		tabelaProcessos[i].listaTrace = initNodeList();
		cauda = tabelaProcessos[i].listaTrace;
		cauda = insertNodeList(cauda, -1, tabelaProcessos[i].t0);

		p = strtok(line, search);
		t = strtok(NULL, search);

		while (p != NULL) {
			cauda = insertNodeList(cauda, atoi(p), atoi(t));
			// printf("%d: %d %d\n", i, atoi(p), atoi(t));
			p = strtok(NULL, search);
			t = strtok(NULL, search);
		}

		cauda = insertNodeList(cauda, -1, tabelaProcessos[i].tf);

		copiaLinhaTabela(i, myTable, tabelaProcessos);
		i++;
	}

	nProcs = i;
	fclose(arqEntrada);

	if (nProcs > NMAX_PROCS) {
		printf("# MAX de traces permitidos: 256.\n");
		arqEntrada = NULL;
		return ;
	}

	pagina = (int*)Malloc((memVirtual/16)*sizeof(int));
	quadrosUsados = (int*)Malloc((memTotal/16)*sizeof(int));
}

static void copiaLinhaTabela(int linha, Process t1[NMAX_PROCS], Process t2[NMAX_PROCS]) {
	Node cauda, aux;

	strcpy(t1[linha].nome, t2[linha].nome);
	t1[linha].t0 = t2[linha].t0;
	t1[linha].tf = t2[linha].tf;
	t1[linha].b = t2[linha].b;

	t1[linha].listaTrace = cauda = initNodeList();

	for (aux = t2[linha].listaTrace->next; aux != NULL; aux = aux->next) {
		cauda = insertNodeList(cauda, aux->p, aux->t);
	}
}