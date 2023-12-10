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
#include "tDadosReceita.h"
#include "utils.h"

#define TAM_MAX_TIPO_PELE 5
#define TAM_MAX_CPF 15
#define TAM_MAX_DATA 11
#define TAM_MAX_NOME 100
#define TAM_CRM 12
#define TAM_INSTRUCOES 300

typedef struct tConsulta tConsulta;

tConsulta* RealizaConsulta(tUsuario* user, tDatabase* d, tFila* f, tListaDataReceita* l);

tConsulta* LeInformacoesConsulta(char* cpfPaciente, char* cpfMedico, char* CRM);

void AdicionaLesaoConsulta (tConsulta* c, tLesao* l);

tReceita* PreencheCriaReceitaMedica (char* nomePaciente, char* CRM, char* nomeMedico, char* data,  tListaDataReceita* l);

int ObtemQtdLesoesConsulta (tConsulta* c);

tLesao** ObtemLesoesConsulta(tConsulta* c);

char* ObtemDataConsulta (tConsulta* c);

char* ObtemCPFPacienteConsulta (tConsulta* c);

void SalvaConsultaArquivoBinario (tConsulta* consulta, FILE* file);

int ObtemQuantidadeConsultasBinario (FILE* file);

int ObtemQtdCpfUnicos (char** cpfs, int qtd);

void DesalocaConsulta (tConsulta* c);


#endif