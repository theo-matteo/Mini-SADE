#include "tSistema.h"

struct tSistema {

    // Estrutura que armazena o usuario que esta utilizando o sistema
    tUsuarioSistema* usuario;
    
    char caminhoImprDocs[TAM_MAX_DIRETORIO];
    char caminhoBD[TAM_MAX_DIRETORIO]; 

    // Fila de impressao dos documentos
    tFila* filaDocs; 

    // Arquivos binarios
    FILE* arqvMedicos; 
    FILE* arqvSecretarios;
    FILE* arqvConsultas;
    FILE* arqvPacientes;
    FILE* arqvLesoes;
};

FILE* AbreArquivo(char* path, char* filename) {

    char dir[TAM_MAX_DIRETORIO];
    sprintf(dir, "%s/%s", path, filename);

    FILE* file = fopen(dir, "a+b");    
    if (file == NULL) {
        printf("Falha ao Abrir / Criar Arquivo Binario");
        exit(EXIT_FAILURE);
    }

    return file;
}

void TelaImpressaoSecrADMIN() {
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) CADASTRAR SECRETARIO\n");
    printf("\t(2) CADASTRAR MEDICO\n");
    printf("\t(3) CADASTRAR PACIENTE\n");
    printf("\t(4) REALIZAR CONSULTA\n");
    printf("\t(5) BUSCAR PACIENTES\n");
    printf("\t(6) RELATORIO GERAL\n");
    printf("\t(7) FILA DE IMPRESSAO\n");
    printf("\t(8) FINALIZAR O PROGRAMA\n");
    printf("###############################################################\n");
}

void TelaImpressaoSecrUSER() {
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(2) CADASTRAR MEDICO\n");
    printf("\t(3) CADASTRAR PACIENTE\n");
    printf("\t(5) BUSCAR PACIENTES\n");
    printf("\t(6) RELATORIO GERAL\n");
    printf("\t(7) FILA DE IMPRESSAO\n");
    printf("\t(8) FINALIZAR O PROGRAMA\n");
    printf("###############################################################\n");
}

void TelaImpressaoMedico() {
    printf("####################### MENU PRINCIPAL #########################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(4) REALIZAR CONSULTA\n");
    printf("\t(5) BUSCAR PACIENTES\n");
    printf("\t(6) RELATORIO GERAL\n");
    printf("\t(7) FILA DE IMPRESSAO\n");
    printf("\t(8) FINALIZAR O PROGRAMA\n");
    printf("###############################################################\n");
}

bool ArquivoEstaVazio (FILE* file) {

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return (size == 0);
}



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
    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS: ");
    scanf("%s", sistema->caminhoBD);
    scanf("%*c"); // Consome o '\n'
    printf("################################################\n");
    

    sistema->arqvMedicos = AbreArquivo(sistema->caminhoBD, "medicos.bin");
    sistema->arqvSecretarios = AbreArquivo(sistema->caminhoBD, "secretarios.bin");
    sistema->arqvConsultas = AbreArquivo(sistema->caminhoBD, "consultas.bin");
    sistema->arqvPacientes = AbreArquivo(sistema->caminhoBD, "pacientes.bin");
    sistema->arqvLesoes = AbreArquivo(sistema->caminhoBD, "lesoes.bin");
    
    return sistema;
}

void IniciaSistema (tSistema* s) {

    
    if (EhPrimeiroAcessoSistema(s)) ConfiguraPrimeiroAcessoSistema(s);

    // Repete a tela de acesso 
    while (!AcessaSistemaUsuario(s)) {
        printf("SENHA INCORRETA OU USUARIO INEXISTENTE\n");
    }

    printf("AQUI ESTAMOS\n");

}

void ConfiguraPrimeiroAcessoSistema(tSistema* s) {
    tSecretario* sec = CadastraSecretario(); // Cria um novo secretario
    SalvaSecretarioArquivoBinario(sec, s->arqvSecretarios); // Salva secretario em um arquivo binario
    DesalocaSecretario(sec);
}


bool AcessaSistemaUsuario (tSistema* s) {

    char user[TAM_MAX_USER], senha[TAM_MAX_SENHA];

    printf("######################## ACESSO MINI-SADE ######################\n");
    printf("DIGITE SEU LOGIN: ");
    scanf("%s", user);
    printf("DIGITE SUA SENHA: ");
    scanf("%s", senha);
    printf("###############################################################\n");

    // Retorna os arquivos para o inicio
    rewind(s->arqvSecretarios);
    rewind(s->arqvMedicos);

    

    tSecretario* sec = ObtemSecretarioArqvBinario(user, senha, s->arqvSecretarios);

    // Caso encontre o secretario no banco de dados
    if (sec) {
        LogaSecretarioSistema(sec, s);
        return true;
    }
    
    // Caso nao encontre o medico, busca no banco de dados de medicos
    tMedico* med = ObtemMedicoArquivoBinario(user, senha, s->arqvMedicos);
    if (med) {
        LogaMedicoSistema(med, s);
        return true;
    }


    return false;
}

void LogaSecretarioSistema (tSecretario* sec, tSistema* s) {

    if (EhSecretarioADMIN(sec)) {
        s->usuario = CriaUsuarioSistema(sec, TelaImpressaoSecrADMIN, DesalocaSecretario, S_ADMIN);
    }
    else {
        s->usuario = CriaUsuarioSistema(sec, TelaImpressaoSecrUSER, DesalocaSecretario, S_USER);
    }
}

void LogaMedicoSistema (tMedico* m, tSistema* s) {
    s->usuario = CriaUsuarioSistema(m, TelaImpressaoMedico, DesalocaMedico, MEDICO);
}

bool EhPrimeiroAcessoSistema (tSistema* s) {
    return (ArquivoEstaVazio(s->arqvSecretarios) && ArquivoEstaVazio(s->arqvMedicos));
}


void DesalocaSistema (tSistema* s) {

    if (!s) return;

    DesalocaUsuarioSistema(s->usuario);
    desalocaFila(s->filaDocs);

    // Fecha os Arquivos
    fclose(s->arqvSecretarios);
    fclose(s->arqvMedicos);
    fclose(s->arqvConsultas);
    fclose(s->arqvPacientes);
    fclose(s->arqvLesoes);

    free(s);
}