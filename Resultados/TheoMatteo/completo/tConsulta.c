#include "tConsulta.h"

struct tConsulta {

    // Paciente que realizou a consulta
    char cpfPaciente[TAM_MAX_CPF];

    // Medico que realizou a consulta
    char cpfMedico[TAM_MAX_CPF];
    char CRM[TAM_CRM];

    // Informacoes obtidas durante a consulta
    char data[TAM_MAX_DATA];
    Vector* lesoes;

    int possui_diabetes;
    int eh_fumante;
    int possui_alergia;
    int possui_HistCancer;
    char tipoPele[TAM_MAX_TIPO_PELE];
};

void ExecutaConsulta (tUsuario* user, tDatabase* d, tFila* f, Vector* dados_receita) {

    // Rotulo das lesoes cadastradas, eh incrementado gradualmente
    int numRotulo = 0;

    // CPF do paciente
    char cpfPaciente[TAM_MAX_CPF];

    // Informacoes do medico inicalizadas
    char CRM[TAM_CRM]; memset(CRM, '\0', TAM_CRM);
    char nomeMedico[TAM_MAX_NOME];  memset(nomeMedico, '\0', TAM_MAX_NOME);
    char cpfMedico[TAM_MAX_CPF]; memset(cpfMedico, '\0', TAM_MAX_CPF);

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
        ImprimeErroConsulta();
        return;
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
    tConsulta* consulta = CriaConsulta(cpfPaciente, cpfMedico, CRM);  

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
                VectorPushBack(consulta->lesoes, lesao);
                SalvaLesaoArquivoBinario(lesao, ObtemArquivoLesoes(d));
                break;

            case 2:
                tReceita* receita = PreencheCriaReceitaMedica(nomePaciente, CRM, nomeMedico, data, dados_receita);
                insereDocumentoFila(f, receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
                break;

            case 3:
                tBiopsia* biopsia = SolicitaBiopsia(consulta->lesoes, nomePaciente, cpfPaciente, nomeMedico, CRM, data);
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

   
   // Salva consulta no banco de dados
    SalvaConsultaArquivoBinario(consulta, ObtemArquivoConsultas(d));

    // Desaloca estruturas usadas durante a consulta
    DesalocaPaciente(paciente);
    DesalocaConsulta(consulta);
}

tConsulta* CriaConsulta(char* cpfPaciente, char* cpfMedico, char* CRM) {

    tConsulta* consulta = (tConsulta*) malloc(sizeof(tConsulta));
    if (!consulta) {
        printf("Falha na Alocacao da Consulta\n");
        exit(EXIT_FAILURE);
    }

    // Aloca um vetor de lesoes
    consulta->lesoes = VectorConstruct();

    // Inicializa as strings com zero 
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

tReceita* PreencheCriaReceitaMedica (char* nomePaciente, char* CRM, char* nomeMedico, char* data,  Vector* dados_receita) {

    // Realiza leitura dos dados da receita e aloca dinamicamente 
    tDataReceita* d = LeDadosReceita(nomePaciente, data, nomeMedico, CRM);
    VectorPushBack(dados_receita, d); 

    // Mensagem de sucesso
    printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    char c; scanf("%c%*c", &c);
    ImprimeBarraFinalMenu();

    // Cria uma receita com dados alocados dinamicamente 
    return CriaReceitaDadosReceita(d);
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

int ObtemQtdConsultasBinario (FILE* file) {

    // Vetor que ira armazenar os cpfs de todos os pacientes atendidos
    char** cpfPacientes = NULL;
    int qtdPacientes = 0;
    
    // Buffer para armazenar as informacoes nao relevantes 
    int qtdBytesBuffer = TAM_MAX_CPF + TAM_MAX_DATA + TAM_MAX_TIPO_PELE + TAM_CRM + sizeof(int) * 4;
    char buffer[qtdBytesBuffer];

    // Retorna o ponteiro do arquivo para o inicio
    rewind(file);

    while (!feof(file)) {

        char cpf[TAM_MAX_CPF];
        if (fread(cpf, sizeof(char), TAM_MAX_CPF, file) != TAM_MAX_CPF) break;
        else  {
            qtdPacientes++;
            cpfPacientes = (char**) realloc(cpfPacientes, sizeof(char*) * qtdPacientes);
            cpfPacientes[qtdPacientes- 1] = (char*) malloc(sizeof(char) * TAM_MAX_CPF);
            strcpy(cpfPacientes[qtdPacientes - 1], cpf);
        }

        if (fread(buffer, sizeof(char), qtdBytesBuffer, file) != qtdBytesBuffer) break;
    }

    int qtd = ObtemQtdCpfUnicos(cpfPacientes, qtdPacientes);

    // Desaloca array de cpf's 
    if (cpfPacientes) {
        for (int i = 0; i < qtdPacientes; i++) {
            free(cpfPacientes[i]);
        }
        free(cpfPacientes);
    }

    return qtd;
}

int ObtemQtdCpfUnicos (char** cpfs, int qtd) {

    int count = 0;
    bool flag;

    for (int i = 0; i < qtd; i++) {
        flag = false;
        for (int j = 0; j < i; j++) {
            if (strcmp(cpfs[i], cpfs[j]) == 0) {
                flag = true;
                break;
            }
        }
        if (!flag) count++;
    }

    return count;
}

void ImprimeErroConsulta() {
    printf("PACIENTE SEM CADASTRO\n\n");
    printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    char c; scanf("%c%*c", &c);
    ImprimeBarraFinalMenu();
}

void DesalocaConsulta (void* dado) {
    if (!dado) return;
    tConsulta* c = (tConsulta*) dado;
    VectorDestroy(c->lesoes, DesalocaLesao);
    free(c);
}