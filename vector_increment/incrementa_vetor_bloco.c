/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 2 */
/* Codigo: Incrementa os valores de um vetor usando threads em C */

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include "timer.h"  //para usar funcoes de medida de tempo
#include <unistd.h> //para usar a funcao "sysconf"

//variaveis globais/compartilhadas
//numero de threads e tamanho do vetor
int nthreads, tam;
//vetor de elementos
float *vet;

//funcao executada pelas threads
void *IncrementaVetorBloco (void *tid) {
  int i = * (int *) tid;
  int inicio, fim; //intervalo de elementos processados por cada thread
  int tam_bloco = tam/nthreads;
  inicio = i * tam_bloco;
  //o ultimo fluxo trata os elementos restantes
  if (i<nthreads-1) fim = inicio + tam_bloco; 
  else fim = tam;
  for(i=inicio; i<fim; i++) {
     vet[i]++;
  }
  free(tid);
  pthread_exit(NULL);
}

//funcao principal do programa
int main(int argc, char *argv[]) {
  pthread_t *tid_sistema; //vetor de identificadores das threads no sistema
  int t; //variavel contadora
  int *tid; //identificadores das threads no programa

  double inicio, fim, delta1, delta2, delta3; //variaveis para medir o tempo de execucao
  
  //descobre quantos processadores a maquina possui
  int numCPU = sysconf(_SC_NPROCESSORS_ONLN); 
  printf("Numero de processadores: %d\n", numCPU);

  //-----------------------------------------------------------------------------------
  GET_TIME(inicio);
  
  //valida e recebe os valores de entrada
  if(argc < 3) {
    printf("Use: %s <numero de elementos> <numero de threads>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  tam = atoi(argv[1]); //tamanho do vetor
  nthreads = atoi(argv[2]); //numero de threads

  //limita o numero de threads ao tamanho do vetor
  if(nthreads>tam) nthreads = tam;

  //aloca espaco para o vetor de identificadores das threads no sistema
  tid_sistema = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  if(tid_sistema==NULL) {
      printf("--ERRO: malloc()\n"); exit(-1);
  }

  //aloca espaco de memoria e inicializa o vetor de entrada com valores sequenciais
  vet = malloc (sizeof(float) * tam);
  if(vet==NULL) {
      printf("--ERRO: malloc()\n"); exit(-1);
  }
  for(t=0; t<tam; t++) {
     vet[t] = t;
  }
  GET_TIME(fim);

  //calcula o tempo gasto com as inicializacoes
  delta1 = fim - inicio;

  //-----------------------------------------------------------------------------------
  GET_TIME(inicio);
  //cria as threads
  for(t=0; t<nthreads; t++) {
    tid = malloc(sizeof(int)); if(tid==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
    *tid = t;

    if (pthread_create(&tid_sistema[t], NULL, IncrementaVetorBloco, (void*) tid)) {
       printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }

  //espera todas as threads terminarem e imprime o vetor de saída
  for(t=0; t<nthreads; t++) {
     if (pthread_join(tid_sistema[t], NULL)) {
        printf("--ERRO: pthread_join()\n"); exit(-1);
     }
  }
  GET_TIME(fim);

  //calcula o tempo gasto com a parte concorrente (incremento do vetor)
  delta2 = fim - inicio;

  //-----------------------------------------------------------------------------------
  GET_TIME(inicio);
  //imprime o vetor de saida
  /*   
  for(t=0; t<tam; t++) {
     printf("%.1f ", vet[t]);
  }
  printf("\n");
  */

  //desaloca os espacos de memoria
  free(vet);
  free(tid_sistema);
  GET_TIME(fim);

  //calcula o tempo gasto com as finalizacoes 
  delta3 = fim - inicio;


  //exibe os tempos gastos em cada parte do programa 
  printf("Tempo inicializacoes: %.8lf\n", delta1);
  printf("Tempo incremento vetor com %d threads: %.8lf\n", nthreads, delta2);
  printf("Tempo finalizacoes: %.8lf\n", delta3);

  //printf("--Thread principal terminou\n");
  pthread_exit(NULL);
}
