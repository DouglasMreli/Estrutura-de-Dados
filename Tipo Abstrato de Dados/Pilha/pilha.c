#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

#define N 100

struct pilha{
	int vet[N];
	int topo;
};


Pilha Inicializar() {
	Pilha p = (Pilha)malloc(sizeof(struct pilha));
	p->topo = 0;
	return p;	
}

Pilha Destruir(Pilha p) {
	free(p);
	return NULL;
}

int Cheia(Pilha p){
	if(p->topo == N) 
		return 1;
	else 
		return 0;
}

int Vazia(Pilha p) {
	if(p->topo == 0)
		return 1;
	else
		return 0;
}

int Push(Pilha p, int x) {
	if(Cheia(p)){
		return 0;
	}
	
	p->vet[p->topo] = x;
	p->topo++;
	return 1;
}

int Pop(Pilha p, int *x) {
	if(Vazia(p)){
		return 0;
	}
	
	p->topo--;
	*x = p->vet[p->topo];
	return 1;	
}

