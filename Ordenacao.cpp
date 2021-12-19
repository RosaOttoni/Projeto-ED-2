#define ORDENACAO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <ctime>
#include "Review.h"
#include "FileIO.h"


using namespace std;

void troca(Review *vet[], int i, int j){
    Review *aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

int particiona(Review *vet[], int p, int q, int &comparacao, int &movimentacao){

    int pivo = vet[q]->getUpvotes();

    int i = p, j = q - 1;

    do{
        while(i < q && vet[i]->getUpvotes() < pivo){
            i++;
            comparacao++;
        }


        comparacao++;

        while( j >= p && vet[j]->getUpvotes() > pivo){
            j--;
            comparacao++;
        }

        comparacao++;

        if (i <= j){
            troca(vet, i, j);
            i++;
            j--;
            movimentacao++;
        }
    }while(i <= j);

    troca(vet, i, q);
    movimentacao++;

    return i;
}

void quickSort(Review *vet[], int p, int r, int &comparacao, int &movimentacao){

    int q;

    if(p < r){
        q = particiona(vet, p, r, comparacao, movimentacao);
        quickSort(vet, p, q - 1, comparacao, movimentacao);
        quickSort(vet, q + 1, r, comparacao, movimentacao);
    }
}
