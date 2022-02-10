#include "ArvoreHuffman.h"
#include "NoHuffman.h"

using namespace std;

ArvoreHuffman::ArvoreHuffman(string frase)
{
    chave = frase;// inicia a chave com o valor recebido
    alfabeto = new NoHuffman*[chave.size()](); 
    frequencia = new int[chave.size()](); //calcula a frequencia
    tamamho = criaAlfabeto(chave); //cria o alfabeto
    criaArvore(); //gera a arvore de huffman
}
ArvoreHuffman::~ArvoreHuffman()
{
    deletaNo(raiz);
}
void ArvoreHuffman::deletaNo(NoHuffman* no)
{// funcao auxliar de destrutor para deletar os nos da arvore
    if(no->getEsq()!=NULL)
        deletaNo(no->getEsq()); 
    if (no->getDir()!=NULL)
        deletaNo(no->getDir()); 
    delete no; //deleta raiz principal
}
void ArvoreHuffman::criaArvore()
{}

