/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Trabalho 1 - Versão Sequencial */
/* Codigo: Programa sequencial de contagem de caracteres num arquivo.*/
/* Alunos:
    Silvio Mançano de Mattos Junior DRE: 115092720
    Vitor Curiel Trentin Corral DRE: 115007555
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "timer.h"

//Vetores da ED
//validos = caracteres válidos na descrição do Trabalho
char *validos;
//frequencia = conta a qntd de aparições do caractere
int *frequencia;

//Função que inicializa todas os caracters a serem contados(validos)
void inicializaPossiveisChar(FILE *arq){
  int qntd;
  fscanf(arq, "%d", &qntd);
  validos = (char *) malloc(sizeof(char)*qntd);
  frequencia = (int *) malloc(sizeof(int)*qntd);
  int i;
  fgetc(arq);//Usamos este fgetc() para deixar o pontenteiro da funcao na linha de caracteres("pulando" o \n apos a quantidade)
  for(i = 0; i<qntd; i++){
    validos[i] = fgetc(arq);
    frequencia[i] = 0;
  }
}

//Checa se o caracter "lido" está no vetor de caracteres validos
int valida(char lido){
  int i;
  for(i=0;i<strlen(validos);i++){
    if(validos[i] == lido){
      return i; //retorna a posição em que está o caracter
    }
  }
  return -1; //ou -1 caso não seja um caractere válido
}

//Incrementa a frequencia do caracter na posição dada
void incrementa(int posicao){
  if(posicao != -1){
    frequencia[posicao]++;
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

  //Variáveis de controle de Tempo
  double inicio, fim, inicio1, fim1;
  GET_TIME(inicio1);

  //Abre como arquivo de leitura os caracteres válidos.
  char url[] = "validos.txt",lido;
  FILE *arq;
  arq = fopen(url, "r");
  inicializaPossiveisChar(arq);

  //Abre arquivo de teste e pega o primeiro caractere através da função "fgetc".
  arq = fopen(argv[1], "r");
  GET_TIME(inicio);
  lido = fgetc(arq);//Fazemos esse fgetc() fora do while para pegar o primeiro caracter e checar ...
  //Enquanto não chegar ao final do arquivo, pegamos mais um caractere e passamos para as funções
  while(lido != EOF){
    incrementa(valida(lido));
    lido = fgetc(arq);
  }

  GET_TIME(fim);
  //Variáveis de controle de Tempo para impressao
  double impIn, impOut;
  GET_TIME(impIn);
  imprime(argv[2]);
  GET_TIME(impOut);
  impOut = impOut - impIn;//Pega tempo de impressão

  printf("Leitura e Processamento : %lf\nImpressão : %lf\n", fim-inicio, impOut);
  fclose(arq);
  GET_TIME(fim1);
  printf("Tempo Total do programa: %lf\n", fim1-inicio1);

  return 0;
}
