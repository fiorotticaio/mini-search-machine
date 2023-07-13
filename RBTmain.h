#ifndef RBT_MAIN_H
#define RBT_MAIN_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "documento.h"
#include "RBTpal.h"
#include "RBTdocs.h"
#include "RBTgen.h"

#define RED true
#define BLACK false

typedef struct infoMain InfoMain;

/// @brief Cria um novo no da arvore Árvore Rubro-Negra principal
/// @param chave 
/// @param valor 
/// @return Nó criado
RBTgen* criaNoRBTmain(char* chave, Doc* valor);

/// @brief Busca um nó na árvore
/// @param n 
/// @param chave 
/// @return Nó encontrado, ou NULL caso não exista
RBTgen* buscaRBTmain(RBTgen* n, char* chave);

/// @brief Insere um novo nó na árvore
/// @param no 
/// @param chave 
/// @param valor 
/// @return Árvore com o novo nó inserido
RBTgen* insereRBTmain(RBTgen* no, char* chave, Doc* valor);

/// @brief Preenche a árvore principal com as palavras dos documentos
/// @param docs 
/// @param stopWords 
/// @param dirEntrada 
/// @param T 
void criaRBTpesquisa(RBTgen* documentos, RBTgen* stopWords, char* dirEntrada, RBTgen** T);

/// @brief Ordena os documentos de uma palavra de acordo com o page rank
/// @param T 
RBTgen* ordenaValuesPorPageRank(RBTgen* T);

/// @brief Imprime a árovre principal
/// @param raiz
void printRBTmain(RBTgen* no);

/// @brief Interação com o usuário para a pesquisa
/// @param T 
bool promptPesquisa(RBTgen * T);

/// @brief Faz a intersecção dos documentos de cada termo da pesquisa
/// @param resultadoFinal 
/// @param resultadoPalavra 
/// @param nmrResultados 
/// @return 
Doc** interseccao(Doc** resultadoFinal, RBTgen* resultadoPalavra, int * nmrResultados);

/// @brief Libera a memória alocada para a árvore principal
/// @param no 
void liberaNoRBTmain(RBTgen* no);

#endif // RBT_MAIN_H