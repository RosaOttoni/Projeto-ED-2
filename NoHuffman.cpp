#include "NoHuffman.h"
#include <cstddef>

using namespace std;

NoHuffman::NoHuffman(char chave, int freq){
    this->chave = chave; //Chave
    this->freq = freq; //frequencia de vezes qua aparece
    this->esq = nullptr; //Nó a esquerda
    this->dir = nullptr; //Nó a direita
}
bool NoHuffman::ehFolha(){
    return (getEsq() == NULL) && (getDir() == NULL);
}
char NoHuffman::getChave(){
    return this->chave;
}
int NoHuffman::getFreq(){
    return this->freq;
}
NoHuffman* NoHuffman::getEsq(){
    return this->esq;
}
NoHuffman* NoHuffman::getDir(){
    return this->dir;
}
void NoHuffman::setChave(char chave){
    this->chave = chave;
}
void NoHuffman::setFreq(int freq){
    this->freq = freq;
}
void NoHuffman::setEsq(NoHuffman* esq){
    this->esq = esq;
}
void NoHuffman::setDir(NoHuffman* dir){
    this->dir = dir;
}

