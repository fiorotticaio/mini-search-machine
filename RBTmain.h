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
RBTmain* criaNoRBTmain(char* chave, Doc* valor);

/// @brief Rotaciona o nó para a esquerda
/// @param no 
/// @return Nó rotacionado para a esquerda
RBTmain* rotacionaEsqRBTmain(RBTmain* no);

/// @brief Rotaciona o nó para a direita
/// @param no 
/// @return Nó rotacionado para a direita
RBTmain* rotacionaDirRBTmain(RBTmain* no);

/// @brief Troca a cor do nó
/// @param no 
void trocaCorRBTmain(RBTmain* no);

/// @brief Busca um nó na árvore
/// @param n 
/// @param chave 
/// @return Nó encontrado, ou NULL caso não exista
RBTmain* buscaRBTmain(RBTmain* n, char* chave);

/// @brief Insere um novo nó na árvore
/// @param no 
/// @param chave 
/// @param valor 
/// @return Árvore com o novo nó inserido
RBTmain* insereRBTmain(RBTmain* no, char* chave, Doc* valor);

/// @brief Preenche a árvore principal com as palavras dos documentos
/// @param docs 
/// @param stopWords 
/// @param dirEntrada 
/// @param T 
void criaRBTpesquisa(RBTdocs* documentos, RBTgen* stopWords, char* dirEntrada, RBTmain** T);

/// @brief Ordena os documentos de uma palavra de acordo com o page rank
/// @param T 
void ordenaValuesPorPageRank(RBTmain** T);

/// @brief Verifica se o nó é vermelho
/// @param no 
/// @return treu se for vermelho, false caso contrário
bool ehVermelhoRBTmain(RBTmain* no);

/// @brief Imprime a árovre principal
/// @param raiz
void printRBTmain(RBTmain* no);

/// @brief Interação com o usuário para a pesquisa
/// @param T 
bool promptPesquisa(RBTmain * T);

/// @brief Faz a intersecção dos documentos de cada termo da pesquisa
/// @param resultadoFinal 
/// @param resultadoPalavra 
/// @param nmrResultados 
/// @return 
Doc** interseccao(Doc** resultadoFinal, RBTmain* resultadoPalavra, int * nmrResultados);

/// @brief Libera a memória alocada para a árvore principal
/// @param no 
void liberaNoRBTmain(RBTmain* no);

#endif // RBT_MAIN_H