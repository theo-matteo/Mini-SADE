#ifndef _TCREDENCIAISACESSO_H_
#define _TCREDENCIAISACESSO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM_MAX_USER 20   
#define TAM_MAX_SENHA 20

typedef struct tCredenciaisAcesso tCredenciaisAcesso;


/// @brief Cria credencial com informacoes passadas por parametro
/// @param user user
/// @param senha senha
/// @return credenciais
tCredenciaisAcesso* CriaCredenciaisAcesso(char* user, char* senha);

/// @brief Le credenciais de acesso de medicos e secretarios
/// @return retorna ponteiro da estrutura com contem dados de acesso
tCredenciaisAcesso* LeCredenciaisAcesso ();


/// @brief Obtem credenciais de acesso a partir de um arquivo binario
/// @param  arquivo
/// @return credenciais
tCredenciaisAcesso* ObtemCredenciaisArquivoBinario (FILE*);


/// @brief 
/// @param user 
/// @param senha 
/// @param c 
/// @return 
bool CrediciaisSaoIguais (char *user, char* senha, tCredenciaisAcesso* c);


char* ObtemUserCredenciais (tCredenciaisAcesso*);


char* ObtemSenhaCredenciais (tCredenciaisAcesso*);


/// @brief Salva informacoes das credenciais em um arquivo binario
/// @param  credenciais
/// @param  arquivo
void SalvaCredenciaisArqvBinario (tCredenciaisAcesso*, FILE*);

/// @brief Desaloca memoria da estrutura
/// @param credenciais
void DesalocaCredenciais (tCredenciaisAcesso*);

#endif