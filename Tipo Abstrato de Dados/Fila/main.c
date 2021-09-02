//Grupo: Ayla Rodrigues, Douglas Mareli, Sofia Kitaeva
//pilha - TAD

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "fila.h"

void MenuOpcoes(){
	printf("O que deseja fazer?\n");
	printf(" 1.Inserir um elemento na Fila.\n");
	printf(" 2.Remover um elemento da Fila.\n");
	printf(" 3.Impimir a Fila.\n");
	printf(" 4.Sair\n");	
}

int main() {
	setlocale(LC_ALL, "");
	
	Fila a;
	a = Inicializar();
	int opcao = 0;
	while(opcao!=4)  {
		MenuOpcoes();
		scanf("%d", &opcao);
		
		if(opcao == 1) {
			int elemento;
			printf("Qual elementa deseja inserir?\n>");
			scanf("%d",&elemento);
			int inseriu = Inserir(a, elemento);
			
			printf("\n\n");
			if(!inseriu) {
				printf("A fila está cheia, não foi possível inserir.\n");
			} else{
				printf("Elemento %d inserido com sucesso!\n", elemento);
			}
		
		}else if(opcao == 2) {
			
			int elemento;
			int removeu = Remover(a, &elemento);
			
			printf("\n\n");
			if(!removeu) {
				printf("A pilha está vazia, não foi possível remover.\n");
			} else{
				printf("Elemento %d removido com sucesso!\n", elemento);
			}
			
		}else if(opcao == 3) {
			Imprimir(a);
		}else if(opcao == 4) {
			Destruir(a);
		}
		
		printf("\n\n");
		system("pause");	
	}
	
	printf("O usuário saiu!\n");
	return 0;
	
}

