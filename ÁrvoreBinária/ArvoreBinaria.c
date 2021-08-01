// Grupo: Ayla Rodrigues, Douglas Mareli, Sofia Kitaeva
// Exercicio 2 - Estrutura de dados

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <Windows.h>

typedef struct arvore{
	int info;
	struct arvore *esq;
	struct arvore *dir;
}arvore;

arvore *LerArvore(FILE *arq, arvore *a){
	char c;
	int num;
	
	fscanf(arq, "%c", &c);
	fscanf(arq, "%d", &num);
	if(num == -1) {
		fscanf(arq, "%c", &c);
		return NULL;
	} else {
		a = (arvore*)malloc(sizeof(arvore));
		a->info = num;
		a->esq = LerArvore(arq, a);
		a->dir = LerArvore(arq, a);
		fscanf(arq, "%c", &c);
		return a;
	}
}

int AlturaArvore(arvore *a)
{
	if (a == NULL)
	{
		return 0;
	}
	else
	{
		int he, hd;
		he=AlturaArvore(a->esq);
		hd=AlturaArvore(a->dir);

		if (he>hd)
		{
			return he+1;
		}
		else
			return hd+1;
	}
}

void ImprimirNivel(arvore *a, int cont, int nivel)//impressao de nivel do no
{
	if (a!= NULL)
	{
		if (cont==nivel)
		{
			printf("%d\n", a->info);
		}
		else
		{
			ImprimirNivel(a-> esq, cont+1, nivel);
			ImprimirNivel(a-> dir, cont+1, nivel);
		}
	}
}

void ImprimirPreOrdem(arvore *a)//impressao pre ordem
{
	if(a != NULL) 
	{
		printf("%d\n", a->info);
		ImprimirPreOrdem(a->esq);
		ImprimirPreOrdem(a->dir);
	}	
}

void ImprimirEmOrdem(arvore *a)//impressao em ordem
{
	if (a != NULL)
	{
		ImprimirEmOrdem(a->esq);
		printf("%d\n", a->info);
		ImprimirEmOrdem(a->dir);
	}
}

void ImprimirEmLargura(arvore *a, int nivel)//impressao pos ordem
{
	int h = AlturaArvore(a);
	if(nivel != h) {
		ImprimirNivel(a,0,nivel);
		ImprimirEmLargura(a,nivel+1);
	}
}				
		
void ImprimirPosOrdem(arvore *a)//impressao pos ordem
{
	if (a != NULL)
	{
		ImprimirPosOrdem(a->esq);
		ImprimirPosOrdem(a->dir);
		printf("%d\n", a->info);
	}
}

void ImprimirFolhas(arvore *a) {
	if(a != NULL){
		if(a->esq == NULL && a->dir == NULL) {
			printf("%d\n",a->info);
		}
		
		ImprimirFolhas(a->esq);
		ImprimirFolhas(a->dir);
	}
}

void NivelNo(arvore *a, int no, int nivel) //imprimir nivel de um no
 {
	if(a != NULL) {
		if(a->info == no) {
			printf("%d\n",nivel);
		} else {
			NivelNo(a->esq, no ,nivel + 1);
			NivelNo(a->dir, no, nivel + 1);
		}
	}
}		

int Existe(arvore *a, int x)//verificar existencia de um numero x na arvore
{
	if (a==NULL)
	{
		return 0;
	}
	else if (a->info ==x)
	{
		return 1;
	}
	else
	{
		int ret = Existe(a->esq, x);
		if (ret ==1)
		{
			return 1;
		}
		return Existe(a->dir, x);
	}
}

arvore *Destruir(arvore *a)//liberar a memoria da arvore e destrui-la
{
	if (a!=NULL)
	{
		a->esq = Destruir(a->esq);
		a->dir = Destruir(a->dir);
		free(a);
	}
	return NULL;
}

int ContarElementos(arvore *a)//contar quantos elementos tem na arvore, tem que colocar recursiva
{
    if (a == NULL)
    {
        return 0;
    } else {
        return ContarElementos(a->esq) + ContarElementos(a->dir) + 1;
    }
}

int VerificaBalanceamento(arvore *a){
	
	int hEsq,hDir;
	
	if(a != NULL) {
		hEsq = AlturaArvore(a->esq);
		hDir = AlturaArvore(a->dir);
		if(abs(hEsq - hDir) == 1 || abs(hEsq - hDir ==0)) {
			return 0 + VerificaBalanceamento(a->esq) + VerificaBalanceamento(a->dir);
		} else {
			return 1;
		}	
	}
}

void VerificarCheia(arvore *a) {
	int numElem = ContarElementos(a);
	int h = AlturaArvore(a);

	if( numElem == pow(2, h)- 1) {
		printf("Essa árvore está cheia.\n");
	} else {
		printf("Essa árvore não está cheia.\n");
	}
}

int main() {
	setlocale(LC_ALL, "");
	
	FILE *arq;
	arvore *a;

	arq = fopen("arvore.txt", "rt");
	
	int opcao=0;

	while(opcao!=9)
	{
		printf("O que deseja fazer?\n 1.Ler árvore\n 2.Imprimir árvore\n 3.Verificar existência de um elemento\n 4.Contar número de elementos\n 5.Imprimir os nós-folha da árvore\n 6.Verificar balanceamento da árvore\n 7.Verificar se a árvore é cheia\n 8.Imprimir nivel de um nó\n 9.Sair\n");
		scanf("%d", &opcao);
		printf("\n");
		
		if (opcao==1)//leitua da arvore
		{
			printf("-----------\n");
			printf("Árvore Lida\n");
			printf("-----------\n");
			a = LerArvore(arq, a);
		}
		else if(opcao==2)//impressao arvore
		{
			int escolha=0;
			printf("Como deseja que seja feita a impressão da árvore?\n 1.Pré-Ordem\n 2.Em-Ordem\n 3.Pós-Ordem\n 4.Em largura\n");
			scanf("%d", &escolha);
			if (escolha==1)
			{
				printf("----------\n");
				ImprimirPreOrdem(a);
				printf("----------");
				printf("\n\n");
			}
			else if (escolha==2)
			{
				printf("----------\n");
				ImprimirEmOrdem(a);
				printf("----------");
				printf("\n\n");
			}
			else if (escolha ==3)
			{
				printf("----------\n");
				ImprimirPosOrdem(a);
				printf("----------");
				printf("\n\n");
			}
			else
			{
				printf("----------\n");
				ImprimirEmLargura(a,0);
				printf("----------");
				printf("\n\n");
			}
			
		}
		else if(opcao==3)//verificar existencia
		{
			int x;
			printf("Qual o número que deseja verificar na árvore?\n");
			scanf("%d", &x);
			x = Existe(a, x);

			if (x==1)
			{
				printf("----------------------------\n");
				printf("Esse número existe na árvore\n");
				printf("----------------------------\n");
			}
			else
			{
				printf("--------------------------------\n");
				printf("Esse número não existe na árvore\n");
				printf("--------------------------------\n");
			}
		}
		else if (opcao==4)//contar quant. elementos
		{
			int numElementos = ContarElementos(a);
			printf("-------------------------\n");
			printf("A árvore tem %d elementos\n", numElementos);
			printf("-------------------------\n");
		}
		else if(opcao==5)//imprimir nos folhas 
		{
			printf("----------\n");
			ImprimirFolhas(a);
			printf("----------\n");
		}
		else if(opcao==6)//verificar balanceamento
		{
			int balanc = VerificaBalanceamento(a);
			if(balanc ==0) {
				printf("------------------------\n");
				printf("A árvore está balanceada.\n");
				printf("------------------------\n");
			}else {
				printf("----------------------------\n");
				printf("A árvore não está balanceada.\n");
				printf("----------------------------\n");
			}
		}
		else if(opcao==7)//verificar se é cheia
		{
			printf("--------------------------\n");
			VerificarCheia(a);
			printf("--------------------------\n");
		}
		else if(opcao==8)//imprimir nivel de um no
		{
			int no;
			printf("De qual nó você deseja imprimir o nível?\n");
			scanf("%d",&no);
			printf("\n----------\n");
			NivelNo(a,no,0);
			printf("----------\n");
		}
		
		Sleep(2500);
		system("cls");
	}
		a = Destruir(a);
		printf("O usuário saiu!\n");
		fclose(arq);
	return 0;
}

