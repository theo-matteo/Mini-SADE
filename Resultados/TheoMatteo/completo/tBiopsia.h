#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#include <stdio.h>
#include <stdlib.h>
#include "tLesao.h"

#include "utils.h"
#include "vector.h"

typedef struct tBiopsia tBiopsia;



/// @brief Aloca uma biopsia com as informacoes passadas por parametro
/// @param l 
/// @param qtd 
/// @param nomePaciente 
/// @param cpfPaciente 
/// @param nomeMedico 
/// @param CRM 
/// @param data 
/// @return biopsia
tBiopsia* AlocaBiopsia (Vector* l, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data);



/// @brief Solicita uma biopsia com as informacoes passadas de uma consulta
/// @param lesoes 
/// @param qtdLesoes 
/// @param nomePaciente 
/// @param cpfPaciente 
/// @param nomeMedico 
/// @param CRM 
/// @param data 
/// @return biopsia
tBiopsia* SolicitaBiopsia (Vector* lesoes, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data);



/// @brief Imprime biopsia na tela
/// @param dado 
void imprimeNaTelaBiopsia(void *dado);



/// @brief Imprime biopsia em um arquivo dado um caminho
/// @param dado 
/// @param path 
void imprimeEmArquivoBiopsia(void *dado, char *path);



/// @brief Desaloca memoria de uma biopsia
/// @param dado 
void DesalocaBiopsia (void* dado);


#endif