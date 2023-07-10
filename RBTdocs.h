#ifndef RBT_DOCS_H
#define RBT_DOCS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "documento.h"
#include "RBTgen.h"

#define RED true
#define BLACK false

typedef struct noDocs RBTdocs;


/// @brief Cria um novo nó da árvore
/// @param chave 
/// @param valor 
/// @return Nó criado
RBTgen* criaNoRBTdocs(char* chave, Doc* valor);

/// @brief Busca um nó na árvore
/// @param raiz
/// @param chave 
/// @return Documento buscado, caso exista. NULL, caso contrário
Doc* buscaRBTdocs(RBTgen* n, char* chave);

/// @brief Insere um novo nó na árvore
/// @param no 
/// @param chave 
/// @param valor 
/// @return Árvore com o novo nó inserido
RBTgen* insereRBTdocs(RBTgen* no, char* chave, Doc* valor);

/// @brief Imprime a árvore
/// @param no 
void printRBTdocs(RBTgen* no);

/// @brief Libera a memória alocada pela árvore
/// @param no 
void liberaNoRBTdocs(RBTgen* no);

/// @brief Calcula o PageRank de todos os documentos da árvore
/// @param no 
/// @param numDocs 
void calculaPageRankRBTdocs(RBTdocs* no, int numDocs);

#endif // RBT_DOCS_H