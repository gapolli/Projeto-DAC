int redirect(int op){
    int erro;

    switch(op){
        case 1:
            erro = cadastrar();

            if(erro == 1)
                puts("Erro ao abrir o arquivo!");
        break;

        case 2:
        break;

        case 3:
        break;

        case 4:
        break;

        default:
            puts("");
            puts("Opcao Invalida!");
            puts("");
    }
}