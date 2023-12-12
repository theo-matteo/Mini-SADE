#ifndef _TDADOSRECEITA_H_
#define _TDADOSRECEITA_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que armazena os dados de uma receita
typedef struct tDataReceita tDataReceita;

tDataReceita* AlocaDadosReceita ();

tDataReceita* LeDadosReceita (char* nome_paciente, char* data, char* nome_medico, char* crm);

char* ObtemNomeMedicamento (tDataReceita* d);

char* ObtemTipoMedicamento (tDataReceita* d);

char* ObtemInstrucoes (tDataReceita* d);

int ObtemQtdMedicamento (tDataReceita* d);

char* ObtemNomePacienteReceita (tDataReceita* d);

char* ObtemNomeMedicoReceita (tDataReceita* d);

char* ObtemCRMReceita (tDataReceita* d);

char* ObtemDataReceita (tDataReceita* d);

void DesalocaDadosReceita (void* dado);


#endif