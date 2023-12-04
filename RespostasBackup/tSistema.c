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

    
    if (EhPrimeiroAcessoSistema(s)) {
        CadastraSecretario(ObtemArquivoSecretarios(ObtemBaseDadosSistema(s)));
    } 
    
    // Repete a tela de acesso enquanto o usuario nao conseguir logar
    while (!AcessaSistemaUsuario(s)) {
        printf("SENHA INCORRETA OU USUARIO INEXISTENTE\n");
    }

    while (true) {

        int opcao = -1;
        ImprimeMenuPrincipalUsuario(ObtemUsuario(s));
        scanf("%d %*c", &opcao);

        if (!UsuarioEscolheuOpcaoValida(ObtemUsuario(s), opcao)) {
            printf("OPCAO INVALIDA!\n");
            continue;
        }

        if (opcao == 1) {
            CadastraNovoSecretarioSistema(ObtemArquivoSecretarios(s));
        }
        else if (opcao == 2) {
            CadastraNovoMedicoSistema(ObtemArquivoMedicos(s));
        }
        else if (opcao == 3) {
            CadastraNovoPacienteSistema(ObtemArquivoPacientes(s));
        }


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

    tUsuarioSistema* user = ObtemUsuariocomCredenciaisBD(user, senha, s->database);
    if (user) s->usuario = user;
    else return false;

    return true;
}

tUsuarioSistema* ObtemUsuario (tSistema* s) {
    return s->usuario;
}

tDatabase* ObtemBaseDadosSistema (tSistema* s) {
    return s->database;
}

void DesalocaSistema (tSistema* s) {

    if (!s) return;

    DesalocaBancoDados(s->database);
    DesalocaUsuarioSistema(s->usuario);
    desalocaFila(s->filaDocs);
    
    free(s);
}