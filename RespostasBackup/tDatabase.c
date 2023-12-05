#include "tDatabase.h"

struct tDatabase {
    char path[TAM_MAX_DIRETORIO]; 
    FILE* arqvMedicos; 
    FILE* arqvSecretarios;
    FILE* arqvConsultas;
    FILE* arqvPacientes;
    FILE* arqvLesoes;
};  

tDatabase* CriaBancodeDados (char* path) {

    tDatabase* database = (tDatabase *) malloc(sizeof(tDatabase));
    if (database == NULL) {
        printf("Falha na Alocacao do Banco de Dados\n");
        exit(EXIT_FAILURE);
    }

    strcpy(database->path, path);

    database->arqvMedicos = AbreArquivoBinario(database->path, "medicos.bin");
    database->arqvSecretarios = AbreArquivoBinario(database->path, "secretarios.bin");
    database->arqvConsultas = AbreArquivoBinario(database->path, "consultas.bin");
    database->arqvPacientes = AbreArquivoBinario(database->path, "pacientes.bin");
    database->arqvLesoes = AbreArquivoBinario(database->path, "lesoes.bin");

    return database;
}



tUsuarioSistema* ObtemUsuariocomCredenciaisBD (char* user, char* senha, tDatabase* database) {

    // Retorna os arquivos para o inicio do arquivo
    rewind(database->arqvSecretarios);
    rewind(database->arqvMedicos);

    tSecretario* sec = ObtemSecretarioArqvBinario(user, senha, database->arqvSecretarios);

    if (sec) {
        if (EhSecretarioADMIN(sec)) {
            return CriaUsuarioSistema(sec, TelaImpressaoSecrADMIN, DesalocaSecretario, S_ADMIN);
        }
        else {
            return CriaUsuarioSistema(sec, TelaImpressaoSecrUSER, DesalocaSecretario, S_USER);
        }
    }

    tMedico* med = ObtemMedicoArquivoBinario(user, senha, database->arqvMedicos);
    if (med) return CriaUsuarioSistema(med, TelaImpressaoMedico, DesalocaMedico, MED);


    return NULL;
}

void CadastraNovoAtorBD (tDatabase* d, TipoAtor tipo) {

    // Verifica se o cadastro foi bem sucedido
    void* ator;

    // Obtem o arquivo de acordo com o ator que sera cadastrado
    FILE* file =  ObtemArquivoTipoAtor (d, tipo);

    // Coloca o ponteiro no final do arquivo binario
    fseek(file, 0, SEEK_END);

    // Cadastra um novo ator (MEDICO, SECRETARIO OU PACIENTE)
    if (tipo == MEDICO) {
        
        tMedico* medico = CadastraMedico();

        if (VerificaMesmoCPFBD(tipo, file, ObtemCPFDadosP(ObtemDPMedico(medico)))) {
            printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
            DesalocaMedico(medico);
            return;
        }

        SalvaMedicoArquivoBinario(medico, file);
        DesalocaMedico(medico);
    }

    else if (tipo == SECRETARIO) {

        tSecretario* sec = CadastraSecretario();
        if (VerificaMesmoCPFBD(tipo, file, ObtemCPFDadosP(ObtemDPSecretario(sec)))) {
            printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
            DesalocaSecretario(sec);
            return;
        }

        SalvaSecretarioArquivoBinario(sec, file);
        DesalocaSecretario(sec);
    }   

    
    char c;
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    scanf("%c%*c", &c);
    printf("###############################################################\n");

}

bool VerificaMesmoCPFBD (TipoAtor tipo, FILE* file, char* cpf) {

    rewind(file);
    int qtdBytesCredenciais = ObtemQtdBytesCredenciais();
    char bufferCredenciais[qtdBytesCredenciais];

    while (!feof(file)) {

        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) return false;

        fread(bufferCredenciais, qtdBytesCredenciais, 1, file);

        // Descarta informacoes irrelevantes
        if (tipo == MEDICO) {
            char bufferCRM[TAM_CRM];
            fread(bufferCRM, sizeof(char), TAM_CRM, file);
        }
        else if (tipo == SECRETARIO) {
            char bufferNivelAcesso[TAM_MAX_NIVEL_ACESSO];
            fread(bufferNivelAcesso, sizeof(char), TAM_MAX_NIVEL_ACESSO, file);
        }

        // Verifica se os CPF's se coincidem
        if (CPFsaoIguais(cpf, d)) {
            DesalocaDadosPessoais(d);
            return true;
        }

        DesalocaDadosPessoais(d);
    }

    return false;
}   


bool EhPrimeiroAcessoSistema (tDatabase* database) {
    return (ArquivoEstaVazio(database->arqvSecretarios) && ArquivoEstaVazio(database->arqvMedicos));
}

FILE*  ObtemArquivoTipoAtor  (tDatabase* d, TipoAtor tipo) {
    if (tipo == MEDICO) return d->arqvMedicos;
    else if (tipo == SECRETARIO) return d->arqvSecretarios;
    else return d->arqvPacientes;
}

FILE* ObtemArquivoSecretarios (tDatabase* d) {
    return d->arqvSecretarios;
}

FILE* ObtemArquivoMedicos (tDatabase* d) {
    return d->arqvMedicos;
}

FILE* ObtemArquivoConsultas (tDatabase* d) {
    return d->arqvConsultas;
}

FILE* ObtemArquivoPacientes (tDatabase* d) {
    return d->arqvPacientes;
}

FILE* ObtemArquivoLesoes (tDatabase* d) {
    return d->arqvLesoes;
}


void DesalocaBancoDados (tDatabase* d) {

    if (!d) return;

    fclose(d->arqvSecretarios);
    fclose(d->arqvMedicos);
    fclose(d->arqvConsultas);
    fclose(d->arqvPacientes);
    fclose(d->arqvLesoes); 
    free(d);
}