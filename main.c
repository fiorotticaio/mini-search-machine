#include <stdio.h>
#include "documento.h"
#include "RBTpal.h"
#include "RBTdocs.h"
#include "RBTmain.h"

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


  /*========== Leitura dos dados de entrada ==========*/
  int qtdDocs = 0;
  char** nomeDocumentos = leNomeDocumentos(argv[1], &qtdDocs);
  RBTpal* S = leStopWords(argv[1]);
  RBTdocs* documentos = leDocumentos(nomeDocumentos, qtdDocs, argv[1]);
  linkaDocumentos(documentos, argv[1]);


  /*========== Cálculo do page rank ==========*/
  int ultimaPosPageRank = calculaPageRankRBTdocs(documentos, qtdDocs);

  RBTmain* T = NULL;
  criaRBTpesquisa(documentos,  S, argv[1], &T);


  /*========== Debug ==========*/
  //printRBTdocs(documentos, ultimaPosPageRank);
  //printRBTmain(T);


  /*========== Liberação da memória ==========*/
  liberaNomeDocumentos(nomeDocumentos);
  liberaNoRBTpal(S);
  liberaNoRBTdocs(documentos);
  liberaNoRBTmain(T);
  
  return 0;
}