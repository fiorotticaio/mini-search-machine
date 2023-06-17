#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noDocs RBTdocs;

typedef struct documento Doc;

Doc* criaDocumento(char* nome, int numTotalDocs);

char *getNomeDocumento(Doc* documento);

long double getPageRankDocumento(Doc* documento);

void setPageRankDocumento(Doc* documento, long double pageRank);

int getNumLinksInDocumento(Doc* documento);

void setNumLinksInDocumento(Doc* documento, int numLinks);

int getNumLinksOutDocumento(Doc* documento);

void setNumLinksOutDocumento(Doc* documento, int numLinks);

Doc* encontraDocumentoPeloNome(Doc** documentos, char* nome);

void adicionaLinkOutDocumento(Doc* documento, Doc* link, int posicao);

void adicionaLinkInDocumento(Doc* documento, Doc* link);

void liberaDocumento(Doc* documento);

char** leNomeDocumentos(char* dirEntrada, int* qtdDocs);

void liberaNomeDocumentos(char** nomeDocumentos);

RBTdocs* leDocumentos(char** nomeDocumentos, int numDocs, char* dirEntrada);


void linkaDocumentos(RBTdocs* documentos, char* dirEntrada);

#endif // DOCUMENTO_H