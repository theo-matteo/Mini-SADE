#include "tDadosPessoais.h"
#define TAM_NOME 100
#define TAM_CPF 12
#define TAM_DATA 16
#define TAM_TELEFONE 16
#define TAM_GENERO 12

struct tDadosPessoais {
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char dtNasc[TAM_DATA];
    char tel[TAM_TELEFONE];
    char genero[TAM_GENERO];
};

tDadosPessoais* CriaDadosPessoais (char* nome, char* cpf, char* dtNasc, char* tel, char* genero) {

    tDadosPessoais* d = (tDadosPessoais *) malloc(sizeof(tDadosPessoais));
    if (d == NULL) {
        printf("Falha na Alocacao dos Dados Pessoais \n");
        exit(EXIT_FAILURE);
    }

    memset(d->nome, '\0', TAM_NOME);
    memset(d->cpf, '\0', TAM_CPF);
    memset(d->dtNasc, '\0', TAM_DATA);
    memset(d->tel, '\0', TAM_TELEFONE);
    memset(d->genero, '\0', TAM_GENERO);

    strcpy(d->nome, nome);
    strcpy(d->cpf, cpf);
    strcpy(d->dtNasc, dtNasc);
    strcpy(d->tel, tel);
    strcpy(d->genero, genero);

    return d;
}

tDadosPessoais* LeDadosPessoais() {

    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    char dtNasc[TAM_DATA];
    char tel[TAM_TELEFONE];
    char genero[TAM_GENERO];

    // Realiza leitura da entrada padrao
    printf("NOME COMPLETO: ");
    scanf("%[^\n]", nome);
    scanf("%*c"); // consome o '\n'
    printf("CPF: ");
    scanf("%s", cpf);
    printf("DATA DE NASCIMENTO: ");
    scanf("%s", dtNasc);
    printf("TELEFONE: ");
    scanf("%s", tel);
    printf("GENERO: ");
    scanf("%s", genero);

    return CriaDadosPessoais(nome, cpf, dtNasc, tel, genero);
}

void SalvaDadosPessoaisArquivoBinario (tDadosPessoais* d, FILE* file) {
    fwrite(d->nome, sizeof(char), TAM_NOME, file);
    fwrite(d->cpf, sizeof(char), TAM_CPF, file);
    fwrite(d->dtNasc, sizeof(char), TAM_DATA, file);
    fwrite(d->tel, sizeof(char), TAM_TELEFONE, file);
    fwrite(d->genero, sizeof(char), TAM_GENERO, file);
}

tDadosPessoais* ObtemDadosPessoaisArquivoBinario (FILE* file) {

    char nome[TAM_NOME], cpf[TAM_CPF], dtNasc[TAM_DATA];
    char tel[TAM_TELEFONE], genero[TAM_GENERO];

    if (fread(nome, sizeof(char), TAM_NOME, file) != TAM_NOME) return NULL;
    if (fread(cpf, sizeof(char), TAM_CPF, file) != TAM_CPF) return NULL;
    if (fread(dtNasc, sizeof(char), TAM_DATA, file) != TAM_DATA) return NULL;
    if (fread(tel, sizeof(char), TAM_TELEFONE, file) != TAM_TELEFONE) return NULL;
    if (fread(genero, sizeof(char), TAM_GENERO, file) != TAM_GENERO) return NULL;

    return CriaDadosPessoais(nome, cpf, dtNasc, tel, genero);
}

char* ObtemNomeDadosP(tDadosPessoais* d) {
    return d->nome;
}

char* ObtemCPFDadosP(tDadosPessoais* d) {
    return d->cpf;
}

char* ObtemDtNascDadosP(tDadosPessoais* d) {
    return d->dtNasc;
}

char* ObtemTelDadosP(tDadosPessoais* d) {
    return d->tel;
}

char* ObtemGeneroDadosP(tDadosPessoais* d) {
    return d->genero;
}

void DesalocaDadosPessoais(tDadosPessoais* d) {
    if (d) free(d);
}