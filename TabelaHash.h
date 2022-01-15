#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

using namespace std;

class TabelaHash
{
private:
  struct item
  {
    char chave[10];
    int valor;
  };
  item *tabela;
  int tam_max;
  int primo;
  int qtd;
  bool checaPrimo(int n);
  int primoMaior(int n);
  int primoMenor(int n);
  unsigned long hash_string(char *cstr);
  int hash1(unsigned long key);
  int hash2(unsigned long key);
  void rehash();
  int qpart(item *conj, int esq, int dir);

public:
  TabelaHash(int n);
  TabelaHash();
  ~TabelaHash();
  item *getTabela();
  int getTamMax();
  void insereChave(char *str);
  void qsort(item *conj, int esq, int dir);
  void mostraTabela(int n);
  string linhaTabela(int n);
};

#endif