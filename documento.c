#include "documento.h"

struct documento {
    char* nome;
    long double pageRank;
    int numLinks; // Número de documentos para as quais o documento aponta
    Doc** links; // Lista de documentos para as quais o documento aponta
};

Doc* criaDocumento(char* nome, int numTotalDocs) {
    Doc *documento = (Doc*) malloc(sizeof(Doc));
    documento->nome = strdup(nome);
    documento->pageRank = 1.0 / numTotalDocs;
    documento->numLinks = 0;
    documento->links = NULL;
    return documento;
}

char* getNomeDocumento(Doc* documento) {
    return documento->nome;
}

void setPageRankDocumento(Doc* documento, long double pageRank) {
    documento->pageRank = pageRank;
}

long double getPageRankDocumento(Doc* documento) {
    return documento->pageRank;
}

void liberaDocumento(Doc* documento) {
    free(documento->nome);
    free(documento);
}

char** leNomeDocumentos(char* dirEntrada, int* qtdDocs) {
    int numDocs = 0, numMaximoDocs = 1000;
    char** nomeDocs = (char**) malloc(numMaximoDocs * sizeof(char*));

    /* Abrindo o arquivo index.txt */
    char dirIndex[100];
    sprintf(dirIndex, "%s/index.txt", dirEntrada);
    FILE* arq = fopen(dirIndex, "r");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo no diretorio: %s\n", dirIndex);
        exit(1);
    }

    while (!feof(arq)) { // Enquanto tiver coisa pra ler
        char nomeDoc[100]; // Variável auxiliar para leitura
        fscanf(arq, "%[^\n]\n", nomeDoc); // Lê o nome do documento

        if (numDocs == numMaximoDocs-1) { // Se atingiu o limite (-1 por causa do NULL)
            numMaximoDocs *= 2; // Dobra o limite
            nomeDocs = (char**) realloc(nomeDocs, numMaximoDocs * sizeof(char*));
        }

        nomeDocs[numDocs] = strdup(nomeDoc);
        numDocs++;
    }

    /* Realocando o vetor para o tamanho definitivo */
    nomeDocs = (char**) realloc(nomeDocs, (numDocs+1) * sizeof(char*));
    nomeDocs[numDocs] = NULL; // Para facilitar iteração

    fclose(arq);
    *qtdDocs = numDocs; // Atualizando o valor de qtdDocs para a main
    return nomeDocs;
}

void liberaNomeDocumentos(char** nomeDocumentos) {
    int i = 0;
    while (nomeDocumentos[i] != NULL) {
        free(nomeDocumentos[i]);
        i++;
    }
    free(nomeDocumentos);
}

Doc** leDocumentos(char** nomeDocumentos, int numDocs, char* dirEntrada) {
    /* Criando o diretório onde estão os documentos */
    char dirDocs[100];
    sprintf(dirDocs, "%s/pages", dirEntrada);
    FILE* arq = fopen(dirDocs, "r");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo no diretorio: %s\n", dirDocs);
        exit(1);
    }

    /*
    Nota:
    Para criar a tabela (árvore) T, vamos ter que passar por todos os documentos
    pra conferir se dada palavra está lá, para assim ir criando as linhas da tabela.
    Portando, não tem problema criar um vetor de documentos aqui.
    */

    Doc** documentos = (Doc**) malloc((numDocs+1) * sizeof(Doc*)); // +1 por causa do NULL

    int i = 0;
    while (nomeDocumentos[i] != NULL) {
        documentos[i] = criaDocumento(nomeDocumentos[i], numDocs);
        i++;
    }
    documentos[i] = NULL; // Para facilitar iteração

    fclose(arq);
    return documentos;
}

void liberaDocumentos(Doc** documentos) {
    int i = 0;
    while (documentos[i] != NULL) {
        liberaDocumento(documentos[i]);
        i++;
    }
    free(documentos);
}