#ifndef RBT_PAL_H
#define RBT_PAL_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "documento.h"

#define RED true
#define BLACK false

typedef struct noPal RBTpal;

RBTpal* criaNoRBTpal(int chave, char* valor);

RBTpal* rotacionaEsqRBTpal(RBTpal* no);

RBTpal* rotacionaDirRBTpal(RBTpal* no);

void trocaCorRBTpal(RBTpal* no);

char* buscaRBTPal(RBTpal* n, char* valor);

RBTpal* insereRBTpal(RBTpal* no, int chave, char* valor);

bool ehVermelhoRBTpal(RBTpal* no);

void liberaNoRBTpal(RBTpal* no);

RBTpal* leStopWords(char* dirEntrada);

#endif // RBT_PAL_H