#include "ArvoreVermelhoPreto.h"
#include <string.h>
#include <iostream>

using namespace std;

ArvoreVermelhoPreto::ArvoreVermelhoPreto(){
    this->raiz = nullptr;
}

ArvoreVermelhoPreto::~ArvoreVermelhoPreto(){
    raiz = libera(raiz);
}

NoVP* ArvoreVermelhoPreto::libera(NoVP *p){
    if(p != nullptr){
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = nullptr;
    }
    return p;
}


bool ArvoreVermelhoPreto::vazia(){
    if(this->raiz == nullptr){
        return true;
    }
    return false;
}

char ArvoreVermelhoPreto::printCor(int cor){
    if(cor == VERMELHO){
        return 'V';
    }
    return 'P';
}

void ArvoreVermelhoPreto::imprime()
{
    cout << endl;
    imprimePorNivel(this->raiz, 0);
}

void ArvoreVermelhoPreto::imprimePorNivel(NoVP *p, int nivel)
{
    if(p != nullptr)
    {
        cout << "(" << nivel << ") ";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        cout << p->getInfo()->getId() << "(" << printCor(p->getCor()) << ")" << endl;
        imprimePorNivel(p->getEsq(), nivel+1);
        imprimePorNivel(p->getDir(), nivel+1);
    }
}

NoVP *ArvoreVermelhoPreto::getAvo(NoVP *no){
    return no->getPai()->getPai();
}

NoVP *ArvoreVermelhoPreto::getTio(NoVP *no){
    NoVP *avo = getAvo(no);

    if(strcmp(no->getInfo()->getId(), avo->getInfo()->getId()) < 0){
        return avo->getDir();
    }
    else{
        return avo->getEsq();
    }
}

int ArvoreVermelhoPreto::getCor(NoVP *no){
    if(no == nullptr){
        return PRETO;
    }
    return no->getCor();
}

NoVP *ArvoreVermelhoPreto::rotacaoSimplesEsquerda(NoVP *p){
    NoVP *q = p->getDir();
    q->setPai(p->getPai());
    if(q->getEsq() != nullptr){
        q->getEsq()->setPai(p);
    }
    p->setDir(q->getEsq());
    p->setPai(q);
    q->setEsq(p);
    return q;
}

NoVP *ArvoreVermelhoPreto::rotacaoSimplesDireita(NoVP *p){
    NoVP *q = p->getEsq();
    q->setPai(p->getPai());
    if(q->getDir() != nullptr){
        q->getDir()->setPai(p);
    }
    p->setEsq(q->getDir());
    p->setPai(q);
    q->setDir(p);
    return q;
}

NoVP *ArvoreVermelhoPreto::rotacaoDuplaEsquerda(NoVP *p){
    NoVP *q = p->getDir();
    NoVP *r = q->getEsq();
    if(r->getEsq() != nullptr){
        r->getEsq()->setPai(p);
    }
    p->setDir(r->getEsq());
    if(r->getDir() != nullptr){
        r->getDir()->setPai(q);
    }
    q->setEsq(r->getDir());
    r->setEsq(p);
    p->setPai(r);
    if(q != nullptr){
        q->setPai(r);
    }
    r->setDir(q);
    return r;
}

NoVP *ArvoreVermelhoPreto::rotacaoDuplaDireita(NoVP *p){
    NoVP *q = p->getEsq();
    NoVP *r = q->getDir();
    if(r->getDir() != nullptr){
        r->getDir()->setPai(p);
    }
    p->setEsq(r->getDir());
    if(r->getEsq() != nullptr){
        r->getEsq()->setPai(q);
    }
    q->setDir(r->getEsq());
    r->setDir(p);
    p->setPai(r);
    if(q != nullptr){
        q->setPai(r);
    }
    r->setEsq(q);
    return r;
}

void ArvoreVermelhoPreto::consertaInsercao(NoVP *no){
    NoVP *avo = getAvo(no);
    NoVP *pai = no->getPai();

    if(avo != nullptr){
        NoVP *tio = getTio(no);
        //Caso 2
        if(getCor(no) == VERMELHO && getCor(pai) == VERMELHO && getCor(tio) == VERMELHO){
            pai->recolore();
            tio->recolore();
            avo->recolore();
            if(avo->getPai() == nullptr){
                avo->setCor(PRETO);
            }
            else{
                consertaInsercao(avo);
            }
        }
        else{
            //Caso 3
            if(getCor(no) == VERMELHO && getCor(pai) == VERMELHO && getCor(tio) == PRETO){
                    //Se avô menor que pai o nó está na sub-árvore direita
                if(strcmp(avo->getInfo()->getId(), pai->getInfo()->getId()) < 0){
                    //Se pai menor que nó, ele está na sub-árvore direita(rotação simples a esquerda)
                    if(strcmp(pai->getInfo()->getId(), no->getInfo()->getId()) < 0){
                        pai->recolore();
                        avo->recolore();
                        // Se o no for a raiz, deve-se atualizar o ponteiro da raiz
                        if(avo->getPai() == nullptr){
                            this->raiz = rotacaoSimplesEsquerda(avo);
                            this->raiz->setPai(nullptr);
                        }
                        else{
                            NoVP *bisavo = avo->getPai();
                            if(strcmp(bisavo->getInfo()->getId(), avo->getInfo()->getId()) < 0){
                                NoVP *filho = rotacaoSimplesEsquerda(avo);
                                bisavo->setDir(filho);
                                filho->setPai(bisavo);
                                consertaInsercao(filho);
                            }
                            else{
                                NoVP *filho = rotacaoSimplesEsquerda(avo);
                                bisavo->setEsq(filho);
                                filho->setPai(bisavo);
                                consertaInsercao(filho);
                            }
                        }

                        if(getCor(raiz) == VERMELHO){
                            raiz->setCor(PRETO);
                        }
                    }
                    else{
                        //Se pai não é menor que nó, ele está na sub-árvore esquerda(rotação dupla a esquerda)
                        no->recolore();
                        avo->recolore();
                        // Se o no for a raiz, deve-se atualizar o ponteiro da raiz
                        if(avo->getPai() == nullptr){
                            this->raiz = rotacaoDuplaEsquerda(avo);
                            this->raiz->setPai(nullptr);
                        }
                        else{
                            NoVP *bisavo = avo->getPai();
                            if(strcmp(bisavo->getInfo()->getId(), avo->getInfo()->getId()) < 0){
                                NoVP *filho = rotacaoDuplaEsquerda(avo);
                                bisavo->setDir(filho);
                                filho->setPai(bisavo);
                                consertaInsercao(filho);
                            }
                            else{
                                NoVP *filho = rotacaoDuplaEsquerda(avo);
                                bisavo->setEsq(filho);
                                filho->setPai(bisavo);
                                consertaInsercao(filho);
                            }
                        }

                        if(getCor(raiz) == VERMELHO){
                            raiz->setCor(PRETO);
                        }
                    }
                }
                else{
                    //Se avô maior que pai o nó está na sub-árvore esquerda
                    if(strcmp(pai->getInfo()->getId(), no->getInfo()->getId()) > 0){
                        //Se pai maior que nó, ele está na sub-árvore esquerda(rotação simples a direita)
                        pai->recolore();
                        avo->recolore();
                        // Se o no for a raiz, deve-se atualizar o ponteiro da raiz
                        if(avo->getPai() == nullptr){
                            this->raiz = rotacaoSimplesDireita(avo);
                            this->raiz->setPai(nullptr);
                        }
                        else{
                            NoVP *bisavo = avo->getPai();
                            if(strcmp(bisavo->getInfo()->getId(), avo->getInfo()->getId()) < 0){
                                NoVP *filho = rotacaoSimplesDireita(avo);
                                bisavo->setDir(filho);
                                filho->setPai(bisavo);
                                consertaInsercao(filho);
                            }
                            else{
                                NoVP *filho = rotacaoSimplesDireita(avo);
                                bisavo->setEsq(filho);
                                filho->setPai(bisavo);
                                consertaInsercao(filho);
                            }
                        }

                        if(getCor(raiz) == VERMELHO){
                            raiz->setCor(PRETO);
                        }
                    }
                    else{
                        //Se pai não é maior que nó, ele está na sub-árvore direita(rotação dupla a direita)
                        no->recolore();
                        avo->recolore();
                        // Se o no for a raiz, deve-se atualizar o ponteiro da raiz
                        if(avo->getPai() == nullptr){
                            this->raiz = rotacaoDuplaDireita(avo);
                            this->raiz->setPai(nullptr);
                        }
                        else{
                            NoVP *bisavo = avo->getPai();
                            if(strcmp(bisavo->getInfo()->getId(), avo->getInfo()->getId()) < 0){
                                NoVP *filho = rotacaoDuplaDireita(avo);
                                bisavo->setDir(filho);
                                filho->setPai(bisavo);
                                consertaInsercao(filho);
                            }
                            else{
                                NoVP *filho = rotacaoDuplaDireita(avo);
                                bisavo->setEsq(filho);
                                filho->setPai(bisavo);
                                consertaInsercao(filho);
                            }
                        }

                        if(getCor(raiz) == VERMELHO){
                            raiz->setCor(PRETO);
                        }
                    }
                }
            }
        }
    }
}

void ArvoreVermelhoPreto::insere(ReviewNode *info, int &comparacoes){
    comparacoes = 0;
    //Caso 1
    if(vazia()){
        raiz = new NoVP(info);
        raiz->setCor(PRETO);
    }
    else{
        //raiz = auxInsere(nullptr, raiz, info);
        NoVP *aux = raiz;
        NoVP *pai = nullptr;
        NoVP *no  = new NoVP(info);

        //Encontra a posição de inserção e o pai
        while(aux != nullptr){
            pai = aux;
            comparacoes++;
            if(strcmp(no->getInfo()->getId(), aux->getInfo()->getId()) < 0){
                aux = aux->getEsq();
            }
            else{
                if(strcmp(no->getInfo()->getId(), aux->getInfo()->getId()) > 0){
                    aux = aux->getDir();
                }
                else{
                    // Se chave for repetida, não insere na árvore
                    delete no;
                    return;
                }
            }
        }
        no->setPai(pai);

        //Decide se é filho a direita ou esquerda
        comparacoes++;
        if(strcmp(no->getInfo()->getId(), pai->getInfo()->getId()) < 0){
            pai->setEsq(no);
        }
        else{
            pai->setDir(no);
        }
        consertaInsercao(no);
    }
}

ReviewNode *ArvoreVermelhoPreto::busca(char* id, int &comparacoes){
    NoVP *aux = this->raiz;
    comparacoes = 0;

    //Encontra a posição de inserção e o pai
    while(aux != nullptr){
        comparacoes++;
        if(strcmp(id, aux->getInfo()->getId()) == 0){
            return aux->getInfo();
        }
        else{
            comparacoes++;
            if(strcmp(id, aux->getInfo()->getId()) < 0){
                aux = aux->getEsq();
            }
            else{
                aux = aux->getDir();
            }
        }
    }
    return nullptr;
}

