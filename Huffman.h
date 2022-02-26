#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#include "Review.h"
#include <string>
#include <vector>

typedef struct{
    char caractere;
    int frequencia;
}itemTabela;

class NoHuffman{
    private:
        int freq;
        char caractere;
        string cod;
        NoHuffman *esq;
        NoHuffman *dir;

    public:
        NoHuffman();

        ~NoHuffman();

        int getFreq();
        char getCaractere();
        string getCod();
        NoHuffman *getEsq();
        NoHuffman *getDir();

        void setFreq(int freq);
        void setCaractere(char caractere);
        void setEsq(NoHuffman *esq);
        void setDir(NoHuffman *dir);
        void setCod(string cod);
};

class Huffman{

    private:

        NoHuffman* listaNosHeap[256];

        NoHuffman* listaNos[256];

        int tamanhoTabela;

        NoHuffman *raiz;

        int comparacoes;

        void criaHeap();

        void troca(int i, int j);

        void subir(int i);

        void descer(int i);

        void inserir(NoHuffman *no);

        NoHuffman *remover();

        void criaArvore();

        void imprimePorNivel(NoHuffman *p, int nivel);

        void geraCodigo(NoHuffman *no, string codigo);

        string decimalParaBinario(int in);

        int binarioParaDecimal(string in);

        NoHuffman* libera(NoHuffman *p);

    public:

        Huffman(Review *vetor[], int n);

        ~Huffman();

        int getComparacoes();

        void imprimeArvoreHuffman();

        float compressao(Review *vetor[], int n);

        void descompressao(char nomeArquivo[]);
};




#endif // HUFFMAN_H_INCLUDED
