#include "TST.h"

struct node
{
    unsigned char c;
    Doc** val;
    int nDocs;
    TST* l, * m, * r;
};

TST* rec_insert(TST* t, String* key, Doc* val, int d){
    unsigned char c = key->c[d];
    if (t == NULL) { t = create_node(); t->c = c;}
    if (c < t->c) { t->l = rec_insert(t->l, key, val, d); }
    else if (c > t->c) { t->r = rec_insert(t->r, key, val, d); }
    else if (d < key->len - 1) {
        t->m = rec_insert(t->m, key, val, d+1);
    } else { 
        int i = 0;
        for (i = 0; i < t->nDocs; i++) {
            char* nomeDocNaArvore = getNomeDocumento(t->val[i]);
            char* nomeDocAInserir = getNomeDocumento(val);
            if (strcmp(nomeDocAInserir, nomeDocNaArvore) == 0) return t;
        }

        /* Caso não esteja, insira-o na árvore */
        t->nDocs++;
        Doc** docs = (Doc**) realloc(t->val, sizeof(Doc*) * t->nDocs);
        docs[t->nDocs - 1] = val;
        t->val = docs;
    }
    return t;

}

TST* TST_insert(TST* t, String* key , Doc* val) {
    return rec_insert(t, key, val, 0);
}

TST* rec_search(TST* t, String* key, int d) {
    if (t == NULL) { return NULL; }
    unsigned char c = key->c[d];
    if (c < t->c) { return rec_search(t->l, key, d); }
    else if (c > t->c) { return rec_search(t->r, key, d); }
    else if (d < key->len - 1) {
    return rec_search(t->m, key, d+1);
    } else { return t; }
}

Doc** TST_search(TST* t, String* key) {
    t = rec_search(t, key, 0);
    if (t == NULL) { return NULL; }
    else { return t->val; }
}

void TST_destroy(TST* t){
    if (t == NULL) return;
    TST_destroy(t->l);
    TST_destroy(t->m);
    TST_destroy(t->r);
    free(t->val);
    free(t);
}

