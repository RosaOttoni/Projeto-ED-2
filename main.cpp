#include "Review.h"
#include "FileIO.h"
#include "Ordenacao.h"
#include "TabelaHash.h"
#include "ArvoreVermelhoPreto.h"
#include "Arvores.h"
#include <fstream>
#include <iomanip>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

void imprimeMenu(){
    cout<<"____________________MENU__________________________"<<endl;
    cout<<"| Para executar, escolha uma das opcoes abaixo:  |"<<endl;
    cout<<"| 1 - Arvore Vermelho-Preto                      |"<<endl;
    cout<<"| 2 - Arvore B                                   |"<<endl;
    cout<<"| 3 - SAIR                                       |"<<endl;
    cout<<"|________________________________________________|"<<endl<<endl;
}

int main(int argc, char *argv[])
{
   int comparacoes, n = 5, totalComparacoes, opcao,op2;//n =1000000
    imprimeMenu();

    cin>> opcao;

    while(opcao != 3)
    {
        switch(opcao)
        {
            case 1: // arvore vermelho e preta
            {                
                cout<<endl<<" ___________________SUBMENU_____________________|"<<endl;
                cout<<"| Para analise de estruturas, digite [1]              |"<<endl;
                cout<<"| Para modulo de testes [2]                           |"<<endl;
                cout<<"| Para finalizar digite [0]                           |"<<endl;
                cout<<"|_____________________________________________________|"<<endl<<endl;
                int op2;
                        
                cin>> op2;
                while(op2 != 3)
                {
        
                    switch(op2)
                    {
                        case 1: 
                        {                        
                            int m = 3;
                            ArvoreVermelhoPreto *arvoreVP = new ArvoreVermelhoPreto();

                            ReviewNode **vet = new ReviewNode*[n];

                            importaConjunto(argv[1], n, vet);
                            cout<<"Registros importados...."<<endl;

                            totalComparacoes = 0;

                            for(int i = 0; i < 100; i++){
                            arvoreVP->insere(vet[i], comparacoes);
                            totalComparacoes += comparacoes;}
                                
                            Arvores arvores;
                            //analise (insercao  e busca de 100 conjuntos)
                            
                            arvores.analise(m); // imprime etapa 3
                            cout<<"registros analisados";
                            delete arvoreVP;
                            
                        }
                        break; 

                        case 2:// modulo teste
                        {
                            char *b;
                            fstream arq;
                            arq.open("Dados.txt");
                            ArvoreVermelhoPreto *arvoreVP = new ArvoreVermelhoPreto();
                            ReviewNode **vet = new ReviewNode*[n];
                            importaConjunto(argv[1], n, vet);
                            cout<<"Registros importados...."<<endl;
                            
                            cout<< "Digite o numero desejado busca na arvore:";
                            cin>>b;
                                                        
                            if(arq)
                            {  
                                ofstream busca;                                
                                busca.open("saidaBusca.txt");
                                
                                if(busca)
                                {
                                    while(!arq.eof())
                                    {
                                        int comparacoes;

                                        ReviewNode **vet = new ReviewNode*[n];
                                        high_resolution_clock::time_point inicio = high_resolution_clock::now();                             
                                        for(int i=0;i<n;i++){

                                            arvoreVP->insere(vet[i], comparacoes);
                                            arvoreVP->busca(b, comparacoes);
                                            totalComparacoes += comparacoes;
                                            auto resultado = high_resolution_clock::now() - inicio;
                                            double tempo = duration_cast<nanoseconds >(resultado).count();
                                            
                                            
                                            busca << "Arvore-VP: \n" << "Tempo: " << tempo/1000000000 << "\nComparações: " <<totalComparacoes << endl;

                                            busca << "ID" << b << endl<<endl;
                                            delete arvoreVP;
                                        }
                                        busca.close();
                                    }
                                }else
                                    cout << "Erro ao criar o arquivo de saida da busca" << endl;
                                    arq.close();                        
                            }else
                            cout << "Erro ao abrir arquivo de entrada" << endl;
                        }
                        break;
                    } 
                }
                   
            }break;
            case 2: // arvore b
            {
                cout<<endl<<" ___________________SUBMENU_____________________|"<<endl;
                cout<<"| Para analise de estruturas, digite [1]              |"<<endl;
                cout<<"| Para modulo de testes [2]                           |"<<endl;
                cout<<"| Para finalizar digite [0]                           |"<<endl;
                cout<<"|_____________________________________________________|"<<endl<<endl;
                int op2;
                        
                cin>> op2;
                while(op2 != 3)
                {
        
                    switch(op2)
                    {
                        case 1: 
                        {        
                        }
                    }
                }

            } 
            break;
            default: cout << "Opcao Invalida!" << endl;

        }
        imprimeMenu();
        cin >> opcao;
    }
     return 0;
}
    

