#include "main.h"

int menu(){
    int op;

    puts("Menu de Opcoes:");
    puts("");
    puts("1 - Cadastro de Alunos");
    puts("2 - Consultar Disciplinas");
    puts("3 - Realizar Matricula");
    puts("4 - Atualizar Nota e Falta");
    puts("5 - Trocar usuario");
    puts("0 - Sair");
    puts("");
    printf("Escolha uma opcao: ");
    scanf("%d", &op);

    return op;
}
