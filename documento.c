#include "documento.h"

struct documento {
    char *nome;
    long double pageRank;
};

Doc* criaDocumento(char* nome, int numLinks) {
    Doc *documento = (Doc*) malloc(sizeof(Doc));
    documento->nome = strdup(nome);
    documento->pageRank = 1.0 / numLinks;
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
