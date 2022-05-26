#include "descompacta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Percorre a árvore segundo o código dado até chegar numa folha e retorna o char correspondente
char codigo_para_char(char * codigo, s_node * raiz, int * profundidade){
  if(!raiz->left_child && !raiz->right_child){
    return raiz->symbol;
  }
  *profundidade += 1;
  if(codigo[0] == '0'){
    codigo++;
    return codigo_para_char(codigo, raiz->left_child, profundidade);
  }
  else{
    codigo++;
    return codigo_para_char(codigo, raiz->right_child, profundidade);
  }
}

// Recebe um vetor de bytes e junta numa string binária 
char * vetor_para_binaria(unsigned char * vetor_de_bytes, long size){
  char * bin = (char *)malloc(MAXSIZE * 256);
  for(int i=0; i < size; i++){
    for(int j=0; j < 8; j++){
      char to_append;
      if(((vetor_de_bytes[i] << j) & 0x80) != 0x80){
        to_append = '0';
      }
      else{
        to_append = '1';
    }
      //printf("%c", to_append);
      strncat(bin, &to_append, 1);
      }
  }
  return bin;
}

// Recebe uma string binária e percorre a mesma substituindo cada código por seu caractere 
char * binaria_para_string(char * string_binaria, s_node * arvore){
  char * str = (char *)malloc(MAXSIZE);
  int percorridos = 0;
   while(*string_binaria){
     char prox = codigo_para_char(string_binaria, arvore, &percorridos);
     if(prox == (char)3){
       break;
     }
     strncat(str, &prox, 1);
     string_binaria += percorridos;
     percorridos = 0;
   }
  return str;
}


unsigned char * arquivo_para_vetor(FILE * arquivo_compactado, long size){
  unsigned char * vetor = (unsigned char*)malloc(size + 1);
  fread(vetor, 1, size, arquivo_compactado);
  return vetor;
}


// Lê o arquivo compactado, transforma o vetor de bytes correspondente numa string normal e grava a string no arquivo texto
void descompacta(FILE * arquivo_compactado, FILE * arquivo_texto, s_node * arvore, long size){
  unsigned char * vetor;
  char * bin;
  char * texto;

  vetor = arquivo_para_vetor(arquivo_compactado, size);
  bin = vetor_para_binaria(vetor, size);
  texto = binaria_para_string(bin, arvore);

  //printf("%s", texto);
  //printf("%s", bin);

  fwrite(texto, 1, strlen(texto), arquivo_texto);
  free(bin);
  free(vetor);
  free(texto);
  
}