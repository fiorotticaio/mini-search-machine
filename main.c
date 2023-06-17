#include <stdio.h>
#include "documento.h"
#include "RBTpal.h"

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
  Doc** documentos = leDocumentos(nomeDocumentos, qtdDocs, argv[1]);

  // for (int i = 0; documentos[i] != NULL; i++) {
  //   printf("%s\n", getNomeDocumento(documentos[i]));
  //   printf("%Lf\n", getPageRankDocumento(documentos[i]));
  // }
  

  /*========== Liberação da memória ==========*/
  liberaNomeDocumentos(nomeDocumentos);
  liberaNoRBTpal(S);
  liberaDocumentos(documentos);
  
  return 0;
}