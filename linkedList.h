/********************** MAPA DE MEMÓRIA  ***************************/
typedef struct segmento* Link;

struct segmento{
	char info;
	int base;
	int tamanho;
	Link prox;
} Segmento;

Link head, tail;

void initList(int totalMemoria);
void insertItemList(Link ant, char info, int base, int tamanho);
void splitHoleInPL(Link aux, int tamanho);
Link mallocItemList();