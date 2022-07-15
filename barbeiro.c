#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CADEIRAS 10
#define MAX 100

int fila = 0,j = 50;
pthread_mutex_t fila_movimento;
pthread_mutex_t pablo_ocupado;

pthread_cond_t condCons,condProd;

//sem_t clientes,pablo;


void *sentar();
void *trabalhar();

int main(int argn, char **argv) {

  pthread_t entrada[MAX];
  //pthread_t barbear;

	// Thread representa o pablo(Nome do barbeiro) trabalhando 
 // pthread_create(&barbear, NULL, trabalhar, NULL);
	
	// Mutex patra evitar conflitop no buffer
	pthread_mutex_init(&fila_movimento,NULL);
	// Semaforo registra se alguem esta entrando na fila
	//sem_init(&clientes,0,0);
	//sem_init(&pablo,0,1);
	
	// Semaforo registra 
  int i;
  for (i = 0; i < MAX; i++) {
    pthread_create(&entrada[i], NULL, sentar,NULL);
  }
	//pthread_create(&barbear, NULL, trabalhar, NULL);
  //pthread_join(barbear,NULL);
  for (i = 0; i < MAX; i++) {
    pthread_join(entrada[i], NULL);
  }
	
  
	// for (i = 0; i < MAX; i++) {
 //    pthread_exit(&entrada[i]);
 //  }
  
  return 0;
	
}

void *sentar() {
	while(j){
	pthread_mutex_lock(&fila_movimento);
	while (fila != 0 ) pthread_cond_wait(&condProd, &pablo_ocupado);
  if (fila < CADEIRAS) {
		fila++;
		printf("Local %d da fila ocupado\n",fila);
  }
	else if(fila >= CADEIRAS){
		printf("Fila cheia\n");
	}
	printf("Fila aumentou\n");
	pthread_mutex_unlock(&fila_movimento);
	pthread_cond_signal(&condCons);
	printf("Sinal\n");
		j--;
	//pthread_exit();
	trabalhar();
		}
	}

void *trabalhar(){
	printf("Tenta trabalhar: %d\n",j);
	pthread_mutex_lock(&fila_movimento);
	printf("Trabalha\n");
	while (fila == 0 ) {
		printf("Pablo mimiu\n");
		pthread_cond_wait(&condCons, &pablo_ocupado);
		}
	printf("Pablo atendeu cliente\n");
	fila--;
	pthread_cond_signal(&condProd);
	pthread_mutex_unlock(&fila_movimento);
	}
