#ifndef REVIEWNODE_H_INCLUDED
#define REVIEWNODE_H_INCLUDED

class ReviewNode{
    private:
        char id[90];
        int posicaoArquivo;

    public:
        ReviewNode(char *id, int posicaoArquivo);

        ReviewNode();

        ~ReviewNode();

        char *getId();
        int getPosicaoArquivo();

        void setId(char *id);
        void setPosicaoArquivo(int posicaoArquivo);
};

#endif // REVIEWNODE_H_INCLUDED
