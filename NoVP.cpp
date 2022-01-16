#include "NoVP.h"

NoVP::NoVP(ReviewNode *info){
    this->info = info;
    this->esq = nullptr;
    this->dir = nullptr;
    this->pai = nullptr;
    this->cor = VERMELHO;
}

NoVP::~NoVP(){

}

ReviewNode *NoVP::getInfo(){
    return this->info;
}

NoVP *NoVP::getEsq(){
    return this->esq;
}

NoVP *NoVP::getDir(){
    return this->dir;
}

NoVP *NoVP::getPai(){
    return this->pai;
}

int NoVP::getCor(){
    return this->cor;
}

void NoVP::setInfo(ReviewNode *info){
    this->info = info;
}

void NoVP::setEsq(NoVP *esq){
    this->esq = esq;
}

void NoVP::setDir(NoVP *dir){
    this->dir = dir;
}

void NoVP::setPai(NoVP *pai){
    this->pai = pai;
}

void NoVP::setCor(int cor){
    this->cor = cor;
}

void NoVP::recolore(){
    if(this->cor == VERMELHO){
        this->cor = PRETO;
    }
    else{
        this->cor = VERMELHO;
    }
}
