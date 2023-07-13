#ifndef TST_H
#define TST_H

#include "documento.h"

typedef struct node TST;

typedef struct{
    char *c;
    int len;
}String;


TST* rec_insert(TST* t, String* key, Doc* val, int d);

TST* TST_insert(TST* t, String* key , Doc* val);

TST* rec_search(TST* t, String* key, int d);

Doc** TST_search(TST* t, String* key);

void TST_destroy(TST* t);


#endif // TST_H