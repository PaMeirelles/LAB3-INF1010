#include <stdio.h>
#include "infraestrutura.h"
#include "compacta.h" 

int main(void){
  char * teste = "122333444455555";
  int * frequencias = coleta_frequencia(teste);
  s_node * min_heap = cria_min_heap(frequencias);
  cria_arvore(min_heap);
  return 0;
}