#ifndef _TSISTEMA_H_
#define _TSISTEMA_H_

#include "tFila.h"
#include "tDocumento.h"
#include "tDadosPessoais.h"
#include "tMedico.h"
#include "tSecretario.h"

#include "tUsuarioSistema.h"
#include "tDatabase.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct tSistema tSistema;


/// @brief Aloca memoria dinamicamente para o sistema
/// @param path caminho do diretorios dos arquivos .txt
/// @return retorna ponteiro para estrutura tSistema
tSistema* CriaSistema (char* path);

/// @brief Acessa sistema com base nas credenciais fornecidas pela entrada padrao
/// @param  sistema
/// @return retorna true se o login foi realizado com sucesso, senao retorna false
bool AcessaSistemaUsuario (tSistema*);


/// @brief Inicia o sistema, disponibilizando acoes para o usuario
/// @param  s
void IniciaSistema (tSistema*);


/// @brief Obtem usuario que esta logado no sistema
/// @param s 
/// @return usuario
tUsuarioSistema* ObtemUsuario (tSistema* s);

tDatabase* ObtemBDSistema (tSistema* s);


void DesalocaSistema (tSistema*);



#endif