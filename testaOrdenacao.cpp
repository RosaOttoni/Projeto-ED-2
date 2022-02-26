#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include "Review.h"
#include "FileIO.h"
#include "testaOrdenacao.h"
#include "Ordenacao.h"


using namespace std;
using namespace std::chrono;


void testaQuickSort(){
        int comparacao, movimentacao, m = 5, n;

        double mediaComparacao = 0, mediaMovimentacao = 0, mediaTempo = 0, tempo;

        ofstream arq("Saida_QuickSort.txt");
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
                tempo = duration_cast<milliseconds>(fim - inicio).count();

                mediaComparacao += comparacao;
                mediaMovimentacao += movimentacao;
                mediaTempo += tempo;
                arq << setw(6) << j+1 << setw(20) << comparacao << setw(12) << movimentacao << setw(20) << tempo << endl;

                for(int i = 0; i < n; i++){
                    delete vet[i];
                }
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
}

void testaHeapkSort(){
        int comparacao, movimentacao, m = 5, n;

        double mediaComparacao = 0, mediaMovimentacao = 0, mediaTempo = 0, tempo;

        ofstream arq("Saida_HeapSort.txt");
        ifstream input;

        arq << "Resultados do HeapSort" << endl;
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
                heapSort(vet, n, comparacao, movimentacao);
                high_resolution_clock::time_point fim = high_resolution_clock::now();
                tempo = duration_cast<milliseconds>(fim - inicio).count();

                mediaComparacao += comparacao;
                mediaMovimentacao += movimentacao;
                mediaTempo += tempo;
                arq << setw(6) << j+1 << setw(20) << comparacao << setw(12) << movimentacao << setw(20) << tempo << endl;

                for(int i = 0; i < n; i++){
                    delete vet[i];
                }
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
}

void testaTimkSort(){
        double comparacao, movimentacao;
        int m = 5, n;

        double mediaComparacao = 0, mediaMovimentacao = 0, mediaTempo = 0, tempo;

        ofstream arq("Saida_TimSort.txt");
        ifstream input;

        arq << "Resultados do TimSort" << endl;
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
                timSort(vet, n, comparacao, movimentacao );
                high_resolution_clock::time_point fim = high_resolution_clock::now();
                tempo = duration_cast<milliseconds>(fim - inicio).count();

                mediaComparacao += comparacao;
                mediaMovimentacao += movimentacao;
                mediaTempo += tempo;
                arq << setw(6) << j+1 << setw(20) << comparacao << setw(12) << movimentacao << setw(20) << tempo << endl;

                for(int k = 0; k < n; k++){
                    delete vet[k];
                }
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
}
