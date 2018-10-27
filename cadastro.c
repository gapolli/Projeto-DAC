#include "main.h"

int cadastrar(){
    Aluno cad; //vari�vel que guardar� tempor�riamente os dados do aluno a ser cadastrado
    FILE *fp; //vari�vel apontadora para arquivo

    fp = fopen("Alunos.txt", "a"); //abrindo o arquivo para "append" para que o arquivo n�o seja reescrito

    if(fp == NULL) //interrompendo a fun��o, pois o arquivo n�o pode ser aberto
        return 1;

    //guardando os dados na struct tempor�riamente para salvar no arquivo
    puts("");
    puts("Cadastro de Alunos:");
    puts("");
    printf("Digite o RA do Aluno:");
    scanf("%d", &cad.ra);
    getchar(); //limpando o buffer do teclado

    printf("\nDigite o Nome do Aluno:");
    scanf("%[^\n]s", cad.nome); //maneira de permitir que o scanf salve uma string com espa�os se necess�rio

    printf("\nDigite o Login:");
    scanf("%s", cad.login);

    printf("\nDigite a Senha:");
    scanf("%s", cad.senha);
    puts("");

    //salvando no arquivo o novo aluno
    fprintf(fp, "\n%d,%s,%s,%s", cad.ra, cad.nome, cad.login, cad.senha);

    puts("Aluno cadastrado com sucesso!");
    puts("");

    return 0;
}
