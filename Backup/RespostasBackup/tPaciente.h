#ifndef _TPACIENTE_H_
#define _TPACIENTE_H_


#include "tDadosPessoais.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tPaciente tPaciente;


/// @brief Cadastra um novo paciente a partir da entrada padrao
/// @return paciente
tPaciente* CadastraPaciente ();


tPaciente* CriaPaciente (tDadosPessoais* d);


/// @brief Salva um paciente no arquivo binario 'pacientes'
/// @param p 
/// @param file 
void SalvaPacienteArquivoBinario (void* p, FILE* file);

char* ObtemCPFPaciente (void* paciente);

char* ObtemNomePaciente (void* p);

char* ObtemDtNascPaciente (void *p);

/// @brief Desaloca memoria de um paciente
/// @param  paciente
void DesalocaPaciente (void* p);


#endif