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

    // Vetor de lesoes da biopsia
    Vector* lesoes;
};


tBiopsia* AlocaBiopsia (Vector* l, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data) {

    tBiopsia* biopsia = (tBiopsia*) malloc(sizeof(tBiopsia));
    if (biopsia == NULL) {
        printf("Falha na Alocacao da Biopsia\n");
        exit(EXIT_FAILURE);
    }
    
    // Realiza atribuicao do vetor
    biopsia->lesoes = l;

    // Copia informacoes passadas por parametro 
    strcpy(biopsia->nomePaciente, nomePaciente);
    strcpy(biopsia->cpfPaciente, cpfPaciente);
    strcpy(biopsia->nomeMedico, nomeMedico);
    strcpy(biopsia->CRMmedico, CRM);
    strcpy(biopsia->data, data);

    return biopsia;
}


tBiopsia* SolicitaBiopsia (Vector* lesoes, char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* CRM, char* data) {

    Vector* lesoesCirurgicas = ObtemLesoesCirurgicas(lesoes);
    
    // Caso o vetor seja nulo, nao retorna uma biopsia valida
    if (lesoesCirurgicas == NULL) {
        ImprimeErroBiopsia();
        return NULL;
    }

    ImprimeSucessoBiopsia();
    return AlocaBiopsia(lesoesCirurgicas, nomePaciente, cpfPaciente, nomeMedico, CRM, data);
}

Vector* ObtemLesoesCirurgicas (Vector* lesoes) {

    Vector* v = VectorConstruct();

    // Verifica se a lesao foi encaminhada para a cirurgia e salva no vetor de lesoes cirurgicas
    for (int i = 0; i < VectorSize(lesoes); i++) {
        tLesao* l = VectorGet(lesoes, i);
        if (LesaoFoiEncaminhadaPraCirurgia(l)) {
            VectorPushBack(v, ClonaLesao(l));
        }  
    }

    if (VectorSize(v) == 0) {
        VectorDestroy(v, DesalocaLesao);
        return NULL;
    }

    return v;
}

void ImprimeErroBiopsia () {
    ImprimeBarraConsultaMedica();
    printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    char c; scanf("%c%*c", &c);
    ImprimeBarraFinalMenu();
}


void ImprimeSucessoBiopsia() {
    ImprimeBarraConsultaMedica();
    printf("SOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    char c; scanf("%c%*c", &c);
    ImprimeBarraFinalMenu();
}


void imprimeNaTelaBiopsia(void *dado) {

    tBiopsia* b = (tBiopsia*) dado;

    printf("PACIENTE: %s\n", b->nomePaciente);
    printf("CPF: %s\n\n", b->cpfPaciente);
    printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n\n");

    for (int i = 0; i < VectorSize(b->lesoes); i++) {
        tLesao* lesao = VectorGet(b->lesoes, i);
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

    for (int i = 0; i < VectorSize(b->lesoes); i++) {
        tLesao* lesao = VectorGet(b->lesoes, i);
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
    VectorDestroy(b->lesoes, DesalocaLesao);
    free(b);
}

