#include "Review.h"
#include "FileIO.h"
#include "Ordenacao.h"
#include "testaOrdenacao.h"
#include "TabelaHash.h"
#include "ArvoreVermelhoPreto.h"
#include "Arvores.h"
#include "Huffman.h"
#include "testaHuffman.h"
#include <fstream>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <random>

using namespace std;
using namespace std::chrono;

void imprimeMenu(){
    cout<<"_____________________________MENU________________________________________"<<endl;
    cout<<"| Para executar, escolha uma das opcoes abaixo para gerar as metricas:  |"<<endl;
    cout<<"| 1 - QuickSort                                                         |"<<endl;
    cout<<"| 2 - HeapSort                                                          |"<<endl;
    cout<<"| 3 - TimSort                                                           |"<<endl;
    cout<<"| 4 - Arvore VP                                                         |"<<endl;
    cout<<"| 5 - Arvore B                                                          |"<<endl;
    cout<<"| 6 - Huffman                                                           |"<<endl;
    cout<<"| 7 - SAIR                                                              |"<<endl;
    cout<<"|_______________________________________________________________________|"<<endl<<endl;
}

int main(int argc, char *argv[])
{
    int opcao, n;

    //srand(time(NULL));

    if(argc != 2){
        cout << "Erro: Diretorio nao especificado" << endl;
        return 0;
    }

    leituraCsv(argv[1]);

    imprimeMenu();

    cin >> opcao;

    while(opcao != 7){
        switch(opcao){
            case 1:{
                testaQuickSort();
            }
            break;
            case 2:{
                testaHeapkSort();
            }
            break;
            case 3:{
                testaTimkSort();
            }
            break;
            case 4:{
                analise(100, 4, 1000000, argv[1]);
            }
            break;
            case 5:{
            }
            break;
            case 6:{
                testaHuffman();
            }
            default:
                cout << "Opcao invalida!" << endl;
        }
        imprimeMenu();
        cin >> opcao;
    }

    return 0;
}
