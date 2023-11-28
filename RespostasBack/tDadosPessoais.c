#include "tDadosPessoais.h"
#include <stdio.h>
#include <stdlib.h>

struct tDadosPessoais {
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char dtNasc[TAM_DATA];
    char tel[TAM_TELEFONE];
    char genero;
};

tDadosPessoais* CriaDadosPessoais () {

    tDadosPessoais* d = (tDadosPessoais *) malloc(sizeof(tDadosPessoais));
    if (d == NULL) {
        printf("Falha na Alocacao dos Dados Pessoais \n");
        exit(EXIT_FAILURE);
    }

    return d;
}

void LeDadosPessoais(tDadosPessoais* d) {

    printf("NOME COMPLETO: ");
    scanf(" %[^\n]\n", d->nome);
    
    printf("\nCPF: ");
    scanf("%s", d->cpf);

    printf("\nDATA DE NASCIMENTO: ");
    scanf("%s", d->dtNasc);

    printf("\nTELEFONE: ");
    scanf("%s", d->tel);

    printf("\nGENERO: ");
    scanf("%c", &d->genero);
}


void DesalocaDadosPessoais(tDadosPessoais* d) {
    if (d) free(d);
}