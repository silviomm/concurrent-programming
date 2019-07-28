/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho 1 - Versão Concorrente */
/* Codigo: Programa concorrente de contagem de caracteres num arquivo.*/
/* Alunos:
    Silvio Mançano de Mattos Junior DRE: 115092720
    Vitor Curiel Trentin Corral DRE: 115007555
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "timer.h"
#include <string.h>

//Quantidade maxima de caracteres que o fgets irá ler
#define LINHA 200

//Vetores da ED
//validos = caracteres válidos na descrição do Trabalho
char *validos;
//frequencia = conta a qntd de aparições do caractere
int *frequencia;
//quantidade de caracteres validos
int qntd;


pthread_mutex_t mutex_freq;

//Função que inicializa todas os caracters a serem contados(validos)
void inicializaPossiveisChar(FILE *arq){
  fscanf(arq, "%d", &qntd);
  validos = (char *) malloc(sizeof(char)*qntd);
  frequencia = (int *) malloc(sizeof(int)*qntd);
  int i;
  fgetc(arq);
  for(i = 0; i<qntd; i++){
    validos[i] = fgetc(arq);
    frequencia[i] = 0;
  }
}

//Incrementa a frequencia do caracter na posição dada
void incrementa(int *freq_parc){
    int i;
    pthread_mutex_lock(&mutex_freq);
    for(i=0;i<qntd;i++){
      frequencia[i]+=freq_parc[i];
    }
    pthread_mutex_unlock(&mutex_freq);
}

//Checa se o caracter "lido" está no vetor de caracteres validos
//Atualiza o valor da freq_parcial, para no final do programa somarmos tudo
void valida(char* lido, int** freq_parc){
  int i=0,j=0;
  for(j=0;j<strlen(lido);j++){
     for(i=0;i<strlen(validos);i++){
          if(validos[i] == lido[j]){
	    (*freq_parc)[i]++;
            i = strlen(validos);
          }
    }
  }
}



//Imprime o caracter e sua frequencia dos vetores indexos
void imprime(char *nome){
  FILE *arq = fopen(nome, "w+");
  int i;
  for(i = 0;i<strlen(validos);i++){
    if(frequencia[i]!=0){
      fprintf(arq, "%c, %d\n", validos[i], frequencia[i]);
    }
  }
  fclose(arq);
}

//Le "linhas" do arquivo enquanto fgets() nao retorna NULL(fim do arquivo)
void * leitura(void* args){
  FILE *arq = (FILE *) args;
  char lido[LINHA];
  int* freq_aux = (int *) malloc(sizeof(int)*qntd);
  int i;
  for(i=0;i<qntd;i++){freq_aux[i] = 0;}
  while(fgets(lido,LINHA,arq) != NULL){
    valida(lido, &freq_aux);
  }
  incrementa(freq_aux);
}

int main(int argc, char* argv[3]){

  //Variáveis de controle de Tempo
  double inicio, fim, concInicio, concFim, impInicio, impFim;
  GET_TIME(inicio);

  //Inicializa as variáveis de exclusão mútua
  pthread_mutex_init(&mutex_freq,NULL);

  //Abre como arquivo de leitura os caracteres válidos e usa a função "inicializaPossiveisChar"
  char url[] = "validos.txt";
  FILE *arq;
  arq = fopen(url, "r");
  inicializaPossiveisChar(arq);

  //----------------------------------------------------------------------------

  //Abre o arquivo de entrada e Inicializa o vetor de Threads informado como argumento do programa.
  arq = fopen(argv[1], "r");
  int nthreads = atoi(argv[3]);
  pthread_t *tid_sistema = malloc(sizeof(pthread_t)*nthreads);

  //Cria n-threads e passa a função "leitura" para ser executada em cada uma, além de um ponteiro pro arquivo teste.
  int t;
  GET_TIME(concInicio);
  for(t=0; t<nthreads; t++) {
     if (pthread_create(&tid_sistema[t], NULL, leitura, (void *) arq)) {
       printf("--ERRO: pthread_create()\n"); exit(-1);
     }
   }

   //Espera todas as threads terminarem
   for(t=0; t<nthreads; t++) {
     if (pthread_join(tid_sistema[t], NULL)) {
       printf("--ERRO: pthread_join()\n"); exit(-1);
     }
  }
  GET_TIME(concFim);

  //----------------------------------------------------------------------------

  //Imprime resultados no arquivo de saída e calcula seu tempo
  GET_TIME(impInicio);
  imprime(argv[2]);
  GET_TIME(impFim);

  fclose(arq);

  GET_TIME(fim);

  //Faz a diferença de tempos para saber a quantidade decorrida
  fim = fim - inicio;
  concFim = concFim - concInicio;
  impFim = impFim - impInicio;

  printf("Tempo Total: %lf\n", fim);
  printf("Tempo De Leitura e Processamento Paralelo: %lf\n", concFim);
  printf("Tempo de Impressão no Arquivo: %lf\n", impFim);

  return 0;
}
