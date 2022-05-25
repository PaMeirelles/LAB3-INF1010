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
char * vetor_para_binaria(unsigned char * vetor_de_bytes){
  char * bin = (char *)malloc(10000);
  while(*vetor_de_bytes){
    for(int i=0; i < 8; i++){
      char to_append;
      if(((*vetor_de_bytes << i) & 0x80) != 0x80){
        to_append = '0';
      }
      else{
        to_append = '1';
    }
      //printf("%c", to_append);
      strncat(bin, &to_append, 1);
      }
    vetor_de_bytes++;
  }
  return bin;
}

// Recebe uma string binária e percorre a mesma substituindo cada código por seu caractere 
char * binaria_para_string(char * string_binaria, s_node * arvore){
  char * str = (char *)malloc(10000);
  int percorridos = 0;
   while(*string_binaria){
     char prox = codigo_para_char(string_binaria, arvore, &percorridos);
     strncat(str, &prox, 1);
     string_binaria += percorridos;
     percorridos = 0;
   }
  return str;
}


unsigned char * arquivo_para_vetor(FILE * arquivo_compactado){
  unsigned char * vetor = (unsigned char*)malloc(10000);
    fread(vetor, 1, 748, arquivo_compactado);
  return vetor;
}

// Lê o arquivo compactado, transforma o vetor de bytes correspondente numa string normal e grava a string no arquivo texto
void descompacta(FILE * arquivo_compactado, FILE * arquivo_texto, s_node * arvore){
  unsigned char * vetor;
  char * bin;
  char * texto;

  vetor = arquivo_para_vetor(arquivo_compactado);
  bin = vetor_para_binaria(vetor);
  texto = binaria_para_string(bin, arvore);

  printf("%s", texto);
  //printf("%s", bin);
  
}