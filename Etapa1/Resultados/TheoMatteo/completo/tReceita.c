#include "tReceita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_MAX_NOME 100
#define TAM_CRM 12
#define TAM_INSTRUCOES 300
#define TAM_DATA 12

struct tReceita {
    char nomePaciente[TAM_MAX_NOME];
    eTipoUso tipoUso;
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    int qtd;
    char instrucoes[TAM_INSTRUCOES];
    char nomeMedico[TAM_MAX_NOME];
    char CRM[TAM_CRM];
    char dataStr[TAM_DATA];
};

tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
                      char *tipoMedicamento, char *instrucoes, int qntd,
                      char *nomeMedico, char *CRM, char *dataStr)
{
    tReceita* receita = (tReceita*) malloc (sizeof(tReceita));
    if (receita == NULL) {
        printf("Erro na Alocacao da Receita\n");
        exit(EXIT_FAILURE);
    }

    receita->tipoUso = tipoUso;
    receita->qtd = qntd;

    strcpy(receita->nomePaciente, nomePaciente);
    strcpy(receita->nomeMedicamento, nomeMedicamento);
    strcpy(receita->tipoMedicamento, tipoMedicamento);
    strcpy(receita->instrucoes, instrucoes);
    strcpy(receita->nomeMedico, nomeMedico);
    strcpy(receita->CRM, CRM);
    strcpy(receita->dataStr, dataStr);

    return receita;
}

void desalocaReceita(void *dado) {
    if(dado) free(dado);
}

void imprimeNaTelaReceita(void *dado) {

    if (dado == NULL) return;
    tReceita* r = (tReceita *) dado;

    printf("RECEITUARIO\n");
    printf("NOME: %s\n\n", r->nomePaciente);

    if (r->tipoUso == ORAL) printf("USO ORAL\n\n");
    else printf("USO TOPICO\n\n");

    printf("%s\n", r->nomeMedicamento);
    printf("%d %s\n\n", r->qtd, r->tipoMedicamento);
    printf("%s\n\n", r->instrucoes);
    printf("%s (%s)\n", r->nomeMedico, r->CRM);


    // Formatacao da data
    int dia, mes, ano;
    sscanf(r->dataStr, "%d/%d/%d", &dia, &mes, &ano);
    printf("%d/%d/%d", dia, mes, ano);
    printf("\n\n");

}

void imprimeEmArquivoReceita(void *dado, char *path) {

    tReceita* r = (tReceita *) dado;
    char pathDoc [strlen(path) + strlen("/receita.txt") + 1];
    
    // Concatenacao do caminho + nome arquivo
    sprintf(pathDoc, "%s/%s", path, NOME_ARQUIVO_RECEITA);

    // Dados sao adicionados no fim do arquivo no modo 'a'
    FILE* file = fopen(pathDoc, "a");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo de receita no diretorio: %s\n", pathDoc);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "RECEITUARIO\n");
    fprintf(file, "NOME: %s\n\n", r->nomePaciente);
    if (r->tipoUso == ORAL) fprintf(file, "USO ORAL\n\n");
    else fprintf(file, "USO TOPICO\n\n");
    fprintf(file, "%s\n", r->nomeMedicamento);
    fprintf(file, "%d %s\n\n", r->qtd, r->tipoMedicamento);
    fprintf(file, "%s\n\n", r->instrucoes);
    fprintf(file, "%s (%s)\n", r->nomeMedico, r->CRM);

     // Formatacao da data
    int dia, mes, ano;
    sscanf(r->dataStr, "%d/%d/%d", &dia, &mes, &ano);
    fprintf(file, "%d/%d/%d", dia, mes, ano);
    fprintf(file, "\n\n");
    

    fclose(file);
}