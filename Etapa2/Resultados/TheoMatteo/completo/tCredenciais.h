#ifndef _TCREDENCIAIS_H_
#define _TCREDENCIAIS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM_MAX_USER 20   
#define TAM_MAX_SENHA 20

typedef struct tCredenciais tCredenciais;


/// @brief Cria credencial com informacoes passadas por parametro
/// @param user user
/// @param senha senha
/// @return credenciais
tCredenciais* CriaCredenciaisAcesso(char* user, char* senha);


/// @brief Le credenciais de acesso de medicos e secretarios
/// @return retorna ponteiro da estrutura com contem dados de acesso
tCredenciais* LeCredenciaisAcesso ();


/// @brief Obtem credenciais de acesso a partir de um arquivo binario
/// @param  arquivo
/// @return credenciais
tCredenciais* ObtemCredenciaisArquivoBinario (FILE* file);


/// @brief Verifica se as credenciais se coincidem, se sim retorna true
/// @param user 
/// @param senha 
/// @param c 
/// @return true or false
bool VerificaCredenciais (char *user, char* senha, tCredenciais* c);


/// @brief Obtem o nome do usuario
/// @param  c
/// @return nome do usuario
char* ObtemUserCredenciais (tCredenciais* c);


/// @brief Obtem a senha do usuario
/// @param c 
/// @return senha do usuarioi
char* ObtemSenhaCredenciais (tCredenciais* c);


/// @brief Obtem o numero de bytes da estrutura tCredenciais
/// @return 
int ObtemQtdBytesCredenciais ();


/// @brief Salva informacoes das credenciais em um arquivo binario
/// @param  credenciais
/// @param  arquivo
void SalvaCredenciaisArqvBinario (tCredenciais* c, FILE* file);


/// @brief Desaloca memoria da estrutura
/// @param credenciais
void DesalocaCredenciais (tCredenciais* c);

#endif