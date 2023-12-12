#ifndef _TLESAO_H_
#define _TLESAO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tMedico.h"
#include "utils.h"


#define TAM_MAX_DIAGNOSTICO 50
#define TAM_MAX_REGIAO_CORPO 25
#define TAM_MAX_ROTULO 5

typedef struct tLesao tLesao;

tLesao* CadastraLesao (int numRotulo, char* cpfPaciente, char* cpfMedico, char* CRM, char* data);

bool LesaoFoiEncaminhadaPraCirurgia (tLesao* l);

bool LesaoFoiEncaminhaCrioterapia (tLesao* l);

tLesao* ClonaLesao (tLesao* l);

char* ObtemDiagnosticoLesao (tLesao* l);

int ObtemTamanhoLesao (tLesao* l);

char* ObtemRegiaoCorpoLesao (tLesao* l);

char* ObtemRotuloLesao (tLesao* l);

void SalvaLesaoArquivoBinario (tLesao* l, FILE* file);

tLesao* ObtemLesaoArquivoBinario (FILE* file);

void DesalocaLesao (tLesao*);

#endif