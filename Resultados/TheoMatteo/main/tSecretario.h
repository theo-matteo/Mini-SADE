#ifndef _TSECRETARIO_H_
#define _TSECRETARIO_H_

#include "tDadosPessoais.h"
#include "tCredenciais.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_MAX_NIVEL_ACESSO 10

typedef struct tSecretario tSecretario;

/// @brief Cadastra novo Secretario a partir da entrada padrao (teclado) e salva no banco de dados
/// @return retorna um ponteiro da estrutura secretario
tSecretario* CadastraSecretario ();


/// @brief Cria um secretario e adiciona as informacoes passadas por parametro
/// @param d 
/// @param c 
/// @param nivelAcesso 
/// @return secretario
tSecretario* CriaSecretario (tDadosPessoais* d, tCredenciais* c, char* nivelAcesso);


/// @brief Salva informacoes de um secretario em um arquivo binario
/// @param  secretario
/// @param  arquivo
void SalvaSecretarioArquivoBinario (void* sec, FILE* file);


/// @brief Obtem um secretario com as credenciais informadas, se houver retorna ponteiro, senao retorna NULL
/// @param user nome do usuario
/// @param senha senha
/// @param file arquivo
/// @return secretario
tSecretario* ObtemSecretarioBD (char* user, char* senha, FILE* file);


/// @brief Obtem o nivel de acesso ao sistema de um usuario
/// @param  secretario
/// @return nivel de acesso
char* ObtemNivelAcessoSecretario (tSecretario* s);


/// @brief Obtem CPF de um secretario
/// @param sec 
/// @return CPF secretario
char* ObtemCPFSecretario (void* sec);


/// @brief Verifica se o secretario eh admin
/// @param sec 
/// @return 1 sim e 0 nao
int VerificaAcessoAdminSec (tSecretario* sec);


/// @brief Desaloca memoria da estrutura assumindo que o ponteiro eh do tipo tSecretario
/// @param  secretario
void DesalocaSecretario(void* sec);


#endif