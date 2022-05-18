#include "infraestrutura.h"
#include <stdlib.h>
#include <stdio.h>
// Recebe um vetor de char com a amostra e devolve um vetor de char indexado pelo código ASCII com a frequência daquele char na amostra
int * coleta_frequencia(char * amostra){
  int * vetor_de_frequencias = (int *)malloc(128 * 4);

  for(int i=0; i<128;i++){
    vetor_de_frequencias[i] = 0;
  }
  
  while(*amostra){
    vetor_de_frequencias[*amostra]++;
    amostra++;
  }
  return vetor_de_frequencias;
}

// Estrutura para o nó da árvore
typedef struct node{
 int value;
 char symbol;
 struct node * left_child;
 struct node * right_child;
}s_node;

// Sobe nó na min heap até a sua posição correta
void sobe_no_mh(s_node heap[], int i){
  int j;
  s_node aux;
  j = (i - 1) / 2;
  if (j >= 0){
    if (heap[i].value > heap[j].value) {
    aux = heap[i];
    heap[i] = heap[j];
    heap[j] = aux;
    sobe_no_mh(heap, j);
    }
  }
}

// Recebe um nó e insere na min heap
void insere_no_mh(s_node heap[], s_node no, int tam){
  heap[tam] = no;
  sobe_no_mh(heap, tam);
}

// Recebe o vetor de frequências e devolve a raiz do min heap correspondente
s_node * cria_min_heap(int * frequencias){
  s_node * min_heap = (s_node *)malloc(128 * sizeof(s_node));
  for(int i=0; i<128; i++){
    s_node no = {.value = frequencias[i], .symbol=(char)i};
    insere_no_mh(min_heap, no, i);
  }
  for(int i =0; i<128; i++){
  }
  return min_heap;
}

// Recebe o vetor de frequencias e devolve a raiz da árvore de huffman correspondente
s_node * cria_arvore(char * frequencias);





