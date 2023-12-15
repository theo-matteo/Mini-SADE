#include "tCredenciais.h"


struct tCredenciais {
    char user[TAM_MAX_USER];
    char senha[TAM_MAX_SENHA];
};

tCredenciais* CriaCredenciaisAcesso(char* user, char* senha) {

    tCredenciais* c = (tCredenciais *) malloc(sizeof(tCredenciais));
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


tCredenciais* LeCredenciaisAcesso () {

    char user[TAM_MAX_USER], senha[TAM_MAX_SENHA];

    printf("NOME DE USUARIO: ");
    scanf("%s", user);
    printf("SENHA: ");
    scanf("%s", senha);

    return CriaCredenciaisAcesso(user, senha);
}


void SalvaCredenciaisArqvBinario (tCredenciais* c, FILE* file) {
    fwrite(c->user, sizeof(char), TAM_MAX_USER, file);
    fwrite(c->senha, sizeof(char), TAM_MAX_SENHA, file);
}

tCredenciais* ObtemCredenciaisArquivoBinario (FILE* file) {
    
    char user[TAM_MAX_USER], senha[TAM_MAX_SENHA];

    // Verifica se a leitura foi bem sucedida
    if (fread(user, sizeof(char), TAM_MAX_USER, file) != TAM_MAX_USER) return NULL;
    if (fread(senha, sizeof(char), TAM_MAX_SENHA, file) != TAM_MAX_USER) return NULL;

    return CriaCredenciaisAcesso(user, senha); 
}

bool VerificaCredenciais (char *user, char* senha, tCredenciais* c) {
    return (!strcmp(user, ObtemUserCredenciais(c)))  && (!strcmp(senha, ObtemSenhaCredenciais(c)));
}

int ObtemQtdBytesCredenciais () {
    return sizeof(tCredenciais);
}

char* ObtemUserCredenciais (tCredenciais* c) {
    return c->user;
}

char* ObtemSenhaCredenciais (tCredenciais* c) {
    return c->senha;
}

void DesalocaCredenciais (tCredenciais* c) {
    if (c) free(c);
}