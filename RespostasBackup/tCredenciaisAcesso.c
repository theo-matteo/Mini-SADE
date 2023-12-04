#include "tCredenciaisAcesso.h"


struct tCredenciaisAcesso {
    char user[TAM_MAX_USER];
    char senha[TAM_MAX_SENHA];
};

tCredenciaisAcesso* CriaCredenciaisAcesso(char* user, char* senha) {

    tCredenciaisAcesso* c = (tCredenciaisAcesso *) malloc(sizeof(tCredenciaisAcesso));
    if (c == NULL) {
        printf("Falha na Alocacao das Credenciais de Acesso ao Sistema\n");
        exit(EXIT_FAILURE);
    }

    // Inicializa strings com zero
    memset(c->user, '\0', TAM_MAX_USER);
    memset(c->senha, '\0', TAM_MAX_SENHA);

    strcpy(c->user, user);
    strcpy(c->senha, senha);

    return c;
}


tCredenciaisAcesso* LeCredenciaisAcesso () {

    char user[TAM_MAX_USER], senha[TAM_MAX_SENHA];

    printf("NOME DE USUARIO: ");
    scanf("%s", user);
    printf("SENHA: ");
    scanf("%s", senha);

    return CriaCredenciaisAcesso(user, senha);
}


void SalvaCredenciaisArqvBinario (tCredenciaisAcesso* c, FILE* file) {
    fwrite(c->user, sizeof(char), TAM_MAX_USER, file);
    fwrite(c->senha, sizeof(char), TAM_MAX_SENHA, file);
}

tCredenciaisAcesso* ObtemCredenciaisArquivoBinario (FILE* file) {
    
    char user[TAM_MAX_USER], senha[TAM_MAX_SENHA];

    // Verifica se a leitura foi bem sucedida
    if (fread(user, sizeof(char), TAM_MAX_USER, file) != TAM_MAX_USER) return NULL;
    if (fread(senha, sizeof(char), TAM_MAX_SENHA, file) != TAM_MAX_USER) return NULL;

    return CriaCredenciaisAcesso(user, senha); 
}

bool CrediciaisSaoIguais (char *user, char* senha, tCredenciaisAcesso* c) {
    return (!strcmp(user, ObtemUserCredenciais(c)))  && (!strcmp(senha, ObtemSenhaCredenciais(c)));
}

char* ObtemUserCredenciais (tCredenciaisAcesso* c) {
    return c->user;
}

char* ObtemSenhaCredenciais (tCredenciaisAcesso* c) {
    return c->senha;
}

void DesalocaCredenciais (tCredenciaisAcesso* c) {
    if (c) free(c);
}