#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct documento Doc;

Doc* criaDocumento(char* nome, int numLinks);

char *getNomeDocumento(Doc* documento);

long double getPageRankDocumento(Doc* documento);

void setPageRankDocumento(Doc* documento, long double pageRank);

void liberaDocumento(Doc* documento);

char** leNomeDocumentos(char* dirEntrada);

void liberaNomeDocumentos(char** nomeDocumentos);

#endif // DOCUMENTO_H