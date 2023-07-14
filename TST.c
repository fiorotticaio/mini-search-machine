#include "TST.h"

struct node
{
    unsigned char c;
    Doc** val;
    int nDocs;
    TST* l, * m, * r;
};

int comparaLexicografico2(const void* a, const void* b) {
    Doc* docA = *(Doc**) a;
    Doc* docB = *(Doc**) b;
    return strcmp(getNomeDocumento(docA), getNomeDocumento(docB));
}

String* String_create(char* c, int len){
    String* s = (String*) malloc(sizeof(String));
    s->c = (unsigned char*) malloc(sizeof(unsigned char) * len);
    memcpy(s->c, c, len);
    s->len = len;
    return s;
}

TST * create_node(){
    TST* t = (TST*) malloc(sizeof(TST));
    t->c = 0;
    t->val = NULL;
    t->nDocs = 0;
    t->l = t->m = t->r = NULL;
    return t;
}

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
    else if (d < key->len - 1) { return rec_search(t->m, key, d+1);}
    else { return t; }
}

TST* TST_search(TST* t, String* key) {
    return rec_search(t, key, 0);
}

int comparaPageRankComDesempateTST(const void* a, const void* b) {
    Doc* docA = *(Doc**) a;
    Doc* docB = *(Doc**) b;
    if (getPageRankAtualDocumento(docA) > getPageRankAtualDocumento(docB)) return -1;
    if (getPageRankAtualDocumento(docA) < getPageRankAtualDocumento(docB)) return 1;
        
    return strcmp(getNomeDocumento(docA), getNomeDocumento(docB));
}

TST* criaTSTpesquisa(RBTdocs* documentos, RBTpal* stopWords, char* dirEntrada, TST* T){
    if (documentos == NULL) return NULL;

    /* Percorrendo recursivamente o ramo da esquerda */
    if (getEsq(documentos) != NULL) T = criaTSTpesquisa(getEsq(documentos), stopWords, dirEntrada, T);
    
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
            String* str = String_create(palavra, strlen(palavra));
            T = TST_insert(T, str, doc);
            free(str->c);
            free(str);
        }
        
        free(palavra);
    }

    /* Percorrendo recursivamente o ramo da direita */
    if (getDir(documentos) != NULL)T = criaTSTpesquisa(getDir(documentos), stopWords, dirEntrada, T);

    fclose(arq);
    return T;
}

TST* ordenaValuesPorPageRankTST(TST* T){
    if (T == NULL) return T;

    if(T->l != NULL)T->l = ordenaValuesPorPageRankTST(T->l);

    /* Nó atual */
    Doc** docs = T->val;
    int nDocs = T->nDocs;
    qsort(docs, nDocs, sizeof(Doc*), comparaLexicografico2);

    if(T->r != NULL) T->r = ordenaValuesPorPageRankTST(T->r);

    return T;
}

bool promptPesquisaTST(TST * T) {
    /* Recebendo todas as palavras buscadas em um vetor */
    printf("search:");
    char * buscas = NULL;
    size_t size = 0;
    size_t lido = getline(&buscas, &size, stdin);

    /* Tratando caso seja recebido o caractere de "fim do arquivo" */
    if (lido==EOF) {
        free(buscas);
        return false;
    }

    /* Retirando o \n do final da busca */
    char* palavra = strtok(buscas, "\n");

    palavra = strtok(palavra, " ");
    Doc** resultadoFinal = NULL;
    int nmrResultados = 0;
    TST* resultadoPalavra = NULL;
    
    /* Iterando por cada palavra da busca */
    while (palavra) {

        /* Achando os nó da RBT com os documentos que contém a palavra atual */
        String* str = String_create(palavra, strlen(palavra));
        resultadoPalavra = TST_search(T, str);
        free(str->c);
        free(str);

        /* Fazendo a intersecção com os resultados anteriores */
        resultadoFinal = interseccaoTST(resultadoFinal, resultadoPalavra, &nmrResultados);

        /* Proxima palavra */
        palavra = strtok(NULL, " ");

        /* Caso tenha algum dos termo que não tenha sido achado, nem continua a procurar os outros */
        if (resultadoFinal==NULL) break;
    }

    /* Definido Buffer os valores de page ranks que serão impressos */
    char* pageRanksArquivos = NULL;

    if (resultadoFinal != NULL)  {

        /* Ordenando os resultados, incluindo criterio de desempate */
        qsort(resultadoFinal, nmrResultados, sizeof(Doc*), comparaPageRankComDesempateTST);
        
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
    free(buscas);
    
    return true;
}

Doc** interseccaoTST(Doc** resultadoFinal, TST* resultadoPalavra, int * nmrResultados){

    /* Vetor de resultados anteriores está vazio, apenas copie o resultado atual */
    if (resultadoFinal == NULL && resultadoPalavra != NULL) {
        (*nmrResultados) = resultadoPalavra->nDocs;
        Doc** novoResultado = malloc(sizeof(Doc*) * (*nmrResultados));
        for (int i=0;i<(*nmrResultados);i++) novoResultado[i] = resultadoPalavra->val[i];
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
        char* nomeDocAtual = getNomeDocumento(resultadoPalavra->val[j]);
        
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

void TST_destroy(TST* t){
    if (t == NULL) return;
    TST_destroy(t->l);
    TST_destroy(t->m);
    TST_destroy(t->r);
    free(t->val);
    free(t);
}

