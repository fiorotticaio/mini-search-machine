#include "RBTmain.h"

/* Red-Black Tree de possíveis buscas */

struct infoMain {
    Doc **valor;
    int   nDocs;
};

int retornaNdocs(InfoMain *info){
    if(info != NULL) 
        return info->nDocs;
    return 0;
}    

Doc* retornaDoc(InfoMain *info, int i){
    return info->valor[i];
}
Doc** retornaPtDocs(InfoMain *info){
    return info->valor;
}


int comparaLexicografico(const void* a, const void* b) {
    Doc* docA = *(Doc**) a;
    Doc* docB = *(Doc**) b;
    return strcmp(getNomeDocumento(docA), getNomeDocumento(docB));
}

RBTgen* criaNoRBTmain(char* chave, Doc* valor) {

    InfoMain* info = (InfoMain*)malloc(sizeof(InfoMain));   //alocando struct info
    info->valor = malloc(sizeof(Doc*));                  //alocando Doc **
        
    info->valor[0] = valor;
    info->nDocs =    1;

    return criaNoRBTgen(strdup(chave), info);
}

//int comparaDadosMain(void *a, void* b){
//    InfoMain* info = (InfoMain*)b;
//    return strcmp((char*)a, info->valor);
//}

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

//Função sem declaração no .h//
int verificaDocJaPertence(RBTgen* no, void* info){
    Doc* doc = (Doc*) info;
    
    int i = 0;
    int N = retornaNdocs(retornaInfo(no));
    
    for (i = 0; i < N; i++) {
        char* nomeDocNaArvore = getNomeDocumento(retornaDoc(retornaInfo(no), i));
        char* nomeDocAInserir = getNomeDocumento(doc);
        if (strcmp(nomeDocAInserir, nomeDocNaArvore) == 0) return 1;
    }
    return 0;
}

//void RBTmainSetNdocs()

//Função sem declaração no .h//
void* alocaInfoMain(RBTgen *no, void *valor){
    Doc* doc = (Doc*) valor;
    
    
    //InfoMain* info = retornaInfo(no);
    //info->nDocs = info->nDocs +1;
    /*InfoMain *info = retornaInfo(no);
    info->nDocs++;
    Doc** docs = (Doc**) realloc(info->valor, sizeof(Doc*) * info->nDocs);
    docs[info->nDocs - 1] = (Doc*)valor;
    info->valor = docs;
    return info;
    */
    //retornaInfo(no);
    //InfoMain *info = retornaInfo(no);
    //info->nDocs++;
    //info->valor = (Doc**) realloc(info->valor, sizeof(Doc*) * info->nDocs);
    //info->valor[info->nDocs - 1] = (Doc*)valor;
    //return info;
    return NULL;
}

RBTgen* insereRBTmain(RBTgen* no, char* chave, Doc* valor) {
    insereRBTgen(no, chave, valor, comparaString, verificaDocJaPertence, alocaInfoMain);
}



void criaRBTpesquisa(RBTgen* documentos, RBTgen* stopWords, char* dirEntrada, RBTgen** T){
    if (documentos == NULL) return;

    // Percorrendo recursivamente o ramo da esquerda //
    if (retornaEsq(documentos) != NULL) criaRBTpesquisa(retornaEsq(documentos), stopWords, dirEntrada, T);
    
    // Acessando o documento atual //
    Doc* doc = retornaInfo(documentos);
    char diretorio[100];
    sprintf(diretorio, "%s/pages/%s", dirEntrada, getNomeDocumento(doc));
    FILE* arq = fopen(diretorio, "r");

    // Caso haja problema com o diretório //
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", diretorio);
        exit(1);
    }

    // Adicionando as palavras do documento na RBT de pesquisa ///
    char* palavra = NULL;
    while (fscanf(arq, "%ms", &palavra) != EOF) {
        
        // Transforma a palavra em minusculo //
        int i = 0;
        for (i = 0; palavra[i] != '\0'; i++) palavra[i] = tolower(palavra[i]);

        // Adiciona a palavra nas pesquisas possíveis se não for uma stopwords //
        if (buscaRBTPal(stopWords, palavra) == NULL) {
            *T = insereRBTmain(*T, palavra, doc);
        }
        
        free(palavra);
    }

    // Percorrendo recursivamente o ramo da direita //
    if (retornaDir(documentos) != NULL) criaRBTpesquisa(retornaDir(documentos), stopWords, dirEntrada, T);

    fclose(arq);
}

RBTgen* ordenaValuesPorPageRank(RBTgen* T){
    if (T == NULL) return NULL;

    if(retornaEsq(T) != NULL) RBTgenSetEsq(T, ordenaValuesPorPageRank(retornaEsq(T))); 

    /* Nó atual */
    Doc** docs = retornaPtDocs(retornaInfo(T)); 
    int nDocs = retornaNdocs(retornaInfo(T));
    qsort(docs, nDocs, sizeof(Doc*), comparaLexicografico);

    if(retornaDir(T) != NULL) RBTgenSetDir(T, ordenaValuesPorPageRank(retornaDir(T)));

    return T;
}

//Função sem declaração no .h//
void printDadosMain(void *info){
    InfoMain *infoDados = (InfoMain*)info;

    //printf("%s %d\n", no->chave, infoDados->nDocs);/************VErificar se Função eh usada|não imprime chave************/
    for (int i = 0; i < infoDados->nDocs; i++) {
        printf("\t%s\t %Lf \n", getNomeDocumento(infoDados->valor[i]), getPageRankAtualDocumento(infoDados->valor[i]));
    }
}
void printRBTmain(RBTgen* no) {
    percorreRBTgen(no, printDadosMain);
}

int comparaPageRankComDesempate(const void* a, const void* b) {
    Doc* docA = *(Doc**) a;
    Doc* docB = *(Doc**) b;
    if (getPageRankAtualDocumento(docA) > getPageRankAtualDocumento(docB)) return -1;
    if (getPageRankAtualDocumento(docA) < getPageRankAtualDocumento(docB)) return 1;
        
    return strcmp(getNomeDocumento(docA), getNomeDocumento(docB));
}

bool promptPesquisa(RBTgen * T) {
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
    RBTgen* resultadoPalavra = NULL;
    
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

Doc** interseccao(Doc** resultadoFinal, RBTgen* resultadoPalavra, int * nmrResultados){


    /* Vetor de resultados anteriores está vazio, apenas copie o resultado atual */
    if (resultadoFinal == NULL && resultadoPalavra != NULL) {
        (*nmrResultados) = retornaNdocs(retornaInfo(resultadoPalavra));
        Doc** novoResultado = malloc(sizeof(Doc*) * (*nmrResultados));
        for (int i=0;i<(*nmrResultados);i++) novoResultado[i] = retornaDoc(retornaInfo(resultadoPalavra), i);
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
    while ((i < tamanhoMaximo) && (j < retornaNdocs(retornaInfo(resultadoPalavra)))) {
        char* nomeDocAnterior = getNomeDocumento(resultadoFinal[i]);
        char* nomeDocAtual    = getNomeDocumento(retornaDoc(retornaInfo(resultadoPalavra), j));
        
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

void liberaDadosMain(void *info){
    InfoMain *infoDados = (InfoMain*)info;
    free(infoDados);
    return;
}
void liberaNoRBTmain(RBTgen* no) {
    liberaNoRBTgen(no, liberaDadosMain);
}
