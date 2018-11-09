#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matricula{
        int ra;
        char codigo[6];
        int semestre;
        float nota;
        float faltas;
} Matricula;

typedef struct disciplina{
	char codigo[6];
	char nome[101];
	int creditos;
} Disciplina;

typedef struct prerequisito{
        char nomePre[101];
	char codDisc[6];
	char codPrereq[6];
} Prereq;

typedef struct aluno{
	int ra;
	char nome[101];
	char login[11];
	char senha[11];
} Aluno;

#endif // MAIN_H
