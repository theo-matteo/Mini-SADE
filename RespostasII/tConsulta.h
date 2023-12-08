#ifndef _TCONSULTA_H_
#define _TCONSULTA_H_

#include <stdio.h>
#include <stdlib.h>

#include "tDatabase.h"
#include "tUsuario.h"
#include "tFila.h"
#include "tPaciente.h"
#include "tLesao.h"
#include "tReceita.h"
#include "tBiopsia.h"
#include "tEncaminhamento.h"
#include "utils.h"

#define TAM_MAX_TIPO_PELE 5

typedef struct tConsulta tConsulta;

tConsulta* RealizaConsulta(tUsuario* user, tDatabase* d, tFila* f);

tConsulta* LeInformacoesConsulta(char* cpfPaciente, char* cpfMedico, char* CRM);

void AdicionaLesaoConsulta (tConsulta* c, tLesao* l);

void PrintTelaConsultaMedica();

tReceita* PreencheCriaReceitaMedica (char* nomePaciente, char* CRM, char* nomeMedico, char* data);

int ObtemQtdLesoesConsulta (tConsulta* c);

tLesao** ObtemLesoesConsulta(tConsulta* c);

char* ObtemDataConsulta (tConsulta* c);

char* ObtemCPFPacienteConsulta (tConsulta* c);

void SalvaConsultasArquivoBinario (tConsulta** consultas, int qtd, FILE* file);

void DesalocaConsulta (tConsulta* c);


#endif