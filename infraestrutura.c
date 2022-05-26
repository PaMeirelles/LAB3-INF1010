#include "infraestrutura.h"
#include <stdlib.h>
#include <stdio.h>

// Recebe um vetor de char com a amostra e devolve um vetor de char indexado pelo código ASCII com a frequência daquele char na amostra
int * coleta_frequencia(char * amostra)
{
  int * vetor_de_frequencias = (int *)malloc(256 * 4);

  for(int i=0; i<256;i++)
  {
    vetor_de_frequencias[i] = 0;
  }
  
  while(*amostra)
  {
    vetor_de_frequencias[(unsigned char)*amostra]++;
    amostra++;
  }
  
  return vetor_de_frequencias;
}

// Sobe nó na min heap até a sua posição correta
void sobe_no_mh(s_node heap[], int i)
{
  int j;
  s_node aux;
 
  j = (i - 1) / 2;
  
  if (j >= 0)
  {
    if (heap[i].value < heap[j].value)
    {
      aux = heap[i];
      heap[i] = heap[j];
      heap[j] = aux;
      sobe_no_mh(heap, j);
    }
  }
}

// Recebe um nó e insere na min heap
void insere_no_mh(s_node heap[], s_node no, int tam)
{
  heap[tam] = no;
  sobe_no_mh(heap, tam);
}

// Recebe o vetor de frequências e devolve a raiz do min heap correspondente
s_node * cria_min_heap(int * frequencias)
{
  s_node * min_heap = (s_node *)malloc(256 * sizeof(s_node));
  
  for(int i=0; i<256; i++)
  {
    s_node no = {.value = frequencias[i], .symbol=(char)i, .left_child=NULL, .right_child=NULL};
    insere_no_mh(min_heap, no, i);
  }
  /*
  for(int i =0; i<256; i++){
    printf("%c %d\n", min_heap[i].symbol,  min_heap[i].value);
  }*/
  
  return min_heap;
}


// Desce nó na min heap até a sua posição correta
void desce_no_mh(s_node heap[], int i, int tam)
{
  int j;
  s_node aux;
  j = (2 * i) + 1;
  
  if (j <= tam) 
  {
    if (j < tam)
    {
      if (heap[j + 1].value < heap[j].value)
      {
        j++;
      }
      if (heap[i].value > heap[j].value) 
      {
        aux = heap[i];
        heap[i] = heap[j];
        heap[j] = aux;
        desce_no_mh(heap, j, tam);
      }
    }
  }

}

// Remove raiz do heap
void remove_no_mh(s_node heap[], int tam)
{
  heap[0] = heap[tam - 1];
  tam--;
  desce_no_mh(heap, 0, tam);
}

void printa_arvore(s_node * raiz)
{
  if(!raiz)
  {
    printf("NULL\n");
  }
  else
  {
    if(!raiz->left_child && !raiz->right_child)
    {
      printf("%c %d\n", raiz->symbol, raiz->value);
    }
    else
    {
      printf("Intermediário %d\n", raiz->value);
    }
    
    printa_arvore(raiz->left_child);
    printa_arvore(raiz->right_child);
  }
}

// Recebe o vetor de frequencias e devolve a raiz da árvore de huffman correspondente
s_node * cria_arvore(s_node * min_heap)
{
  int tam_heap = 256;
  
  while(tam_heap > 1)
  {
    s_node * menor = (s_node *)malloc(sizeof(s_node));
    s_node * segundo_menor = (s_node *)malloc(sizeof(s_node));
    s_node * no_interno = (s_node *)malloc(sizeof(s_node));
    
    *menor = min_heap[0];
    remove_no_mh(min_heap, tam_heap);
    tam_heap--;
    
    *segundo_menor = min_heap[0];
    remove_no_mh(min_heap, tam_heap);
    tam_heap--;
    
    no_interno->value = menor->value + segundo_menor->value;
    no_interno->left_child = menor;
    no_interno->right_child = segundo_menor;
    

    insere_no_mh(min_heap, *no_interno, tam_heap);
    tam_heap++;

  }
  
  //printa_arvore(min_heap);
 
  return min_heap;
}


void printa_heap(s_node * min_heap){
  for(int i=0; i<256;i++){
    printf("%d Simbolo: %c, Valor: %d\n", i, min_heap[i].symbol, min_heap[i].value);
  }
}

// troca elementos
void swap(int *a, int *b) 
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// function to find the partition position
int partition(int array[], int low, int high) 
{
  // seleciona o elemento mais a direita como pivot
  int pivot = array[high];
  
  // ponteiro para maior elemento
  int i = (low - 1);

  // percorre cada elemento do array e compara com o pivot
  for (int j = low; j < high; j++) 
  {
    if (array[j] <= pivot) 
    {
      // se um elemento menor que o pivot for encontrado
      // troca ele com o maior elemento (i)
      i++;
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  // troca o elemento pivot com o maior elemento (i)
  swap(&array[i + 1], &array[high]);
  
  // retorna o ponto de partição
  return (i + 1);
}

void quickSort(int array[], int low, int high) 
{
  if (low < high) 
  {
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot

    // encotra o pivot tal que os elementos menores que ele estão na esquerda
    // e os maiores estão na direita
    int pivot = partition(array, low, high);
    
    // recurção para a esquerda do pivot
    quickSort(array, low, pivot - 1);
    
    // recurção para a direita do pivot
    quickSort(array, pivot + 1, high);
  }
  }

s_node * arvore_do_zero(char * texto){
  int * frequencias = coleta_frequencia(texto);
  s_node * min_heap = cria_min_heap(frequencias);
  s_node * arvore = cria_arvore(min_heap);

  free(frequencias);
  free(min_heap);
  return arvore;
}