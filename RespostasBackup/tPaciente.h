#ifndef _TPACIENTE_H_
#define _TPACIENTE_H_


#include "tDadosPessoais.h"
#include "tCredenciaisAcesso.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tPaciente tPaciente;

tPaciente* CadastraPaciente ();


void DesalocaPaciente (void*);


#endif