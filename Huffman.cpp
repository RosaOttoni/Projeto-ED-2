#include "Huffman.h"
#include <string.h>
#include <fstream>

using namespace std;

NoHuffman::NoHuffman(){
    this->freq = 0;
    this->esq = nullptr;
    this->dir = nullptr;
    this->cod = "";
}

NoHuffman::~NoHuffman(){

}

int NoHuffman::getFreq(){
    return this->freq;
}

char NoHuffman::getCaractere(){
    return this->caractere;
}

string NoHuffman::getCod(){
    return this->cod;
}

NoHuffman *NoHuffman::getEsq(){
    return this->esq;
}

NoHuffman *NoHuffman::getDir(){
    return this->dir;
}

int Huffman::getComparacoes(){
    return comparacoes;
}

void NoHuffman::setFreq(int freq){
    this->freq = freq;
}

void NoHuffman::setCaractere(char caractere){
    this->caractere = caractere;
}

void NoHuffman::setEsq(NoHuffman *esq){
    this->esq = esq;
}

void NoHuffman::setDir(NoHuffman *dir){
    this->dir = dir;
}

void NoHuffman::setCod(string cod){
    this->cod = cod;
}

void Huffman::troca(int i, int j){
    NoHuffman *aux = listaNosHeap[i];
    listaNosHeap[i] = listaNosHeap[j];
    listaNosHeap[j] = aux;
}

void Huffman::subir(int i){
    //Para achar o pai
    int p = (i - 1)/2;

    if(p >= 0){
        if(listaNosHeap[i]->getFreq() < listaNosHeap[p]->getFreq()){
            troca(i,p);
            subir(p);
            comparacoes++;
        }
    }
}

void Huffman::descer(int i){
    int menor = i; // inicializa o menor como a raiz
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // se o filho da esquerda é menor que a raiz
    if (l < tamanhoTabela && listaNosHeap[l]->getFreq() < listaNosHeap[menor]->getFreq()){
        menor = l;
        comparacoes++;
    }

    // se o filho da direita é menor que o atual menor
    if (r < tamanhoTabela && listaNosHeap[r]->getFreq() < listaNosHeap[menor]->getFreq()){
        menor = r;
        comparacoes++;
    }

    // se o menor não é a raiz
    if (menor != i) {
        // troca a raiz com o menor
        troca(i, menor);

        // ajusta a subarvore afetada
        descer(menor);
    }
}

void Huffman::inserir(NoHuffman *no){
    //Insere na ultima posicao da lista
    listaNosHeap [tamanhoTabela] = no;
    tamanhoTabela++;
    subir(tamanhoTabela - 1);
}

void Huffman::criaHeap(){
    // Indice do último nó não folha
    int indiceInicial = (tamanhoTabela / 2) - 1;

    // cria o heap ajustando dos nós não folha em ordem reversa
    for (int i = indiceInicial; i >= 0; i--) {
        descer(i);
    }
}

NoHuffman *Huffman::remover(){
    NoHuffman *no = listaNosHeap[0];
    listaNosHeap[0] = listaNosHeap[tamanhoTabela - 1];
    tamanhoTabela--;
    descer(0);
    return no;
}

void Huffman::criaArvore(){
    while(tamanhoTabela > 1){
        NoHuffman *aux = remover();
        raiz = new NoHuffman();
        raiz->setEsq(aux);
        raiz->setFreq(aux->getFreq());
        aux = remover();
        raiz->setDir(aux);
        raiz->setFreq(raiz->getFreq() + aux->getFreq());
        inserir(raiz);
    }
}

void Huffman::imprimeArvoreHuffman()
{
    cout << endl;
    imprimePorNivel(this->raiz, 0);
}

void Huffman::imprimePorNivel(NoHuffman *p, int nivel)
{
    if(p != nullptr)
    {
        cout << "(" << nivel << ") ";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        if(p->getDir() == nullptr && p->getEsq() == nullptr){
            cout << p->getCaractere() << "(" << p->getFreq() << "-->" << p->getCod() << ")" << endl;
        }
        else{
            cout << "(" << p->getFreq() << ")" << endl;
        }

        imprimePorNivel(p->getEsq(), nivel+1);
        imprimePorNivel(p->getDir(), nivel+1);
    }
}

void Huffman::geraCodigo(NoHuffman *no, string codigo){

    //Percorre a arvore para inserir os codigos 0 e 1
    if(no->getDir() == nullptr && no->getEsq() == nullptr){
        no->setCod(codigo);
    }
    else{
        geraCodigo(no->getEsq(), codigo + '0');
        geraCodigo(no->getDir(), codigo + '1');

    }
}

Huffman::Huffman(Review *vetor[], int n){

    comparacoes = 0;

    for(int i = 0; i < 256; i++){
        listaNos[i] = new NoHuffman();
        listaNos[i]->setCaractere(i);
    }

    for(int i = 0; i < n; i++){
        //cout << vetor[i]->getReview_text() << endl;
        for(int j = 0; vetor[i]->getReview_text()[j] != '\0'; j++){
            int caractere = vetor[i]->getReview_text()[j];
            listaNos[caractere]->setFreq(listaNos[caractere]->getFreq()+1);
        }
    }

    tamanhoTabela = 0;

    for(int i = 0; i < 256; i++){
        if(listaNos[i]->getFreq() > 0){
            listaNosHeap[tamanhoTabela] = listaNos[i];
            tamanhoTabela++;
        }
    }

    criaHeap();

    criaArvore();

    string codigo = "";

    geraCodigo(raiz, codigo);
}

float Huffman::compressao(Review *reviews[], int n){

    ofstream outfile;

    int ce = 0, cs = 0;

    outfile.open("reviewsComp.bin",ios::binary);

    string s = "", in = "";

    for(int i = 0; i < n; i++){
        for(int j = 0; reviews[i]->getReview_text()[j] != '\0'; j++){
            int caractere = reviews[i]->getReview_text()[j];
            ce++;
            s += listaNos[caractere]->getCod();
            while (s.size() > 8)
            {
                in += (char)binarioParaDecimal(s.substr(0, 8));
                s = s.substr(8);
                cs++;
            }
        }
    }

	in += (char)binarioParaDecimal(s);
	cs++;

    outfile.write(in.c_str(), in.size());

    outfile.close();

    cout << "Conjunto de registros comprimido para o arquivo reviewsComp.bin" << endl;

    return ((ce-cs)/(float)ce)*100;
}

void Huffman::descompressao(char nomeArquivo[]){
    ifstream infile(nomeArquivo,ios::binary);
    ofstream outfile("reviewsOrig.bin",ios::binary);

    string in = "";

    vector<unsigned char> text;
	unsigned char textseg;
	infile.read(reinterpret_cast<char*>(&textseg), 1);
	while (!infile.eof())
	{
		text.push_back(textseg);
		infile.read(reinterpret_cast<char*>(&textseg), 1);
	}
	NoHuffman *no = raiz;
	string codigo;

	for (int i = 0; i < text.size() - 1; i++)
	{
		codigo = decimalParaBinario(text[i]);
		for (int j = 0; j < codigo.size(); j++)
		{
			if (codigo[j] == '0')
				no = no->getEsq();
			else
				no = no->getDir();
			if (no->getEsq() == nullptr && no->getDir() == nullptr)
			{
				in += no->getCaractere();
				//cout << no->getCaractere() << endl;
				no = raiz;
			}
		}
	}

	outfile.write(in.c_str(), in.size());

    outfile.close();

    infile.close();

    cout << "Conjunto de registros descomprimido para o arquivo reviewsOrig.bin" << endl;
}

int Huffman::binarioParaDecimal(string in)
{
	int result = 0;
	for (int i = 0; i < in.size(); i++)
		result = result * 2 + in[i] - '0';
	return result;
}

string Huffman::decimalParaBinario(int in)
{
	string temp = "";
	string result = "";
	while (in)
	{
		temp += ('0' + in % 2);
		in /= 2;
	}
	result.append(8 - temp.size(), '0');
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		result += temp[i];
	}
	return result;
}

Huffman::~Huffman(){
    raiz = libera(raiz);
}

NoHuffman* Huffman::libera(NoHuffman *p){
    if(p != nullptr){
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = nullptr;
    }
    return p;
}
