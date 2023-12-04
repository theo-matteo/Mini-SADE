#include "tMedico.h"
#define TAM_CRM 12

struct tMedico {
    tDadosPessoais* dadosPessoais;
    tCredenciaisAcesso* credenciaisAcesso;
    char CRM[TAM_CRM];
};


tMedico* CadastraMedico() {

    tMedico* medico = (tMedico *) malloc(sizeof(tMedico));
    if (medico == NULL) {
        printf("Falha na Alocacao do Medico\n");
        exit(EXIT_FAILURE);
    }

    memset(medico->CRM, '\0', TAM_CRM);

    printf("#################### CADASTRO MEDICO #######################\n");
    medico->dadosPessoais = LeDadosPessoais();
    printf("CRM: ");
    scanf("%s", medico->CRM);
    medico->credenciaisAcesso = LeCredenciaisAcesso();
    
    return medico;
}

tMedico* CriaMedico (tDadosPessoais* d, tCredenciaisAcesso* c, char* CRM) {

    tMedico* medico = (tMedico *) malloc(sizeof(tMedico));
    if (medico == NULL) {
        printf("Falha na Alocacao do Medico\n");
        exit(EXIT_FAILURE);
    }

    memset(medico->CRM, '\0', TAM_CRM);

    medico->credenciaisAcesso = c;
    medico->dadosPessoais = d;
    strcpy(medico->CRM, CRM);

    return medico;
}



void SalvaMedicoArquivoBinario (tMedico* s, FILE* file) {
    SalvaDadosPessoaisArquivoBinario(s->dadosPessoais, file);
    fwrite(s->CRM, sizeof(char), TAM_CRM, file);
    SalvaCredenciaisArqvBinario(s->credenciaisAcesso, file);
}

tMedico* ObtemMedicoArquivoBinario (char* user, char* senha, FILE* file) {

    tMedico* m = NULL;

    while (!feof(file)) {

        char CRM[TAM_CRM];
        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) return NULL;

        fread(CRM, sizeof(char), TAM_CRM, file);

        tCredenciaisAcesso* c = ObtemCredenciaisArquivoBinario(file);

        if (CrediciaisSaoIguais(user, senha, c)) {
            m = CriaMedico(d, c, CRM);
        }

        DesalocaDadosPessoais(d);
        DesalocaCredenciais(c);
    }

    return m;
}

void DesalocaMedico(void* m) {

    if (m == NULL) return;

    tMedico* med = (tMedico*) m;
    DesalocaDadosPessoais(med->dadosPessoais);
    DesalocaCredenciais(med->credenciaisAcesso);
    free(med);
}