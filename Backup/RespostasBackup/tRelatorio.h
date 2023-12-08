#ifndef _TRELATORIO_H_
#define _TRELATORIO_H_

#include <stdio.h>
#include <stdlib.h>
#include "tDatabase.h"

typedef struct tRelatorio tRelatorio;

tRelatorio* CriaRelatorio (tDatabase* database);

void ImprimeRelatorioTela (void* dado);

void ImprimeRelatorioArquivo (void* dado, char* path);

void DesalocaRelatorio (void* dado);

#endif