#ifndef ARVOREVERMELHOPRETO_H_INCLUDED
#define ARVOREVERMELHOPRETO_H_INCLUDED

#include "NoVP.h"

class ArvoreVermelhoPreto{
    private:
        NoVP *raiz;

        char printCor(int cor);

        void imprimePorNivel(NoVP *p, int nivel);

        NoVP *getTio(NoVP *no);

        NoVP *getAvo(NoVP *no);

        int getCor(NoVP *no);

        NoVP *rotacaoSimplesEsquerda(NoVP *no);

        NoVP *rotacaoDuplaEsquerda(NoVP *no);

        NoVP *rotacaoSimplesDireita(NoVP *p);

        NoVP *rotacaoDuplaDireita(NoVP *p);

        void consertaInsercao(NoVP *no);

        NoVP* libera(NoVP *p);

    public:
        ArvoreVermelhoPreto();

        ~ArvoreVermelhoPreto();

        bool vazia();

        void imprime();

        void insere(ReviewNode *info,  int &comparacoes);

        ReviewNode *busca(char *id, int &comparacoes);
};

#endif // ARVOREVERMELHOPRETO_H_INCLUDED
