#ifndef ORDENACAO_H_INCLUDED
#define ORDENACAO_H_INCLUDED
#include <iostream>
#include "Review.h"

using namespace std;

void quickSort(Review *vet[], int p, int r, int &comparacao, int &movimentacao);

void timSort(Review *vetor[], int n,  int &comparacao, int &movimentacao);

void insertionSort(Review *vetor[], int esq, int dir,  int &comparacao, int &movimentacao);

void mergeSort(Review *vetor[], int inicio, int fim,  int &comparacao, int &movimentacao);

void intercala(Review vetor[],int inicio, int meio,int fim,  int &comparacao, int &movimentacao);

void heapSort(Review *vetor[], int n, int &comparacao, int &movimentacao);

void constroiHeap(Review *vetor[], int n, int &comparacao, int &movimentacao);

void heapify(Review *vetor[], int i, int n, int &comparacao, int &movimentacao);


#endif // ORDENACAO_H_INCLUDED
