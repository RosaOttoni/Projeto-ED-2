#define FILEIO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <ctime>
#include "Review.h"
#include "FileIO.h"
#include "ReviewNode.h"
#include <random>

using namespace std;

int num_registro;

random_device rd;

default_random_engine gen{rd()};

void acessaRegistro(int i, char *diretorio){
    Review* review = new Review();

    char nomeArquivo[200];

    sprintf(nomeArquivo, "%s%s", diretorio, "tiktok_app_reviews.bin");

    ifstream infile(nomeArquivo,ios::binary);

    infile.seekg(i*sizeof(Review));
    infile.read((char*)review, sizeof(Review));

    cout << "Review ID: " << review->getReview_id() << endl;
    cout << "Review Text: " << review->getReview_text() << endl;
    cout << "Upvotes: " << review->getUpvotes() << endl;
    cout << "App Version: " << review->getApp_version() << endl;
    cout << "Posted Date: " << review->getPosted_date() << endl<<endl;
    infile.close();
}

void geraArquivo(int n, int *vet){

    ifstream infile("tiktok_app_reviews.bin",ios::binary);
    ofstream arq("Dados.txt");

    for(int i=0;i<n;i++){
        Review* review = new Review();
        //cout<<"vetooooor ["<< i<<"]  "<<vet[i]<<endl;
        infile.seekg(vet[i]*sizeof(Review));
        infile.read((char*)review, sizeof(Review));

        arq << review->getReview_id()<< ", " ;
        arq << review->getReview_text()<< ", ";
        arq << review->getUpvotes()<< ", " ;
        arq << review->getApp_version()<< ", ";
        arq << review->getPosted_date() << endl;

    }
    cout<<"Registros salvos no arquivo Dados.txt"<<endl;
    infile.close();
    arq.close();
}
void leituraCsv(string diretorio){
    ifstream infile;
    ofstream outfile;

    infile.open(diretorio + "tiktok_app_reviews.csv",ios::in);
    outfile.open("tiktok_app_reviews.bin",ios::binary);

    string linha, linhaAux;

    num_registro = 0;

    if(!infile) {
        cout << "Nao foi possivel ler o arquivo" << endl;
        exit(EXIT_FAILURE);
    }

    cout<<endl<< "CARREGANDO ARQUIVO CSV, CRIANDO E CONVERTENDO PARA ARQUIVO BINARIO..."<<endl<<endl;

    getline(infile, linhaAux);

    while(!infile.eof()){

        getline(infile, linhaAux);

        linha = "";

        for(int i = 0; i < linhaAux.size(); i++){
            if(linhaAux[i] >= 0 && linhaAux[i] <= 255){
                linha += linhaAux[i];
            }
        }

        try{
            int pos = linha.find(",");

            string id = linha.substr(0, pos);
            linha.erase(0, pos+1);

            pos = linha.find_last_of(",");
            string posted_date = linha.substr(pos+1, linha.length());
            linha.erase(pos, linha.length());

            pos = linha.find_last_of(",");
            string app_version = linha.substr(pos+1, linha.length());
            linha.erase(pos, linha.length());

            pos = linha.find_last_of(",");
            int upvotes = stoi(linha.substr(pos+1, linha.length()));
            linha.erase(pos, linha.length());

            linha = linha.substr(0,1000);

            Review* review = new Review(const_cast<char*>(id.c_str()), const_cast<char*>(linha.c_str()), const_cast<char*>(app_version.c_str()), const_cast<char*>(posted_date.c_str()), upvotes);
            outfile.write((char*)review, sizeof(Review));

            delete review;

            num_registro++;

        }catch(exception e){
            continue;
        }
    }

    infile.close();
    outfile.close();

    cout<<"ARQUIVO BINARIO CRIADO COM SUCESSO"<<endl<<endl;

}

void importaConjunto(int n, Review *vet[]){
    int aux;

    ifstream infile("tiktok_app_reviews.bin",ios::binary);

    uniform_int_distribution<> distribuicao(0, num_registro-1);

    for(int i = 0; i < n; i++){
        //aux = rand()% num_registro;
        aux = distribuicao(gen);
        vet[i] = new Review;
        infile.seekg(aux* sizeof(Review));
        infile.read((char*) vet[i], sizeof(Review));
    }
    infile.close();
}

void importaConjunto (char *nomeDiretorio, int n, Review *vet[]){
    int aux;

    char nomeArquivo[200];

    sprintf(nomeArquivo, "%s%s", nomeDiretorio, "tiktok_app_reviews.bin");

    ifstream infile(nomeArquivo,ios::binary);

    uniform_int_distribution<> distribuicao(0, num_registro-1);

    for(int i = 0; i < n; i++){
        //aux = rand()% num_registro;
        aux = distribuicao(gen);
        vet[i] = new Review;
        infile.seekg(aux* sizeof(Review));
        infile.read((char*) vet[i], sizeof(Review));
    }
    infile.close();
}

void importaConjunto (char *nomeDiretorio, int n, ReviewNode *vet[], int indicesBusca[], int m){
    int aux;

    char nomeArquivo[200];

    sprintf(nomeArquivo, "%s%s", nomeDiretorio, "tiktok_app_reviews.bin");

    ifstream infile(nomeArquivo,ios::binary);

    if(infile.is_open()){
        uniform_int_distribution<> distribuicao(0, num_registro-1);
        for(int i = 0; i < n; i++){
            //aux = (rand()/(float)RAND_MAX)* num_registro;
            aux = distribuicao(gen);
            Review *auxReview = new Review;
            infile.seekg(aux* sizeof(Review));
            infile.read((char*) auxReview, sizeof(Review));
            vet[i] = new ReviewNode(auxReview->getReview_id(), aux);
            delete auxReview;
        }
        infile.close();

        uniform_int_distribution<> distribuicaoIndices(0, n-1);
        for(int i = 0; i < m; i++){
            aux = distribuicaoIndices(gen);
            indicesBusca[i] = aux;
        }
    }
    else{
        cout << "Arquivo de entrada nao encontrado no diretorio especificado!" << endl;
        exit(1);
    }
}

void imprimeConjunto (int n, Review *vet[]){

    for(int i = 0; i < n; i++){
        //cout << "Review ID: " << vet[i]->getReview_id() << endl;
        //<< "Review Text: " << vet[i]->getReview_text() << endl;
        cout << "Upvotes: " << vet[i]->getUpvotes() << endl;
        //cout << "App Version: " << vet[i]->getApp_version() << endl;
        cout << "Posted Date: " << vet[i]->getPosted_date() << endl<<endl;
    }
}

