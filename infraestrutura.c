#include "infraestrutura.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Recebe um vetor de char com a amostra e devolve um vetor de char indexado pelo código ASCII com a frequência daquele char na amostra
int * coleta_frequencia(char * amostra){
  /*
   alocamos espaço para o vetor que guardará as frequências
   A tabela ASCII expandida contém 256 caracteres, que é também o tamanho do nosso vetor. O valor numa posição i qualquer representa a frequência do caractere com código ASCII i no texto. É uma maneira elegante de substituir um dicionário
  */
  int * vetor_de_frequencias = (int *)malloc(256 * 4);

  // Inicializamos cada frequência como 0
  for(int i=0; i<256;i++)
  {
    vetor_de_frequencias[i] = 0;
  }
  
  while(*amostra)
  {
    // Para cada caractere na amostra, incrementamos a frequência dele
    vetor_de_frequencias[(unsigned char)*amostra]++;
    amostra++;
  }
  
  return vetor_de_frequencias;
}

// Sobe nó na min heap até a sua posição correta
void sobe_no_mh(s_node * heap[], int i)
{
  // Variáveis úteis
  int j;
  s_node * aux;

  // j é o "pai" de i
  j = (i - 1) / 2;

  // É importante garantir que j está dentro do vetor
  if (j >= 0)
  {
    // Se j for maior que i, é necessário inverter suas posições, para que o menor elemento fique em cima
    if (heap[i]->value < heap[j]->value)
    {
      // Usamos a estrutura auxiliar para fazer essa troca
      aux = heap[i];
      heap[i] = heap[j];
      heap[j] = aux;
      // Chamamos a função recursivamente para subir o nó até onde seja necessário
      sobe_no_mh(heap, j);
    }
  }
}

// Recebe um nó e insere na min heap
void insere_no_mh(s_node * heap[], s_node * no, int tam)
{
  // Colocamos o nó no fim do vetor e subimos o mesmo até onde seja necessário
  heap[tam] = no;
  sobe_no_mh(heap, tam);
}

// Recebe o vetor de frequências e devolve a raiz do min heap correspondente
s_node ** cria_min_heap(int * frequencias)
{
  /* A decisão de usar a heap para guardar os ponteiros invés das estruturas em si facilita a prevenção de memory leaks */
  // Alocamos espaço para a nossa heap
  s_node ** min_heap = malloc(256 * sizeof(s_node *));

  for(int i=0; i<256; i++)
  {
    // Alocamos espaço para um nó. Posteriormente, usaremos os mesmos nós para criar a árvore 
    s_node * no = malloc(sizeof(s_node));
    // Preenchemos o nó com os valores adequados
    no->value = frequencias[i] ;
    no->symbol=(char)i;
    no->left_child=NULL;
    no->right_child=NULL;
    // Inserimos na heap
    insere_no_mh(min_heap, no, i);
  }
  return min_heap;
}


// Desce nó na min heap até a sua posição correta
void desce_no_mh(s_node * heap[], int i, int tam)
{
  // Variáveis úteis
  int j;
  s_node * aux;
  // j é o "filho" de i
  j = (2 * i) + 1;

  // Garantimos que j está contido no array
    if (j < tam)
    {
    // i tem dois filhos. É interessante que j seja o menor deles
      if (heap[j + 1]->value < heap[j]->value)
      {
        j++;
      }
      // Se o pai é maior que o filho, devemos trocá-los
      if (heap[i]->value > heap[j]->value) 
      {
        // Usaremos o elemento auxiliar para isso
        aux = heap[i];
        heap[i] = heap[j];
        heap[j] = aux;
        // Chamamos a função recursivamente, para descer até onde seja necessário
        desce_no_mh(heap, j, tam);
      }
    }
}

// Remove raiz do heap
void remove_no_mh(s_node * heap[], int tam)
{
  // Movemos o último elemento para a raiz
  heap[0] = heap[tam - 1];
  // Atualizamos o tamanho
  tam--;
  // Descemos até que a min heap esteja correta novamente
  desce_no_mh(heap, 0, tam);
}

// Recebe o vetor de frequencias e devolve a raiz da árvore de huffman correspondente
s_node * cria_arvore(s_node ** min_heap)
{
  // Tamanho inicial da heap
  int tam_heap = 256;
  // Enquanto houver mais de um elemento, retiraremos da heap para inserir na árvore
  while(tam_heap > 1)
  {
    // Variáveis úteis
    s_node * menor;
    s_node * segundo_menor;
    s_node * no_interno;

    // Extraímos primeiro e o segundo nó com maior frequência
    menor = min_heap[0];
    remove_no_mh(min_heap, tam_heap);
    tam_heap--;

    segundo_menor = min_heap[0];
    remove_no_mh(min_heap, tam_heap);
    
    tam_heap--;
    // Alocamos espaço para um novo nó intermediáro, que possui os dois menores como seu filho e a frequência como a soma deles
    no_interno = malloc(sizeof(s_node));
    no_interno->value = menor->value + segundo_menor->value;
    no_interno->left_child = menor;
    no_interno->right_child = segundo_menor;
    // Inserimos esse novo nó na heap
    insere_no_mh(min_heap, no_interno, tam_heap);
    tam_heap++;
  }
  return *min_heap;
}

// Função auxiliar usada para debug
void printa_heap(s_node ** min_heap){
  for(int i=0; i<256;i++){
    printf("%d Simbolo: %c, Valor: %d\n", i, min_heap[i]->symbol, min_heap[i]->value);
  }
}

// troca elementos
void swap(int *a, int *b) 
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// function to find the partition position
int partition(int array[], int low, int high) 
{
  // seleciona o elemento mais a direita como pivot
  int pivot = array[high];
  
  // ponteiro para maior elemento
  int i = (low - 1);

  // percorre cada elemento do array e compara com o pivot
  for (int j = low; j < high; j++) 
  {
    if (array[j] <= pivot) 
    {
      // se um elemento menor que o pivot for encontrado
      // troca ele com o maior elemento (i)
      i++;
      swap(&array[i], &array[j]);
    }
  }

  // swap the pivot element with the greater element at i
  // troca o elemento pivot com o maior elemento (i)
  swap(&array[i + 1], &array[high]);
  
  // retorna o ponto de partição
  return (i + 1);
}

void quickSort(int array[], int low, int high) 
{
  if (low < high) 
  {
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot

    // encotra o pivot tal que os elementos menores que ele estão na esquerda
    // e os maiores estão na direita
    int pivot = partition(array, low, high);
    
    // recurção para a esquerda do pivot
    quickSort(array, low, pivot - 1);
    
    // recurção para a direita do pivot
    quickSort(array, pivot + 1, high);
  }
  }

// Cria a arvore de Huffman
s_node * arvore_de_huffman(char * texto){
  // Usamos as funções do módulo para criar a árvore
  int * frequencias = coleta_frequencia(texto);
  s_node ** min_heap = cria_min_heap(frequencias);
  s_node * arvore = cria_arvore(min_heap);
  // Liberamos os espaços de memória não mais necessários
  free(frequencias);
  free(min_heap);
  return arvore;
}

// Libera memória da árvore
void libera_arvore(s_node * raiz){
  if(!raiz){
    return;
  }
  libera_arvore(raiz->left_child);
  libera_arvore(raiz->right_child);
  free(raiz);
}

// Função auxiliar usada para debugging
void printa_arvore(s_node * raiz)
{
  if(raiz->left_child)
  {
    printa_arvore(raiz->left_child);
  }
  if(raiz->right_child){
    printa_arvore(raiz->right_child);
  }
  if(!raiz->right_child && !raiz->left_child)
  {
    printf("Símbolo: %c Código: %s Valor: %d\n", raiz->symbol, raiz->codigo, raiz->value);
  }


}

// Extrai string de um arquivo de texto
char * le_arquivo(FILE * arquivo_texto)
{
  long lSize;
  char *vetor_arq_str;

  // Mede o número de chars no arquivo
  fseek(arquivo_texto , 0L , SEEK_END);
  lSize = ftell(arquivo_texto);
  rewind(arquivo_texto);
  
  /* aloca memória para todo o conteúdo do texto*/
  vetor_arq_str = (char *) malloc(lSize+2);

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
  char fim = 3;
  strncat(vetor_arq_str, &fim, 1);
  return vetor_arq_str;
}
