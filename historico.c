#include "main.h"

int hist(Aluno user){
    int i, j, k, l, m, n; //va,riáveis inteiras auxiliares
    int contcred; //contador de créditos totais do aluno
    float contcn; //contador de créditos * nota totais do aluno
    int validador; //variável auxiliar de validação
    float aux; //variável auxiliar para ordenação
    char ra[11]; //string que guardará o ra para ser o nome do arquivo
    int pos; //variável que guarda a classificação do aluno logado
    float valpos; //variável que guarda o valor do coeficiente do usuário
    Aluno alunotmp; //variável temporária para contagem de alunos
    Aluno *aluno; //variável que guadará os alunos cadastrados
    Matricula temp; //variável temporária para contagem de matriculas
    Matricula *alunos; //vetor de struct dinâmico que guarda todos os alunos
    Disciplina tmp; //variável temporária para contagem de disciplinas
    Disciplina *disc; //vetor de struct dinâmico que guarda todas as disciplinas
    FILE *fp; //ponteiro para arquivo
    
    getchar();
    
    fp = fopen("AlunosDisciplinas.txt", "r"); /* abrindo o arquivo para pegar o
                                               * ra do usuário em formato de string. */
    
    if(fp == NULL)
       return 1; //impossível abrir o arquivo e interrompe a função
    
    while(fscanf(fp, "%[^,],%[^,],%d,%f,%f\n", ra, temp.codigo, &temp.semestre, 
            &temp.nota, &temp.faltas) != EOF){
        //achando o ra e saindo do laço
        if(atoi(ra) == user.ra)
            break;
    }
    
    fflush(fp);
    fclose(fp);
    
    //completando a string manualmente
    ra[6] = '.';
    ra[7] = 't';
    ra[8] = 'x';
    ra[9] = 't';
    ra[10] = '\0';
    
    fp = fopen("Alunos.txt", "r"); /* abrindo o arquivo para contar todos
                                    * os alunos cadastrados. */
    
    if(fp == NULL)
        return 1; //impossível abrir o arquivo e interrompe a função
    
    m = 0; //inicialmente atribuindo zero ao m para usar no laço abaixo
    
    //laço que conta quantos alunos estão cadastrados
    while(fscanf(fp, "%d,%[^,],%[^,],%[^\n]", &alunotmp.ra, alunotmp.nome, 
            alunotmp.nome, alunotmp.senha) != EOF){
        m++;
    }
    
    float coeficiente[m]; /* vetor de pf que guardará os coeficientes de rendimento 
                          * dos alunos */
    
    fflush(fp);
    fclose(fp);
    
    aluno = (Aluno *) malloc(m * sizeof(Aluno));
    
    fp = fopen("Alunos.txt", "r"); /* abrindo o arquivo para leitura de todos os
                                    * alunos. */
    
    if(fp == NULL)
        return 1; //impossível abrir o arquivo e interrompe a função
    
    l = 0; //atribuindo inicialmente zero ao l para usar abaixo
    
    //laço que guarda os alunos no sistema
    while(fscanf(fp, "%d,%[^,],%[^,],%[^\n]", &aluno[l].ra, aluno[l].nome, 
            aluno[l].nome, aluno[l].senha) != EOF){
        l++;
        
        //evitando que o laço tente salvar em uma posição inexistente
        if(l >= m)
            break;
    }
    
    fflush(fp);
    fclose(fp);
    
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
    
    fp = fopen("Disciplinas.txt", "r"); /* abrindo o arquivo para ver o número de
                                         * disciplinas presentes no arquivo */
    
    if(fp == NULL)
       return 1; //impossível abrir o arquivo e interrompe a função
    
    k = 0; /* variável que guardará quantas disciplinas o aluno se matriculou 
            * no semestre. */
    
    while(fscanf(fp,"%[^,],%[^,],%d\n", tmp.codigo, tmp.nome, 
            &tmp.creditos) != EOF){
        k++;
    }
    
    fflush(fp);
    fclose(fp);
    
    fp = fopen("Disciplinas.txt", "r"); /* abrindo o arquivo para salvar as
                                         * disciplinas em uma struct. */
    
    if(fp == NULL)
       return 1; //impossível abrir o arquivo e interrompe a função
    
    //alocando espaço para as disciplinas do aluno no semestre
    disc = (Disciplina *) malloc(k * sizeof(Disciplina));
    
    l = 0; //atribuindo zero ao l para usar como posição do vetor no laço abaixo
    
    while(fscanf(fp,"%[^,],%[^,],%d\n", disc[l].codigo, disc[l].nome, 
            &disc[l].creditos) != EOF){
        l++;
                    
        //evitando que o laço tente salvar em uma posição inexistente
        if(l >= k)
            break;
    }
    
    fflush(fp);
    fclose(fp);
    
    //atribuindo zero a estas variáveis para usar abaixo
    contcn = 0;
    contcred = 0;
    
    //laço que calcula os coeficientes de rendimento dos alunos
    for(l = 0; l < m; l++){ //1º laço repete por quantidade de alunos cadastrados
       for(j = 0; j < i; j++){ //2º laço repete por quantidade de matrículas
           //condição onde o aluno é encontrado
           if(aluno[l].ra == alunos[j].ra){
               for(n = 0; n < k; n++){ //3º laço repete por quantidade de disciplinas
                   //condição onde a disciplina é encontrada
                   if(strcmp(alunos[j].codigo, disc[n].codigo) == 0){
                       contcn += (disc[n].creditos * alunos[j].nota);
                       contcred += disc[n].creditos;
                       
                       break;
                   }
               }
           }
       }
       
       coeficiente[l] = (contcn / contcred); //calculando o coeficiente
       contcn = 0; //zerando para usar novamente
       contcred = 0; //zerando para usar novamente
       
       //condição onde o aluno sendo tratado é o do usuário
       if(user.ra == aluno[l].ra){
           valpos = coeficiente[l]; //salvando o valor do coeficiente do usuário
       }
    }

    //bubble sort para ordenar o vetor
    for(l = 0; l < m; l++){
        for(j = (l+1); j < m; j++){
            if(coeficiente[j] < coeficiente[l]){
                aux = coeficiente[l];
                coeficiente[l] = coeficiente[j];
                coeficiente[j] = aux;
            }
        }
    }
    
    //laço que encontra a posição do aluno no classificação
    for(l = 0; l < m; l++){
        //condição onde se encontra o valor
        if(valpos == coeficiente[l]){
            pos = l+1;
        }
    }
    
    fp = fopen(ra, "w"); //criando o histórico do aluno
    
    if(fp == NULL)
       return 1; //impossível abrir o arquivo e interrompe a função
    
    fputs("Faculdade de Tecnologia - UNICAMP\n", fp);
    fputs("\n", fp);
    fputs("Relatorio de Matricula\n", fp);
    fputs("\n", fp);
    
    fprintf(fp, "Nome Completo: %s\n", user.nome);
    fprintf(fp, "RA: %d\n", user.ra);
    fprintf(fp, "Coeficiente de Rendimento: %.2f\n", valpos);
    fprintf(fp, "Classificacao do aluno na turma: %d de %d\n", pos, m);
    
    fputs("\n", fp);
    
    fputs("Disciplina\tNota\tFaltas(%)\tSituacao\n", fp);
    
    //laço que imprime as matrículas na tela
    for(j = 0; j < i; j++){
        if(user.ra == alunos[j].ra){
            if(alunos[j].nota >= 5 && alunos[j].faltas < 25){
                fprintf(fp, "%s\t\t%.1f\t%.1f\t\tAprovado por Nota e Frequencia\n", 
                        alunos[j].codigo, alunos[j].nota, alunos[j].faltas);
            }else{
                if(alunos[j].nota < 5){
                    fprintf(fp, "%s\t\t%.1f\t%.1f\t\tReprovado por Nota\n", 
                            alunos[j].codigo, alunos[j].nota, alunos[j].faltas);
                }else{
                    fprintf(fp, "%s\t\t%.1f\t%.1f\t\tReprovado por Frequencia\n", 
                        alunos[j].codigo, alunos[j].nota, alunos[j].faltas);
                }
            }
        }
    }
    
    fflush(fp);
    fclose(fp);
    
    puts("O arquivo foi gerado com sucesso!");
    puts("Pressione ENTER para continuar");
    getchar();
    
    return 0;
}