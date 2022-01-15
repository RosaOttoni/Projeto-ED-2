#include <iostream>
#include <fstream>
#include <cstring>
#include "TabelaHash.h"

#define PRIMOS                                                                                                                                                                                                                                           \
  {                                                                                                                                                                                                                                                      \
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257 \
  }

using namespace std;

TabelaHash::TabelaHash(int n) // construtor com param de tamanho
{
  if (n < 10)
  {
    tam_max = 11;
    primo = 7;
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

TabelaHash::TabelaHash() // construtor padrao
{
  tam_max = 11;
  primo = 7;
  tabela = new item[tam_max];
  qtd = 0;
  for (int i = 0; i < tam_max; i++)
  {
    tabela[i].chave[0] = '\0';
    tabela[i].valor = 0;
  }
}

TabelaHash::~TabelaHash() {} // destrutor

bool TabelaHash::checaPrimo(int n)
{
  int primos[] = PRIMOS; // é checado primalidade para valores até o ultimo primo ao quadrado
  {
    for (int i = 0; (i < (sizeof(primos) / sizeof(*primos)) && primos[i] < n); i++)
    {
      if (n % primos[i] == 0)
      {
        return false;
      }
    }
    return true;
  }
}

int TabelaHash::primoMaior(int n) // busca primo maior para definir tam_max
{
  if (checaPrimo(n + 1))
  {
    return (n + 1);
  }
  return (primoMaior(n + 1));
}

int TabelaHash::primoMenor(int n) // busca primo menor para definir primo do hash2
{
  if (checaPrimo(n - 1))
  {
    return (n - 1);
  }
  return (primoMenor(n - 1));
}

unsigned long TabelaHash::hash_string(char *cstr) // hash de string para int positivo
{
  unsigned long hash = 7129; // primo
  int c;
  while (c = *cstr++)                // percorre cstr
    hash = ((hash << 4) + hash) + c; // hash * 17 + c, atraves de shift
  return hash;
}

int TabelaHash::hash1(unsigned long key) // funcao de dispersao 1
{
  return (key % tam_max);
}

int TabelaHash::hash2(unsigned long key) // funcao de dispersao 2
{
  return (primo - (key % primo));
}

void TabelaHash::rehash() // reestrutura para uma tabela maior
{
  // cout << "[Iniciando rehashing...]" << endl;
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
  // cout << "[Rehasing efetuado.]" << endl;
}

void TabelaHash::qsort(item *conj, int esq, int dir) // quicksort
{
  if (esq < dir)
  {
    int part = qpart(conj, esq, dir);
    qsort(conj, esq, part - 1);
    qsort(conj, part + 1, dir);
  }
}

int TabelaHash::qpart(item *conj, int esq, int dir) // particiona do quicksort
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

void TabelaHash::insereChave(char *str) // insere chave na tabela
{
  if (qtd > 0.75 * tam_max) // se fator excede 0.75 aumenta tabela
  {
    rehash();
  }
  int key = hash_string(str);
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

void TabelaHash::mostraTabela(int n) // exibe tabela valida
{
  if (n > tam_max)
  {
    n = tam_max;
  }
  for (int i = 0; i < n; i++)
  {
    if (tabela[i].valor != 0)
      cout << (i + 1) << " ----> " << tabela[i].chave << " : " << tabela[i].valor << endl;
  }
}

string TabelaHash::linhaTabela(int n) // retorna string da linha n da tabela
{
  if (n > tam_max)
  {
    n = tam_max;
  }
  string str = "";
  {
    if (tabela[n].valor != 0)
      str += to_string(n + 1) + " ----> " + string(tabela[n].chave) + " : " + to_string(tabela[n].valor) + '\n';
  }
  return str;
}

// getters
TabelaHash::item *TabelaHash::getTabela()
{
  return this->tabela;
}

int TabelaHash::getTamMax()
{
  return this->tam_max;
}