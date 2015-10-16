#ifndef MEMORYMANAGER_H 
#define MEMORYMANAGER_H

void firstFit(Link head, int tamanho, int pid);
void nextFit(Link head, int tamanho, int pid);
void quickFit(int tamanho, int pid);

void inicializaTabelaQuick();
void inserePonteiroTabelaQuick(int lacuna, Link p);
void removePonteiroTabelaQuick(int tamAntigo, Link rem);

#endif