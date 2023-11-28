#include "tMedico.h"
#include <stdio.h>
#include <stdlib.h>

struct tMedico {
    tDadosPessoais* dadosPessoais;
    char user[TAM_NOME_USER];
    char senha[TAM_MAX_SENHA];
    char CRM[TAM_CRM];
};

tMedico* CriaMedico () {

    tMedico* medico = (tMedico *) malloc(sizeof(tMedico));
    if (medico == NULL) {
        printf("Falha na Alocacao do Medico\n");
        exit(EXIT_FAILURE);
    }

    medico->dadosPessoais = CriaDadosPessoais();

    return medico;
}

tMedico* CadastraMedico() {

    tMedico* medico = CriaMedico();

    printf("#################### CADASTRO MEDICO #######################\n");
    LeDadosPessoais(medico->dadosPessoais);

    printf("\nCRM: ");
    scanf("%s", medico->CRM);

    printf("\nNOME DE USUARIO: ");
    scanf("%s", medico->user);

    printf("\nSENHA: ");
    scanf("%s", medico->senha);

}

void DesalocaMedico(tMedico* m) {
    if (m == NULL) return;
    DesalocaDadosPessoais(m->dadosPessoais);
    free(m);
}