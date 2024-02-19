#include "tPaciente.h"

struct tPaciente {
    tDadosPessoais* dadosPessoais;
};


tPaciente* CriaPaciente (tDadosPessoais* d) {

    tPaciente* p = (tPaciente*) malloc(sizeof(tPaciente));
    if (!p) {
        printf("Falha na Alocacao do Paciente\n");
        exit(EXIT_FAILURE);
    }

    p->dadosPessoais = d;
    return p;
}

tPaciente* CadastraPaciente () {
    printf("#################### CADASTRO PACIENTE #######################\n");
    tDadosPessoais* dadosPessoais = LeDadosPessoais();
    return CriaPaciente(dadosPessoais);
}

void SalvaPacienteArquivoBinario (void* p, FILE* file) {
    tPaciente* paciente = (tPaciente*) p;
    SalvaDadosPessoaisArquivoBinario(paciente->dadosPessoais, file);
}


Vector* ObtemPacientesBD (FILE* file) {

    rewind(file);

    Vector* v = VectorConstruct();

    while (true) {
        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) break;
        tPaciente* paciente = CriaPaciente(d);
        VectorPushBack(v, paciente);
    }
    
    return v;

}


char* ObtemCPFPaciente (void* paciente) {
    tPaciente* p = (tPaciente*) paciente;
    return ObtemCPFDadosP(p->dadosPessoais);
}

char* ObtemNomePaciente (void* p) {
    tPaciente* paciente = (tPaciente*) p;
    return ObtemNomeDadosP(paciente->dadosPessoais);
}

char* ObtemDtNascPaciente (void *p) {
    tPaciente* paciente = (tPaciente*) p;
    return ObtemDtNascDadosP(paciente->dadosPessoais);
}

void ImprimePaciente(tPaciente* p, FILE* file) {
    fprintf(file, "NOME: %s\n", ObtemNomePaciente(p));
    fprintf(file, "CPF: %s\n", ObtemCPFPaciente(p));
    fprintf(file, "DATA DE NASCIMENTO: ");
    ImprimeDataArquivo(ObtemDtNascPaciente(p), file);
    fprintf(file, "TELEFONE: %s\n", ObtemTelDadosP(p->dadosPessoais));
    fprintf(file, "GENERO: %s\n", ObtemGeneroDadosP(p->dadosPessoais));
}

void DesalocaPaciente (void* p) {
    
    if (p == NULL) return;
    
    tPaciente* paciente = (tPaciente*) p;
    DesalocaDadosPessoais(paciente->dadosPessoais);
    free(paciente);
}

