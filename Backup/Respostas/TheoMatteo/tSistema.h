#ifndef _TSISTEMA_H_
#define _TSISTEMA_H_

#include "tFila.h"
#include "tDocumento.h"
#include "tDadosPessoais.h"
#include "tMedico.h"
#include "tSecretario.h"
#include "tListaBusca.h"
#include "tConsulta.h"
#include "tRelatorio.h"
#include "tDadosReceita.h"

#include "tUsuario.h"
#include "tDatabase.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct tSistema tSistema;


/// @brief Aloca memoria dinamicamente para o sistema
/// @param path caminho do diretorios dos arquivos .txt
/// @return sistema
tSistema* CriaSistema (char* path);


/// @brief Acessa sistema com base nas credenciais fornecidas pela entrada padrao
/// @param  sistema
/// @return true (sucesso) or false 
bool AcessaSistemaUsuario (tSistema* s);


/// @brief Executa sistema 
/// @param  s
void ExecutaSistema (tSistema* s);


/// @brief Obtem usuario que esta logado no sistema
/// @param s 
/// @return usuario
tUsuario* ObtemUsuario (tSistema* s);


/// @brief Obtem banco de dados do sistema
/// @param s 
/// @return banco de dados
tDatabase* ObtemBDSistema (tSistema* s);


/// @brief Executa fila de impressao de documentos
/// @param s 
void ExecutaFiladeImpressao (tSistema* s);


/// @brief Executa relatorio 
/// @param s 
void ExecutaRelatorio (tSistema* s);


/// @brief Obtem fila de documentos do sistema
/// @param s 
/// @return fila
tFila* ObtemFilaImprSistema (tSistema* s);


/// @brief Obtem caminho de impressao dos documentos
/// @param s 
/// @return caminho de impressao
char* ObtemPathImprDocs (tSistema* s);


/// @brief Desaloca memoria do sistema
/// @param  
void DesalocaSistema (tSistema*);



#endif