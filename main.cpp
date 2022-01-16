#include "Review.h"
#include "FileIO.h"
#include "Ordenacao.h"
#include "TabelaHash.h"
#include "ArvoreVermelhoPreto.h"
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
    int comparacoes, n = 5, totalComparacoes, opcao;

    imprimeMenu();

    cin>> opcao;

    while(opcao != 3){
        switch(opcao){

            case 1:{
                ArvoreVermelhoPreto *arvoreVP = new ArvoreVermelhoPreto();

                ReviewNode **vet = new ReviewNode*[n];

                importaConjunto(argv[1], n, vet);

                totalComparacoes = 0;

                for(int i = 0; i < n; i++){
                    arvoreVP->insere(vet[i], comparacoes);
                    totalComparacoes += comparacoes;
                }

                delete arvoreVP;
            }
            break;

            case 2:
            break;

            default: cout << "Opcao Invalida!" << endl;
        }

        imprimeMenu();
        cin >> opcao;
    }


    return 0;
}
