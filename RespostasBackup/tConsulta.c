#include "tConsulta.h"
#define TAM_MAX_CPF 20
#define TAM_MAX_DATA 20
#define TAM_MAX_NOME 100
#define TAM_CRM 12
#define TAM_INSTRUCOES 300

struct tConsulta {

    char data[TAM_MAX_DATA];
    tLesao** lesoes;
    int qtdLesoes;

    // Informacoes Obtidas na Consulta
    int possui_diabetes;
    int eh_fumante;
    int possui_alergia;
    int possui_HistCancer;
    char tipoPele[TAM_MAX_TIPO_PELE];
};

void RealizaConsulta (tUsuarioSistema* user, tDatabase* d, tFila* f) {

    char cpf[TAM_MAX_CPF];
    char CRM[] = "\0";
    char nomeMedico[] = "\0";

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE: ");
    scanf("%s", cpf);
    printf("############################################################\n");

    tPaciente* paciente = ObtemPessoaArquivoBinario(PACIENTE, ObtemArquivoPacientes(d), cpf);
    if (!paciente) {
        printf("PACIENTE SEM CADASTRO\n\n");
        printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        char c; scanf("%c%*c", &c);
        printf("############################################################\n");
        return;
    }

    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE: %s\n", ObtemCPFPaciente(paciente));
    printf("- - -\n");
    printf("- NOME: %s\n", ObtemNomePaciente(paciente));
    printf("- DATA DE NASCIMENTO: %s\n", ObtemDtNascPaciente(paciente));
    printf("- - -\n");

    tConsulta* consulta = LeInformacoesConsulta();  
    
    if (ObtemTipoUsuarioSistema(user) == MED) {
        tMedico* m = (tMedico*) ObtemUsuarioSistema(user);
        strcpy(CRM, ObtemCRMMedico(m));
        strcpy(nomeMedico, ObtemNomeMedico(m));
    }

    while (true) {

        int op;
        PrintTelaConsultaMedica();
        scanf("%d%*c", &op);

        switch (op) {

            case 1:
                tLesao* lesao = CadastraLesao();
                AdicionaLesaoConsulta(consulta, lesao);
                break;

            case 2:
                tReceita* receita = PreencheCriaReceitaMedica(ObtemNomePaciente(paciente), CRM, nomeMedico, consulta->data);
                insereDocumentoFila(f, receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);

            case 3:
                tLesao** lesoes = ObtemLesoesConsulta(consulta);
                int qtdLesoes = ObtemQtdLesoesConsulta(consulta);
                char* data = ObtemDataConsulta(consulta);
                tBiopsia* biopsia = SolicitaBiopsia(lesoes, qtdLesoes, ObtemNomePaciente(paciente), ObtemCPFPaciente(paciente), nomeMedico, CRM, data);
                

            default:
                break;
        }

        if (op > 2) break;

    }

    DesalocaConsulta(consulta);
    DesalocaPaciente(paciente);
}

tConsulta* LeInformacoesConsulta() {

    tConsulta* consulta = (tConsulta*) malloc(sizeof(tConsulta));
    if (!consulta) {
        printf("Falha na Alocacao da Consulta\n");
        exit(EXIT_FAILURE);
    }

    consulta->lesoes = NULL;
    consulta->qtdLesoes = 0;

    memset(consulta->data, '\0', TAM_MAX_DATA);
    memset(consulta->tipoPele, '\0', TAM_MAX_TIPO_PELE);

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


    return consulta;
}

tReceita* PreencheCriaReceitaMedica (char* nomePaciente, char* CRM, char* nomeMedico, char* data) {

    int tipoUso, qtd;
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    char instrucoes[TAM_INSTRUCOES];

    printf("TIPO DE USO: ");
    scanf("%d%*c", &tipoUso);

    printf("NOME DO MEDICAMENTO: ");
    scanf("%[^\n]", nomeMedicamento);
    scanf("%*c");

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

    return criaReceita(nomePaciente, tipoUso, nomeMedicamento, tipoMedicamento, instrucoes, qtd, nomeMedico, CRM, data);
}

void AdicionaLesaoConsulta (tConsulta* c, tLesao* l) {
    c->qtdLesoes++;
    c->lesoes = realloc(c->lesoes, sizeof(tLesao*) * c->qtdLesoes);
    c->lesoes[c->qtdLesoes - 1] = l;
}

void PrintTelaConsultaMedica() {
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) CADASTRAR LESAO\n");
    printf("\t(2) GERAR RECEITA MEDICA\n");
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