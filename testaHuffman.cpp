#include "testaHuffman.h"
#include "Huffman.h"
#include "Review.h"
#include "FileIO.h"

void testaHuffman(){
    int m = 3;
    int N[] = {10000, 100000, 1000000};

    float mediaComparacoes, mediaTaxaComp;

    ofstream arq;
    arq.open("saida.txt");

    if(arq){
        for(int i = 0; i < 3; i++){
            int n = N[i];

            mediaComparacoes = 0;
            mediaTaxaComp = 0;

            cout << "Gerando resultados para N = " << n << endl;

            arq << "Resultados da compressao para N = " << n << endl;

            arq << setw(12) << "Execucao" << " | " << setw(12) << "Comparacoes" << " | ";
            arq << setw(12) << "Taxa de Compressao" << " | " << endl;
            arq << "-------------------------------------------------------------------------------" << endl;

            for(int j = 1; j <= m; j++){

                Review **reviews;
                reviews = new Review*[n];

                importaConjunto(n, reviews);

                Huffman *huffman = new Huffman(reviews, n);

                float taxaComp = huffman->compressao(reviews, n);

                arq << setw(6) << j << setw(16) << huffman->getComparacoes() << setw(16) << taxaComp << endl;

                mediaComparacoes += huffman->getComparacoes();
                mediaTaxaComp += taxaComp;

                delete huffman;

                for(int i = 0; i < n; i++){
                    delete reviews[i];
                }

                delete []reviews;
            }
            arq << "-------------------------------------------------------------------------------" << endl;
            arq << setw(6) << "Media" << setw(16) << mediaComparacoes/m << setw(16) << mediaTaxaComp/m << endl;
        }

        arq.close();
    }
    else{
        cout << "Nao foi possivel abrir o arquivo de saida!" << endl;
    }
}
