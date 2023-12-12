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
#include "vector.h"

#define TAM_MAX_TIPO_PELE 5
#define TAM_MAX_CPF 15
#define TAM_MAX_DATA 11
#define TAM_MAX_NOME 100
#define TAM_CRM 12
#define TAM_INSTRUCOES 300

typedef struct tConsulta tConsulta;


/// @brief Executa a consulta dado as informacoes da base da dados e o usuario
/// @param user 
/// @param d 
/// @param f 
/// @param l 
/// @return consulta
void ExecutaConsulta (tUsuario* user, tDatabase* d, tFila* f, Vector* dados_receita);


/// @brief Aloca consulta e le informacoes da entrada padrao
/// @param cpfPaciente 
/// @param cpfMedico 
/// @param CRM 
/// @return consulta
tConsulta* CriaConsulta(char* cpfPaciente, char* cpfMedico, char* CRM);


/// @brief Adiciona uma nova lesao a consulta
/// @param c 
/// @param l 
void AdicionaLesaoConsulta (tConsulta* c, tLesao* l);


/// @brief Ler informacoes da receita e cria uma receita
/// @param nomePaciente 
/// @param CRM 
/// @param nomeMedico 
/// @param data 
/// @param l 
/// @return receita
tReceita* PreencheCriaReceitaMedica (char* nomePaciente, char* CRM, char* nomeMedico, char* data, Vector* dados_receita);


/// @brief Obtem data da realizacao da consulta
/// @param c 
/// @return data
char* ObtemDataConsulta (tConsulta* c);


/// @brief Obtem CPF do paciente
/// @param c 
/// @return CPF do paciente 
char* ObtemCPFPacienteConsulta (tConsulta* c);


/// @brief Salva consulta no arquivo binario
/// @param consulta 
/// @param file 
void SalvaConsultaArquivoBinario (tConsulta* consulta, FILE* file);


/// @brief Obtem quantidade de consultas dentro do arquivo binario
/// @param file 
/// @return total consultas realizadas
int ObtemQtdConsultasBinario (FILE* file);


/// @brief Obtem quantidade de CPF unicos em um array de cpfs
/// @param cpfs 
/// @param qtd 
/// @return qtd cpf unicos
int ObtemQtdCpfUnicos (char** cpfs, int qtd);


/// @brief Desaloca memoria de uma consulta
/// @param c 
void DesalocaConsulta (void* dado);


#endif