/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 2 */
/* Codigo: Multiplica uma matriz por outra */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"  //para usar funcoes de medida de tempo
#include <unistd.h> //para usar a funcao "sysconf"

//variaveis globais
//variaveis de controle de tempo

int nthreads;
float *vet;

float *matA; //matriz de entrada
float *matX; //vetor de entrada
float *matB; //vetor de saida
int linhas, colunas; //dimensoes da matriz de entrada
int linhas2, colunas2;

void* multiplicaMatrizMatriz(void* id) {
  int tid = *(int *) id;
  int k, j, i;
  int aux = 0;
   for (i=tid; i<linhas; i+=nthreads) {
      for(k=0; k<colunas2;k++){
        for (j=0; j<colunas; j++) {
           matB[i*linhas +k] += matA[i*colunas+j] * matX[j*linhas2+k];
        }
      }
   }
}

//funcao que aloca espaco para uma matriz e preenche seus valores
//entrada: matriz de entrada, dimensoes da matriz
//saida: retorna 1 se a matriz foi preenchida com sucesso e 0 caso contrario
int preencheMatriz(float **mat, int linhas, int colunas, FILE *arq) {
   int i, j;
   //aloca espaco de memoria para a matriz
   *mat = (float*) malloc(sizeof(float) * linhas * colunas);
   if (mat == NULL) return 0;
   //preenche o vetor
   for (i=0; i<linhas; i++) {
      for (j=0; j<colunas; j++) {
         //fscanf(arq, "%f", *( (*mat) + (i*colunas+j) ) );
         fscanf(arq, "%f", (*mat) + (i*colunas+j));
      }
   }
   return 1;
}

//funcao que imprime uma matriz
//entrada: matriz de entrada, dimensoes da matriz
//saida: matriz impressa na tela
void imprimeMatriz(float *mat, int linhas, int colunas, FILE *arq) {
   int i, j;
   for (i=0; i<linhas; i++) {
      for (j=0; j<colunas; j++) {
         fprintf(arq, "%.1f ", mat[i*colunas+j]);
      }
      fprintf(arq, "\n");
   }
}

//funcao que aloca espaco para um vetor e preenche seus valores
//entrada: vetor de entrada, dimensao do vetor
//saida: retorna 1 se o vetor foi preenchido com sucesso e 0 caso contrario
int preencheVetor(float **vet, int dim, FILE *arq) {
   int i;
   //aloca espaco de memoria para o vetor
   *vet = (float*) malloc(sizeof(float) * dim);
   if (vet == NULL) return 0;
   //preenche o vetor
   for (i=0; i<dim; i++) {
       //*( (*vet)+i ) = 1.0;
       fscanf(arq, "%f", (*vet) + i);
   }
   return 1;
}

//funcao que imprime um vetor
//entrada: vetor de entrada, dimensao do vetor
//saida: vetor impresso na tela
void imprimeVetor(float *vet, int dim, FILE *arq) {
   int i;
   for (i=0; i<dim; i++) {
      fprintf(arq, "%.1f ", vet[i]);
   }
   fprintf(arq, "\n");
}

//funcao principal
int main(int argc, char *argv[]) {

  double parte1, parte1fim;

  GET_TIME(parte1);

   //float *matA; //matriz de entrada
   //float *vetX; //vetor de entrada
   //float *vetB; //vetor de saida
   FILE *arqA, *arqX, *arqB; //arquivos dos dados de entrada e saida


   int t; //variavel contadora
   int *tid; //identificadores das threads no programa


   //le e valida os parametros de entrada
   //o arquivo da matriz de entrada deve conter na primeira linha as dimensoes da matriz (linha coluna) seguido dos elementos da matriz separados por espaco
   //o arquivo do vetor de entrada deve conter na primeira linha a dimensao do vetor seguido dos elementos separados por espaco
   if(argc < 5) {
      fprintf(stderr, "Digite: %s <arquivo matriz A> <arquivo matriz B> <arquivo matriz saida> <n-threads>\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   nthreads = atoi(argv[4]);
   pthread_t tid_sistema[nthreads]; //vetor de identificadores das threads no sistema

   //abre o arquivo da matriz de entrada
   arqA = fopen(argv[1], "r");
   if(arqA == NULL) {
      fprintf(stderr, "Erro ao abrir o arquivo da matriz de entrada.\n");
      exit(EXIT_FAILURE);
   }
   //le as dimensoes da matriz de entrada
   fscanf(arqA, "%d", &linhas);
   fscanf(arqA, "%d", &colunas);

   //abre o arquivo do vetor de entrada
   arqX = fopen(argv[2], "r");
   if(arqX == NULL) {
      fprintf(stderr, "Erro ao abrir o arquivo do vetor de entrada.\n");
      exit(EXIT_FAILURE);
   }
   //le a dimensao do vetor de entrada
   fscanf(arqX, "%d", &linhas2);
   fscanf(arqX, "%d", &colunas2);


   //valida as dimensoes da matriz e vetor de entrada
   if(colunas != linhas2) {
      fprintf(stderr, "Erro: as dimensoes da matriz e do vetor de entrada nao sao compativeis.\n");
      exit(EXIT_FAILURE);
   }

   //abre o arquivo do vetor de saida
   arqB = fopen(argv[3], "w");
   if(arqB == NULL) {
      fprintf(stderr, "Erro ao abrir o arquivo do vetor de saida.\n");
      exit(EXIT_FAILURE);
   }

   //aloca e preenche a matriz de entrada
   if(preencheMatriz(&matA, linhas, colunas, arqA) == 0) {
      fprintf(stderr, "Erro de preenchimento da matriz de entrada\n");
      exit(EXIT_FAILURE);
   }
   //aloca e preenche o vetor de entrada
   if(preencheMatriz(&matX, linhas2, colunas2, arqX) == 0) {
      fprintf(stderr, "Erro de preenchimento do vetor de entrada\n");
      exit(EXIT_FAILURE);
   }
   //aloca o vetor de saida
   matB = (float*) malloc(sizeof(float) * linhas * linhas2);
   if(matB==NULL) {
      fprintf(stderr, "Erro de alocacao do vetor de saida\n");
      exit(EXIT_FAILURE);
   }

   GET_TIME(parte1fim);

   double resultado = parte1fim - parte1;
   printf("LEITURA: %f\n", resultado);

  GET_TIME(parte1);

   for(t=0; t<nthreads; t++) {
     tid = malloc(sizeof(int)); if(tid==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
     //printf("começa a criar thread\n");
     *tid = t;

     if (pthread_create(&tid_sistema[t], NULL, multiplicaMatrizMatriz, (void*) tid)) {
       printf("--ERRO: pthread_create()\n"); exit(-1);
     }
   }
   //espera todas as threads terminarem e imprime o vetor de saída
   for(t=0; t<nthreads; t++) {
     if (pthread_join(tid_sistema[t], NULL)) {
       printf("--ERRO: pthread_join()\n"); exit(-1);
     }
   }

  GET_TIME(parte1fim);
  resultado = parte1fim-parte1;
  printf("MULTIPLICACAO C/ %d THREADS: %f\n", nthreads, resultado);

  GET_TIME(parte1);
   /*
   //imprime a matriz de entrada
   printf("Matriz de entrada:\n");
   imprimeMatriz(matA, linhas, colunas, stdout);
   //imprime o vetor de entrada
   printf("Vetor de entrada:\n");
   imprimeMatriz(vetX, colunas, stdout);
   */



   //multiplica a matriz de entrada pelo vetor de entrada
   //multiplicaMatrizMatriz(matA, vetX, vetB, linhas, colunas);

   //imprime o vetor de saida no arquivo de saida
   imprimeMatriz(matB, linhas, colunas2, arqB);

   //libera os espacos de memoria alocados
   free(matA);
   free(matX);
   free(matB);

  GET_TIME(parte1fim);
  resultado = parte1fim-parte1;
  printf("IMPRESSAO: %f\n", resultado);

   printf("------------------------------------------\n");

   return 0;
}
