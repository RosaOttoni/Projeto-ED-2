#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED
#include <iostream>
#include <ctime>
#include <random>
#include "Review.h"
#include "ReviewNode.h"

using namespace std;

void acessaRegistro(int i, char *diretorio);

void geraArquivo(int n, int *vet);

void leituraCsv(string diretorio);

void importaConjunto(int n, Review *vet[]);

void importaConjunto (char *nomeDiretorio, int n, Review *vet[]);

void importaConjunto (char *nomeDiretorio, int n, ReviewNode *vet[], int indicesBusca[], int m);

void imprimeConjunto (int n, Review *vet[]);

#endif // FILEIO_H_INCLUDED
