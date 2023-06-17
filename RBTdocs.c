#include "RBTdocs.h"

struct noDocs { // BRT
    char* chave;
    Doc** valor;
    bool cor;
    RBTdocs *esq, *dir;
};

RBTdocs* criaNoRBTdocs(char* chave, Doc** valor) {
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

Doc** buscaRBTdocs(RBTdocs* n, char* chave) {
    while (n != NULL) {
        int cmp = strcmp(chave, n->chave);
        if      (cmp < 0)   n = n->esq;
        else if (cmp > 0)   n = n->dir;
        else /* cmp == 0 */ return n->valor;
    }
    return NULL;
}

RBTdocs* insereRBTdocs(RBTdocs* no, char* chave, Doc** valor) {
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

void liberaNoRBTdocs(RBTdocs* no) {
    if (no == NULL) return;

    free(no->chave);
    free(no->valor);
    if (no->esq != NULL) liberaNoRBTdocs(no->esq);
    if (no->dir != NULL) liberaNoRBTdocs(no->dir);
    free(no);
}