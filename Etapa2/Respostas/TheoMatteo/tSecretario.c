#include "tSecretario.h"

struct tSecretario {
    tDadosPessoais* dadosPessoais;
    tCredenciais* credenciaisAcesso;
    char nivelAcesso[TAM_MAX_NIVEL_ACESSO];
};


tSecretario* CriaSecretario (tDadosPessoais* d, tCredenciais* c, char* nivelAcesso) {

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

    // Inicializa string com '\0'
    memset(s->nivelAcesso, '\0', TAM_MAX_NIVEL_ACESSO);

    /* Realiza Leitura da Entrada Padrao */
    printf("#################### CADASTRO SECRETARIO #######################\n");
    s->dadosPessoais = LeDadosPessoais();
    s->credenciaisAcesso = LeCredenciaisAcesso();
    printf("NIVEL DE ACESSO: ");
    scanf("%s", s->nivelAcesso);

    return s;
}


void SalvaSecretarioArquivoBinario (void* sec, FILE* file) {

    tSecretario* s = (tSecretario*) sec;

    SalvaDadosPessoaisArquivoBinario(s->dadosPessoais, file);
    SalvaCredenciaisArqvBinario(s->credenciaisAcesso, file);
    fwrite(s->nivelAcesso, sizeof(char), TAM_MAX_NIVEL_ACESSO, file);
}

Vector* ObtemSecretariosBD (FILE* file) {

    rewind(file);

    Vector* v = VectorConstruct();

    while (!feof(file)) {

        char nivelAcesso[TAM_MAX_NIVEL_ACESSO]; 

        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) {
            break;
        }

        tCredenciais* c = ObtemCredenciaisArquivoBinario(file);
        fread(nivelAcesso, sizeof(char), TAM_MAX_NIVEL_ACESSO, file);
        tSecretario* secretario = CriaSecretario(d, c, nivelAcesso);
        VectorPushBack(v, secretario);

    }
    
    return v;
}

void ImprimeTodosSecretarios (Vector* v, FILE* file) {

    for (int i = 0; i < VectorSize(v); i++) {

        tSecretario* s = VectorGet(v, i);

        fprintf(file, "NOME: %s\n", ObtemNomeDadosP(s->dadosPessoais));
        fprintf(file, "CPF: %s\n", ObtemCPFDadosP(s->dadosPessoais));
        fprintf(file, "DATA DE NASCIMENTO: ");
        ImprimeDataArquivo(ObtemDtNascDadosP(s->dadosPessoais), file);
        fprintf(file, "TELEFONE: %s\n", ObtemTelDadosP(s->dadosPessoais));
        fprintf(file, "GENERO: %s\n", ObtemGeneroDadosP(s->dadosPessoais));
        fprintf(file, "NOME DE USUARIO: %s\n", ObtemUserCredenciais(s->credenciaisAcesso));
        fprintf(file, "NIVEL DE ACESSO: %s\n", s->nivelAcesso);
        fprintf(file, "- - - - - -\n");
 
    }


}


tSecretario* ObtemSecretarioBD (char* user, char* senha, FILE* file) {

    tSecretario* s = NULL;

    while (!feof(file)) {

        char nivelAcesso[TAM_MAX_NIVEL_ACESSO]; 

        tDadosPessoais* d = ObtemDadosPessoaisArquivoBinario(file);
        if (!d) return NULL;

        tCredenciais* c = ObtemCredenciaisArquivoBinario(file);
        if (!c) return NULL;

        fread(nivelAcesso, sizeof(char), TAM_MAX_NIVEL_ACESSO, file);

        // Verifica se as credenciais se coincidem, se sim cria um secretario
        if (VerificaCredenciais(user, senha, c)) {
            s = CriaSecretario(d, c, nivelAcesso);
            break;
        }

        DesalocaDadosPessoais(d);
        DesalocaCredenciais(c);
    }

    return s;
}

char* ObtemNivelAcessoSecretario (tSecretario* s) {
    return s->nivelAcesso;
}

int VerificaAcessoAdminSec (tSecretario* sec) {
    return (!strcmp(ObtemNivelAcessoSecretario(sec), "ADMIN"));
}

char* ObtemCPFSecretario (void* sec) {
    tSecretario* s = (tSecretario*) sec;
    return ObtemCPFDadosP(s->dadosPessoais);
}


void DesalocaSecretario(void* s) {

    if (s == NULL) return;

    tSecretario* secretario = (tSecretario*) s;
    DesalocaDadosPessoais(secretario->dadosPessoais);
    DesalocaCredenciais(secretario->credenciaisAcesso);
    free(s);
    
}