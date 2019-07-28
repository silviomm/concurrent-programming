/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 9 */
/* Codigo: Comunicação entre threads usando variável compartilhada e sincronização com semáforos */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 4
#define N 5

int buffer[N];
//2 semaforos binarios e os que indicam cheio(começa 0) e vazio(começa N)
sem_t bin, bout, cheio, vazio;

//gasta tempo
void boba(){
  int n = 500000000;
  while(n>0){
    n--;
  }
}

//imprime o buffer
void imprime(){
  int i;
  for (i = 0; i < N; i++) {
    printf("%d | ", buffer[i]);
  }
  printf("\n");
}

//insere no buffer
void insere(int entrada){
  static int in = 0;
  sem_wait(&vazio);
    sem_wait(&bin);
      printf("Inserindo %d na posição %d\n", entrada, in);
      buffer[in] = entrada;
      imprime();
      in = ++in%N;
    sem_post(&bin);
  sem_post(&cheio);
}

//retira do buffer
void retira(){
  static int out = 0;
  sem_wait(&cheio);
    sem_wait(&bout);
      printf("Retirando %d da posição %d\n", buffer[out], out);
      buffer[out] = 0;
      imprime();
      out = ++out%N;
    sem_post(&bout);
  sem_post(&vazio);
}

void *produtor (void *threadid) {
  int tid = *(int*) threadid;
  while (1) {
    insere(tid);
    boba();
  }
}

void *consumidor (void *threadid) {
  int *tid = (int*) threadid;
  while(1){
    retira();
    boba();
  }
}

//funcao principal
int main(int argc, char *argv[]) {
  pthread_t tid[NTHREADS];
  int *id[NTHREADS], t;

  //inicia os semaforos
  sem_init(&vazio, 0, N);
  sem_init(&cheio, 0, 0);
  sem_init(&bin, 0, 1);
  sem_init(&bout, 0, 1);

  int a = 1;
  for (t=0; t<NTHREADS; t++) {
    if ((id[t] = malloc(sizeof(int))) == NULL) {
       pthread_exit(NULL); return 1;
    }
    *id[t] = t+1;

    if(a){
      if (pthread_create(&tid[t], NULL, produtor, (void *)id[t])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
      a = 0;
    }
    else {
      if (pthread_create(&tid[t], NULL, consumidor, (void *)id[t])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
      a = 1;
    }


  }

  //--espera todas as threads terminarem
  for (t=0; t<NTHREADS; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1);
    }
    free(id[t]);
  }
  pthread_exit(NULL);
}
