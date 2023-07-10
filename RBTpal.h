#ifndef RBT_PAL_H
#define RBT_PAL_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "documento.h"
#include "RBTgen.h"

#define RED true
#define BLACK false


/// @brief Cria nó da RBT de palavras
/// @param chave 
/// @return Nó criado
RBTgen* criaNoRBTpal(char* chave);

/// @brief Busca nó na RBT de palavras
/// @param n 
/// @param valor 
/// @return A palavra buscada, ou NULL se não encontrada
char* buscaRBTPal(RBTgen* n, char* chave);

/// @brief Insere nó na RBT de palavras
/// @param no 
/// @param chave 
/// @return Árvore com o nó inserido
RBTgen* insereRBTpal(RBTgen* no, char* chave);


/// @brief Libera nó da RBT de palavras
/// @param no 
void liberaNoRBTpal(RBTgen* no);

/// @brief Lê as stopwords
/// @param dirEntrada 
/// @return RBT das stopwords
RBTgen* leStopWords(char* dirEntrada);

#endif // RBT_PAL_H