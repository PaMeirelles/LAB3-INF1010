#include "compacta.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Percorre a árvore e devolve uma tabela com os códigos de cada símbolo
void preenche_tabela(s_node * raiz, char tabela[256][256]){
  if(raiz->left_child){
    strcpy(raiz->left_child->codigo, raiz->codigo);
    char a[] = "0"; 
    strncat(raiz->left_child->codigo, a, 1);
    preenche_tabela(raiz->left_child, tabela);
  }
  if(raiz->right_child){
    strcpy(raiz->right_child->codigo, raiz->codigo);
    char a[] = "1"; 
    strncat(raiz->right_child->codigo, a, 1);
    preenche_tabela(raiz->right_child, tabela);
  }
  if(!raiz->left_child && !raiz->right_child){
    strcpy(tabela[(unsigned char)raiz->symbol], raiz->codigo);
    //printf("Posição %d(%c) possui %s\n", raiz->symbol, raiz->symbol, tabela[raiz->symbol]);
  }
}

// Percorre a string substituindo cada char pelo código correspondente e devolve a string binária que resulta desse processo
char * string_para_binaria(char * string, char tabela[256][256], long * binary_size){
  char * str = (char *)malloc(MAXSIZE);
  char * buffer = (char*)malloc(256);
  while(*string){
    strcpy(buffer, tabela[(unsigned char)*string]);
    strcat(str, buffer);
    //printf("%c: %s\n", *string, tabela[*string]);
    string++;
    *binary_size += strlen(buffer);
  }

  return str;
}

// Recebe uma string binária, agrupa os zeros e uns 8 a 8 para formar um vetor de bytes e devolve esse vetor
unsigned char * binaria_para_vetor(char * string_binaria, long len)
{
  unsigned char byte;
  unsigned char * vetor;

  vetor = (unsigned char *)malloc((len + 7)/8);

  for(int i=0; i < len; i+=8)
  {
    byte = 0;
    for(int j=0; j<8;j++)
    {
      if(!*string_binaria)
      {
        break;
      }
      byte += (*string_binaria - '0') << (7-j);
      string_binaria++;
    }
    vetor[i/8]=byte;  
    //printf("%x %d\n", byte, i);
  }
  return vetor;
}

// Lê o arquivo texto, transforma a string num vetor de bytes e grava esse vetor no arquivo fornecido
char * le_arquivo(FILE * arquivo_texto)
{
  long lSize;
  char *vetor_arq_str;

  // Mede o número de chars no arquivo
  fseek(arquivo_texto , 0L , SEEK_END);
  lSize = ftell(arquivo_texto);
  rewind(arquivo_texto);
  
  /* aloca memória para todo o conteúdo do texto*/
  vetor_arq_str = (char *) malloc(lSize+1);

  // checa se a alocação de memória funcionou
  if(!vetor_arq_str) 
  {
    fclose(arquivo_texto);
    fputs("memory alloc fails",stderr);
    exit(1);
  }
  
  /* copia arquivo para o vetor usando fread*/
  if( 1 != fread(vetor_arq_str , lSize, 1 , arquivo_texto))
  {
    free(vetor_arq_str);
    fputs("entire read fails",stderr);
    exit(1);
  }
  return vetor_arq_str;
}


void compacta(char * texto, FILE * compactado, s_node * arvore, long * tam_final){
  char tabela[256][256];
  char * bin;
  unsigned char * vetor;
  long binary_size = 0;
  
  preenche_tabela(arvore, tabela);
  bin = string_para_binaria(texto, tabela, &binary_size);
  vetor = binaria_para_vetor(bin, binary_size);
  *tam_final = (binary_size + 7) / 8;
  fwrite(vetor, *tam_final, 1, compactado);
}