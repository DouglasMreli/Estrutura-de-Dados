// Grupo: Ayla Rodrigues, Douglas Mareli, Sofia Kitaeva
// Exercicio 4 - Estrutura de dados

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

typedef struct avl{
	int info;
	int FB; // Fator de Balanceamento -> Altura da Sub arvore dir - Altura da sub arvore esq
	struct avl *esq;
	struct avl *dir;
}AVL;

AVL *LerArvore(FILE *arq, AVL *a);

int AlturaArvore(AVL *a);

void AjustarFB(AVL *a);

AVL *LerAVL(FILE *arq);

AVL *Destruir(AVL *a);

void ImprimirPreOrdem(AVL *a);
void ImprimirEmOrdem(AVL *a);
void NivelNo(AVL *a, int no, int nivel); //imprimir nivel de um no
void ImprimirPosOrdem(AVL *a);
void ImprimirNivel(AVL *a, int cont, int nivel); //impressao de todos os nós do nivel de um nó especifico
void ImprimirEmLargura(AVL *a, int nivel);

int Existe(AVL *a, int x); //verificar existencia de um numero x na arvore

void ImprimirMenores(AVL *a, int x);

AVL *RotacaoEsq(AVL *r);
AVL *RotacaoEsqSimples(AVL *r);
AVL *RotacaoEsqDupla(AVL *r);

AVL *RotacaoDir(AVL *r);
AVL *RotacaoDirSimples(AVL *r);
AVL *RotacaoDirDupla(AVL *r);

AVL *Inserir(AVL *r, int x, int *hMudou);
AVL *Remover(AVL *r, int x, int *hMudou);

int main(){
	setlocale(LC_ALL, "");
	
	FILE *arq;
	AVL *a;
	
	int hMudou = 0;
	int opcao=0;

	while(opcao!=8)
	{
		printf("O que deseja fazer?\n 1.Ler árvore\n 2.Imprimir árvore\n 3.Verificar existência de um elemento\n 4.Imprimir nível de um nó\n 5.Imprimir as folhas menores que um valor\n 6.Inserir um nó na árvore\n 7.Remover um nó da árvore\n 8.Sair\n>");
		scanf("%d", &opcao);
		printf("\n");
		
		if (opcao==1)//leitua da arvore
		{
			char arv[100]; 
			printf("Qual árvore deseja ler?\n>");
			scanf("%s", arv);
			arq = fopen(arv, "rt");
			printf("-----------\n");
			printf("Árvore Lida\n");
			printf("-----------\n");
			a = LerAVL(arq);
		}
		else if(opcao==2)//impressao arvore
		{
			int escolha=0;
			printf("Como deseja que seja feita a impressão da árvore?\n 1.Pré-Ordem\n 2.Em-Ordem\n 3.Pós-Ordem\n 4.Em largura\n");
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
			printf("Qual o número que deseja verificar na árvore?\n");
			scanf("%d", &x);
			x = Existe(a, x);

			if (x==1){
				printf("----------------------------\n");
				printf("Esse número existe na árvore\n");
				printf("----------------------------\n");
			}
			else{
				printf("--------------------------------\n");
				printf("Esse número não existe na árvore\n");
				printf("--------------------------------\n");
			}
		}
		else if (opcao==4)//imprimir nível de nó
		{
			int no;
			printf("De qual nó você deseja imprimir o nível?\n");
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
		else if(opcao==6)//inserir nó
		{
			int x;
			printf("Qual elemento você deseja inserir?\n");
			scanf("%d",&x);
			a = Inserir(a, x, &hMudou);
			printf("-----------------\nElemento Inserido\n-----------------\n");
		}
		else if(opcao==7)//remover nó
		{
			int rem;
			printf("Qual nó deseja remover?\n>");
			scanf("%d", &rem);
			printf("-----------\n");
			a = Remover(a, rem, &hMudou);
			printf("Nó Removido\n");
			printf("-----------\n");
		}
		
		printf("\n");
		system("pause");
		system("cls");
	}
		a = Destruir(a);
		printf("O usuário saiu!\n");
		fclose(arq);
	return 0;
}

AVL *LerArvore(FILE *arq, AVL *a){
	char c;
	int num;
	
	fscanf(arq, "%c", &c);
	fscanf(arq, "%d", &num);
	if(num == -1) {
		fscanf(arq, "%c", &c);
		return NULL;
	} else {
		a = (AVL*)malloc(sizeof(AVL));
		a->info = num;
		a->esq = LerArvore(arq, a);
		a->dir = LerArvore(arq, a);
		fscanf(arq, "%c", &c);
		return a;
	}
}

int AlturaArvore(AVL *a){
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

void AjustarFB(AVL *a) {
	if(a != NULL) {
		int he = AlturaArvore(a->esq);
		int hd = AlturaArvore(a->dir);
		a->FB = hd - he;
		AjustarFB(a->esq);
		AjustarFB(a->dir);
	}
}

AVL *LerAVL(FILE *arq){
	AVL *a = LerArvore(arq, a);
	AjustarFB(a);
	AjustarFB(a);
	return a;
}

AVL *Destruir(AVL *a){
	if (a!=NULL)
	{
		a->esq = Destruir(a->esq);
		a->dir = Destruir(a->dir);
		free(a);
	}
	return NULL;
}

void ImprimirPreOrdem(AVL *a){ //impressao pre ordem
	if(a != NULL) 
	{
		printf("%d\n", a->info);
		ImprimirPreOrdem(a->esq);
		ImprimirPreOrdem(a->dir);
	}	
}

void ImprimirEmOrdem(AVL *a){ //impressao em ordem
	if (a != NULL)
	{
		ImprimirEmOrdem(a->esq);
		printf("%d\n", a->info);
		ImprimirEmOrdem(a->dir);
	}
}

void NivelNo(AVL *a, int no, int nivel) 
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

void ImprimirPosOrdem(AVL *a){ //impressao pos ordem
	if (a != NULL)
	{
		ImprimirPosOrdem(a->esq);
		ImprimirPosOrdem(a->dir);
		printf("%d\n", a->info);
	}
}

void ImprimirEmLargura(AVL *a, int nivel)//impressao em largura
{
	int h = AlturaArvore(a);
	if(nivel != h) {
		ImprimirNivel(a,0,nivel);
		printf("\n");
		ImprimirEmLargura(a,nivel+1);
	}
}

void ImprimirNivel(AVL *a, int cont, int nivel)
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

int Existe(AVL *a, int x)
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

void ImprimirMenores(AVL *a, int x)
{
	if (a!=NULL)
	{
		if(a->info < x) {
			if (a->esq == NULL && a->dir == NULL)
			{
				printf("%d\n", a->info);
			}
			
			ImprimirMenores(a->esq, x);
			ImprimirMenores(a->dir, x);
			
		} else {
			ImprimirMenores(a->esq, x);
		}
	}
}

AVL *RotacaoEsq(AVL *r){
	if(r->dir->FB == -1) {
		r = RotacaoEsqDupla(r);
	} else { 
		r = RotacaoEsqSimples(r);
	}
	
	return r;
}

AVL *RotacaoEsqSimples(AVL *r){
	AVL *a = r;
	AVL *b = a->dir;
	
	a->dir = b->esq;
	b->esq = a;
	
	if(b->FB == 1) {
		a->FB = 0;
		b->FB = 0;
	} else {
		a->FB = 1;
		b->FB = -1;
	}
	r = b;
	
	return r;
}

AVL *RotacaoEsqDupla(AVL *r){
	AVL *a = r;
	AVL *c = a->dir;
	AVL *b = c->esq;
	
	c->esq = b->dir;
	a->dir = b->esq;
	b->esq = a;
	b->dir = c;
	
	switch(b->FB) {
		case -1: a->FB = 0; c->FB = 1;
			break;
		case 0: a->FB = 0; c->FB = 0;
			break;
		case +1: a->FB = -1; c->FB = 0;
			break;
	}
	b->FB = 0;
	r = b;
	
	return r;
}

AVL *RotacaoDir(AVL *r) {
	if(r->esq->FB == 1) {
		r = RotacaoDirDupla(r);
	} else {
		r = RotacaoDirSimples(r);
	}
	
	return r;
}

AVL *RotacaoDirSimples(AVL *r) {
	AVL *a = r->esq;
	AVL *b = r;
	
	b->esq = a->dir;
	a->dir = b;
	if(a->FB == -1) {
		a->FB = 0;
		b->FB = 0;
	} else {
		a->FB = 1;
		a->FB = -1;
	}
	r=a;
	
	return r;
}

AVL *RotacaoDirDupla(AVL *r) {
	AVL *c = r;
	AVL *a = c->esq;
	AVL *b = a->dir;
	
	c->esq = b->dir;
	a->dir = b->esq;
	b->esq = a;
	b->dir = c;
	
	//setando os valores dos FB's de acordo com o FB raiz
	switch(b->FB) {
		case -1: a->FB = 0; c->FB = 1;
			break;
		case 0: a->FB = 0; c->FB = 0;
			break;
		case +1: a->FB = -1; c->FB = 0;
			break;
	}
	b->FB = 0;
	r = b;
	
	return r;
}

AVL *Inserir(AVL *r, int x, int *hMudou) {
	if(r == NULL) {
		r = (AVL *)malloc(sizeof(AVL));
		r->info = x;
		r->esq = NULL;
		r->dir = NULL;
		r->FB = 0;
		*hMudou = 1;
	} else {
		if(x <= r->info) {
			r->esq = Inserir(r->esq, x, hMudou);
			if(*hMudou == 1) {
				switch(r->FB) {
					case -1: r = RotacaoDir(r); *hMudou = 0;
						break;
					case 0 : r->FB = -1; *hMudou = 1;
						break;
					case +1: r->FB = 0; *hMudou = 0;
						break;
				}
			}
		} else {
			r->dir = Inserir(r->dir, x, hMudou);
				if(*hMudou == 1) {
					switch(r->FB) {
						case -1: r->FB = 0; *hMudou + 0;
							break;
						case 0: r->FB = 1; *hMudou = 1;
							break;
						case +1: r = RotacaoEsq(r); *hMudou = 0;
							break;
					}
				}
			}
		}
	
	return r;
}

AVL *Remover(AVL *r, int x, int *hMudou) {
	if(r != NULL) {
		if(r->info == x) {
			if(r->esq == NULL && r->dir == NULL) {
				free(r);
				*hMudou = 1;
				return NULL;
			} else if(r->esq == NULL || r->dir == NULL) {
				AVL *aux;
				if(r->esq == NULL) {
					aux = r->dir;
				} else {
					aux = r->esq;
				}
				free(r);
				*hMudou = 1;
				return aux;
			} else {
				AVL *maiorEsq = r->esq;
				while(maiorEsq->dir != NULL) {
					maiorEsq = maiorEsq->dir;
				}
				r->info = maiorEsq->info;
				r->esq = Remover(r->esq, r->info, hMudou);
				
				if(*hMudou == 1) {
					switch(r->FB) {
						case -1: r->FB = 0; *hMudou = 1; 
							break;
						case 0: r->FB = 0; *hMudou = 0;
							break;
						case +1: {
							int aux = r->dir->FB;
							r = RotacaoEsq(r);
							if(aux == 0) {
								*hMudou = 0;
							} else {
								*hMudou = 1;
							}
							break;
						}
					}
				}
			}
		} else if(x < r->info) {
			r->esq = Remover(r->esq, x, hMudou);
			
			if(*hMudou == 1) {
				switch(r->FB) {
					case -1: r->FB = 0; *hMudou = 1;
						break;
					case 0: r->FB = 1; *hMudou = 0; 
						break;
					case 1: {
						int aux = r->dir->FB;
						r = RotacaoEsq(r);
						if(aux == 0) {
							*hMudou = 0;
						}else {
							*hMudou = 1;
						}
						break;
					}
				}
			}
		} else {
			r->dir = Remover(r->dir, x, hMudou);
			
			if(*hMudou == 1) {
				switch(r->FB) {
					case +1: r->FB = 0; *hMudou = 1;
						break;
					case 0: r->FB = -1; *hMudou = 0;
						break;
					case -1: {
						int aux = r->esq->FB;
						r = RotacaoDir(r);
						if(aux == 0) {
							*hMudou = 0;
						} else {
							*hMudou = 1;
						}
						break;
					}
				}
			}
		}
	}
	
	return r;
}
