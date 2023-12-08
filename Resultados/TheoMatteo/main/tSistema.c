#include "tSistema.h"

struct tSistema {

    // Usuario que esta utilizando o sistema
    tUsuario* user;

    // Caminho onde ira imprimir os documentos
    char caminhoImprDocs[TAM_MAX_DIRETORIO];

    // Fila de documentos para impressao
    tFila* filaDocs;    

    // Banco de dados (onde ha os arquivos binarios)
    tDatabase* database;

    // Consultas realizadas durante o uso do sistema
    tConsulta** consultas;
    int qtdConsultas;
};

tSistema* CriaSistema (char* path) {

    tSistema* sistema = malloc(sizeof(tSistema));
    if (sistema == NULL) {
        printf("Falha na Alocacao do Sistema\n");
        exit(EXIT_FAILURE);
    }

    // Obtem caminho de dados imprimir documentos
    strcpy(sistema->caminhoImprDocs, path);
    strcat(sistema->caminhoImprDocs, "/saida");

    // Usuario logado no sistema inicializado com NULL
    sistema->user = NULL;
    sistema->filaDocs = criaFila();

    // Inicializa informacoes de consultas realizadas
    sistema->consultas = NULL;
    sistema->qtdConsultas = 0;

    // Obtem caminho do banco de dados
    char pathDB[TAM_MAX_DIRETORIO];
    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS: ");
    scanf("%s", pathDB); scanf("%*c");
    printf("################################################\n");

    // Realiza concatenacao da string
    char dirDB[TAM_MAX_DIRETORIO];
    sprintf(dirDB, "%s/%s", path, pathDB);

    // Cria banco de dados
    sistema->database = CriaBancodeDados(dirDB);

    return sistema;
}

void IniciaSistema (tSistema* s) {

    tDatabase* database = ObtemBDSistema(s);
    
    if (EhPrimeiroAcessoSistema(database)) {
        tSecretario* secretario = CadastraSecretario(ObtemArquivoSecretarios(database));
        SalvaSecretarioArquivoBinario(secretario, ObtemArquivoSecretarios(database));
        DesalocaSecretario(secretario);
    } 
    
    // Repete a tela de acesso enquanto o usuario nao conseguir logar
    while (!AcessaSistemaUsuario(s)) {
        printf("SENHA INCORRETA OU USUARIO INEXISTENTE\n");
    }

    while (true) {

        int opcao = -1;
        ImprimeMenuPrincipalUsuario(ObtemUsuario(s));
        scanf("%d", &opcao);
        scanf("%*c");

        if (!UsuarioEscolheuOpcaoValida(ObtemUsuario(s), opcao)) {
            printf("OPCAO INVALIDA!\n");
            continue;
        }

        switch (opcao) {
            
            case 1:
                CadastraNovaPessoaBD(database, SECRETARIO);
                break;
            case 2:
                CadastraNovaPessoaBD(database, MEDICO);
                break;
            case 3:
                CadastraNovaPessoaBD(database, PACIENTE);
                break;
            case 4:
                tConsulta* consulta = RealizaConsulta(s->user, database, s->filaDocs);
                if (consulta) {
                    SalvaConsultaArquivoBinario(consulta, ObtemArquivoConsultas(database));
                    SalvaConsultaSistema(s, consulta);
                }
                break;
            case 5:
                tListaBusca* lista = BuscaPacientes(ObtemArquivoPacientes(database));
                if (lista) insereDocumentoFila(s->filaDocs, lista, ImprimeListaBusca, imprimeEmArquivoListaBusca, DesalocaListaBusca);
                break;
            case 6:
                ExecutaRelatorio(s);
                break;
            case 7:
                ExecutaFiladeImpressao(s);
                break;
            default:
                break;
        }

        if (opcao == 8) break;
    }
}


bool AcessaSistemaUsuario (tSistema* s) {

    char user[TAM_MAX_USER], senha[TAM_MAX_SENHA];

    printf("######################## ACESSO MINI-SADE ######################\n");
    printf("DIGITE SEU LOGIN: ");
    scanf("%s", user);
    printf("DIGITE SUA SENHA: ");
    scanf("%s", senha);
    printf("###############################################################\n");

    s->user = ObtemUsuariocomCredenciaisBD(user, senha, ObtemBDSistema(s));
    if (s->user == NULL) return false;

    return true;
}

void ExecutaFiladeImpressao (tSistema* s) {

    int op = -1;

    while (true) {

        printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
        printf("ESCOLHA UMA OPCAO:\n");
        printf("\t(1) EXECUTAR FILA DE IMPRESSAO\n");
        printf("\t(2) RETORNAR AO MENU ANTERIOR\n");
        scanf("%d%*c", &op);

        if (op == 1) {
            printf("EXECUTANDO FILA DE IMPRESSAO:\n");
            imprimeFila(ObtemFilaImprSistema(s), ObtemPathImprDocs(s));
            printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU ANTERIOR\n");
            char c; scanf("%c%*c", &c);
            printf("############################################################\n");
            continue;
        }

        else break;
    }   

    printf("############################################################\n");
}

void ExecutaRelatorio (tSistema* s) {

    tRelatorio* relatorio = GeraRelatorioCompleto(ObtemBDSistema(s));
    printf("#################### RELATORIO GERAL #######################\n");
    ImprimeRelatorioTela(relatorio);

    int op = -1;
    printf("SELECIONE UMA OPCAO:\n");
    printf("\t(1) ENVIAR PARA IMPRESSAO\n");
    printf("\t(2) RETORNAR AO MENU PRINCIPAL\n");
    scanf("%d%*c", &op);

    if (op == 1) {
        insereDocumentoFila(s->filaDocs, relatorio, ImprimeRelatorioTela, ImprimeRelatorioArquivo, DesalocaRelatorio);
        printf("RELATÓRIO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU ANTERIOR\n");
        char c; scanf("%c%*c", &c);
    }
        
    else DesalocaRelatorio(relatorio);
    printf("############################################################\n");
    
}

void SalvaConsultaSistema(tSistema* s, tConsulta* c) {
    s->qtdConsultas++;
    s->consultas = (tConsulta**) realloc(s->consultas, sizeof(tConsulta*) * s->qtdConsultas);
    s->consultas[s->qtdConsultas - 1] = c;
}

tUsuario* ObtemUsuario (tSistema* s) {
    return s->user;
}

tDatabase* ObtemBDSistema (tSistema* s) {
    return s->database;
}

tFila* ObtemFilaImprSistema (tSistema* s) {
    return s->filaDocs;
}

char* ObtemPathImprDocs (tSistema* s) {
    return s->caminhoImprDocs;
}

void DesalocaSistema (tSistema* s) {

    if (!s) return;

    DesalocaBancoDados(s->database);
    DesalocaUsuarioSistema(s->user);
    desalocaFila(s->filaDocs);

    for (int i = 0; i < s->qtdConsultas; i++) {
        DesalocaConsulta(s->consultas[i]);
    }
    
    free(s->consultas);
    free(s);
}