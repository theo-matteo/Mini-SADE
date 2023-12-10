#include "tDadosReceita.h"

#define MAX_TAM_NOME_MEDICAMENTO 50
#define MAX_TAM_TIPO_MEDICAMENTO 50
#define MAX_TAM_INSTRUCOES 300
#define TAM_CRM 12
#define TAM_MAX_NOME 100
#define TAM_MAX_DATA 11

struct tDataReceita {
    char* nome_paciente;
    char* crm;
    char* nome_medico;
    char* data;
    char* nome_medicamento;
    char* tipo_medicamento;
    char* instrucoes;
    int qtd;
};

struct tListaDataReceita {
    tDataReceita** dados;
    int qtd;
};


tListaDataReceita* CriaListaDataReceita () {
    
    tListaDataReceita* l = malloc(sizeof(tListaDataReceita));
    if (!l) {
        printf("Falha na Alocacao da Lista de Dados da Receita\n");
        exit(EXIT_FAILURE);
    }

    l->dados = NULL;
    l->qtd = 0;
    return l;
}

void DesalocaListaDataReceita (tListaDataReceita* l) {
    
    if (l == NULL) return;

    if (l->dados) {
        for (int i = 0; i < l->qtd; i++) {
            DesalocaDadosReceita(l->dados[i]);
        }
        free(l->dados);
    }

    free(l); 
}


void AdicionaDataReceitaLista (tListaDataReceita* l, tDataReceita* d) {

    if (l == NULL || d == NULL);

    l->qtd++;
    l->dados = (tDataReceita**) realloc(l->dados, sizeof(tDataReceita*) * l->qtd);
    l->dados[l->qtd - 1] = d;

}

tDataReceita* AlocaDadosReceita () {

    tDataReceita* d = malloc(sizeof(tDataReceita));
    if (d == NULL) {
        printf("Erro ao alocar dados da receita\n");
        exit(1);
    }

    d->nome_paciente = malloc(sizeof(char) * TAM_MAX_NOME);
    d->crm = malloc(sizeof(char) * TAM_CRM);
    d->nome_medico = malloc(sizeof(char) * TAM_MAX_NOME);
    d->data = malloc(sizeof(char) * TAM_MAX_DATA);
    d->nome_medicamento = malloc(sizeof(char) * MAX_TAM_NOME_MEDICAMENTO);
    d->tipo_medicamento = malloc(sizeof(char) * MAX_TAM_TIPO_MEDICAMENTO);
    d->instrucoes = malloc(sizeof(char) * MAX_TAM_INSTRUCOES);

    memset(d->nome_paciente, '\0', TAM_MAX_NOME);
    memset(d->crm, '\0', TAM_CRM);
    memset(d->nome_medico, '\0', TAM_MAX_NOME);
    memset(d->data, '\0', TAM_MAX_DATA);
    memset(d->nome_medicamento, '\0', MAX_TAM_NOME_MEDICAMENTO);
    memset(d->tipo_medicamento, '\0', MAX_TAM_TIPO_MEDICAMENTO);
    memset(d->instrucoes, '\0', MAX_TAM_INSTRUCOES);


    return d;
}

tDataReceita* LeDadosReceita (char* nome_paciente, char* data, char* nome_medico, char* crm) {

    tDataReceita* d = AlocaDadosReceita();

    // Nome do Medicamento  
    printf("NOME DO MEDICAMENTO: ");
    scanf("%[^\n]", d->nome_medicamento);
    scanf("%*c");

    // Comprimidos ou Pomada 
    printf("TIPO DE MEDICAMENTO: "); 
    scanf("%s", d->tipo_medicamento);

    printf("QUANTIDADE: ");
    scanf("%d%*c", &d->qtd);

    printf("INSTRUCOES DE USO: ");
    scanf("%[^\n]", d->instrucoes);
    scanf("%*c");

    // Copia informacoes de fora 
    strcpy(d->nome_paciente, nome_paciente);
    strcpy(d->crm, crm);
    strcpy(d->nome_medico, nome_medico);

    // Realiza formatacao da data 
    int dia, mes, ano;
    sscanf(data, "%d/%d/%d", &dia, &mes, &ano);
    sprintf(d->data, "%d/%d/%d", dia, mes, ano);
    
    return d;
}

void DesalocaDadosReceita (void* dado) {

    if (!dado) return;

    tDataReceita* d = (tDataReceita*) dado;

    free(d->nome_paciente);
    free(d->crm);
    free(d->nome_medico);
    free(d->data);
    free(d->nome_medicamento);
    free(d->tipo_medicamento);
    free(d->instrucoes);
    free(d);

}

char* ObtemNomeMedicamento (tDataReceita* d) {
    return d->nome_medicamento;
}

char* ObtemTipoMedicamento (tDataReceita* d) {
    return d->tipo_medicamento;
}

char* ObtemInstrucoes (tDataReceita* d) {
    return d->instrucoes;
}

int ObtemQtdMedicamento (tDataReceita* d) {
    return d->qtd;
}

char* ObtemNomePacienteReceita (tDataReceita* d) {
    return d->nome_paciente;
}

char* ObtemNomeMedicoReceita (tDataReceita* d) {
    return d->nome_medico;
}

char* ObtemCRMReceita (tDataReceita* d) {
    return d->crm;
}

char* ObtemDataReceita (tDataReceita* d) {
    return d->data;
}





