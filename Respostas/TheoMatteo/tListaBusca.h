#ifndef _TLISTABUSCA_H_
#define _TLISTABUSCA_H_

#include <stdio.h>
#include <stdlib.h>

#include "tPaciente.h"
#include "tDadosPessoais.h"
#include "utils.h"
#include "tFila.h"

typedef struct tListaBusca tListaBusca;


/// @brief Busca pacientes no banco de dados
/// @param file 
/// @param fila 
void BuscaPacientes (FILE* file, tFila* fila);


/// @brief Obtem uma lista de pacientes de acordo com o nome em um arquivo binario
/// @param nome 
/// @param file 
/// @return lista de busca
tListaBusca* BuscaPacientesNomeArqvBinario (char* nome, FILE* file);


/// @brief Imprime lista de busca em um arquivo 
/// @param dado 
/// @param path 
void imprimeEmArquivoListaBusca(void *dado, char *path);


/// @brief Imprime lista de busca na tela
/// @param l 
void ImprimeListaBusca(void* l);


/// @brief Desaloca lista de busca
/// @param l 
void DesalocaListaBusca(void* l);


/// @brief Obtem quantidade de pacientes da lista de busca
/// @param l 
/// @return qtd pacientes lista busca
int ObtemQtdPacientesListaBusca (tListaBusca* l);

#endif