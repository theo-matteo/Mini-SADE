#include "tBiopsia.h"
#define TAM_MAX_NOME 100
#define TAM_MAX_CPF 20
#define TAM_MAX_CRM 20
#define TAM_MAX_DATA 20

struct tBiopsia {
    char nomePaciente[TAM_MAX_NOME];
    char cpfPaciente[TAM_MAX_CPF];
    char nomeMedico[TAM_MAX_NOME];
    char CRMmedico [TAM_MAX_CRM];
    char data[TAM_MAX_DATA];
    tLesao** lesoes;
    int qtdLesoes;
};


tBiopsia* CriaBiopsia (tLesao** l, int qtd, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data) {

    tBiopsia* biopsia = (tBiopsia*) malloc(sizeof(tBiopsia));
    if (biopsia == NULL) {
        printf("Falha na Alocacao da Biopsia\n");
        exit(EXIT_FAILURE);
    }

    memset(biopsia->nomePaciente, '\0', TAM_MAX_NOME);
    memset(biopsia->cpfPaciente, '\0', TAM_MAX_CPF);
    memset(biopsia->nomeMedico, '\0', TAM_MAX_NOME);
    memset(biopsia->CRMmedico, '\0', TAM_MAX_CRM);
    memset(biopsia->data, '\0', TAM_MAX_DATA);
    
    biopsia->lesoes = l;
    biopsia->qtdLesoes = qtd;
    strcpy(biopsia->nomePaciente, nomePaciente);
    strcpy(biopsia->cpfPaciente, cpfPaciente);
    strpcy(biopsia->nomeMedico, nomeMedico);
    strcpy(biopsia->CRMmedico, CRM);
    strcpy(biopsia->data, data);


    return biopsia;
}


tBiopsia* SolicitaBiopsia (tLesao** lesoes, int qtdLesoes, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data) {

    tLesao** lesoesCirurgicas = NULL;
    int qtdLesoesCirurgicas = 0;

    for (int i = 0; i < qtdLesoes; i++) {
        if (LesaoFoiEncaminhadaPraCirurgia(lesoes[i])) {
            qtdLesoesCirurgicas++;
            lesoesCirurgicas = (tLesao**) realloc(lesoesCirurgicas, sizeof(tLesao *) * qtdLesoesCirurgicas);
            lesoesCirurgicas[qtdLesoesCirurgicas - 1] = ClonaLesao(lesoes[i]);
        }  
    }

    if (qtdLesoesCirurgicas == 0) {
        printf("#################### CONSULTA MEDICA #######################\n");
        printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        char c; scanf("%c%*c");
        printf("############################################################");
        return NULL;
    }

    tBiopsia* biopsia = CriaBiopsia(lesoesCirurgicas, qtdLesoesCirurgicas, nomePaciente, cpfPaciente, nomeMedico, CRM, data);
    return biopsia;
}

void imprimeNaTelaBiopsia(void *dado) {

    tBiopsia* b = (tBiopsia*) dado;

    printf("PACIENTE: %s\n", b->nomePaciente);
    printf("CPF: %s\n", b->cpfPaciente);
    printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");

    for (int i = 0; i < b->qtdLesoes; i++) {
        tLesao* lesao = b->lesoes[i];
        printf("L%d - %s - %s - %dMM\n", i + 1, ObtemDiagnosticoLesao(lesao), ObtemRegiaoCorpoLesao(lesao), ObtemTamanhoLesao(lesao));
    }

    printf("%s (%s)\n", b->nomeMedico, b->CRMmedico);
    printf("%s", b->data);
    printf("\n\n");

}

void imprimeEmArquivoBiopsia(void *dado, char *path);


void DesalocaBiopsia (void* dado) {

    if (!dado) return;

    tBiopsia* b = (tBiopsia*) dado;

    for (int i = 0; i < b->qtdLesoes; i++) {
        DesalocaLesao(b->lesoes[i]);
    }

    free(b->lesoes);
    free(b);
}

