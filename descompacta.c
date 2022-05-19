#include "descompacta.h"

// Percorre a árvore segundo o código dado até chegar numa folha e retorna o char correspondente
char * char_para_simbolo(char * codigo, s_node * raiz, int * profundidade){
  if(!raiz->left_child && !raiz->right_child){
    return raiz->symbol;
  }
  *profundidade++;
  if(codigo[0] == '0'){
    codigo++;
    return char_para_simbolo(codigo, raiz->left_child, profundidade);
  }
  else{
    codigo++;
    return char_para_simbolo(codigo, raiz->right_child, profundidade);
  }
}

// Recebe um vetor de bytes e junta numa string binária 
char * vetor_para_binaria(unsigned char * vetor_de_bytes);

// Recebe uma string binária e percorre a mesma substituindo cada código por seu caractere 
char * binaria_para_string(char * string binaria);

// Lê o arquivo compactado, transforma o vetor de bytes correspondente numa string normal e grava a string no arquivo texto
void descompacta(FILE * arquivo_compactado, FILE * arquivo_texto);