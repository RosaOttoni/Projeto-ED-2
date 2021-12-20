#include "Review.h"
#include "FileIO.h"
#include "Ordenacao.h"
#include <fstream>
#include <iomanip>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

void imprimeMenu(){
    cout<<endl<<" ____________________________MENU____________________________"<<endl;
    cout<<"| Para acessar um registro especifico do arquivo, digite [1] |"<<endl;
    cout<<"| Para teste de importacao digite [2]                        |"<<endl;
    cout<<"| Para finalizar digite [0]                                  |"<<endl;
    cout<<"|____________________________________________________________|"<<endl<<endl;
}

int main(int argc, char const *argv[])
{
    int opM, comparacao, movimentacao, m = 5;
    long int n[5] = {10000, 50000, 100000, 500000, 1000000};
    double mediaComparacao = 0, mediaMovimentacao = 0, mediaTempo = 0, tempo;

    if(argc != 2){
        cout << "Erro: Diretorio nao especificado" << endl;
        return 0;
    }

    ofstream arq("Saida.txt");
    arq << "Resultados do QuickSort" << endl;

    for(int i = 0; i < 5; i++){
        arq << "\nTamanho do conjunto: " << n[i] << endl;
        arq << setw(12) << "Execucao" << " | " << setw(12) << "Comparacoes" << " | ";
        arq << setw(12) << "Movimentacoes" << " | " << setw(12) << "Tempo "  << endl;
        arq << "-------------------------------------------------------------------------------" << endl;
        for(int j = 0; j < m; j++){
            Review **vet = new Review*[n[i]];
            comparacao = 0;
            movimentacao = 0;

            importaConjunto(n[i], vet);

            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            quickSort(vet, 0, n[i] - 1, comparacao, movimentacao);
            high_resolution_clock::time_point fim = high_resolution_clock::now();
            tempo = duration_cast<duration<double>>(fim - inicio).count();

            mediaComparacao += comparacao;
            mediaMovimentacao += movimentacao;
            mediaTempo += tempo;
            arq << setw(6) << j+1 << setw(20) << comparacao << setw(12) << movimentacao << setw(20) << tempo << endl;
            delete[] vet;
        }
        mediaComparacao /= 5;
        mediaMovimentacao /= 5;
        mediaTempo /= 5;

        arq << "-------------------------------------------------------------------------------" << endl;
        arq << setw(6) << "Media" << setw(20) << mediaComparacao << setw(12) << mediaMovimentacao << setw(20) << mediaTempo << endl;
    
    }
    mediaComparacao = 0, mediaMovimentacao = 0, mediaTempo = 0, tempo =0;
    arq << "Resultados do TimSort" << endl;
    for(int i = 0; i < 5; i++){
        arq << "\nTamanho do conjunto: " << n[i] << endl;
        arq << setw(12) << "Execucao" << " | " << setw(12) << "Comparacoes" << " | ";
        arq << setw(12) << "Movimentacoes" << " | " << setw(12) << "Tempo "  << endl;
        arq << "-------------------------------------------------------------------------------" << endl;
        for(int j = 0; j < m; j++){
            Review **vet2 = new Review*[n[i]];
            comparacao = 0;
            movimentacao = 0;

            importaConjunto(n[i], vet2);
           
            high_resolution_clock::time_point inicio = high_resolution_clock::now();
            timSort(vet2, n[i] - 1, comparacao, movimentacao );
            high_resolution_clock::time_point fim = high_resolution_clock::now();
            tempo = duration_cast<duration<double>>(fim - inicio).count();

            mediaComparacao += comparacao;
            mediaMovimentacao += movimentacao;
            mediaTempo += tempo;
            arq << setw(6) << j+1 << setw(20) << comparacao << setw(12) << movimentacao << setw(20) << tempo << endl;
            delete[] vet2;
        }
        mediaComparacao /= 5;
        mediaMovimentacao /= 5;
        mediaTempo /= 5;

        arq << "-------------------------------------------------------------------------------" << endl;
        arq << setw(6) << "Media" << setw(20) << mediaComparacao << setw(12) << mediaMovimentacao << setw(20) << mediaTempo << endl;
    }
    arq.close();

    //leituraCsv(argv[1]);

    /*imprimeMenu();

    cin >> opM;

    while(opM!=0){
        if(opM==1){
            cout<<"Digite o numero do registro que voce gostaria de acessar.";
            int reg;
            cin>>reg;
            cout<<endl;
            acessaRegistro(reg);
        }
        else if(opM==2){
            testeImportacao();
        }
        else{
            cout<<"Erro de digitação, siga as instrucoes do menu e tente de novo."<<endl<<endl;
        }
        imprimeMenu();
        cin >> opM;
    }*/
    return 0;
}
