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
    cout<<endl<<" ___________________MENU___________________"<<endl;
    cout<<"| Para ordenacao, digite [1]               |"<<endl;
    cout<<"| Para Hash, digite [2]                    |"<<endl;
    cout<<"| Para modulo de teste digite [3]          |"<<endl;
    cout<<"| Para finalizar digite [0]                |"<<endl;
    cout<<"|__________________________________________|"<<endl<<endl;
}

int main(int argc, char const *argv[])
{
    int v[5] = {10000, 50000, 100000, 500000, 1000000};

    ofstream xpto("input.dat", ios::binary);

    xpto.write((char*)v, sizeof(int)*5);

    xpto.close();

    imprimeMenu();
    int auxmenu;
    cin>>auxmenu;

    switch(auxmenu){

        case 1:{

        int opM, comparacao, movimentacao, m = 5, n;
        //int n[5] = {10000, 50000, 100000, 500000, 1000000};
        double mediaComparacao = 0, mediaMovimentacao = 0, mediaTempo = 0, tempo;

        if(argc != 2){
            cout << "Erro: Diretorio nao especificado" << endl;
            return 0;
        }


        ofstream arq("Saida.txt");
        ifstream input;

        arq << "Resultados do QuickSort" << endl;
        input.open("input.dat", ios::binary);

        input.read((char*)&n, sizeof(int));
        while(!input.eof()){

            arq << "\nTamanho do conjunto: " << n << endl;
            arq << setw(12) << "Execucao" << " | " << setw(12) << "Comparacoes" << " | ";
            arq << setw(12) << "Movimentacoes" << " | " << setw(12) << "Tempo "  << endl;
            arq << "-------------------------------------------------------------------------------" << endl;
            for(int j = 0; j < m; j++){
                Review **vet = new Review*[n];
                comparacao = 0;
                movimentacao = 0;

                importaConjunto(n, vet);

                high_resolution_clock::time_point inicio = high_resolution_clock::now();
                quickSort(vet, 0, n - 1, comparacao, movimentacao);
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
            input.read((char*)&n, sizeof(int));
        }
        mediaComparacao = 0, mediaMovimentacao = 0, mediaTempo = 0, tempo =0;
        input.close();

        arq << "Resultados do TimSort" << endl;
        input.open("input.dat", ios::binary);
        input.read((char*)&n, sizeof(int));

        while(!input.eof()){

            arq << "\nTamanho do conjunto: " << n << endl;
            arq << setw(12) << "Execucao" << " | " << setw(12) << "Comparacoes" << " | ";
            arq << setw(12) << "Movimentacoes" << " | " << setw(12) << "Tempo "  << endl;
            arq << "-------------------------------------------------------------------------------" << endl;
            for(int j = 0; j < m; j++){
                Review **vet2 = new Review*[n];
                comparacao = 0;
                movimentacao = 0;

                importaConjunto(n, vet2);

                high_resolution_clock::time_point inicio = high_resolution_clock::now();
                timSort(vet2, n - 1, comparacao, movimentacao );
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
            input.read((char*)&n, sizeof(int));
        }

        mediaComparacao = 0, mediaMovimentacao = 0, mediaTempo = 0, tempo =0;
        input.close();

        arq << "Resultados do HeapSort" << endl;
        input.open("input.dat", ios::binary);
        input.read((char*)&n, sizeof(int));

        while(!input.eof()){

            arq << "\nTamanho do conjunto: " << n << endl;
            arq << setw(12) << "Execucao" << " | " << setw(12) << "Comparacoes" << " | ";
            arq << setw(12) << "Movimentacoes" << " | " << setw(12) << "Tempo "  << endl;
            arq << "-------------------------------------------------------------------------------" << endl;
            for(int j = 0; j < m; j++){
                Review **vet3 = new Review*[n];
                comparacao = 0;
                movimentacao = 0;

                importaConjunto(n, vet3);

                high_resolution_clock::time_point inicio = high_resolution_clock::now();
                heapSort(vet3, n, comparacao, movimentacao );
                high_resolution_clock::time_point fim = high_resolution_clock::now();
                tempo = duration_cast<duration<double>>(fim - inicio).count();

                mediaComparacao += comparacao;
                mediaMovimentacao += movimentacao;
                mediaTempo += tempo;
                arq << setw(6) << j+1 << setw(20) << comparacao << setw(12) << movimentacao << setw(20) << tempo << endl;

                delete[] vet3;
            }
            mediaComparacao /= 5;
            mediaMovimentacao /= 5;
            mediaTempo /= 5;

            arq << "-------------------------------------------------------------------------------" << endl;
            arq << setw(6) << "Media" << setw(20) << mediaComparacao << setw(12) << mediaMovimentacao << setw(20) << mediaTempo << endl;
            input.read((char*)&n, sizeof(int));
        }
        input.close();
        arq.close();
        }
        break;

        case 2:{}
        break;

        case 3:{

            ofstream teste("teste.txt");
            Review **vet4 = new Review*[100];
            int comparacao, movimentacao;

            importaConjunto(100, vet4);
            quickSort(vet4, 0, 99, comparacao, movimentacao);

            teste << "Saida do QuickSort" << endl;
            for(int i = 0; i < 99; i++){
                teste << "Review ID: " << vet4[i]->getReview_id() << endl;
                teste << "Review Text: " << vet4[i]->getReview_text() << endl;
                teste << "Upvotes: " << vet4[i]->getUpvotes() << endl;
                teste << "App Version: " << vet4[i]->getApp_version() << endl;
                teste << "Posted Date: " << vet4[i]->getPosted_date() << endl<<endl;
            }

            importaConjunto(100, vet4);
            timSort(vet4,100,comparacao, movimentacao);

            teste << "Saida do TimSort" << endl;
            for(int i = 0; i < 99; i++){
                teste << "Review ID: " << vet4[i]->getReview_id() << endl;
                teste << "Review Text: " << vet4[i]->getReview_text() << endl;
                teste << "Upvotes: " << vet4[i]->getUpvotes() << endl;
                teste << "App Version: " << vet4[i]->getApp_version() << endl;
                teste << "Posted Date: " << vet4[i]->getPosted_date() << endl<<endl;
            }

            importaConjunto(100, vet4);
            heapSort(vet4, 100, comparacao, movimentacao);

            teste << "Saida do HeapSort" << endl;
            for(int i = 0; i < 99; i++){
                teste << "Review ID: " << vet4[i]->getReview_id() << endl;
                teste << "Review Text: " << vet4[i]->getReview_text() << endl;
                teste << "Upvotes: " << vet4[i]->getUpvotes() << endl;
                teste << "App Version: " << vet4[i]->getApp_version() << endl;
                teste << "Posted Date: " << vet4[i]->getPosted_date() << endl<<endl;
            }
        }
            break;
    }


    return 0;
}
