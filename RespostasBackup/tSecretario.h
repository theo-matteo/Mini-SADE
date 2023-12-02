#ifndef _TSECRETARIO_H_
#define _TSECRETARIO_H_

#include "tDadosPessoais.h"
#define TAM_NOME_USER 20   
#define TAM_MAX_SENHA 20

typedef struct tSecretario tSecretario;

typedef enum {
    ADMIN = 0,
    USER = 1
} tipoSecretario;


tSecretario* CriaSecretario();

void LeSecretario (tSecretario*);

void DesalocaSecretario(tSecretario*);


#endif