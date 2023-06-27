#ifndef RBT_MAIN_H
#define RBT_MAIN_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "documento.h"
#include "RBTpal.h"
#include "RBTdocs.h"

#define RED true
#define BLACK false

typedef struct noMain RBTmain;

RBTmain* criaNoRBTmain(char* chave, Doc* valor);

RBTmain* rotacionaEsqRBTmain(RBTmain* no);

RBTmain* rotacionaDirRBTmain(RBTmain* no);

void trocaCorRBTmain(RBTmain* no);

Doc** buscaRBTmain(RBTmain* n, char* chave);

RBTmain* insereRBTmain(RBTmain* no, char* chave, Doc* valor);

void criaRBTpesquisa(RBTdocs* docs, RBTpal* stopWords, char* dirEntrada, RBTmain** T);

void ordenaValuesPorPageRank(RBTmain** T);

bool ehVermelhoRBTmain(RBTmain* no);

void printRBTmain(RBTmain* no);

void liberaNoRBTmain(RBTmain* no);

#endif // RBT_MAIN_H