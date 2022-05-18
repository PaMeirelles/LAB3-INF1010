#include "compacta.h"
#include "infraestrutura.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Percorre a árvore e devolve o código correspondente ao simbolo fornecido
char * simbolo_para_codigo(char simbolo, s_node * raiz);
// Percorre a string substituindo cada char pelo código correspondente e devolve a string binária que resulta desse processo
char * string_para_binaria(char * string);
// Recebe uma string binária, agrupa os zeros e uns 8 a 8 para formar um vetor de bytes e devolve esse vetor
unsigned char * binaria_para_vetor(char * string_binaria){
  unsigned char byte;
  int len = strlen(string_binaria);
  unsigned char * vetor;
  if(len/8 == 0){
    vetor = (unsigned char *)malloc(len/8);
  }
  else{
    vetor = (unsigned char *)malloc(len/8 + 1);
  }
  while(len > 0){
    byte = 0;
    for(int i=0; i<8;i++){
      if(!*string_binaria){
        break;
      }
      byte += (*string_binaria - '0') << (7-i);
      string_binaria++;
    }
    *vetor=byte;  
    vetor++;
    len -= 8;
  }
}

// Lê o arquivo texto, transforma a string num vetor de bytes e grava esse vetor no arquivo fornecido
void * compacta(FILE * arquivo_texto, FILE * arquivo_compactado);