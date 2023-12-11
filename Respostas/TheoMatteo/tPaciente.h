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


/// @brief Cria um paciente e seta dados pessoais
/// @param d 
/// @return paciente
tPaciente* CriaPaciente (tDadosPessoais* d);


/// @brief Salva paciente em um arquivo binario
/// @param p 
/// @param file 
void SalvaPacienteArquivoBinario (void* p, FILE* file);


/// @brief Obtem CPF de um paciente
/// @param paciente 
/// @return cpf paciente
char* ObtemCPFPaciente (void* paciente);


/// @brief Obtem nome de um paciente
/// @param p 
/// @return nome paciente
char* ObtemNomePaciente (void* p);


/// @brief Obtem data de nascimento paciente
/// @param p 
/// @return data nascimento paciente
char* ObtemDtNascPaciente (void *p);


/// @brief Desaloca memoria de um paciente
/// @param p 
void DesalocaPaciente (void* p);


#endif