#include "RBT.h"
#include "documento.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define RED true
#define BLACK false

struct node // RBT
{
    char *chave;
    Doc **valores;
    int numValores;
    bool cor;
    RBT *esq, *dir;
};

RBT *criaNo(char *chave, Doc **valores)
{
    RBT *no = (RBT *)malloc(sizeof(RBT));
    no->chave = strdup(chave);
    no->valores = valores;
    no->numValores = 1;
    no->cor = RED;
    no->esq = no->dir = NULL;
    return no;
}

RBT *rotacionaEsq(RBT *no)
{
    RBT *x = no->dir;
    no->dir = x->esq;
    x->esq = no;
    x->cor = x->esq->cor;
    x->esq->cor = RED;
    return x;
}

RBT *rotacionaDir(RBT *no)
{
    RBT *x = no->esq;
    no->esq = x->dir;
    x->dir = no;
    x->cor = x->dir->cor;
    x->dir->cor = RED;
    return x;
}

void trocaCor(RBT *no)
{
    no->cor = RED;
    no->esq->cor = BLACK;
    no->dir->cor = BLACK;
}

RBT *insere_RBT(RBT *no, char *chave, Doc **valores)
{
    if (no == NULL)
        return criaNo(chave, valores);

    int cmp = strcmp(chave, no->chave);
    if (cmp < 0)
        no->esq = insere_RBT(no->esq, chave, valores);
    else if (cmp > 0)
        no->dir = insere_RBT(no->dir, chave, valores);
    else // cmp == 0
    {
        no->valores = valores;
    }

    if (ehVermelho(no->dir) && !ehVermelho(no->esq))
        no = rotacionaEsq(no);
    if (ehVermelho(no->esq) && ehVermelho(no->esq->esq))
        no = rotacionaDir(no);
    if (ehVermelho(no->esq) && ehVermelho(no->dir))
        trocaCor(no);

    return no;
}
bool ehVermelho(RBT *no)
{
    if (no == NULL)
        return BLACK;
    return no->cor == RED;
}

void liberaNo(RBT *no)
{
    free(no->chave);
    free(no->valores);
    free(no);
}
