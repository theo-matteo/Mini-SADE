#include "tRelatorio.h"


struct tRelatorio {

    /* Estatisticas Pacientes */
    int totalPacientesAtendidos;
    int idadeMedia;
    int qtdGeneroMasc;
    int qtdGeneroFem;
    int qtdGeneroOutros;

    /* Estatisticas Lesoes */
    int tamMedioLesoes;
    int totalLesoes;
    int totalCirurgias;
    int totalCrioterapia;
};

tRelatorio* CriaRelatorio (tDatabase* database) {

    tRelatorio* r = (tRelatorio*) malloc(sizeof(tRelatorio));
    if (r == NULL) {
        printf("Falha na Alocacao do Relatorio\n");
        exit(EXIT_FAILURE);
    }


    return r;
}


void ImprimeRelatorioTela (void* dado) {

    tRelatorio* r = (tRelatorio*) dado;

    printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", r->totalPacientesAtendidos);
    printf("IDADE MEDIA: %d\n", r->idadeMedia);
    printf("DISTRIBUICAO POR GENERO:\n");
    printf("- FEMININO: %d\n", r->qtdGeneroFem);
    printf("- MASCULINO: %d\n", r->qtdGeneroMasc);
    printf("- OUTROS: %d\n", r->qtdGeneroOutros);


    printf("TAMANHO MEDIO DAS LESOES: %d\n", r->tamMedioLesoes);
    printf("NUMERO TOTAL DE LESOES: %d\n", r->totalLesoes);
    printf("NUMERO TOTAL DE CIRURGIAS: %d\n", r->totalCirurgias);
    printf("NUMERO TOTAL DE CRIOTERAPIA: %d\n", r->totalCrioterapia);
    printf("\n\n");

}

void ImprimeRelatorioArquivo (void* dado, char* path) {

    tRelatorio* r = (tRelatorio*) dado;
    char pathDoc [strlen(path) + strlen("/relatorio_geral.txt") + 1];
    sprintf(pathDoc, "%s/%s", path, "relatorio_geral.txt");

    FILE* file = fopen(pathDoc, "a");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo de lista_busca no diretorio: %s\n", pathDoc);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", r->totalPacientesAtendidos);
    fprintf(file, "IDADE MEDIA: %d\n", r->idadeMedia);
    fprintf(file, "DISTRIBUICAO POR GENERO:\n");
    fprintf(file, "- FEMININO: %d\n", r->qtdGeneroFem);
    fprintf(file, "- MASCULINO: %d\n", r->qtdGeneroMasc);
    fprintf(file, "- OUTROS: %d\n", r->qtdGeneroOutros);

    fprintf(file, "TAMANHO MEDIO DAS LESOES: %d\n", r->tamMedioLesoes);
    fprintf(file, "NUMERO TOTAL DE LESOES: %d\n", r->totalLesoes);
    fprintf(file, "NUMERO TOTAL DE CIRURGIAS: %d\n", r->totalCirurgias);
    fprintf(file, "NUMERO TOTAL DE CRIOTERAPIA: %d\n", r->totalCrioterapia);
    fprintf(file, "\n\n");


    fclose(file);
}

void DesalocaRelatorio (void* dado) {
    tRelatorio* r = (tRelatorio*) dado;
    free(r);
}