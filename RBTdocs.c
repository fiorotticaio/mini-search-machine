#include "RBTdocs.h"

#include <stdio.h>

// Red-Black Tree de Documentos/Páginas
struct noDocs { 
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

void printRBTdocs(RBTdocs* no) {
    if (no == NULL) return;

    printRBTdocs(no->esq);
    imprimeDocumento(no->valor);
    printf("\n\n");
    printRBTdocs(no->dir);
}

void liberaNoRBTdocs(RBTdocs* no) {
    if (no==NULL) return;
    if (no->chave != NULL) free(no->chave);
    if (no->valor != NULL) liberaDocumento(no->valor);
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

static long double getDifPageRank(RBTdocs* no) { // Função recursiva
    if (no == NULL) return 0;

    long double somatorio = 0.0;
    somatorio += getDifPageRank(no->esq);

    /* Nó atual */
    long double dif = (getPageRankAtualDocumento(no->valor) - getPageRankAnteriorDocumento(no->valor));
    if (dif < 0) dif *= -1; // Pegar o módulo
    somatorio += dif;
    setPageRankAnteriorDocumento(no->valor, getPageRankAtualDocumento(no->valor)); // Atualiza o page rank anterior

    somatorio += getDifPageRank(no->dir);
    return somatorio;
}

static int terminouCalculoPageRank(RBTdocs* no, int numDocs) {
    long double E = 0.0, somatorio = 0.0;
    somatorio = getDifPageRank(no);
    E = (long double) somatorio / numDocs;
    return E < DIF_LIMITE_PR;
}

static void calcPG(RBTdocs* no, int numDocs) { // Função recursiva
    if (no == NULL) return;
    calcPG(no->esq, numDocs);
    calculaPageRankDocumento(no->valor, numDocs); // Nó atual
    calcPG(no->dir, numDocs);
}

void calculaPageRankRBTdocs(RBTdocs* no, int numDocs) {
    if (no == NULL) return;
    int k = 0;
    do {
        calcPG(no, numDocs); // Calcula o page rank de todos os docs para cada iteração
        k++;
    } while (!terminouCalculoPageRank(no, numDocs));
    // printf("Número de iterações: %d\n", k);
}