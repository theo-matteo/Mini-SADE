#ifndef _TRELATORIO_H_
#define _TRELATORIO_H_

#include <stdio.h>
#include <stdlib.h>
#include "tDatabase.h"
#include "tConsulta.h"

typedef struct tRelatorio tRelatorio;


/// @brief Cria um relatorio e aloca dinamicamente
/// @return relatorio
tRelatorio* CriaRelatorio ();


/// @brief 
/// @param database 
/// @return 
tRelatorio* GeraRelatorio (tDatabase* database);


/// @brief Imprime relatorio na tela
/// @param dado 
void ImprimeRelatorioTela (void* dado);


/// @brief Preenche relatorio a partir da obtencao de dados do arquivo de lesoes
/// @param file 
/// @param r 
void PreencheRelatorioDadosLesoes (FILE* file, tRelatorio* r);


/// @brief Preenche relatorio a partir da obtencao de dados do arquivo de pacientes
/// @param file 
/// @param r 
void PreencheRelatorioDadosPacientes (FILE* file, tRelatorio* r);


/// @brief Imprime relatorio em um arquivo 
/// @param dado 
/// @param path 
void ImprimeRelatorioArquivo (void* dado, char* path);


/// @brief Desaloca memoria de um arquivo
/// @param dado 
void DesalocaRelatorio (void* dado);

#endif