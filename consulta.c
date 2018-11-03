#include "main.h"

int consultarDisc(){
    int i, j; //variáveis inteiras auxiliares
    int validador; //variável que valida se a disciplina foi encontrada com sucesso
    char codigodisc[6]; //variável que receberá o código da disciplina
    char codigotemp[6]; /* variável que recebe temporáriamente o código da disciplina
                         * que é pré-requisito. */
    int credtemp; /* variável inteira temporária que pega os créditos da disciplina
                   que é pré-requisito, apenas para navegação no arquivo. */
    Disciplina disc; //variável do tipo struct disciplina
    Prereq discPre[7]; //vetor de struct que guarda os pré-requisitos
    FILE *fp; //ponteiro para arquivo
    
    fp = fopen("Disciplinas.txt", "r"); //abrindo o arquivo para leitura das disciplinas
    
    if(fp == NULL)
        return 1; //impossível abrir o arquivo e interrompe a função
    
    printf("Digite a Disciplina: "); //obtendo o código da disciplina
    scanf("%5s", codigodisc);
    getchar(); /* detalhe: o 5 é para limitar o tanto de caracteres 
                * que serão pegos, eliminando a necessidade de um
                * fgets. */
    
    validador = 0; /* atribuindo o zero préviamente, caso a disciplina não seja
                    * encontrada, o valor continuará o mesmo. */
    
    //laço que pega os dados das disciplinas até achar a correspondente ou até acabar o arquivo
    while(fscanf(fp, "%[^,],%[^,],%d\n", disc.codigo, disc.nome, &disc.creditos) != EOF){
        //condição que compara as strings para descobrir se a disciplina foi encontrada
        if(strcmp(codigodisc, disc.codigo) == 0){
            validador = 1; /* alterando o validador para 1, dessa maneira dessa maneira
                            é indicado que a disciplina foi encontrada*/
            
            break; //saindo do laço
        }
    }
    
    //condição que interrompe a função caso não se encontre a disciplina
    if(validador == 0){
        puts("Disciplina nao encontrada!");
        puts("Pressione ENTER para continuar...");
        getchar();
        
        fclose(fp);
        return 0;
    }
    
    fclose(fp);
    
    fp = fopen("Prerequisitos.txt", "r"); /* abrindo o arquivo para leitura dos
                                           pré-requisitos. */
    
    if(fp == NULL)
        return 1; //impossível abrir o arquivo e interrompe a função
    
    i = 0; //atribuindo zero a esta variável para usar no laço abaixo
    
    //laço que obterá a disciplina e seu pré-requisito
    while(fscanf(fp, "%[^,],%[^\n]\n", discPre[i].codDisc, discPre[i].codPrereq) != EOF){
        //condição de entrada ao achar a disciplina na lita de pré-requisitos
        if(strcmp(discPre[i].codDisc, disc.codigo) == 0){
            /* verificando se a disciplina não tem nenhum pré-requisito, sendo
             uma condição de parada do laço. */
            if(strcmp(discPre[i].codPrereq, "0") == 0){
                validador = 0; /* atribuindo o zero ao validador, desta maneira
                                entende-se posteriormente que a disciplina não
                                possui pré-requisito. */
                break;
            }else{ // caso contrário ele pega o pré-requisito               
                i++; //incrementando o i para guardar todos os pré-requisitos
            }
        }
    }
    
    //condição que finaliza a função mostrando a disciplina que não tem pré-requisito
    if(validador == 0){
        printf("Nome: %s\n", disc.nome);
        printf("Quantidade de Creditos: %d\n", disc.creditos);
        printf("Pre-requisito: Nenhum\n");
        puts("Pressione ENTER para continuar...");
        getchar();
        
        return 0;
    }
    
    fclose(fp);
    
    fp = fopen("Disciplinas.txt", "r"); /* abrindo o arquivo para leitura das disciplinas
                                         novamente, porém desta vez para obtenção do nome
                                         da disciplina que é pré-requisito. */
    
    if(fp == NULL)
        return 1; //impossível abrir o arquivo e interrompe a função
    
    j = 0; //atribuindo zero ao j para usar no laço abaixo
    
    /* laço que pega o nome das disciplinas e o código para comparação, porém
     * os créditos apenas são pegos para evitar conflitos na navegação do arquivo,
     * ou seja, não são utilizados. */
    while(fscanf(fp, "%[^,],%[^,],%d\n", codigotemp, discPre[j].nomePre, &credtemp) != EOF){
        /* comparando se o codigo pego é igual ao do pré-requisito, dessa maneira
         * muda-se a posição do vetor para guardar outros pré-requisitos. */
        if(strcmp(codigotemp, discPre[j].codPrereq) == 0){
            j++;
        }
    }
    
    //imprimindo na tela a disciplina
    printf("Nome: %s\n", disc.nome);
    printf("Quantidade de Creditos: %d\n", disc.creditos);

    //laço que imprime todos os pré-requisitos
    for(j = 0; j < i; j++){
        printf("Pre-requisito: %s\n", discPre[j].nomePre);    
    }
        
    puts("Pressione ENTER para continuar...");
    getchar();
    
    fclose(fp);
    
    return 0;
}