#include <iostream>
#include <fstream>
#include <cstring>
#include "TabelaHash.h"

using namespace std;

TabelaHash::TabelaHash(int n)
{
  if (n < 10)
  {
    tam_max = 11;
    primo = 7;
  }
  else if (n > 157)
  {
    tam_max = 157;
    primo = 151;
  }
  else
  {
    tam_max = primoMaior(n);
    primo = primoMenor(n);
  }

  tabela = new item[tam_max];
  qtd = 0;
  for (int i = 0; i < tam_max; i++)
  {
    tabela[i].chave[0] = '\0';
    tabela[i].valor = 0;
  }
}

TabelaHash::TabelaHash()
{
  tam_max = 101;
  primo = 97;
  tabela = new item[tam_max];
  qtd = 0;
  for (int i = 0; i < tam_max; i++)
  {
    tabela[i].chave[0] = '\0';
    tabela[i].valor = 0;
  }
}

TabelaHash::~TabelaHash() {}

bool TabelaHash::checaPrimo(int n)
{
  if (n == 1)
  {
    return false;
  }
  for (int i = 2; i * i <= n; i++)
  {
    if (n % i == 0)
    {
      return false;
    }
  }
  return true;
}

int TabelaHash::primoMaior(int n)
{
  for (int i = n + 1; i < 2 * n; i++)
  {
    if (checaPrimo(i))
    {
      return i;
    }
  }
  return (primoMaior(n + 1));
}

int TabelaHash::primoMenor(int n)
{
  for (int i = n - 1; i > 0; i--)
  {
    if (checaPrimo(i))
    {
      return i;
    }
  }
  return (primoMenor(n - 1));
}

int TabelaHash::qpart(item *conj, int esq, int dir)
{
  int i = (esq - 1);
  for (int j = esq; j < dir; j++)
  {
    if (conj[j].valor > conj[dir].valor)
    {
      i++;
      item temp = conj[i];
      conj[i] = conj[j];
      conj[j] = temp;
    }
  }
  item temp = conj[i + 1];
  conj[i + 1] = conj[dir];
  conj[dir] = temp;
  return (i + 1);
}

void TabelaHash::qsort(item *conj, int esq, int dir)
{
  if (esq < dir)
  {
    int part = qpart(conj, esq, dir);
    qsort(conj, esq, part - 1);
    qsort(conj, part + 1, dir);
  }
}

int TabelaHash::hash1(unsigned long key)
{
  return (key % tam_max);
}

int TabelaHash::hash2(unsigned long key)
{
  return (primo - (key % primo));
}

void TabelaHash::rehash()
{
  cout << "<Iniciando rehashing...>" << endl;
  TabelaHash aux_tabelaHash(tam_max * 2); // nova tabela 2x maior
  for (int i = 0; i < tam_max; i++)
  {
    if (tabela[i].valor != 0) // se existe chave
    {
      for (int j = tabela[i].valor; j > 0; j--)
      {
        aux_tabelaHash.insereChave(tabela[i].chave); // insere chave na nova tabela j vezes
      }
    }
  }
  delete[] tabela;
  tabela = aux_tabelaHash.tabela;
  tam_max = aux_tabelaHash.tam_max;
  primo = aux_tabelaHash.primo;
  qtd = aux_tabelaHash.qtd;
  cout << "<Rehasing efetuado.>" << endl;
}

unsigned long TabelaHash::hash_djb2(char *cstr)
{
  unsigned long hash = 5381;
  int c;
  while (c = *cstr++)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash;
}

void TabelaHash::insereChave(char *str)
{
  if (qtd > 0.75 * tam_max)
  {
    rehash();
  }

  int key = hash_djb2(str);
  int iHash1 = hash1(key);

  if (tabela[iHash1].valor != 0) // se colisao ocorre
  {
    if (strcmp(tabela[iHash1].chave, str) == 0) // se string coincidir
    {
      tabela[iHash1].valor++; // incrementa valor
    }
    else // string nao coincide
    {
      int iHash2 = hash2(key); // obtem indice do hash 2
      int i = 1;
      while (1)
      {
        int novo_iHash = (iHash1 + i * iHash2) % tam_max;
        if (tabela[novo_iHash].valor != 0)
        {
          if (strcmp(tabela[novo_iHash].chave, str) == 0) // se string coincidir
          {
            tabela[novo_iHash].valor++; // incrementa valor
            break;                      // e quebra o loop
          }
        }
        else // se nao colidir
        {
          strcpy(tabela[novo_iHash].chave, str); // registra chave
          tabela[novo_iHash].valor++;            // incrementa valor
          qtd++;
          break; // e quebra o loop
        }
        i++; // se colidir e nao coincidir string, itera i e tenta novamente
      }
    }
  }
  else // se nenhuma colisao ocorre
  {
    strcpy(tabela[iHash1].chave, str); // registra chave
    tabela[iHash1].valor++;            // incrementa valor
    qtd++;
  }
}

void TabelaHash::buscaChave(char *str)
{
  unsigned long key = hash_djb2(str);
  int iHash1 = hash1(key);
  int iHash2 = hash2(key);
  int i = 0;
  while ((strcmp(tabela[(iHash1 + i * iHash2) % tam_max].chave, str) != 0))
  {
    if (tabela[(iHash1 + i * iHash2) % tam_max].chave[0] == '\0')
    {
      cout << str << " nao existe!" << endl;
      return;
    }
    i++;
  }
  cout << str << " encontrado!" << endl;
}

void TabelaHash::mostraTabela(int n)
{
  for (int i = 0; i < n; i++)
  {
    if (tabela[i].chave[0] != '\0')
      cout << i << " ----> " << tabela[i].chave << " : " << tabela[i].valor << endl;
  }
}

string TabelaHash::strTabela(int n){
  string str="";
  for(int i = 0;i<n;i++){
    if (tabela[i].chave[0] != '\0')
      str += i, " ----> ", tabela[i].chave, " : " + tabela[i].valor,'\n';
  }
  return str;
}

TabelaHash::item *TabelaHash::getTabela()
{
  return this->tabela;
}

int TabelaHash::getTamMax()
{
  return this->tam_max;
}