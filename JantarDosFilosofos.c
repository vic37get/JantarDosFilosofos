#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <windows.h>
#define N 5
#define ESQUERDA (i+N-1)%N
#define DIREITA (i+1)%N
#define PENSANDO 0
#define FOME 1
#define COMENDO 2
//Aluno: Victor Ribeiro da Silva

typedef int semaphore;
int state[N];
int identificador_filosofos[N];
pthread_mutex_t s[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void pensar(int n){
	//Filosofo est� pensando
	Sleep(1);
}

void comer(int n){
	//Filosofo est� comendo
	Sleep(1);
}

void estados(){
	int i;
	printf("Filosofos que estao COMENDO: ");
	for(i = 0; i < N; i ++){
		if(state[i] == COMENDO){
			printf("%d ",i);
		}
	}
	printf("\n");
	printf("\n");
	printf("Filosofos que estao PENSANDO: ");
	for(i = 0; i < N; i ++){
		if(state[i] == PENSANDO){
			printf("%d ",i);
		}
	}
	printf("\n");
	printf("\n");
	printf("Filosofos que estao COM FOME: ");
	for(i = 0; i < N; i ++){
		if(state[i] == FOME){
			printf("%d ",i);
		}
	}
	printf("\n");
	printf("--------------------------------------|\n");
	Sleep(1500);
}


void test(int i){
	if(state[i] == FOME && state[ESQUERDA] != COMENDO && state[DIREITA] != COMENDO){
		state[i] = COMENDO;
		pthread_mutex_unlock(&(s[i]));
	}
	
}

void pegar_garfos(int i){
	
	pthread_mutex_lock(&mutex);
	estados();
	state[i] = FOME;
	estados();
	test(i);
	estados();
	pthread_mutex_unlock(&mutex);
	pthread_mutex_lock(&(s[i]));
}

void devolver_garfos(int i){
	
	pthread_mutex_lock(&mutex);
	estados();
	state[i] = PENSANDO;
	estados();
	test(ESQUERDA);
	estados();
	test(DIREITA);
	estados();
	pthread_mutex_unlock(&mutex);
}

void *filosofo(void *ptr){
	
	while(1){
	int *n = ptr;
	pensar(*n);
	pegar_garfos(*n);
	comer(*n);
	devolver_garfos(*n);
	}
	
}

int main(){
	
	int i;
	pthread_t filosofos[N];
	
	for(i = 0; i < N; i++){
		pthread_mutex_init(&(s[i]), NULL);
	}
	
	for(i = 0; i < N; i++){
		identificador_filosofos[i] = i;
	}
	
	for(i = 0; i< N; i++){
		pthread_t t;
		int result;
		
		result = pthread_create(&(filosofos[i]), NULL, filosofo, &identificador_filosofos[i]);
		
	}
	
	for(i = 0; i < N; i++){
		pthread_join(filosofos[i], NULL);
	}

	
	
	return 0;
}


