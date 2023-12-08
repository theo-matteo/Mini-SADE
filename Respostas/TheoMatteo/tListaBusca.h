#ifndef _TLISTABUSCA_H_
#define _TLISTABUSCA_H_

#include <stdio.h>
#include <stdlib.h>
#include "tPaciente.h"
#include "tDadosPessoais.h"

typedef struct tListaBusca tListaBusca;

tListaBusca* BuscaPessoasArqvBinario (char* nome, FILE* file);

tListaBusca* BuscaPacientes (FILE* file);

void imprimeEmArquivoListaBusca(void *dado, char *path);

void ImprimeListaBusca(void* l);

void DesalocaListaBusca(void* l);

int ObtemQtdPacientesListaBusca (tListaBusca* l);

#endif