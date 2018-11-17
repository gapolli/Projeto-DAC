#include "main.h"

int redirect(int op,Aluno *user){
    int aux; //variável inteira auxiliar
    int erro; /* variável que recebe o que uma função chamada retorna e dessa
               * maneira, descobre-se se a função funcionou normalmente ou não. */

    switch(op){
        case 1:
            erro = cadastrar(); //chamando a função de cadastro

            //condição satisfeita quando o programa não consegue abrir o arquivo
            if(erro == 1)
                puts("Erro ao abrir o arquivo!");
        break;

        case 2:
            erro = consultarDisc(); //chamando a função de consulta
            
            //condição satisfeita quando o programa não consegue abrir o arquivo
            if(erro == 1)
                puts("Erro ao abrir o arquivo!");
        break;

        case 3:
            erro = fazerMatricula(*user); //chamando a função de matrícula
            
            //condição satisfeita quando o programa não consegue abrir o arquivo
            if(erro == 1)
                puts("Erro ao abrir o arquivo!");
        break;

        case 4:
            erro = atualizar(*user); //chamando a função de atualizar nota e falta
            
            //condição satisfeita quando o programa não consegue abrir o arquivo
            if(erro == 1)
                puts("Erro ao abrir o arquivo!");
        break;
        
        case 5:
            erro = hist(*user); //chamando a função de consultar histórico
            
            //condição satisfeita quando o programa não consegue abrir o arquivo
            if(erro == 1)
                puts("Erro ao abrir o arquivo!");
        break;
        
        case 6:
            while(erro != 0){ //laço que repete o login até o usuário entrar com as credenciais corretas
                erro = login(user); //chamando a função de login
            }
        break;

        default:
            //apenas impresso caso a opção escolhida não conste no programa
            puts("");
            puts("Opcao Invalida!");
            puts("");
    }
}
