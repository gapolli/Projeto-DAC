#include "main.h"

int fazerMatricula(Aluno user){
    int i, j, k; //variáveis inteiras auxiliares
    int creditos; /* variável que guardará a quantidade de créditos do aluno no
                   * semestre. */
    int semtemp; //variável que guarda o semestre temporáriamente
    int validador; //variável auxiliar de validação
    char codigodisc[6]; //variável que receberá o código da disciplina
    char saida[6] = "XX000"; //string que contém o que deve ser digitado para sair
    Disciplina disc; //variável do tipo struct disciplina
    Matricula mat[10]; /* variável que guardará as disciplinas onde o aluno está
                        * matriculado. */
    Matricula mattemp; //variável temporária que obtêm as matrículas do aluno
    Prereq discPre[7]; //vetor de struct que guarda os pré-requisitos
    FILE *fp; //ponteiro para arquivo
    
    validador = 0; //inicialmente atribuindo o zero ao validador, deixando-o falso
    
    //laço onde o semestre onde o aluno fará as matrículas será inserido 
    while(validador != 1){
        fp = fopen("AlunosDisciplinas.txt", "r"); /* abrindo o arquivo para verificar
                                               * a situação do aluno. */
    
        if(fp == NULL)
            return 1; //impossível abrir o arquivo e interrompe a função
        
        puts("Realizar Matricula:");
        puts("");
        printf("Digite o semestre: ");
        scanf("%d", &semtemp);
        getchar();
        puts("");
        
        //caso de um semestre menor que 1 ou maior que 10
        if(semtemp < 1 || semtemp > 10){
            puts("Semestre invalido!");

			if(semtemp > 10)
				puts("Acima da integralizacao maxima!");

            continue;
        }

        /* laço que detecta se há algum semestre mais avançado que o que o 
         * usuário quer fazer matrículas. */ 
        while(fscanf(fp, "%d,%[^,],%d,%f,%f\n", &mattemp.ra, mattemp.codigo, 
                &mattemp.semestre, &mattemp.nota, &mattemp.faltas) != EOF){
            if(user.ra == mattemp.ra){//ra encontrado
                if(semtemp >= mattemp.semestre){//semestre é válido
                    validador = 1;
                }else{//semestre inválido
                    puts("Nao e possivel se matricular em um semestre anterior!");
                    
                    validador = 2;
                    break;
                }
            }
        }
        
        //o ra não existe ainda na lista
        if(validador == 0)
            validador = 1;
        
        fflush(fp);
        fclose(fp);
    }
    
   
    
    fp = fopen("AlunosDisciplinas.txt", "r"); /* abrindo o arquivo para salvar as
                                               * atuais disciplinas que o aluno
                                               * está matriculado. */
    
    if(fp == NULL)
        return 1; //impossível abrir o arquivo e interrompe a função
    
    i = 0; //atribuindo zero a variável auxiliar
    
    //laço que guarda na memória as matrículas do aluno
    while(fscanf(fp, "%d,%[^,],%d,%f,%f\n", &mat[i].ra, mat[i].codigo,
            &mat[i].semestre, &mat[i].nota, &mat[i].faltas) != EOF){
        /* condição de que ao encontrar uma matrícula do aluno, incrementa-se
         * o i, para encontrar possíveis matrículas restantes do aluno no
         * semestre. */
        if(mat[i].ra == user.ra && mat[i].semestre == semtemp){
            i++;
        }
    }
    
    fflush(fp);
    fclose(fp);
    
    fp = fopen("Disciplinas.txt", "r"); //abrindo o arquivo para leitura de disciplinas
    
    if(fp == NULL)
        return 1; //impossível abrir o arquivo e interrompe a função
    
    creditos = 0; //inicialmente dando zero créditos no semestre atual do aluno
    
    //laço que verifica se a quantidade de créditos no semestre já foi excedida
    while(fscanf(fp, "%[^,],%[^,],%d\n", disc.codigo, disc.nome, &disc.creditos) != EOF){
        //verificando se já está igual a 32 ou ultrapassou
        if(creditos >= 32){
            puts("Impossivel fazer matricula neste semestre! Quantidade maxima de creditos alcancada!");
            puts("Pressione ENTER para continuar...");
            getchar();
            
            return 0;
        }
        
        //laço aninhado que coloca a quantidade de créditos atuais no semestre
        for(j = 0; j < i; j++){
            //comparando os códigos das disciplinas para adicionar os créditos
            if(strcmp(disc.codigo, mat[j].codigo) == 0){
                creditos += disc.creditos;
                
                break;
            }
        }
    }
    
    fflush(fp);
    fclose(fp);
    
    //laço que trabalha com a matrícula do aluno
    do{ 
        puts("Para sair, digite XX000");
        printf("Digite a disciplina: ");
        scanf("%5s", codigodisc);
        
        for(k = 0; k < 2; k++){ //modifica os 2 primeiros dígitos do código informado para maiúsculas
            codigodisc[k] = toupper(codigodisc[k]);
        }
        
        puts("");
        getchar();

		//verificando se o aluno está tentando se matricular em uma disciplina especial
		if(codigodisc[0] == 'A' && codigodisc[1] == 'A'){
			puts("Autorizacao! Somente a coordenacao pode te matricular nesta disciplina.");
			continue;
		}
        
        fp = fopen("Disciplinas.txt", "r"); //abrindo o arquivo para leitura de disciplinas
    
        if(fp == NULL)
            return 1; //impossível abrir o arquivo e interrompe a função
        
        validador = 0; /* validador igual a zero em relação a ter achado a disciplina
                        * no arquivo. */
        
        //laço que verifica se a disciplina existe
        while(fscanf(fp, "%[^,],%[^,],%d\n", disc.codigo, disc.nome, &disc.creditos) != EOF){
            //condição que verifica se foi encontrada a disciplina no arquivo.
            if(strcmp(codigodisc, disc.codigo) == 0){
                validador = 1; //validador igual a um, indicando que a disciplina foi encontrada
                break;
            }
        }
        
        //condição para pular o resto dos passos do laço, caso a disciplina não exista
        if(validador == 0 && strcmp(codigodisc, "XX000") != 0){
            puts("Esta disciplina nao existe! Tente novamente.");
            continue;
        }
        
        fflush(fp);
        fclose(fp);
        
        if(strcmp(codigodisc, saida) == 0){
            puts("Transacao efetuada com sucesso");
            puts("Pressione ENTER para continuar...");
            getchar();
            break;
        }
        
        fp = fopen("AlunosDisciplinas.txt", "r"); /* abrindo o arquivo para verificar
                                                   * se o aluno já cursou está disciplina
                                                   * ou não. */

        if(fp == NULL)
            return 1; //impossível abrir o arquivo e interrompe a função
            
        /* laço que guarda na memória as matrículas do aluno para verificar se a
        * disciplina já foi cursada ou não. */
        while(fscanf(fp, "%d,%[^,],%d,%f,%f\n", &mattemp.ra, mattemp.codigo, 
            &mattemp.semestre, &mattemp.nota, &mattemp.faltas) != EOF){
            if(strcmp(codigodisc, mattemp.codigo) == 0 && user.ra == mattemp.ra){
                puts("Matricula impossivel, pois a disciplina ja foi cursada!");
                validador = 2;
                    
                break;
            }
        }
        
        fflush(fp);
        fclose(fp);
        
        //pulando o resto do conteúdo do laço já que a disciplina já foi cursada
        if(validador == 2)
            continue;
        
        fp = fopen("Prerequisitos.txt", "r"); /* abrindo o arquivo para leitura dos
                                           pré-requisitos. */
    
        if(fp == NULL)
            return 1; //impossível abrir o arquivo e interrompe a função
        
        i = 0; //atribuindo zero a esta variável para usar no laço abaixo
    
        //laço que obterá a disciplina e seu pré-requisito
        while(fscanf(fp, "%[^,],%[^\n]\n", discPre[i].codDisc, discPre[i].codPrereq) != EOF){
            //condição de entrada ao achar a disciplina na lita de pré-requisitos
            if(strcmp(discPre[i].codDisc, codigodisc) == 0){
                /* verificando se a disciplina não tem nenhum pré-requisito, sendo
                 uma condição de parada do laço. */
                if(strcmp(discPre[i].codPrereq, "0") == 0){
                    validador = 0; //dizendo que a disciplina não tem pré-requisito
                    
                    break;
                }else{ // caso contrário ele pega o pré-requisito               
                    i++; //incrementando o i para guardar todos os pré-requisitos
                }
            }
        }
        
        fflush(fp);
        fclose(fp);
        
        //condição caso a disciplina tenha pré-requisito
        if(validador != 0){
            
            fp = fopen("AlunosDisciplinas.txt", "r"); /* abrindo o arquivo para verificar
                                                       * se ele já cursou os pré-requisitos
                                                       * da matéria que ele irá se matricular. */

            if(fp == NULL)
                return 1; //impossível abrir o arquivo e interrompe a função
            
            k = 0; //atribuindo zero a esta variável para usar no laço abaixo
            
             /* laço que guarda na memória as matrículas do aluno para verificação
             * dos pré-requisitos feitos. */
            while(fscanf(fp, "%d,%[^,],%d,%f,%f\n", &mattemp.ra, mattemp.codigo, 
                &mattemp.semestre, &mattemp.nota, &mattemp.faltas) != EOF){
                /* condição de parada instantânea caso o aluno não tenha nota 
                 * satisfatória ou tenha faltas demais no pré-requisito. */
                if(validador == -1 || validador == -2)
                    break;
                
                // condição de parada se todos os pré-requisitos foram satisfeitos
                if(k == i)
                    break;
                
                //laço que verifica se o aluno cursou o pré-requisito
                for(j = 0; j < i; j++){
                    //verificando se foi encontrado o pré-requisito
                    if(strcmp(discPre[j].codPrereq, mattemp.codigo) == 0 && 
                            user.ra == mattemp.ra && semtemp > mattemp.semestre){
                        //verificando se o aluno tem o desempenho satisfatório
                        if(mattemp.nota >= 5 && mattemp.faltas < 25){
                            validador = 1; /* indicando que o pré-requisito foi satisfeito para
                                            * mais abaixo no código. */
                            k++; //indicador de que o pré-requisito foi satisfeito
                            break;
                        }else{//verificando por qual motivo o aluno não cumpriu o pré-requisito
                            if(mattemp.nota < 5){ //por nota
                                validador = -1;
                                break;
                            }
                            
                            if(mattemp.faltas >= 25){ //por falta
                                validador = -2;
                                break;
                            }
                        }
                    }else{ /* caso onde o pré-requisito não foi achado ou o
                            * usuário está tentando matricular-se no mesmo
                            * semestre que cursou o pré-requisito. */
                        validador = -3;
                    }
                }
            }

            fflush(fp);
            fclose(fp);
        }
        
        if(validador == -1){ //condição caso houve reprovação por nota
            puts("Matricula impossivel, pois o aluno reprovou por nota no(s) pre-requisitos!");
        }else{ //condição caso houve reprovação por falta
            if(validador == -2){
                puts("Matricula impossivel, pois o aluno reprovou por falta no(s) pre-requisitos!");
            }else{ //condição caso houve falta de pré-requisitos concluídos
                if(validador == -3){
                    printf("Matricula impossivel, pois o pre-requisito nao foi cursado, ");
                    printf("ou a matricula desta disciplina esta tentando ser feita no mesmo semestre ");
                    puts("que o pre-requisito!");
                }else{ /* condição onde a matrícula é feita ou o
                            * usuário está tentando matricular-se no mesmo
                            * semestre que cursou o pré-requisito. */
                    fp = fopen("AlunosDisciplinas.txt", "a");
                    //abrindo o arquivo para "append" para adicionar a matrícula nova
                    
                    if(fp == NULL)
                         return 1; //impossível abrir o arquivo e interrompe a função
                    
                    //imprimindo no arquivo a matrícula
                    fprintf(fp,"%d,%s,%d,-1.0,-1.0\n", user.ra, codigodisc, semtemp);
                    
                    puts("Transacao efetuada com sucesso");
                    puts("Pressione ENTER para continuar...");
                    getchar();
                    
                    fflush(fp);
                    fclose(fp);
                }
            }
        }
    }while(strcmp(codigodisc, saida) != 0);
    
    return 0;
}
