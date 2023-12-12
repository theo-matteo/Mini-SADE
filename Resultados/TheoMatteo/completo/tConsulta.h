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



/// @brief Executa uma consulta medica de acordo com os parametros 
/// @param user (usuario que esta logado no sistema)
/// @param d (banco de dados do sistema)
/// @param f (fila de impressao de documentos)
/// @param dados_receita (dados das receitas cadastradas)
void ExecutaConsulta (tUsuario* user, tDatabase* d, tFila* f, Vector* dados_receita);


/// @brief Aloca consulta, le informacoes da entrada padrao e copia informacoes passadas por parametro
/// @param cpfPaciente 
/// @param cpfMedico 
/// @param CRM 
/// @return consulta
tConsulta* CriaConsulta(char* cpfPaciente, char* cpfMedico, char* CRM);

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


/// @brief Imprime mensagem de erro caso nao encontre um paciente para realizacao da consulta
void ImprimeErroConsulta();


/// @brief Desaloca memoria de uma consulta
/// @param c 
void DesalocaConsulta (void* dado);


#endif