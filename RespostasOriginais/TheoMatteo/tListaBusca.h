#ifndef _TLISTABUSCA_H_
#define _TLISTABUSCA_H_

#include <stdio.h>
#include <stdlib.h>

#include "tPaciente.h"
#include "tDadosPessoais.h"
#include "utils.h"
#include "tFila.h"

typedef struct tListaBusca tListaBusca;



/// @brief Busca pacientes pelo nome em um arquivo binario (pacientes.bin)
/// @param nome 
/// @param file 
/// @return lista de busca com os pacientes encontrados
tListaBusca* BuscaPessoaNomeArqv (char* nome, FILE* file);

void BuscaPacientes (FILE* file, tFila* fila);

void imprimeEmArquivoListaBusca(void *dado, char *path);

void ImprimeListaBusca(void* l);

void DesalocaListaBusca(void* l);

int ObtemQtdPacientesListaBusca (tListaBusca* l);

#endif