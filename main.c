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
  char * teste = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabfbseiofsefkw=-ero3-r-ror=";
  //printf("%s", string_para_binaria(teste));

  //pa(arvore);
  
  return 0;
}