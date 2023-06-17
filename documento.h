#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <stdlib.h>
#include <string.h>

typedef struct documento Doc;

Doc* criaDocumento(char* nome, int numLinks);

char *getNomeDocumento(Doc* documento);

long double getPageRankDocumento(Doc* documento);

void setPageRankDocumento(Doc* documento, long double pageRank);

void liberaDocumentoDocumento(Doc* documento);

#endif // DOCUMENTO_H