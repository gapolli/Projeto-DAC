#include "main.h"

int cadastrar(){
    Aluno cad; //variável que guardará temporáriamente os dados do aluno a ser cadastrado
    FILE *fp; //variável apontadora para arquivo

    fp = fopen("Alunos.txt", "a"); //abrindo o arquivo para "append" para que o arquivo não seja reescrito

    if(fp == NULL) //interrompendo a função, pois o arquivo não pode ser aberto
        return 1;

    //guardando os dados na struct temporáriamente para salvar no arquivo
    puts("");
    puts("Cadastro de Alunos:");
    puts("");
    printf("Digite o RA do Aluno:");
    scanf("%d", &cad.ra);
    getchar(); //limpando o buffer do teclado

    printf("\nDigite o Nome do Aluno:");
    scanf("%[^\n]s", cad.nome); //maneira de permitir que o scanf salve uma string com espaços se necessário

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