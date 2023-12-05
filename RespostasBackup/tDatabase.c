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
    int status = 0;

    // Obtem o arquivo de acordo com o ator que sera cadastrado
    FILE* file =  ObtemArquivoTipoAtor (d, tipo);

    // Coloca o ponteiro no final do arquivo binario
    fseek(file, 0, SEEK_END);

    
    // Cadastra um novo ator (MEDICO, SECRETARIO OU PACIENTE)
    if (tipo == MEDICO) {
        CadastraMedico(file);
    }
    else if (tipo == SECRETARIO) status = CadastraSecretario(file);
    
    if (status == 0) {
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
        return;
    }

    char c;
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    scanf("%c%*c", &c);
    printf("###############################################################\n");

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