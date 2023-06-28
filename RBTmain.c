#include "RBTmain.h"


struct noMain { // BRT
    char* chave;
    Doc** valor;
    int nDocs;
    bool cor;
    RBTmain *esq, *dir;
};

int comparaPageRank(const void* a, const void* b) {
    Doc* docA = *(Doc**) a;
    Doc* docB = *(Doc**) b;
    if (getLastPageRankDocumento(docA)> getLastPageRankDocumento(docB)) return -1;
    if (getLastPageRankDocumento(docA)< getLastPageRankDocumento(docB)) return 1;
    return 0;
}


RBTmain* criaNoRBTmain(char* chave, Doc* valor) {
    RBTmain* no = (RBTmain*) malloc(sizeof(RBTmain));
    Doc** docs = (Doc**) malloc(sizeof(Doc*));
    docs[0] = valor;
    no->chave = strdup(chave);
    no->valor = docs;
    no->cor = RED;
    no->esq = no->dir = NULL;
    no->nDocs = 1;
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
    char* chave_lower = strdup(chave);  // Cria uma cópia da chave

    for (int i = 0; chave_lower[i] != '\0'; i++) {
        chave_lower[i] = tolower(chave_lower[i]);  // Converte para minúsculo
    }
    while (n != NULL) {
        int cmp = strcmp(chave_lower, n->chave);
        if      (cmp < 0)   n = n->esq;
        else if (cmp > 0)   n = n->dir;
        else {
            free(chave_lower);
            return n->valor;
        }
    }
    free(chave_lower);
    return NULL;
}

RBTmain* insereRBTmain(RBTmain* no, char* chave, Doc* valor) {
    if (no == NULL){
        return criaNoRBTmain(chave, valor);
    }

    int cmp = strcmp(chave, no->chave);
    if      (cmp < 0)   no->esq = insereRBTmain(no->esq, chave, valor);
    else if (cmp > 0)   no->dir = insereRBTmain(no->dir, chave, valor);
    else{
        no->nDocs++;
        Doc** docs = (Doc**) realloc(no->valor, sizeof(Doc*) * no->nDocs);
        docs[no->nDocs - 1] = valor;
        no->valor = docs;

    }

    if (ehVermelhoRBTmain(no->dir) && !ehVermelhoRBTmain(no->esq))     no = rotacionaEsqRBTmain(no);
    if (ehVermelhoRBTmain(no->esq) && ehVermelhoRBTmain(no->esq->esq)) no = rotacionaDirRBTmain(no);
    if (ehVermelhoRBTmain(no->esq) && ehVermelhoRBTmain(no->dir))      trocaCorRBTmain(no);

    return no;
}

void criaRBTpesquisa(RBTdocs* documentos, RBTpal* stopWords, char* dirEntrada, RBTmain** T){
    if (documentos == NULL) return;

    if(getEsq(documentos) != NULL) criaRBTpesquisa(getEsq(documentos), stopWords, dirEntrada, T);
    
    Doc* doc = getValor(documentos);
    char diretorio[100];
    sprintf(diretorio, "%s/pages/%s", dirEntrada, getNomeDocumento(doc));

    FILE* arq = fopen(diretorio, "r");
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", diretorio);
        exit(1);
    }

    char* palavra = NULL;
    while (fscanf(arq, "%ms", &palavra) != EOF) {
        //transforma em minusculo
        for (int i = 0; palavra[i] != '\0'; i++) {
            palavra[i] = tolower(palavra[i]);
        }
        if (buscaRBTPal(stopWords, palavra) == NULL) {
            *T = insereRBTmain(*T, palavra, doc);
        }
        else{
        }
        free(palavra);
    }


    if(getDir(documentos) != NULL) criaRBTpesquisa(getDir(documentos), stopWords, dirEntrada, T);
    fclose(arq);
}

void ordenaValuesPorPageRank(RBTmain** T){
    if (*T == NULL) return;

    if((*T)->esq != NULL) ordenaValuesPorPageRank(&(*T)->esq);

    Doc** docs = (*T)->valor;
    int nDocs = (*T)->nDocs;
    qsort(docs, nDocs, sizeof(Doc*), comparaPageRank);

    if((*T)->dir != NULL) ordenaValuesPorPageRank(&(*T)->dir);
}

bool ehVermelhoRBTmain(RBTmain* no) {
    if (no == NULL) return BLACK;
    return no->cor == RED;
}

void printRBTmain(RBTmain* no) {
    if (no == NULL) return;

    printRBTmain(no->esq);
    printf("%s %d\n", no->chave, no->nDocs);
    for (int i = 0; i < no->nDocs; i++) {
        printf("\t%s\t %Lf \n", getNomeDocumento(no->valor[i]), getLastPageRankDocumento(no->valor[i]));
    }
    printRBTmain(no->dir);
}

void liberaNoRBTmain(RBTmain* no) {
    if (no == NULL) return;

    free(no->chave);
    free(no->valor);
    if (no->esq != NULL) liberaNoRBTmain(no->esq);
    if (no->dir != NULL) liberaNoRBTmain(no->dir);
    free(no);
}