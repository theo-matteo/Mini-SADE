#ifndef _TSECRETARIO_H_
#define _TSECRETARIO_H_

#include "tDadosPessoais.h"
#include "tCredenciaisAcesso.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_MAX_NIVEL_ACESSO 10

typedef struct tSecretario tSecretario;

/// @brief Cadastra novo Secretario a partir da entrada padrao (teclado) e salva no banco de dados
/// @return retorna um ponteiro da estrutura secretario
tSecretario* CadastraSecretario ();


/// @brief Salva informacoes de um secretario em um arquivo binario
/// @param  secretario
/// @param  arquivo
void SalvaSecretarioArquivoBinario (void*, FILE*);



/// @brief Obtem um secretario com as credenciais informadas, se houver retorna ponteiro, senao retorna NULL
/// @param user nome do usuario
/// @param senha senha
/// @param file arquivo
/// @return secretario
tSecretario* ObtemSecretarioArqvBinario (char* user, char* senha, FILE* file);


/// @brief Obtem o nivel de acesso ao sistema de um usuario
/// @param  secretario
/// @return nivel de acesso
char* ObtemNivelAcessoSecretario (tSecretario*);


char* ObtemCPFSecretario (void* sec);

int EhSecretarioADMIN (tSecretario*);

/// @brief Desaloca memoria da estrutura assumindo que o ponteiro eh do tipo tSecretario
/// @param  secretario
void DesalocaSecretario(void*);


#endif