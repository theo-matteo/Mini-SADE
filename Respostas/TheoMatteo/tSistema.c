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

        tSecretario* secretario = NULL;

        // Verifica se o arquivo de inicia esta vazio
        if (ArquivoEstaVazio(ObtemArqvInicio(database)) == true) {
            secretario = CadastraSecretario(ObtemArquivoSecretarios(database));
        }
        else {
            secretario = ObtemSecretarioArqvInicio(database);
        }

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

        switch (opcao) {
            
            case CADASTRAR_SECRETARIO:
                AdicionaPessoaBD(database, SECRETARIO);
                break;
            case CADASTRAR_MEDICO:
                AdicionaPessoaBD(database, MEDICO);
                break;
            case CADASTRAR_PACIENTE:
                AdicionaPessoaBD(database, PACIENTE);
                break;
            case EXECUTAR_CONSULTA:
                ExecutaConsulta(ObtemUsuario(s), database, fila, s->dados_receita);
                break;
            case BUSCAR_PACIENTES:
                BuscaPacientes(ObtemArquivoPacientes(database), fila);
                break;
            case EXECUTAR_RELATORIO:
                ExecutaRelatorio(s);
                break;
            case EXECUTAR_FILA_IMPRESSAO:
                ExecutaFiladeImpressao(s);
                break;
            case DUMP:
                ImprimeSecretariosBD(database, s->caminhoImprDocs);
                ImprimeMedicosBD(database, s->caminhoImprDocs);
                ImprimePacientesBD(database, s->caminhoImprDocs);
            default:
                break;
        }
        
        // Caso o usuario decida realizar o DUMP, o sistema encerra.
        if (opcao == DUMP) break;
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
        ImprimeBarraFinalMenu();

        if (op == 1) {
            ImprimeBarraFilaImpr();
            printf("EXECUTANDO FILA DE IMPRESSAO:\n");
            imprimeFila(ObtemFilaImprSistema(s), ObtemPathImprDocs(s));
            printf("\nPRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU ANTERIOR\n");
            char c; scanf("%c%*c", &c);
            ImprimeBarraFinalMenu();
            continue;
        }

        else break;
    }   
}

void ExecutaRelatorio (tSistema* s) {

    tRelatorio* relatorio = GeraRelatorio(ObtemBDSistema(s));
    printf("#################### RELATORIO GERAL #######################\n");
    ImprimeRelatorioTela(relatorio);


    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) ENVIAR PARA IMPRESSAO\n");
    printf("\t(2) RETORNAR AO MENU PRINCIPAL\n");
    int op = -1; scanf("%d%*c", &op);
    ImprimeBarraFinalMenu();

    if (op == 1) {
        insereDocumentoFila(s->filaDocs, relatorio, ImprimeRelatorioTela, ImprimeRelatorioArquivo, DesalocaRelatorio);
        printf("\nRELATÓRIO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        char c; scanf("%c%*c", &c);
        ImprimeBarraFinalMenu();
    }
    else DesalocaRelatorio(relatorio);
    
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