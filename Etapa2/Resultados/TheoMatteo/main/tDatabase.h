#ifndef _TDATABASE_H_
#define _TDATABASE_H_

#include "tUsuario.h"
#include "tSecretario.h"
#include "tMedico.h"
#include "tPaciente.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM_MAX_DIRETORIO 250

typedef enum {
    MEDICO,
    SECRETARIO,
    PACIENTE,
} tipoPessoa;


typedef char* (*ObtemCPFPessoaFunc) (void *);
typedef void (*SalvaPessoaArqvFunc)(void *, FILE*);
typedef void (*DesalocaPessoaFunc)(void *);
typedef struct tDatabase tDatabase;


/// @brief Cria um banco de dados dado o caminho dos arquivos binarios
/// @param path 
/// @return banco de dados
tDatabase* CriaBancodeDados (char* path);


/// @brief Verifica se eh o primeiro acesso ao sistema
/// @param d 
/// @return true or false
bool EhPrimeiroAcessoSistema (tDatabase* d);


/// @brief Abre um arquivo binario dado o nome do arquivo e o caminho 
/// @param path 
/// @param filename 
/// @return arquivo
FILE* AbreArquivoBinario(char* path, char* filename);


/// @brief Verifica se um arquivo esta vazio verificando a posicao do ponteiro no final do arquivo
/// @param file 
/// @return true or false
bool ArquivoEstaVazio (FILE* file);


/// @brief Realiza autenticacao de login dado as credenciais e o banco de dados para verificacao
/// @param user 
/// @param senha 
/// @param d 
/// @return usuario do sistema
tUsuario* AutenticaUsuario (char* user, char* senha, tDatabase* d);


/// @brief Adiciona uma pessoa ao banco de dados dependendo do seu tipo
/// @param d 
/// @param tipo 
void AdicionaPessoaBD (tDatabase* d, tipoPessoa tipo);


/// @brief Realiza busca de pessoa de acordo com seu tipo e o cpf informado
/// @param tipo 
/// @param file 
/// @param cpf 
/// @return pessoa 
void* BuscaPessoaPorCpf (tipoPessoa tipo, FILE* file, char* cpf);



/// @brief Obtem arquivo binario de acordo com o tipo da pessoa
/// @param d 
/// @param tipo 
/// @return arquivo
FILE* ObtemArquivoTipoPessoa (tDatabase* d, tipoPessoa tipo);


/// @brief Obtem funcao de obter cpf de acordo com o tipo da pessoa
/// @param tipo 
/// @return funcao obter cpf
ObtemCPFPessoaFunc ObtemFuncaoObterCPFPessoa (tipoPessoa tipo);


/// @brief Obtem funcao de salvar pessoa em um arquivo binario de acordo com o tipo
/// @param tipo 
/// @return funcao salvar em arquivo binario
SalvaPessoaArqvFunc ObtemFuncaoSalvaPessoaArqv (tipoPessoa tipo);


/// @brief Obtem funcao de desalocar pessoa de acordo com seu tipo
/// @param tipo 
/// @return funcao desalocar pessoa 
DesalocaPessoaFunc ObtemFuncaoDesalocarPessoa (tipoPessoa tipo);

/* Funcao para obter secretario do arquivo de inicio */
tSecretario* ObtemSecretarioArqvInicio (tDatabase* d);

/* Imprime todos os medicos do banco de dados */
void ImprimeMedicosBD (tDatabase* d, char* path);

/* Imprime todos os pacientes do banco de dados*/
void ImprimePacientesBD (tDatabase* d, char* path);

/* Obtem arquivo de inicio */
FILE* ObtemArqvInicio (tDatabase* d);

/* Imprime todos os secretarios do BD*/
void ImprimeSecretariosBD (tDatabase* d, char* path);

/// @brief Obtem arquivo binario dos secretarios
/// @param d 
/// @return arquivo secretarios
FILE* ObtemArquivoSecretarios (tDatabase* d);


/// @brief Obtem arquivo binario dos medicos
/// @param d 
/// @return arquivo medicos
FILE* ObtemArquivoMedicos (tDatabase* d);


/// @brief Obtem arquivo binario de consultas
/// @param d 
/// @return arquivo consultas
FILE* ObtemArquivoConsultas (tDatabase* d);


/// @brief Obtem arquivo binario de pacientes
/// @param d 
/// @return arquivo pacientes
FILE* ObtemArquivoPacientes (tDatabase* d);


/// @brief Obtem arquivo binarios de lesoes
/// @param d 
/// @return arquivo lesoes
FILE* ObtemArquivoLesoes (tDatabase* d);


/// @brief Desaloca memoria do banco de dados e fecha os arquivos
/// @param d 
void DesalocaBancoDados (tDatabase* d);



#endif