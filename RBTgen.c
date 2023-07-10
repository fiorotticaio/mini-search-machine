#include "RBTgen.h"


// Red-Black Tree de possíveis buscas //
struct noGen { 
    void   *info;
    bool    cor;
    RBTgen *esq, *dir;
};


RBTgen* criaNoRBTgen(void *info) {
    RBTgen* no = (RBTgen*) malloc(sizeof(RBTgen));
    no->info   = info;
    no->cor    = RED;
    no->esq    = no->dir = NULL;
    return no;
}

RBTgen* rotacionaEsqRBTgen(RBTgen* no) {
    RBTgen* x   = no->dir;
    no->dir     = x->esq;
    x->esq      = no;
    x->cor      = x->esq->cor;
    x->esq->cor = RED;
    return        x;
}

RBTgen* rotacionaDirRBTgen(RBTgen *no) {
    RBTgen* x   = no->esq;
    no->esq     = x->dir;
    x->dir      = no;
    x->cor      = x->dir->cor;
    x->dir->cor = RED;
    return x;
}

void trocaCorRBTgen(RBTgen* no) {
    no->cor = RED;
    no->esq->cor = BLACK;
    no->dir->cor = BLACK;
}

RBTgen* buscaRBTgen(RBTgen* n, void* chave, int (*cb) (void*, void*)) {
    
    while (n != NULL) {
        int cmp = cb(chave, n->info);
        
        if      (cmp < 0) n = n->esq;
        else if (cmp > 0) n = n->dir;
        else            {   return n;}              // Encontrou
    }
    return NULL;
}

RBTgen* insereRBTgen(RBTgen* no, void* data, int (*cb) (void*, void*)){
    // Caso nó seja NULO, não há chave, então crie //
    if (no == NULL) return criaNoRBTgen(data);

    int cmp = cb(data , no->info);
    // Caso chave seja menor, vá p esquerda, caso for maior, vá p direita, senão substitui //
    if      (cmp < 0) no->esq = insereRBTgen(no->esq, data, cb);
    else if (cmp > 0) no->dir = insereRBTgen(no->dir, data, cb);
    else {
        // Verificando se o documento já não está associado à essa chave //
        if(cb(no, data))    return 0;
        
        // Caso não esteja, insira-o na árvore //
        no->info = data;
    }

    // Linhas que demoraram 30 anos para serem feitas pelo Sedwick (conserta RBT ao inserir) //
    if (ehVermelhoRBTgen(no->dir) && !ehVermelhoRBTgen(no->esq))     no = rotacionaEsqRBTgen(no);
    if (ehVermelhoRBTgen(no->esq) && ehVermelhoRBTgen(no->esq->esq)) no = rotacionaDirRBTgen(no);
    if (ehVermelhoRBTgen(no->esq) && ehVermelhoRBTgen(no->dir))           trocaCorRBTgen(no);
    return no;
}


bool ehVermelhoRBTgen(RBTgen* no) {
    if (no == NULL) return BLACK;
    return no->cor == RED;
}



void percorreRBTgen(RBTgen* no, void (*cb) (void*)) {
    if (no == NULL) return;
    percorreRBTgen(no->esq, cb);
    cb(no->info);
    percorreRBTgen(no->dir, cb);
}

void liberaNoRBTgen(RBTgen* no, void (*cb) (void*)) {
    if (no == NULL) return;
    cb(no->info);
    if (no->esq != NULL) liberaNoRBTgen(no->esq, cb);
    if (no->dir != NULL) liberaNoRBTgen(no->dir, cb);
    free(no);
}
