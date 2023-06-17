#ifndef RBT_DOCS_H
#define RBT_DOCS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "documento.h"

#define RED true
#define BLACK false

typedef struct noDocs RBTdocs;

// struct node {
//     char* chave;
//     Doc** valores;
//     int numValores;
//     bool cor;
//     RBTdocs *esq, *dir;
// };

RBTdocs* criaNo(char* chave, Doc** valores);

RBTdocs* rotacionaEsq(RBTdocs* no);

RBTdocs* rotacionaDir(RBTdocs* no);

void trocaCor(RBTdocs* no);

RBTdocs* insere_RBTdocs(RBTdocs* no, char* chave, Doc** valores);

bool ehVermelho(RBTdocs* no);

void liberaNo(RBTdocs* no);

#endif // RBT_DOCS_H