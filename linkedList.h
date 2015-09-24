typedef struct segmento* Link;

struct segmento{
	char info;
	int base;
	int tamanho;
	Link prox;
} Segmento;

Link inicio, tail;

void initList(int totalMemoria);
void insertProcessList(int tamanho);
void splitSegment_L_in_PL(Link aux, int tamanho);
void insertList(Link ant, char info, int base, int tamanho);