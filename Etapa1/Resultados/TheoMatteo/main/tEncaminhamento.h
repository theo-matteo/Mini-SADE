#ifndef _TENCAMINHAMENTO_H_
#define _TENCAMINHAMENTO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct tEncaminhamento tEncaminhamento;


/// @brief Cria uma estrutura com informacoes de um encaminhamento medico
/// @param nomePac 
/// @param cpfPac 
/// @param nomeMed 
/// @param CRM 
/// @param data 
/// @return encaminhamento
tEncaminhamento* CriaEncaminhamento (char* nomePac, char* cpfPac, char* nomeMed, char* CRM, char* data);


/// @brief Imprime encaminhamento na tela
/// @param dado 
void ImprimeEncaminhamentoNaTela (void* dado);

/// @brief Imprime o encaminhamento em um arquivo 
/// @param dado 
/// @param path 
void ImprimeEncaminhamentoArquivo (void* dado, char* path);

/// @brief Desaloca memoria do encaminhamento
/// @param dado 
void DesalocaEncaminhamento (void* dado);


#endif