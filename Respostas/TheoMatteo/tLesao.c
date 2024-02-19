#include "tLesao.h"
#define TAM_MAX_CPF 15
#define TAM_MAX_DATA 11
#define TAM_MAX_CRM 12

struct tLesao {

    // Informacoes obtidas durante o cadastro da lesao
    char cpfPaciente[TAM_MAX_CPF];
    char cpfMedico[TAM_MAX_CPF];
    char CRMmedico[TAM_MAX_CRM];
    char data[TAM_MAX_DATA];

    // Informacoes da Lesao
    char rotulo[TAM_MAX_ROTULO];
    char diagnostico[TAM_MAX_DIAGNOSTICO];
    char regiao_corpo [TAM_MAX_REGIAO_CORPO];
    int tamanho;
    int enviar_cirurgia;
    int enviar_crioterapia;
}; 

tLesao* CriaLesao () {

    tLesao* lesao = (tLesao*) malloc(sizeof(tLesao));
    if (lesao == NULL) {
        printf("Falha na Alocacao da Lesao\n");
        exit(EXIT_FAILURE);
    }

    memset(lesao->diagnostico, '\0', TAM_MAX_DIAGNOSTICO);
    memset(lesao->regiao_corpo, '\0', TAM_MAX_REGIAO_CORPO);
    memset(lesao->rotulo, '\0', TAM_MAX_ROTULO);
    memset(lesao->cpfPaciente, '\0', TAM_MAX_CPF);
    memset(lesao->cpfMedico, '\0', TAM_MAX_CPF);
    memset(lesao->CRMmedico, '\0', TAM_MAX_CRM);

    return lesao;
}

tLesao* CadastraLesao (int numRotulo, char* cpfPaciente, char* cpfMedico, char* CRM, char* data) {

    tLesao* lesao = CriaLesao();

    ImprimeBarraConsultaMedica();
    printf("CADASTRO DE LESAO:\n");

    sprintf(lesao->rotulo, "L%d", numRotulo);
    strcpy(lesao->cpfPaciente, cpfPaciente);
    strcpy(lesao->cpfMedico, cpfMedico);
    strcpy(lesao->CRMmedico, CRM);
    strcpy(lesao->data, data);

    printf("DIAGNOSTICO CLINICO: ");
    scanf("%[^\n]", lesao->diagnostico);
    scanf("%*c");

    printf("REGIAO DO CORPO: ");
    scanf("%[^\n]", lesao->regiao_corpo);
    scanf("%*c");

    printf("TAMANHO: ");
    scanf("%d", &lesao->tamanho);

    printf("ENVIAR PARA CIRURGIA: ");
    scanf("%d", &lesao->enviar_cirurgia);

    printf("ENVIAR PARA CRIOTERAPIA: ");
    scanf("%d", &lesao->enviar_crioterapia);

    printf("\nLESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    char c; scanf("%c%*c", &c);
    ImprimeBarraFinalMenu();

    return lesao;
}

tLesao* ClonaLesao (tLesao* l) {

    // Cria um clone
    tLesao* lesao = CriaLesao();

    // Copia os dados da lesao original para o clone
    strcpy(lesao->cpfPaciente, l->cpfPaciente);  
    strcpy(lesao->cpfMedico, l->cpfMedico);
    strcpy(lesao->CRMmedico, l->CRMmedico);
    strcpy(lesao->data, l->data);

    strcpy(lesao->diagnostico, l->diagnostico);
    strcpy(lesao->regiao_corpo, l->regiao_corpo);
    strcpy(lesao->rotulo, l->rotulo);  
    
    lesao->tamanho = l->tamanho;
    lesao->enviar_cirurgia = l->enviar_cirurgia;
    lesao->enviar_crioterapia = l->enviar_crioterapia;

    return lesao;
}

char* ObtemDiagnosticoLesao (tLesao* l) {
    return l->diagnostico;
}

int ObtemTamanhoLesao (tLesao* l) {
    return l->tamanho;
}

char* ObtemRegiaoCorpoLesao (tLesao* l) {
    return l->regiao_corpo;
}


bool LesaoFoiEncaminhadaPraCirurgia (tLesao* l) {
    return (l->enviar_cirurgia == 1);
}

bool LesaoFoiEncaminhaCrioterapia (tLesao* l) {
    return (l->enviar_crioterapia == 1);
}

char* ObtemRotuloLesao (tLesao* l) {
    return l->rotulo;
}

void SalvaLesaoArquivoBinario (tLesao* l, FILE* file) {
    
    if (!l) return;

    // Salva informacoes (ancora) da lesao no arquivo
    fwrite(l->cpfPaciente, sizeof(char), TAM_MAX_CPF, file);
    fwrite(l->data, sizeof(char), TAM_MAX_DATA, file);


    fwrite(l->CRMmedico, sizeof(char), TAM_MAX_CRM, file);
    fwrite(l->cpfMedico, sizeof(char), TAM_MAX_CPF, file);
    fwrite(l->rotulo, sizeof(char), TAM_MAX_ROTULO, file);
    fwrite(l->diagnostico, sizeof(char), TAM_MAX_DIAGNOSTICO, file);
    fwrite(l->regiao_corpo, sizeof(char), TAM_MAX_REGIAO_CORPO, file);
    fwrite(&l->tamanho, sizeof(int), 1, file);
    fwrite(&l->enviar_cirurgia, sizeof(int), 1, file);
    fwrite(&l->enviar_crioterapia, sizeof(int), 1, file);
    
}

bool LesaoPertencePaciente(char* cpf, tLesao* l) {
    if (!strcmp(cpf, l->cpfPaciente)) return true;
    return false;
}

Vector* ObtemLesoesConsulta(char* cpf, char* data, FILE* file) {

    rewind(file);
    Vector* v = VectorConstruct();

    int buffer_size = TAM_MAX_CRM + TAM_MAX_CPF + TAM_MAX_ROTULO  + TAM_MAX_DIAGNOSTICO + TAM_MAX_REGIAO_CORPO + sizeof(int) * 3;
    char buffer[buffer_size];

    while(true) {

        char cpf_paciente[TAM_MAX_CPF];
        char data_consulta[TAM_MAX_DATA];

        if (fread(cpf_paciente, sizeof(char), TAM_MAX_CPF, file) != TAM_MAX_CPF) break;
        fread(data_consulta, sizeof(char), TAM_MAX_DATA, file);

        if (!strcmp(cpf, cpf_paciente) && !strcmp(data, data_consulta)) {

            tLesao* lesao = CriaLesao();
            strcpy(lesao->cpfPaciente, cpf);
            strcpy(lesao->data, data);

            fread(lesao->CRMmedico, sizeof(char), TAM_MAX_CRM, file);
            fread(lesao->cpfMedico, sizeof(char), TAM_MAX_CPF, file); 
            fread(lesao->rotulo, sizeof(char), TAM_MAX_ROTULO, file); 
            fread(lesao->diagnostico, sizeof(char), TAM_MAX_DIAGNOSTICO, file); 
            fread(lesao->regiao_corpo, sizeof(char), TAM_MAX_REGIAO_CORPO, file); 
            fread(&lesao->tamanho, sizeof(int), 1, file);
            fread(&lesao->enviar_cirurgia, sizeof(int), 1, file);
            fread(&lesao->enviar_crioterapia, sizeof(int), 1, file);

            VectorPushBack(v, lesao);
        }
        else {
            if(fread(buffer, sizeof(char), buffer_size, file) != buffer_size) break;
        }

    }


    return v;
}

tLesao* ObtemLesaoArquivoBinario (FILE* file) {
    
    char cpfPaciente[TAM_MAX_CPF];

    // Informacoes de ancoragem
    if (fread(cpfPaciente, sizeof(char), TAM_MAX_CPF, file) != TAM_MAX_CPF) return NULL;
    tLesao* lesao = CriaLesao();
    fread(lesao->data, sizeof(char), TAM_MAX_DATA, file);

    // Outras informacoes
    fread(lesao->CRMmedico, sizeof(char), TAM_MAX_CRM, file);
    fread(lesao->cpfMedico, sizeof(char), TAM_MAX_CPF, file); 
    fread(lesao->rotulo, sizeof(char), TAM_MAX_ROTULO, file); 
    fread(lesao->diagnostico, sizeof(char), TAM_MAX_DIAGNOSTICO, file); 
    fread(lesao->regiao_corpo, sizeof(char), TAM_MAX_REGIAO_CORPO, file); 
    fread(&lesao->tamanho, sizeof(int), 1, file);
    fread(&lesao->enviar_cirurgia, sizeof(int), 1, file);
    fread(&lesao->enviar_crioterapia, sizeof(int), 1, file);
    
    return lesao;
}

void ImprimeLesaoArquivo (void* dado, FILE* file) {

    if (!dado) return;
    tLesao* l = (tLesao*) dado;

    fprintf(file, "ROTULO: %s\n", l->rotulo);
    fprintf(file, "DIAGNOSTICO CLINICO: %s\n", l->diagnostico);
    fprintf(file, "REGIAO DO CORPO: %s\n", l->regiao_corpo);
    fprintf(file, "TAMANHO: %d\n", l->tamanho);
    fprintf(file, "ENVIADA PARA CIRURGIA: %s\n", RetornaResposta(l->enviar_cirurgia));
    fprintf(file, "ENVIADA PARA CRIOTERAPIA: %s\n", RetornaResposta(l->enviar_crioterapia));
    

}


void DesalocaLesao (void* dado) {
    if (!dado) return;
    tLesao* l = (tLesao*) dado;
    if (l) free(l);
}

