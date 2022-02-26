#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED
#include "ArvoreB.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <ctime>
#include <algorithm>
#include <utility>

using namespace std;

struct chave
{
    int id;

};

struct NodeB
{
    int n=0;                 //quantidade de chaves armazenadas no nó
    NodeB *pai;             //pt para o nó pai
    vector<chave *> chaves;  //array de chaves //TAM m-1
    vector<NodeB *> folhas; //ponteiro para array de ponteiros p/ os filhos //TAM m
    bool folha;            //verifica se o no e folha
};


class ArvoreB
{

private:

    NodeB *raiz;
    int m;
    void auxInsert(NodeB *no, chave *val);
    void auxImprimeArvoreB(NodeB *r);

    void cisao(NodeB *r, chave *val);
    int auxBusca(NodeB *no, string val);
    int BuscaIN(NodeB *no, string val);

public:
    ArvoreB(int t);
    ArvoreB();
    int compara(int chnova, int chexistente);
    void insercao(chave *aux);
    void busca(string val);
    void busca();
    NodeB* getRAiz();
    void imprimeArvoreB();
};

#endif // ARVOREB_H_INCLUDED
