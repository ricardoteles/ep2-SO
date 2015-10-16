#ifndef MEMORY_H
#define MEMORY_H

void imprimeMemoriaVirtual();
void escreveNoArquivoVirtual(char pid, int inicio, int nbytes);
void inicializaMemoriaVirtual(int totalMemoria);

void imprimeMemoriaFisica();
void escreveNoArquivoFisico(char pid, int inicio, int nbytes);
void inicializaMemoriaFisica(int totalMemoria);
#endif