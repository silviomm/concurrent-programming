/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho 1 - Versão Sequencial */
/* Codigo: Programa sequencial de contagem de caracteres num arquivo utilizando a função fgets.*/
/* Alunos:
    Silvio Mançano de Mattos Junior DRE: 115092720
    Vitor Curiel Trentin Corral DRE: 115007555
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "timer.h"

//quantos caracteres no máximo o fgets irá pegar do arquivo
#define TAM 150

//Vetores da ED
//validos = caracteres válidos na descrição do Trabalho
char *validos;
//frequencia = conta a quantidade de aparições do caractere
int *frequencia;

//Função que inicializa todas os caracters a serem contados(validos)
void inicializaPossiveisChar(FILE *arq){
  int qntd;
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

//Checa se cada caractere na string "lido" está no vetor de caracteres validos
//E incrementa a sua frequencia caso seja verdadeiro
int valida(char *lido){
  int i,j;
  for(j=0;j<strlen(lido);j++){
      for(i=0;i<strlen(validos);i++){
        if(validos[i] == lido[j]){
          frequencia[i]++;
          i = strlen(validos)-1;
        }
	  }
  }
}

//Imprime o caracter e sua frequencia dos vetores indexos no arquivo de saída
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

int main(int argc, char* argv[2]){

  //variáveis de controle de tempo
  double inicio, fim;
  double leitura_inicio, leitura_fim, diff = 0;
  double imprime_inicio, imprime_fim;
  double processa_inicio, processa_fim, diff2 = 0;
  
  GET_TIME(inicio);

  //Abre o arquivo de caracteres válidos.
  char url[] = "validos.txt";
  FILE *arq;
  arq = fopen(url, "r");
  inicializaPossiveisChar(arq);


  //Abre arquivo de teste e inicializa string a ser lida
  arq = fopen(argv[1], "r");
  char lido[TAM];


  //Enquanto não chegar ao final do arquivo, pegamos mais uma string e passamos para as funções.
  //Vamos somando o tempo também de quanto demoram as funções de leitura e processamento
  GET_TIME(leitura_inicio);
  while(fgets(lido,TAM,arq) != NULL){
    GET_TIME(leitura_fim);
    diff += leitura_fim - leitura_inicio;
    GET_TIME(processa_inicio);
    valida(lido);
    GET_TIME(processa_fim);
    diff2 += processa_fim - processa_inicio;
    GET_TIME(leitura_inicio);
  }
  GET_TIME(leitura_fim);
  diff += leitura_fim - leitura_inicio;

  GET_TIME(imprime_inicio);
  imprime(argv[2]);
  GET_TIME(imprime_fim);
  fclose(arq);
  

  GET_TIME(fim);
  
  //Print do tempo decorrido em cada parte do programa
  printf("Tempo Total: %lf\n", fim-inicio);
  printf("Tempo Leitura: %lf\n", diff);
  printf("Tempo Processamento: %lf\n", diff2);
  printf("Tempo Impressão: %lf\n", imprime_fim - imprime_inicio);

  return 0;
}



