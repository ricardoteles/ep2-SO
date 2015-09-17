#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINMAX 10
#define COLMAX 50

FILE* arqEntrada;

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
/****************************************************/

int main(int argc, char* argv[]) {

	parserArgumentosEntrada(argc, argv);

	return 0;
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
		printf("Carrega %s\n", command[1]);
	}
	else if (strcmp(command[0],"espaco") == 0) {
		printf("Espaco %s\n", command[1]);
	}
	else if (strcmp(command[0], "substitui") == 0) {
	 	printf("Substitui %s\n", command[1]);
	}
	else if (strcmp(command[0], "executa") == 0) {
	 	printf("Executa %s\n", command[1]);
	}
	else if (strcmp(command[0], "sai") == 0){
		exit(0);
	}
	else {
		fprintf(stderr, "comando %s inválido!\n", command[0]);
	}
}

void apagaMatriz(){
	int i, j;

	for (i = 0; i < LINMAX; i++) {
		for (j = 0; j < COLMAX; j++) {
			command[i][j] = 0;
		}
	}
}

void parserCommandShell(char *line){
	int i, lin = 0, col = 0;

	for(i = 0; line[i] != '\0'; i++){
		if(line[i] != ' '){
			command[lin][col++] = line[i];
		}
		else if(col != 0){
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

	else if (argc == 2) {
		arqEntrada = fopen(argv[1], "r");

		if (!arqEntrada) {
			fprintf(stderr, "ERRO ao abrir o arquivo %s\n", argv[2]);
			exit(0);
		}  
	}
	else {
		printf("Formato esperado:\n./ep2 <arq_entrada> OU ./ep2\n");
		exit(-2);
	}
}