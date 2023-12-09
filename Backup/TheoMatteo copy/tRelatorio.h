#ifndef _TRELATORIO_H_
#define _TRELATORIO_H_

#include <stdio.h>
#include <stdlib.h>
#include "tDatabase.h"
#include "tConsulta.h"

typedef struct tRelatorio tRelatorio;

tRelatorio* CriaRelatorio ();

tRelatorio* GeraRelatorioCompleto(tDatabase* database);

void ImprimeRelatorioTela (void* dado);

void PreencheRelatorioDadosLesoes (FILE* file, tRelatorio* r);

void PreencheRelatorioDadosPacientes (FILE* file, tRelatorio* r);

void ImprimeRelatorioArquivo (void* dado, char* path);

void DesalocaRelatorio (void* dado);

#endif