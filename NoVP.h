#ifndef NOVP_H_INCLUDED
#define NOVP_H_INCLUDED

#define VERMELHO 0
#define PRETO 1

#include "ReviewNode.h"

class NoVP{
    private:
        ReviewNode *info;
        NoVP *esq;
        NoVP *dir;
        NoVP *pai;
        int cor;

    public:
        NoVP(ReviewNode *info);

        ~NoVP();

        //Getters
        ReviewNode *getInfo();

        NoVP *getEsq();

        NoVP *getDir();

        NoVP *getPai();

        int getCor();

        //Setters
        void setInfo(ReviewNode *info);

        void setEsq(NoVP *esq);

        void setDir(NoVP *dir);

        void setPai(NoVP *pai);

        void setCor(int cor);

        void recolore();
};

#endif // NOVP_H_INCLUDED
