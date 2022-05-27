#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compacta.h" 
#include "descompacta.h" 
#include "infraestrutura.h"


int main(void)
{
  // Abrimos o arquivo a ser lido e criamos um para receber a versão compactada
  FILE * texto = fopen("texto.txt", "r");
  FILE * compactado = fopen("compactado.dat", "wb");

  // Lemos o arquivo fonte e extraímos a string correspondente
  char * mensagem = le_arquivo(texto);

  // Variáveis que guardarão a árvore e o tamanho do arquivo compactado. Em usos práticos, seria necessário enviar ambos para quem fosse descompactar o arquivo
  long size;
  s_node * arvore = arvore_de_huffman(mensagem);

  // Compactamos o arquivo
  compacta(mensagem, compactado, arvore, &size);

  // Fechamos os arquivos
  fclose(texto);
  fclose(compactado);

  // Importante liberar a memória ocupada pela string quando ela não for mais necessária
  free(mensagem);
  // --------------------------------------
  // Agora,para descompactar, abrimos os arquivos relevantes
  FILE * comp = fopen("compactado.dat", "rb");
  FILE * txt = fopen("novo.txt", "w");
  // Descompactamos
  descompacta(comp, txt, arvore, size);
  // Fechamos os arquivos
  fclose(comp);
  fclose(txt);
  // Importante liberar a memória alocada pela árvore quando ela não for mais necessária
  libera_arvore(arvore);

  return 0;
}