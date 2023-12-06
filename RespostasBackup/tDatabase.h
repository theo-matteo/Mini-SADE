#ifndef _TDATABASE_H_
#define _TDATABASE_H_

#include "tUsuarioSistema.h"
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


tDatabase* CriaBancodeDados (char* path);

/// @brief Verifica se os arquivos binarios medicos e secretarios estao vazios, caracterizando primeiro acesso
/// @param  sistema
/// @return true or false
bool EhPrimeiroAcessoSistema (tDatabase* d);


/// @brief Obtem um usuario do banco de dados atraves das credenciais de seguranca
/// @param user 
/// @param senha 
/// @param  database
/// @return tUsuario
tUsuarioSistema* ObtemUsuariocomCredenciaisBD (char* user, char* senha, tDatabase* d);


bool VerificaMesmoCPFBD (tipoPessoa tipo, FILE* file, char* cpf);

void* ObtemPessoaArquivoBinario (tipoPessoa tipo, FILE* file, char* cpf);

void CadastraNovaPessoaBD (tDatabase* d, tipoPessoa tipo);

FILE* ObtemArquivoTipoPessoa (tDatabase* d, tipoPessoa tipo);

ObtemCPFPessoaFunc ObtemFuncaoObterCPFPessoa (tipoPessoa tipo);

SalvaPessoaArqvFunc ObtemFuncaoSalvaPessoaArqv (tipoPessoa tipo);

DesalocaPessoaFunc ObtemFuncaoDesalocarPessoa (tipoPessoa tipo);

FILE* ObtemArquivoSecretarios (tDatabase* d);

FILE* ObtemArquivoMedicos (tDatabase* d);

FILE* ObtemArquivoConsultas (tDatabase* d);

FILE* ObtemArquivoPacientes (tDatabase* d);

FILE* ObtemArquivoLesoes (tDatabase* d);

/// @brief Desaloca banco de dados fechando arquivos
/// @param  
void DesalocaBancoDados (tDatabase* d);




#endif