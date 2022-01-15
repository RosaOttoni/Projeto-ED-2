#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED
#include <iostream>
#include <ctime>
#include "Review.h"

using namespace std;

void acessaRegistro(int i);

void geraArquivo(int n, int *vet);

void testeImportacao();

void leituraCsv(string diretorio);

void importaConjunto (char *nomeDiretorio, int n, Review *vet[]);

void imprimeConjunto (int n, Review *vet[]);

#endif // FILEIO_H_INCLUDED
