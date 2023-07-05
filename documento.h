#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIF_LIMITE_PR 0.000001 // 10^-6  
#define ALFA_PR 0.85

typedef struct noDocs RBTdocs;

typedef struct documento Doc;

Doc* criaDocumento(char* nome, int numTotalDocs);

char *getNomeDocumento(Doc* documento);

long double getPageRankAtualDocumento(Doc* documento);

long double getPageRankAnteriorDocumento(Doc* documento);

void setPageRankAnteriorDocumento(Doc* documento, long double pageRankAnterior);

int getNumLinksInDocumento(Doc* documento);

void setNumLinksInDocumento(Doc* documento, int numLinks);

int getNumLinksOutDocumento(Doc* documento);

void setNumLinksOutDocumento(Doc* documento, int numLinks);

void adicionaLinkOutDocumento(Doc* documento, Doc* link, int posicao);

void adicionaLinkInDocumento(Doc* documento, Doc* link);

void liberaDocumento(Doc* documento);

void imprimeDocumento(Doc* doc);

char** leNomeDocumentos(char* dirEntrada, int* qtdDocs);

void liberaNomeDocumentos(char** nomeDocumentos);

RBTdocs* leDocumentos(char** nomeDocumentos, int numDocs, char* dirEntrada);

void linkaDocumentos(RBTdocs* documentos, char* dirEntrada);

void calculaPageRankDocumento(Doc* doc, int numDocs);

#endif // DOCUMENTO_H