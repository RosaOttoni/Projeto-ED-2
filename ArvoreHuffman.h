#ifndef ARVOREHUFFMAN_H_INCLUDED
#define ARVOREHUFFMAN_H_INCLUDED
#include "NoHuffman.h"

using namespace std;


class ArvoreHuffman
{
    public:
        ArvoreHuffman(); 
        ~ArvoreHuffman(); 

    private:
        string chave; //Chave a ser codificada
        NoHuffman* raiz; //Nó raiz    
        NoHuffman** alfabeto; //Nós da árvore 
        int* frequencia; //Vetor de frequências
        int tamanho; //guarda o tamanho do alfabeto

        void deletaNo(NoHuffman* p); 
        void criaArvore(); 
};

#endif // ARVOREHUFFMAN_H_INCLUDED