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

RBTpal* insereRBTpal(RBTpal* no, int chave, char* valor) {
    if (no == NULL) return criaNoRBTpal(chave, valor);

    int cmp = strcmp(valor, no->valor);
    if (cmp < 0)        no->esq = insereRBTpal(no->esq, chave, valor);
    else if (cmp > 0)   no->dir = insereRBTpal(no->dir, chave, valor);
    else /* cmp == 0 */ no->valor = valor;

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
    free(no->valor);
    free(no);
}