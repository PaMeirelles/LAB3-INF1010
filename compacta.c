#include "compacta.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Percorre a árvore e preenche uma tabela com os códigos de cada símbolo
void preenche_tabela(s_node * raiz, char tabela[256][256]){
  // Se o nó tem um filho na esquerda, adicionamos um "0" no código dele, pois tomamos o caminho da esquerda para chegar lá, e chamamos a função para o filho esquerdo
  if(raiz->left_child){
    strcpy(raiz->left_child->codigo, raiz->codigo);
    char a[] = "0"; 
    strncat(raiz->left_child->codigo, a, 1);
    preenche_tabela(raiz->left_child, tabela);
  }
  // Da mesma maneira para o filho direito
  if(raiz->right_child){
    strcpy(raiz->right_child->codigo, raiz->codigo);
    char a[] = "1"; 
    strncat(raiz->right_child->codigo, a, 1);
    preenche_tabela(raiz->right_child, tabela);
  }
  // Caso não possua filhos, chegamos numa folha e podemos gravar na tabela o código correspondente a esse símbolo
  if(!raiz->left_child && !raiz->right_child){
    strcpy(tabela[(unsigned char)raiz->symbol], raiz->codigo);
  }
}

// Percorre a string substituindo cada char pelo código correspondente e devolve a string binária que resulta desse processo
char * string_para_binaria(char * string, char tabela[256][256], long * binary_size){
  // Alocamos espaço para a string e criamos um buffer
  char * str = (char *)malloc(MAXSIZE);
  char * buffer = (char*)malloc(256);
  while(*string){
    // Para cada símbolo na string, consultamos a tabela para saber seu código, e copiamos esse código para o buffer
    strcpy(buffer, tabela[(unsigned char)*string]);
    // Adicionamos o conteúdo do buffer nas string binária
    strcat(str, buffer);
    string++;
    // Atualizamos o tamanho da string binária
    *binary_size += strlen(buffer);
  }
  // Liberamos o buffer quando o mesmo não é mais necessário
  free(buffer);
  return str;
}

// Recebe uma string binária, agrupa os zeros e uns 8 a 8 para formar um vetor de bytes e devolve esse vetor
unsigned char * binaria_para_vetor(char * string_binaria, long len)
{
  // Declaramos variáveis para um byte e para o vetor de bytes
  unsigned char byte;
  unsigned char * vetor;

  // Alocamos memória para o vetor
  vetor = (unsigned char *)malloc((len + 7)/8);

  // Para cada grupo de 8 da string binária, executamos o loop
  for(int i=0; i < len; i+=8)
  {
    // Zeramos o byte
    byte = 0;
    for(int j=0; j<8;j++)
    {
      // Caso a string tenha acabado, paramos a repetição
      if(!*string_binaria)
      {
        break;
      }
      // Checamos se o char atual é "0" ou "1" e deslocamos ele a quantia adequada para formar o byte
      byte += (*string_binaria - '0') << (7-j);
      string_binaria++;
    }
    // Inserimos o byte na posição correspondente
    vetor[i/8]=byte;  
  }
  return vetor;
}

// Lê o arquivo texto, transforma a string num vetor de bytes e grava esse vetor no arquivo fornecido
void compacta(char * texto, FILE * compactado, s_node * arvore, long * tam_final){
  // Algumas variáveis úteis
  char tabela[256][256];
  char * bin;
  unsigned char * vetor;
  long binary_size = 0;

  // Chamamos as funções do módulo para executar a rotina mencionada
  preenche_tabela(arvore, tabela);
  bin = string_para_binaria(texto, tabela, &binary_size);
  vetor = binaria_para_vetor(bin, binary_size);
  // Salvamos o tamanho do arquivo compactado
  *tam_final = (binary_size + 7) / 8;
  // Escrevemos no arquivo
  fwrite(vetor, *tam_final, 1, compactado);
  // Liberamos os espaços de memória não mais necessários
  free(bin);
  free(vetor);
}