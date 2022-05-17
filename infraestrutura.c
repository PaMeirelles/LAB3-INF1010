#include "infraestrutura.h"
#include <stdlib.h>
#include <stdio.h>
// Recebe um vetor de char com a amostra e devolve um vetor de char indexado pelo código ASCII com a frequência daquele char na amostra
int * coleta_frequencia(char * amostra){
  int * vetor_de_frequencias = (int *)malloc(256 * 4);

  for(int i=0; i<256;i++){
    vetor_de_frequencias[i] = 0;
  }
  
  while(*amostra){
    vetor_de_frequencias[*amostra]++;
    amostra++;
  }
  return vetor_de_frequencias;
}

// Estrutura para o nó da árvore
struct node{
 int value;
 char symbol;
 struct node * left_child;
 struct node * right_child;
} typedef s_node;

// Recebe o vetor de frequencias e devolve a raiz para o nó correspondente 
s_node * cria_arvore(char * frequencias);





