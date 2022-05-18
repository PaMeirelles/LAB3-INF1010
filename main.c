#include <stdio.h>
#include "compacta.h" 


void pa(s_node * raiz)
{
  if(raiz->left_child)
  {
    pa(raiz->left_child);
  }
  if(raiz->right_child){
    pa(raiz->right_child);
  }
  if(!raiz->right_child && !raiz->left_child)
  {
    printf("Símbolo: %c Código: %s Valor: %d\n", raiz->symbol, raiz->codigo, raiz->value);
  }


}

int main(void)
{
  char * teste = "abcdefghijklmnopqrstuvwxyzAABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWXXYYZZ!!!@@@###$$$%%%¨¨¨&&&***((()))";
  int * frequencias = coleta_frequencia(teste);
  s_node * min_heap = cria_min_heap(frequencias);

  s_node * arvore = cria_arvore(min_heap);
  char tabela[128][128];

  preenche_tabela(arvore, tabela);

  //pa(arvore);
  
  return 0;
}