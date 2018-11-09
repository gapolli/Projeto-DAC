#include "main.h"

int atualizar(Aluno user){
    int i, j, k, l; //variáveis inteiras auxiliares
    int semtemp; //variável que guarda o semestre temporáriamente
    int validador; //variável auxiliar de validação
    char codigodisc[6]; //variável que receberá o código da disciplina
    char saida[6] = "XX000"; //string que contém o que deve ser digitado para sair
    Matricula temp; //variável temporária para contagem de matriculas
    Matricula *alunos; //vetor de struct dinâmico que guarda todos os alunos
    Disciplina *disc; //vetor de struct dinâmico que guarda as disciplinas do aluno
    FILE *fp; //ponteiro para arquivo
    
    fp = fopen("AlunosDisciplinas.txt", "r"); /* abrindo o arquivo para contar
                                               * quantas matrículas tem. */
    
    if(fp == NULL)
        return 1; //impossível abrir o arquivo e interrompe a função
    
    i = 0; //atribuindo inicialmente o zero para o i
    
    //laço que incrementa o i para contar quantas matrículas tem no sistema
    while(fscanf(fp, "%d,%[^,],%d,%f,%f\n", &temp.ra, temp.codigo, &temp.semestre, 
            &temp.nota, &temp.faltas) != EOF){
        i++;
    }
    
    fflush(fp);
    fclose(fp);
    
    //alocando espaço para guardar as matrículas
    alunos = (Matricula *) malloc(i * sizeof(Matricula));
    
    fp = fopen("AlunosDisciplinas.txt", "r"); /* abrindo o arquivo para ler e
                                               * salvar no sistema todas as 
                                               * matrículas existentes. */
    
    if(fp == NULL)
        return 1; //impossível abrir o arquivo e interrompe a função
    
    //laço que aloca espaço e salva o resto das matrículas existentes
    for(j = 0; j < i; j++){
        fscanf(fp, "%d,%[^,],%d,%f,%f\n", &alunos[j].ra, alunos[j].codigo, 
                &alunos[j].semestre, &alunos[j].nota, &alunos[j].faltas);
    }
    
    fflush(fp);
    fclose(fp);
    
    puts("Atualizar nota e falta:");
    
    validador = 0; //inicialmente atribuindo o zero ao validador, deixando-o falso
    
    //laço que valida o semestre escolhido
    while(validador != 1){
        puts("");
        printf("Digite o semestre: ");
        scanf("%d", &semtemp);
        getchar();
        puts("");
        
        //caso de um semestre menor que 1
        if(semtemp < 1){
            puts("Semestre invalido!");
            continue;
        }
        
        /* laço que verifica se o usuário digitou um semestre em que ele não tem
         * matrícula ainda. */
        for(j = 0; j < i; j++){
            //condição de parada do laço ao achar o semestre
            if(user.ra == alunos[j].ra && semtemp == alunos[j].semestre){
                validador = 1;
                break;
            }else{ //caso não ache o validador é indicador disso
                validador = -1;
            }
        }
        
        //condição onde não se achou o semestre
        if(validador == -1){
            puts("Voce nao possui nenhuma matricula neste semestre!");
            continue;
        }
    }
    
    
    
    fp = fopen("Disciplinas.txt", "r"); /* abrindo o arquivo para saber o nome
                                         * das disciplinas que o aluno se matriculou
                                         * no semestre em questão. */
    
    if(fp == NULL)
       return 1; //impossível abrir o arquivo e interrompe a função
    
    k = 0; /* variável que guardará quantas disciplinas o aluno se matriculou 
            * no semestre. */
    
    /* laço que incrementa k para guardar quantas disciplinas o aluno 
     * se matriculou no semestre em questão. */
    for(j = 0; j < i; j++){
        //condição onde se encontra uma disciplina que o aluno se matriculou no semestre
        if(user.ra == alunos[j].ra && semtemp == alunos[j].semestre){
            k++;
        }
    }
    
    //alocando espaço para as disciplinas do aluno no semestre
    disc = (Disciplina *) malloc(k * sizeof(Disciplina));
    
    l = 0; //atribuindo zero ao l para usar como posição do vetor no laço abaixo
    
    while(fscanf(fp,"%[^,],%[^,],%d\n", disc[l].codigo, disc[l].nome, 
            &disc[l].creditos) != EOF){
        //laço que incrementa l ao achar a disciplina que o aluno se matriculou
        for(j = 0; j < i; j++){
            //condição onde se acha as matérias que o aluno se matriculou
            if(alunos[j].ra == user.ra && semtemp == alunos[j].semestre){
                //condição onde se encontra a disciplina que o aluno cursou
                if(strcmp(alunos[j].codigo, disc[l].codigo) == 0)
                    l++;
            }
        }
        
        //evitando que o laço tente salvar em uma posição inexistente
        if(l >= k)
            break;
    }
    
    fflush(fp);
    fclose(fp);
    
    puts("Disciplinas:");
    
    //laço que imprime todas as disciplinas do aluno no semestre escolhido
    for(l = 0; l < k; l++){
        /* laço aninhado que percorre o vetor de struct toda vez para poder
         * imprimir corretamente todas as disciplinas. */
        for(j = 0; j < i; j++){
            //condição onde acha-se as disciplinas do aluno no semestre escolhido
            if(alunos[j].ra == user.ra && semtemp == alunos[j].semestre){
                //condição onde se encontra a disciplina que o aluno cursou
                if(strcmp(alunos[j].codigo, disc[l].codigo) == 0){
                    printf("%s - %s - Nota: %.1f, Falta (%%): %.1f\n", alunos[j].codigo,
                            disc[l].nome, alunos[j].nota, alunos[j].faltas);
                }         
            }
        }
    }
    
    puts("");
    
    //laço que atualiza a nota do aluno
    do{
        puts("Para sair, digite XX000");
        printf("Digite o codigo da disciplina que deseja fazer a alteracao: ");
        scanf("%5s", codigodisc);
        
        for(l = 0; l < 2; l++){ //modifica os 2 primeiros dígitos do código informado para maiúsculas
            codigodisc[l] = toupper(codigodisc[l]);
        }
        
        puts("");
        getchar();
        
        //çondição para sair da função
        if(strcmp(codigodisc, saida) == 0){
            puts("Atualizacao com sucesso");
            puts("Pressione ENTER para continuar...");
            getchar();
            break;
        }
        
        //laço que verifica se o aluno está matriculado na disciplina digitada
        for(l = 0; l < k; l++){
            //condição onde o aluno está matriculado na disciplina digitada
            if(strcmp(codigodisc, disc[l].codigo) == 0){
                validador = 1;
                break;
            }else{ //condição onde a disciplina não foi encontrada
                validador = 0;
            }
        }
        
        //condição de reiniciar o laço caso a disciplina não tenha sido encontrada
        if(validador == 0){
            puts("Voce nao esta matriculado nesta disciplina!");
            continue;
        }
        
        //laço que salva no vetor de struct os novos dados
        for(j = 0; j < i; j++){
            //condição onde a disciplina foi encontrada
            if(strcmp(codigodisc, alunos[j].codigo) == 0){
                printf("Nota: ");
                scanf("%f", &alunos[j].nota);
                puts("");
                getchar();
                
                printf("Falta (%%): ");
                scanf("%f", &alunos[j].faltas);
                puts("");
                getchar();
                
                break;
            }
        }
        
        fp = fopen("AlunosDisciplinas.txt", "w"); /* Abrindo o arquivo para
                                                   * escrita para atualizar as
                                                   * informações de nota e falta. */
        
        if(fp == NULL)
            return 1; //impossível abrir o arquivo e interrompe a função
        
        //laço que salva no arquivo os novos dados atualizados
        for(j = 0; j < i; j++){
            //imprimindo no arquivo os novos dados atualizados
            fprintf(fp, "%d,%s,%d,%.1f,%.1f\n", alunos[j].ra, alunos[j].codigo,
                    alunos[j].semestre, alunos[j].nota, alunos[j].faltas);
        }
        
        fflush(fp);
        fclose(fp);
        
        puts("Atualizacao com sucesso");
        puts("Pressione ENTER para continuar...");
        getchar();
        
    }while(strcmp(codigodisc, saida) != 0);
        
    return 0;
}