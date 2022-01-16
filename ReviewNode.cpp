#include "ReviewNode.h"

#include <string.h>

ReviewNode::ReviewNode(char *id, int posicaoArquivo){
    strcpy(this->id, id);
    this->posicaoArquivo = posicaoArquivo;
}

ReviewNode::ReviewNode(){}

ReviewNode::~ReviewNode(){}

char * ReviewNode::getId(){
    return this->id;
}

int ReviewNode::getPosicaoArquivo(){
    return posicaoArquivo;
}

void ReviewNode::setId(char* id){
    strcpy(this->id, id);
}

void ReviewNode::setPosicaoArquivo(int posicaoArquivo){
    this->posicaoArquivo = posicaoArquivo;
}
