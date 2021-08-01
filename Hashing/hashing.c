#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


typedef struct registro {
	
	int mat;
	char nome[20];
	char curso[50];
	int disponibilidade;
	
}Registro;

int hash(int key, int size) 
{
	return key % size;
}

void inicializar(char *nomeArq) 
{
	FILE *arq = fopen(nomeArq, "wb");
	Registro a;
	a.disponibilidade = 1;
	for(int i = 0; i < 15; i++) {
		fwrite(&a, sizeof(Registro), 1, arq);
	}
	
	fclose(arq);
}

int AcharPosicao(char *nomeArq, int mat)
{
	int N = 15;
	int pos = hash(mat, 15);

	Registro a;
	FILE *arq=fopen(nomeArq,"rb");
	fseek(arq, pos*sizeof(Registro),SEEK_SET);
	fread(&a,sizeof(Registro), 1, arq);

	while(a.disponibilidade == 0)
	{
		pos = (pos+1)%N;
		fseek(arq, pos*sizeof(Registro), SEEK_SET);
		fread(&a,sizeof(Registro), 1, arq);
	}
	
	fclose(arq);
	return pos;
}

void imprimirAluno(char *nomeArq, int mat) {
	
	int N = 15;
	FILE *arq = fopen(nomeArq,"rb");
	
	Registro a;
	int pos = hash(mat, N);
	
	fseek(arq, pos*sizeof(Registro),SEEK_SET);
	fread(&a,sizeof(Registro), 1, arq);
	if(a.disponibilidade == 0 && a.mat != mat) {
		while(a.disponibilidade != 1 || a.mat != mat) {
			pos = (pos + 1) % N;
			fseek(arq, pos*sizeof(Registro),SEEK_SET);
			fread(&a, sizeof(Registro), 1, arq);
		}
	}
	
	if(a.disponibilidade == 1) {
		printf("Esse matrícula não está no Hashing");
	} else {
		printf("\n\tInformações do Aluno:\n\n");
		printf("Matrícula: %d\n",a.mat);
		printf("Nome: %s \n",a.nome);
		printf("Curso: %s\n",a.curso);
	}
	
	fclose(arq);
	
}

void inserir(char *nomeArq, int mat, char *nome, char *curso) 
{
	int pos = AcharPosicao(nomeArq, mat);

	FILE *arq = fopen(nomeArq, "r+b");

	Registro a;
	a.mat = mat;
	strcpy(a.nome, nome);
	strcpy(a.curso, curso);
	a.disponibilidade = 0;

	fseek(arq, pos*sizeof(Registro), SEEK_SET);
	fwrite(&a, sizeof(Registro), 1, arq);
	

	fclose(arq);
}

void ImprimirHashing(char *nomeArq) {
	
	int N = 15;
	FILE *arq = fopen(nomeArq,"rb");
	
	Registro a;
	
	for(int pos = 0; pos < N; pos++) {
		fseek(arq, pos * sizeof(Registro), SEEK_SET);
		fread(&a, sizeof(Registro), 1, arq);
		if(a.disponibilidade == 0) {
			printf("\n\tInformações do Aluno:\n\n");
			printf("Matrícula: %d\n",a.mat);
			printf("Nome: %s \n",a.nome);
			printf("Curso: %s\n",a.curso);
		}
	}
	
	fclose(arq);
}

int main()
{
	setlocale(LC_ALL, "");
	
	int opcao = 0;
	int matricula;
	char nome[20];
	char curso[50];
	char arq[10] = "alunos.bin";
	
	inicializar(arq);
	
	while(opcao!=4)
	{
		printf("O que deseja fazer?\n 1.Inserir novo aluno\n 2.Imprimir as informações de um determinado aluno\n 3.Imprimir tabela Hash\n 4.Sair\n\n>");
		scanf("%d", &opcao);
		printf("\n");
		
		if (opcao == 1)//inserir novo aluno
		{
			printf("> Qual a matricula do aluno?\n");
			scanf("%d", &matricula);
	
			fflush(stdin);
			printf("> Qual o nome do aluno?\n");
			scanf("%[^\n]s", nome);
			fflush(stdin);
			
			printf("> Qual o curso do aluno?\n");
			scanf("%[^\n]s", curso);
			fflush(stdin);
			
			inserir(arq, matricula, nome, curso);
			
			printf("\n-------------\n");
			printf("Aluno Inserido");
			printf("\n-------------\n");
		}
		else if(opcao == 2)//imprimir info
		{
			int mat, pos;
			printf("> Qual o matrícula do aluno?\n");
			scanf("%d", &mat);
			
			printf("\n-------------------------------\n");
			imprimirAluno(arq, mat);
			printf("\n-------------------------------\n");
		}
		else if(opcao==3)//imprimir tabela de dispersao
		{
			printf("\n-------------------------------\n");
			ImprimirHashing(arq);
			printf("\n-------------------------------\n");
		}
		
		printf("\n\n");
		
		system("pause");
		system("cls");
	}
	printf("O usuário saiu!\n");

	return 0;
}

