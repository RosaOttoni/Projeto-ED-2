#define FILEIO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <ctime>
#include "Review.h"
#include "FileIO.h"
#include "ReviewNode.h"

using namespace std;

const int num_registro = 3660723;

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

    string linha;

    if(!infile) {
        cout << "Nao foi possivel ler o arquivo" << endl;
        exit(EXIT_FAILURE);
    }

    cout<<endl<< "CARREGANDO ARQUIVO CSV, CRIANDO E CONVERTENDO PARA ARQUIVO BINARIO..."<<endl<<endl;

    getline(infile, linha);

    int cont = 0;

    while(!infile.eof()){

        getline(infile, linha);

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

            cont++;

        }catch(exception e){
            continue;
        }
    }

    infile.close();
    outfile.close();

    //cout << "Sucesso: " << cont << endl;
    cout<<"ARQUIVO BINARIO CRIADO COM SUCESSO"<<endl<<endl;

}

void importaConjunto (char *nomeDiretorio, int n, Review *vet[]){
    int aux;

    char nomeArquivo[200];

    sprintf(nomeArquivo, "%s%s", nomeDiretorio, "tiktok_app_reviews.bin");

    ifstream infile(nomeArquivo,ios::binary);

    srand(time(NULL));

    for(int i = 0; i < n; i++){
        aux = rand()% num_registro;
        vet[i] = new Review;
        infile.seekg(aux* sizeof(Review));
        infile.read((char*) vet[i], sizeof(Review));
    }
    infile.close();
}

void importaConjunto (char *nomeDiretorio, int n, ReviewNode *vet[]){
    int aux;

    char nomeArquivo[200];

    sprintf(nomeArquivo, "%s%s", nomeDiretorio, "tiktok_app_reviews.bin");

    ifstream infile(nomeArquivo,ios::binary);

    if(infile.is_open()){

        for(int i = 0; i < n; i++){
            aux = rand()% num_registro;
            Review *auxReview = new Review;
            infile.seekg(aux* sizeof(Review));
            infile.read((char*) auxReview, sizeof(Review));
            vet[i] = new ReviewNode(auxReview->getReview_id(), aux);
            delete auxReview;
        }
        infile.close();
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

