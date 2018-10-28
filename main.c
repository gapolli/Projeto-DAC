#include "main.h"

Aluno user; //variável global que recebe os dados do aluno que logar

int main()
{
    int erro; //variável que identifica se tudo ocorreu bem em funções que forem chamadas
    int opcao; //variável que terá o controle das opções selecionadas no menu

    erro = 1; //atribuindo 1 à variável para que o laço de login se inicie
    opcao = -1; //atribuindo -1 à variável para que o laço que executa as ações do programa se inicie

    while(erro != 0){ //laço que repete o login até o usuário entrar com as credenciais corretas
        erro = login(&user); //chamando a função de login
    }

    while(opcao != 0){ //laço que executa as ações do programa
        opcao = menu();

        if(opcao == 0) //finalizando o programa quando o usuário seleciona a opção zero
            exit(0);

        redirect(opcao); //chamando função que redireciona para o que o usuário escolheu
    }
}