#include <stdio.h>
#include "compacta.h" 
#include "descompacta.h" 
#include "infraestrutura.h"
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
  //char * teste = "Rafael Paladini Meirelles e Ricardo Leta(mb n sei o outro sobrenome) sao(americano burro nao usa til ent n tem na ascii) os autores desse trabalho incrivel, lindo e maravilhoso";

  
  FILE * texto = fopen("texto.txt", "r");
  FILE * compactado = fopen("compactado.dat", "wb");
  long size;
  char * teste = le_arquivo(texto);

  //printf("\n%s\n", teste);
  s_node * arvore = arvore_do_zero(teste);
  compacta(teste, compactado, arvore, &size);

  fclose(texto);
  fclose(compactado);

  FILE * comp = fopen("compactado.dat", "rb");
  FILE * txt = fopen("novo.txt", "w");
  descompacta(comp, txt, arvore);
  
  //char tabela[128][128];

  //preenche_tabela(arvore, tabela);
    
  //char * bin = string_para_binaria(teste, tabela);
  //printf("\n%s\n", bin);
  //char * normal = binaria_para_string(bin, arvore);
  //printf("\n %s\n", normal);

  return 0;
}