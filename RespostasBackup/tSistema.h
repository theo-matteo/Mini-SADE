#ifndef _TSISTEMA_H_
#define _TSISTEMA_H_

#include "tFila.h"
#include "tDocumento.h"
#include "tDadosPessoais.h"
#include "tMedico.h"
#include "tSecretario.h"
#include "tUsuarioSistema.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_DIRETORIO 250
typedef struct tSistema tSistema;


/// @brief Aloca memoria dinamicamente para o sistema
/// @param path caminho do diretorios dos arquivos .txt
/// @return retorna ponteiro para estrutura tSistema
tSistema* CriaSistema (char* path);


/// @brief Verifica se os arquivos binarios medicos e secretarios estao vazios, caracterizando primeiro acesso
/// @param  sistema
/// @return true or false
bool EhPrimeiroAcessoSistema (tSistema*);

/// @brief Cadastra um novo usuario e configura o ambiente do sistema em caso de primeiro acesso
/// @param  sistema
void ConfiguraPrimeiroAcessoSistema(tSistema*);


/// @brief Acessa sistema com base nas credenciais fornecidas pela entrada padrao
/// @param  sistema
/// @return retorna true se o login foi realizado com sucesso, senao retorna false
bool AcessaSistemaUsuario (tSistema*);

void SalvaAtorArquivoBinario (FILE* file, userType tipoUsuario);

void LogaSecretarioSistema (tSecretario*, tSistema*);

void LogaMedicoSistema (tMedico*, tSistema*);

void DesalocaSistema (tSistema*);

void IniciaSistema (tSistema*);

#endif