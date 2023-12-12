#include "tListaBusca.h"
#define TAM_MAX_NOME 100

struct tListaBusca {
    tPaciente** pacientes;
    int qtdPacientes;
};

void BuscaPacientes (FILE* file, tFila* fila) {

    char nome[TAM_MAX_NOME];

    TelaImprBuscaPacientes1();
    scanf("%[^\n]", nome);
    scanf("%*c");

    tListaBusca* lista = BuscaPessoaNomeArqv(nome, file);

    // Caso nao encontrou nenhum paciente com o nome informado
    if (lista == NULL) {
        printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        char c; scanf("%c%*c", &c);
        ImprimeBarraFinalMenu();
        return;
    }

    // Imprime os pacienes (caso se foi encontrado ao menos um)
    printf("PACIENTES ENCONTRADOS:\n");
    ImprimeListaBusca(lista);

    // Imprime submenu de busca de pacientes
    TelaImprBuscaPacientes2();
    int op = -1; scanf("%d%*c", &op);
    ImprimeBarraFinalMenu();

    // Insere lista busca na fila de impressao (opcao 1)
    if (op == 1) {
        printf("LISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n");
        char c; scanf("%c%*c", &c);
        ImprimeBarraFinalMenu();
        insereDocumentoFila(fila, lista, ImprimeListaBusca, imprimeEmArquivoListaBusca, DesalocaListaBusca);
        return;
    }
    else DesalocaListaBusca(lista); // retorna menu principal (opcao 2)

}   

tListaBusca* BuscaPessoaNomeArqv (char* nome, FILE* file) {

    // Retorna o arquivo para o inicio
    rewind(file);

    tPaciente** pacientes = NULL;
    int qtd = 0;
    
    while (!feof(file)) {

        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) break; // Caso tenha chegado no fim do arquivo

        // Se os nomes coincidirem retorna o paciente 
        if (ComparaNome(nome, d)) {
            qtd++;
            pacientes = (tPaciente **) realloc(pacientes, sizeof(tPaciente *) * qtd);
            pacientes[qtd - 1] = CriaPaciente(d);
        }
        else DesalocaDadosPessoais(d);

    }

    if (!qtd) return NULL;

    // Aloca uma lista dinamicamente 
    tListaBusca* lista = (tListaBusca*) malloc(sizeof(tListaBusca));
    if (lista == NULL) {
        printf("Falha na alocacao da lista de busca\n");
        exit(EXIT_FAILURE);
    }

    lista->pacientes = pacientes;
    lista->qtdPacientes = qtd;

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
    fclose(file);
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



