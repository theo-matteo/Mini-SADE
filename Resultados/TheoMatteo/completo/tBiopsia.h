#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#include <stdio.h>
#include <stdlib.h>
#include "tLesao.h"

#include "utils.h"
#include "vector.h"

typedef struct tBiopsia tBiopsia;



tBiopsia* AlocaBiopsia (Vector* l, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data);

tBiopsia* SolicitaBiopsia (Vector* lesoes, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data);

Vector* ObtemLesoesCirurgicas (Vector* lesoes);


/// @brief Imprime biopsia na tela
/// @param dado 
void imprimeNaTelaBiopsia(void *dado);


/// @brief Imprime biopsia em um arquivo dado um caminho
/// @param dado 
/// @param path 
void imprimeEmArquivoBiopsia(void *dado, char *path);

void ImprimeErroBiopsia ();

void ImprimeSucessoBiopsia();

/// @brief Desaloca memoria de uma biopsia
/// @param dado 
void DesalocaBiopsia (void* dado);


#endif