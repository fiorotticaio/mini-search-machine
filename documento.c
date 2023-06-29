#include "documento.h"
#include "RBTdocs.h"

struct documento {
    char* nome;
    long double pageRankAnterior;
    long double pageRankAtual;
    Doc** linksOut ; // Lista de documentos para as quais o documento aponta
    Doc** linksIn; // Lista de documentos que apontam para o documento
    int numLinksIn; // Número de links que o documento recebe
    int numLinksOut; // Número de links que apontam para o documento
};

Doc* criaDocumento(char* nome, int numTotalDocs) {
    Doc *documento = (Doc*) malloc(sizeof(Doc));
    documento->nome = strdup(nome);
    documento->pageRankAnterior = 1.0 / numTotalDocs;
    documento->pageRankAtual = -1;
    documento->numLinksIn = 0;
    documento->numLinksOut = 0;
    documento->linksIn = NULL;
    documento->linksOut = NULL;
    return documento;
}

char* getNomeDocumento(Doc* documento) {
    return documento->nome;
}

long double getPageRankAtualDocumento(Doc* documento) {
    return documento->pageRankAtual;
}

long double getPageRankAnteriorDocumento(Doc* documento) {
    return documento->pageRankAnterior;
}

long double getLastPageRankDocumento(Doc *documento)
{
    return 0;
}

int getNumLinksInDocumento(Doc* documento) {
    return documento->numLinksIn;
}

void setNumLinksInDocumento(Doc* documento, int numLinksIn) {
    documento->numLinksIn = numLinksIn;
}

int getNumLinksOutDocumento(Doc* documento) {
    return documento->numLinksOut;
}

void setNumLinksOutDocumento(Doc* documento, int numLinksOut) {
    documento->numLinksOut = numLinksOut;
}

void liberaDocumento(Doc* documento) {    
    free(documento->nome);
    free(documento->linksIn);
    free(documento->linksOut);
    free(documento);
}

void imprimeDocumento(Doc* doc) {
    printf("nome: %s\n", doc->nome);
    printf("page rank: %.5Lf\n", doc->pageRankAtual);    
    printf("num links out: %d\n", doc->numLinksOut);
    for (int i = 0; i < doc->numLinksOut; i++) {
        printf("\tlink out %d: %s\n", i, doc->linksOut[i]->nome);
    }
    printf("num links in: %d\n", doc->numLinksIn);
    for (int i = 0; i < doc->numLinksIn; i++) {
        printf("\tlink in %d: %s\n", i, doc->linksIn[i]->nome);
    }
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

RBTdocs* leDocumentos(char** nomeDocumentos, int numDocs, char* dirEntrada) {
    /* Criando o diretório onde estão os documentos */
    char dirDocs[100];
    sprintf(dirDocs, "%s/pages", dirEntrada);
    FILE* arq = fopen(dirDocs, "r");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo no diretorio: %s\n", dirDocs);
        exit(1);
    }

    RBTdocs* documentos = NULL;
    int i = 0;
    while (nomeDocumentos[i] != NULL) {
        Doc* documento = criaDocumento(nomeDocumentos[i], numDocs);
        documentos = insereRBTdocs(documentos, nomeDocumentos[i], documento);
        i++;
    }

    fclose(arq);
    return documentos;
}

void linkaDocumentos(RBTdocs* documentos, char* dirEntrada) {
    /* Criando diretório do arquivo do grafo */
    char dirGrafo[100];
    sprintf(dirGrafo, "%s/graph.txt", dirEntrada);
    FILE* arq = fopen(dirGrafo, "r");

    if (arq == NULL) {
        printf("Erro ao abrir arquivo no diretorio: %s\n", dirGrafo);
        exit(1);
    }

    char nomeDoc[100], nomeDocLink[100];
    int qtdLinksDoc = 0;

    while (!feof(arq)) {
        fscanf(arq, "%s", nomeDoc); // Lê o nome do documento
        fscanf(arq, "%d", &qtdLinksDoc); // Lê a quantidade de links do documento

        Doc* doc = buscaRBTdocs(documentos, nomeDoc); // Busca o documento na árvore
        setNumLinksOutDocumento(doc, qtdLinksDoc); // Atualiza o número de links out do documento
        doc->linksOut = (Doc**) malloc(qtdLinksDoc * sizeof(Doc*)); // Aloca o vetor de links out do documento
        // FIXME: erro aqui

        int i = 0;
        while (i < qtdLinksDoc) {
            fscanf(arq, "%s", nomeDocLink); // Lê o nome do documento que o documento aponta

            /* Acessa o documento que o documento aponta */ 
            Doc* docLink = buscaRBTdocs(documentos, nomeDocLink);

            /* Adiciona o documento que o documento aponta na lista de links out do documento */
            adicionaLinkOutDocumento(doc, docLink, i);

            /* Adiciona o documento na lista de links in do documento que o documento aponta */
            adicionaLinkInDocumento(docLink, doc);

            i++;
        }
    }
    fclose(arq);
}

void adicionaLinkOutDocumento(Doc* documento, Doc* documentoLink, int posicao) {
    documento->linksOut[posicao] = documentoLink;
}

void adicionaLinkInDocumento(Doc *documento, Doc *documentoLink) {
    int numLinksIn = getNumLinksInDocumento(documento);
    if (numLinksIn == 0) {
        documento->linksIn = (Doc**) malloc(sizeof(Doc*));
    } else {
        documento->linksIn = (Doc**) realloc(documento->linksIn, (numLinksIn + 1) * sizeof(Doc*));
    }
    setNumLinksInDocumento(documento, numLinksIn + 1);
    documento->linksIn[numLinksIn] = documentoLink;
}

void calculaPageRankDocumento(Doc* doc, int numDocs) { // Diretamente da formula
    if (doc->numLinksOut != 0) {
        long double parcela = (long double) (1 - ALFA_PR) / numDocs;
        long double somatorio = 0.0;
        int j = 0;
        for (j = 0; j < doc->numLinksIn; j++) {
            Doc* docLink = doc->linksIn[j];
            somatorio += (long double) docLink->pageRankAnterior / docLink->numLinksOut;
        }
        doc->pageRankAtual = parcela + (ALFA_PR * somatorio);

    } else { // doc->numLinksOut == 0
        long double parcela1 = (long double) (1 - ALFA_PR) / numDocs;
        long double parcela2 = ALFA_PR * doc->pageRankAnterior;
        long double somatorio = 0.0;
        int j = 0;
        for (j = 0; j < doc->numLinksIn; j++) {
            Doc* docLink = doc->linksIn[j];
            somatorio += (long double) docLink->pageRankAnterior / docLink->numLinksOut;
        }
        doc->pageRankAtual = parcela1 + parcela2 + (ALFA_PR * somatorio);
    }
}

void consertaPageRankDocumento(Doc* doc) {
    doc->pageRankAnterior = doc->pageRankAtual;
}