#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct disciplina{
	char codigo[5];
	char nome[100];
	int creditos;
} Disciplina;

typedef struct aluno{
	int ra;
	char nome[100];
	char login[10];
	char senha[10];
} Aluno;

#endif // MAIN_H
