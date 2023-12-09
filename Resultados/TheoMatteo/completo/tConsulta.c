#include "tConsulta.h"

struct tConsulta {

    // Paciente que realizou a consulta
    char cpfPaciente[TAM_MAX_CPF];

    // Medico que realizou a consulta
    char cpfMedico[TAM_MAX_CPF];
    char CRM[TAM_CRM];

    // Informacoes obtidas durante a consulta
    char data[TAM_MAX_DATA];
    tLesao** lesoes;
    int qtdLesoes;

    int possui_diabetes;
    int eh_fumante;
    int possui_alergia;
    int possui_HistCancer;
    char tipoPele[TAM_MAX_TIPO_PELE];
};

tConsulta* RealizaConsulta (tUsuario* user, tDatabase* d, tFila* f) {

    // Indica o rotulo da lesao cadastrada, eh incrementada toda vez que cadastra uma nova lesao
    int numRotulo = 0;

    // CPF do paciente
    char cpfPaciente[TAM_MAX_CPF];

    // Informacoes do medico inicalizadas com string vazias
    char CRM[TAM_CRM];
    char nomeMedico[TAM_MAX_NOME];
    char cpfMedico[TAM_MAX_CPF];

    // Inicializa as strings com '\0'
    memset(CRM, '\0', TAM_CRM);
    memset(nomeMedico, '\0', TAM_MAX_NOME);
    memset(cpfMedico, '\0', TAM_MAX_CPF);

    // Obtem o cpf do paciente
    ImprimeBarraConsultaMedica();
    printf("CPF DO PACIENTE: ");
    scanf("%s", cpfPaciente);
    scanf("%*c");
    ImprimeBarraFinalMenu();

    // Obtem o paciente direto do arquivo binario
    tPaciente* paciente = BuscaPessoaPorCpf(PACIENTE, ObtemArquivoPacientes(d), cpfPaciente);

    // Caso o paciente nao foi encontrado, encerra consulta
    if (!paciente) {
        printf("PACIENTE SEM CADASTRO\n\n");
        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        char c; scanf("%c%*c", &c);
        ImprimeBarraFinalMenu();
        return NULL;
    }

    // Imprime as informacoes do paciente apos ser encontrado 
    ImprConsultaDadosPaciente(ObtemNomePaciente(paciente), ObtemCPFPaciente(paciente), ObtemDtNascPaciente(paciente));
    

    // Verifica se o usuario do sistema eh umm medico e obtem informacoes do medico
    if (ObtemTipoUsuarioSistema(user) == M) {
        strcpy(CRM, ObtemCRMMedico(ObtemUsuarioSistema(user)));
        strcpy(nomeMedico, ObtemNomeMedico(ObtemUsuarioSistema(user)));
        strcpy(cpfMedico, ObtemCPFMedico(ObtemUsuarioSistema(user)));
    }

    // Le informacoes clinicas
    tConsulta* consulta = LeInformacoesConsulta(cpfPaciente, cpfMedico, CRM);  

    // Obtem informacoes da consulta 
    char* data = ObtemDataConsulta(consulta);
    char* nomePaciente = ObtemNomePaciente(paciente);
    
    // Loop para realizar as operacoes da consulta
    while (true) {

        int op;
        ImprTelaConsultaMedica();
        scanf("%d%*c", &op);
        ImprimeBarraFinalMenu();

        switch (op) {

            case 1:
                tLesao* lesao = CadastraLesao(++numRotulo, cpfPaciente, cpfMedico, CRM, data);
                AdicionaLesaoConsulta(consulta, lesao);
                SalvaLesaoArquivoBinario(lesao, ObtemArquivoLesoes(d));
                break;

            case 2:
                tReceita* receita = PreencheCriaReceitaMedica(nomePaciente, CRM, nomeMedico, data);
                insereDocumentoFila(f, receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
                break;

            case 3:
                tLesao** lesoes = ObtemLesoesConsulta(consulta);
                int qtdLesoes = ObtemQtdLesoesConsulta(consulta);
                tBiopsia* biopsia = SolicitaBiopsia(lesoes, qtdLesoes, nomePaciente, cpfPaciente, nomeMedico, CRM, data);
                if (biopsia) insereDocumentoFila(f, biopsia, imprimeNaTelaBiopsia, imprimeEmArquivoBiopsia, DesalocaBiopsia);
                break;
                
            case 4:
                tEncaminhamento* encaminhamento = CriaEncaminhamento(ObtemNomePaciente(paciente), ObtemCPFPaciente(paciente), nomeMedico, CRM, data);
                insereDocumentoFila(f, encaminhamento, ImprimeEncaminhamentoNaTela, ImprimeEncaminhamentoArquivo, DesalocaEncaminhamento);
                break;

            default:
                break;
        }

        if (op == 5) break;
    }

    DesalocaPaciente(paciente);
    return consulta;
}

tConsulta* LeInformacoesConsulta(char* cpfPaciente, char* cpfMedico, char* CRM) {

    tConsulta* consulta = (tConsulta*) malloc(sizeof(tConsulta));
    if (!consulta) {
        printf("Falha na Alocacao da Consulta\n");
        exit(EXIT_FAILURE);
    }

    consulta->lesoes = NULL;
    consulta->qtdLesoes = 0;

    memset(consulta->data, '\0', TAM_MAX_DATA);
    memset(consulta->tipoPele, '\0', TAM_MAX_TIPO_PELE);
    memset(consulta->cpfMedico, '\0', TAM_MAX_CPF);
    memset(consulta->cpfPaciente, '\0', TAM_MAX_CPF);
    memset(consulta->CRM, '\0', TAM_CRM);

    printf("DATA DA CONSULTA: ");
    scanf("%s", consulta->data);

    printf("POSSUI DIABETES: ");
    scanf("%d", &consulta->possui_diabetes);

    printf("FUMANTE: ");
    scanf("%d", &consulta->eh_fumante);

    printf("ALEGIA A MEDICAMENTO: ");
    scanf("%d", &consulta->possui_alergia);

    printf("HISTORICO DE CANCER: ");
    scanf("%d", &consulta->possui_HistCancer);

    printf("TIPO DE PELE: ");
    scanf("%s", consulta->tipoPele);
    scanf("%*c");

    // Copia informacoes do medico para dentro da consulta
    strcpy(consulta->cpfPaciente, cpfPaciente);
    strcpy(consulta->cpfMedico, cpfMedico);
    strcpy(consulta->CRM, CRM);

    return consulta;
}

tReceita* PreencheCriaReceitaMedica (char* nomePaciente, char* CRM, char* nomeMedico, char* data) {

    eTipoUso tipoUsoEnum;
    int qtd;
    char tipoUso[10];
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    char instrucoes[TAM_INSTRUCOES];

    printf("TIPO DE USO: "); // ORAL ou TOPICO
    scanf("%s", tipoUso);
    scanf("%*c");

    // Converte  para enum
    if (!strcmp(tipoUso, "ORAL")) tipoUsoEnum = ORAL;
    else tipoUsoEnum = TOPICO;

    // Nome do Medicamento  
    printf("NOME DO MEDICAMENTO: ");
    scanf("%[^\n]", nomeMedicamento);
    scanf("%*c");

    // Comprimidos ou Pomada 
    printf("TIPO DE MEDICAMENTO: "); 
    scanf("%s", tipoMedicamento);

    printf("QUANTIDADE: ");
    scanf("%d%*c", &qtd);

    printf("INSTRUCOES DE USO: ");
    scanf("%[^\n]", instrucoes);
    scanf("%*c");

    printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    char c; scanf("%c%*c", &c);
    ImprimeBarraFinalMenu();

    if (nomeMedico[0] == '\0') return criaReceita(nomePaciente, tipoUsoEnum, nomeMedicamento, tipoMedicamento, instrucoes, qtd, "\0", "\0", data);
    return criaReceita(nomePaciente, tipoUsoEnum, nomeMedicamento, tipoMedicamento, instrucoes, qtd, nomeMedico, CRM, data);
}

void AdicionaLesaoConsulta (tConsulta* c, tLesao* l) {
    c->qtdLesoes++;
    c->lesoes = (tLesao**) realloc(c->lesoes, sizeof(tLesao*) * c->qtdLesoes);
    c->lesoes[c->qtdLesoes - 1] = l;
}

int ObtemQtdLesoesConsulta (tConsulta* c) {
    return c->qtdLesoes;
}

tLesao** ObtemLesoesConsulta(tConsulta* c) {
    return c->lesoes;
}

char* ObtemDataConsulta (tConsulta* c) {
    return c->data;
}

void SalvaConsultaArquivoBinario (tConsulta* consulta, FILE* file) {

    if (consulta == NULL) return;

    fwrite(consulta->cpfPaciente, sizeof(char), TAM_MAX_CPF, file);
    fwrite(consulta->cpfMedico, sizeof(char), TAM_MAX_CPF, file);
    fwrite(consulta->CRM, sizeof(char), TAM_CRM, file);
    fwrite(consulta->data, sizeof(char), TAM_MAX_DATA, file);
    fwrite(consulta->tipoPele, sizeof(char), TAM_MAX_TIPO_PELE, file);
    fwrite(&consulta->possui_diabetes, sizeof(int), 1, file);
    fwrite(&consulta->eh_fumante, sizeof(int), 1, file);
    fwrite(&consulta->possui_alergia, sizeof(int), 1, file);
    fwrite(&consulta->possui_HistCancer, sizeof(int), 1, file);
}

int ObtemQuantidadeConsultasBinario (FILE* file) {

    char** cpfPacientesAtendidos = NULL;
    int qtdPacientesAtendidos = 0;
    int qtdBytesBuffer = TAM_MAX_CPF + TAM_MAX_DATA + TAM_MAX_TIPO_PELE + TAM_CRM + sizeof(int) * 4;
    char buffer[qtdBytesBuffer];

    rewind(file);

    while (!feof(file)) {

        char cpf[TAM_MAX_CPF];
        if (fread(cpf, sizeof(char), TAM_MAX_CPF, file) != TAM_MAX_CPF) break;
        else  {
            qtdPacientesAtendidos++;
            cpfPacientesAtendidos = (char**) realloc(cpfPacientesAtendidos, sizeof(char*) * qtdPacientesAtendidos);
            cpfPacientesAtendidos[qtdPacientesAtendidos - 1] = (char*) malloc(sizeof(char) * TAM_MAX_CPF);
            strcpy(cpfPacientesAtendidos[qtdPacientesAtendidos - 1], cpf);
        }

        if (fread(buffer, sizeof(char), qtdBytesBuffer, file) != qtdBytesBuffer) break;

    }

    int count = 0;
    bool flag;

    for (int i = 0; i < qtdPacientesAtendidos; i++) {
        flag = false;
        for (int j = 0; j < i; j++) {
            if (strcmp(cpfPacientesAtendidos[i], cpfPacientesAtendidos[j]) == 0) {
                flag = true;
                break;
            }
        }
        if (!flag) count++;
    }

    // Desaloca array de cpf's 
    if (cpfPacientesAtendidos) {
        for (int i = 0; i < qtdPacientesAtendidos; i++) {
            free(cpfPacientesAtendidos[i]);
        }
        free(cpfPacientesAtendidos);
    }

    return count;
}

char* ObtemCPFPacienteConsulta (tConsulta* c) {
    return c->cpfPaciente;
}


void DesalocaConsulta (tConsulta* c) {

    if (!c) return;

    if (c->lesoes) {
        for (int i = 0; i < c->qtdLesoes; i++) {
            DesalocaLesao(c->lesoes[i]);
        }
        free(c->lesoes);
    }

    free(c);
}