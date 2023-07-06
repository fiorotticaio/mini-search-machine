#include "RBTmain.h"


// Red-Black Tree de possíveis buscas
struct noMain { 
    char* chave;
    Doc** valor;
    int nDocs;
    bool cor;
    RBTmain *esq, *dir;
};

// TODO: lembrar de tirar depois
// int comparaPageRank(const void* a, const void* b) {
//     Doc* docA = *(Doc**) a;
//     Doc* docB = *(Doc**) b;
//     if (getPageRankAtualDocumento(docA)> getPageRankAtualDocumento(docB)) return -1;
//     if (getPageRankAtualDocumento(docA)< getPageRankAtualDocumento(docB)) return 1;
//     return 0;
// }

int comparaLexicografico(const void* a, const void* b) {
    Doc* docA = *(Doc**) a;
    Doc* docB = *(Doc**) b;
    return strcmp(getNomeDocumento(docA), getNomeDocumento(docB));
}


RBTmain* criaNoRBTmain(char* chave, Doc* valor) {
    RBTmain* no = (RBTmain*) malloc(sizeof(RBTmain));
    Doc** docs = (Doc**) malloc(sizeof(Doc*));
    docs[0] = valor;
    no->chave = strdup(chave);
    no->valor = docs;
    no->cor = RED;
    no->esq = no->dir = NULL;
    no->nDocs = 1;
    return no;
}

RBTmain* rotacionaEsqRBTmain(RBTmain* no) {
    RBTmain* x = no->dir;
    no->dir = x->esq;
    x->esq = no;
    x->cor = x->esq->cor;
    x->esq->cor = RED;
    return x;
}

RBTmain* rotacionaDirRBTmain(RBTmain *no) {
    RBTmain* x = no->esq;
    no->esq = x->dir;
    x->dir = no;
    x->cor = x->dir->cor;
    x->dir->cor = RED;
    return x;
}

void trocaCorRBTmain(RBTmain* no) {
    no->cor = RED;
    no->esq->cor = BLACK;
    no->dir->cor = BLACK;
}

RBTmain* buscaRBTmain(RBTmain* n, char* chave) {
    char* chave_lower = strdup(chave);  // Cria uma cópia da chave

    for (int i = 0; chave_lower[i] != '\0'; i++) {
        chave_lower[i] = tolower(chave_lower[i]);  // Converte para minúsculo
    }
    while (n != NULL) {
        int cmp = strcmp(chave_lower, n->chave);
        if      (cmp < 0)   n = n->esq;
        else if (cmp > 0)   n = n->dir;
        else {
            free(chave_lower);
            // return n->valor;
            return n;
        }
    }
    free(chave_lower);
    return NULL;
}

RBTmain* insereRBTmain(RBTmain* no, char* chave, Doc* valor) {
    
    // Caso nó seja NULO, não há chave, então crie
    if (no == NULL){
        return criaNoRBTmain(chave, valor);
    }

    int cmp = strcmp(chave, no->chave);

    // Caso chave seja menor, vá p esquerda, caso for maior, vá p direita, senão substitui
    if      (cmp < 0)   no->esq = insereRBTmain(no->esq, chave, valor);
    else if (cmp > 0)   no->dir = insereRBTmain(no->dir, chave, valor);
    else {
        // Verificando se o documento já não está associado à essa chave
        for(int i=0;i<no->nDocs;i++) {
            char * nomeDocNaArvore = getNomeDocumento(no->valor[i]);
            char * nomeDocAInserir = getNomeDocumento(valor);
            if (strcmp(nomeDocAInserir, nomeDocNaArvore)==0) return no;
        }

        // Caso não esteja, insira-o na árvore
        no->nDocs++;
        Doc** docs = (Doc**) realloc(no->valor, sizeof(Doc*) * no->nDocs);
        docs[no->nDocs - 1] = valor;
        no->valor = docs;
    }

    // Linhas que demoraram 30 anos para serem feitas pelo Sedwick (conserta RBT ao inserir)
    if (ehVermelhoRBTmain(no->dir) && !ehVermelhoRBTmain(no->esq))     no = rotacionaEsqRBTmain(no);
    if (ehVermelhoRBTmain(no->esq) && ehVermelhoRBTmain(no->esq->esq)) no = rotacionaDirRBTmain(no);
    if (ehVermelhoRBTmain(no->esq) && ehVermelhoRBTmain(no->dir))      trocaCorRBTmain(no);
    return no;
}

void criaRBTpesquisa(RBTdocs* documentos, RBTpal* stopWords, char* dirEntrada, RBTmain** T){
    if (documentos == NULL) return;

    // Percorrendo recursivamente o ramo da esquerda
    if(getEsq(documentos) != NULL) criaRBTpesquisa(getEsq(documentos), stopWords, dirEntrada, T);
    
    // Acessando o documento atual
    Doc* doc = getValor(documentos);
    char diretorio[100];
    sprintf(diretorio, "%s/pages/%s", dirEntrada, getNomeDocumento(doc));
    FILE* arq = fopen(diretorio, "r");

    // Caso haja problema com o diretório
    if(arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", diretorio);
        exit(1);
    }

    // Adicionando as palavras do documento na RBT de pesquisa
    char* palavra = NULL;
    while (fscanf(arq, "%ms", &palavra) != EOF) {
        
        // Transforma a palavra em minusculo
        for (int i = 0; palavra[i] != '\0'; i++) {
            palavra[i] = tolower(palavra[i]);
        }

        // Adiciona a palavra nas pesquisas possíveis se não for uma stopwords
        if (buscaRBTPal(stopWords, palavra) == NULL) {
            *T = insereRBTmain(*T, palavra, doc);
        }
        
        free(palavra);
    }

    // Percorrendo recursivamente o ramo da direita
    if(getDir(documentos) != NULL) criaRBTpesquisa(getDir(documentos), stopWords, dirEntrada, T);
    fclose(arq);
}

void ordenaValuesPorPageRank(RBTmain** T){
    if (*T == NULL) return;

    if((*T)->esq != NULL) ordenaValuesPorPageRank(&(*T)->esq);

    Doc** docs = (*T)->valor;
    int nDocs = (*T)->nDocs;
    // qsort(docs, nDocs, sizeof(Doc*), comparaPageRank);
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

//TODO: tem uma função igual essa só q sem desempate la encima
int comparaPageRankComDesempate(const void* a, const void* b) {
    Doc* docA = *(Doc**) a;
    Doc* docB = *(Doc**) b;
    if (getPageRankAtualDocumento(docA) > getPageRankAtualDocumento(docB)) return -1;
    if (getPageRankAtualDocumento(docA) < getPageRankAtualDocumento(docB)) return 1;
        
    return strcmp(getNomeDocumento(docA), getNomeDocumento(docB));
}

void promptPesquisa(RBTmain * T) {
    // Recebendo todas as palavras buscadas em um vetor
    char buscas[100]; //TODO: valor 100 arbitrário
    printf("search:");
    scanf("%[^\n]", buscas);

    char * palavra = strtok(buscas, " ");
    Doc** resultadoFinal = NULL;
    int nmrResultados = 0;
    bool buscaPorPalavraUnica = true;
    
    // Iterando por cada palavra da busca
    while(palavra) {
        // Achando os nó da RBT com os documentos que contém a palavra atual
        RBTmain* resultadoPalavra = buscaRBTmain(T, palavra);

        // Fazendo a intersecção com os resultados anteriores
        resultadoFinal = interseccao(resultadoFinal, resultadoPalavra, &nmrResultados);

        // Proxima palavra
        palavra = strtok(NULL, " ");

        // Sinalizando que a busca tem mais de uma palavra, para tomar a melhor decisao ao desalocar mais tarde
        if (palavra!=NULL) buscaPorPalavraUnica=false;
    }

    // Definido Buffer os valores de page ranks que serão impressos
    char * pageRanksArquivos = NULL;

    if (resultadoFinal != NULL)  {

        // Ordenando os resultados, incluindo criterio de desempate
        qsort(resultadoFinal, nmrResultados, sizeof(Doc*), comparaPageRankComDesempate);
        
        printf("pages:");

        // Iterando pelos resultados uma única vez, com ajuda de buffer
        for(int i=0;i<nmrResultados;i++) {
            
            //FIXME: tem um erro de memcpy nesses buffers q eu ainda não consegui resolver...

            // Não precisa fazer um buffer com os nomes, só os pageranks
            printf("%s ", getNomeDocumento(resultadoFinal[i]));

            // Fazendo um buffer com os valores de page rank
            long double pageRank = getPageRankAtualDocumento(resultadoFinal[i]);
            char aux[100];
            sprintf(aux, "%Lf", pageRank);
            if (pageRanksArquivos == NULL) {
                pageRanksArquivos = strdup(aux);
            } else {
                pageRanksArquivos = realloc(pageRanksArquivos, strlen(aux) + strlen(pageRanksArquivos) + 2);
                sprintf(pageRanksArquivos, "%s %Lf", pageRanksArquivos, pageRank);
            }
        }

        // Imprimindo page ranks
        if (pageRanksArquivos==NULL) printf("\npr:\n");
        else printf("\npr:%s\n", pageRanksArquivos);

        free(pageRanksArquivos);
        if (!buscaPorPalavraUnica) free(resultadoFinal);
    }
    
}

Doc** interseccao(Doc** resultadoFinal, RBTmain* resultadoPalavra, int * nmrResultados){

    // Vetor de resultados anteriores está vazio, apenas copie o resultado atual
    if (resultadoFinal==NULL && resultadoPalavra != NULL) {
        (*nmrResultados) = resultadoPalavra->nDocs;
        return resultadoPalavra->valor;
    
    // Caso não tenha sido encontrada nenhuma palavra anteriormente e nem atualmente, retorne nulo
    } else if (resultadoFinal==NULL && resultadoPalavra != NULL) return NULL;

    // Senão, crie um novo vetor para armazenar a intersecção
    int tamanhoMaximo = (*nmrResultados);
    Doc ** novoResultado = malloc(sizeof(Doc*) * tamanhoMaximo);
    (*nmrResultados) = 0;

    // Loops aninhados para detectar as intersecções (Giovanne falou que se fizer assim vai dar ruim)
    // int k=0;
    // for(int i=0;i<tamanhoMaximo;i++) {
    //     for(int j=0;j<resultadoPalavra->nDocs;j++) {
    //         char * nomeDocAtual = getNomeDocumento(resultadoFinal[i]);
    //         char * nomeDocNovaBusca = getNomeDocumento(resultadoPalavra->valor[j]);
    //         if (strcmp(nomeDocAtual, nomeDocNovaBusca)==0) {
    //             novoResultado[k++] = resultadoFinal[i];
    //             (*nmrResultados)++;
    //         }
    //     }
    // }

    // MÉTODO SEM LOOP ANINHADO
    int i = 0; // "Ponteiro" do vetor de resultados anteriores
    int j = 0; // "Ponteiro" do vetor de resultados atuais
    int k = 0; // "Ponteiro" do vetor da intersecção

    // Iterando pelos valores dos dois vetores, levando em consideração o page rank
    while ((i < tamanhoMaximo) && (j < resultadoPalavra->nDocs)) {
        char * nomeDocAnterior = getNomeDocumento(resultadoFinal[i]);
        char * nomeDocAtual = getNomeDocumento(resultadoPalavra->valor[j]);
        // Caso o page rank seja menor no vetor de resultados anteriores, incremente o ponteiro i 
        if (strcmp(nomeDocAnterior, nomeDocAtual)<0) {
            i++;
        // Caso o page rank seja menor no vetor de resultados atuais, incremente o ponteiro j
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


    //TODO: o vetor de resultados é maior doq realmente precisa, pq o tamanho mudou (intersecção),
    //      mas fazer um realloc pode ser disperdicio de tempo

    // Liberando o vetor antigo de resultados anterioress e retornando o novo
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