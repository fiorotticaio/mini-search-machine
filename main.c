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
  char** nomeDocumentos = leNomeDocumentos(argv[1]);
  RBTpal* S = leStopWords(argv[1]);

  /* Debug */
  // char* palBuscada = buscaRBTPal(S, "its");
  // if (palBuscada != NULL) {
  //   printf("Palavra buscada: %s\n", palBuscada);
  // } else {
  //   printf("Palavra buscada não encontrada\n");
  // } 
  

  /*========== Liberação da memória ==========*/
  liberaNomeDocumentos(nomeDocumentos);
  liberaNoRBTpal(S);
  
  return 0;
}