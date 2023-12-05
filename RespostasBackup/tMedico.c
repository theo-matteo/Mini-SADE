#include "tMedico.h"

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

    // Inicializa strings com '\0'
    memset(medico->CRM, '\0', TAM_CRM);

    // Realiza leitura dos dados pela entrada padrao
    printf("#################### CADASTRO MEDICO #######################\n");
    medico->dadosPessoais = LeDadosPessoais();
    printf("CRM: ");
    scanf("%s%*c", medico->CRM);
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
    SalvaCredenciaisArqvBinario(s->credenciaisAcesso, file);
    fwrite(s->CRM, sizeof(char), TAM_CRM, file);
}

tMedico* ObtemMedicoArquivoBinario (char* user, char* senha, FILE* file) {

    tMedico* m = NULL;

    while (!feof(file)) {

        char CRM[TAM_CRM];

        /* Obtem dados do medico no banco de dados verificando se a leitura ocorre normalmente */
        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) return NULL;

        tCredenciaisAcesso* c = ObtemCredenciaisArquivoBinario(file);
        fread(CRM, sizeof(char), TAM_CRM, file);

        if (CrediciaisSaoIguais(user, senha, c)) {
            m = CriaMedico(d, c, CRM);
            break;
        } 
    
        DesalocaDadosPessoais(d);
        DesalocaCredenciais(c);
    }

    return m;
}

tDadosPessoais* ObtemDPMedico (tMedico* m) {
    return m->dadosPessoais;
}

void DesalocaMedico(void* m) {

    if (m == NULL) return;

    tMedico* med = (tMedico*) m;
    DesalocaDadosPessoais(med->dadosPessoais);
    DesalocaCredenciais(med->credenciaisAcesso);
    free(med);
}