#ifndef _TMEDICO_H_
#define _TMEDICO_H_

#include "tDadosPessoais.h"
#include "tCredenciais.h"
#include "vector.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAM_CRM 12

typedef struct tMedico tMedico;


/// @brief Cadastra um novo medico a partir da entrada padrao
/// @return medico
tMedico* CadastraMedico();


/// @brief Aloca memoria para um medico e seta informacoes passadas por parametro
/// @param d 
/// @param c 
/// @param CRM 
/// @return medico
tMedico* CriaMedico (tDadosPessoais* d, tCredenciais* c, char* CRM);


/// @brief Salva medico em um arquivo binario
/// @param m 
/// @param file 
void SalvaMedicoArquivoBinario (void* m, FILE* file);


/// @brief Obtem um medico no banco de dados a partir de credenciais
/// @param user 
/// @param senha 
/// @param file 
/// @return medico
tMedico* ObtemMedicoBD(char* user, char* senha, FILE* file);

/* Obtem todos os medicos do banco de dados */
Vector* ObtemMedicosBD (FILE* file);

/* Imprime todos os medicos */
void ImprimeTodosMedicos (Vector* v, FILE* file);

/// @brief Obtem cpf de um medico
/// @param m 
/// @return cpf medico
char* ObtemCPFMedico (void* m);


/// @brief Obtem CRM de um medico
/// @param m 
/// @return crm medico
char* ObtemCRMMedico (void *m);


/// @brief Obtem nome de um medico
/// @param m 
/// @return nome medico
char* ObtemNomeMedico (void *m);


/// @brief Desaloca memoria de um medico
/// @param m 
void DesalocaMedico(void* m);


#endif