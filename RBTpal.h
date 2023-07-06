#ifndef RBT_PAL_H
#define RBT_PAL_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "documento.h"

#define RED true
#define BLACK false

typedef struct noPal RBTpal;

/// @brief Cria nó da RBT de palavras
/// @param chave 
/// @return Nó criado
RBTpal* criaNoRBTpal(char* chave);

/// @brief Rotaciona nó para a esquerda
/// @param no 
/// @return Nó rotacionado para a esquerda
RBTpal* rotacionaEsqRBTpal(RBTpal* no);

/// @brief Rotaciona nó para a direita
/// @param no 
/// @return Nó rotacionado para a direita
RBTpal* rotacionaDirRBTpal(RBTpal* no);

/// @brief Troca cor do nó
/// @param no 
void trocaCorRBTpal(RBTpal* no);

/// @brief Busca nó na RBT de palavras
/// @param n 
/// @param valor 
/// @return A palavra buscada, ou NULL se não encontrada
char* buscaRBTPal(RBTpal* n, char* valor);

/// @brief Insere nó na RBT de palavras
/// @param no 
/// @param chave 
/// @return Árvore com o nó inserido
RBTpal* insereRBTpal(RBTpal* no, char* chave);

/// @brief Verifica se nó é vermelho
/// @param no 
/// @return true, se vermelho; false, se preto
bool ehVermelhoRBTpal(RBTpal* no);

/// @brief Libera nó da RBT de palavras
/// @param no 
void liberaNoRBTpal(RBTpal* no);

/// @brief Lê as stopwords
/// @param dirEntrada 
/// @return RBT das stopwords
RBTpal* leStopWords(char* dirEntrada);

#endif // RBT_PAL_H