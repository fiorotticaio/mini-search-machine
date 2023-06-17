#include "RBTdocs.h"

struct noDocs { // BRT
    char* chave;
    Doc** valores;
    bool cor;
    RBTdocs *esq, *dir;
};

RBTdocs* criaNo(char* chave, Doc** valores) {
    RBTdocs* no = (RBTdocs*) malloc(sizeof(RBTdocs));
    no->chave = strdup(chave);
    no->valores = valores;
    no->cor = RED;
    no->esq = no->dir = NULL;
    return no;
}

RBTdocs* rotacionaEsq(RBTdocs* no) {
    RBTdocs* x = no->dir;
    no->dir = x->esq;
    x->esq = no;
    x->cor = x->esq->cor;
    x->esq->cor = RED;
    return x;
}

RBTdocs* rotacionaDir(RBTdocs *no) {
    RBTdocs* x = no->esq;
    no->esq = x->dir;
    x->dir = no;
    x->cor = x->dir->cor;
    x->dir->cor = RED;
    return x;
}

void trocaCor(RBTdocs* no) {
    no->cor = RED;
    no->esq->cor = BLACK;
    no->dir->cor = BLACK;
}

RBTdocs* insere_RBTdocs(RBTdocs* no, char* chave, Doc** valores) {
    if (no == NULL) return criaNo(chave, valores);

    int cmp = strcmp(chave, no->chave);
    if (cmp < 0)        no->esq = insere_RBTdocs(no->esq, chave, valores);
    else if (cmp > 0)   no->dir = insere_RBTdocs(no->dir, chave, valores);
    else /* cmp == 0 */ no->valores = valores;

    if (ehVermelho(no->dir) && !ehVermelho(no->esq))     no = rotacionaEsq(no);
    if (ehVermelho(no->esq) && ehVermelho(no->esq->esq)) no = rotacionaDir(no);
    if (ehVermelho(no->esq) && ehVermelho(no->dir))      trocaCor(no);

    return no;
}

bool ehVermelho(RBTdocs* no) {
    if (no == NULL) return BLACK;
    return no->cor == RED;
}

void liberaNo(RBTdocs* no) {
    free(no->chave);
    free(no->valores);
    free(no);
}