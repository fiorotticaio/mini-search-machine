#include "RBTmain.h"

struct noMain { // BRT
    char* chave;
    Doc** valor;
    bool cor;
    RBTmain *esq, *dir;
};

RBTmain* criaNoRBTmain(char* chave, Doc** valor) {
    RBTmain* no = (RBTmain*) malloc(sizeof(RBTmain));
    no->chave = strdup(chave);
    no->valor = valor;
    no->cor = RED;
    no->esq = no->dir = NULL;
    return no;
}

RBTmain* rotacionaEsqRBTmain(RBTmain* no) {
    RBTmain* x = no->dir;
    no->dir = x->esq;
    x->esq = no;
    x->cor = x->esq->cor;
    x->esq->cor = RED;
    return x;
}

RBTmain* rotacionaDirRBTmain(RBTmain *no) {
    RBTmain* x = no->esq;
    no->esq = x->dir;
    x->dir = no;
    x->cor = x->dir->cor;
    x->dir->cor = RED;
    return x;
}

void trocaCorRBTmain(RBTmain* no) {
    no->cor = RED;
    no->esq->cor = BLACK;
    no->dir->cor = BLACK;
}

Doc** buscaRBTmain(RBTmain* n, char* chave) {
    while (n != NULL) {
        int cmp = strcmp(chave, n->chave);
        if      (cmp < 0)   n = n->esq;
        else if (cmp > 0)   n = n->dir;
        else /* cmp == 0 */ return n->valor;
    }
    return NULL;
}

RBTmain* insereRBTmain(RBTmain* no, char* chave, Doc** valor) {
    if (no == NULL) return criaNoRBTmain(chave, valor);

    int cmp = strcmp(chave, no->chave);
    if      (cmp < 0)   no->esq = insereRBTmain(no->esq, chave, valor);
    else if (cmp > 0)   no->dir = insereRBTmain(no->dir, chave, valor);
    else /* cmp == 0 */ no->valor = valor;

    if (ehVermelhoRBTmain(no->dir) && !ehVermelhoRBTmain(no->esq))     no = rotacionaEsqRBTmain(no);
    if (ehVermelhoRBTmain(no->esq) && ehVermelhoRBTmain(no->esq->esq)) no = rotacionaDirRBTmain(no);
    if (ehVermelhoRBTmain(no->esq) && ehVermelhoRBTmain(no->dir))      trocaCorRBTmain(no);

    return no;
}

bool ehVermelhoRBTmain(RBTmain* no) {
    if (no == NULL) return BLACK;
    return no->cor == RED;
}

void liberaNoRBTmain(RBTmain* no) {
    if (no == NULL) return;

    free(no->chave);
    free(no->valor);
    if (no->esq != NULL) liberaNoRBTmain(no->esq);
    if (no->dir != NULL) liberaNoRBTmain(no->dir);
    free(no);
}