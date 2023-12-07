#include "tEncaminhamento.h"
#define TAM_MAX_NOME 100
#define TAM_MAX_CPF 20
#define TAM_MAX_ESPECIALIDADE 50
#define TAM_MAX_MOTIVO 300
#define TAM_MAX_CRM 20
#define TAM_MAX_DATA 20

struct tEncaminhamento {
    char nomePaciente[TAM_MAX_NOME];
    char cpfPaciente[TAM_MAX_CPF];
    char especialidade[TAM_MAX_ESPECIALIDADE];
    char motivo[TAM_MAX_MOTIVO];
    char nomeMedico[TAM_MAX_NOME];
    char CRMmedico [TAM_MAX_CRM];
    char data[TAM_MAX_DATA]; 
};

tEncaminhamento* CriaEncaminhamento (char* nomePac, char* cpfPac, char* nomeMed, char* CRM, char* data) {

    tEncaminhamento* e = (tEncaminhamento*) malloc(sizeof(tEncaminhamento));
    if (e == NULL) {
        printf("Falha na Alocacao do Encaminhamento\n");
        exit(EXIT_FAILURE);
    }

    // Realiza copia dos dados
    strcpy(e->cpfPaciente, cpfPac);
    strcpy(e->CRMmedico, CRM);
    strcpy(e->data, data);
    strcpy(e->nomeMedico, nomeMed);
    strcpy(e->nomePaciente, nomePac);

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ENCAMINHAMENTO:\n");

    printf("ESPECIALIDADE ENCAMINHADA: ");
    scanf("%s", e->especialidade);
    scanf("%*c");

    printf("MOTIVO: ");
    scanf("%[^\n]", e->motivo);
    scanf("%*c");

    printf("ENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    char c; scanf("%c%*c", &c);
    printf("############################################################\n");

    return e;
}

void ImprimeEncaminhamentoNaTela (void* dado) {

    tEncaminhamento* e = (tEncaminhamento*) dado;

    printf("PACIENTE: %s\n", e->nomePaciente);
    printf("CPF: %s\n\n", e->cpfPaciente);
    printf("ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
    printf("MOTIVO: %s\n\n", e->motivo);

    printf("%s (%s)\n", e->nomeMedico, e->CRMmedico);
    printf("%s", e->data);
    printf("\n\n");

}

void ImprimeEncaminhamentoArquivo (void* dado, char* path) {

    tEncaminhamento* e = (tEncaminhamento*) dado;

    char pathDoc [strlen(path) + strlen("/encaminhamento.txt") + 1];

    // Concatenacao do caminho + nome arquivo
    sprintf(pathDoc, "%s/%s", path, "encaminhamento.txt");

    FILE* file = fopen(pathDoc, "a");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo de encaminhamento no diretorio: %s\n", pathDoc);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "PACIENTE: %s\n", e->nomePaciente);
    fprintf(file, "CPF: %s\n\n", e->cpfPaciente);
    fprintf(file, "ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
    fprintf(file, "MOTIVO: %s\n\n", e->motivo);

    fprintf(file, "%s (%s)\n", e->nomeMedico, e->CRMmedico);
    fprintf(file, "%s", e->data);
    fprintf(file, "\n\n");

    fclose(file);
}

void DesalocaEncaminhamento (void* dado) {
    if (!dado) return;
    tEncaminhamento* e = (tEncaminhamento*) dado;
    free(e);
}