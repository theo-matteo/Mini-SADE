#include "tSecretario.h"
#define TAM_MAX_NIVEL_ACESSO 10

struct tSecretario {
    tDadosPessoais* dadosPessoais;
    tCredenciaisAcesso* credenciaisAcesso;
    char nivelAcesso[TAM_MAX_NIVEL_ACESSO];
};


tSecretario* CriaSecretario (tDadosPessoais* d, tCredenciaisAcesso* c, char* nivelAcesso) {

    tSecretario* s = (tSecretario*) malloc(sizeof(tSecretario));
    if (s == NULL) {
        printf("Falha na Alocacao do Secretario!\n");
        exit(EXIT_FAILURE);
    }

    memset(s->nivelAcesso, '\0', TAM_MAX_NIVEL_ACESSO);
    s->dadosPessoais = d;
    s->credenciaisAcesso = c;
    strcpy(s->nivelAcesso, nivelAcesso);

    return s;
}

tSecretario* CadastraSecretario () {

    tSecretario* s = (tSecretario*) malloc(sizeof(tSecretario));
    if (s == NULL) {
        printf("Falha na Alocacao do Secretario!\n");
        exit(EXIT_FAILURE);
    }

    memset(s->nivelAcesso, '\0', TAM_MAX_NIVEL_ACESSO);

    printf("#################### CADASTRO SECRETARIO #######################\n");
    s->dadosPessoais = LeDadosPessoais();
    s->credenciaisAcesso = LeCredenciaisAcesso();
    printf("NIVEL DE ACESSO: ");
    scanf("%s", s->nivelAcesso);

    return s;
}

void SalvaSecretarioArquivoBinario (tSecretario* s, FILE* file) {
    SalvaDadosPessoaisArquivoBinario(s->dadosPessoais, file);
    SalvaCredenciaisArqvBinario(s->credenciaisAcesso, file);
    fwrite(s->nivelAcesso, sizeof(char), TAM_MAX_NIVEL_ACESSO, file);
}


tSecretario* ObtemSecretarioArqvBinario (char* user, char* senha, FILE* file) {

    tSecretario* s = NULL;

    while (!feof(file)) {

        char nivelAcesso[TAM_MAX_NIVEL_ACESSO]; 

        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) return NULL;

        tCredenciaisAcesso* c = ObtemCredenciaisArquivoBinario(file);
        if (!c) return NULL;

        fread(nivelAcesso, sizeof(char), TAM_MAX_NIVEL_ACESSO, file);

        // Verifica se as credenciais se coincidem, se sim cria um secretario
        if (CrediciaisSaoIguais(user, senha, c)) {
            s = CriaSecretario(d, c, nivelAcesso);
            break;
        }

        DesalocaDadosPessoais(d);
        DesalocaCredenciais(c);
    }

    // Retorna o ponteiro do arquivo para o inicio
    fseek(file, 0, SEEK_SET);   
    return s;
}

char* ObtemNivelAcessoSecretario (tSecretario* s) {
    return s->nivelAcesso;
}

int EhSecretarioADMIN (tSecretario* sec) {
    return (!strcmp(ObtemNivelAcessoSecretario(sec), "ADMIN"));
}


void DesalocaSecretario(void* s) {

    if (s == NULL) return;

    tSecretario* secretario = (tSecretario*) s;
    DesalocaDadosPessoais(secretario->dadosPessoais);
    DesalocaCredenciais(secretario->credenciaisAcesso);
    free(s);
    
}