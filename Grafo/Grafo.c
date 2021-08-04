#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

typedef struct lista {
	int destino;
	int custo;
	struct lista *prox;
}lista;

void Inicializar(lista **g, int n) {
	for(int i = 0; i <= n; i++) 
		g[i] = NULL;
}

lista *InserirLista(lista *l, int d, int c) {
	lista *no = (lista *)malloc(sizeof(lista));
	no->destino = d;
	no->custo = c;
	no->prox = l;
	return no;
}

void *RemoveLista(lista *l, int d) {
	
	if(l->destino == d) {
		lista *aux = l;
		l = l->prox;
		free(aux);
		return l;		
	}
	
	lista *aux = l->prox;
	lista *auxAnt = l;
	
	while(auxAnt != NULL) {
		if(aux->destino == d) {
			auxAnt->prox = aux->prox;
			free(aux);
			return l;
		}
		aux = aux->prox;
		auxAnt = auxAnt->prox;
	}
	
	free(aux);
	return l;
	
}

void *InserirAresta(lista **g, int origem, int destino, int custo) {
	g[origem] = InserirLista(g[origem],destino,custo);
}

void *RemoverAresta(lista **g, int origem, int destino) {
	g[origem] = RemoveLista(g[origem], destino);
}

void ImprimirLista(lista *l) {
	if(l != NULL) {
		printf("-(destino: %d, custo: %d)",l->destino,l->custo);
		ImprimirLista(l->prox);
	}
}

void ImprimirGrafo(lista **g, int n) {
	printf("---- Grafo: ----");
	for(int i = 1; i <= n; i++) {
		printf("\nVértice %d: ",i);
		ImprimirLista(g[i]);
	}
}

void ImprimirGrausES(lista **g, int n) {
	int *vet = (int *)malloc((n+1)*sizeof(int));
	for(int i = 0; i < n; i++) {
		vet[i] = 0;
	}
	
	
	printf("\n---- Grau de Saída: ----\n");
	for(int i = 1; i <= n; i++) {
		int ct = 0;
		lista *aux = g[i];
		while(aux != NULL) {     
			ct++;
			vet[aux->destino - 1]++; // 
			aux = aux->prox;
		}
		printf("Vértice %d: grau %d\n",i, ct);
		
	}
	
	printf("\n---- Grau de Entrada: ----\n");
	for(int i = 0; i < n; i++) {
		printf("Vértice %d: grau %d\n",i+1,vet[i]);
	}
	
	free(vet);
}

int VerificaGrafoCompleto(lista **g, int n) {
	
	int ct = 0;
	for(int i = 1; i <= n; i++) {
		lista *aux = g[i];
		while(aux != NULL) {     
			ct++; 
			aux = aux->prox;
		}
	}
	
	int total = n * (n-1);
	
	if(ct == total) {
		return 1;
	} else {
		return 0;
	}
	
	
}

int main() {
	setlocale(LC_ALL, "");
	
	int n;
	printf("Digite o número de vértices do grafico:\n");
	scanf("%d",&n);
	
	lista **g;
	g = (lista**)malloc((n+1)*sizeof(lista));
	Inicializar(g, n);
	
	printf("\n------ Grafo Inicializado ------\n\n");
	
	int opcao = 0;
	while(opcao != 6) {
		printf("O que deseja fazer?\n 1.Inserir uma aresta no grafo\n 2.Remover uma aresta do grafo\n 3.Imprimir grafo\n 4.Imprimir os graus de entrada e saída de um vértice\n 5.Verificar se um grafo é completo\n 6.Sair\n>");
		scanf("%d", &opcao);
		
		if(opcao == 1) {
			int origem;
			printf("\nDigite a vértice de origem: \n>");
			scanf("%d", &origem);
			
			int destino;
			printf("Digite a vértice de destino: \n>");
			scanf("%d", &destino);
			
			int custo;
			printf("Digite o custo entre da aresta: \n>");
			scanf("%d", &custo);
			
			InserirAresta(g, origem, destino, custo);
			printf("\n-----------------\n");
			printf("Aresta inserida\n");
			printf("-----------------\n");
		}else if(opcao == 2) {
			int origem;
			printf("\nDigite o vértice de origem: \n>");
			scanf("%d", &origem);
			
			int destino;
			printf("Digite o vértice de destino: \n>");
			scanf("%d", &destino);
			
			RemoverAresta(g,origem,destino);
			printf("\n-----------------\n");
			printf("Aresta removida\n");
			printf("-----------------\n");
			
		}else if(opcao == 3) {
			ImprimirGrafo(g, n);
		}else if(opcao == 4) {
			ImprimirGrausES(g, n);
		}else if(opcao == 5) {
			
			int ehCompleto;
			ehCompleto = VerificaGrafoCompleto(g, n);
			if(ehCompleto == 1) {
				printf("\n----------------------\n");
				printf("O grafo está completo\n");
				printf("----------------------\n");
			}else {
				printf("\n--------------------------\n");
				printf("O grafo não está completo\n");
				printf("--------------------------\n");
			}
		}
	
		printf("\n\n");
		system("pause");
		system("cls");
	}
	printf("O usuário saiu.\n");
	
	return 0;
}

