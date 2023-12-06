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

#define TAM_MAX_TIPO_PELE 5

typedef struct tConsulta tConsulta;

void RealizaConsulta(tUsuarioSistema* user, tDatabase* d, tFila* f);

tConsulta* LeInformacoesConsulta();

void AdicionaLesaoConsulta (tConsulta* c, tLesao* l);

void PrintTelaConsultaMedica();

tReceita* PreencheCriaReceitaMedica (char* nomePaciente, char* CRM, char* nomeMedico, char* data);

void DesalocaConsulta (tConsulta* c);


#endif