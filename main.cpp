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
    int comparacoes, totalComparacoes, opcao;

    srand(time(NULL));

    imprimeMenu();

    cin>> opcao;

    while(opcao != 3){
        switch(opcao){

            case 1:{ // arvore vermelho e preta

                cout<<" ___________________SUBMENU___________________________"<<endl;
                cout<<"| 1 - Para analise de estruturas                      |"<<endl;
                cout<<"| 2 - Para modulo de testes                           |"<<endl;
                cout<<"| 3 - Para finalizar digite                           |"<<endl;
                cout<<"|_____________________________________________________|"<<endl<<endl;
                int op2;

                cin>> op2;
                while(op2 != 3)
                {

                    switch(op2)
                    {
                        case 1:
                        {
                            analise(100, 4, 1000000, argv[1]);
                        }
                        break;
                        case 2:// modulo teste
                        {
                            busca(argv[1]);
                        }
                        break;
                    }

                    cin >> op2;
                }
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
