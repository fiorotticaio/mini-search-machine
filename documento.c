#include "documento.h"

#include <stdlib.h>
#include <string.h>

struct documento
{
    char *nome;
    long double pageRank;
};

Doc *criaDocumento(char *nome, int numLinks)
{
    Doc *documento = (Doc *)malloc(sizeof(Doc));
    documento->nome = strdup(nome);
    documento->pageRank = 1.0 / numLinks;
    return documento;
}

char *getNome(Doc *documento)
{
    return documento->nome;
}

void setPageRank(Doc *documento, long double pageRank)
{
    documento->pageRank = pageRank;
}

long double getPageRank(Doc *documento)
{
    return documento->pageRank;
}

void liberaDocumento(Doc *documento)
{
    free(documento->nome);
    free(documento);
}
