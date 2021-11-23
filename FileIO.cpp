#define FILEIO_H_INCLUDED
#include <iostream>
#include <fstream>
#include <ctime>
#include "Review.h"
#include "FileIO.h"

using namespace std;

const int num_registro = 3660723;

void acessaRegistro(int i){
    Review* review = new Review();

    ifstream infile("tiktok_app_reviews.bin",ios::binary);

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

void testeImportacao()
{
    int op;

    cout << "Para exibir saida em tela digite 0 e para salvar em um arquivo de texto digite 1"<<endl;
    cin >> op;

    while(op != 0 && op != 1){
        cout << "Erro de digitacao, tente de novo"<<endl;
        cout << "Para exibir saida em tela digite 0 e para salvar em um arquivo de texto digite 1"<<endl;
        cin >> op;
    }

    srand(time(NULL));

    if (op == 0){
        cout<<"Por padrao o numeros de registros sorteados e exibidos e de 10, gostaria de alterar a quantidade de registros exibidos? Se sim digite 0, Nao digite 1."<<endl;
        int op1;
        cin>>op1;
        if(op1==1){
            int n = 10;
            int aux = 0;
            for(int i=0; i<n; i++){
                aux = rand()% num_registro;
                acessaRegistro(aux);
            }
        }
        else if(op1==0){
            cout<<"Quantos registros gostaria de visualizar no console?"<<endl;
            int n;
            cin>>n;
            int aux = 0;
            for(int i=0; i<n; i++){
                aux = rand()% num_registro;
                acessaRegistro(aux);
            }
        }
        else{
            cout<<"Erro, opcao invalida"<<endl;
        }

    }
    else if(op == 1){
        cout<<"Por padrao o numeros de registros sorteados e salvos em Dados.txt e de 100, gostaria de alterar a quantidade de registros exibidos? Se sim digite 0, Nao digite 1."<<endl;
        int op1;
        cin>>op1;
        if(op1==1){
            int n = 100;
            int vet[n];
                for(int i=0; i<n; i++){
                    vet[i]=rand()% num_registro;
                }
             geraArquivo(n, vet);
        }
        else if(op1==0){
            cout<<"Quantos registros gostaria de salvar em Dados.txt?"<<endl;
            int n;
            cin>>n;
            int vet[n];
                for(int i=0; i<n; i++){
                    vet[i]=rand()% num_registro;
                }
             geraArquivo(n, vet);
        }
        else{
            cout<<"Erro, opcao invalida"<<endl;
        }
    }
    else{
        cout<<"Erro, opcao invalida"<<endl;
    }
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
