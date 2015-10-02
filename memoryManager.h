#ifndef MEMORYMANAGER_H 
#define MEMORYMANAGER_H

#include "linkedList.h"

static Link inicioNextFit;

void firstFit(int tamanho, int pid);
void nextFit(int tamanho, int pid);

#endif