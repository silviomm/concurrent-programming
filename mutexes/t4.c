/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 6 */
/* Codigo: Uso de variáveis de condição e suas operações básicas para sincronização por condição */

/***** Condicao logica da aplicacao: a thread B so pode imprimir "ByeBye" depois que duas threads A imprimirem  "Hello"  ****/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  4

/* Variaveis globais */
int x = 1;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;

/* Thread A */
void *A (void *t) {
  int boba1, boba2;

 // printf("A: Comecei\n");
  
  /* faz alguma coisa inutil pra gastar tempo... */
  boba1=10000; boba2=-10000; while (boba2 < boba1) boba2++;
  
  printf("tudo bem?\n");

  pthread_mutex_lock(&x_mutex);
  x++;
  if (x>2) {
    //  printf("A:  x = %d, vai sinalizar a condicao \n", x);
      pthread_cond_broadcast(&x_cond);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}

/* Thread B */
void *B (void *t) {
 // printf("B: Comecei\n");
printf("Hola!\n");

  pthread_mutex_lock(&x_mutex);
  x++;
  if (x >2) { 
	//printf("B:  x = %d, vai sinalizar a condicao \n", x);
     pthread_cond_broadcast(&x_cond);
  }
  pthread_mutex_unlock(&x_mutex); 
  pthread_exit(NULL);
}

void *C (void *t) {
  //printf("C: Comecei\n");

  pthread_mutex_lock(&x_mutex);
 while (x <3) { 
	//printf("C:  x = %d, vai se bloquear a condicao \n", x);
     pthread_cond_wait(&x_cond, &x_mutex);
  }

	printf("Até mais tarde\n");
  pthread_mutex_unlock(&x_mutex); 
  pthread_exit(NULL);
}

void *D (void *t) {
  //printf("D: Comecei\n");

  pthread_mutex_lock(&x_mutex);
 while (x <3) { 
	//printf("D:  x = %d, vai sse bloquear a condicao \n", x);
     pthread_cond_wait(&x_cond, &x_mutex);
  }
	printf("tchau!\n");
  pthread_mutex_unlock(&x_mutex); 
  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);

  /* Cria as threads */
  pthread_create(&threads[0], NULL, A, NULL);
  pthread_create(&threads[1], NULL, B, NULL);
  pthread_create(&threads[2], NULL, C, NULL);
  pthread_create(&threads[3], NULL, D, NULL);

  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("\nFIM\n");

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
  pthread_exit (NULL);
}
