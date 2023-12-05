#include "tMedico.h"
#define TAM_CRM 12

struct tMedico {
    tDadosPessoais* dadosPessoais;
    tCredenciaisAcesso* credenciaisAcesso;
    char CRM[TAM_CRM];
};


void CadastraMedico(FILE* file) {

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
    
    // Salva Medico no Banco de Dados 
    SalvaMedicoArquivoBinario(medico, file);
    DesalocaMedico(medico);

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

        /* Obtem dados do medico no banco de dados verificando se a leitura ocorre normalmente */
        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) return NULL;

        fread(CRM, sizeof(char), TAM_CRM, file);
        tCredenciaisAcesso* c = ObtemCredenciaisArquivoBinario(file);

        if (CrediciaisSaoIguais(user, senha, c)) {
            m = CriaMedico(d, c, CRM);
            break;
        } 
    
        DesalocaDadosPessoais(d);
        DesalocaCredenciais(c);
    }

    return m;
}


bool VerificaMesmoCPFMedicoBD (FILE* file, char* cpf) {

    int qtdBytesCredenciais = ObtemQtdBytesCredenciais();
    char bufferCRM[TAM_CRM], bufferCredenciais[qtdBytesCredenciais];
    

    while (!feof(file)) {
        
        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) return false;

        fread(bufferCRM, sizeof(char), TAM_CRM, file);
        fread(bufferCredenciais, qtdBytesCredenciais, 1, file);
        
        

    }



    return false;
}

void DesalocaMedico(void* m) {

    if (m == NULL) return;

    tMedico* med = (tMedico*) m;
    DesalocaDadosPessoais(med->dadosPessoais);
    DesalocaCredenciais(med->credenciaisAcesso);
    free(med);
}