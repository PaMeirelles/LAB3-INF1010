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
  char * teste = "Rafael Paladini Meirelles e Ricardo Leta(mb n sei o outro sobrenome) sao(americano burro nao usa til ent n tem na ascii) os autores desse trabalho incrivel, lindo e maravilhoso";
  
  int * frequencias = coleta_frequencia(teste);
  s_node * min_heap = cria_min_heap(frequencias);
  s_node * arvore = cria_arvore(min_heap);
  char tabela[128][128];

  preenche_tabela(arvore, tabela);
  
  char * string = string_para_binaria(teste, tabela);
  printf("%s", string);

  //pa(arvore);
  
  return 0;
}