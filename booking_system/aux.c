/*
  Programa auxiliar ao Sistema de reserva de assentos, verifica se as funções do sistema foram executadas corretamente,
partindo de um log de execução impresso pelo sistema.

Autores: Vitor Curiel Trentin Corral & Silvio Mançano Mattos Junior
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* v0;//V
int* vPrincipal;//Ponteiro para o vetor de estado dos assentos anterior a chamada de uma função
int TAM;//Guarda o tamanho do vetor de estados dos assentos. Para podermos percorrelos

void printPrincipal(){
  int i;
  printf("[");
  for ( i = 0; i < TAM; i++) {
    printf("%d ,", vPrincipal[i] );
  }
  printf("]\n");
}
//-----------------------------------------------------------------------------------------------------------------------

//Verifica se o vetor que esta sendo passado esta igual ao vPrincipal
int veSeTaIgual(int* vet){
  int i;
  for (i = 0; i < TAM; i++) {//Percorre os vet e vPrincipal comparado posição a posição
    if(vet[i] != vPrincipal[i]){
      return 0;//Retorna 1 caso exista alguma diferença
    }
  }
  return 1;//Retorna 1 caso não exista diferença
}
//-----------------------------------------------------------------------------------------------------------------------

//Verifica se a função vizualizaAssento foi executada corretamente
void op1(int id, int* vet, int retorno){//Recebe o id da thread que chamou a função, o vetor de assentos que a função
  //retornou e o retorno(0 não conseguiu realizar, 1 conseguiu realizar)
  if(!veSeTaIgual(vet)){ printf("Erro na Operacao 01");}
  vPrincipal = vet;//Atualiza vPrincipal com o vetor atual de estado dos assentos
}
//-----------------------------------------------------------------------------------------------------------------------

//Verifica se a função alocaAssentoLivre foi executada corretamente
void op2(int id, int* vet, int retorno){//Recebe o id da thread que chamou a função, o vetor de assentos que a função
  //retornou e o retorno(0 não conseguiu realizar, 1 conseguiu realizar)
  if(retorno){//Se a função conseguiu realizar a operação
    int i;
    int alterado = 0;//Armazena a quantidade de alterações que ocorreram no vetor de assentos
    int certo = 0; //Armazena 0 ou 1 dependendo se a alteração do vetor foi feita corretamente
    for (i = 0; i < TAM; i++) {//Percorre os vet e vPrincipal comparado posição a posição
      if(vet[i] != vPrincipal[i]){
        alterado++;//Se encontrar uma diferença incrementa alterado
        if(vPrincipal[i] == 0 && vet[i]==id){
          certo = 1;//Certo vPrincipal o assento alterado estava com 0 vet ele esta com o id da thread
        }
      }
    }
    if(!(alterado == 1 && certo==1)){//Printa Erro caso tenha não tenha ocorrido somente uma alteração no vetor e essa
      //alteração esteja correta
        printf("Erro na Operacao 02\n");
    }
  }else{//Se a função não conseguiu realizar a operação
    if(!veSeTaIgual(vet)){ printf("Erro na Operacao 02");}//Printa Erro caso exista alguma alteração do vetor de assentos
  }
  vPrincipal = vet;//Atualiza vPrincipal com o vetor atual de estado dos assentos
}
//-----------------------------------------------------------------------------------------------------------------------
//Verifica se a função alocaAssentoDado foi executada corretamente
void op3(int id, int* vet, int retorno){//Recebe o id da thread que chamou a função, o vetor de assentos que a função
  //retornou e o retorno(0 não conseguiu realizar, 1 conseguiu realizar)
  if(retorno){//Se a função conseguiu realizar a operação
    int i;
    int alterado = 0;//Armazena a quantidade de alterações que ocorreram no vetor de assentos
    int certo = 0; //Armazena 0 ou 1 dependendo se a alteração do vetor foi feita corretamente
    for (i = 0; i < TAM; i++) {//Percorre os vet e vPrincipal comparado posição a posição
      if(vet[i] != vPrincipal[i]){
        alterado++;//Se encontrar uma diferença incrementa alterado
        if(vPrincipal[i] == 0 && vet[i]==id){
          certo = 1;//Certo vPrincipal o assento alterado estava com 0 vet ele esta com o id da thread
        }
      }
    }
    if(!(alterado == 1 && certo==1)){//Printa Erro caso tenha não tenha ocorrido somente uma alteração no vetor e essa
      //alteração esteja correta
        printf("Erro na Operacao 03\n");
    }
  }else{//Se a função não conseguiu realizar a operação
    if(!veSeTaIgual(vet)){ printf("Erro na Operacao 03");}//Printa Erro caso exista alguma alteração do vetor de assentos
  }
  vPrincipal = vet;//Atualiza vPrincipal com o vetor atual de estado dos assentos
}
//-----------------------------------------------------------------------------------------------------------------------
//Verifica se a função liberaAssento foi executada corretamente
void op4(int id, int* vet, int retorno){//Recebe o id da thread que chamou a função, o vetor de assentos que a função
  //retornou e o retorno(0 não conseguiu realizar, 1 conseguiu realizar)
  if(retorno){//Se a função conseguiu realizar a operação
    int i;
    int alterado = 0;//Armazena a quantidade de alterações que ocorreram no vetor de assentos
    int certo = 0; //Armazena 0 ou 1 dependendo se a alteração do vetor foi feita corretamente
    for (i = 0; i < TAM; i++) {//Percorre os vet e vPrincipal comparado posição a posição
        alterado++;//Se encontrar uma diferença incrementa alterado
        if(vet[i] == 0 && vPrincipal[i]==id){
          certo = 1;//Certo se vPrincipal estava um assento com o id da thread que chamou a função e vet consta 0
        }
      }
    
    if(!(alterado == 1 && certo==1)){//Printa Erro caso tenha não tenha ocorrido somente uma alteração no vetor e essa
      //alteração esteja correta
        printf("Erro na Operacao 04\n");
    }

  }else{
    if(!veSeTaIgual(vet)){ printf("Erro na Operacao 04");}//Printa Erro caso exista alguma alteração do vetor de assentos
  }
  vPrincipal = vet;//Atualiza vPrincipal com o vetor atual de estado dos assentos
}
//-----------------------------------------------------------------------------------------------------------------------
