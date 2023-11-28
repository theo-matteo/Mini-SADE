#ifndef _TMEDICO_H_
#define _TMEDICO_H_

#include "tDadosPessoais.h"

#define TAM_NOME_USER 20   
#define TAM_MAX_SENHA 20
#define TAM_CRM 12

typedef struct tMedico tMedico;

tMedico* CriaMedico ();

tMedico* CadastraMedico();

void DesalocaMedico(tMedico*);


#endif