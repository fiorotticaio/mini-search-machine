#ifndef RBT_H
#define RBT_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "documento.h"

#define RED true
#define BLACK false

typedef struct node RBT;

#include "RBT.h"
#include "documento.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define RED true
#define BLACK false

// struct node {
//     char* chave;
//     Doc** valores;
//     int numValores;
//     bool cor;
//     RBT *esq, *dir;
// };

RBT* criaNo(char* chave, Doc** valores);

RBT* rotacionaEsq(RBT* no);

RBT* rotacionaDir(RBT* no);

void trocaCor(RBT* no);

RBT* insere_RBT(RBT* no, char* chave, Doc** valores);

bool ehVermelho(RBT* no);

void liberaNo(RBT* no);

#endif // RBT_H