#ifndef _TMEDICO_H_
#define _TMEDICO_H_

#include "tDadosPessoais.h"
#include "tCredenciaisAcesso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct tMedico tMedico;



void CadastraMedico(FILE* file);


tMedico* CriaMedico (tDadosPessoais*, tCredenciaisAcesso*, char* CRM);


/// @brief Salva dados do medico em  um arquivo binario, assumindo que o arquivo ja esta aberto
/// @param  tMedico
/// @param  arquivo
void SalvaMedicoArquivoBinario (tMedico*, FILE*);


tMedico* ObtemMedicoArquivoBinario (char* user, char* senha, FILE* file);


/// @brief Desaloca um medico assumindo que o ponteiro recebido por parametro eh do tipo tMedico
/// @param  tMedico pointer
void DesalocaMedico(void*);


#endif