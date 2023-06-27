#include "RBTdocs.h"

#include <stdio.h>

struct noDocs { // BRT
    char* chave;
    Doc* valor;
    bool cor;
    RBTdocs *esq, *dir;
};

RBTdocs* criaNoRBTdocs(char* chave, Doc* valor) {
    RBTdocs* no = (RBTdocs*) malloc(sizeof(RBTdocs));
    no->chave = strdup(chave);
    no->valor = valor;
    no->cor = RED;
    no->esq = no->dir = NULL;
    return no;
}

RBTdocs* rotacionaEsqRBTdocs(RBTdocs* no) {
    RBTdocs* x = no->dir;
    no->dir = x->esq;
    x->esq = no;
    x->cor = x->esq->cor;
    x->esq->cor = RED;
    return x;
}

RBTdocs* rotacionaDirRBTdocs(RBTdocs *no) {
    RBTdocs* x = no->esq;
    no->esq = x->dir;
    x->dir = no;
    x->cor = x->dir->cor;
    x->dir->cor = RED;
    return x;
}

void trocaCorRBTdocs(RBTdocs* no) {
    no->cor = RED;
    no->esq->cor = BLACK;
    no->dir->cor = BLACK;
}

Doc* buscaRBTdocs(RBTdocs* n, char* chave) {
    while (n != NULL) {
        int cmp = strcmp(chave, n->chave);
        if      (cmp < 0)   n = n->esq;
        else if (cmp > 0)   n = n->dir;
        else /* cmp == 0 */ return n->valor;
    }
    return NULL;
}

RBTdocs* insereRBTdocs(RBTdocs* no, char* chave, Doc* valor) {
    if (no == NULL) return criaNoRBTdocs(chave, valor);

    int cmp = strcmp(chave, no->chave);
    if      (cmp < 0)   no->esq = insereRBTdocs(no->esq, chave, valor);
    else if (cmp > 0)   no->dir = insereRBTdocs(no->dir, chave, valor);
    else /* cmp == 0 */ no->valor = valor;

    if (ehVermelhoRBTdocs(no->dir) && !ehVermelhoRBTdocs(no->esq))     no = rotacionaEsqRBTdocs(no);
    if (ehVermelhoRBTdocs(no->esq) && ehVermelhoRBTdocs(no->esq->esq)) no = rotacionaDirRBTdocs(no);
    if (ehVermelhoRBTdocs(no->esq) && ehVermelhoRBTdocs(no->dir))      trocaCorRBTdocs(no);

    return no;
}

bool ehVermelhoRBTdocs(RBTdocs* no) {
    if (no == NULL) return BLACK;
    return no->cor == RED;
}

void printRBTdocs(RBTdocs* no, int ultimaPosPageRank) {
    if (no == NULL) return;

    printRBTdocs(no->esq, ultimaPosPageRank);
    imprimeDocumento(no->valor, ultimaPosPageRank);
    printf("\n\n");
    printRBTdocs(no->dir, ultimaPosPageRank);
}

void liberaNoRBTdocs(RBTdocs* no) {
    free(no->chave);
    liberaDocumento(no->valor);
    if (no->esq != NULL) liberaNoRBTdocs(no->esq);
    if (no->dir != NULL) liberaNoRBTdocs(no->dir);
    free(no);
}

RBTdocs* getEsq(RBTdocs* no){
    return no->esq;
}

RBTdocs* getDir(RBTdocs* no){
    return no->dir;
}

Doc* getValor(RBTdocs* no){
    return no->valor;
}

char* getChave(RBTdocs* no){
    return no->chave;
}

static long double getDifPageRank(RBTdocs* no, int k) { // Função resursiva
    if (no == NULL) return 0;

    long double somatorio = 0.0;
    somatorio += getDifPageRank(no->esq, k);

    /* Nó atual */
    long double dif = (getPageRankDocumento(no->valor, k) - getPageRankDocumento(no->valor, k-1));
    if (dif < 0) dif *= -1; // Pegar o módulo
    somatorio += dif;

    somatorio += getDifPageRank(no->dir, k);
    return somatorio;
}

static int terminouCalculoPageRank(RBTdocs* no, int numDocs, int k) {
    long double E = 0.0, somatorio = 0.0;
    somatorio = getDifPageRank(no, k);
    E = (long double) somatorio / numDocs;
    return E < DIF_LIMITE_PR;
}

static void calcPG(RBTdocs* no, int numDocs, int k) { // Função resursiva
    if (no == NULL) return;
    calcPG(no->esq, numDocs, k);
    calculaPageRankDocumento(no->valor, numDocs, k); // Nó atual
    calcPG(no->dir, numDocs, k);
}

int calculaPageRankRBTdocs(RBTdocs* no, int numDocs) {
    if (no == NULL) return -1;
    int k = 1; // A iteração 0 já foi feita na criação do documento
    do {
        calcPG(no, numDocs, k); // Calcula o page rank de todos os docs para a iteração k
    } while (!terminouCalculoPageRank(no, numDocs, k++));
    return k-1; // Retorna a última posição válida do page rank 
}