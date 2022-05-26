#include "infraestrutura.h"
#include <stdio.h>
unsigned char * binaria_para_vetor(char * string_binaria, long len);
void preenche_tabela(s_node * raiz, char tabela[256][256]);
char * string_para_binaria(char * string, char tabela[256][256], long * binary_size);
char * le_arquivo(FILE * arquivo_texto);
void compacta(char * texto, FILE * compactado, s_node * arvore, long * tam_final);