#include "RBTpal.h"

/* Red-Black Tree de palavras (para as stopwords) */



RBTgen* criaNoRBTpal(char* chave) {
    return criaNoRBTgen(strdup(chave), NULL);
}

char* buscaRBTPal(RBTgen* n, char* chave) {
    if(buscaRBTgen(n, chave, comparaString) != NULL) 
        return chave;
    return NULL;
}

void* RetornaDadoPal (RBTgen* r, void *info){
    return info;
}

RBTgen* insereRBTpal(RBTgen* no, char* chave) {
    return insereRBTgen(no, chave, NULL, comparaString, funcFalse, RetornaDadoPal);
}

void liberaDadosNo(void *info){
    free(info);
    return;
}

void liberaNoRBTpal(RBTgen* no) {
    liberaNoRBTgen(no, liberaDadosNo);
}

RBTgen* leStopWords(char* dirEntrada) {
    /* Criando diretório do arquivo stopwords.txt */
    char stopWordsDir[100];
    sprintf(stopWordsDir, "%s/stopwords.txt", dirEntrada);
    FILE* stopWordsArq = fopen(stopWordsDir, "r");

    if (stopWordsArq == NULL) {
        printf("Erro ao abrir arquivo no diretorio: %s\n", stopWordsDir);
        exit(1);
    }

    int chaveStopWord = 0;
    RBTgen* stopWords = NULL; // Raiz da árvore

    while (!feof(stopWordsArq)) {
        char stopWord[100]; // Variável auxiliar para leitura
        fscanf(stopWordsArq, "%[^\n]\n", stopWord); // Lê a stopWord
        stopWords = insereRBTpal(stopWords, stopWord); // Insere a nova stopWord na RBT
        chaveStopWord++;
    }

    fclose(stopWordsArq);
    return stopWords;
}