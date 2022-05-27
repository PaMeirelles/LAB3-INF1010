#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compacta.h" 
#include "descompacta.h" 
#include "infraestrutura.h"


int main(void)
{
  FILE * texto = fopen("poema_certo.txt", "r");
  FILE * compactado = fopen("compactado.dat", "wb");
  long size;
  char * teste = le_arquivo(texto);

  s_node * arvore = arvore_do_zero(teste);
  compacta(teste, compactado, arvore, &size);

  fclose(texto);
  fclose(compactado);

  FILE * comp = fopen("compactado.dat", "rb");
  FILE * txt = fopen("novo.txt", "w");
  descompacta(comp, txt, arvore, size);
  
  fclose(comp);
  fclose(txt);
  free(teste);
  libera_arvore(arvore);

  return 0;
}