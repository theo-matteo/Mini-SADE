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

void CadastraNovaPessoaBD (tDatabase* d, tipoPessoa tipo) {

    // Verifica se o cadastro foi bem sucedido
    void* pessoa = NULL;

    // Obtem o arquivo de acordo com o pessoa que sera cadastrado
    FILE* file =  ObtemArquivoTipoPessoa (d, tipo);

    ObtemCPFPessoaFunc obtemCPFfunc = ObtemFuncaoObterCPFPessoa(tipo);
    SalvaPessoaArqvFunc salvaPessoaArqv = ObtemFuncaoSalvaPessoaArqv(tipo);
    DesalocaPessoaFunc desalocaPessoaFunc = ObtemFuncaoDesalocarPessoa(tipo);

    // Cadastra uma nova pessoa baseado no tipo
    if (tipo == MEDICO) pessoa = CadastraMedico();
    else if (tipo == SECRETARIO) pessoa = CadastraSecretario();
    else pessoa = CadastraPaciente();

    /* Verifica se ha um mesmo cpf cadastrado */
    void* pessoaTemp = ObtemPessoaArquivoBinario(tipo, file, obtemCPFfunc(pessoa));
    if (pessoaTemp) {
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
        desalocaPessoaFunc(pessoaTemp); // Desaloca pessoa temporaria
        desalocaPessoaFunc(pessoa); // Desaloca pessoa recem cadastrada
        return;
    }

    // Coloca o ponteiro no final do arquivo binario para salvar a pessoa 
    fseek(file, 0, SEEK_END);
    salvaPessoaArqv(pessoa, file);

    desalocaPessoaFunc(pessoa);
    
    /* Aguarda o usuario digitar uma tecla para retornar ao menu principal */
    char c;
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    scanf("%c%*c", &c);
    printf("###############################################################\n");

}


ObtemCPFPessoaFunc ObtemFuncaoObterCPFPessoa (tipoPessoa tipo) {
    if (tipo == MEDICO) return ObtemCPFMedico;
    else if (tipo == SECRETARIO) return ObtemCPFSecretario;
    else return ObtemCPFPaciente;
}

SalvaPessoaArqvFunc ObtemFuncaoSalvaPessoaArqv (tipoPessoa tipo) {
    if (tipo == SECRETARIO) return SalvaSecretarioArquivoBinario;
    else if (tipo == MEDICO) return SalvaMedicoArquivoBinario;
    else return SalvaPacienteArquivoBinario;
}

DesalocaPessoaFunc ObtemFuncaoDesalocarPessoa (tipoPessoa tipo) {
    if (tipo == SECRETARIO) return DesalocaSecretario;
    else if (tipo == MEDICO) return DesalocaMedico;
    else return DesalocaPaciente;
}

void* ObtemPessoaArquivoBinario (tipoPessoa tipo, FILE* file, char* cpf) {

    rewind(file);

    void* pessoa = NULL;
    char bufferCRM[TAM_CRM];
    char bufferNivelAcesso[TAM_MAX_NIVEL_ACESSO];

    while(!feof(file)) {

        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) break;

        tCredenciais* c = NULL;
        if (tipo != PACIENTE) c = ObtemCredenciaisArquivoBinario(file);

        if (tipo == MEDICO) fread(bufferCRM, sizeof(char), TAM_CRM, file);
        else if (tipo == SECRETARIO) fread(bufferNivelAcesso, sizeof(char), TAM_MAX_NIVEL_ACESSO, file);

        if (CPFsaoIguais(cpf, d)) {
            if (tipo == MEDICO) return CriaMedico(d, c, bufferCRM);
            else if (tipo == SECRETARIO) return CriaSecretario(d, c, bufferNivelAcesso);
            else return CriaPaciente(d);
        }
        else {
            DesalocaDadosPessoais(d);
            if (c) DesalocaCredenciais(c);
        }
    }

    return NULL;
}


bool EhPrimeiroAcessoSistema (tDatabase* database) {
    return (ArquivoEstaVazio(database->arqvSecretarios) && ArquivoEstaVazio(database->arqvMedicos));
}

FILE*  ObtemArquivoTipoPessoa  (tDatabase* d, tipoPessoa tipo) {
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