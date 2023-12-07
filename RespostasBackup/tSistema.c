#include "tSistema.h"

struct tSistema {

    // Estrutura que armazena o usuario que esta utilizando o sistema
    tUsuarioSistema* usuario;

    // Diretorio onde ira imprimir os documentos
    char caminhoImprDocs[TAM_MAX_DIRETORIO];

    // Fila de Documentos
    tFila* filaDocs;    

    // Banco de Dados onde se encontra os arquivos binarios
    tDatabase* database;
    
};

tSistema* CriaSistema (char* path) {

    tSistema* sistema = malloc(sizeof(tSistema));
    if (sistema == NULL) {
        printf("Falha na Alocacao do Sistema\n");
        exit(EXIT_FAILURE);
    }

    // Copia caminho para impressao dos documentos
    strcpy(sistema->caminhoImprDocs, path);

    // Usuario logado no sistema inicializado com NULL
    sistema->usuario = NULL;
    sistema->filaDocs = criaFila();

    // Obtem caminho do banco de dados
    char pathDB[TAM_MAX_DIRETORIO];
    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS: ");
    scanf("%s", pathDB);
    scanf("%*c"); // Consome o '\n'
    printf("################################################\n");
    
    // Cria banco de dados
    sistema->database = CriaBancodeDados(pathDB);

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
                RealizaConsulta(s->usuario, database, s->filaDocs);
                break;
            case 5:
                tListaBusca* lista = BuscaPacientes(ObtemArquivoPacientes(database));
                if (lista) insereDocumentoFila(s->filaDocs, lista, ImprimeListaBusca, imprimeEmArquivoListaBusca, DesalocaListaBusca);
            case 6:
                break;
            case 7:
                ExecutaFiladeImpressao(s);
                break;

            default:
                break;
        }

        if (opcao == 1) {
            
        }

        else if (opcao == 8) break;

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

    s->usuario = ObtemUsuariocomCredenciaisBD(user, senha, ObtemBDSistema(s));
    if (s->usuario == NULL) return false;

    return true;
}

void ExecutaFiladeImpressao (tSistema* s) {

    int op = -1;

    printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) EXECUTAR FILA DE IMPRESSAO\n");
    printf("\t(2) RETORNAR AO MENU ANTERIOR\n");
    scanf("%d%*c", &op);

    if (op == 2) {
        printf("############################################################\n");
        return;
    }

    printf("################ FILA DE IMPRESSAO MEDICA ##################\n");
    printf("EXECUTANDO FILA DE IMPRESSAO:\n");
    imprimeFila(ObtemFilaImprSistema(s), ObtemPathImprDocs(s));

    printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU ANTERIOR\n");
    char c; scanf("%c%*c", &c);
    printf("############################################################\n");

}


tUsuarioSistema* ObtemUsuario (tSistema* s) {
    return s->usuario;
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
    DesalocaUsuarioSistema(s->usuario);
    desalocaFila(s->filaDocs);
    
    free(s);
}