#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

#define N 100

struct fila{
	int vet[N];
	int ultimo;
};


Fila Inicializar() {
	Fila f = (Fila)malloc(sizeof(struct fila));
	f->ultimo = 0;
	return f;	
}

Fila Destruir(Fila f) {
	free(f);
	return NULL;
}

int Cheia(Fila f){
	if(f->ultimo == N) 
		return 1;
	else 
		return 0;
}

int Vazia(Fila f) {
	if(f->ultimo == 0)
		return 1;
	else
		return 0;
}

int Inserir(Fila f, int x) {
	if(Cheia(f)){
		return 0;
	}
	
	f->vet[f->ultimo] = x;
	f->ultimo++;
	return 1;
}

int Remover(Fila f, int *x) {
	if(Vazia(f)){
		return 0;
	}
	
	*x = f->vet[0];
	
	for(int i = 1; i < f->ultimo; i++) {
		f->vet[i-1] = f->vet[i]; 
	}
	f->ultimo--;
	
	return 1;	
}

void Imprimir(Fila f) {
	printf("\n");
	printf("Elementos: ");
	
	for(int i = 0; i < f->ultimo; i++) {
		printf("%d ", f->vet[i]);
	}
}

