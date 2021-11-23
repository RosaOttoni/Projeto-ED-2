#include "Review.h"
#include "FileIO.h"

using namespace std;

void imprimeMenu(){
    cout<<endl<<" ____________________________MENU____________________________"<<endl;
    cout<<"| Para acessar um registro especifico do arquivo, digite [1] |"<<endl;
    cout<<"| Para teste de importacao digite [2]                        |"<<endl;
    cout<<"| Para finalizar digite [0]                                  |"<<endl;
    cout<<"|____________________________________________________________|"<<endl<<endl;
}

int main(int argc, char const *argv[])
{
    int opM;

    if(argc != 2){
        cout << "Erro: Diretorio nao especificado" << endl;
        return 0;
    }

    leituraCsv(argv[1]);

    imprimeMenu();

    cin >> opM;

    while(opM!=0){
        if(opM==1){
            cout<<"Digite o numero do registro que voce gostaria de acessar.";
            int reg;
            cin>>reg;
            cout<<endl;
            acessaRegistro(reg);
        }
        else if(opM==2){
            testeImportacao();
        }
        else{
            cout<<"Erro de digitação, siga as instrucoes do menu e tente de novo."<<endl<<endl;
        }
        imprimeMenu();
        cin >> opM;
    }
    return 0;
}
