#include "tListaBusca.h"
#define TAM_MAX_NOME 100


void BuscaPacientes (FILE* file, tFila* fila) {

    char nome[TAM_MAX_NOME];
    TelaImprBuscaPacientes1();

    scanf("%[^\n]", nome);
    scanf("%*c");

    Vector* lista = BuscaPacientesNomeArqvBinario (nome, file);

    // Caso nao encontrou nenhum paciente com o nome informado
    if (!lista ) {
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
        printf("\nLISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n");
        char c; scanf("%c%*c", &c);
        ImprimeBarraFinalMenu();
        insereDocumentoFila(fila, lista, ImprimeListaBusca, imprimeEmArquivoListaBusca, DesalocaListaBusca);
        return;
    }
    else DesalocaListaBusca(lista); // retorna menu principal (opcao 2)

}   

Vector* BuscaPacientesNomeArqvBinario (char* nome, FILE* file) {

    // Retorna o arquivo para o inicio
    rewind(file);

    // Vetor de pacientes
    Vector* pacientes = VectorConstruct();
    
    while (!feof(file)) {

        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) break; // Caso tenha chegado no fim do arquivo

        // Se os nomes coincidirem armazena um paciente
        if (VerificaNomesIguais(nome, d)) VectorPushBack(pacientes, CriaPaciente(d));
        else DesalocaDadosPessoais(d);

    }

    if (VectorSize(pacientes) == 0) {
        VectorDestroy(pacientes, DesalocaPaciente);
        return NULL;
    }

    return pacientes;
}


void ImprimeListaBusca(void* l) {

    Vector* lista = (Vector*) l;

    for (int i = 0; i < VectorSize(lista); i++) {
        tPaciente* p = VectorGet(lista, i);
        char* nome = ObtemNomePaciente(p);
        char* cpf = ObtemCPFPaciente(p);
        printf("%d - %s (%s)\n", i + 1, nome, cpf);
    }

    printf("\n");    
}

void imprimeEmArquivoListaBusca(void *dado, char *path) {

    Vector* lista = (Vector*) dado;
    char pathDoc [strlen(path) + strlen("/lista_busca.txt") + 1];
    sprintf(pathDoc, "%s/%s", path, "lista_busca.txt");
    FILE* file = fopen(pathDoc, "a");

    if (file == NULL) {
        printf("Nao foi possivel abrir o arquivo de lista_busca no diretorio: %s\n", pathDoc);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < VectorSize(lista); i++) {
        tPaciente* p = VectorGet(lista, i);
        char* nome = ObtemNomePaciente(p);
        char* cpf = ObtemCPFPaciente(p);
        fprintf(file, "%d - %s (%s)\n", i + 1, nome, cpf);
    }

    fprintf(file, "\n");  
    fclose(file);
}

void DesalocaListaBusca(void* l) {
    if (l == NULL) return;
    Vector* lista = (Vector*) l;
    VectorDestroy(lista, DesalocaPaciente);
}



