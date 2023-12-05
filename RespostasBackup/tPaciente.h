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


/// @brief Salva um paciente no arquivo binario 'pacientes'
/// @param p 
/// @param file 
void SalvaPacienteArquivoBinario (void* p, FILE* file);



tPaciente* BuscaPacienteArqvBinario (char* nome, FILE* file);


/// @brief Desaloca memoria de um paciente
/// @param  paciente
void DesalocaPaciente (void* p);


#endif