#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "Arvores.h"
#include "ArvoreVermelhoPreto.h"

using namespace std;
using namespace chrono;

void analise(int b, int m, int n, char *diretorio){
    ofstream arq;
    arq.open("saida.txt");

    int comparacoes, totalComparacoes, comparacaoInsercao = 0, comparacaoBusca = 0, aux;
    double tempoInsercao = 0, tempoBusca = 0, media;

    if(arq){

        arq << "Resultados para Arvore Vermelho e Preto N = " << n << " B = " << b << endl;

        for(int cont = 1; cont <= m; cont++){
            cout << "Execucao e resultados da Arvore Vermelho e Preta: " << cont << "..." << endl;
            arq << "TESTE " << cont << endl;

            ArvoreVermelhoPreto *arvoreVP = new ArvoreVermelhoPreto();
            ReviewNode **vet = new ReviewNode*[n];

            importaConjunto(diretorio, n, vet);

            totalComparacoes = 0;

            high_resolution_clock::time_point inicio = high_resolution_clock::now();

            for(int i = 0; i < n; i++){
                arvoreVP->insere(vet[i], comparacoes);
                totalComparacoes += comparacoes;
            }

            auto resultado = high_resolution_clock::now() - inicio;
            double tempo = duration_cast<milliseconds>(resultado).count();


            arq << "Tempo de Insercao: " << tempo << endl;
            arq << "Comparacoes da Insercao: " << totalComparacoes << endl;

            comparacaoInsercao += totalComparacoes;
            tempoInsercao += tempo;

            inicio = high_resolution_clock::now();

            totalComparacoes = 0;

            for(int i = 0; i < b; i++){
                 aux = rand()% n;
                 arvoreVP->busca(vet[aux]->getId(), comparacoes);
                 totalComparacoes += comparacoes;
            }

            resultado = high_resolution_clock::now() - inicio;
            tempo = duration_cast<nanoseconds >(resultado).count();

            arq << "Tempo de Busca: " << tempo << endl;
            arq << "Comparacoes da Busca: " << totalComparacoes << endl;

            comparacaoBusca += totalComparacoes;
            tempoBusca += tempo;


            for(int i = 0; i < n; i++){
                delete vet[i];
            }

            delete []vet;
            delete arvoreVP;

            cout << "Finalizado teste " << cont << endl;

        }
        media = tempoInsercao / (double)m;

        arq << "Tempo Medio de Insercao: " << media << endl;

        media = comparacaoInsercao / (double)m;

        arq << "Media de Comparacoes da Insercao: " << media << endl;

        media = tempoBusca / (double)m;

        arq << "Tempo Medio de Busca: " << media << endl;

        media = comparacaoBusca / (double)m;

        arq << "Media de Comparacoes da Busca: " << media << endl;

        arq.close();

    }else
        cout << "Erro ao criar o arquivo de saida!" << endl;
}

void busca(char *diretorio){

    int n = 1000000, comparacoes;
    char id[90];

    ArvoreVermelhoPreto *arvoreVP = new ArvoreVermelhoPreto();
    ReviewNode **vet = new ReviewNode*[n];

    importaConjunto(diretorio, n, vet);

     for(int i = 0; i < n; i++){
        arvoreVP->insere(vet[i], comparacoes);
    }

    cout << "Digite um ID para busca: ";
    cin >> id;

    ReviewNode *node = arvoreVP->busca(id, comparacoes);

    if(node != nullptr){
        acessaRegistro(node->getPosicaoArquivo(), diretorio);
    }
    else{
        cout << "Registro nao encontrado na arvore!" << endl;
    }

}
