#include "RBTmain.h"

/* Red-Black Tree de possíveis buscas */

struct infoMain {
    Doc **valor;
    int   nDocs;
};




int comparaLexicografico(const void* a, const void* b) {
    Doc* docA = *(Doc**) a;
    Doc* docB = *(Doc**) b;
    return strcmp(getNomeDocumento(docA), getNomeDocumento(docB));
}

RBTgen* criaNoRBTmain(char* chave, Doc* valor) {

    InfoMain* info = (InfoMain*)malloc(sizeof(InfoMain));
    Doc**     docs = (Doc**)    malloc(sizeof(Doc*));
    
    info->valor[0] = valor;
    info->nDocs =    1;

    return criaNoRBTgen(strdup(chave), info);
}

int comparaDadosMain(void *a, void* b){
    InfoMain* info = (InfoMain*)b;
    return strcmp((char*)a, info->valor)
}

RBTgen* buscaRBTmain(RBTgen* n, char* chave) {
    char* chaveLower = strdup(chave);  // Cria uma cópia da chave

    int i = 0;
    for (i = 0; chaveLower[i] != '\0'; i++) {
        chaveLower[i] = tolower(chaveLower[i]);  // Converte para minúsculo
    }

    RBTgen* r = buscaRBTmain(n, chaveLower);
    free(chaveLower);
    return r;
}
int retornaNdocs(InfoMain *info){
    if(info != NULL) 
        return info->nDocs;
    return 0;
}    
Doc* retornaDoc(InfoMain *info, int i){
    return info->valor[i];
}
/*
int verificaDocJaPertence(RBTgen* no, void* info){
    InfoMain* infoM = (InfoMain*)info;

    int i = 0;
    int N = retornaNdocs(retornaInfo(no));
    
    for (i = 0; i < N; i++) {
        char* nomeDocNaArvore = getNomeDocumento(retornaDoc(retornaInfo(no), i));
        char* nomeDocAInserir = getNomeDocumento(infoM->valor);
        if (strcmp(nomeDocAInserir, nomeDocNaArvore) == 0) return 1;
    }
    return 0;
}*/

RBTgen* insereRBTmain(RBTgen* no, char* chave, Doc* valor) {
    /* Caso nó seja NULO, não há chave, então crie */
    if (no == NULL) return criaNoRBTmain(chave, valor);

    int cmp = strcmp(chave, (char*)retornaChave(no));
    /* Caso chave seja menor, vá p esquerda, caso for maior, vá p direita, senão substitui */
    if      (cmp < 0) no->esq = insereRBTmain(no->esq, chave, valor);
    else if (cmp > 0) no->dir = insereRBTmain(no->dir, chave, valor);
    else {
        /* Verificando se o documento já não está associado à essa chave */
        int i = 0;
        for (i = 0; i < no->nDocs; i++) {
            char* nomeDocNaArvore = getNomeDocumento(no->valor[i]);
            char* nomeDocAInserir = getNomeDocumento(valor);
            if (strcmp(nomeDocAInserir, nomeDocNaArvore) == 0) return no;
        }

        /* Caso não esteja, insira-o na árvore */
        no->nDocs++;
        Doc** docs = (Doc**) realloc(no->valor, sizeof(Doc*) * no->nDocs);
        docs[no->nDocs - 1] = valor;
        no->valor = docs;
    }

    /* Linhas que demoraram 30 anos para serem feitas pelo Sedwick (conserta RBT ao inserir) */
    if (ehVermelhoRBTmain(no->dir) && !ehVermelhoRBTmain(no->esq))     no = rotacionaEsqRBTmain(no);
    if (ehVermelhoRBTmain(no->esq) && ehVermelhoRBTmain(no->esq->esq)) no = rotacionaDirRBTmain(no);
    if (ehVermelhoRBTmain(no->esq) && ehVermelhoRBTmain(no->dir))      trocaCorRBTmain(no);
    return no;
}

void criaRBTpesquisa(RBTdocs* documentos, RBTgen* stopWords, char* dirEntrada, RBTmain** T){
    if (documentos == NULL) return;

    /* Percorrendo recursivamente o ramo da esquerda */
    if (getEsq(documentos) != NULL) criaRBTpesquisa(getEsq(documentos), stopWords, dirEntrada, T);
    
    /* Acessando o documento atual */
    Doc* doc = getValor(documentos);
    char diretorio[100];
    sprintf(diretorio, "%s/pages/%s", dirEntrada, getNomeDocumento(doc));
    FILE* arq = fopen(diretorio, "r");

    /* Caso haja problema com o diretório */
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", diretorio);
        exit(1);
    }

    /* Adicionando as palavras do documento na RBT de pesquisa */
    char* palavra = NULL;
    while (fscanf(arq, "%ms", &palavra) != EOF) {
        
        /* Transforma a palavra em minusculo */
        int i = 0;
        for (i = 0; palavra[i] != '\0'; i++) palavra[i] = tolower(palavra[i]);

        /* Adiciona a palavra nas pesquisas possíveis se não for uma stopwords */
        if (buscaRBTPal(stopWords, palavra) == NULL) {
            *T = insereRBTmain(*T, palavra, doc);
        }
        
        free(palavra);
    }

    /* Percorrendo recursivamente o ramo da direita */
    if (getDir(documentos) != NULL) criaRBTpesquisa(getDir(documentos), stopWords, dirEntrada, T);

    fclose(arq);
}

void ordenaValuesPorPageRank(RBTmain** T){
    if (*T == NULL) return;

    if((*T)->esq != NULL) ordenaValuesPorPageRank(&(*T)->esq);

    /* Nó atual */
    Doc** docs = (*T)->valor;
    int nDocs = (*T)->nDocs;
    qsort(docs, nDocs, sizeof(Doc*), comparaLexicografico);

    if((*T)->dir != NULL) ordenaValuesPorPageRank(&(*T)->dir);
}

bool ehVermelhoRBTmain(RBTmain* no) {
    if (no == NULL) return BLACK;
    return no->cor == RED;
}

void printRBTmain(RBTmain* no) {
    if (no == NULL) return;
    printRBTmain(no->esq);
    printf("%s %d\n", no->chave, no->nDocs);
    for (int i = 0; i < no->nDocs; i++) {
        printf("\t%s\t %Lf \n", getNomeDocumento(no->valor[i]), getPageRankAtualDocumento(no->valor[i]));
    }
    printRBTmain(no->dir);
}

int comparaPageRankComDesempate(const void* a, const void* b) {
    Doc* docA = *(Doc**) a;
    Doc* docB = *(Doc**) b;
    if (getPageRankAtualDocumento(docA) > getPageRankAtualDocumento(docB)) return -1;
    if (getPageRankAtualDocumento(docA) < getPageRankAtualDocumento(docB)) return 1;
        
    return strcmp(getNomeDocumento(docA), getNomeDocumento(docB));
}

bool promptPesquisa(RBTmain * T) {
    /* Recebendo todas as palavras buscadas em um vetor */
    char buscas[100]; //TODO: valor 100 arbitrário
    printf("search:");
    
    /* Testando condição de parada */
    if (scanf("%[^\n]", buscas)<0) return false;
    
    /* Limpando o buffer do scanf */
    scanf("%*c"); 

    char* palavra = strtok(buscas, " ");
    Doc** resultadoFinal = NULL;
    int nmrResultados = 0;
    RBTmain* resultadoPalavra = NULL;
    
    /* Iterando por cada palavra da busca */
    while (palavra) {

        /* Achando os nó da RBT com os documentos que contém a palavra atual */
        resultadoPalavra = buscaRBTmain(T, palavra);

        /* Fazendo a intersecção com os resultados anteriores */
        resultadoFinal = interseccao(resultadoFinal, resultadoPalavra, &nmrResultados);

        /* Proxima palavra */
        palavra = strtok(NULL, " ");

        /* Caso tenha algum dos termo que não tenha sido achado, nem continua a procurar os outros */
        if (resultadoFinal==NULL) break;
    }

    /* Definido Buffer os valores de page ranks que serão impressos */
    char* pageRanksArquivos = NULL;

    if (resultadoFinal != NULL)  {

        /* Ordenando os resultados, incluindo criterio de desempate */
        qsort(resultadoFinal, nmrResultados, sizeof(Doc*), comparaPageRankComDesempate);
        
        printf("pages:");

        /* Iterando pelos resultados uma única vez, com ajuda de buffer */
        int i = 0;
        for (i = 0; i < nmrResultados; i++) {
            
            /* Não precisa fazer um buffer com os nomes, só os pageranks */
            printf("%s ", getNomeDocumento(resultadoFinal[i]));

            /* Fazendo um buffer com os valores de page rank */
            long double pageRank = getPageRankAtualDocumento(resultadoFinal[i]);
            char aux[100];
            sprintf(aux, "%Lf", pageRank);
            if (pageRanksArquivos == NULL) {
                pageRanksArquivos = strdup(aux);
            } else {
                size_t newSize = strlen(aux) + strlen(pageRanksArquivos) + 2;
                char* tempBuffer = malloc(newSize); 
                if (tempBuffer == NULL) {
                    printf("Erro ao alocar memória para o buffer de page ranks\n");
                    exit(1);
                }
                sprintf(tempBuffer, "%s %Lf", pageRanksArquivos, pageRank);
                free(pageRanksArquivos);
                pageRanksArquivos = tempBuffer;
            }
        }

        /* Imprimindo page ranks */
        if (pageRanksArquivos == NULL) printf("\npr:\n");
        else                           printf("\npr:%s\n", pageRanksArquivos);

        free(pageRanksArquivos);
    } else {
        printf("pages:\n");
        printf("pr:\n");
    }

    free(resultadoFinal);
    
    return true;
}

Doc** interseccao(Doc** resultadoFinal, RBTmain* resultadoPalavra, int * nmrResultados){

    /* Vetor de resultados anteriores está vazio, apenas copie o resultado atual */
    if (resultadoFinal == NULL && resultadoPalavra != NULL) {
        (*nmrResultados) = resultadoPalavra->nDocs;
        Doc** novoResultado = malloc(sizeof(Doc*) * (*nmrResultados));
        for (int i=0;i<(*nmrResultados);i++) novoResultado[i] = resultadoPalavra->valor[i];
        return novoResultado;
    
    // Caso não tenha sido encontrada nenhuma palavra anteriormente e nem atualmente, retorne nulo
    } else if (resultadoFinal == NULL && resultadoPalavra != NULL) return NULL;

    // Caso não tenha sido encontrada nenhuma palavra atualmente, retorne NULL, já que não há intersecção
    else if (resultadoPalavra==NULL) {
        free(resultadoFinal);
        return NULL;
    }

    // Senão, crie um novo vetor para armazenar a intersecção
    int tamanhoMaximo = (*nmrResultados);
    Doc** novoResultado = malloc(sizeof(Doc*) * tamanhoMaximo);
    (*nmrResultados) = 0;

    int i = 0; // "Ponteiro" do vetor de resultados anteriores
    int j = 0; // "Ponteiro" do vetor de resultados atuais
    int k = 0; // "Ponteiro" do vetor da intersecção

    /* Iterando pelos valores dos dois vetores, levando em consideração o page rank */
    while ((i < tamanhoMaximo) && (j < resultadoPalavra->nDocs)) {
        char* nomeDocAnterior = getNomeDocumento(resultadoFinal[i]);
        char* nomeDocAtual = getNomeDocumento(resultadoPalavra->valor[j]);
        
        // Caso o nome do documento seja menor (alfabeticamente) no vetor de resultados anteriores, incremente o ponteiro i 
        if (strcmp(nomeDocAnterior, nomeDocAtual)<0) {
            i++;
        
        // Caso o nome do documento seja menor (alfabeticamente) no vetor de resultados atuais, incremente o ponteiro j
        } else if (strcmp(nomeDocAnterior, nomeDocAtual)>0) {
            j++;
        
        // Caso contrário, é uma intersecção, então adicione ao vetor e incremente todos os ponteiros
        } else {
            novoResultado[k] = resultadoFinal[i];
            i++;
            j++;
            k++;
            (*nmrResultados)++;
        }
    }

    /* Desalocando o vetor de resultados antigo */
    free(resultadoFinal);
    
    /* Retornando novo vetor de resultados */
    return novoResultado;
}

void liberaNoRBTmain(RBTmain* no) {
    if (no == NULL) return;
    if (no->chave!=NULL) free(no->chave);
    if (no->valor!=NULL) free(no->valor);
    if (no->esq != NULL) liberaNoRBTmain(no->esq);
    if (no->dir != NULL) liberaNoRBTmain(no->dir);
    free(no);
}