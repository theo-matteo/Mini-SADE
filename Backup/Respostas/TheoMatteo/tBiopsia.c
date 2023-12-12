#include "tBiopsia.h"
#define TAM_MAX_NOME 100
#define TAM_MAX_CPF 15
#define TAM_MAX_CRM 12
#define TAM_MAX_DATA 11

struct tBiopsia {


    // Informacoes obtidas da consulta
    char nomePaciente[TAM_MAX_NOME];
    char cpfPaciente[TAM_MAX_CPF];
    char nomeMedico[TAM_MAX_NOME];
    char CRMmedico [TAM_MAX_CRM];
    char data[TAM_MAX_DATA];

    // Lesoes cirurgicas do paciente 
    tLesao** lesoes;
    int qtdLesoes;
};


tBiopsia* AlocaBiopsia (tLesao** l, int qtd, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data) {

    tBiopsia* biopsia = (tBiopsia*) malloc(sizeof(tBiopsia));
    if (biopsia == NULL) {
        printf("Falha na Alocacao da Biopsia\n");
        exit(EXIT_FAILURE);
    }

    // Inicializa strings com '\0'
    memset(biopsia->nomePaciente, '\0', TAM_MAX_NOME);
    memset(biopsia->cpfPaciente, '\0', TAM_MAX_CPF);
    memset(biopsia->nomeMedico, '\0', TAM_MAX_NOME);
    memset(biopsia->CRMmedico, '\0', TAM_MAX_CRM);
    memset(biopsia->data, '\0', TAM_MAX_DATA);
    
    biopsia->lesoes = l;
    biopsia->qtdLesoes = qtd;

    strcpy(biopsia->nomePaciente, nomePaciente);
    strcpy(biopsia->cpfPaciente, cpfPaciente);
    strcpy(biopsia->nomeMedico, nomeMedico);
    strcpy(biopsia->CRMmedico, CRM);
    strcpy(biopsia->data, data);

    return biopsia;
}


tBiopsia* SolicitaBiopsia (tLesao** lesoes, int qtdLesoes, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data) {

    tLesao** lesoesCirurgicas = NULL;
    int qtd = 0;

    // Verifica se a lesao foi encaminhada para a cirurgia e salva no vetor de lesoes cirurgicas
    for (int i = 0; i < qtdLesoes; i++) {
        if (LesaoFoiEncaminhadaPraCirurgia(lesoes[i])) {
            qtd++;
            lesoesCirurgicas = (tLesao**) realloc(lesoesCirurgicas, sizeof(tLesao *) * qtd);
            lesoesCirurgicas[qtd - 1] = ClonaLesao(lesoes[i]);
        }  
    }

    // Caso nao encontre lesao cirurgicas, retorna NULL
    if (!qtd) {
        ImprimeBarraConsultaMedica();
        printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        char c; scanf("%c%*c", &c);
        ImprimeBarraFinalMenu();
        return NULL;
    }

    ImprimeBarraConsultaMedica();
    printf("SOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    char c; scanf("%c%*c", &c);
    ImprimeBarraFinalMenu();


    // Retorna uma biopsia alocada dinamicamente
    return AlocaBiopsia(lesoesCirurgicas, qtd, nomePaciente, cpfPaciente, nomeMedico, CRM, data);
}

void imprimeNaTelaBiopsia(void *dado) {

    tBiopsia* b = (tBiopsia*) dado;

    printf("PACIENTE: %s\n", b->nomePaciente);
    printf("CPF: %s\n\n", b->cpfPaciente);
    printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n\n");

    for (int i = 0; i < b->qtdLesoes; i++) {
        tLesao* lesao = b->lesoes[i];
        printf("%s - %s - %s - %dMM\n", ObtemRotuloLesao(lesao), ObtemDiagnosticoLesao(lesao), ObtemRegiaoCorpoLesao(lesao), ObtemTamanhoLesao(lesao));
    }

    printf("\n\n");
    printf("%s (%s)\n", b->nomeMedico, b->CRMmedico);
    ImprimeDataTela(b->data);    
    printf("\n\n");

}

void imprimeEmArquivoBiopsia(void *dado, char *path) {

    tBiopsia* b = (tBiopsia*) dado;
    char pathDoc [strlen(path) + strlen("/biopsia.txt") + 1];

    // Concatenacao do caminho + nome arquivo
    sprintf(pathDoc, "%s/%s", path, "biopsia.txt");

    // Dados sao adicionados no fim do arquivo no modo 'append'
    FILE* file = fopen(pathDoc, "a");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo de receita no diretorio: %s\n", pathDoc);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "PACIENTE: %s\n", b->nomePaciente);
    fprintf(file, "CPF: %s\n\n", b->cpfPaciente);
    fprintf(file, "SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");

    for (int i = 0; i < b->qtdLesoes; i++) {
        tLesao* lesao = b->lesoes[i];
        fprintf(file, "%s - %s - %s - %dMM\n", ObtemRotuloLesao(lesao), ObtemDiagnosticoLesao(lesao), ObtemRegiaoCorpoLesao(lesao), ObtemTamanhoLesao(lesao));
    }

    fprintf(file, "\n");
    fprintf(file, "%s (%s)\n", b->nomeMedico, b->CRMmedico);
    ImprimeDataArquivo(b->data, file);
    fprintf(file, "\n\n");


    fclose(file);
}


void DesalocaBiopsia (void* dado) {

    if (!dado) return;

    tBiopsia* b = (tBiopsia*) dado;

    for (int i = 0; i < b->qtdLesoes; i++) {
        DesalocaLesao(b->lesoes[i]);
    }

    free(b->lesoes);
    free(b);
}

