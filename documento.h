#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIF_LIMITE_PR 0.000001 // 10^-6  
#define ALFA_PR 0.85

typedef struct noDocs RBTdocs;

typedef struct documento Doc;

/// @brief Cria um documento
/// @param nome 
/// @param numTotalDocs 
/// @return Documento criado
Doc* criaDocumento(char* nome, int numTotalDocs);

/// @brief Retorna o nome do documento
/// @param documento 
/// @return Nome do documento
char* getNomeDocumento(Doc* documento);

/// @brief Retorna o page rank atual do documento
/// @param documento 
/// @return Page rank atual do documento
long double getPageRankAtualDocumento(Doc* documento);

/// @brief Retorna o page rank anterior do documento
/// @param documento 
/// @return Page rank anterior do documento
long double getPageRankAnteriorDocumento(Doc* documento);

/// @brief Define o page rank anterior do documento
/// @param documento 
/// @param pageRankAnterior 
void setPageRankAnteriorDocumento(Doc* documento, long double pageRankAnterior);

/// @brief Retorna o número de links in do documento
/// @param documento 
/// @return Número de links in do documento
int getNumLinksInDocumento(Doc* documento);

/// @brief Define o número de links in do documento
/// @param documento 
/// @param numLinks 
void setNumLinksInDocumento(Doc* documento, int numLinks);

/// @brief Retorna o número de links out do documento
/// @param documento 
/// @return Número de links out do documento
int getNumLinksOutDocumento(Doc* documento);

/// @brief Define o número de links out do documento
/// @param documento 
/// @param numLinks 
void setNumLinksOutDocumento(Doc* documento, int numLinks);

/// @brief Adiciona um link out ao documento
/// @param documento 
/// @param link 
/// @param posicao 
void adicionaLinkOutDocumento(Doc* documento, Doc* link, int posicao);

/// @brief Adiciona um link in ao documento
/// @param documento 
/// @param link 
void adicionaLinkInDocumento(Doc* documento, Doc* link);

/// @brief Libera a memória alocada para o documento
/// @param documento 
void liberaDocumento(Doc* documento);

/// @brief Imprime o documento
/// @param doc 
void imprimeDocumento(Doc* doc);

/// @brief Lê os nomes dos documentos
/// @param dirEntrada 
/// @param qtdDocs 
/// @return Vetor com os nomes dos documentos
char** leNomeDocumentos(char* dirEntrada, int* qtdDocs);

/// @brief Libera a memória alocada para o vetor de nomes dos documentos
/// @param nomeDocumentos 
void liberaNomeDocumentos(char** nomeDocumentos);

/// @brief Lê os documentos
/// @param nomeDocumentos 
/// @param numDocs 
/// @param dirEntrada 
/// @return Red Black Tree com os documentos
RBTdocs* leDocumentos(char** nomeDocumentos, int numDocs, char* dirEntrada);

/// @brief Linka cada documento com seus links in e links out
/// @param documentos 
/// @param dirEntrada 
void linkaDocumentos(RBTdocs* documentos, char* dirEntrada);

/// @brief Calcula o page rank do documento
/// @param doc
/// @param numDocs 
void calculaPageRankDocumento(Doc* doc, int numDocs);

#endif // DOCUMENTO_H