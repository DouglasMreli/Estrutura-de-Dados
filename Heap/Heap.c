#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <math.h>

int totalElementos = 0;

int IndiceFilhoEsq(int x)
{
	int indice=(2*x)+1;
	if (x >= totalElementos || indice >= totalElementos)
	{
		return -1;
	}
	else
		return indice;
}

int IndiceFilhoDir(int x)
{
	int indice = (2 * x) + 2;
	if (x >= totalElementos || indice >= totalElementos)
	{
		return -1;
	}
	else
		return indice;
}

int IndicePai(int x)
{
	int indice = (int)floor((x - 1) / 2);
	if (x <= 0 || x > totalElementos)
	{
		return -1;
	}
	else
		return indice;
}

void AjustarSubindo(int *heap, int pos)
{
	if (pos != -1)
	{
		int pai = IndicePai(pos);
		if (pai != -1)
		{
			
			if (heap[pos] < heap[pai])
			{
				int aux = heap[pos];
				heap[pos] = heap[pai];
				heap[pai] = aux;
				AjustarSubindo(heap, pai);
			}
		}
	}
}

void Inserir(int *heap, int x)
{
	heap[totalElementos] = x;
	totalElementos++;

	AjustarSubindo(heap, totalElementos-1);
}

void AjustarDescendo(int *heap, int pos)
{
	if (pos != -1 && IndiceFilhoEsq(pos) != -1)
	{
		int indiceMenorFilho = IndiceFilhoEsq(pos);
		if (IndiceFilhoDir(pos) != -1 && heap[IndiceFilhoDir(pos)] < heap[indiceMenorFilho])
		{
			indiceMenorFilho = IndiceFilhoDir(pos);
		}

		if (heap[indiceMenorFilho] < heap[pos])
		{
			int aux = heap[pos];
			heap[pos] = heap[indiceMenorFilho];
			heap[indiceMenorFilho] = aux;
			AjustarDescendo(heap, indiceMenorFilho);
		}
	}
}

int Remover(int *heap) {
	if(totalElementos == 0)
		return -1;
	else {
		int retorno = heap[0];
		heap[0] = heap[totalElementos - 1];
		totalElementos--;
		AjustarDescendo(heap, 0);
		return retorno;
	}
}

int main(){
	setlocale(LC_ALL, "");
	
	int opcao=0;
	
	int heap[10];
	
	while(opcao!=4)
	{
		printf("O que deseja fazer?\n 1.Inserir elemento na heap\n 2.Remover elemento da heap\n 3.Imprimir heap\n 4.Sair\n>");
		scanf("%d", &opcao);
		printf("\n");
		
		if (opcao==1)//inserir elemento
		{
			int x; 
			printf("Digite o elemento que deseja inserir: \n");
			scanf("%d", &x);
			Inserir(heap, x);
			printf("\n--------------------\n");
			printf("Elemento %d inserido", x);
			printf("\n--------------------\n");
		}
		else if(opcao==2)//remover elemento
		{
			int removido = Remover(heap);
			printf("\n--------------------\n");
			printf("Elemento %d removido", removido);
			printf("\n--------------------\n");
			
		}
		else if(opcao==3)//imprimir heap
		{
			printf("\n----------------------------------\n");
			for(int i = 0; i < totalElementos; i++) {
				printf("- %d -", heap[i]);
			}
			printf("\n----------------------------------\n");
		}
		else if(opcao == 4) {
			break;
		}
		
		printf("\n\n");
		system("pause");
		system("cls");
	}
		
		printf("O usuário saiu!\n");
		
	return 0;
}


