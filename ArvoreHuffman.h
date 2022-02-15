#ifndef ARVOREHUFFMAN_H_INCLUDED
#define ARVOREHUFFMAN_H_INCLUDED
#include "NoHuffman.h"
#include <string>

using namespace std;


class ArvoreHuffman
{
    public:
        ArvoreHuffman(string frase); 
        ~ArvoreHuffman(); 

    private:
        string chave; //Chave a ser codificada
        NoHuffman* raiz; //Nó raiz    
        NoHuffman** alfabeto; //Nós da árvore 
        int* frequencia; //Vetor de frequências
        int tamanhoAlf; //guarda o tamanho do alfabeto

        void deletaNo(NoHuffman* p); 
        int verifica(char c, int tam);
        int criaAlfabeto(string chave);
        void construirArvore();
        void inserir(int tam);
};

#endif // ARVOREHUFFMAN_H_INCLUDED