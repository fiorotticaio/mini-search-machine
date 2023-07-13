#ifndef TST_H
#define TST_H

#include "documento.h"
#include "RBTpal.h"
#include "RBTdocs.h"
#include <ctype.h>


typedef struct node TST;

typedef struct{
    char *c;
    int len;
}String;

String* String_create(char* c, int len);

TST * create_node();

TST* rec_insert(TST* t, String* key, Doc* val, int d);

TST* TST_insert(TST* t, String* key , Doc* val);

TST* rec_search(TST* t, String* key, int d);

TST* TST_search(TST* t, String* key);

TST* criaTSTpesquisa(RBTdocs* documentos, RBTpal* stopWords, char* dirEntrada, TST* T);

bool promptPesquisaTST(TST* t);

TST* ordenaValuesPorPageRankTST(TST* t);

Doc** interseccaoTST(Doc** resultadoFinal, TST* resultadoPalavra, int * nmrResultados);

void TST_destroy(TST* t);


#endif // TST_H