#define ORDENACAO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <ctime>
#include "Review.h"
#include "FileIO.h"
const int minRUN =32;// tamanho minimo do run


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
// Classificando os elementos de cada execução usando classificação por inserção
// vetor de objetos tipo Review. posicao inicial e final 
void insertionSort(Review *vetor[], int inicio, int fim,  int &comparacao, int &movimentacao)
{
    Review *aux;
    for(int i=inicio + 1;i<fim;i++)
    {
        aux = vetor[i];
        int j=i-1;
        movimentacao++;
        //deslocando os elementos anteriores a chave que sao maiores 
        while (j>0 && vetor[j]->getUpvotes() > aux->getUpvotes())
        {
            vetor[j+1] = vetor[j--];
            comparacao++;
            movimentacao++;
        }
        vetor[j+1] = aux;
        movimentacao++;
        comparacao++;
    }
}
void intercala(Review *vetor[],int esq, int meio,int dir,  int &comparacao, int &movimentacao)
{
    int i,j;
    int vet1 = meio - esq + 1;
    int vet2 = dir - meio;
    //cria vetores temporarios
    Review *vetorEsq[vet1], *vetorDir[vet2];
    //coloca os valores nos vetores temporarios
    for (i = 0; i < vet1; i++)
    {
        vetorEsq[i] = vetor[esq + i];
        movimentacao++;
    }
    for (j = 0; j < vet2; j++)
    {
        vetorDir[j] = vetor[meio +1+j];
        movimentacao++;
    }
    i =0,j=0;
    int k = esq;            

    while (i <= vet1 && j <= vet2)
    {
        if (vetorEsq[i]->getUpvotes() <= vetorDir[j]->getUpvotes())
        {
            vetor[k] = vetorEsq[i];
            i++;
            comparacao++;
            movimentacao++;
        }
        else
        {
            vetor[k] = vetorDir[j];
            j++; 
             movimentacao++;

        }
        k++;
        comparacao++;
     }
    while (i<vet1)
    {
        vetor[k] = vetorEsq[i];
        i++;
        k++;
        movimentacao++;
    }
    while (j<vet2)
    {
        vetor[k] = vetorDir[j];
        j++; 
        k++;
        movimentacao++;
    }
            
}

//Mesclando as execuções classificadas usando o algoritmo de classificação de mesclagem
void mergeSort(Review *vetor[], int inicio, int fim, int &comparacao, int &movimentacao)
{
    int meio;
    if (inicio < fim)
    {
        meio = (inicio + fim) / 2;
        //dividindo o vetor em espaços individuais.
        mergeSort(vetor, inicio, meio, comparacao, movimentacao);//primiraa metade
        mergeSort(vetor, meio + 1, fim, comparacao, movimentacao);//segunda metade
        intercala(vetor, inicio, meio, fim,comparacao, movimentacao );// une od dois sub arrays criados
    }
}
void timSort(Review *vetor[], int n, int &comparacao, int &movimentacao)
{
    //Ordenando os arrays individuais de tamanho minRun
    for(int i=0; i<n;i+=minRUN)
    {
        insertionSort(vetor,i,std::min((i + minRUN -1),(n-1)),comparacao,movimentacao);
        for (int tam = minRUN; tam < n; tam = 2*tam) 
        { 
            for (int esq = 0; esq < n; esq += 2*tam) 
            { 
                int meio = esq + tam - 1; 
                int dir = std::min((esq + 2*tam - 1), (n-1)); 
                if(meio<esq)
                //mesclando as sublistas vetor[esquerda...meio] e vetor[meio+1..direita]
                mergeSort(vetor, esq, dir,comparacao, movimentacao);
            }
        }
    }
}

void heapify(Review *vetor[], int i, int n, int &comparacao, int &movimentacao)
{
    while(i < n)
    {
        int filho = 2*i + 1;
        if(filho < n)
        {
            comparacao++;
            if(filho+1 < n && vetor[filho+1]->getUpvotes() > vetor[filho]->getUpvotes())
                filho++;
            
            if(vetor[filho]->getUpvotes() > vetor[i]->getUpvotes()){
                troca(vetor, i, filho);
                movimentacao++;
            }
        }
        i = filho;
    }

}   

void constroiHeap(Review *vetor[], int n, int &comparacao, int &movimentacao)
{
    for(int i = n/2-1; i >= 0; i--)
        heapify(vetor, i, n, comparacao, movimentacao);
}

void heapSort(Review *vetor[], int n, int &comparacao, int &movimentacao)
{
    constroiHeap(vetor, n, comparacao, movimentacao);
    while(n > 0)
    {
        troca(vetor, 0, n-1);
        movimentacao++;
        heapify(vetor, 0, n-1, comparacao, movimentacao);
        n--;
    }
}


