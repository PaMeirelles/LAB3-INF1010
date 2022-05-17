// Percorre a árvore e devolve o código correspondente ao simbolo fornecido
char * simbolo_para_codigo(char simbolo, s_node * raiz)
// Percorre a string substituindo cada char pelo código correspondente e devolve a string binária que resulta desse processo
char * string_para_binaria(char * string)
// Recebe uma string binária, agrupa os zeros e uns 8 a 8 para formar um vetor de bytes e devolve esse vetor
unsigned char * binaria_para_vetor(char * string_binaria)

// Lê o arquivo texto, transforma a string num vetor de bytes e grava esse vetor no arquivo fornecido
void * compacta(FILE * arquivo_texto, FILE * arquivo_compactado)