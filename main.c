#include <stdio.h>
#include "infraestrutura.h"

void print_int_array(int * i_array, int tamanho){
  printf("[ ");
  for(int i=0; i<tamanho;i++){
    printf("%d ", i_array[i]);
  }
  printf("]\n");
}

int main(void){
  char teste[] = "abbcccdddd!***";
  print_int_array(coleta_frequencia(teste), 256);
  
  return 0;
}