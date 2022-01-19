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
   n=10;
   for(int cont=1; cont<n; cont++)
   {

       cout << "Execução e resultados da Arvore Vermelho e Preta: " << cont << "..." << endl;
        
        fstream arq;
        arq.open("Dados.txt");
        
        if(arq)
        {
         //Criando arquivo para salvar estatísticas de busca
            ofstream arqSaidaI;
            arqSaidaI  << "saidaBusca" + cont ; 
            arqSaidaI.open("saidaInsercao.txt");

            if (arqSaidaI)
            {
                ofstream saidaBusca;
                saidaBusca  << "saidaBusca" + cont ; 
                saidaBusca.open("saidaBusca.txt");
                
                if(saidaBusca)
                {
                    //Para busca nas árvores
                    while(!arq.eof())

                    {
                        ArvoreVermelhoPreto *arvoreVP;
                        
                        ReviewNode **vet = new ReviewNode*[n];
                         
                        // cout<<"Buscando..";              

                        
                        high_resolution_clock::time_point inicio = high_resolution_clock::now();
                        saidaBusca << " \nTamanho do conjunto: N: " << n << endl; 
                        comparacoes = 0;
                            
                        //Buscando na Árvore Vermelha e Preta
                        for(int i=0; i<n; i++)
                        arvoreVP->insere(vet[i], comparacoes);
                        auto resultado = high_resolution_clock::now() - inicio;
                        double tempo = duration_cast<nanoseconds >(resultado).count();
                        arqSaidaI << "Arvore-VP: \n" << "Tempo: " << tempo/1000000000 << "\nComparações: " << comparacoes << endl;

                        comparacoes = 0;
                        
                        for(int i=0; i<n; i++)
                        arvoreVP->busca(vet[i], comparacoes);
                        resultado = high_resolution_clock::now() - inicio;
                        tempo = duration_cast<nanoseconds >(resultado).count();                     
                        saidaBusca << "Arvore-VP: \n" << "Tempo: " << tempo/1000000000 << "\nComparações: " << comparacoes << endl;


                        delete []vet;
                    }
                    saidaBusca.close();
                }
                else
                    cout << "Erro ao criar o arquivo de saida da insercao" << endl;
                    arqSaidaI.close();
            }
            else
            cout << "" << endl;
            arq.close();
        }
        else
         cout << "Erro ao abrir arquivo de entrada" << endl;
   }
}