#include "RBTdocs.h"

#include <stdio.h>

/* Red-Black Tree de Documentos/Páginas */

int comparaString(void* a, void* b){
    return strcmp((char*)a, (char*)b);
}

RBTgen* criaNoRBTdocs(char* chave, Doc* valor) {
    return criaNoRBTgen(strdup(chave), valor);
}

Doc* buscaRBTdocs(RBTgen* n, char* chave) {
    RBTgen* no = buscaRBTgen(n, chave, comparaString);
    if(no != NULL) 
        return retornaInfo(no);
    return NULL;

}

int funcFalse(RBTgen *a, void *b){
    return 0;
}

RBTgen* insereRBTdocs(RBTgen* no, char* chave, Doc* valor) {
    return insereRBTgen(no, chave, valor, comparaString, funcFalse);
}


void printRBTdocs(RBTgen* no) {
    percorreRBTgen(no, imprimeDocumento);
}

void liberaDadosRBTdocs(void *dados){
    if(retornaChave(dados) != NULL) free(retornaChave(dados));
    if(retornaInfo (dados) != NULL) liberaDocumento(retornaInfo (dados));
    return;
}

void liberaNoRBTdocs(RBTgen* no) {
    liberaNoRBTgen(no, liberaDadosRBTdocs);
}


/* Função recursiva */
static long double getDifPageRank(RBTgen* no) {
    if (no == NULL) return 0;

    long double somatorio = 0.0;
    somatorio += getDifPageRank(retornaEsq(no));

    /* Nó atual */
    long double dif = (getPageRankAtualDocumento(retornaInfo(no)) - getPageRankAnteriorDocumento(retornaInfo(no)));
    if (dif < 0) dif *= -1; // Pegar o módulo
    somatorio += dif;
    setPageRankAnteriorDocumento(retornaInfo(no), getPageRankAtualDocumento(retornaInfo(no))); // Atualiza o page rank anterior

    somatorio += getDifPageRank(retornaDir(no));
    return somatorio;
}

static int terminouCalculoPageRank(RBTgen* no, int numDocs) {
    long double E = 0.0, somatorio = 0.0;
    somatorio = getDifPageRank(no);
    E = (long double) somatorio / numDocs;
    return E < DIF_LIMITE_PR;
}

/* Função recursiva */
static void calcPG(RBTgen* no, int numDocs) {
    if (no == NULL) return;
    calcPG(retornaEsq(no), numDocs);
    calculaPageRankDocumento(retornaInfo(no), numDocs); // Nó atual
    calcPG(retornaDir(no), numDocs);
}

void calculaPageRankRBTgen(RBTgen* no, int numDocs) {
    if (no == NULL) return;
    int k = 0;
    do {
        calcPG(no, numDocs); // Calcula o page rank de todos os docs para cada iteração
        k++;
    } while (!terminouCalculoPageRank(no, numDocs));
}