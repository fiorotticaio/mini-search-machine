#include <stdio.h>
#include "documento.h"
#include "RBTpal.h"
#include "RBTdocs.h"

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

  /*========== Debug ==========*/
  printRBTdocs(documentos);

  /*========== Liberação da memória ==========*/
  liberaNomeDocumentos(nomeDocumentos);
  liberaNoRBTpal(S);
  liberaNoRBTdocs(documentos);
  
  return 0;
}