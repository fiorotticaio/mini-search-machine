#include <stdio.h>
#include "documento.h"
#include "RBTpal.h"
#include "RBTdocs.h"
#include "RBTmain.h"
#include "TST.h"

int main(int argc, char** argv) {
  /**
   * @brief Significado de cada parâmetro:
   * argv[0] = ./trab3
   * argv[1] = diretório_entrada
  */

  if (argc < 2) {
    printf("Use: ./trab3 <diretório_entrada>\n");
    return 1;
  }

  char * diretorio = argv[1];

  /*========== Leitura dos dados de entrada ==========*/
  int qtdDocs = 0;
  char** nomeDocumentos = leNomeDocumentos(diretorio, &qtdDocs);
  RBTpal* S = leStopWords(diretorio);
  RBTdocs* documentos = leDocumentos(nomeDocumentos, qtdDocs, diretorio);
  linkaDocumentos(documentos, diretorio);

  /*========== Cálculo do page rank final de todas as páginas ==========*/
  calculaPageRankRBTdocs(documentos, qtdDocs);
  
  /*================ Criação da árvore com as possíveis buscas ================*/
  RBTmain* T = NULL;
  criaRBTpesquisa(documentos,  S, diretorio, &T);
  ordenaValuesPorPageRank(&T); // ordenando os documentos em cada busca possível

  TST* Tst = NULL;
  Tst = criaTSTpesquisa(documentos, S, diretorio, Tst);
  Tst = ordenaValuesPorPageRankTST(Tst);

  /*========== Debug ==========*/
  // printRBTdocs(documentos);
  // printRBTmain(T);

  /* =========== Prompt de Buscas ===========  */
  // bool continuaPromp = true;
  // while(continuaPromp) continuaPromp=promptPesquisa(T);

  bool continuaPromp = true;
  while(continuaPromp) continuaPromp=promptPesquisaTST(Tst);

  /*========== Liberação da memória ==========*/
  liberaNomeDocumentos(nomeDocumentos);
  liberaNoRBTpal(S);
  liberaNoRBTdocs(documentos);
  liberaNoRBTmain(T);
  
  return 0;
}