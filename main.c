#include <stdio.h>
#include <stdlib.h>

typedef struct disciplina{
	char codigo[5];
	char nome[100];
	int creditos;
} Disciplina;

typedef struct aluno{
	int ra;
	char nome[100];
	char login[10];
	char senha[10];
} Aluno;

Disciplina* leDisc();
int topD=5;

int main(){
	printf("Teste");
	Disciplina * d;
	d=leDisc();
	printf("%s,%s,%d",d[1].codigo,d[1].nome,d[1].creditos);
	return 0;	
}

Disciplina* leDisc(){
	FILE* fp = fopen("Disciplinas.txt","r");
	int top, i;
	fscanf(fp,"%d",&top);
	printf("%d",top);
	topD=top;
	Disciplina * aux;
	aux = (Disciplina*)malloc(sizeof(Disciplina)*top);
	for(i=0;i<top;i++)
	{
		fscanf(fp,"%s,%s,%d",aux[i].codigo,aux[i].nome,&aux[i].creditos);
	}
	fclose(fp);
	return aux;
}
