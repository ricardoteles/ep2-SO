typedef struct segmento* Link;

struct segmento{
	char info;
	int base;
	int tamanho;
	Link prox;
	Link ant;
} Segmento;

Link head, tail;

void initList(int totalMemoria);
void insertItemList(Link aux, char info, int base, int tamanho);
void splitHoleInPL(Link aux, int tamanho);
void removeList(Link aux, Link rem);
void printList();
Link mallocItemList();