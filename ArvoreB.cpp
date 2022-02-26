#include "ArvoreB.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <math.h>
#include <ctime>
#include <algorithm>
#include <utility>

using namespace std;


ArvoreB::ArvoreB(int m)
{
    raiz = NULL;
    this->m = m;
    int maxchav = m-1;
    int kfmin, kfmax, kchmin, kchmax;
    kfmin = m/2;
    kfmax = m;
    kchmin = kfmin-1;
    kchmax = kfmax-1;

    cout<< "Quantas chavez deseja cadastrar?";
    int nchav;
    cin>>nchav;

    for (int i = 0; i < nchav; i++)
    {
        chave *aux = new chave();
        int auxid;
        cout<<"digite id da chave"<<endl;
        cin>>auxid;
        aux->id = auxid;
        insercao(aux);
    }
    cout << "\nINSERCAO CONCLUIDA COM SUCESSO" << endl;
}

void ArvoreB::insercao(chave *p)
{
    if (raiz == NULL)
    {
        raiz = new NodeB();
        raiz->pai = NULL;
        raiz->folha = true;
        raiz->n = 1;
        raiz->folhas.resize(m, NULL);
        raiz->chaves.push_back(p);
        raiz->chaves.resize(m-1, NULL);
    }
    else
    {
        auxInsert(raiz, p);
    }
}
int ArvoreB::compara(int chnova, int chexistente)
{
    if(chnova==chexistente)
        return 1;
    else if(chnova>chexistente)
        return 2;
    else
        return 0;
}

void ArvoreB::auxInsert(NodeB *no, chave *k)
{
    //caso base , de ser uma folha
    if (no->folha)
    {
        if( no->n < m-1)
        {
            int prox = 0;
            for (int i = 0; no->chaves[i] != NULL; i++)
            {
                if (compara(k->id, no->chaves[i]->id) <= 1)
                {
                    no->chaves.insert(no->chaves.begin() + i, k);
                    no->chaves.resize(m-1, NULL);
                    no->n++;
                    return;
                }
                prox = i + 1;
            }
            no->chaves[prox] = k;
            no->n++;
        }
        else
        {
            cisao(no, k);
        }
    }
    else //caso de ser um no
    {
         if( no->n < m-1)
        {
            int prox = 0;
            for (int i = 0; i <no->n; i++)
            {
                if (compara(k->id, no->chaves[i]->id) <=1)
                {
                    auxInsert(no->folhas[i], k);
                    return;
                }
                prox = i + 1;
            }
            auxInsert(no->folhas[prox], k);
        }
    }
}

void ArvoreB::cisao(NodeB *no, chave *k)
{
        if(no->pai==NULL)
        {
            NodeB *irmao1 = new NodeB();
            NodeB *irmao2 = new NodeB();

            irmao1->folhas.resize(m, NULL);
            irmao2->folhas.resize(m, NULL);

            irmao1->pai = no;
            irmao2->pai = no;

            int auxk=0;
            for (int i = 0; i<m; i++)
            {
                if(auxk==0 && i==m-1)
                {
                    irmao2->chaves.push_back(k);
                    irmao2->n++;
                    auxk=1;
                    if(no->folha)
                    {
                        irmao2->folhas[irmao2->n-1]=NULL;
                    }
                    else
                    {
                        irmao2->folhas[irmao2->n-1]= no->folhas[i];
                    }
                }
                else
                {
                    if(i<(m/2))
                    {
                        if(auxk==1)
                        {
                            irmao1->chaves.push_back(no->chaves[i-1]);
                            irmao1->n++;
                            if(no->folha)
                            {
                                irmao1->folhas[irmao1->n-1]=NULL;
                            }
                            else
                            {
                                irmao1->folhas[irmao1->n-1]= no->folhas[i];
                            }
                        }
                        else
                        {
                            if(compara(k->id, no->chaves[i]->id) <= 1)
                            {
                                irmao1->chaves.push_back(k);
                                irmao1->n++;
                                auxk=1;
                                if(no->folha)
                                {
                                    irmao1->folhas[irmao1->n-1]=NULL;
                                }
                                else
                                {
                                    irmao1->folhas[irmao1->n-1]= no->folhas[i];
                                }
                            }
                            else
                            {
                                irmao1->chaves.push_back(no->chaves[i]);
                                irmao1->n++;
                                if(no->folha)
                                {
                                    irmao1->folhas[irmao1->n-1]=NULL;
                                }
                                else
                                {
                                    irmao1->folhas[irmao1->n-1]= no->folhas[i];
                                }
                            }
                        }
                    }
                    else if (i==m/2)
                    {
                        if(auxk==1)
                        {
                            no->chaves[0]=no->chaves[i-1];
                        }
                        else
                        {
                            if(compara(k->id, no->chaves[i]->id) <= 1)
                            {
                                no->chaves[0]=k;
                                auxk=1;
                            }
                            else
                                no->chaves[0]=no->chaves[i];
                        }
                    }
                    else
                    {
                        if(auxk==1)
                        {
                            irmao2->chaves.push_back(no->chaves[i-1]);
                            irmao2->n++;
                            if(no->folha)
                                {
                                irmao2->folhas[irmao2->n-1]= NULL;
                                }
                                else
                                {
                                irmao2->folhas[irmao2->n-1]= no->folhas[i];
                                }
                        }
                        else
                        {
                            if(compara(k->id, no->chaves[i]->id) <= 1)
                            {
                                irmao2->chaves.push_back(k);
                                irmao2->n++;
                                auxk=1;
                                if(no->folha)
                                {
                                irmao2->folhas[irmao2->n-1]=NULL;
                                }
                                else
                                {
                                irmao2->folhas[irmao2->n-1]= no->folhas[i];
                                }
                            }
                            else
                            {
                                irmao2->chaves.push_back(no->chaves[i]);
                                irmao2->n++;
                                if(no->folha)
                                {
                                irmao2->folhas[irmao2->n-1]= NULL;
                                }
                                else
                                {
                                irmao2->folhas[irmao2->n-1]= no->folhas[i];
                                }
                            }
                        }
                    }
                }
            }
            irmao1->chaves.resize(m-1, NULL);
            irmao2->chaves.resize(m-1, NULL);

            for(int i=1;i<m-1;i++)
            {
                no->chaves[i]==NULL;
            }

            if (no->folha)
            {
                irmao1->folha = true;
                irmao2->folha = true;
            }
            else
            {
                irmao1->folha = false;
                irmao2->folha = false;
            }
            no->folha=false;
            no->folhas[0]=irmao1;
            no->folhas[1]=irmao2;
            no->n=1;
            for(int i=no->n+1;i<m;i++)
            {
                no->folhas[i]=NULL;
            }
        }
        else
        {
            NodeB *irmao = new NodeB();
            irmao->pai = no->pai;
            irmao->folhas.resize(m, NULL);

            int auxcont=0;
            int auxk=0;
            for (int i = 0; i<m; i++)
            {
                if(auxk==0 && i==m-1)
                {
                    no->chaves[auxcont]= no->chaves[i-1];
                    auxcont = auxcont+1;
                    if(no->folha)
                    {
                        no->folhas[auxcont-1]=NULL;
                    }
                    else
                    {
                        no->folhas[auxcont-1]= no->folhas[i];
                    }
                }
                else
                {
                    if(i<m/2)
                    {
                        if(auxk==1)
                        {
                            irmao->chaves.push_back(no->chaves[i-1]);
                            irmao->n++;
                            if(no->folha)
                                {
                                    irmao->folhas[irmao->n-1]=NULL;
                                }
                                else
                                {
                                    irmao->folhas[irmao->n-1]= no->folhas[i];
                                }
                        }
                        else
                        {
                            if(compara(k->id, no->chaves[i]->id) <= 1)
                            {
                                irmao->chaves.push_back(k);
                                irmao->n++;
                                auxk=1;
                                if(no->folha)
                                {
                                    irmao->folhas[irmao->n-1]=NULL;
                                }
                                else
                                {
                                    irmao->folhas[irmao->n-1]= no->folhas[i];
                                }
                            }

                            else
                            {
                                irmao->chaves.push_back(no->chaves[i]);
                                irmao->n++;
                                if(no->folha)
                                {
                                    irmao->folhas[irmao->n-1]=NULL;
                                }
                                else
                                {
                                    irmao->folhas[irmao->n-1]= no->folhas[i];
                                }
                            }
                        }
                    }
                    else if (i==m/2)
                    {
                        if(auxk==1)
                        {
                            if(no->pai->n == m-1)
                            {
                                cisao(no->pai,no->chaves[i-1]);
                            }
                            else
                            {
                                no->pai->chaves[no->pai->n+1] = no->chaves[i-1];
                                no->pai->n = no->pai->n+1;
                            }
                        }
                        else
                        {
                            if(no->pai->n == m-1)
                            {
                                if(compara(k->id, no->chaves[i]->id) <= 1)
                                {
                                    cisao(no->pai, k);
                                    auxk=1;
                                }
                                else
                                {
                                    cisao(no->pai,no->chaves[i]);
                                }
                            }
                            else
                            {
                                if(compara(k->id, no->chaves[i]->id) <= 1)
                                {
                                    no->pai->chaves[no->pai->n+1] = k;
                                    no->pai->n = no->pai->n+1;
                                    auxk=1;
                                }
                                else
                                {
                                    no->pai->chaves[no->pai->n+1] = no->chaves[i];
                                    no->pai->n = no->pai->n+1;
                                }
                            }
                        }
                    }
                    else
                    {
                        if(auxk==1)
                        {
                            no->chaves[auxcont]= no->chaves[i-1];
                            auxcont = auxcont+1;
                            if(no->folha)
                            {
                                no->folhas[auxcont-1]=NULL;
                            }
                            else
                            {
                                no->folhas[auxcont-1]= no->folhas[i];
                            }
                        }
                        else
                        {
                            if(compara(k->id, no->chaves[i]->id) <= 1)
                            {
                                no->chaves[auxcont]=k;
                                auxcont = auxcont+1;
                                auxk=1;
                                if(no->folha)
                                {
                                    no->folhas[auxcont-1]=NULL;
                                }
                                else
                                {
                                    no->folhas[auxcont-1]= no->folhas[i];
                                }
                            }
                            else
                            {
                                no->chaves[auxcont]= no->chaves[i];
                                auxcont = auxcont+1;
                                if(no->folha)
                                {
                                    no->folhas[auxcont-1]=NULL;
                                }
                                else
                                {
                                    no->folhas[auxcont-1]= no->folhas[i];
                                }
                            }
                        }
                    }
                }
            }

            no->n = auxcont;

            for(int i=auxcont;i<m-1;i++)
            {
                no->chaves[i]==NULL;
            }

            irmao->chaves.resize(m-1, NULL);

            no->pai = irmao->pai->folhas[irmao->pai->n];

            if(no->folha)
                irmao->folha=true;
            else
                irmao->folha=false;

            for(int i=no->n+1;i<m;i++)
            {
                no->folhas[i]=NULL;
            }

        }
}
NodeB* ArvoreB::getRAiz()
{
    if (raiz!= NULL)
        return raiz;
    else
    {
        cout<< "arvore vazia!"<<endl;

    }
}

void ArvoreB::imprimeArvoreB()
{
    cout<<"Imprimindo ArvoreB"<<endl;
    auxImprimeArvoreB(raiz);
    cout<<endl;
}

void ArvoreB::auxImprimeArvoreB(NodeB *r)
{
    if(r!=NULL)
    {
        for(int i=0;i<r->n;i++)
        {
            cout<<r->chaves[i]->id<<"|";
        }
        cout<<endl;
        for(int i=0;i<r->n+1;i++)
        {
            auxImprimeArvoreB(r->folhas[i]);
        }
    }
}