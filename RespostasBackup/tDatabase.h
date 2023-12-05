#ifndef _TDATABASE_H_
#define _TDATABASE_H_

#include "tUsuarioSistema.h"
#include "tSecretario.h"
#include "tMedico.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM_MAX_DIRETORIO 250

typedef enum {
    MEDICO,
    SECRETARIO,
    PACIENTE,
} TipoAtor;


typedef char* (*ObtemCPFPessoaFunc) (void *);
typedef void (*SalvaPessoaArqvFunc)(void *, FILE*);
typedef void (*DesalocaPessoaFunc)(void *);


typedef struct tDatabase tDatabase;

tDatabase* CriaBancodeDados (char* path);

/// @brief Verifica se os arquivos binarios medicos e secretarios estao vazios, caracterizando primeiro acesso
/// @param  sistema
/// @return true or false
bool EhPrimeiroAcessoSistema (tDatabase*);


/// @brief Obtem um usuario do banco de dados atraves das credenciais de seguranca
/// @param user 
/// @param senha 
/// @param  database
/// @return tUsuario
tUsuarioSistema* ObtemUsuariocomCredenciaisBD (char* user, char* senha, tDatabase*);

bool VerificaMesmoCPFBD (TipoAtor tipo, FILE* file, char* cpf);

void CadastraNovoAtorBD (tDatabase* d, TipoAtor tipo);

FILE* ObtemArquivoTipoAtor (tDatabase*, TipoAtor tipo);

ObtemCPFPessoaFunc ObtemFuncaoObterCPFPessoa (TipoAtor tipo);

SalvaPessoaArqvFunc ObtemFuncaoSalvaPessoaArqv (TipoAtor tipo);

DesalocaPessoaFunc ObtemFuncaoDesalocarPessoa (TipoAtor tipo);


FILE* ObtemArquivoSecretarios (tDatabase*);

FILE* ObtemArquivoMedicos (tDatabase*);

FILE* ObtemArquivoConsultas (tDatabase*);

FILE* ObtemArquivoPacientes (tDatabase*);

FILE* ObtemArquivoLesoes (tDatabase*);


/// @brief Desaloca banco de dados fechando arquivos
/// @param  
void DesalocaBancoDados (tDatabase*);




#endif