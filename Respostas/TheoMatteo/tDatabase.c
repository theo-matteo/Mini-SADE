#include "tDatabase.h"
#include "tConsulta.h"

struct tDatabase {
    char path[TAM_MAX_DIRETORIO]; 
    FILE* arqvMedicos; 
    FILE* arqvSecretarios;
    FILE* arqvConsultas;
    FILE* arqvPacientes;
    FILE* arqvLesoes;
    FILE* arqvInicio;
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
    database->arqvInicio = AbreArquivoBinario(database->path, "inicio.bin");

    return database;
}

FILE* AbreArquivoBinario(char* path, char* filename) {

    char dir[TAM_MAX_DIRETORIO];
    sprintf(dir, "%s%s", path, filename);

    FILE* file = fopen(dir, "a+b");
    if (file == NULL) {
        printf("Falha ao abrir ou criar arquivo binário no diretório %s\n", dir);
        exit(EXIT_FAILURE);
    }

    return file;
}

bool ArquivoEstaVazio (FILE* file) {

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    return (size == 0);
}

tUsuario* AutenticaUsuario (char* user, char* senha, tDatabase* database) {

    // Seta os arquivos para o inicio do arquivo
    rewind(database->arqvSecretarios);
    rewind(database->arqvMedicos);

    // Tenta obter um secretario com as credenciais fornecidas
    tSecretario* sec = ObtemSecretarioBD (user, senha, database->arqvSecretarios);

    // Se o secretario for encontrado, verifica o nivel de acesso e retorna um usuario valido
    if (sec) {
        if (VerificaAcessoAdminSec(sec)) return CriaUsuarioSistema(sec, TelaImpressaoSecrADMIN, DesalocaSecretario, S_ADMIN);
        else return CriaUsuarioSistema(sec, TelaImpressaoSecrUSER, DesalocaSecretario, S_USER);
    }

    // Tenta encontrar um medico com as credenciais forncedias
    tMedico* med = ObtemMedicoBD(user, senha, database->arqvMedicos);
    if (med) return CriaUsuarioSistema(med, TelaImpressaoMedico, DesalocaMedico, M);

    // Retorna NULL para sinalizar que nao foi encontrado nenhum usuario valido
    return NULL;
}


tSecretario* ObtemSecretarioArqvInicio (tDatabase* d) {

    FILE* file = d->arqvInicio;
    rewind(file);

    int dia, mes, ano;
    char data[11];

    char nome[100];
    char cpf[15], tel[15];
    char genero[13], senha[20];
    char nomeUser[20];
    char nivelAcesso[7];

    fread(nome, sizeof(char), 100, file);
    fread(cpf, sizeof(char), 15, file);
    fread(&dia, sizeof(int), 1, file);
    fread(&mes, sizeof(int), 1, file);
    fread(&ano, sizeof(int), 1, file);
    fread(tel, sizeof(char), 15, file);
    fread(genero, sizeof(char), 13, file);
    fread(senha, sizeof(char), 20, file);
    fread(nomeUser, sizeof(char), 20, file);
    fread(nivelAcesso, sizeof(char), 7, file);

    sprintf(data, "%d/%d/%d", dia, mes, ano);

    tDadosPessoais* dados = CriaDadosPessoais(nome, cpf, data, tel, genero);
    tCredenciais* c = CriaCredenciaisAcesso(nomeUser, senha);

    return CriaSecretario(dados, c, nivelAcesso);
}


FILE* ObtemArqvInicio (tDatabase* d) {
    return d->arqvInicio;
}

void ImprimeSecretariosBD (tDatabase* d, char* path) {

    char pathDoc [strlen(path) + strlen("/secretarios.txt") + 1];

    // Concatenacao do caminho + nome arquivo
    sprintf(pathDoc, "%s/%s", path, "secretarios.txt");

    FILE* file = fopen(pathDoc, "w");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo de encaminhamento no diretorio: %s\n", pathDoc);
        exit(EXIT_FAILURE);
    }


    Vector* vector = ObtemSecretariosBD(ObtemArquivoSecretarios(d));
    if (VectorSize(vector) == 0) {
        VectorDestroy(vector, DesalocaSecretario);
        fclose(file);
        return;
    }

    ImprimeTodosSecretarios(vector, file);
    VectorDestroy(vector, DesalocaSecretario);
    fclose(file);
}

void ImprimeMedicosBD (tDatabase* d, char* path) {

    char pathDoc [strlen(path) + strlen("/medicos.txt") + 1];

    // Concatenacao do caminho + nome arquivo
    sprintf(pathDoc, "%s/%s", path, "medicos.txt");

    FILE* file = fopen(pathDoc, "w");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo de encaminhamento no diretorio: %s\n", pathDoc);
        exit(EXIT_FAILURE);
    }


    Vector* vector = ObtemMedicosBD(ObtemArquivoMedicos(d));

    if (VectorSize(vector) == 0) {
        VectorDestroy(vector, DesalocaMedico);
        fclose(file);
        return;
    }


    ImprimeTodosMedicos(vector, file);
    VectorDestroy(vector, DesalocaMedico);
    fclose(file);

}

void ImprimePacientesBD (tDatabase* d, char* path) {

    char pathDoc [strlen(path) + strlen("/pacientes.txt") + 1];
    sprintf(pathDoc, "%s/%s", path, "pacientes.txt");

    FILE* file = fopen(pathDoc, "w");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo de encaminhamento no diretorio: %s\n", pathDoc);
        exit(EXIT_FAILURE);
    }   

    // Obtem todos os pacientes do banco de dados
    Vector* pacientes = ObtemPacientesBD(ObtemArquivoPacientes(d));

    
    for (int i = 0; i < VectorSize(pacientes); ++i) {

        tPaciente* p = VectorGet(pacientes, i);
        ImprimePaciente(p, file);

        // Obtem todas as consultas relacionadas ao paciente
        Vector* consultas  = ObtemConsultasCPF(ObtemCPFPaciente(p), ObtemArquivoConsultas(d));
        int qtd_consultas = VectorSize(consultas);

        if (qtd_consultas == 0) {
            fprintf(file, "DIABETES: -\n");
            fprintf(file, "FUMANTE: -\n");
            fprintf(file, "ALERGIA: -\n");
            fprintf(file, "HISTORICO DE CANCER: -\n");
            fprintf(file, "TIPO DE PELE: -\n");
            fprintf(file, "QUANTIDADE DE CONSULTAS: %d\n", qtd_consultas);
            fprintf(file, "- - - - - -\n");
            
        }
        else {
            tConsulta* c = VectorGet(consultas, 0);
            fprintf(file, "DIABETES: %s\n", RetornaResposta(PossuiDiabetesConsulta(c)));
            fprintf(file, "FUMANTE: %s\n", RetornaResposta(EhFumante(c)));
            fprintf(file, "ALERGIA: %s\n", RetornaResposta(PossuiAlergiaConsulta(c)));
            fprintf(file, "HISTORICO DE CANCER: %s\n", RetornaResposta(PossuiHistoricoCancer(c)));
            fprintf(file, "TIPO DE PELE: %s\n", TipoPeleConsulta(c));
            fprintf(file, "QUANTIDADE DE CONSULTAS: %d\n", qtd_consultas);
            fprintf(file, "- - -\n");
            
        }

        for (int j = 0; j < qtd_consultas; ++j) {
            
            tConsulta* c = VectorGet(consultas, j);
            Vector* lesoes = ObtemLesoesConsulta(ObtemCPFPaciente(p), ObtemDataConsulta(c), ObtemArquivoLesoes(d));

            fprintf(file, "DATA DA CONSULTA: ");
            ImprimeDataArquivo(ObtemDataConsulta(c), file);
            fprintf(file, "QUANTIDADE DE LESOES GERADAS: %d\n", VectorSize(lesoes));

            if (VectorSize(lesoes) == 0) {
                if (j == qtd_consultas -1) fprintf(file, "- - - - - -\n");
                else fprintf(file, "- - -\n");
            }
            else fprintf(file, "- -\n");

            for (int k = 0; k < VectorSize(lesoes); ++k) {
                ImprimeLesaoArquivo(VectorGet(lesoes, k), file);

                if (k == VectorSize(lesoes) - 1) {
                    if (j == qtd_consultas - 1) fprintf(file, "- - - - - -\n");
                    else fprintf(file, "- - -\n");
                }
                else fprintf(file, "- -\n");
            } 

            VectorDestroy(lesoes, DesalocaLesao);            
        }
        VectorDestroy(consultas, DesalocaConsulta);
        fprintf(file, "- - - - - -\n");
    }
    VectorDestroy(pacientes, DesalocaPaciente);
    fclose(file);
}



void AdicionaPessoaBD (tDatabase* d, tipoPessoa tipo) {

    // Verifica se o cadastro foi bem sucedido
    void* pessoa = NULL;

    // Obtem o arquivo de acordo com o pessoa que sera cadastrado
    FILE* file =  ObtemArquivoTipoPessoa (d, tipo);

    // Obtem as funcoes (callback) de acordo com o tipo de pessoa
    ObtemCPFPessoaFunc obtemCPFfunc = ObtemFuncaoObterCPFPessoa(tipo);
    SalvaPessoaArqvFunc salvaPessoaArqv = ObtemFuncaoSalvaPessoaArqv(tipo);
    DesalocaPessoaFunc desalocaPessoaFunc = ObtemFuncaoDesalocarPessoa(tipo);

    // Cadastra uma nova pessoa baseado no tipo
    if (tipo == MEDICO) pessoa = CadastraMedico();
    else if (tipo == SECRETARIO) pessoa = CadastraSecretario();
    else pessoa = CadastraPaciente();

    // Verifica se o CPF ja existe no banco de dados
    void* pessoaTemp = BuscaPessoaPorCpf(tipo, file, obtemCPFfunc(pessoa));
    if (pessoaTemp) {
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
        desalocaPessoaFunc(pessoaTemp); // Desaloca pessoa temporaria
        desalocaPessoaFunc(pessoa); // Desaloca pessoa recem cadastrada
        return;
    }

    // Salva pessoa no banco de dados e desaloca da memoria
    salvaPessoaArqv(pessoa, file);
    desalocaPessoaFunc(pessoa);
    
    /* Aguarda o usuario digitar uma tecla para retornar ao menu principal */
    ImprimeSucessoCadastro();
    char c; scanf("%c%*c", &c);
    ImprimeBarraFinalMenu();

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

void* BuscaPessoaPorCpf (tipoPessoa tipo, FILE* file, char* cpf) {

    // Retorna o ponteiro para o inicio do arquivo 
    rewind(file);

    // Buffers para armazenar dados (se for necessario)
    char bufferCRM[TAM_CRM]; 
    char bufferNivelAcesso[TAM_MAX_NIVEL_ACESSO]; 

    while(true) {

        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) break;

        tCredenciais* c = NULL;
        if (tipo != PACIENTE) c = ObtemCredenciaisArquivoBinario(file);

        if (tipo == MEDICO) fread(bufferCRM, sizeof(char), TAM_CRM, file);
        else if (tipo == SECRETARIO) fread(bufferNivelAcesso, sizeof(char), TAM_MAX_NIVEL_ACESSO, file);

        if (VerificaCpfIguais(cpf, d)) {
            if (tipo == MEDICO) return CriaMedico(d, c, bufferCRM);
            else if (tipo == SECRETARIO) return CriaSecretario(d, c, bufferNivelAcesso);
            else return CriaPaciente(d);
        }
        else {
            DesalocaDadosPessoais(d);
            if (c) DesalocaCredenciais(c);
        }
    }

    // Retorna null caso nao encontre nenhuma pessoa com o CPF fornecido
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
    fclose(d->arqvInicio);

    free(d);
}