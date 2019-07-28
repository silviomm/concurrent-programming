/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 9 */
/* Codigo: Comunicação entre threads usando variável compartilhada e sincronização com semáforos */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 4

// Variaveis globais
int x = 0;      //variavel compartilhada entre as threads
sem_t condt, condt1;     //semaforos para sincronizar a ordem de execucao das threads

//funcao executada pela thread 1
void *t1 (void *threadid) {
  int *tid = (int*) threadid;
  printf("Thread : %d esta executando...\n", *tid);
  printf("ola, tudo bem?\n");
  sem_wait(&condt);
  sem_post(&condt1);
  sem_post(&condt1);
  printf("Thread : %d terminou!\n", *tid);
  pthread_exit(NULL);
}

//funcao executada pela thread 2
void *t2 (void *threadid) {
  int *tid = (int*) threadid;
  printf("Thread : %d esta executando...\n", *tid);
  printf("hello\n");
  sem_post(&condt);
  printf("Thread : %d terminou!\n", *tid);
  pthread_exit(NULL);
}

//funcao executada pela thread 3
void *t3 (void *threadid) {
  int *tid = (int*) threadid;
  printf("Thread : %d esta executando...\n", *tid);
  sem_wait(&condt1);
  printf("até mais tarde!\n");
  printf("Thread : %d terminou!\n", *tid);
  pthread_exit(NULL);
}

void *t4 (void *threadid) {
  int *tid = (int*) threadid;
  printf("Thread : %d esta executando...\n", *tid);
  sem_wait(&condt1);
  printf("tchau!\n");
  printf("Thread : %d terminou!\n", *tid);
  pthread_exit(NULL);
}

//funcao principal
int main(int argc, char *argv[]) {
  pthread_t tid[NTHREADS];
  int *id[NTHREADS], t;

  for (t=0; t<NTHREADS; t++) {
    if ((id[t] = malloc(sizeof(int))) == NULL) {
       pthread_exit(NULL); return 1;
    }
    *id[t] = t+1;
  }

  //inicia os semaforos
  sem_init(&condt, 0, 0);
  sem_init(&condt1, 0, 0);

  //cria as tres threads
  if (pthread_create(&tid[0], NULL, t1, (void *)id[0])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[1], NULL, t2, (void *)id[1])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[2], NULL, t3, (void *)id[2])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[3], NULL, t4, (void *)id[3])) { printf("--ERRO: pthread_create()\n"); exit(-1); }


  //--espera todas as threads terminarem
  for (t=0; t<NTHREADS; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1);
    }
    free(id[t]);
  }
  pthread_exit(NULL);
}
