#ifndef _TENCAMINHAMENTO_H_
#define _TENCAMINHAMENTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tEncaminhamento tEncaminhamento;

tEncaminhamento* CriaEncaminhamento (char* nomePac, char* cpfPac, char* nomeMed, char* CRM, char* data);

void ImprimeEncaminhamentoNaTela (void* dado);

void ImprimeEncaminhamentoArquivo (void* dado, char* path);

void DesalocaEncaminhamento (void* dado);


#endif