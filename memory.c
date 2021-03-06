#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

static FILE* arq;

void imprimeMemoriaVirtual() {
	char val;
	arq = fopen("/tmp/ep2.vir", "rb");
	
	printf("Memoria Virtual:\n");

	while (!feof(arq)) {
		if (fread(&val, sizeof(char), 1, arq) == 1) {
			printf("%d ", val);
		}
	}

	fclose(arq);
}

void escreveNoArquivoVirtual(char pid, int inicio, int nbytes) {
	int i;
	char myPID = pid;

	arq = fopen("/tmp/ep2.vir", "r+b");  
	
	fseek(arq, inicio * sizeof(char), SEEK_SET);	
	
	for (i = 0; i < nbytes; i++)
		if (fwrite(&myPID, sizeof(char), 1, arq) != 1) 
			printf("Não escreveu 1 byte!\n");

	fclose(arq);
}

void inicializaMemoriaVirtual(int totalMemoria) {
	int i;
	char valor = -1;
	arq = fopen("/tmp/ep2.vir", "wb");

	for (i = 0; i < totalMemoria; i++)
		if (fwrite(&valor, sizeof(char), 1, arq) != 1)
			printf("Não escreveu 1 byte ao inicializar!\n");

	fclose(arq);
}

void imprimeMemoriaFisica() {
	char val;
	arq = fopen("/tmp/ep2.mem", "rb");
	
	printf("Memoria Fisica:\n");

	while (!feof(arq)) {
		if (fread(&val, sizeof(char), 1, arq) == 1) {
			printf("%d ", val);
		}
	}

	fclose(arq);
}

void escreveNoArquivoFisico(char pid, int inicio, int nbytes) {
	int i;
	char myPID = pid;

	arq = fopen("/tmp/ep2.mem", "r+b");  
	
	fseek(arq, inicio * sizeof(char), SEEK_SET);	
	
	for (i = 0; i < nbytes; i++)
		if (fwrite(&myPID, sizeof(char), 1, arq) != 1) 
			printf("Não escreveu 1 byte!\n");

	fclose(arq);
}

void inicializaMemoriaFisica(int totalMemoria) {
	int i;
	char valor = -1;
	arq = fopen("/tmp/ep2.mem", "wb");

	for (i = 0; i < totalMemoria; i++)
		if (fwrite(&valor, sizeof(char), 1, arq) != 1)
			printf("Não escreveu 1 byte ao inicializar!\n");

	fclose(arq);
}