#include "tPaciente.h"

struct tPaciente {
    tDadosPessoais* dadosPessoais;
};


tPaciente* CadastraPaciente () {

    tPaciente* p = (tPaciente*) malloc(sizeof(tPaciente));
    if (!p) {
        printf("Falha na Alocacao do Paciente\n");
        exit(EXIT_FAILURE);
    }

    printf("#################### CADASTRO PACIENTE #######################\n");
    p->dadosPessoais = LeDadosPessoais();

    return p;
}

void SalvaPacienteArquivoBinario (void* p, FILE* file) {
    tPaciente* paciente = (tPaciente*) p;
    SalvaDadosPessoaisArquivoBinario(paciente->dadosPessoais, file);
}


tPaciente* BuscaPacienteArqvBinario (char* nome, FILE* file) {

    // to do

}


void DesalocaPaciente (void* p) {
    if (!p) return;
    tPaciente* paciente = (tPaciente*) p;
    DesalocaDadosPessoais(paciente->dadosPessoais);
    free(paciente);
}

