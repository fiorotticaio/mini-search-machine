#ifndef RBT_GEN_H
#define RBT_GEN_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define RED true
#define BLACK false

typedef struct noGen RBTgen;


/// @brief Cria um novo no da arvore Árvore Rubro-Negra principal
/// @param dado  
/// @return Nó criado
RBTgen* criaNoRBTgen(void* chave, void *info);

/// @brief Rotaciona o nó para a esquerda
/// @param no 
/// @return Nó rotacionado para a esquerda
RBTgen* rotacionaEsqRBTgen(RBTgen* no);

/// @brief Rotaciona o nó para a direita
/// @param no 
/// @return Nó rotacionado para a direita
RBTgen* rotacionaDirRBTgen(RBTgen* no);

/// @brief Troca a cor do nó
/// @param no 
void trocaCorRBTgen(RBTgen* no);

/// @brief Busca um nó na árvore
/// @param n 
/// @param dado
/// @param função callback comparação 
/// @return Nó encontrado, ou NULL caso não exista
RBTgen* buscaRBTgen(RBTgen* n, void* chave, int (*cb) (void*, void*));

/// @brief Insere um novo nó na árvore
/// @param no 
/// @param chave 
/// @param função callback verifica se já existe valor asssociado a chave 
/// @return Árvore com o novo nó inserido
RBTgen* insereRBTgen(RBTgen* no,void* chave, void* dado, int (*cb) (void*, void*), int (*cbDado) (RBTgen*, void*));

/// @brief Verifica se o nó é vermelho
/// @param no 
/// @return treu se for vermelho, false caso contrário
bool ehVermelhoRBTgen(RBTgen* no);

/// @brief percorre árvore RBT
/// @param raiz
/// @param função trata dados
void percorreRBTgen(RBTgen* no, void (*cb) (void*) );

void liberaNoRBTgen(RBTgen* no, void (*cb) (void*));

#endif // RBT_GEN_H