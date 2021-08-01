// Grupo: Ayla Rodrigues, Douglas Mareli, Sofia Kitaeva
// Exercicio 3 - Estrutura de dados

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
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

void ImprimirPreOrdem(arvore *a){ //impressao pre ordem
	if(a != NULL) 
	{
		printf("%d\n", a->info);
		ImprimirPreOrdem(a->esq);
		ImprimirPreOrdem(a->dir);
	}	
}

void ImprimirEmOrdem(arvore *a){ //impressao em ordem
	if (a != NULL)
	{
		ImprimirEmOrdem(a->esq);
		printf("%d\n", a->info);
		ImprimirEmOrdem(a->dir);
	}
}

int AlturaArvore(arvore *a){
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
			printf("%d ", a->info);
		}
		else
		{
			ImprimirNivel(a-> esq, cont+1, nivel);
			ImprimirNivel(a-> dir, cont+1, nivel);
		}
	}
}

void ImprimirEmLargura(arvore *a, int nivel)//impressao em largura
{
	int h = AlturaArvore(a);
	if(nivel != h) {
		ImprimirNivel(a,0,nivel);
		printf("\n");
		ImprimirEmLargura(a,nivel+1);
	}
}				
		
void ImprimirPosOrdem(arvore *a){ //impressao pos ordem
	if (a != NULL)
	{
		ImprimirPosOrdem(a->esq);
		ImprimirPosOrdem(a->dir);
		printf("%d\n", a->info);
	}
}

int Existe(arvore *a, int x)//verificar existencia de um numero x na arvore
{
	if (a==NULL){
		return 0;
	}
	else if (a->info ==x){
		return 1;
	}
	else if(x<a->info)
		return Existe(a->esq, x);
	else
		return Existe(a->dir, x);
}

void NivelNo(arvore *a, int no, int nivel) //imprimir nivel de um no
 {
	if(a != NULL) {
		if(a->info == no){
			printf("%d\n",nivel);
		}
		else if(a->info>no)
			NivelNo(a->esq, no, nivel+1);
		else
			NivelNo(a->dir, no, nivel+1);
	}
}

void ImprimirMenores(arvore *a, int x)
{
	if (a!=NULL)
	{
		if (a->info < x)
		{
			printf("%d\n", a->info);
			ImprimirMenores(a->esq, x);
			ImprimirMenores(a->dir, x);
		}
		else
			ImprimirMenores(a->esq, x);
	}
}

arvore *Inserir(arvore *a, int x) {
	if(a == NULL) {
		a = (arvore*)malloc(sizeof(arvore));
		a->info = x;
		a->esq = NULL;
		a->dir = NULL;
	} else if(x <= a->info) {
		a->esq = Inserir(a->esq, x);
	} else {
		a->dir = Inserir(a->dir, x);
	}
	return a;
}

arvore *Remover(arvore *a, int x){
	if(a!=NULL)
		if(a->info==x)
			if(a->dir==NULL && a->esq==NULL){
				free(a);
				return NULL;
			}
			else if(a->esq==NULL){
				arvore *aux=a->dir;
				free(a);
				return aux;
			}
			else if(a->dir==NULL){
				arvore *aux=a->esq;
				free(a);
				return aux;
			}
		else{
			arvore *aux=a->esq;
			while(aux->dir!=NULL)
				aux=aux->dir;
			a->info=aux->info;
			a->esq=Remover(a->esq, aux->info);
		}
		else if(x<a->info)
			a->esq=Remover(a->esq, x);
		else
			a->dir=Remover(a->dir, x);
	return a;
}

arvore *Destruir(arvore *a){
	if (a!=NULL)
	{
		a->esq = Destruir(a->esq);
		a->dir = Destruir(a->dir);
		free(a);
	}
	return NULL;
}

int main(){
	setlocale(LC_ALL, "");
	
	FILE *arq;
	arvore *a;
	
	int opcao=0;

	while(opcao!=8)
	{
		printf("O que deseja fazer?\n 1.Ler �rvore\n 2.Imprimir �rvore\n 3.Verificar exist�ncia de um elemento\n 4.Imprimir n�vel de um n�\n 5.Imprimir as folhas menores que um valor\n 6.Inserir um n� na �rvore\n 7.Remover um n� da �rvore\n 8.Sair\n>");
		scanf("%d", &opcao);
		printf("\n");
		
		if (opcao==1)//leitua da arvore
		{
			char arv[100]; 
			printf("Qual �rvore deseja ler?\n>");
			scanf("%s", arv);
			arq = fopen(arv, "rt");
			printf("-----------\n");
			printf("�rvore Lida\n");
			printf("-----------\n");
			a = LerArvore(arq, a);
		}
		else if(opcao==2)//impressao arvore
		{
			int escolha=0;
			printf("Como deseja que seja feita a impress�o da �rvore?\n 1.Pr�-Ordem\n 2.Em-Ordem\n 3.P�s-Ordem\n 4.Em largura\n");
			scanf("%d", &escolha);
			if (escolha==1){
				printf("----------\n");
				ImprimirPreOrdem(a);
				printf("----------");
				printf("\n\n");
			}
			else if (escolha==2){
				printf("----------\n");
				ImprimirEmOrdem(a);
				printf("----------");
				printf("\n\n");
			}
			else if (escolha ==3){
				printf("----------\n");
				ImprimirPosOrdem(a);
				printf("----------");
				printf("\n\n");
			}
			else{
				printf("----------\n");
				ImprimirEmLargura(a, 0);
				printf("----------");
				printf("\n\n");
			}
			
		}
		else if(opcao==3)//verificar existencia
		{
			int x;
			printf("Qual o n�mero que deseja verificar na �rvore?\n");
			scanf("%d", &x);
			x = Existe(a, x);

			if (x==1){
				printf("----------------------------\n");
				printf("Esse n�mero existe na �rvore\n");
				printf("----------------------------\n");
			}
			else{
				printf("--------------------------------\n");
				printf("Esse n�mero n�o existe na �rvore\n");
				printf("--------------------------------\n");
			}
		}
		else if (opcao==4)//imprimir n�vel de n�
		{
			int no;
			printf("De qual n� voc� deseja imprimir o n�vel?\n");
			scanf("%d",&no);
			printf("\n----------\n");
			NivelNo(a,no,0);
			printf("----------\n");
		}
		else if(opcao==5)//imprimir folhas menores q x 
		{
			int x;
			printf("Qual o valor de x?\n");
			scanf("%d", &x);
			printf("----------\n");
			ImprimirMenores(a, x);
			printf("----------\n");
		}
		else if(opcao==6)//inserir n�
		{
			int x;
			printf("Qual elemento voc� deseja inserir?\n");
			scanf("%d",&x);
			a = Inserir(a, x);
			printf("-----------------\nElemento Inserido\n-----------------\n");
		}
		else if(opcao==7)//remover n�
		{
			int rem;
			printf("Qual n� deseja remover?\n>");
			scanf("%d", &rem);
			printf("-----------\n");
			printf("N� Removido\n");
			Remover(a, rem);
			printf("-----------\n");
		}
		
		Sleep(5000);
		system("cls");
	}
		a = Destruir(a);
		printf("O usu�rio saiu!\n");
		fclose(arq);
	return 0;
}

