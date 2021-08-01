//Grupo: Ayla Rodrigues, Douglas Mareli, Sofia Kitaeva
//Backtracking exercício 1

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


void ImprimirCombinacoesAEI(char *vet, int pos, int n, char *vetAux) {
	if(pos == n) {
		int qtdA = 0; //quantidade de As
		int qtdEI = 0; //quantidade de e + i
		
		for(int i = 0; i < n; i++) {
			if(vet[i] == 'a') {
				qtdA++;     
			} else {
				qtdEI++;
			}
		}	
		
		if(qtdA > qtdEI) {
				printf("%s\n",vet);
		}
		                             
	} else {
		for(int i = 0; i <= 2; i++) {
			vet[pos] = vetAux[i];
			ImprimirCombinacoesAEI(vet,pos+1,n,vetAux);
		}
	}	
}


int main() {
	
	setlocale(LC_ALL, "");
	
	int n;
	
	printf("Digite o tamanho da combinação:");
	scanf("%d",&n);	
	printf("\n");
	printf("Combinações entre 'a', 'e' e 'i' em que o número de a's é maior que de e's + i's:\n");
	
	char* vet=(char *)malloc(n * sizeof(char));
	char vetAux[3] = "aei";
	ImprimirCombinacoesAEI(vet, 0, n, vetAux);
	
	
	return 0;
}



