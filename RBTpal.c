#include "RBTpal.h"

struct noPal {
    int chave;
    char* valor;
    bool cor;
    RBTpal *esq, *dir;
};

RBTpal* criaNoRBTpal(int chave, char* valor) {
    RBTpal* no = (RBTpal*) malloc(sizeof(RBTpal));
    no->chave = chave;
    no->valor = strdup(valor);
    no->cor = RED;
    no->esq = no->dir = NULL;
    return no;
}

RBTpal* rotacionaEsqRBTpal(RBTpal* no) {
    RBTpal* x = no->dir;
    no->dir = x->esq;
    x->esq = no;
    x->cor = x->esq->cor;
    x->esq->cor = RED;
    return x;
}

RBTpal* rotacionaDirRBTpal(RBTpal *no) {
    RBTpal* x = no->esq;
    no->esq = x->dir;
    x->dir = no;
    x->cor = x->dir->cor;
    x->dir->cor = RED;
    return x;
}

void trocaCorRBTpal(RBTpal* no) {
    no->cor = RED;
    no->esq->cor = BLACK;
    no->dir->cor = BLACK;
}

char* buscaRBTPal(RBTpal* n, char* valor) {
    while (n != NULL) {
        int cmp = strcmp(valor, n->valor);
        if      (cmp < 0)   n = n->esq;
        else if (cmp > 0)   n = n->dir;
        else /* cmp == 0 */ return n->valor;
    }
    return NULL;
}

RBTpal* insereRBTpal(RBTpal* no, int chave, char* valor) {
    if (no == NULL) return criaNoRBTpal(chave, valor);

    int cmp = strcmp(valor, no->valor);
    if      (cmp < 0)   no->esq = insereRBTpal(no->esq, chave, valor);
    else if (cmp > 0)   no->dir = insereRBTpal(no->dir, chave, valor);
    else                printf("Stopword %s ja existe na arvore\n", valor);

    if (ehVermelhoRBTpal(no->dir) && !ehVermelhoRBTpal(no->esq))     no = rotacionaEsqRBTpal(no);
    if (ehVermelhoRBTpal(no->esq) && ehVermelhoRBTpal(no->esq->esq)) no = rotacionaDirRBTpal(no);
    if (ehVermelhoRBTpal(no->esq) && ehVermelhoRBTpal(no->dir))      trocaCorRBTpal(no);

    return no;
}

bool ehVermelhoRBTpal(RBTpal* no) {
    if (no == NULL) return BLACK;
    return no->cor == RED;
}

void liberaNoRBTpal(RBTpal* no) {
    if (no == NULL) return;

    free(no->valor);
    if (no->esq != NULL) liberaNoRBTpal(no->esq);
    if (no->dir != NULL) liberaNoRBTpal(no->dir);
    free(no);
}

RBTpal* leStopWords(char* dirEntrada) {
    /* Criando diretório do arquivo stopwords.txt */
    char stopWordsDir[100];
    sprintf(stopWordsDir, "%s/stopwords.txt", dirEntrada);
    FILE* stopWordsArq = fopen(stopWordsDir, "r");

    if (stopWordsArq == NULL) {
        printf("Erro ao abrir arquivo no diretorio: %s\n", stopWordsDir);
        exit(1);
    }

    int chaveStopWord = 0;
    RBTpal* stopWords = NULL; // Raiz da árvore

    while (!feof(stopWordsArq)) {
        char stopWord[100]; // Variável auxiliar para leitura
        fscanf(stopWordsArq, "%[^\n]\n", stopWord); // Lê a stopWord
        stopWords = insereRBTpal(stopWords, chaveStopWord, stopWord); // Insere a nova stopWord na RBT
        chaveStopWord++;
    }

    fclose(stopWordsArq);
    return stopWords;
}