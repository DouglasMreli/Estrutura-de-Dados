#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void ImprimirCombinacoes(int *vet, int pos, int n, int cent, int* vetAux){
	if(pos == n) {
		int soma = 0;
		for(int i = 0; i < n; i++) {
	
			soma += (vet[i] * vetAux[i]);
		}
		if(soma == cent) {
			for(int i = 0; i < n; i++) {
				printf("%d moedas de %d centavos; ",vet[i],vetAux[i]);
			}
			printf("\n");
		}
		
	} else {
		
		int maximo = (int)cent/vetAux[pos];
		
		for(int i = 0; i <= maximo; i++) {
			vet[pos] = i;
			ImprimirCombinacoes(vet, pos+1, n, cent, vetAux);
			
		}
	}
}

int main(){
	int cent;

	printf("Quantos centavos quer representar?\n>> ");
	scanf("%d", &cent);

	int* vet = (int*) malloc(sizeof(int)*5);
	int* vetAux = (int*) malloc(sizeof(int)*5);	
	vetAux[0] = 1;
	vetAux[1] = 5;
	vetAux[2] = 10;
	vetAux[3] = 25;
	vetAux[4] = 50;
	
	
	ImprimirCombinacoes(vet,0,5,cent,vetAux);

	return 0;
}

