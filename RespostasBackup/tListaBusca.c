#include "tListaBusca.h"
#define TAM_MAX_NOME 100

struct tListaBusca {
    tPaciente** pacientes;
    int qtdPacientes;
};

tListaBusca* BuscaPacientes (FILE* file) {

    char nome[TAM_MAX_NOME];

    printf("#################### BUSCAR PACIENTES #######################\n");
    printf("NOME DO PACIENTE: ");
    scanf("%[^\n]", nome);
    scanf("%*c");

    tListaBusca* lista = BuscaPessoasArqvBinario(nome, file);

    // Caso nao encontrou nenhum paciente com o nome informado
    if (lista == NULL) {
        printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        char c; scanf("%c%*c", &c);
        printf("############################################################\n");
        return NULL;
    }

    printf("PACIENTES ENCONTRADOS:\n");
    ImprimeListaBusca(lista);

    int op = -1;
    printf("#################### BUSCAR PACIENTES #######################\n");
    printf("ESCOLHA UMA OPCAO:\n");
    printf("\t(1) ENVIAR LISTA PARA IMPRESSAO\n");
    printf("\t(2) RETORNAR AO MENU PRINCIPAL\n");
    scanf("%d%*c", &op);
    printf("############################################################\n");

    if (op == 1) {
        printf("LISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n");
        char c; scanf("%c%*c", &c);
        printf("############################################################\n");
        return lista;
    }

    // Desaloca lista de busca o usuario nao queira enviar para a fila de impressao
    if (lista) DesalocaListaBusca(lista);
    return NULL;

}   

tListaBusca* BuscaPessoasArqvBinario (char* nome, FILE* file) {

    // Retorna o arquivo para o inicio
    rewind(file);

    tPaciente** pacientes = NULL;
    int qtdEncontrados = 0;
    
    while (!feof(file)) {

        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) break;

        // Se os nomes coincidirem retorna o paciente 
        if (NomeSaoIguais(nome, d)) {
            qtdEncontrados++;
            pacientes = (tPaciente **) realloc(pacientes, sizeof(tPaciente *) * qtdEncontrados);
            pacientes[qtdEncontrados - 1] = CriaPaciente(d);
        }
        else DesalocaDadosPessoais(d);

    }

    if (qtdEncontrados == 0) return NULL;

    tListaBusca* lista = (tListaBusca*) malloc(sizeof(tListaBusca));
    if (lista == NULL) {
        printf("Falha na alocacao da lista de busca\n");
        exit(EXIT_FAILURE);
    }

    lista->pacientes = pacientes;
    lista->qtdPacientes = qtdEncontrados;

    return lista;
}


void ImprimeListaBusca(void* l) {

    tListaBusca* lista = (tListaBusca*) l;

    for (int i = 0; i < ObtemQtdPacientesListaBusca(lista); i++) {
        char* nome = ObtemNomePaciente(lista->pacientes[i]);
        char* cpf = ObtemCPFPaciente(lista->pacientes[i]);
        printf("%d - %s (%s)\n", i + 1, nome, cpf);
    }

    printf("\n");    
}

void imprimeEmArquivoListaBusca(void *dado, char *path) {

    tListaBusca* lista = (tListaBusca*) dado;
    char pathDoc [strlen(path) + strlen("/lista_busca.txt") + 1];

    sprintf(pathDoc, "%s/%s", path, "lista_busca.txt");

    FILE* file = fopen(pathDoc, "a");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo de lista_busca no diretorio: %s\n", pathDoc);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ObtemQtdPacientesListaBusca(lista); i++) {
        char* nome = ObtemNomePaciente(lista->pacientes[i]);
        char* cpf = ObtemCPFPaciente(lista->pacientes[i]);
        fprintf(file, "%d - %s (%s)\n", i + 1, nome, cpf);
    }

    fprintf(file, "\n");  
}

int ObtemQtdPacientesListaBusca (tListaBusca* l) {
    return l->qtdPacientes;
}

void DesalocaListaBusca(void* l) {

    if (l == NULL) return;

    tListaBusca* lista = (tListaBusca*) l;

    if (lista->pacientes != NULL) {
        for (int i = 0; i < ObtemQtdPacientesListaBusca(l); i++) {
            DesalocaPaciente(lista->pacientes[i]);
        }
        free(lista->pacientes);
    }

    free(lista);
}



