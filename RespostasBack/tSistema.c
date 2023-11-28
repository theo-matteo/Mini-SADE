#include "tSistema.h"
#include "tFila.h"
#include "tDocumento.h"
#include "tDadosPessoais.h"
#include "tMedico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tSistema {

    void* usuario; // Ponteiro para o tipo de usuario logado
    userType tipoUsuario; // Pode ser medico, secretario (ADMIN ou USER)

    char caminhoImprDocs[TAM_MAX_DIRETORIO];
    char caminhoBD[TAM_MAX_DIRETORIO]; 

    tFila* filaDocs; 
    FILE* arqvMedicos, *arqvSecretarios;
};

FILE* AbreArquivo(char* path, char* filename) {

    char dir[TAM_MAX_DIRETORIO];
    sprintf(dir, "%s/%s", path, filename);

    FILE* file = fopen(dir, "a+b");    
    if (file == NULL) {
        printf("Falha ao Abrir / Criar Arquivo Binario");
        exit(EXIT_FAILURE);
    }

    return file;
}


tSistema* CriaSistema (char* path) {

    tSistema* sistema = malloc(sizeof(tSistema));
    if (sistema == NULL) {
        printf("Falha na Alocacao do Sistema\n");
        exit(EXIT_FAILURE);
    }

    // Copia caminho para impressao dos documentos
    strcpy(sistema->caminhoImprDocs, path);

    // Usuario logado no sistema inicializado com NULL
    sistema->usuario = NULL;
    sistema->filaDocs = criaFila();

    // Obtem caminho do banco de dados
    printf("################################################\n");
    printf("DIGITE O CAMINHO DO BANCO DE DADOS: ");
    scanf("%s", sistema->caminhoBD);
    printf("\n################################################\n");
    

    sistema->arqvMedicos = AbreArquivo(sistema->caminhoBD, "medicos.bin");
    sistema->arqvSecretarios = AbreArquivo(sistema->caminhoBD, "secretarios.bin");
    
    return sistema;
}

void IniciaSistema (tSistema* s) {

    if (EhPrimeiroAcessoSistema(s)) s->tipoUsuario = ADMIN;
    else AcessaSistemaUsuario(s);
   

}


void AcessaSistemaUsuario (tSistema* s) {

    char user[TAM_NOME_USER], senha[TAM_MAX_SENHA];

    printf("######################## ACESSO MINI-SADE ######################\n");
    printf("DIGITE SEU LOGIN: ");
    scanf("%s", user);
    printf("\nDIGITE SUA SENHA: ");
    scanf("%s", senha);
    printf("###############################################################\n");

    


}

bool EhPrimeiroAcessoSistema (tSistema* s) {

    // Move o ponteiros dos arquivos para o final 
    fseek(s->arqvMedicos, 0, SEEK_END);
    fseek(s->arqvSecretarios, 0, SEEK_END);

    // Verifica se os arquivos estao vazios atraves da posicao
    int size1 = ftell(s->arqvMedicos);
    int size2 = ftell(s->arqvSecretarios);

    // Retorna os ponteiros para inicio
    fseek(s->arqvMedicos, 0, SEEK_SET);
    fseek(s->arqvSecretarios, 0, SEEK_SET);

    if (size1 == 0 && size2 == 0) return true;
    return false;
}

void DesalocaSistema (tSistema* s) {

    if (s->usuario) free(s->usuario);
    desalocaFila(s->filaDocs);
    fclose(s->arqvSecretarios);
    fclose(s->arqvMedicos);
    free(s);

}