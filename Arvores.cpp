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

Arvores::Arvores(){}
void Arvores::analise(int n){


   int comparacoes;
   n=10; // 100 registros
   for(int cont=1; cont<n; cont++)
   {
       cout << "Execução e resultados da Arvore Vermelho e Preta: " << cont << "..." << endl;
        
        fstream arq;
        arq.open("Dados.txt");
        
        if(arq)
        {
                  //Criando arquivo para salvar estatísticas de busca
                ofstream saidaBusca;
                saidaBusca  << "saidaBusca" + cont ;
                saidaBusca.open("saida.txt");
                
                if(saidaBusca)
                {
                    //Para e busca nas árvores
                    while(!arq.eof())
                    {

                         ArvoreVermelhoPreto *arvoreVP = new ArvoreVermelhoPreto();
                        
                         ReviewNode **vet = new ReviewNode*[n];
                         
                         
                        // cout<<"Buscando..";                 

                        
                        high_resolution_clock::time_point inicio = high_resolution_clock::now();
                         
                            
                            saidaBusca << " \nTamanho do conjunto: N: " << n << endl; //Imprime o tamanho do vetor no arquivo de saída da busca
                            comparacoes = 0;
                            
                        //Buscando na Árvore Vermelha e Preta                        
                        
                            for(int i=0; i<n; i++)
                            arvoreVP->busca(vet[i], comparacoes);
                        auto resultado = high_resolution_clock::now() - inicio;
                        double tempo = duration_cast<nanoseconds >(resultado).count();

                        

                        saidaBusca << "Arvore-VP: \n" << "Tempo: " << tempo/1000000000 << "\nComparações: " << comparacoes << endl;


                        delete []vet;
                    }

                    saidaBusca.close();

                }else
                cout << "Erro ao criar o arquivo de saida da insercao" << endl;

            arq.close();
        }
        else
            cout << "Erro ao abrir arquivo de entrada" << endl;
    }
}