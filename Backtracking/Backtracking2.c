// Grupo: Ayla Rodrigues, Douglas Mareli, Sofia Kitaeva
// Exercicio de Backtracking 2 - Estrutura de dados

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void ImprimirCombinacoes(int *vet, int pos, int n, int* vetAux){
	int aux=0;
	if(pos==n){
		for(int i=0; i<=n;i++)
			aux+=vet[i];
		if(aux%2==0){
			for(int i=0; i<n;i++)
				printf("%d ", vet[i]);
			printf("\n");
		}
	}
	else{
		for(int i=0;i<=3;i++){
			vet[pos]=vetAux[i];
			ImprimirCombinacoes(vet,pos+1,n,vetAux);
		}
	}
}

int main(){
	setlocale(LC_ALL, "");
	int n;
	
	printf("Informe n\n>> ");
	scanf("%d", &n);
	int* vet = (int*) malloc(sizeof(int)*n);

	int* vetAux = (int*) malloc(sizeof(int)*4);	
	vetAux[0] = 15;
	vetAux[1] = 31;
	vetAux[2] = 55;
	vetAux[3] = 44;
	
	ImprimirCombinacoes(vet,0,n,vetAux);
	
	return 0;
}
