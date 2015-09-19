//#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINMAX 10
#define COLMAX 50

FILE* arqEntrada;

/******************* prompt **************************/
char word[LINMAX][COLMAX];

void prompt();
void interpretaComandosPrompt();
void limpaMatriz();
void parserCommandPrompt(char *line);
/******************* UTILS **************************/

/****************************************************/

int main(int argc, char* argv[]) {
	if (argc != 1) {
		printf("Formato esperado: ./ep2\n");
		exit(0);
	}

	printf("\n--------------------- Prompt EP2 ---------------------\n\n");
	prompt();
	return 0;
}

/******************* prompt **************************/
void prompt() {
	char line[200];
	line[0] = 0;

	do {
		printf("[ep2]: ");
		__fpurge(stdin); // limpa buffer do teclado
		scanf("%200[^\n]s", &line[0]);

		if (line[0] != 0) {
			//printf("%s\n", line);
			limpaMatriz();
			parserCommandPrompt(line);
			interpretaComandosPrompt();
			line[0] = 0;
		}
	} while(1);
}

void interpretaComandosPrompt() {
	if (strcmp(word[0],"carrega") == 0) {
		printf("Carrega %s\n", word[1]);
	}
	else if (strcmp(word[0],"espaco") == 0) {
		printf("Espaco %s\n", word[1]);
	}
	else if (strcmp(word[0], "substitui") == 0) {
	 	printf("Substitui %s\n", word[1]);
	}
	else if (strcmp(word[0], "executa") == 0) {
	 	printf("Executa %s\n", word[1]);
	}
	else if (strcmp(word[0], "sai") == 0) {
		exit(0);
	}
	else {
		fprintf(stderr, "comando %s inválido!\n", word[0]);
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

void parserCommandPrompt(char *line) {
	int i, lin = 0, col = 0;

	for(i = 0; line[i] != '\0'; i++){
		if(line[i] != ' '){
			word[lin][col++] = line[i];
		}
		else if(col != 0){
			lin++;
			col = 0;
		}
	}
}

/******************* UTILS **************************/
