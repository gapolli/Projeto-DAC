/*
PROJETO FINAL SI200A
GRUPO 05
Andrey Toshiro Okamura 213119
Max ...
Gustavo...
bom noitarde
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>


//codigo de disciplina apenas maiusculo. ex.: SI100





/*
ESTRUTURAS
*/
typedef struct disciplina{//formato "EB101,C�lculo I,6", "codigo,nome,creditos"
	int topD;
	char codigo[5];
	char nome[100];
	int creditos;
} Disciplina;

typedef struct prerequisito{ //formato "SI200,SI100", "cod disciplina,cod prerequisito"
	int topP;
	char codDisc[5];
	char codPrereq[5];
} Prereq;

typedef struct aluno{ //formato "111111,Andrey,andrey,andrey", "ra,nome,login,senha"
	int topA;
	int ra;
	char nome[100];
	char login[10];	//obs.: para padronizacao, definimos o maximo para 10 (pode ser mudado a qualquer hora)
	char senha[10];
} Aluno;
typedef struct vetprereq{
	char codigo[5];
} Vetprereq;

typedef struct alunodisc{//RA,C�digodaDisciplina,Semestre,Nota,Faltas
	int ra;
	char codigo[5];
	int semestre;
	int nota;
	int faltas;
}Alunodisc;




//char vetprereq[43][5];
/*
PROTOTIPOS
*/
Disciplina* leDisc();//le  todas as disciplinas
Disciplina* leDisc2();
Prereq* lePrereq();	//le  todos os pre requisitos
Aluno* leAluno();	//le todos os alunos
void newAluno();	//cria novo aluno; pede os dados e escreve no arquivo (append para apenas adicionar no final)//ou pode dar realloc, e salva ao sair
void saveAluno(Aluno novo, Aluno alunos);	//funcao usada imediatamente apos newAluno, libera a antiga memoria de Alunos e cria uma struct atualizada(?.. solucao imediata, ha possiveis otimizacoes) por causa do malloc

int login(Aluno *user);

void consultaDisc();
void exibePrereq(Disciplina d);

/*
VARIAVEIS GLOBAIS
*/
//teste inicial com 5
int topD=5;//31, numero total de disciplinas /*NUMERO FIXO, NAO ALTERAR O ARQUIVO!*/ //ps.: estamos fazendo fixo, supondo que o arquivo nao sera alterado manualmente
int topP=43;//43, o mesmo que anterior, arquivo apenas para leitura! nao alterar por favor
int topVP=0;
	Disciplina * d;
	Disciplina * d2;
	Prereq * p;
	Aluno * a;
	Alunodisc * ad;
int logra;

int main(){
	int i;
	int op;
	//Disciplina * d;
	//Prereq * p;
	//Aluno * a;

	d=leDisc();
	d2=leDisc2();
	p=lePrereq();
	a=leAluno();
	ad=leAlunodisc();
//	printf("%s,%s,%d",d[0].codigo,d[0].nome,d[0].creditos);


    int erro; //variável que identifica se tudo ocorreu bem em funções que forem chamadas

    do{ //laço que repete o login até o usuário entrar com as credenciais corretas
        erro = login(a); //chamando a função de login
    }while(erro != 0);
    printf("login realizado com sucesso\n");

	printf("1: Cadastro de Alunos\n");
	printf("2: Consulta de Disciplinas\n");
	printf("3: Realizar Matricula\n");
	printf("4: Atualizar Nota e Falta\n");
	
	printf("0: Sair\n");
	scanf("%d",&op);
	
	switch(op){
		
		case 1:
			break;
		
		case 2:
			consultaDisc();
			break;
		case 3:
			break;
		case 4:
			break;
		case 0:
			break;
			
		default:
			break;	
	}
	
	return 0;
}


/*
FUNCOES
*/
Disciplina* leDisc2(){
	FILE* fp = fopen("Disciplinas.txt","r");
	
	int top, i;

	Disciplina * aux;
	aux = (Disciplina*)malloc(sizeof(Disciplina)*topD);
	for(i=0;i<topD;i++)
	{
	fscanf(fp, "%[^,], %[^,], %d", aux[i].codigo, aux[i].nome, &aux[i].creditos);
	
		//printf("codigo:%s\n",aux[i].codigo);
		//printf("nome:%s\n",aux[i].nome);
		//printf("creditos:%d\n",aux[i].creditos);
	}
	fclose(fp);
	return aux;
}

Disciplina* leDisc(){
	FILE* fp = fopen("Disciplinas.txt","r");
	char aseparar[100];
	int top, i;
	char *cod, *nom, *cred; //codigo, nome, credito temporario
	char *saveptr;
	//fscanf(fp,"%d",&top);
	//printf("%d",top);
	//topD=top;
	Disciplina * aux;
	aux = (Disciplina*)malloc(sizeof(Disciplina)*topD);
	for(i=0;i<topD;i++)
	{
		//fscanf(fp,"%s,%s,%d",aux[i].codigo,aux[i].nome,&aux[i].creditos);
		fgets(aseparar,100,fp);
		//printf("%s",aseparar);

		cod = strtok_r(aseparar, ",", &saveptr);

		nom = strtok_r(NULL, ",", &saveptr);

		cred = strtok_r(NULL, "\n", &saveptr);


		//printf("Direto do strtok, na variavel:\n");
		//printf("codigo:%s\n",cod);
		//printf("nome:%s\n",nom);
		//printf("creditos:%s\n",cred);

		fflush(stdin);
		
		strcpy(aux[i].codigo,cod);
		strcpy(aux[i].nome,nom);
		aux[i].creditos=atoi(cred);

		fflush(stdin);
	
		//printf("Depois de strcpy, pela struct:\n");
		//printf("codigo:%s\n",aux[i].codigo);
		//printf("nome:%s\n",aux[i].nome);
		//printf("creditos:%d\n",aux[i].creditos);

//		printf("\n");
	}
	fclose(fp);
	return aux;
}


Prereq* lePrereq(){
	FILE* fp = fopen("Prerequisitos.txt","r");
	char aseparar[100];
	int top, i;
	char *codDisc, *codPrereq; //codigo da disciplina,codigo do prerequisito temporario
	char *saveptr;

	Prereq * aux;
	aux = (Prereq*)malloc(sizeof(Prereq)*topP);
	for(i=0;i<topP;i++)
	{
		fgets(aseparar,100,fp);

		codDisc = strtok_r(aseparar, ",", &saveptr);
		codPrereq = strtok_r(NULL, "\n", &saveptr);

	//	printf("Direto do strtok, na variavel:\n");
//		printf("codigo disciplina:%s\n",codDisc);
//		printf("codigo prerequisito:%s\n",codPrereq);

		strcpy(aux[i].codDisc,codDisc);
		strcpy(aux[i].codPrereq,codPrereq);

//		printf("Depois de strcpy, pela struct:\n");
//		printf("codigo disciplina:%s\n",aux[i].codDisc);
//		printf("codigo prerequisito:%s\n",aux[i].codPrereq);

//		printf("\n");
	}
	fclose(fp);
	return aux;
}
Aluno* leAluno(){
	FILE* fp = fopen("Alunos.txt","r");
	char aseparar[100];
	int top, i;
	char *ra, *nom, *log, *sen; //codigo, nome, credito temporario
	char *saveptr;
	//fscanf(fp,"%d",&top);
	//printf("%d\n",top);
	top=3;
	Aluno * aux;
	aux = (Aluno*)malloc(sizeof(Aluno)*top);
	for(i=0;i<top;i++)
	{
		//fscanf(fp,"%s,%s,%d",aux[i].codigo,aux[i].nome,&aux[i].creditos);
		fgets(aseparar,100,fp);
		//printf("%s",aseparar);

		ra = strtok_r(aseparar, ",", &saveptr);
		nom = strtok_r(NULL, ",", &saveptr);
		log = strtok_r(NULL, ",", &saveptr);
		sen = strtok_r(NULL, "\n", &saveptr);

//		printf("Direto do strtok, na variavel:\n");
//		printf("RA:%s\n",ra);
//		printf("nome:%s\n",nom);
//		printf("login:%s\n",log);
//		printf("senha:%s\n",sen);//estamos exibindo a senha APENAS PARA TESTES

		aux[i].ra=atoi(ra);
		strcpy(aux[i].nome,nom);
		strcpy(aux[i].login,log);
		strcpy(aux[i].senha,sen);

//		printf("Depois de strcpy, pela struct:\n");
//		printf("RA:%d\n",aux[i].ra);
//		printf("nome:%s\n",aux[i].nome);
//		printf("login:%s\n",aux[i].login);
//		printf("senha:%s\n",aux[i].senha);

//		printf("\n");
	}
	fclose(fp);
	return aux;
}

Alunodisc* leAlunodisc(){
	FILE* fp = fopen("AlunosDisciplinas.txt","r");
	char aseparar[100];
	int top, i;
	char *ra, *cod, *sem, *notas, *fal; //codigo, nome, credito temporario
	char *saveptr;
	//fscanf(fp,"%d",&top);
	//printf("%d",top);
	//topD=top;
	Alunodisc * aux;
	aux = (Alunodisc*)malloc(sizeof(Alunodisc));
	i=1;
	//for(i=0;i<1;i++)
	while(aseparar!=NULL)
	{
		realloc(aux,sizeof(aux)*i);
		
		fgets(aseparar,100,fp);

		ra = strtok_r(aseparar, ",", &saveptr);
		cod = strtok_r(NULL, ",", &saveptr);
		sem = strtok_r(NULL, ",", &saveptr);
		notas = strtok_r(NULL, ",", &saveptr);
		fal = strtok_r(NULL, "\n", &saveptr);



		fflush(stdin);
		aux[i].ra=atoi(ra);
		strcpy(aux[i].codigo,cod);
		aux[i].semestre=atoi(sem);
		aux[i].nota=atoi(notas);
		aux[i].faltas=atoi(fal);
		

		fflush(stdin);
	
		//printf("Depois de strcpy, pela struct:\n");
		printf("ra:%d\n",aux[i].ra);
		printf("codigo:%s\n",aux[i].codigo);
		printf("semestre:%d\n",aux[i].semestre);
		printf("nota:%d\n",aux[i].nota);
		printf("faltas:%d\n",aux[i].faltas);
		

		printf("\n");
		i++;
	}
	fclose(fp);
	return aux;
}







/*
void* newAluno(Aluno alunos){
	Aluno aux;
	printf("Menu Cadastro de Alunos\n");
	printf("Digite o RA do Aluno: ");
	scanf("%d",&aux.ra);
	printf("\nDigite o Nome do Aluno: ");
	fgets(aux.nome,101,stdin);
	printf("\nDigite o login: ");
	fgets(aux.login,11,stdin);
	printf("\nDigite a senha: ");
	fgets(aux.senha,11,stdin);

	printf("\nRA: %d",&aux.ra);
	printf("Nome: %s",aux.nome);
	printf("\nLogin: %s",aux.login);
	printf("\nSenha: %s",aux.senha);

	saveAluno(aux, alunos);

}*/
/*
void* saveAluno(Aluno novo, Aluno alunos){


	int top, i;
	Aluno aux;
	aux.ra = novo.ra;
	strcpy (aux.nome,novo.nome);
	strcpy (aux.login,novo.login);
	strcpy (aux.senha,novo.senha);

	FILE* fp = fopen("Alunos.txt","w");

	//fscanf(fp,"%d",&top);
	//printf("%d\n",top);
	fprintf(fp,"%d\n",alunos.topA+1);

	for(i=0;i<top;i++){
		fprintf(fp,"%d");


	}



	fclose(fp);


}
*/
int login(Aluno *user){
    FILE *fp; //variável apontadora do arquivo
    char login[10], senha[10]; //strings que receberão do usuário o login e senha
    char nomeArq[100], loginArq[10], senhaArq[10]; //strings que salvarão dados puxados do arquivo
    int raArq; //inteiro que receberá os RAs do arquivo

    fp = fopen("Alunos.txt", "r"); //abrindo o arquivo para leitura

    if(fp == NULL){ //condição de finalização do programa caso o arquivo não seja aberto com sucesso
        puts("Impossivel abrir o arquivo!");
        exit(1);
    }

    //recebendo os dados de login e senha do usuário
    //puts("Por favor, insira seu usuario e senha:");
    printf("Usuario: ");
    scanf("%s", login);
    printf("Senha: ");
    scanf("%s", senha);

    /*laço que percorre o arquivo até encontrar o login e senha correspondente com o que o
    usuário digitou anteriormente. */
    while(fscanf(fp, "%d, %[^,], %[^,], %[^\n]", &raArq, nomeArq, loginArq, senhaArq)!= EOF){
        //comparando dados para autenticação
        if(strcmp(login, loginArq) == 0 && strcmp(senha, senhaArq) == 0){
            /* Jogando dados pegos do arquivo na variável global que será usada no
            decorrer do programa. */
            (*user).ra = raArq;
            strcpy((*user).nome, nomeArq);
            strcpy((*user).login, loginArq);
            strcpy((*user).senha, senhaArq);

            fclose(fp);

            return 0;
        }
    }

    //impresso em caso de falha de autenticação
    puts("Usuario nao encontrado! Tente novamente!");

    fclose(fp);

    return 1;
}


void consultaDisc(){
	int i;
	int ret;
	char cod[5];
	Disciplina *aux = d;
	printf ("Digite a disciplina: ");
	scanf("%s",cod);
	//strcmp(cod, aux[i].codigo) == 0
	//ret = strcmp(cod, aux[i].codigo);
	//printf("%d\n",ret);
	
	for(i=0;i<topD;i++){
	ret = strcmp(cod, aux[i].codigo);

		if(ret==0){

			printf("Nome: %s\n",aux[i].nome);
			printf("Quantidade de Creditos: %d\n",aux[i].creditos);
			
			exibePrereq(aux[i]);
			break;
		}
		
		
	}
	//exibePrereq(aux[0]);
	
}



void exibePrereq(Disciplina dd){
	printf("entrou no exibePrereq\n");
	Disciplina *aux2 = d;
	Prereq* pre = p;
	char temp[]="SI401";
	int i;
	int ret;
	
	Vetprereq * aux;
	aux = (Vetprereq*)malloc(sizeof(Vetprereq)*43);
	
	for(i=0;i<topP;i++){

		if(strcmp(dd.codigo,pre[i].codDisc)){
			//if(strcmp(temp,pre[i].codDisc)==0){
			topVP++;
			strcpy(aux[i].codigo,pre[i].codPrereq);
			//printf("%s\n",aux[i].codigo);
			
			continue;
		}
		
	
	}
	
	
		for(i=0;i<topVP;i++){
			ret = strcmp(aux[i].codigo,aux2[i].codigo);
			if(ret==0){
				printf("Pre-requisito: %s\n",aux2[i].nome);
			}

		}
}
