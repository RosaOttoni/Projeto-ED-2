#ifndef NOHUFFMAN_H_INCLUDED
#define NOHUFFMAN_H_INCLUDED

#include "ReviewNode.h"

using namespace std;

class NoHuffman
{
    private:
        
        char chave;
        int freq; 
        NoHuffman* esq; 
        NoHuffman* dir; 

    public:
        NoHuffman(char chave, int freq); 
        bool ehFolha(); 
        char getChave();
        void setChave(char chave);
        int getFreq();
        void setFreq(int freq);
        NoHuffman* getEsq();
        void setEsq(NoHuffman* esq);
        NoHuffman* getDir();
        void setDir(NoHuffman* dir);

};

#endif // NOHUFFMAN_H_INCLUDED
