#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tLesao.h"
#include "tFila.h"


typedef struct tBiopsia tBiopsia;

tBiopsia* CriaBiopsia (tLesao** l, int qtd, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data);

tBiopsia* SolicitaBiopsia (tLesao** lesoes, int qtdLesoes, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data);

void imprimeNaTelaBiopsia(void *dado);

void imprimeEmArquivoBiopsia(void *dado, char *path);

void DesalocaBiopsia (void* dado);


#endif