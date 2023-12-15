#include "tMedico.h"

struct tMedico {
    tDadosPessoais* dadosPessoais;
    tCredenciais* credenciaisAcesso;
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
    scanf("%s", medico->CRM);
    medico->credenciaisAcesso = LeCredenciaisAcesso();
    
    return medico;
}

tMedico* CriaMedico (tDadosPessoais* d, tCredenciais* c, char* CRM) {

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


void SalvaMedicoArquivoBinario (void* m, FILE* file) {

    tMedico* medico = (tMedico*) m;

    SalvaDadosPessoaisArquivoBinario(medico->dadosPessoais, file);
    SalvaCredenciaisArqvBinario(medico->credenciaisAcesso, file);
    fwrite(medico->CRM, sizeof(char), TAM_CRM, file);

}

Vector* ObtemMedicosBD (FILE* file) {

    rewind(file);

    Vector* v = VectorConstruct();

    while (!feof(file)) {

        char CRM[TAM_CRM];

        /* Obtem dados do medico no banco de dados verificando se a leitura ocorre normalmente */
        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) break;

        tCredenciais* c = ObtemCredenciaisArquivoBinario(file);
        fread(CRM, sizeof(char), TAM_CRM, file);


        tMedico* medico = CriaMedico(d, c, CRM);
        VectorPushBack(v, medico);

    }

    return v;
}

void ImprimeTodosMedicos (Vector* v, FILE* file) {


    for (int i = 0; i < VectorSize(v); i++) {

        tMedico* m = VectorGet(v, i);

        fprintf(file, "NOME: %s\n", ObtemNomeDadosP(m->dadosPessoais));
        fprintf(file, "CPF: %s\n", ObtemCPFDadosP(m->dadosPessoais));
        fprintf(file, "DATA DE NASCIMENTO: ");

        ImprimeDataArquivo(ObtemDtNascDadosP(m->dadosPessoais), file);

        fprintf(file, "TELEFONE: %s\n", ObtemTelDadosP(m->dadosPessoais));
        fprintf(file, "GENERO: %s\n", ObtemGeneroDadosP(m->dadosPessoais));
        fprintf(file, "CRM: %s\n", m->CRM);
        fprintf(file, "NOME DE USUARIO: %s\n", ObtemUserCredenciais(m->credenciaisAcesso));
        fprintf(file, "- - - - - -\n");
 
    }


}


tMedico* ObtemMedicoBD(char* user, char* senha, FILE* file) {

    tMedico* m = NULL;

    while (!feof(file)) {

        char CRM[TAM_CRM];

        /* Obtem dados do medico no banco de dados verificando se a leitura ocorre normalmente */
        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) return NULL;

        tCredenciais* c = ObtemCredenciaisArquivoBinario(file);
        fread(CRM, sizeof(char), TAM_CRM, file);

        if (VerificaCredenciais(user, senha, c)) {
            m = CriaMedico(d, c, CRM);
            break;
        } 
    
        DesalocaDadosPessoais(d);
        DesalocaCredenciais(c);
    }

    return m;
}

char* ObtemCPFMedico (void* m) {
    tMedico* medico = (tMedico*) m;
    return ObtemCPFDadosP(medico->dadosPessoais);
}

char* ObtemCRMMedico (void *m) {
    tMedico* medico = (tMedico*) m;
    return medico->CRM;
}

char* ObtemNomeMedico (void *m) {
    tMedico* medico = (tMedico*) m;
    return ObtemNomeDadosP(medico->dadosPessoais);
}

void DesalocaMedico(void* m) {

    if (m == NULL) return;

    tMedico* med = (tMedico*) m;
    DesalocaDadosPessoais(med->dadosPessoais);
    DesalocaCredenciais(med->credenciaisAcesso);
    free(med);
}