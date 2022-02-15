#include "ArvoreHuffman.h"
#include "NoHuffman.h"
#include <cstddef>
#include <fstream>
#include <string>

using namespace std;

ArvoreHuffman::ArvoreHuffman(string frase)
{
    chave = frase;// inicia a chave com o valor recebido
    alfabeto = new NoHuffman*[chave.size()](); 
    frequencia = new int[chave.size()](); //calcula a frequencia
    tamanhoAlf = criaAlfabeto(chave); //cria o alfabeto
    construirArvore(); //gera a arvore de huffman
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
//verifica se caractere foi encontrado, senão retorna -1
int ArvoreHuffman::verifica(char c, int tam)
{
    for(int i = 0; i < tam; i++)
    {
        if(c == alfabeto[i]->getChave()) return i;
    }
    return -1;
}
//Construçao do alfabeto da arvore de Huffman
int ArvoreHuffman::criaAlfabeto(string chave)
{
    int aux = 0;
    for(unsigned int i = 0; i < chave.size(); i++)
    {
        int posicao = verifica(chave[i],aux);//verifica se caractere foi encontrado
        //Se não foi encontrado no alfabeto, insere um novo 
        if(posicao == -1)
        {
            alfabeto[aux] = new NoHuffman(chave[i],1);
            frequencia[aux] = 1;
            aux++;
        }
        //Se foi encontrado no alfabeto, atualiza a frequencia
        else
        {
            frequencia[posicao]++;
            alfabeto[posicao]->setFreq(alfabeto[posicao]->getFreq()+1);
        }
    }
    return aux;
}

//Construcao da Arvore de Huffman
void ArvoreHuffman::construirArvore()
{
    inserir(tamanhoAlf);
    int tamanho = tamanhoAlf;
    while(tamanho != 0)
    {
    //Inicio do alfabeto, insere a raiz
        if(tamanho == 1)
        {   raiz = alfabeto[0];
            break;
        }
        const char *c = "/0";
        NoHuffman* pai = new NoHuffman(*c ,alfabeto[0]->getFreq() + alfabeto[1]->getFreq()); //cria nó pai
        frequencia[0] = INT_MAX; //atualizando a  frequencia pro max
        //Associando 0 com a esquerda e 1 com a direita
        pai->setEsq(alfabeto[0]); //filho a esquerda
        pai->setDir(alfabeto[1]); //filho a direta

        frequencia[1] = pai->getFreq(); //atualizando a  frequencia do pai
        alfabeto[1] = pai; //insere pai no alfabeto
        inserir(tamanho); //ordenando pelas frequencias com insertion Sort
        tamanho--;
    }
}

//funcao que ordena as frequencias  utilizando algoritmo insertionSort
void ArvoreHuffman::inserir(int tam)
{
    int aux,j;
    for(int i=1; i<tam; i++)
    {
        NoHuffman* auxLetra = alfabeto[i];
        aux = frequencia[i];
        j = i-1;
        while(j >= 0 && frequencia[j] > aux)
        {
            frequencia[j+1] = frequencia[j];
            alfabeto[j+1] = alfabeto[j];
            j = j-1;
        }
        frequencia[j+1] = aux;
        alfabeto[j+1] = auxLetra;
    }
}