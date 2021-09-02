#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct pessoa{
	int tipo; // 1 - professor; 2 - aluno
	void *item; 	
}Pessoa;

typedef struct professor{
	int matricula;
	char nome[26];
	double salario;
}Professor;											 	
												
typedef struct aluno{
	int matricula;
	char nome[26];
	char curso[40];
	int anoDeIngresso;
}Aluno;

typedef struct lista{
	Pessoa *pessoa;
	struct lista *prox;
}Lista;

void ImprimeOpcoes() {
	printf("O que deseja fazer?\n");
	printf(" 1.Inserir uma pessoa no inicio na lista\n");
	printf(" 2.Remover uma pessoa pela matrícula\n");
	printf(" 3.Buscar uma pessoa pela matrícula e imprimir seus dados\n");
	printf(" 4.Contar o número de alunos de um determinado curso\n");
	printf(" 5.Imprimir os professores de maior salário\n");
	printf(" 6.Sair\n");
}

Lista *InsereNaLista(Lista *l, void *item, int tipo) {
	Pessoa *p= (Pessoa *)malloc(sizeof(Pessoa));
	p->tipo = tipo;
	p->item = item;
	
	Lista *aux =(Lista *)malloc(sizeof(Lista));
	aux->prox = l;
	aux->pessoa = p;
	
	return aux;
}

Aluno *CriaAluno(){
	int matricula, anoDeIngresso;
	char nome[26];
	char curso[40];
	
	printf("Digite a matrícula do(a) aluno(a): \n");
	scanf("%d", &matricula);
	printf("Digite o nome do(a) aluno(a):\n");
	fflush(stdin);
	scanf("%[^\n]s",nome);
	printf("Digite o curso do(a) aluno(a):\n");
	fflush(stdin);
	scanf("%[^\n]s",curso);
	printf("Digite o ano de ingresso:\n");
	scanf("%d",&anoDeIngresso);
	
	Aluno *a = (Aluno *)malloc(sizeof(Aluno));
	a->matricula = matricula;
	sscanf(nome, "%[^\n]s", a->nome);
	sscanf(curso, "%[^\n]s", a->curso);
	a->anoDeIngresso = anoDeIngresso;
	
	return a;
}

Professor *CriaProfessor() {
	int matricula;
	double salario;
	char nome[26];
	
	printf("Digite a matrícula do(a) professor(a):\n");
	scanf("%d", &matricula);
	printf("Digite o salário do(a) professorA:\n");
	scanf("%lf",&salario);
	printf("Digite o nome do(a) professor(a):\n");
	fflush(stdin);
	scanf("%[^\n]s",nome);
	
	Professor *p = (Professor *)malloc(sizeof(Professor));
	p->matricula = matricula;
	p->salario = salario;
	sscanf(nome,"%[^\n]s", p->nome);
	
	return p;
}

int VerificaMatricula(Pessoa *p, int matricula) {
	if(p->tipo == 1){
		Professor *prof = (Professor *)p->item;
		if(prof->matricula == matricula) 
			return 1;
		else
			return 0;	
	}else{
		Aluno *a = (Aluno *)p->item;
		if(a->matricula == matricula)
			return 1;
		else
			return 0;
	}
}

Lista *RemoverPessoa(Lista *l, int matricula) {
	Lista *aux = l->prox;
	Lista *auxAnt = l;
	
	if(VerificaMatricula(l->pessoa, matricula)){
		free(auxAnt->pessoa->item);
		free(auxAnt->pessoa);
		free(auxAnt);
		return aux;
	}
	
	while(aux != NULL) {
		if(VerificaMatricula(aux->pessoa, matricula)) {
			auxAnt->prox = aux->prox;
			free(aux->pessoa->item);
			free(aux->pessoa);
			free(aux);
			return l;
		}
		
		aux = aux->prox;
		auxAnt = auxAnt->prox;
	}
	      
	printf("\n-------------------------\nMatrícula não encontrada.\n-------------------------\n");
	return l;	
}

void *ImprimePessoaPelaMatricula(Lista *l, int matricula) {
	
	Lista *aux = l;
	
	int achou = 0;
		while(aux!= NULL) {
			if(VerificaMatricula(aux->pessoa, matricula)) {
				if(aux->pessoa->tipo == 1) {
					Professor *prof = (Professor *)aux->pessoa->item;
					printf("\n---- Professor(a) ----\n");
					printf(" Matricula: %d\n",prof->matricula);
					printf(" Nome: %s\n",prof->nome);
					printf(" Salário: %.2lf\n",prof->salario);
					printf("-----------------------\n");
					achou = 1;
				}else if(aux->pessoa->tipo == 2) {
					Aluno *aluno = (Aluno *)aux->pessoa->item;
					printf("\n------ Aluno(a) ------\n");
					printf(" Matricula: %d\n",aluno->matricula);
					printf(" Nome: %s\n",aluno->nome);
					printf(" Curso: %s\n",aluno->curso);
					printf(" Ano de ingresso: %d\n",aluno->anoDeIngresso);
					printf("-----------------------\n");
					achou = 1;
				}
			}
			aux = aux->prox;
		}
	
	if(!achou)	
		printf("\n-------------------------\nMatrícula não encontrada.\n-------------------------\n");
}

int NumeroAlunosNoCurso(Lista *l, char *curso) {
	Lista *aux = l;
	
	int contador = 0;
	while(aux != NULL) {
		if(aux->pessoa->tipo == 2) {
			Aluno *aluno = (Aluno *)aux->pessoa->item;
		
			if(!strcmp(aluno->curso,curso)) {
				contador++;
			}
		}
		aux = aux->prox;
	}
	
	return contador;
}

double MaiorSalario(Lista *l) {
	Lista *aux = l;
	
	double maior = 0.0;
	while(aux != NULL) {
		if(aux->pessoa->tipo == 1) {
			Professor *prof = (Professor *)aux->pessoa->item;
			if(prof->salario > maior)
				maior = prof->salario;
		}
		aux = aux->prox;
	}
	
	return maior;
}

void ImprimeProfMaiorSalario(Lista *l, double maiorSalario) {
	Lista *aux = l;
	
	
	printf("\n------ Professores com o salário de %.2lf ------\n", maiorSalario);
	while(aux != NULL) {
		if(aux->pessoa->tipo == 1) {
			Professor *prof = (Professor *)aux->pessoa->item;
			if(prof->salario == maiorSalario)
				printf(" %s\n", prof->nome);
		}
		aux = aux->prox;
	}
	
}

int main() {
	setlocale(LC_ALL, "");
	
	Lista *lista = NULL;
	
	int opcao;
	do{
		ImprimeOpcoes();
		scanf("%d", &opcao);
		
		if(opcao==1) //Inserir pessoa na lista
		{ 
			int tipo;
			printf("\nEscolha uma das opções:\n 1.Professor(a) 2.Aluno(a)\n >");
			scanf("%d", &tipo);
			if(tipo == 1) {	
				Professor *p;
				p = CriaProfessor();
				lista = InsereNaLista(lista, p, 1);
				printf("\n------------------\nProfessor(a) Inserido\n------------------\n");		
			}else if(tipo == 2) {
				Aluno *a;
				a = CriaAluno();
				lista = InsereNaLista(lista, a, 2);
				printf("\n--------------\nAluno(a) Inserido\n--------------\n");
				}
		}else if(opcao == 2) //Remover
		{
			int matricula;
			printf("Digite a matrícula que deseja remover:\n");
			scanf("%d",&matricula);
			lista = RemoverPessoa(lista, matricula);
			
		}else if(opcao == 3) //Imprimir dados
		{
			int matricula;
			printf("Digite a matrícula que deseja imprimir:\n");
			scanf("%d",&matricula);
			ImprimePessoaPelaMatricula(lista, matricula);
		}else if(opcao == 4) // numero de alunos de um curso
		{
			char curso[40];
			printf("Digite o nome do curso:\n");
			fflush(stdin);
			scanf("%[^\n]s",curso);
			int num = NumeroAlunosNoCurso(lista, curso);
			printf("\n-----------------------------------------------------\n");
			printf(" Têm %d alunos matriculados no curso %s.\n",num,curso);
			printf("-----------------------------------------------------\n");
			
		}else if(opcao == 5) 
		{
			double maiorSalario = MaiorSalario(lista);
			ImprimeProfMaiorSalario(lista, maiorSalario);	
		}
		
	}while(opcao != 6);
	
	
	return 0;
}
