#ifndef DOCUMENTO_H
#define DOCUMENT_H

typedef struct documento Doc;

// Cria um documento com o nome fornecido e
// inicializa o pagerank com 1/numLinks
Doc *criaDocumento(char *nome, int numLinks);

char *getNome(Doc *documento);

long double getPageRank(Doc *documento);

void setPageRank(Doc *documento, long double pageRank);

void liberaDocumento(Doc *documento);

#endif // DOCUMENTO_H
