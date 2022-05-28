#include "descompacta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Percorre a árvore segundo o código dado até chegar numa folha e retorna o char correspondente
char codigo_para_char(char * codigo, s_node * raiz, int * profundidade){
  // Se chegamos numa folha, retornamos o símbolo
  if(!raiz->left_child && !raiz->right_child){
    return raiz->symbol;
  }
  // Atualizamos a profundidade. Isso será necessário posteriormente para incrementar o ponteiro até o próximo caractere
  *profundidade += 1;
  // Se o char atual do código é 0, tomamos o caminho da esquerda
  if(codigo[0] == '0'){
    codigo++;
    return codigo_para_char(codigo, raiz->left_child, profundidade);
  }
  // Senão, tomamos o caminho da direita
  else{
    codigo++;
    return codigo_para_char(codigo, raiz->right_child, profundidade);
  }
}

// Recebe um vetor de bytes e junta numa string binária 
char * vetor_para_binaria(unsigned char * vetor_de_bytes, long size){
  // Alocamos espaço suficiente para nossa string binária e criamos um buffer
  char * bin = (char *)malloc(MAXSIZE * 256);
  char to_append;
  // Para cada byte no vetor
  for(int i=0; i < size; i++){
    // Para cada bit no byte
    for(int j=0; j < 8; j++){
      // Se nosso bit é igual a 0, nosso buffer vale '0'
      if(((vetor_de_bytes[i] << j) & 0x80) != 0x80){
        to_append = '0';
      }
      // Senão, vale '1'
      else{
        to_append = '1';
    }
      // Adicionamos o buffer à string
      strncat(bin, &to_append, 1);
      }
  }
  return bin;
}

// Recebe uma string binária e percorre a mesma substituindo cada código por seu caractere 
char * binaria_para_string(char * string_binaria, s_node * arvore){
  // Alocamos espaço para a string, criamos um buffer para o tamanho do código e para o símbolo
  char * str = (char *)malloc(MAXSIZE);
  str[0] = '\0';
  int percorridos = 0;
  char prox;
  
   while(*string_binaria){
     // O buffer recebe o valor correspondente a seu código
     prox = codigo_para_char(string_binaria, arvore, &percorridos);
     // Se trata-se de um caractere de fim de texto, paramos o loop
     if(prox == (char)3){
       break;
     }
     // Adicionamos o buffer à string
     strncat(str, &prox, 1);
     // Incrementamos o ponteiro de acordo e zeramos o buffer
     string_binaria += percorridos;
     percorridos = 0;
   }
  return str;
}

// Lê o arquivo compactado e escreve ele num vetor de bytes
unsigned char * arquivo_para_vetor(FILE * arquivo_compactado, long size){
  unsigned char * vetor = (unsigned char*)malloc(size + 1);
  fread(vetor, 1, size, arquivo_compactado);
  return vetor;
}


// Lê o arquivo compactado, transforma o vetor de bytes correspondente numa string normal e grava a string no arquivo texto
void descompacta(FILE * arquivo_compactado, FILE * arquivo_texto, s_node * arvore, long size){
  // Variáveis úteis
  unsigned char * vetor;
  char * bin;
  char * texto;

  // Usamos as funções do módulo para executar a rotina mencionada
  vetor = arquivo_para_vetor(arquivo_compactado, size);
  bin = vetor_para_binaria(vetor, size);
  texto = binaria_para_string(bin, arvore);
  // Escrevemos no arquivo
  fwrite(texto, 1, strlen(texto), arquivo_texto);
  // Liberamos as áreas não mais necessárias
  free(vetor);
  free(bin);
  free(texto);
}