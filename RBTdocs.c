#include "RBTdocs.h"

struct noDocs { // BRT
    char* chave;
    Doc** valores;
    bool cor;
    RBTdocs *esq, *dir;
};

RBTdocs* criaNoRBTdocs(char* chave, Doc** valores) {
    RBTdocs* no = (RBTdocs*) malloc(sizeof(RBTdocs));
    no->chave = strdup(chave);
    no->valores = valores;
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

RBTdocs* insereRBTdocs(RBTdocs* no, char* chave, Doc** valores) {
    if (no == NULL) return criaNoRBTdocs(chave, valores);

    int cmp = strcmp(chave, no->chave);
    if (cmp < 0)        no->esq = insereRBTdocs(no->esq, chave, valores);
    else if (cmp > 0)   no->dir = insereRBTdocs(no->dir, chave, valores);
    else /* cmp == 0 */ no->valores = valores;

    if (ehVermelhoRBTdocs(no->dir) && !ehVermelhoRBTdocs(no->esq))     no = rotacionaEsqRBTdocs(no);
    if (ehVermelhoRBTdocs(no->esq) && ehVermelhoRBTdocs(no->esq->esq)) no = rotacionaDirRBTdocs(no);
    if (ehVermelhoRBTdocs(no->esq) && ehVermelhoRBTdocs(no->dir))      trocaCorRBTdocs(no);

    return no;
}

bool ehVermelhoRBTdocs(RBTdocs* no) {
    if (no == NULL) return BLACK;
    return no->cor == RED;
}

void liberaNoRBTdocs(RBTdocs* no) {
    free(no->chave);
    free(no->valores);
    free(no);
}