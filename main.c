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
  calculaPageRankRBTdocs(documentos, qtdDocs);

  /*================ Criação da árvore com as palavras ================*/
  RBTmain* T = NULL;
  criaRBTpesquisa(documentos,  S, argv[1], &T);
  ordenaValuesPorPageRank(&T);


  /*========== Debug ==========*/
  printRBTdocs(documentos);
  printRBTmain(T);
  
  /*========= Testes de Pesquisa ============*/
  // SÓ FUNCIONAM PARA O EXEMPLO 0 (É SÓ PRA TESTAR MESMO)

  printf("\n\nTESTANDO PESQUISA:\n\n buscando abacate\n");
  
  Doc** ex1 = buscaRBTmain(T, "aBaCaTe");
  printf("%s: %Lf\n", getNomeDocumento(ex1[0]), getLastPageRankDocumento(ex1[0]));   //pegando o primeiro documento só pra testar.
  
  printf("\n Buscando maca\n");

  Doc** ex2 = buscaRBTmain(T, "Maca");
  printf("%s: %Lf\n", getNomeDocumento(ex2[0]), getLastPageRankDocumento(ex2[0]));




  /*========== Liberação da memória ==========*/
  liberaNomeDocumentos(nomeDocumentos);
  liberaNoRBTpal(S);
  liberaNoRBTdocs(documentos);
  liberaNoRBTmain(T);
  
  return 0;
}