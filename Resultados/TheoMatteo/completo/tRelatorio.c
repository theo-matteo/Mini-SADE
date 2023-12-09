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

tRelatorio* CriaRelatorio () {

    tRelatorio* r = (tRelatorio*) malloc(sizeof(tRelatorio));
    if (r == NULL) {
        printf("Falha na Alocacao do Relatorio\n");
        exit(EXIT_FAILURE);
    }

    r->totalPacientesAtendidos = 0;
    r->idadeMedia = 0;
    r->qtdGeneroMasc = 0;
    r->qtdGeneroFem = 0;
    r->qtdGeneroOutros = 0;
    r->tamMedioLesoes = 0;
    r->totalLesoes = 0;
    r->totalCirurgias = 0;
    r->totalCrioterapia = 0;


    return r;
}

tRelatorio* GeraRelatorioCompleto(tDatabase* database) {

    tRelatorio* r = CriaRelatorio();

    // Preenche informacoes do Relatorio  
    r->totalPacientesAtendidos = ObtemQuantidadeConsultasBinario(ObtemArquivoConsultas(database));
    PreencheRelatorioDadosPacientes(ObtemArquivoPacientes(database), r);
    PreencheRelatorioDadosLesoes(ObtemArquivoLesoes(database), r);
    
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
    printf("\n");

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
    fprintf(file, "\n");


    fclose(file);
}


void PreencheRelatorioDadosLesoes (FILE* file, tRelatorio* r) {

    // Seta o arquivo para o inicio do arquivo
    rewind(file);

    while(!feof(file)) {

        tLesao* l = ObtemLesaoArquivoBinario(file);
        if (!l) break;
        
        r->totalLesoes++;
        r->tamMedioLesoes += ObtemTamanhoLesao(l);
        r->totalCirurgias += LesaoFoiEncaminhadaPraCirurgia(l);
        r->totalCrioterapia += LesaoFoiEncaminhaCrioterapia(l);
        
        DesalocaLesao(l);

    }   

    if (r->totalLesoes != 0) r->tamMedioLesoes = r->tamMedioLesoes / r->totalLesoes;
}

void PreencheRelatorioDadosPacientes (FILE* file, tRelatorio* r) {
    
    // Seta o arquivo para o inicio do arquivo
    rewind(file);

    int count = 0;
    int qtdPacientes = 0;

    while(!feof(file)) {

        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) break;

        char* data = ObtemDtNascDadosP(d);  
        char* genero = ObtemGeneroDadosP(d);

        if (!strcmp(genero, "MASCULINO")) r->qtdGeneroMasc++;
        else if (!strcmp(genero, "FEMININO")) r->qtdGeneroFem++;
        else r->qtdGeneroOutros++;

        // Calcula Media de Idade
        int idade = CalculaIdade(data);
        count += idade;
        qtdPacientes++;

        DesalocaDadosPessoais(d);
    }

    if (qtdPacientes == 0) r->idadeMedia = 0;
    else (r->idadeMedia = count / qtdPacientes);
}

void DesalocaRelatorio (void* dado) {
    tRelatorio* r = (tRelatorio*) dado;
    free(r);
}