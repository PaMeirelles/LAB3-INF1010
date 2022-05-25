#include "infraestrutura.h"
char codigo_para_char(char * codigo, s_node * raiz, int * profundidade);
char * binaria_para_string(char * string_binaria, s_node * arvore);
unsigned char * arquivo_para_vetor(FILE * arquivo_compactado);
void descompacta(FILE * arquivo_compactado, FILE * arquivo_texto);