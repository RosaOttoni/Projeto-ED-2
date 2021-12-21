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
  void rehash();
  int hash1(unsigned long key);
  int hash2(unsigned long key);
  unsigned long hash_djb2(char *cstr);
  int qpart(item *conj, int esq, int dir);

public:
  TabelaHash(int n);
  TabelaHash();
  ~TabelaHash();
  item *getTabela();
  int getTamMax();
  void qsort(item *conj, int esq, int dir);
  void insereChave(char *str);
  void buscaChave(char *str);
  void mostraTabela(int n);
  string strTabela(int n);
};

#endif