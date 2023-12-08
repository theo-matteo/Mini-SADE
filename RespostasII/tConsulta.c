#include "tConsulta.h"
#define TAM_MAX_CPF 15
#define TAM_MAX_DATA 11
#define TAM_MAX_NOME 100
#define TAM_CRM 12
#define TAM_INSTRUCOES 300

struct tConsulta {

    // Identificacao do Paciente
    char cpfPaciente[TAM_MAX_CPF];

    // Identificacao do Medico
    char cpfMedico[TAM_MAX_CPF];
    char CRM[TAM_CRM];

    // Informacoes que serao obtidas na consulta
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
    char CRM[TAM_CRM] = {'\0'};
    char nomeMedico[TAM_MAX_NOME] = {'\0'};
    char cpfMedico[TAM_MAX_CPF] = {'\0'};


    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE: ");
    scanf("%s", cpfPaciente);
    scanf("%*c");
    printf("############################################################\n");

    tPaciente* paciente = ObtemPessoaArquivoBinario(PACIENTE, ObtemArquivoPacientes(d), cpfPaciente);
    if (!paciente) {
        printf("PACIENTE SEM CADASTRO\n\n");
        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        char c; scanf("%c%*c", &c);
        printf("############################################################\n");
        return NULL;
    }

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE: %s\n", ObtemCPFPaciente(paciente));
    printf("- - -\n");
    printf("- NOME: %s\n", ObtemNomePaciente(paciente));
    printf("- DATA DE NASCIMENTO: %s\n", ObtemDtNascPaciente(paciente));
    printf("- - -\n");

    // Verifica se o usuario do sistema eh umm medico e obtem informacoes do medico
    if (ObtemTipoUsuarioSistema(user) == M) {
        tMedico* m = (tMedico*) ObtemUsuarioSistema(user);
        strcpy(CRM, ObtemCRMMedico(m));
        strcpy(nomeMedico, ObtemNomeMedico(m));
        strcpy(cpfMedico, ObtemCPFMedico(m));
    }

    // Le informacoes clinicas 
    tConsulta* consulta = LeInformacoesConsulta(cpfPaciente, cpfMedico, CRM);  

    // Obtem informacoes da consulta 
    char* data = ObtemDataConsulta(consulta);
    char* nomePaciente = ObtemNomePaciente(paciente);
    
    // Loop para realizar as operacoes da consulta
    while (true) {

        int op;
        PrintTelaConsultaMedica();
        scanf("%d%*c", &op);

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
    printf("############################################################\n");

    return criaReceita(nomePaciente, tipoUsoEnum, nomeMedicamento, tipoMedicamento, instrucoes, qtd, nomeMedico, CRM, data);
}

void AdicionaLesaoConsulta (tConsulta* c, tLesao* l) {
    c->qtdLesoes++;
    c->lesoes = (tLesao**) realloc(c->lesoes, sizeof(tLesao*) * c->qtdLesoes);
    c->lesoes[c->qtdLesoes - 1] = l;
}

void PrintTelaConsultaMedica() {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) CADASTRAR LESAO\n");
    printf("\t(2) GERAR RECEITA MEDICA\n");
    printf("\t(3) SOLICITACAO DE BIOPSIA\n");
    printf("\t(4) ENCAMINHAMENTO\n");
    printf("\t(5) ENCERRAR CONSULTA\n");
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

void SalvaConsultasArquivoBinario (tConsulta** consultas, int qtd, FILE* file) {

    if (consultas == NULL) return;

    for (int i = 0; i < qtd; i++) {
        fwrite(consultas[i]->cpfPaciente, sizeof(char), TAM_MAX_CPF, file);
        fwrite(consultas[i]->cpfMedico, sizeof(char), TAM_MAX_CPF, file);
        fwrite(consultas[i]->CRM, sizeof(char), TAM_CRM, file);
        fwrite(consultas[i]->data, sizeof(char), TAM_MAX_DATA, file);
        fwrite(consultas[i]->tipoPele, sizeof(char), TAM_MAX_TIPO_PELE, file);
        fwrite(&consultas[i]->possui_diabetes, sizeof(int), 1, file);
        fwrite(&consultas[i]->eh_fumante, sizeof(int), 1, file);
        fwrite(&consultas[i]->possui_alergia, sizeof(int), 1, file);
        fwrite(&consultas[i]->possui_HistCancer, sizeof(int), 1, file);
    }

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