#ifndef _TCONSULTA_H_
#define _TCONSULTA_H_

#include <stdio.h>
#include <stdlib.h>

#include "tDatabase.h"
#include "tUsuarioSistema.h"
#include "tFila.h"
#include "tPaciente.h"
#include "tLesao.h"
#include "tReceita.h"
#include "tBiopsia.h"

#define TAM_MAX_TIPO_PELE 5

typedef struct tConsulta tConsulta;

void RealizaConsulta(tUsuarioSistema* user, tDatabase* d, tFila* f);

tConsulta* LeInformacoesConsulta();

void AdicionaLesaoConsulta (tConsulta* c, tLesao* l);

void PrintTelaConsultaMedica();

tReceita* PreencheCriaReceitaMedica (char* nomePaciente, char* CRM, char* nomeMedico, char* data);

int ObtemQtdLesoesConsulta (tConsulta* c);

tLesao** ObtemLesoesConsulta(tConsulta* c);

char* ObtemDataConsulta (tConsulta* c);

void DesalocaConsulta (tConsulta* c);


#endif