#ifndef _TLESAO_H_
#define _TLESAO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_ROTULO 5
#define TAM_MAX_DIAGNOSTICO 50
#define TAM_MAX_REGIAO_CORPO 25

typedef struct tLesao tLesao;

tLesao* CadastraLesao ();

void DesalocaLesao (tLesao*);

#endif