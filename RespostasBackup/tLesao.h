#ifndef _TLESAO_H_
#define _TLESAO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM_MAX_DIAGNOSTICO 50
#define TAM_MAX_REGIAO_CORPO 25

typedef struct tLesao tLesao;

tLesao* CadastraLesao ();

bool LesaoFoiEncaminhadaPraCirurgia (tLesao* l);

tLesao* ClonaLesao (tLesao* l);

char* ObtemDiagnosticoLesao (tLesao* l);

int ObtemTamanhoLesao (tLesao* l);

char* ObtemRegiaoCorpoLesao (tLesao* l);

void DesalocaLesao (tLesao*);

#endif