#ifndef RBT_DOCS_H
#define RBT_DOCS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "documento.h"

#define RED true
#define BLACK false

typedef struct noDocs RBTdocs;

/// @brief Cria um novo nó da árvore
/// @param chave 
/// @param valor 
/// @return Nó criado
RBTdocs* criaNoRBTdocs(char* chave, Doc* valor);

/// @brief Rotaciona a árvore para a esquerda
/// @param no 
/// @return Árvore rotacionada para a esquerda
RBTdocs* rotacionaEsqRBTdocs(RBTdocs* no);

/// @brief Rotaciona a árvore para a direita
/// @param no 
/// @return Árvore rotacionada para a direita
RBTdocs* rotacionaDirRBTdocs(RBTdocs* no);

/// @brief Troca a cor do nó
/// @param no 
void trocaCorRBTdocs(RBTdocs* no);

/// @brief Busca um nó na árvore
/// @param raiz
/// @param chave 
/// @return Documento buscado, caso exista. NULL, caso contrário
Doc* buscaRBTdocs(RBTdocs* n, char* chave);

/// @brief Insere um novo nó na árvore
/// @param no 
/// @param chave 
/// @param valor 
/// @return Árvore com o novo nó inserido
RBTdocs* insereRBTdocs(RBTdocs* no, char* chave, Doc* valor);

/// @brief Verifica se o nó é vermelho
/// @param no 
/// @return true, caso seja vermelho; false, caso contrário
bool ehVermelhoRBTdocs(RBTdocs* no);

/// @brief Imprime a árvore
/// @param no 
void printRBTdocs(RBTdocs* no);

/// @brief Libera a memória alocada pela árvore
/// @param no 
void liberaNoRBTdocs(RBTdocs* no);

/// @brief Retorna o nó da esquerda
/// @param no 
/// @return Nó da esquerda
RBTdocs* getEsq(RBTdocs* no);

/// @brief Retorna o nó da direita
/// @param no 
/// @return Nó da direita
RBTdocs* getDir(RBTdocs* no);

/// @brief Retorna o valor do nó
/// @param no 
/// @return Valor do nó (documento)
Doc* getValor(RBTdocs* no);

/// @brief Retorna a chave do nó
/// @param no 
/// @return Chave do nó (nome do documento)
char* getChave(RBTdocs* no);

/// @brief Calcula o PageRank de todos os documentos da árvore
/// @param no 
/// @param numDocs 
void calculaPageRankRBTdocs(RBTdocs* no, int numDocs);

#endif // RBT_DOCS_H