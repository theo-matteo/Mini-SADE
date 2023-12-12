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
        exit(EXIT_FAILURE);
    }

    /* Aloca memoria para os dados da receita */
    d->nome_paciente = calloc(TAM_MAX_NOME, sizeof(char));
    d->nome_medico = calloc(TAM_MAX_NOME, sizeof(char));
    d->crm = calloc(TAM_CRM, sizeof(char));
    d->data = calloc(TAM_MAX_DATA, sizeof(char));
    d->nome_medicamento = calloc(MAX_TAM_NOME_MEDICAMENTO, sizeof(char));
    d->tipo_medicamento = calloc(MAX_TAM_TIPO_MEDICAMENTO, sizeof(char));
    d->instrucoes = calloc(MAX_TAM_INSTRUCOES, sizeof(char));

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

    // formata data
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





