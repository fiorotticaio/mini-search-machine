#ifndef RBT_DOCS_H
#define RBT_DOCS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "documento.h"

#define RED true
#define BLACK false

typedef struct noDocs RBTdocs;

RBTdocs* criaNoRBTdocs(char* chave, Doc* valor);

RBTdocs* rotacionaEsqRBTdocs(RBTdocs* no);

RBTdocs* rotacionaDirRBTdocs(RBTdocs* no);

void trocaCorRBTdocs(RBTdocs* no);

Doc* buscaRBTdocs(RBTdocs* n, char* chave);

RBTdocs* insereRBTdocs(RBTdocs* no, char* chave, Doc* valor);

bool ehVermelhoRBTdocs(RBTdocs* no);

void printRBTdocs(RBTdocs* no);

void liberaNoRBTdocs(RBTdocs* no);

#endif // RBT_DOCS_H