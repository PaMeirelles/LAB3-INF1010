#ifndef SOME_HEADER_GUARD_WITH_UNIQUE_NAME
#define SOME_HEADER_GUARD_WITH_UNIQUE_NAME
typedef struct node
{
 int value;
 char symbol;
 struct node * left_child;
 struct node * right_child;
 char codigo[128];
} s_node;
#endif
#include <stdio.h>
#define MAXSIZE 10000
int * coleta_frequencia(char * amostra);
s_node * cria_min_heap(int * frequencias);
s_node * cria_arvore(s_node * min_heap);
void printa_heap(s_node * heap);

void swap(int *a, int *b);
int partition(int array[], int low, int high);
void quickSort(int array[], int low, int high);
s_node * arvore_do_zero(char * texto);