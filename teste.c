#include <stdio.h>
#include <stdlib.h>

#define MAX 15

FILE* arq;

void imprimeMemoria() {
	int val, i;
	arq = fopen("/tmp/ep2.vir", "rb");
	
	while (!feof(arq)) {
		if (fread(&val, sizeof(int), 1, arq) == 1) {
			printf("%d ", val);
		}
	}

	printf("\n");

	fclose(arq);
}

void escreveItem(int offset, int valor, int n) {
	int i;
	int v[MAX];

	arq = fopen("/tmp/ep2.vir", "r+b");  
	
	for (i = 0; i < n; i++)
		v[i] = valor;
	
	fseek(arq, offset * sizeof(int), SEEK_SET);	
	
	if (fwrite(v, sizeof(int), n, arq) != n) 
		printf("Não escreveu %d itens!\n", n);

	fclose(arq);
}

void criaInicializa(int val) {
	 int v[MAX];
	 int i;

	arq = fopen("/tmp/ep2.vir", "wb");  
	 
	for (i = 0; i < MAX; i++)
		v[i] = val;

	if (fwrite(v, sizeof(int), MAX, arq) != MAX)
		printf("Não escreveu %d itens!\n", MAX);

	fclose(arq);
}

int main() {

	criaInicializa(-2);
	imprimeMemoria();
	criaInicializa(-1);
	imprimeMemoria();
	
	escreveItem(0, -30, 5);

	escreveItem(10, -20, 10);
	imprimeMemoria();
	escreveItem(1, -1000, 1);
	imprimeMemoria();
	
	return 0;
}


