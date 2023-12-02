#include "tSecretario.h"
#include <stdio.h>
#include <stdlib.h>

struct tSecretario {
    tDadosPessoais* dadosPessoais;
    char user[TAM_NOME_USER];
    char senha[TAM_MAX_SENHA];
    tipoSecretario tipo;
};

tSecretario* CriaSecretario() {

    tSecretario* s = (tSecretario*) malloc(sizeof(tSecretario));
    if (s == NULL) {
        printf("Falha na Alocacao do Secretario \n");
        exit(EXIT_FAILURE);
    }

    return s;
}



void DesalocaSecretario(tSecretario* s) {
    if (s == NULL) return;
    DesalocaDadosPessoais(s->dadosPessoais);
    free(s);
}