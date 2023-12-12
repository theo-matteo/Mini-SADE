#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#include <stdio.h>
#include <stdlib.h>
#include "tLesao.h"

#include "utils.h"
#include "vector.h"

typedef struct tBiopsia tBiopsia;



/// @brief Aloca uma biopsia e copia as informacoes passadas por parametro
/// @param l (realiza atribuicao)
/// @param nomePaciente 
/// @param cpfPaciente 
/// @param nomeMedico 
/// @param CRM 
/// @param data 
/// @return biopsia
tBiopsia* AlocaBiopsia (Vector* l, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data);


/// @brief Solicita a criacao de uma biopsia e verifica se eh possivel
/// @param lesoes 
/// @param nomePaciente 
/// @param cpfPaciente 
/// @param nomeMedico 
/// @param CRM 
/// @param data 
/// @return biopsia
tBiopsia* SolicitaBiopsia (Vector* lesoes, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data);


/// @brief Cria um vetor com as lesoes cirurgicas de um paciente, se nao tiver retorna NULL
/// @param lesoes 
/// @return vetor de lesoes cirurgicas
Vector* ObtemLesoesCirurgicas (Vector* lesoes);


/// @brief Imprime biopsia na tela
/// @param dado 
void imprimeNaTelaBiopsia(void *dado);


/// @brief Imprime biopsia em um arquivo dado um caminho
/// @param dado 
/// @param path 
void imprimeEmArquivoBiopsia(void *dado, char *path);


/// @brief Imprime mensagem de erro caso nao seja possivel solicitar a biopsia
void ImprimeErroBiopsia ();


/// @brief Imprime mensagem de sucesso caso a criacao do documento foi realizada com sucesso 
void ImprimeSucessoBiopsia();


/// @brief Desaloca memoria de uma biopsia
/// @param dado 
void DesalocaBiopsia (void* dado);


#endif