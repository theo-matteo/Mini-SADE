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

    // Aloca dados da receita temporariamente
    Vector* dados_receita;
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
    
    // Aloca dados da receita temporariamente
    sistema->dados_receita = VectorConstruct();

    // Obtem caminho do banco de dados
    char pathDB[TAM_MAX_DIRETORIO];
    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS: ");
    scanf("%s", pathDB); scanf("%*c");
    printf("################################################\n");


    // Realiza concatenacao da string
    char dirDB[TAM_MAX_DIRETORIO * 2];
    sprintf(dirDB, "%s/%s", path, pathDB);

    // Imprime na tela os caminhos
    printf("Caminho do banco de dados: %s\n", dirDB);
    printf("Caminho da pasta de saida: %s\n", sistema->caminhoImprDocs);

    // Cria banco de dados
    sistema->database = CriaBancodeDados(dirDB);

    return sistema;
}

void ExecutaSistema (tSistema* s) {
    
    tDatabase* database = ObtemBDSistema(s);
    tFila* fila = ObtemFilaImprSistema(s);
    
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
        scanf("%d%*c", &opcao);

        if (!UsuarioEscolheuOpcaoValida(ObtemUsuario(s), opcao)) {
            printf("OPCAO INVALIDA!\n");
            continue;
        }

        switch (opcao) {
            
            case 1:
                AdicionaPessoaBD(database, SECRETARIO);
                break;
            case 2:
                AdicionaPessoaBD(database, MEDICO);
                break;
            case 3:
                AdicionaPessoaBD(database, PACIENTE);
                break;
            case 4:
                ExecutaConsulta(ObtemUsuario(s), database, fila, s->dados_receita);
                break;
            case 5:
                BuscaPacientes(ObtemArquivoPacientes(database), fila);
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
    ImprimeBarraFinalMenu();

    s->user = AutenticaUsuario(user, senha, ObtemBDSistema(s));
    if (s->user == NULL) return false;

    return true;
}

void ExecutaFiladeImpressao (tSistema* s) {

    int op = -1;

    while (true) {

        ImprimeTelaFiladeImpressao();
        scanf("%d%*c", &op);

        if (op == 1) {
            printf("EXECUTANDO FILA DE IMPRESSAO:\n");
            imprimeFila(ObtemFilaImprSistema(s), ObtemPathImprDocs(s));
            printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU ANTERIOR\n");
            char c; scanf("%c%*c", &c);
            ImprimeBarraFinalMenu();
            continue;
        }

        else break;
    }   

    ImprimeBarraFinalMenu();
}

void ExecutaRelatorio (tSistema* s) {

    tRelatorio* relatorio = GeraRelatorio(ObtemBDSistema(s));
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
    ImprimeBarraFinalMenu();
    
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
    VectorDestroy(s->dados_receita, DesalocaDadosReceita);

    free(s);

}