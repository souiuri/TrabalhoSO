#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define DELAY 1000

sem_t mutex;

void *dogWantToEnter();
void *catWantToEnter();
void dogLeave(int *dog);
void catLeave(int *cat);

int medicamentos = 50;
int vet[2] = {0,0};
int prox;

int main(){
	pthread_t dogT,catT;
	
	sem_init(&mutex,0,1);
	pthread_create(&dogT,NULL,dogWantToEnter,NULL);
	pthread_create(&catT,NULL,catWantToEnter,NULL);
	
	pthread_join(dogT,NULL);
	pthread_join(catT,NULL);
	return 0;
}

void *dogWantToEnter(){
	int dog = vet[0];
	while(medicamentos > 0){
		printf("Cachorros tentam entrar\n");
		prox = 0;
		sem_wait(&mutex);
		dog++;
		medicamentos--;
		printf("Cachorros estão na sala, medicamento: %d\n",medicamentos);
		usleep((DELAY)*(medicamentos+1));
		dogLeave(&dog);
	}		
	return NULL;
}

void dogLeave(int *dog){
	printf("Há %d cachorros na sala\n",*dog);
	//if(prox == 1){
		(*dog)--;
		printf("Cachorros estão saindo da sala\n");
		if(*dog == 0){
			sem_post(&mutex);
			printf("Cachorros estão fora da sala\n");
			}
		//}
}

void *catWantToEnter(){
	int cat = vet[1];
	while(medicamentos>0){
		printf("Gatos tentam entrar\n");
		prox = 1;
		sem_wait(&mutex);
		cat++;
		medicamentos--;
		printf("Gatos estão na sala, medicamento: %d\n",medicamentos);
		usleep((DELAY)*(medicamentos+1));
		catLeave(&cat);
	}	
}

void catLeave(int *cat){
	printf("Há %d gatos na sala\n",*cat);
	//if(prox == 0){
		(*cat)--;
		printf("Gatos estão saindo da sala\n");
		if(*cat == 0){
			sem_post(&mutex);
			printf("Gatos estão fora da sala\n");
		}
	//}
}
