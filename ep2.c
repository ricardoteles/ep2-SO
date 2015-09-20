#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINMAX 10
#define COLMAX 50

FILE* arqEntrada;
int numGerEspLiv, numSubsPag;
float intervalo;
struct timeval inicio;


/*********** GERENCIAMENTO DE MEMORIA ***************/
void simulador();
/******************* SHELL **************************/
char *path;
char format[80] = "";
char command[LINMAX][COLMAX];

void shell();
void interpretaComandosShell();
void apagaMatriz();
void parserCommandShell(char *line);
/******************* UTILS **************************/
void parserArgumentosEntrada(int argc, char* argv[]);
float tempoDesdeInicio();
/****************************************************/

int main(int argc, char* argv[]) {
	parserArgumentosEntrada(argc, argv);

	return 0;
}

/*********** GERENCIAMENTO DE MEMORIA ***************/
void simulador(){
	gettimeofday(&inicio, NULL);

	while(tempoDesdeInicio(inicio) < intervalo){
		printf("Oiiii\n");
	}

}

/******************* SHELL **************************/
void shell(){
	printf("\n--------------------- SHELL EP2 ---------------------\n\n");
	char* line = readline("[ep2]: ");

	do {
		add_history (line);
		apagaMatriz();
		parserCommandShell(line);
		interpretaComandosShell();
		line = readline("[ep2]: ");
	} while(1);
}

void interpretaComandosShell(){
	if (strcmp(command[0],"carrega") == 0) {
		arqEntrada = fopen(command[1], "r");
	}
	else if (strcmp(command[0],"espaco") == 0) {
		if(atoi(command[1]) < 1 || atoi(command[1]) > 3) {
			printf("Numero de gerenciamento de espaco livre invalido\n");
		}
		else {
			numGerEspLiv = atoi(command[1]);
		}
		
	}
	else if (strcmp(command[0], "substitui") == 0) {
		if(atoi(command[1]) < 1 || atoi(command[1]) > 4) {
			printf("Numero de substituicao de paginas invalido\n");
		}
		else {
			numSubsPag = atoi(command[1]);
		}
	}
	else if (strcmp(command[0], "executa") == 0) {
	 	if(atof(command[1]) <= 0){
			printf("Intervalo de tempo invalido\n");
		}
		else {
			intervalo = atof(command[1]);
			simulador();
		}
	}
	else if (strcmp(command[0], "sai") == 0) {
		exit(0);
	}
	else {
		fprintf(stderr, "comando %s inválido!\n", command[0]);
	}
}

void apagaMatriz() {
	int i, j;

	for (i = 0; i < LINMAX; i++) {
		for (j = 0; j < COLMAX; j++) {
			command[i][j] = 0;
		}
	}
}

void parserCommandShell(char *line) {
	int i, lin = 0, col = 0;

	for(i = 0; line[i] != '\0'; i++) {
		if(line[i] != ' ') {
			command[lin][col++] = line[i];
		}
		else if(col != 0) {
			lin++;
			col = 0;
		}
	}
}

/******************* UTILS **************************/
void parserArgumentosEntrada(int argc, char* argv[]) {
	if(argc == 1) {
		shell();
	}

	else if (argc == 5) {			/* APAGAR DEPOIS */
		arqEntrada = fopen(argv[1], "r");
		numGerEspLiv = atoi(argv[2]);
		numSubsPag = atoi(argv[3]);
		intervalo = atof(argv[4]);

		printf("Arquivo: %s\nGerencia Espaco Livre: %d\nSubstituicao Pagina: %d\nIntervalo: %f\n", 
			argv[1], numGerEspLiv, numSubsPag, intervalo);

		simulador();

		if (!arqEntrada) {
			fprintf(stderr, "ERRO ao abrir o arquivo %s\n", argv[2]);
			exit(0);
		}  
	}
	else {
		printf("Formato esperado:\n./ep2\n");
		exit(-2);
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