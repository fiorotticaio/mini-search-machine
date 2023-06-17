#include "documento.h"

struct documento {
    char* nome;
    long double pageRank;
    int numLinks; // Número de documentos para as quais o documento aponta
    Doc** links; // Lista de documentos para as quais o documento aponta
};

Doc* criaDocumento(char* nome, int numTotalDocs) {
    Doc *documento = (Doc*) malloc(sizeof(Doc));
    documento->nome = strdup(nome);
    documento->pageRank = 1.0 / numTotalDocs;
    documento->numLinks = 0;
    documento->links = NULL;
    return documento;
}

char* getNomeDocumento(Doc* documento) {
    return documento->nome;
}

void setPageRankDocumento(Doc* documento, long double pageRank) {
    documento->pageRank = pageRank;
}

long double getPageRankDocumento(Doc* documento) {
    return documento->pageRank;
}

void liberaDocumentoDocumento(Doc* documento) {
    free(documento->nome);
    free(documento);
}
