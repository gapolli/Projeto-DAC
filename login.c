#include "main.h"

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
    puts("Por favor, insira seu usuario e senha:");
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

            //impresso quando o usuário for autenticado
            puts("");
            puts("Logado com Sucesso!");
            puts("");

            fclose(fp);

            return 0;
        }
    }

    //impresso em caso de falha de autenticação
    puts("");
    puts("Usuario nao encontrado! Tente novamente!");
    puts("");

    fclose(fp);

    return 1;
}