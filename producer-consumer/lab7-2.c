/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 7 */
/* Codigo: Atividade 2 */
/* Alunos: Silvio Mançano e Vitor Trentin*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NTHREADS  5
#define N 5
#define Nfib 25

/* Variaveis globais */
pthread_mutex_t mutex;
pthread_cond_t cond_cons;
pthread_cond_t cond_prod;
int buffer[N], cont, in, out, processado=Nfib, tid;

int geraDado(){
	static a=1;
	static b=1;
	int aux = a+b;
	a = b;
	b = aux;
	return aux;
}

void insere(int elemento) {
	pthread_mutex_lock(&mutex);
	while(cont==N){
		pthread_cond_wait(&cond_prod,&mutex);
	}
	cont++;
	buffer[in]=elemento;
	in=(in+1)%N;
	pthread_cond_signal(&cond_cons);
	pthread_mutex_unlock(&mutex);
}

/* Thread B */
int retira() {
	int elemento;
  pthread_mutex_lock(&mutex);
	while(cont==0){
		pthread_cond_wait(&cond_cons, &mutex);
	}
	cont--;
	elemento = buffer[out];
	out=(out+1)%N;
	processado--;
	pthread_cond_signal(&cond_prod);
	pthread_mutex_unlock(&mutex);
	return elemento;
}

int ehPrimo(long unsigned int n) {
	int i;
	if(n<=1) return 0;
	if(n==2) return 1;
	if(n%2==0) return 0;
	for(i=3; i< sqrt(n)+1; i+=2) {
			if(n%i==0) return 0;
	}
	return 1;
}

void processa(int dado){
	if(ehPrimo(dado)){
		printf("Primo = %d\n", dado);
	}
	else{
		printf("%d\n", dado);
	}
}

void * produtor(){
	int elemento;
	while(processado != 2){
		elemento = geraDado();
		insere(elemento);
	}
	pthread_exit(NULL);
}

void * consumidor(){
	pthread_mutex_lock(&mutex);
	printf("consumidor criado %d\n", tid);
	tid++;
	pthread_mutex_unlock(&mutex);
	int dado;
	while(processado != 2){
		dado = retira();
		processa(dado);
	}
	pthread_exit(NULL);
}




/* Funcao principal */
int main(int argc, char *argv[]) {
  int i;
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init (&cond_prod, NULL);
  pthread_cond_init (&cond_cons, NULL);

  /* Cria uma thread produtora e NTHREADS-1 consumidoras*/
  int decide=0;
  for(i=0;i<NTHREADS-1;i++){
	  if(decide==0){
	  	pthread_create(&threads[i], NULL, *produtor, NULL);
	  	decide=1;
	  }
	  if(decide==1){
	  	pthread_create(&threads[i], NULL, *consumidor,NULL);
	  }
  }

  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS-1; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("\nFIM\n");

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond_cons);
  pthread_cond_destroy(&cond_prod);
  pthread_exit (NULL);
}
