#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#include <stdio.h>
#include <stdlib.h>
#include "tLesao.h"
#include "utils.h"


typedef struct tBiopsia tBiopsia;

/// @brief Aloca e inicializa uma biopsia
/// @param l 
/// @param qtd 
/// @param nomePaciente 
/// @param cpfPaciente 
/// @param nomeMedico 
/// @param CRM 
/// @param data 
/// @return biopsia
tBiopsia* AlocaBiopsia (tLesao** l, int qtd, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data);



/// @brief Solicita uma biopsia dada uma lista de lesoes e informacoes de uma consulta
/// @param lesoes 
/// @param qtdLesoes 
/// @param nomePaciente 
/// @param cpfPaciente 
/// @param nomeMedico 
/// @param CRM 
/// @param data 
/// @return biopsia
tBiopsia* SolicitaBiopsia (tLesao** lesoes, int qtdLesoes, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data);


/// @brief Imprime uma biopsia na tela
/// @param dado 
void imprimeNaTelaBiopsia(void *dado);


/// @brief Imprime em um arquivo uma biospai
/// @param dado 
/// @param path 
void imprimeEmArquivoBiopsia(void *dado, char *path);



/// @brief Desaloca memoria de uma biopsia
/// @param dado 
void DesalocaBiopsia (void* dado);


#endif