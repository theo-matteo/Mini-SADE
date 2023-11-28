#ifndef _TSISTEMA_H_
#define _TSISTEMA_H_

#include <stdbool.h>
#define TAM_MAX_DIRETORIO 250
#define NOME_ARQV_MEDICO "medicos.bin"

typedef enum {
    MEDICO,
    ADMIN,
    USER,
} userType;


typedef struct tSistema tSistema;


/// @brief 
/// @param path 
/// @return 
tSistema* CriaSistema (char* path);

void AcessaSistemaUsuario (tSistema*);

bool EhPrimeiroAcessoSistema (tSistema*);

void DesalocaSistema (tSistema*);

void IniciaSistema (tSistema*);

#endif