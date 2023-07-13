#include "RBTgen.h"


// Red-Black Tree de possíveis buscas //
struct noGen { 
    void   *chave;
    void   *info;
    bool    cor;
    RBTgen *esq, *dir;
};

void* retornaInfo(RBTgen* no){
    return no->info;
}
void* retornaChave(RBTgen* no){
    return no->chave;
}

RBTgen* retornaEsq(RBTgen* no){
    return no->esq;
}

RBTgen* retornaDir(RBTgen* no){
    return no->dir;
}

void RBTgenSetEsq(RBTgen* no, RBTgen* esq){
    no->esq = esq;
}

void RBTgenSetDir(RBTgen* no, RBTgen* dir){
    no->dir = dir;
}

int funcFalse(RBTgen *a, void *b){
    return 0;
}

int comparaString(void* a, void* b){
    return strcmp((char*)a, (char*)b);
}

RBTgen* criaNoRBTgen(void* chave, void *info) {
    RBTgen* no = (RBTgen*) malloc(sizeof(RBTgen));
    no->chave  = chave;
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
        int cmp = cb(chave, n->chave);
        
        if      (cmp < 0) n = n->esq;
        else if (cmp > 0) n = n->dir;
        else            {   return n;}              // Encontrou
    }
    return NULL;
}

RBTgen* insereRBTgen(RBTgen* no,void* chave, void* dado, int (*cb) (void*, void*), int (*cbDado) (RBTgen*, void*), void* (*cbALocaDado) (RBTgen*, void *)){
    // Caso nó seja NULO, não há chave, então crie //
    if (no == NULL) return criaNoRBTgen(chave, dado);

    int cmp = cb(chave , no->chave);
    // Caso chave seja menor, vá p esquerda, caso for maior, vá p direita, senão substitui //
    if      (cmp < 0) no->esq = insereRBTgen(no->esq, chave, dado, cb, cbDado, cbALocaDado);
    else if (cmp > 0) no->dir = insereRBTgen(no->dir, chave, dado, cb, cbDado, cbALocaDado);
    else {
        // Verificando se o documento já não está associado à essa chave //
        if(cbDado(no, dado)) return no;
        
        // Caso não esteja, insira-o na árvore //
        no->info = cbALocaDado(no, dado);
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

    if (no->esq   != NULL) liberaNoRBTgen(no->esq, cb);
    cb (no->info);
    if (no->chave != NULL) free(no->chave);
    if (no->dir   != NULL) liberaNoRBTgen(no->dir, cb);
    free(no);
}
