#ifndef Fila_H
#define Fila_H

typedef struct fila *Fila;
int Inserir(Fila p, int x);
int Remover(Fila p, int *x);
void Imprimir(Fila p);

Fila Inicializar();
Fila Destruir(Fila p);

#endif


